/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All Rights Reserved
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

#ifndef _NNC_CORE_BACKEND_INTERPRETER_MAX_POOL_2D_
#define _NNC_CORE_BACKEND_INTERPRETER_MAX_POOL_2D_

#include "mir/ops/MaxPool2DOp.h"
#include "mir/TensorVariant.h"

namespace mir_interpreter
{

void MaxPool2D(const mir::TensorVariant &input, const mir::ops::MaxPool2DOp &op,
               mir::TensorVariant &result);

} // namespace mir_interpreter

#endif //_NNC_CORE_BACKEND_INTERPRETER_MAX_POOL_2D_
