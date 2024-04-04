#include <gtest/gtest.h>
#include <array_based_circular_buffer.hpp>


TEST(simple_test, delete_tail_size2)
{
	Circular_buffer<int,4> queue;
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);
	queue.enqueue(4);
	EXPECT_EQ(queue.enqueue(5),false);

	queue.dequeue();
	queue.dequeue();
	queue.dequeue();
	queue.enqueue(5);
	queue.enqueue(6);
	queue.enqueue(7);


	queue.print();
	queue.print_array();
}

int main(int nArgs, char** vArgs) {
    ::testing::InitGoogleTest(&nArgs, vArgs);
    return RUN_ALL_TESTS();
}
