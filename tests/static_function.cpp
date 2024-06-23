#include <functional/static_function.hpp>
#include <gtest/gtest.h>

TEST(StaticFunctionTest, SimpleFunctionCall) {
  ct_functional::static_function<int()> func([]() { return 42; });
  EXPECT_EQ(func(), 42);
}

TEST(StaticFunctionTest, FunctionWithParameters) {
  ct_functional::static_function<int(int, int)> add(
      [](int a, int b) { return a + b; });
  EXPECT_EQ(add(5, 7), 12);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
