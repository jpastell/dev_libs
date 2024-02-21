#pragma once

#include <smart_list.hpp>
#include <gtest/gtest.h>
#include <array>
#include <iterator>
#include <algorithm>
#include <iostream>

enum class Llist_insrt_type { head, tail};
enum class Llist_insrt_mode { reverse, forward};


auto g_data_array = std::array<int,4>{1,2,3,4};

using array_t = std::remove_pointer<decltype(g_data_array.data())>::type;

// static constexpr std::size_t array_s = std::size(g_data_array);

TEST(Linked_list, element_and_empty)
{
    Smart_linked_list<int> s_ll_empty {};
    Smart_linked_list<int> s_ll {1};

    EXPECT_EQ(s_ll_empty.is_empty(),true);
    EXPECT_EQ(s_ll.is_empty(),false);
}

TEST(Smart_linked_list,insertion)
{
    std::cout << "---- Test start ----" << std::endl;
    Smart_linked_list<array_t> s_ll {};

    std::for_each(g_data_array.cbegin(),
                    g_data_array.cend(),
                    [&](auto element)
                    {
                        s_ll.add_tail(element);
                    });

    s_ll.print();

    s_ll.delete_node(2);


    std::cout <<"Head: "<<(s_ll.get_head()).value() << std::endl;
    std::cout <<"Tail: "<<(s_ll.get_tail()).value() << std::endl;

    s_ll.print();




    std::cout << "---- Test ends ----" << std::endl;
}



int main(int nArgs, char** vArgs) {
    ::testing::InitGoogleTest(&nArgs, vArgs);
    return RUN_ALL_TESTS();
}

