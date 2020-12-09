/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef __ONERT_BACKEND_ACL_CL_TENSOR_BUILDER_H__
#define __ONERT_BACKEND_ACL_CL_TENSOR_BUILDER_H__

#include <AclTensorBuilder.h>

#include "operand/CLTensor.h"
#include "operand/CLSubTensor.h"

namespace onert
{
namespace backend
{
namespace acl_cl
{

using TensorBuilder =
  acl_common::AclTensorBuilder<operand::ICLTensor, operand::CLTensor, operand::CLSubTensor>;

} // namespace acl_cl
} // namespace backend
} // namespace onert

#endif // __ONERT_BACKEND_ACL_CL_TENSOR_BUILDER_H__
