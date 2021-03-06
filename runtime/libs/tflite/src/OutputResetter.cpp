/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "tflite/OutputResetter.h"
#include "tflite/TensorView.h"

#include <misc/tensor/IndexIterator.h>

namespace nnfw
{
namespace tflite
{

void OutputResetter::run(::tflite::Interpreter &interp)
{
  for (const auto &tensor_idx : interp.outputs())
  {
    TfLiteTensor *tensor = interp.tensor(tensor_idx);
    switch (tensor->type)
    {
      case kTfLiteInt32:
        resetValue<int32_t>(interp, tensor_idx);
        break;
      case kTfLiteUInt8:
        resetValue<uint8_t>(interp, tensor_idx);
        break;
      case kTfLiteInt8:
        resetValue<int8_t>(interp, tensor_idx);
        break;
      case kTfLiteBool:
        resetValue<bool>(interp, tensor_idx);
        break;
      case kTfLiteFloat32:
        resetValue<float>(interp, tensor_idx);
        break;
      default:
        throw std::runtime_error{"Not supported output type"};
    }
  }
}

template <typename T> void OutputResetter::resetValue(::tflite::Interpreter &interp, int tensor_idx)
{
  auto tensor_view = nnfw::tflite::TensorView<T>::make(interp, tensor_idx);

  nnfw::misc::tensor::iterate(tensor_view.shape())
    << [&](const nnfw::misc::tensor::Index &ind) { tensor_view.at(ind) = 0; };
}

} // namespace tflite
} // namespace nnfw
