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

#ifndef __LOCOEX_IR_CIRCLENODEDECL_H__
#define __LOCOEX_IR_CIRCLENODEDECL_H__

#include <loco/IR/Node.h>
#include <loco/IR/Dialect.h>

#include "CircleOpcode.h"
#include "CircleNodeVisitor.forward.h"

namespace locoex
{

struct CircleNode : public loco::Node
{
  virtual ~CircleNode() = default;

  const loco::Dialect *dialect(void) const final;
  virtual CircleOpcode opcode(void) const = 0;

  template <typename T> T accept(CircleNodeVisitorBase<T> *) const;
  template <typename T> T accept(CircleNodeMutableVisitorBase<T> *);
};

template <CircleOpcode Code> struct CircleNodeImpl : public CircleNode
{
  virtual ~CircleNodeImpl() = default;

  uint32_t opnum(void) const final { return static_cast<uint32_t>(Code); }
  CircleOpcode opcode(void) const final { return Code; }
};

} // namespace locoex

#endif // __LOCOEX_IR_CIRCLENODEDECL_H__
