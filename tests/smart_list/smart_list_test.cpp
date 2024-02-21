#pragma once

#include <smart_list.hpp>
#include <gtest/gtest.h>
#include <array>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <list>

enum class Llist_insrt_type { head, tail};
enum class Llist_insrt_mode { reverse, forward};


auto g_data_array = std::array<int,4>{1,2,3,4};

using array_t = std::remove_pointer<decltype(g_data_array.data())>::type;

//Definition of the array fundamental type
typedef typename std::remove_pointer<decltype(g_data_array.data())>::type array_t;

//Definition of the array size
static constexpr std::size_t array_s = std::size(g_data_array);

//array iterators
auto cbegin = g_data_array.cbegin();
auto cend = g_data_array.cend();

//reverse iterators for the array
auto rev_cbegin = std::make_reverse_iterator(cend);
auto rev_cend = std::make_reverse_iterator(cbegin);


template <typename T, std::size_t S>
void llist_init(std::array<T,S> &ref_array,
                        Smart_linked_list<T> &list,
                        Llist_insrt_type insrt_type,
                        Llist_insrt_mode mode)
{
    auto cbegin_itr = ref_array.cbegin();
    auto cend_itr = ref_array.cend();

    auto insert_lambda = [&](auto element)
    {
        if(insrt_type == Llist_insrt_type::head)
        {
            list.add_head(element);
        }
        else
        {
           list.add_tail(element); 
        }
    };

    if(mode == Llist_insrt_mode::reverse)
    {
        auto rev_cbegin_itr = std::make_reverse_iterator(cend_itr);
        auto rev_cend_itr = std::make_reverse_iterator(cbegin_itr);
        std::for_each(rev_cbegin_itr,rev_cend_itr,insert_lambda);
    }
    else
    {
        std::for_each(cbegin_itr,cend_itr,insert_lambda);
    }

}


template <typename T, std::size_t S>
void comp_and_del_llist_vs_array(   std::array<T,S> &ref_array,
                                    Smart_linked_list<T> &list,
                                    Llist_insrt_type insrt_type,
                                    Llist_insrt_mode mode)
{
    //array iterators
    auto cbegin_itr = ref_array.cbegin();
    auto cend_itr = ref_array.cend();


    auto compare_lambda = [&] (auto element)
    {
        std::optional<T> val;
        if(insrt_type == Llist_insrt_type::head)
        {
            val = list.delete_head();
        }
        else
        {
           val = list.delete_tail();
        }
        EXPECT_EQ(val.value(),element);
    };

    if(mode == Llist_insrt_mode::reverse)
    {
        auto rev_cbegin_itr = std::make_reverse_iterator(cbegin_itr);
        auto rev_cend_itr = std::make_reverse_iterator(cend_itr);
        std::for_each(rev_cbegin_itr,rev_cend_itr,compare_lambda);
    }
    else
    {
        std::for_each(cbegin_itr,cend_itr,compare_lambda);
    }

}

template <typename T>
void comp_std_list_vs_llist(std::list<T> &std_list,Smart_linked_list<T> &list)
{
    std::for_each(  std_list.begin(),
                    std_list.end(),
                    [&](auto element)
                    {
                        auto list_element = list.delete_head();
                        EXPECT_EQ(element,list_element.value());
                    }
                );
}

void find_remove_test(size_t remove_postition)
{
    //Linked list used for testing
    Smart_linked_list<array_t> l_list {};
    //an std list for testing
    std::list<array_t> t_list (g_data_array.cbegin(),g_data_array.cend());
    //add elements to the tail
    llist_init<array_t,array_s>(    g_data_array,
                                    l_list,
                                    Llist_insrt_type::tail,
                                    Llist_insrt_mode::forward );
    //Look for the value
    EXPECT_EQ(l_list.is_in_list(g_data_array.at(remove_postition)),true);
    //Try to delete from the tail
    EXPECT_EQ(l_list.delete_node(g_data_array.at(remove_postition)),true);
    //Delete from the std list
    t_list.remove(g_data_array.at(remove_postition));
    //Look for value it should not be there
    EXPECT_EQ(l_list.is_in_list(g_data_array.at(remove_postition)),false);
    //check the std list is not in the std list
    auto test = std::find(  t_list.cbegin(),
                            t_list.cend(),
                            g_data_array.at(remove_postition));
    //Check the that the element is not there
    EXPECT_EQ(test,t_list.cend());
    if(l_list.size() == 1)
    {
        //Make sure the head and tail point to the same
        EXPECT_EQ(l_list.get_head_node(),l_list.get_tail_node());
    }
}


TEST(Smart_linked_list, element_and_empty)
{
    auto data = "hola";
    auto single_list  = Smart_linked_list<decltype(data)> {data};
    EXPECT_EQ(single_list.size(), 1);
    auto empty_list  = Smart_linked_list<decltype(data)> {};
    EXPECT_EQ(empty_list.size(), 0);
}


