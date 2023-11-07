#pragma once
#include <iostream>

/*
* ********************************************
*       Hayden Zeller        				 *
*	    BinaryTree.hpp (v1.5) 				 *
*		2023-11-07							 *
* ********************************************
*											 *
* This file contains the paint function,	 *
* which is used to color text in the console *
* using ANSII escape codes.					 *
*											 *
* ********************************************
*/
/* source: https://github.com/haydenzeller/HaydensHeaders */


/*
* class BinaryTree
* @brief: A binary tree data structure
* @param T: The type of data to store in the tree
*/
template <typename T>
class BinaryTree
{
	/*
	* struct Node
	* @brief: A node in the binary tree
	* @param left_child: The left child of the node
	* @param right_child: The right child of the node
	* @param data: The data stored in the node
	*/
	struct Node
	{
		Node* left_child;
		Node* right_child;
		T* data;

		Node(const T& value) :left_child(nullptr), right_child(nullptr)
		{
			this->data = new T(value);
		}
		~Node()
		{
			delete data;
		}
	};
	// The root node of the tree
	Node* root_node_;
	/*
	* find_parent_node
	* @brief: Finds the parent node of a given value
	* @param starting_node: The node to start the search from
	* @param value: The value to find the parent of
	* @return: The parent node of the value
	*/
	Node* find_parent_node(Node* starting_node, const T& value)
	{
		Node* result = starting_node;
		if (value < *starting_node->data)
		{
			if (starting_node->left_child)
			{
				return find_parent_node(starting_node->left_child, value);
			}
		}
		else if (starting_node->right_child)
		{
			return find_parent_node(starting_node->right_child, value);
		}
		return result;
	}

	/*
	* free_node
	* @brief: Frees the memory of a node and all of its children
	* @param node: The node to free
	* @return: void
	* @note: This function is recursive
	*/
	void free_node(Node* node)
	{
		if (!node) return;
		free_node(node->left_child);
		free_node(node->right_child);
		delete node;
	}

	/*
	* count_nodes_children
	* @brief: Counts the number of nodes in the tree
	* @param node: The node to start counting from
	* @return: The number of nodes in the tree
	* @note: This function is recursive
	*/
	size_t count_nodes_children(const Node* const node) const
	{
		if (!node) return 0;
		return 1 + count_nodes_children(node->left_child) + 
			count_nodes_children(node->right_child);
	}

	/*
	* height
	* @brief: Finds the height of a node
	* @param node: The node to find the height of
	* @return: The height of the node
	* @note: This function is recursive
	*/
	int height(Node* node)
	{
		if (!node) return 0;
		const int l_height = height(node->left_child);
		const int r_height = height(node->right_child);

		if (l_height > r_height)
		{
			return l_height + 1;
		}
		else
		{
			return r_height + 1;
		}
	}

	/*
	* store_values_arr
	* @brief: Stores the values of the tree in an array
	* @param node: The node to start storing from
	* @param arr: The array to store the values in
	* @param index_ptr: A pointer to the index of the array to store the next value in
	* @return: void
	* @note: This function is recursive
	*/
	void store_values_arr(Node* node, T* arr, int* index_ptr)
	{
		if (!node) return;

		store_values_arr(node->left_child, arr, index_ptr);
		arr[(*index_ptr)++] = *node->data;
		store_values_arr(node->right_child, arr, index_ptr);

	}
	/*
	* reconstruct
	* @brief: Reconstructs the tree from an array of values
	* @param arr: The array to reconstruct the tree from
	* @param low: The lowest index of the array to reconstruct from
	* @param high: The highest index of the array to reconstruct from
	* @return: The root node of the reconstructed tree
	* @note: This function is recursive
	*/
	Node* reconstruct(const T* arr, const int low, const int high)
	{
		if (low > high)
		{
			return nullptr;
		}
		const int mid = low + (high - low) / 2;

		Node* node = new Node(arr[mid]);

		node->left_child = reconstruct(arr, low, mid - 1);
		node->right_child = reconstruct(arr, mid + 1, high);

		return node;
	}

public:
	/*
	* BinaryTree
	* @brief: Default constructor
	* @return: void
	* @note: Initializes the root node to nullptr
	*/
	BinaryTree():root_node_(nullptr){}
	/*
	* ~BinaryTree
	* @brief: Destructor
	* @return: void
	* @note: Calls free_node to free the memory of the tree
	*/
	~BinaryTree()
	{
		free_node(root_node_);
	}
	/*
	* get_root
	* @brief: Gets the root node of the tree
	* @return: The root node of the tree
	* @note: This function is const
	*/
	Node* get_root()const { return root_node_; }

