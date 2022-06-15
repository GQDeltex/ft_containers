#include "../include/ft/rbtree.hpp"
#include "Test.hpp"
#include <cstddef>

typedef ft::RBTree<std::string>::Node Node;

void TestRBTree() {
	{
		Test test("Create Node");
		ft::RBTree<std::string> rbtree;
		Node* x = rbtree.create_node("x");
		rbtree.root = x;
		test.equal(x->color, 'r');
		test.equal(x->data, std::string("x"));
		test.equal(x->left_child, (Node*)NULL);
		test.equal(x->right_child, (Node*)NULL);
		test.equal(x->parent, (Node*)NULL);
	}
	{
		Test test("Create node and child");
		ft::RBTree<std::string> rbtree;
		Node* x = rbtree.create_node("x");
		Node* z = rbtree.create_node("z");
		x->left_child = z;
		z->parent = x;
		rbtree.root = x;

		test.equal(x->color, 'r');
		test.equal(x->data, std::string("x"));
		test.equal(x->left_child, z);
		test.equal(x->right_child, (Node*)NULL);
		test.equal(x->parent, (Node*)NULL);

		test.equal(z->color, 'r');
		test.equal(z->data, std::string("z"));
		test.equal(z->left_child, (Node*)NULL);
		test.equal(z->right_child, (Node*)NULL);
		test.equal(z->parent, x);
	}
	{
		Test test("Left rotate");
		ft::RBTree<std::string> rbtree;
		Node* x = rbtree.create_node("x");
		Node* y = rbtree.create_node("y");
		x->right_child = y;
		y->parent = x;
		rbtree.root = x;

		test.equal(x->data, std::string("x"));
		test.equal(x->parent, (Node*)NULL);
		test.equal(x->left_child, (Node*)NULL);
		test.equal(x->right_child, y);
		test.equal(y->data, std::string("y"));
		test.equal(y->parent, x);
		test.equal(y->left_child, (Node*)NULL);
		test.equal(y->right_child, (Node*)NULL);
		rbtree.rotate_left(rbtree.root);
		test.equal(x->data, std::string("x"));
		test.equal(x->parent, y);
		test.equal(x->left_child, (Node*)NULL);
		test.equal(x->right_child, (Node*)NULL);
		test.equal(y->data, std::string("y"));
		test.equal(y->parent, (Node*)NULL);
		test.equal(y->left_child, x);
		test.equal(y->right_child, (Node*)NULL);
	}
	{
		Test test("Right rotate");
		ft::RBTree<std::string> rbtree;
		Node* y = rbtree.create_node("y");
		Node* x = rbtree.create_node("x");
		y->left_child = x;
		x->parent = y;
		rbtree.root = y;

		test.equal(x->data, std::string("x"), "x is x");
		test.equal(x->parent, y, "x has parent y");
		test.equal(x->left_child, (Node*)NULL, "x has no left child");
		test.equal(x->right_child, (Node*)NULL, "x has no right child");
		test.equal(y->data, std::string("y"), "y is y");
		test.equal(y->parent, (Node*)NULL, "y is root");
		test.equal(y->left_child, x, "y has x as left child");
		test.equal(y->right_child, (Node*)NULL, "y has no right child");
		rbtree.rotate_right(rbtree.root);
		test.equal(x->data, std::string("x"), "x is x");
		test.equal(x->parent, (Node*)NULL, "x is root");
		test.equal(x->left_child, (Node*)NULL, "x has not left child");
		test.equal(x->right_child, y, "x right child is y");
		test.equal(y->data, std::string("y"), "y is y");
		test.equal(y->parent, x, "y's parent is x");
		test.equal(y->left_child, (Node*)NULL, "y has no left child");
		test.equal(y->right_child, (Node*)NULL, "y has no right child");
	}
	{
		Test test("Left-Right Rotate");
		ft::RBTree<std::string> rbtree;
		Node* z = rbtree.create_node("z");
		Node* x = rbtree.create_node("x");
		z->left_child = x;
		x->parent = z;
		Node* y = rbtree.create_node("y");
		x->right_child = y;
		y->parent = x;
		rbtree.root = z;

		test.equal(z->data, std::string("z"), "z is z");
		test.equal(z->parent, (Node*)NULL, "z is root");
		test.equal(z->left_child, x, "z has left child x");
		test.equal(z->right_child, (Node*)NULL, "z has no right child");
		test.equal(x->data, std::string("x"), "x is x");
		test.equal(x->parent, z, "x has parent z");
		test.equal(x->left_child, (Node*)NULL, "x has no left child");
		test.equal(x->right_child, y, "x has right child y");
		test.equal(y->data, std::string("y"), "y is y");
		test.equal(y->parent, x, "y has parent x");
		test.equal(y->left_child, (Node*)NULL, "y has no left child");
		test.equal(y->right_child, (Node*)NULL, "y has no right child");
		rbtree.rotate_left_right(z);
		test.equal(y->data, std::string("y"), "y is y");
		test.equal(y->parent, (Node*)NULL, "y is root node");
		test.equal(y->left_child, x, "y has left child x");
		test.equal(y->right_child, z, "y has right child z");
		test.equal(x->data, std::string("x"), "x is x");
		test.equal(x->parent, y, "x has parent y");
		test.equal(x->left_child, (Node*)NULL, "x has no left child");
		test.equal(x->right_child, (Node*)NULL, "x has no right child");
		test.equal(z->data, std::string("z"), "z is z");
		test.equal(z->parent, y, "z has parent y");
		test.equal(z->left_child, (Node*)NULL, "z has no left child");
		test.equal(z->right_child, (Node*)NULL, "z has no right child");
	}
	{
		Test test("Right-Left Rotate");
		ft::RBTree<std::string> rbtree;
		Node* z = rbtree.create_node("z");
		Node* x = rbtree.create_node("x");
		z->right_child = x;
		x->parent = z;
		Node* y = rbtree.create_node("y");
		y->parent = x;
		x->left_child = y;
		rbtree.root = z;

		test.equal(z->data, std::string("z"), "z is z");
		test.equal(z->parent, (Node*)NULL, "z is root");
		test.equal(z->left_child, (Node*)NULL, "z has no left child");
		test.equal(z->right_child, x, "z has right child x");
		test.equal(x->data, std::string("x"), "x is x");
		test.equal(x->parent, z, "x has parent z");
		test.equal(x->left_child, y, "x has left child y");
		test.equal(x->right_child, (Node*)NULL, "x has no right child");
		test.equal(y->data, std::string("y"), "y is y");
		test.equal(y->parent, x, "y has parent x");
		test.equal(y->left_child, (Node*)NULL, "y has no left child");
		test.equal(y->right_child, (Node*)NULL, "y has no right child");
		rbtree.rotate_right_left(z);
		test.equal(y->data, std::string("y"), "y is y");
		test.equal(y->parent, (Node*)NULL, "y is root node");
		test.equal(y->left_child, z, "y has left child z");
		test.equal(y->right_child, x, "y has right child x");
		test.equal(x->data, std::string("x"), "x is x");
		test.equal(x->parent, y, "x has parent y");
		test.equal(x->left_child, (Node*)NULL, "x has no left child");
		test.equal(x->right_child, (Node*)NULL, "x has no right child");
		test.equal(z->data, std::string("z"), "z is z");
		test.equal(z->parent, y, "z has parent y");
		test.equal(z->left_child, (Node*)NULL, "z has no left child");
		test.equal(z->right_child, (Node*)NULL, "z has no right child");
	}
	{
		Test test("Insert on empty tree");
		ft::RBTree<std::string> rbtree;
		test.equal(rbtree.root, (Node*)NULL, "Tree is empty in the beginning");
		rbtree.insert(std::string("x"));
		test.unequal(rbtree.root, (Node*)NULL, "Tree is not empty anymore");
		test.equal(rbtree.root->color, 'b', "Node is black");
		test.equal(rbtree.root->data, std::string("x"), "Data is correct");
		test.equal(rbtree.root->left_child, (Node*)NULL, "No left child");
		test.equal(rbtree.root->right_child, (Node*)NULL, "No right child");
		test.equal(rbtree.root->parent, (Node*)NULL, "No parent");
	}
	{
		Test test("Insert with one item");
		ft::RBTree<std::string> rbtree;
		test.equal(rbtree.root, (Node*)NULL, "Tree is empty in the beginning");
		rbtree.insert(std::string("x"));
		test.unequal(rbtree.root, (Node*)NULL, "Tree is not empty anymore");
		test.equal(rbtree.root->color, 'b', "Node is black");
		test.equal(rbtree.root->data, std::string("x"), "Data is correct");
		test.equal(rbtree.root->left_child, (Node*)NULL, "No left child");
		test.equal(rbtree.root->right_child, (Node*)NULL, "No right child");
		test.equal(rbtree.root->parent, (Node*)NULL, "No parent");
		rbtree.insert(std::string("y"));
		test.unequal(rbtree.root->left_child, (Node*)NULL, "Left child is not empty");
		Node* y = rbtree.root->left_child;
		test.equal(y->color, 'r', "Color of new node is red");
		test.equal(y->data, std::string("y"), "Data is correct");
		test.equal(y->parent, rbtree.root, "Parent is root node");
		test.equal(y->left_child, (Node*)NULL, "No left child");
		test.equal(y->right_child, (Node*)NULL, "No right child");
	}
	{
		Test test("Insert with two item");
		ft::RBTree<std::string> rbtree;
		test.equal(rbtree.root, (Node*)NULL, "Tree is empty in the beginning");

		rbtree.insert(std::string("x"));
		test.unequal(rbtree.root, (Node*)NULL, "Tree is not empty anymore");
		test.equal(rbtree.root->color, 'b', "Node is black");
		test.equal(rbtree.root->data, std::string("x"), "Data is correct");
		test.equal(rbtree.root->left_child, (Node*)NULL, "No left child");
		test.equal(rbtree.root->right_child, (Node*)NULL, "No right child");
		test.equal(rbtree.root->parent, (Node*)NULL, "No parent");

		rbtree.insert(std::string("y"));
		test.unequal(rbtree.root->left_child, (Node*)NULL, "Left child is not empty");
		Node* y = rbtree.root->left_child;
		test.equal(y->color, 'r', "Color of new node is red");
		test.equal(y->data, std::string("y"), "Data is correct");
		test.equal(y->parent, rbtree.root, "Parent is root node");
		test.equal(y->left_child, (Node*)NULL, "No left child");
		test.equal(y->right_child, (Node*)NULL, "No right child");

		rbtree.insert(std::string("a"));
		Node* a = rbtree.root->right_child;
		test.equal(a->color, 'r', "Color of new node is red");
		test.equal(a->data, std::string("a"), "Data is correct");
		test.equal(a->parent, rbtree.root, "Parent is root node");
		test.equal(a->left_child, (Node*)NULL, "No left child");
		test.equal(a->right_child, (Node*)NULL, "No right child");

		rbtree.insert(std::string("z"));
		test.unequal(y->left_child, (Node*)NULL, "Left child is not empty");
		Node* z = y->left_child;
		test.equal(z->color, 'r', "Color of new node is red");
		test.equal(z->data, std::string("z"), "Data is correct");
		test.equal(z->parent, y, "Parent is y");
		test.equal(z->left_child, (Node*)NULL, "No left child");
		test.equal(z->right_child, (Node*)NULL, "No right child");
	}
}
