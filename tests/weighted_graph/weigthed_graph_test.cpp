#pragma once

#include <weighted_graph.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <functional>

TEST(Graph, graph_test)
{

    Graph test_graph {};

    test_graph.insert_edge(1,2,5);
    test_graph.insert_edge(2,3,7);
    test_graph.insert_edge(3,5,2);
    test_graph.insert_edge(5,6,7);
    test_graph.insert_edge(6,1,12);

    test_graph.insert_edge(1,7,7);
    test_graph.insert_edge(2,7,9);
    test_graph.insert_edge(3,7,4);
    test_graph.insert_edge(5,7,3);
    test_graph.insert_edge(6,7,4);

    test_graph.insert_edge(3,4,5);
    test_graph.insert_edge(5,4,2);

    test_graph.print();
    test_graph.print_number_vetices();
    std::cout << "Prim weight:" << std::endl;
    std::cout << test_graph.prim(1) << std::endl;

    test_graph.print_kruskal_edges();
    std::cout << "Krustal:" << std::endl;
    std::cout << test_graph.kruskal() << std::endl;







    EXPECT_EQ(true,true); 

}




int main(int nArgs, char** vArgs) {
    ::testing::InitGoogleTest(&nArgs, vArgs);
    return RUN_ALL_TESTS();
}

