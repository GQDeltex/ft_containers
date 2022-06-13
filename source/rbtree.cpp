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
		test.equal(x->left_child, (Node*)nullptr);
		test.equal(x->right_child, (Node*)nullptr);
		test.equal(x->parent, (Node*)nullptr);
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
		test.equal(x->right_child, (Node*)nullptr);
		test.equal(x->parent, (Node*)nullptr);

		test.equal(z->color, 'r');
		test.equal(z->data, std::string("z"));
		test.equal(z->left_child, (Node*)nullptr);
		test.equal(z->right_child, (Node*)nullptr);
		test.equal(z->parent, x);
		delete x;
		delete z;
	}
	{
		Test test("Left rotate");
		ft::RBTree<std::string> rbtree;
		Node* x = rbtree.create_node("x");
		Node* y = rbtree.create_node("y", x);
		x->left_child = nullptr;
		x->right_child = y;
		rbtree.root = x;

		//rbtree.print_node(rbtree.root, true);
		test.equal(x->data, std::string("x"));
		test.equal(x->parent, (Node*)nullptr);
		test.equal(x->left_child, (Node*)nullptr);
		test.equal(x->right_child, y);
		test.equal(y->data, std::string("y"));
		test.equal(y->parent, x);
		test.equal(y->left_child, (Node*)nullptr);
		test.equal(y->right_child, (Node*)nullptr);
		rbtree.rotate_left(rbtree.root);
		test.equal(x->data, std::string("x"));
		test.equal(x->parent, y);
		test.equal(x->left_child, (Node*)nullptr);
		test.equal(x->right_child, (Node*)nullptr);
		test.equal(y->data, std::string("y"));
		test.equal(y->parent, (Node*)nullptr);
		test.equal(y->left_child, x);
		test.equal(y->right_child, (Node*)nullptr);
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
		test.equal(x->left_child, (Node*)nullptr, "x has no left child");
		test.equal(x->right_child, (Node*)nullptr, "x has no right child");
		test.equal(y->data, std::string("y"), "y is y");
		test.equal(y->parent, (Node*)nullptr, "y is root");
		test.equal(y->left_child, x, "y has x as left child");
		test.equal(y->right_child, (Node*)nullptr, "y has no right child");
		rbtree.rotate_right(rbtree.root);
		test.equal(x->data, std::string("x"), "x is x");
		test.equal(x->parent, (Node*)nullptr, "x is root");
		test.equal(x->left_child, (Node*)nullptr, "x has not left child");
		test.equal(x->right_child, y, "x right child is y");
		test.equal(y->data, std::string("y"), "y is y");
		test.equal(y->parent, x, "y's parent is x");
		test.equal(y->left_child, (Node*)nullptr, "y has no left child");
		test.equal(y->right_child, (Node*)nullptr, "y has no right child");
		//rbtree.print_node(rbtree.root, true);
		delete x;
		delete y;
	}
}
