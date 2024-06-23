#include <container/static_set.hpp>
#include <gtest/gtest.h>

TEST(StaticSetTest, IsEmptyInitially) {
  using empty_set = ct_container::static_set<int>;
  ASSERT_FALSE(empty_set::contains<1>());
}

TEST(StaticSetTest, CanInsertElement) {
  using single_element_set = ct_container::static_set<int>::insert<10>;
  ASSERT_TRUE(single_element_set::contains<10>());
}

TEST(StaticSetTest, InsertsElementsInSortedOrder) {
  using test_set =
      ct_container::static_set<int>::insert<10>::insert<5>::insert<20>;
  ASSERT_TRUE(
      (std::is_same_v<test_set, ct_container::static_set<int, 5, 10, 20>>));
}

TEST(StaticSetTest, NoDuplicatesAllowed) {
  using duplicate_set = ct_container::static_set<int>::insert<10>::insert<10>;
  ASSERT_TRUE(
      (std::is_same_v<duplicate_set, ct_container::static_set<int, 10>>));
}

TEST(StaticSetTests, ContainsOrNotInsertedElements) {
  using set = ct_container::static_set<int>::insert<5>::insert<3>::insert<9>;
  EXPECT_TRUE(set::contains<3>());
  EXPECT_TRUE(set::contains<5>());
  EXPECT_FALSE(set::contains<1>());
  EXPECT_FALSE(set::contains<4>());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
