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

#include "luci/IR/Nodes/CircleLocalResponseNormalization.h"

#include "luci/IR/CircleDialect.h"
#include "luci/IR/CircleNodeVisitor.h"

#include <gtest/gtest.h>

TEST(CircleLocalResponseNormalizationTest, constructor_P)
{
  luci::CircleLocalResponseNormalization local_response_normalization_node;

  ASSERT_EQ(luci::CircleDialect::get(), local_response_normalization_node.dialect());
  ASSERT_EQ(luci::CircleOpcode::LOCAL_RESPONSE_NORMALIZATION,
            local_response_normalization_node.opcode());

  ASSERT_EQ(nullptr, local_response_normalization_node.input());
  ASSERT_EQ(5, local_response_normalization_node.radius());
  ASSERT_EQ(1.0f, local_response_normalization_node.bias());
  ASSERT_EQ(1.0f, local_response_normalization_node.alpha());
  ASSERT_EQ(0.5f, local_response_normalization_node.beta());
}

TEST(CircleLocalResponseNormalizationTest, input_NEG)
{
  luci::CircleLocalResponseNormalization local_response_normalization_node;
  luci::CircleLocalResponseNormalization node;

  local_response_normalization_node.input(&node);
  ASSERT_NE(nullptr, local_response_normalization_node.input());

  local_response_normalization_node.input(nullptr);
  ASSERT_EQ(nullptr, local_response_normalization_node.input());

  local_response_normalization_node.radius(100);
  local_response_normalization_node.bias(100.0f);
  local_response_normalization_node.alpha(100.0f);
  local_response_normalization_node.beta(100.0f);
  ASSERT_NE(5, local_response_normalization_node.radius());
  ASSERT_NE(1.0f, local_response_normalization_node.bias());
  ASSERT_NE(1.0f, local_response_normalization_node.alpha());
  ASSERT_NE(0.5f, local_response_normalization_node.beta());
}

TEST(CircleLocalResponseNormalizationTest, arity_NEG)
{
  luci::CircleLocalResponseNormalization local_response_normalization_node;

  ASSERT_NO_THROW(local_response_normalization_node.arg(0));
  ASSERT_THROW(local_response_normalization_node.arg(1), std::out_of_range);
}

TEST(CircleLocalResponseNormalizationTest, visit_mutable_NEG)
{
  struct TestVisitor final : public luci::CircleNodeMutableVisitor<void>
  {
  };

  luci::CircleLocalResponseNormalization local_response_normalization_node;

  TestVisitor tv;
  ASSERT_THROW(local_response_normalization_node.accept(&tv), std::exception);
}

TEST(CircleLocalResponseNormalizationTest, visit_NEG)
{
  struct TestVisitor final : public luci::CircleNodeVisitor<void>
  {
  };

  luci::CircleLocalResponseNormalization local_response_normalization_node;

  TestVisitor tv;
  ASSERT_THROW(local_response_normalization_node.accept(&tv), std::exception);
}
