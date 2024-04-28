#include <gtest/gtest.h>
#include <bin_tree.hpp>


TEST(simple_test, delete_tail_size2)
{
	Bin_tree<int> tree{};
	tree.insert(20);
	tree.insert(10);
	tree.insert(30);
	tree.insert(6);
	tree.insert(15);
	tree.insert(25);
	tree.insert(40);
	tree.insert(50);
	tree.insert(8);
	// 
	// tree.insert(2);
	// tree.insert(1);
	// tree.insert(7);
	// tree.insert(4);
	// tree.insert(8);
	// tree.insert(3);
	// tree.insert(6);
	// tree.insert(5);
	std::cout << "Breadth" << std::endl;
	tree.breadth_traversal();
	std::cout << "Pre-order" << std::endl;
	tree.preorder_traversal();
	std::cout << "Post-order" << std::endl;
	tree.postorder_traversal();
	std::cout << "In-order" << std::endl;
	tree.inorder_traversal();

	//Practice
	std::cout << "Breadth test" << std::endl;
	tree.test_breadth_traversal();
	std::cout << "Pree test" << std::endl;
	tree.practice_preorder();
	std::cout << "Pree in" << std::endl;
	tree.practice_inorder();
	std::cout << "post testin" << std::endl;
	tree.practice_postorder();


}

int main(int nArgs, char** vArgs) {
    ::testing::InitGoogleTest(&nArgs, vArgs);
    return RUN_ALL_TESTS();
}
