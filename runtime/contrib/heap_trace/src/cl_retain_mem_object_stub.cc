/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "trace.h"
#include "function_resolver.h"

#include <CL/cl.h>

#include <memory>

extern std::unique_ptr<Trace> GlobalTrace;

extern "C" {

cl_int clRetainMemObject(cl_mem mem)
{
  static auto isOriginalFunctionCallSuccessful = [](cl_int result) -> bool {
    return result == CL_SUCCESS;
  };

  auto originalFunction = findFunctionByName<cl_int, cl_mem>("clRetainMemObject");
  cl_int result = originalFunction(mem);
  if (isOriginalFunctionCallSuccessful(result) && !Trace::Guard{}.isActive())
  {
    GlobalTrace->logAllocationEvent(mem, 0);
  }

  return result;
}
}