	/*
	* insert
	* @brief: Inserts a value into the tree
	* @param value: The value to insert into the tree
	* @return: void
	*/
	void insert(const T& value)
	{
		Node* newNode = new Node(value);
		if (root_node_ == nullptr)
		{
			root_node_ = newNode;
			return;
		}

		//walk the tree to find the insertion point
		Node* current_node = root_node_;
		Node* parent_node = find_parent_node(root_node_, value);
		if (value < *parent_node->data)
		{
			parent_node->left_child = newNode;

		}
		else
			parent_node->right_child=newNode;
		if (!is_balance())
		{
			balance();
		}

	}
	/*
	* print_in_order_traversal
	* @brief: Prints the tree in order
	* @return: void
	*/
	void print_in_order_traversal(Node* current_node)
	{
		//if the node doesn't exist nothing to print
		if (current_node == nullptr)
		{
			return;
		}

		//print left node
		print_in_order_traversal(current_node->left_child);

		//print current node
		std::cout << *current_node->data << " , ";

		//print right node
		print_in_order_traversal(current_node->right_child);


	}
	/*
	* print_pre_order_traversal
	* @brief: Prints the tree in pre order
	* @return: void
	* @note: This function is recursive
	*/
	void print_pre_order_traversal(Node* current_node)
	{
		//if the node doesn't exist nothing to print
		if (current_node == nullptr)
		{
			return;
		}
		//print current node
		std::cout << *current_node->data << " , ";

		//print left nodes
		print_pre_order_traversal(current_node->left_child);

		//print right nodes
		print_pre_order_traversal(current_node->right_child);


	}
	/*
	* print_post_order_traversal
	* @brief: Prints the tree in post order
	* @return: void
	* @note: This function is recursive
	*/
	void print_post_order_traversal(Node* current_node)
	{
		//if the node doesn't exist nothing to print
		if (current_node == nullptr)
		{
			return;
		}
		

		//print left nodes
		print_post_order_traversal(current_node->left_child);

		//print right nodes
		print_post_order_traversal(current_node->right_child);

		//print current node
		std::cout << *current_node->data << " , ";

	}


	/*
	* size
	* @brief: Gets the number of nodes in the tree
	* @return: The number of nodes in the tree
	* @note: This function is const
	*/
	size_t size()const
	{
		return count_nodes_children(root_node_);
	}
	/*
	* is_balance
	* @brief: Checks if the tree is balanced
	* @return: True if the tree is balanced, false otherwise
	* @note: This function is const
	* @note: A tree is balanced if the height of the left and right subtrees differ by at most 1
	*/
	bool is_balance()
	{
		if (!root_node_) return true;

		const int left_subtree_height = height(root_node_->left_child);
		const int right_subtree_height = height(root_node_->right_child);

		return abs(left_subtree_height - right_subtree_height) <= 1;

	}
	/*
	* balance
	* @brief: Balances the tree
	* @return: void
	* @note: This function is const
	*/
	void balance() 
	{
		auto* arr = new T[size()];
		int i = 0;
		
		store_values_arr(root_node_, arr, &i);

		const size_t current_size = size();
		free_node(root_node_);

		root_node_ = reconstruct(arr, 0, current_size-1);

		delete[] arr;
	}

};
