#pragma once

#include <list.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <array>
#include <type_traits>
#include <iterator>
#include <algorithm>


TEST(LList_construction, element_and_empty)
{
    auto data = "hola";
	auto single_list  = LList<decltype(data)> {data};
    EXPECT_EQ(single_list.size(), 1);
    auto empty_list  = LList<decltype(data)> {};
    EXPECT_EQ(empty_list.size(), 0);
}

TEST(LList_construction, addition_head_tail_checks)
{
    auto data_array = std::array<int,4>{1,2,3,4};
    auto l_list  = LList<std::remove_pointer<decltype(data_array.data())>::type> {};

    //array iterators
    auto cbegin = data_array.cbegin();
    auto cend = data_array.cend();

    //reverse iterators for the array
    auto rev_cbegin = std::make_reverse_iterator(cend);
    auto rev_cend = std::make_reverse_iterator(cbegin);

    //Lambda to add elements to the tail
    auto insert_tail = [&](auto element)
    {
        l_list.add_tail(element);
    };

    //Lambda to add elements to the head
    auto insert_head = [&](auto element)
    {
        l_list.add_head(element);
    };

    //We need to check that an empty list returns an empty optional
    EXPECT_EQ(bool{l_list.get_head()},false);
    EXPECT_EQ(bool{l_list.get_tail()},false);

    //add elements to the tail
    std::for_each(cbegin,cend,insert_tail);

    //Check the same amount of data was added
    EXPECT_EQ(l_list.size(),data_array.size());


    //check that the head has the right value
    EXPECT_EQ(l_list.get_head().value(),*(cbegin));

    //check that the tail have the right value
    EXPECT_EQ(l_list.get_tail().value(),*(rev_cbegin));

    //check the list is not empty
    EXPECT_EQ(l_list.empty(),false);

    auto check_head_remove = [&] (auto element) {
        auto val = l_list.delete_head();
        EXPECT_EQ(val.value(),element);
    };

    //Remove all elements form the head and make sure they match
    //the array
    std::for_each(cbegin,cend,check_head_remove);

    //Make sure the size list is 0 and Empty
    EXPECT_EQ(l_list.size(),0);
    EXPECT_EQ(l_list.empty(),true);

    //Insert head test
    std::for_each(rev_cbegin,rev_cend,insert_head);

    //Make sure the insert head matches the array
    std::for_each(cbegin,cend,check_head_remove);

    //Insert from head for testing the tail remove

    //Insert head test
    std::for_each(cbegin,cend,insert_head);

    //Make sure the insert head matches the array
    std::for_each(cbegin,cend,
        [&] (auto element)
        {
            auto val = l_list.delete_tail();
            EXPECT_EQ(val.value(),element);
        }
    );

}



int main(int nArgs, char** vArgs) {
    ::testing::InitGoogleTest(&nArgs, vArgs);
    return RUN_ALL_TESTS();
}

