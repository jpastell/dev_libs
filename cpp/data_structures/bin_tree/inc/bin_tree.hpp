#pragma once
#include <memory>
#include <iostream>
#include <queue>
#include <stack>

template <typename T>
struct Tree_node
{
	Tree_node(const T &t, 
				std::shared_ptr<Tree_node<T>> left_ptr,
				std::shared_ptr<Tree_node<T>> rigth_ptr
			):
				value{t},
				left{left_ptr},
				right{rigth_ptr}
	{

	}
	T value;
	std::shared_ptr<Tree_node<T>> left;
	std::shared_ptr<Tree_node<T>> right;

};



template <typename T>
class Bin_tree
{
	std::shared_ptr<Tree_node<T>> root;
public:

	Bin_tree():root{}{}

	void insert(T data)
	{
		if(root == nullptr)
		{
			std::cout << "Adding to the root: " << data <<std::endl;
			root = std::shared_ptr<Tree_node<T>>{new Tree_node<T>(data, nullptr,nullptr)};
			std::cout << " Root : " << root;
			std::cout << std::endl;
		} else {
			std::cout << "Adding to the branches: " << data;
			//Traverse until you find
			std::shared_ptr<Tree_node<T>> temp = root;
			std::shared_ptr<Tree_node<T>> last = root;

			while(temp != nullptr)
			{
				last = temp;
				if(data < temp->value)
				{
					//Left
					temp=temp->left;
				}
				else if(data > temp->value)
				{
					// rigth
					temp=temp->right;
				} else {
					return;
				}
			}
			std::cout << " Parent : " << last->value <<std::endl;

			if(data < last->value)
			{
				//We found the rigth position
				last->left = std::shared_ptr<Tree_node<T>>{new Tree_node<T>(data, nullptr,nullptr)};
				std::cout << " to the left " << data <<std::endl;
			}
			else {
				std::cout << " to the right " << data <<std::endl;
				last->right = std::shared_ptr<Tree_node<T>>{new Tree_node<T>(data, nullptr,nullptr)};
			}
		}
	}

	void breadth_traversal()
	{
		std::queue<std::shared_ptr<Tree_node<T>>> levels;
		levels.push(root);
		while(!levels.empty())
		{
			std::shared_ptr<Tree_node<T>> temp = levels.front();
			std::cout << temp->value << ",";
			levels.pop();
			if(temp->left != nullptr)
			{
				levels.push(temp->left);
			}
			if(temp->right != nullptr)
			{
				levels.push(temp->right);
			}
		}
		std::cout << std::endl;
	}

	void preorder_traversal()
	{
		std::stack<std::shared_ptr<Tree_node<T>>> stack;
		bool right = false;
		stack.push(root);
		std::cout << root->value << ",";
		while(!stack.empty())
		{
			std::shared_ptr<Tree_node<T>> temp = stack.top();
			if(right)
			{
				stack.pop();
				if(temp->right != nullptr)
				{
					right = false;
					std::cout << temp->right->value << ",";
					stack.push(temp->right);
				}
			}
			else
			{
				if(temp->left != nullptr)
				{
					std::cout << temp->left->value << ",";
					stack.push(temp->left);
				} else {
					right = true;
				}
			}
		}
		std::cout << std::endl;
	}

	void inorder_traversal()
	{
		std::stack<std::shared_ptr<Tree_node<T>>> stack;
		bool right = false;
		stack.push(root);
		while(!stack.empty())
		{
			std::shared_ptr<Tree_node<T>> temp = stack.top();
			if(right)
			{
				std::cout << temp->value << ",";
				stack.pop();

				if(temp->right != nullptr)
				{
					right = false;
					stack.push(temp->right);
				}
			}
			else
			{
				if(temp->left != nullptr)
				{
					stack.push(temp->left);
				} else {
					right = true;
				}
			}
		}
		std::cout << std::endl;
	}

	void postorder_traversal()
	{
		std::stack<std::shared_ptr<Tree_node<T>>> po_stack;
		std::stack<std::shared_ptr<Tree_node<T>>> stack;
		stack.push(root);
		while(!stack.empty())
		{
			auto temp = stack.top();
			stack.pop();
			po_stack.push(temp);
			if(temp->left)
			{
				stack.push(temp->left);
			}
			if(temp->right)
			{
				stack.push(temp->right);
			}
		}

		while(!po_stack.empty())
		{
			auto temp = po_stack.top();
			po_stack.pop();
			std::cout << temp->value << "," ;
		}

		std::cout <<std::endl;

		
	}


};