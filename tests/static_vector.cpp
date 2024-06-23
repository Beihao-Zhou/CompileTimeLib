#include <ct_lib/container/static_vector.hpp>
#include <gtest/gtest.h>
#include <iostream>

TEST(StaticVectorTest, SizeIsCorrect) {
  constexpr size_t size = ct_container::static_vector<int, 1, 2, 3>::size;
  EXPECT_EQ(3, size);
}

TEST(StaticVectorTest, GetElement) {
  constexpr int first = ct_container::static_vector<int, 10, 20, 30>::get<0>();
  constexpr int second = ct_container::static_vector<int, 10, 20, 30>::get<1>();
  constexpr int third = ct_container::static_vector<int, 10, 20, 30>::get<2>();

  EXPECT_EQ(10, first);
  EXPECT_EQ(20, second);
  EXPECT_EQ(30, third);
}

TEST(StaticVectorTest, PushBack) {
  using original = ct_container::static_vector<int, 1, 2, 3>;
  using new_vector1 = original::push_back<4>;
  using new_vector2 = original::emplace_back<4, 5>;

  static_assert(std::is_same_v<new_vector1,
                               ct_container::static_vector<int, 1, 2, 3, 4>>);
  static_assert(
      std::is_same_v<new_vector2,
                     ct_container::static_vector<int, 1, 2, 3, 4, 5>>);
}

TEST(StaticVectorTest, PrintElements) {
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  ct_container::static_vector<int, 1, 2, 3>::print();

  std::cout.rdbuf(old);

  std::string output = buffer.str();
  EXPECT_EQ("1 2 3 \n", output);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