TEST(Smart_linked_list, addition_head_tail_checks)
{

    //Linked list used for testing
    Smart_linked_list<array_t> l_list {};

    //We need to check that an empty list returns an empty optional
    EXPECT_EQ(bool{l_list.get_head()},false);
    EXPECT_EQ(bool{l_list.get_tail()},false);

    //add elements to the tail
    llist_init<array_t,array_s>(    g_data_array,
                                    l_list,
                                    Llist_insrt_type::tail,
                                    Llist_insrt_mode::forward );

    //Check the same amount of data was added
    EXPECT_EQ(l_list.size(),g_data_array.size());


    //check that the head has the right value
    EXPECT_EQ(l_list.get_head().value(),g_data_array.at(0));

    //check that the tail have the right value
    EXPECT_EQ(l_list.get_tail().value(),g_data_array.at(array_s-1));

    //check the list is not empty
    EXPECT_EQ(l_list.empty(),false);

    //Remove all elements form the head and compare against the array
    comp_and_del_llist_vs_array<array_t,array_s>(   g_data_array,
                                                    l_list,
                                                    Llist_insrt_type::head,
                                                    Llist_insrt_mode::forward );

    //Make sure the size list is 0 and Empty
    EXPECT_EQ(l_list.size(),0);
    EXPECT_EQ(l_list.empty(),true);

    //Inser form head in reverse mode
    llist_init<array_t,array_s>(    g_data_array,
                                    l_list,
                                    Llist_insrt_type::head,
                                    Llist_insrt_mode::reverse );

    //Make sure the reversed insert head matches the array
    comp_and_del_llist_vs_array<array_t,array_s>(   g_data_array,
                                                    l_list,
                                                    Llist_insrt_type::head,
                                                    Llist_insrt_mode::forward );

    //Insert from head for testing the tail remove
    llist_init<array_t,array_s>(    g_data_array,
                                    l_list,
                                    Llist_insrt_type::head,
                                    Llist_insrt_mode::forward );

    //Make sure the insert head matches the array
    comp_and_del_llist_vs_array<array_t,array_s>(   g_data_array,
                                                    l_list,
                                                    Llist_insrt_type::tail,
                                                    Llist_insrt_mode::forward );
}

TEST(Smart_linked_list, copy_constructor_copy_assigment_test)
{
    //Linked list used for testing
    Smart_linked_list<array_t> l_list {};

    //add elements to the tail
    llist_init<array_t,array_s>(    g_data_array,
                                    l_list,
                                    Llist_insrt_type::tail,
                                    Llist_insrt_mode::forward );


    //Copy construct to elements
    Smart_linked_list<array_t> l_list_copy{l_list};
    Smart_linked_list<array_t> l_list_copy_assigned = l_list;

    //Remove all items form the first list after the copy construction
    comp_and_del_llist_vs_array<array_t,array_s>(   g_data_array,
                                                    l_list,
                                                    Llist_insrt_type::head,
                                                    Llist_insrt_mode::forward );

    //Make sure the copy constructed Items have the array size
    EXPECT_EQ(l_list_copy.size(),array_s);
    EXPECT_EQ(l_list_copy_assigned.size(),array_s);

    //Create a new array of one item bigger than the global size
    std::array<array_t,array_s+1> array_test {};
    std::copy(g_data_array.cbegin(),g_data_array.cend(),array_test.begin());
    //Populate the extra element added
    array_test[array_s]=array_s;

    //Create a new list with default constructor
    Smart_linked_list<array_t> secod_array_test {};

    //Populate the list based on the new array
    llist_init<array_t,array_s+1>(    array_test,
                                    secod_array_test,
                                    Llist_insrt_type::tail,
                                    Llist_insrt_mode::forward );

    //Make sure the linked list has the proper size
    EXPECT_EQ(secod_array_test.size(),array_s+1);

    //Copy assign the new list to one of the copy constructed list
    secod_array_test = l_list_copy_assigned;

    EXPECT_EQ(secod_array_test.size(),array_s);

    //Make sure the secod_array_test matches the data after the copy assignment
    comp_and_del_llist_vs_array<array_t,array_s>(   g_data_array,
                                                    secod_array_test,
                                                    Llist_insrt_type::head,
                                                    Llist_insrt_mode::forward );
    //Check new sizes
    EXPECT_EQ(secod_array_test.size(),0);
    EXPECT_EQ(l_list_copy_assigned.size(),array_s);

}

TEST(Smart_linked_list, find_delete_head_mid_tail)
{
    //Remove form head
    find_remove_test(0);
    //Remove form middle
    find_remove_test(array_s/2);
    //Remove form tail
    find_remove_test(array_s-1);
}

TEST(Smart_linked_list, find_delete_1_element)
{
    //Linked list used for testing
    array_t element = g_data_array.at(0);
    Smart_linked_list<array_t> l_list {element};
    //Look for head
    EXPECT_EQ(l_list.is_in_list(element),true);
    //Try to delete form an empty list
    EXPECT_EQ(l_list.delete_node(element),true);
    //Check tail and head are nullptr
    EXPECT_EQ(l_list.get_head_node(),nullptr);
    EXPECT_EQ(l_list.get_tail_node(),nullptr);
}


TEST(Smart_linked_list, delete_tail_size2)
{
    //Linked list used for testing
    array_t element = g_data_array.at(0);
    array_t element_2 =  element+1;
    Smart_linked_list<array_t> l_list {element};
    l_list.add_tail(element_2);
    EXPECT_EQ(l_list.delete_node(element_2),true);
    EXPECT_EQ(l_list.get_head_node(),l_list.get_tail_node());
}


int main(int nArgs, char** vArgs) {
    ::testing::InitGoogleTest(&nArgs, vArgs);
    return RUN_ALL_TESTS();
}

