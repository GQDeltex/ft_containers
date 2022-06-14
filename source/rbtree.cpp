#include "../include/ft/rbtree.hpp"
#include "Test.hpp"
#include <cstddef>

typedef ft::RBTree<std::string>::Node Node;

void TestRBTree() {
	{
		Test test("Create Node");
		ft::RBTree<std::string> rbtree;
		Node* x = rbtree.create_node("x");
		test.equal(x->color, 'r');
		test.equal(x->data, std::string("x"));
		test.equal(x->left_child, (Node*)NULL);
		test.equal(x->right_child, (Node*)NULL);
		test.equal(x->parent, (Node*)NULL);
		delete x;
	}
	{
		Test test("Create node and child");
		ft::RBTree<std::string> rbtree;
		Node* x = rbtree.create_node("x");
		Node* z = rbtree.create_node("z", x);

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
		delete x;
		delete z;
	}
	{
		Test test("Left rotate");
		ft::RBTree<std::string> rbtree;
		Node* x = rbtree.create_node("x");
		Node* y = rbtree.create_node("y", x);
		x->left_child = NULL;
		x->right_child = y;
		rbtree.root = x;

		//rbtree.print_node(rbtree.root, true);
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
		//rbtree.print_node(rbtree.root, true);
		delete x;
		delete y;
	}
	{
		Test test("Right rotate");
		ft::RBTree<std::string> rbtree;
		Node* y = rbtree.create_node("y");
		Node* x = rbtree.create_node("x", y);
		rbtree.root = y;

		//rbtree.print_node(rbtree.root, true);
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
		//rbtree.print_node(rbtree.root, true);
		delete x;
		delete y;
	}
	{
		Test test("Left-Right Rotate");
		ft::RBTree<std::string> rbtree;
		Node* z = rbtree.create_node("z");
		Node* x = rbtree.create_node("x", z);
		Node* y = rbtree.create_node("y", x);
		x->left_child = NULL;
		x->right_child = y;
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

		delete y;
		delete x;
		delete z;
	}
	{
		Test test("Right-Left Rotate");
		ft::RBTree<std::string> rbtree;
		Node* z = rbtree.create_node("z");
		Node* x = rbtree.create_node("x", z);
		z->left_child = NULL;
		z->right_child = x;
		Node* y = rbtree.create_node("y", x);
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

		delete y;
		delete x;
		delete z;
	}
}
