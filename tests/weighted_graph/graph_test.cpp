#pragma once

#include <weighted_graph.hpp>
#include <gtest/gtest.h>
#include <iostream>

TEST(Graph, graph_test)
{

    Graph test_graph {};

    test_graph.insert_edge(8,1);
    test_graph.insert_edge(1,7);
    test_graph.insert_edge(1,2);
    test_graph.insert_edge(7,2);
    test_graph.insert_edge(2,3);
    test_graph.insert_edge(2,5);
    test_graph.insert_edge(3,5);
    test_graph.insert_edge(5,4);
    test_graph.insert_edge(3,4);
    test_graph.insert_edge(5,6);

    test_graph.print();

    test_graph.breadth_first_serach(6);
    test_graph.find_path(6,4);

    std::cout << "DFS:" << std::endl;
    test_graph.depth_first_serach(1);
    test_graph.print_time();
    test_graph.print_parent();



    EXPECT_EQ(true,true); 

}




int main(int nArgs, char** vArgs) {
    ::testing::InitGoogleTest(&nArgs, vArgs);
    return RUN_ALL_TESTS();
}

