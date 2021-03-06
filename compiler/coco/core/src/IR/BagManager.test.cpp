/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "coco/IR/BagManager.h"

#include <gtest/gtest.h>

TEST(IR_BAG_MANAGER, create)
{
  coco::BagManager mgr;

  auto bag = mgr.create(3);

  ASSERT_EQ(bag->size(), 3);
}

TEST(IR_BAG_MANAGER, destruct)
{
  coco::BagManager mgr;

  auto b = mgr.create(3);
  mgr.destroy(b);

  ASSERT_EQ(mgr.size(), 0);
}
