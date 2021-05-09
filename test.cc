/*
 * Copyright (C) 2021 takeoverjp@gmail.com
 * All rights reserved.
 */

#include <set>
#include <vector>
#include <unordered_set>

#include "lassert.h"

static void TestInt() {
  int exp, act;

  exp = 1;
  act = 1;
  ASSERT_EQ(exp, act);

  exp = 1;
  act = 2;
  ASSERT_EQ(exp, act);

  exp = 2;
  act = 1;
  ASSERT_EQ(exp, ++act);

  exp = 0;
  act = 0;
  ASSERT_EQ(exp, ++act);
}

static void TestScopedEnum() {
  enum class TestEnum { Val0, Val1, Val2 };

  TestEnum exp, act;

  exp = TestEnum::Val1;
  act = TestEnum::Val1;
  ASSERT_EQ(exp, act);

  exp = TestEnum::Val1;
  act = TestEnum::Val2;
  ASSERT_EQ(exp, act);
}

static void TestBool() {
  bool exp, act;

  exp = true;
  act = true;
  ASSERT_EQ(exp, act);

  exp = true;
  act = false;
  ASSERT_EQ(exp, act);
}

static void TestString() {
  std::string exp, act;

  exp = "expected string";
  act = "expected string";
  ASSERT_EQ(exp, act);

  exp = "expected string";
  act = "actual string";
  ASSERT_EQ(exp, act);
}

template<class IntContainerType>
static void TestIntContainer() {
  IntContainerType exp, act;

  exp = {1, 2, 3};
  act = {1, 2, 3};
  ASSERT_EQ(exp, act);

  exp = {1, 2, 3};
  act = {1, 2, 4};
  ASSERT_EQ(exp, act);
}

template<class StringContainerType>
static void TestStringContainer() {
  StringContainerType exp, act;

  exp = {"1", "2", "3"};
  act = {"1", "2", "3"};
  ASSERT_EQ(exp, act);

  exp = {"1", "2", "3"};
  act = {"1", "2", "4"};
  ASSERT_EQ(exp, act);
}

static void TestSet() {
  std::set<int> exp, act;

  exp = {1, 2, 3};
  act = {1, 3, 2};
  ASSERT_EQ(exp, act);

  exp = {1, 2, 3};
  act = {1, 2, 4};
  ASSERT_EQ(exp, act);
}

int main(void) {
  TestInt();
  TestScopedEnum();
  TestBool();
  TestString();
  TestIntContainer<std::set<int>>();
  TestIntContainer<std::unordered_set<int>>();
  TestIntContainer<std::vector<int>>();
  TestStringContainer<std::set<std::string>>();
  TestStringContainer<std::unordered_set<std::string>>();
  TestStringContainer<std::vector<std::string>>();
  TestSet();

  return 0;
}
