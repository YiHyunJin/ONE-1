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

#ifndef __TEST_HELPER_H__
#define __TEST_HELPER_H__

#include <loco.h>

#include <moco/Support/NodeAs.h>

namespace moco
{
namespace test
{

template <typename T> T *find_first_node_bytype(loco::Graph *g)
{
  for (auto node : loco::active_nodes(loco::output_nodes(g)))
  {
    if (auto T_node = as<T>(node))
    {
      return T_node;
    }
  }

  return nullptr;
}

template <typename T> std::vector<T *> find_nodes_bytype(loco::Graph *g)
{
  std::vector<T *> find_nodes;

  for (auto node : loco::active_nodes(loco::output_nodes(g)))
  {
    if (auto T_node = as<T>(node))
    {
      find_nodes.push_back(T_node);
    }
  }

  return find_nodes;
}

/**
 * @brief Append setup output of graph by adding loco::Push node
 *
 * @note  This is subject to change when loco changes I/O treatment
 */
void setup_output_node(loco::Graph *graph, loco::Node *last_node);

} // namespace test
} // namespace moco

#endif // __TEST_HELPER_H__
