/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ElementwiseActivationLayer.h"

#include "OperationUtils.h"

#include <cker/operation/Logistic.h>
#include <cker/operation/ReLU.h>
#include <cker/operation/ReLU6.h>
#include <cker/operation/Tanh.h>

namespace onert
{
namespace backend
{
namespace cpu
{
namespace ops
{

ElementwiseActivationLayer::ElementwiseActivationLayer()
    : _input(nullptr), _output(nullptr), _kernel()
{
  // DO NOTHING
}

void ElementwiseActivationLayer::PopulateLookupTable(const ElementwiseActivationType op_type)
{
  const auto input_scale = static_cast<double>(_input->data_scale());
  const auto input_zero_point = static_cast<int32_t>(_input->data_offset());
  const auto output_scale = static_cast<double>(_output->data_scale());
  const auto output_zero_point = static_cast<int32_t>(_output->data_offset());
  const float inverse_scale = 1 / output_scale;
  int32_t maxval = std::numeric_limits<uint8_t>::max();
  int32_t minval = std::numeric_limits<uint8_t>::min();
  for (int32_t val = minval; val <= maxval; ++val)
  {
    const float dequantized = input_scale * (val - input_zero_point);
    float transformed = 0.f;
    if (op_type == ElementwiseActivationType::kTanh)
    {
      transformed = std::tanh(dequantized);
    }
    else if (op_type == ElementwiseActivationType::kLogistic)
    {
      transformed = 1.0f / (1.0f + std::exp(-dequantized));
    }
    else
    {
      throw std::runtime_error("ElementwiseActivationLayer : unsupported activation type");
    }
    const float rescaled = std::round(transformed * inverse_scale);
    const int32_t quantized = static_cast<int32_t>(rescaled + output_zero_point);
    _table[val] = static_cast<uint8_t>(std::max(std::min(maxval, quantized), minval));
  }
}

void ElementwiseActivationLayer::EvalUsingLookupTable(const IPortableTensor *input,
                                                      IPortableTensor *output)
{
  const int size = MatchingFlatSize(getTensorShape(input), getTensorShape(output));
  const uint8_t *input_data = reinterpret_cast<const uint8_t *>(input->buffer());
  uint8_t *output_data = reinterpret_cast<uint8_t *>(output->buffer());

  for (int i = 0; i < size; ++i)
  {
    output_data[i] = _table[input_data[i]];
  }
}

void ElementwiseActivationLayer::configure(const IPortableTensor *input, IPortableTensor *output,
                                           float alpha, float beta,
                                           ElementwiseActivationType op_type)
{
  _input = input;
  _output = output;

  switch (op_type)
  {
    case ElementwiseActivationType::kLogistic:
      if (_input->data_type() == OperandType::QUANT_UINT8_ASYMM)
      {
        PopulateLookupTable(op_type);
        _kernel = std::bind(&ElementwiseActivationLayer::EvalUsingLookupTable, this,
                            std::placeholders::_1, std::placeholders::_2);
      }
      else if (_input->data_type() == OperandType::FLOAT32)
      {
        _kernel = [](const IPortableTensor *input, IPortableTensor *output) {
          nnfw::cker::Logistic(getTensorShape(input),
                               reinterpret_cast<const float *>(input->buffer()),
                               getTensorShape(output), reinterpret_cast<float *>(output->buffer()));
        };
      }
      else
      {
        throw std::runtime_error{"ElementwiseActivationLayer(Logistic): unsupported data type"};
      }
      break;
    case ElementwiseActivationType::kReLU:
      if (_input->data_type() == OperandType::FLOAT32)
      {
        if (alpha == std::numeric_limits<float>::infinity() && beta == 0.f)
        {
          _kernel = [](const IPortableTensor *input, IPortableTensor *output) {
            nnfw::cker::ReLU(getTensorShape(input),
                             reinterpret_cast<const float *>(input->buffer()),
                             getTensorShape(output), reinterpret_cast<float *>(output->buffer()));
          };
        }
        else if (alpha == 6.f && beta == 0.f)
        {
          _kernel = [](const IPortableTensor *input, IPortableTensor *output) {
            nnfw::cker::ReLU6(getTensorShape(input),
                              reinterpret_cast<const float *>(input->buffer()),
                              reinterpret_cast<float *>(output->buffer()));
          };
        }
        else
        {
          throw std::runtime_error(
              "ElementwiseActivationLayer : This layer suppports only ReLU(0-inf) and ReLU6(0-6)");
        }
      }
      else
      {
        throw std::runtime_error{"ElementwiseActivationLayer(ReLU): unsupported data type"};
      }
      break;
    case ElementwiseActivationType::kTanh:
      if (_input->data_type() == OperandType::QUANT_UINT8_ASYMM)
      {
        PopulateLookupTable(op_type);
        _kernel = std::bind(&ElementwiseActivationLayer::EvalUsingLookupTable, this,
                            std::placeholders::_1, std::placeholders::_2);
      }
      else if (_input->data_type() == OperandType::FLOAT32)
      {
        _kernel = [](const IPortableTensor *input, IPortableTensor *output) {
          nnfw::cker::Tanh(getTensorShape(input), reinterpret_cast<const float *>(input->buffer()),
                           getTensorShape(output), reinterpret_cast<float *>(output->buffer()));
        };
      }
      else
      {
        throw std::runtime_error{"ElementwiseActivationLayer(Logistic): unsupported data type"};
      }
      break;
    default:
      throw std::runtime_error("ElementwiseActivationLayer: unsupported op type");
  }
}

void ElementwiseActivationLayer::run() { _kernel(_input, _output); }

} // namespace ops
} // namespace cpu
} // namespace backend
} // namespace onert