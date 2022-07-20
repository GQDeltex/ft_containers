#include "../include/ft/rbtree.hpp"
#include "Test.hpp"
#include <cstddef>

typedef ft::Node<std::string> Node;

bool testIsTreeValid(Node* target) {
	if (target->parent != NULL) {
		if (target->parent->color == 'r' && target->color == 'r') {
			std::cout << "Parent and Target are red (!RR)" << std::endl;
			return false;
		}
	}
	if (target->left_child != NULL) {
		if (testIsTreeValid(target->left_child) == false) {
			std::cout << "Left child is the culprit" << std::endl;
			return false;
		}
	}
	if (target->right_child != NULL) {
		if (testIsTreeValid(target->right_child) == false)
		{
			std::cout << "Right child is the culprit" << std::endl;
			return false;
		}
	}
	return true;
}

void TestRBTree() {
	{
		Test test("Create Node");
		ft::RBTree<std::string> rbtree;
		Node* x = rbtree.create_node("x");
		rbtree._root = x;
		test.equal(x->color, 'r');
		test.equal(*(x->data), std::string("x"));
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
		rbtree._root = x;

		test.equal(x->color, 'r');
		test.equal(*(x->data), std::string("x"));
		test.equal(x->left_child, z);
		test.equal(x->right_child, (Node*)NULL);
		test.equal(x->parent, (Node*)NULL);

		test.equal(z->color, 'r');
		test.equal(*(z->data), std::string("z"));
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
		rbtree._root = x;

		test.equal(*(x->data), std::string("x"));
		test.equal(x->parent, (Node*)NULL);
		test.equal(x->left_child, (Node*)NULL);
		test.equal(x->right_child, y);
		test.equal(*(y->data), std::string("y"));
		test.equal(y->parent, x);
		test.equal(y->left_child, (Node*)NULL);
		test.equal(y->right_child, (Node*)NULL);
		rbtree.rotate_left(rbtree._root);
		test.equal(*(x->data), std::string("x"));
		test.equal(x->parent, y);
		test.equal(x->left_child, (Node*)NULL);
		test.equal(x->right_child, (Node*)NULL);
		test.equal(*(y->data), std::string("y"));
		test.equal(y->parent, (Node*)NULL);
		test.equal(y->left_child, x);
	}
	{
		Test test("Right rotate");
		ft::RBTree<std::string> rbtree;
		Node* y = rbtree.create_node("y");
		Node* x = rbtree.create_node("x");
		y->left_child = x;
		x->parent = y;
		rbtree._root = y;

		test.equal(*(x->data), std::string("x"), "x is x");
		test.equal(x->parent, y, "x has parent y");
		test.equal(x->left_child, (Node*)NULL, "x has no left child");
		test.equal(x->right_child, (Node*)NULL, "x has no right child");
		test.equal(*(y->data), std::string("y"), "y is y");
		test.equal(y->parent, (Node*)NULL, "y is root");
		test.equal(y->left_child, x, "y has x as left child");
		test.equal(y->right_child, (Node*)NULL, "y has no right child");
		rbtree.rotate_right(rbtree._root);
		test.equal(*(x->data), std::string("x"), "x is x");
		test.equal(x->parent, (Node*)NULL, "x is root");
		test.equal(x->left_child, (Node*)NULL, "x has not left child");
		test.equal(x->right_child, y, "x right child is y");
		test.equal(*(y->data), std::string("y"), "y is y");
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
		rbtree._root = z;

		test.equal(*(z->data), std::string("z"), "z is z");
		test.equal(z->parent, (Node*)NULL, "z is root");
		test.equal(z->left_child, x, "z has left child x");
		test.equal(z->right_child, (Node*)NULL, "z has no right child");
		test.equal(*(x->data), std::string("x"), "x is x");
		test.equal(x->parent, z, "x has parent z");
		test.equal(x->left_child, (Node*)NULL, "x has no left child");
		test.equal(x->right_child, y, "x has right child y");
		test.equal(*(y->data), std::string("y"), "y is y");
		test.equal(y->parent, x, "y has parent x");
		test.equal(y->left_child, (Node*)NULL, "y has no left child");
		test.equal(y->right_child, (Node*)NULL, "y has no right child");
		rbtree.rotate_left_right(z);
		test.equal(*(y->data), std::string("y"), "y is y");
		test.equal(y->parent, (Node*)NULL, "y is root node");
		test.equal(y->left_child, x, "y has left child x");
		test.equal(y->right_child, z, "y has right child z");
		test.equal(*(x->data), std::string("x"), "x is x");
		test.equal(x->parent, y, "x has parent y");
		test.equal(x->left_child, (Node*)NULL, "x has no left child");
		test.equal(x->right_child, (Node*)NULL, "x has no right child");
		test.equal(*(z->data), std::string("z"), "z is z");
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
		rbtree._root = z;

		test.equal(*(z->data), std::string("z"), "z is z");
		test.equal(z->parent, (Node*)NULL, "z is root");
		test.equal(z->left_child, (Node*)NULL, "z has no left child");
		test.equal(z->right_child, x, "z has right child x");
		test.equal(*(x->data), std::string("x"), "x is x");
		test.equal(x->parent, z, "x has parent z");
		test.equal(x->left_child, y, "x has left child y");
		test.equal(x->right_child, (Node*)NULL, "x has no right child");
		test.equal(*(y->data), std::string("y"), "y is y");
		test.equal(y->parent, x, "y has parent x");
		test.equal(y->left_child, (Node*)NULL, "y has no left child");
		test.equal(y->right_child, (Node*)NULL, "y has no right child");
		rbtree.rotate_right_left(z);
		test.equal(*(y->data), std::string("y"), "y is y");
		test.equal(y->parent, (Node*)NULL, "y is root node");
		test.equal(y->left_child, z, "y has left child z");
		test.equal(y->right_child, x, "y has right child x");
		test.equal(*(x->data), std::string("x"), "x is x");
		test.equal(x->parent, y, "x has parent y");
		test.equal(x->left_child, (Node*)NULL, "x has no left child");
		test.equal(x->right_child, (Node*)NULL, "x has no right child");
		test.equal(*(z->data), std::string("z"), "z is z");
		test.equal(z->parent, y, "z has parent y");
		test.equal(z->left_child, (Node*)NULL, "z has no left child");
		test.equal(z->right_child, (Node*)NULL, "z has no right child");
	}
	{
		Test test("Insert with one item");
		ft::RBTree<std::string> rbtree;
		test.equal(rbtree._root, (Node*)NULL, "Tree is empty in the beginning");
		rbtree.insert(std::string("x"));
		test.unequal(rbtree._root, (Node*)NULL, "Tree is not empty anymore");
		test.equal(rbtree._root->color, 'b', "Node is black");
		test.equal(*(rbtree._root->data), std::string("x"), "Data is correct");
		test.equal(rbtree._root->left_child, (Node*)NULL, "No left child");
		test.equal(rbtree._root->right_child, (Node*)NULL, "No right child");
		test.equal(rbtree._root->parent, (Node*)NULL, "No parent");
		test.equal(testIsTreeValid(rbtree._root), true);
	}
	{
		Test test("Insert with two items");
		ft::RBTree<std::string> rbtree;
		test.equal(rbtree._root, (Node*)NULL, "Tree is empty in the beginning");
		rbtree.insert(std::string("x"));
		test.unequal(rbtree._root, (Node*)NULL, "Tree is not empty anymore");
		test.equal(rbtree._root->color, 'b', "Node is black");
		test.equal(*(rbtree._root->data), std::string("x"), "Data is correct");
		test.equal(rbtree._root->left_child, (Node*)NULL, "No left child");
		test.equal(rbtree._root->right_child, (Node*)NULL, "No right child");
		test.equal(rbtree._root->parent, (Node*)NULL, "No parent");
		rbtree.insert(std::string("y"));
		test.unequal(rbtree._root->right_child, (Node*)NULL, "Right child is not empty");
		Node* y = rbtree._root->right_child;
		test.equal(y->color, 'r', "Color of new node is red");
		test.equal(*(y->data), std::string("y"), "Data is correct");
		test.equal(y->parent, rbtree._root, "Parent is root node");
		test.equal(y->left_child, (Node*)NULL, "No left child");
		test.equal(y->right_child, (Node*)NULL, "No right child");
		test.equal(testIsTreeValid(rbtree._root), true);
	}
	{
		Test test("Insert with four items (E2) lc");
		ft::RBTree<std::string> rbtree;
		test.equal(rbtree._root, (Node*)NULL, "Tree is empty in the beginning");

		rbtree.insert(std::string("x"));
		test.unequal(rbtree._root, (Node*)NULL, "Tree is not empty anymore");
		Node* x = rbtree._root;
		test.equal(rbtree._root->color, 'b', "Node is black");
		test.equal(*(rbtree._root->data), std::string("x"), "Data is correct");
		test.equal(rbtree._root->left_child, (Node*)NULL, "No left child");
		test.equal(rbtree._root->right_child, (Node*)NULL, "No right child");
		test.equal(rbtree._root->parent, (Node*)NULL, "No parent");

		rbtree.insert(std::string("y"));
		test.unequal(rbtree._root->right_child, (Node*)NULL, "Right child is not empty");
		Node* y = rbtree._root->right_child;
		test.equal(y->color, 'r', "Color of new node is red");
		test.equal(*(y->data), std::string("y"), "Data is correct");
		test.equal(y->parent, rbtree._root, "Parent is root node");
		test.equal(y->left_child, (Node*)NULL, "No left child");
		test.equal(y->right_child, (Node*)NULL, "No right child");

		rbtree.insert(std::string("a"));
		test.unequal(rbtree._root->left_child, (Node*)NULL, "Left child is not empty");
		Node* a = rbtree._root->left_child;
		test.equal(a->color, 'r', "Color of new node is red");
		test.equal(*(a->data), std::string("a"), "Data is correct");
		test.equal(a->parent, rbtree._root, "Parent is root node");
		test.equal(a->left_child, (Node*)NULL, "No left child");
		test.equal(a->right_child, (Node*)NULL, "No right child");

		rbtree.insert(std::string("z"));
		test.unequal(y->right_child, (Node*)NULL, "Right child is not empty");
		Node* z = y->right_child;
		test.equal(z->color, 'r', "Color of new node is red");
		test.equal(*(z->data), std::string("z"), "Data is correct");
		test.equal(z->parent, y, "Parent is y");
		test.equal(z->left_child, (Node*)NULL, "No left child");
		test.equal(z->right_child, (Node*)NULL, "No right child");

		test.equal(x->color, 'r');
		test.equal(y->color, 'b');
		test.equal(a->color, 'b');

		rbtree.print_node(rbtree._root, true);
		test.equal(testIsTreeValid(rbtree._root), true);
	}
	{
		Test test("Insert with three items (E2) rc");
		ft::RBTree<std::string> rbtree;
		test.equal(rbtree._root, (Node*)NULL, "Tree is empty in the beginning");

		rbtree.insert(std::string("c"));
		test.unequal(rbtree._root, (Node*)NULL, "Tree is not empty anymore");
		Node* c = rbtree._root;
		test.equal(c->color, 'b', "Node is black");
		test.equal(*(c->data), std::string("c"), "Data is correct");
		test.equal(c->left_child, (Node*)NULL, "No left child");
		test.equal(c->right_child, (Node*)NULL, "No right child");
		test.equal(c->parent, (Node*)NULL, "No parent");

		rbtree.insert(std::string("b"));
		Node* b = rbtree._root->left_child;
		test.equal(b->color, 'r', "Color of new node is red");
		test.equal(*(b->data), std::string("b"), "Data is correct");
		test.equal(b->parent, rbtree._root, "Parent is root node");
		test.equal(b->left_child, (Node*)NULL, "No left child");
		test.equal(b->right_child, (Node*)NULL, "No right child");

		rbtree.insert(std::string("z"));
		Node* z = rbtree._root->right_child;
		test.equal(z->color, 'r', "Color of new node is red");
		test.equal(*(z->data), std::string("z"), "Data is correct");
		test.equal(z->parent, rbtree._root, "Parent is root node");
		test.equal(z->left_child, (Node*)NULL, "No left child");
		test.equal(z->right_child, (Node*)NULL, "No right child");

		rbtree.insert(std::string("a"));
		Node* a = b->left_child;
		test.equal(a->color, 'r', "Color of new node is red");
		test.equal(*(a->data), std::string("a"), "Data is correct");
		test.equal(a->parent, b, "Parent is y");
		test.equal(a->left_child, (Node*)NULL, "No left child");
		test.equal(a->right_child, (Node*)NULL, "No right child");

		test.equal(a->color, 'r');
		test.equal(b->color, 'b');
		test.equal(z->color, 'b');

		rbtree.print_node(rbtree._root, true);
		test.equal(testIsTreeValid(rbtree._root), true);
	}
	{
		Test test("Insert with three items (E3/E4) lc");
		ft::RBTree<std::string> rbtree;
		rbtree.insert(std::string("c"));
		rbtree.insert(std::string("e"));
		rbtree.insert(std::string("d"));
		rbtree.print_node(rbtree._root, true);
		Node* d = rbtree._root;
		test.equal(*(d->data), std::string("d"), "d is root node");
		test.unequal(d->left_child, (Node*)NULL, "d has left child");
		test.unequal(d->left_child, (Node*)NULL, "d has right child");
		test.equal(*(d->left_child->data), std::string("c"), "left child is c");
		test.equal(*(d->right_child->data), std::string("e"), "right child is e");
		test.equal(d->color, 'b', "d is black");
		test.equal(d->left_child->color, 'r', "left child is red");
		test.equal(d->right_child->color, 'r', "right child is red");
		test.equal(testIsTreeValid(rbtree._root), true);
	}
	{
		Test test("Insert with three items (E3/E4) rc");
		ft::RBTree<std::string> rbtree;
		rbtree.insert(std::string("c"));
		rbtree.insert(std::string("a"));
		rbtree.insert(std::string("b"));
		rbtree.print_node(rbtree._root, true);
		Node* d = rbtree._root;
		test.equal(*(d->data), std::string("b"), "d is root node");
		test.unequal(d->left_child, (Node*)NULL, "d has left child");
		test.unequal(d->left_child, (Node*)NULL, "d has right child");
		test.equal(*(d->left_child->data), std::string("a"), "left child is a");
		test.equal(*(d->right_child->data), std::string("c"), "right child is c");
		test.equal(d->color, 'b', "d is black");
		test.equal(d->left_child->color, 'r', "left child is red");
		test.equal(d->right_child->color, 'r', "right child is red");
		test.equal(testIsTreeValid(rbtree._root), true);
	}
	{
		Test test("Testing around");
		ft::RBTree<std::string> rbtree;
		rbtree.insert(std::string("e"));
		rbtree.insert(std::string("c"));
		rbtree.insert(std::string("d"));
		rbtree.insert(std::string("f"));
		rbtree.insert(std::string("a"));
		rbtree.insert(std::string("b"));
		rbtree.insert(std::string("g"));
		rbtree.insert(std::string("h"));
		rbtree.print_node(rbtree._root, true);
		test.equal(testIsTreeValid(rbtree._root), true, "Is Tree valid");
	}
	{
		Test test("delete root from tree");
		ft::RBTree<std::string> rbtree;
		rbtree.insert(std::string("e"));
		test.unequal(rbtree._root, (Node*)NULL);
		rbtree.remove(std::string("e"));
		test.equal(rbtree._root, (Node*)NULL);
	}
	{
		Test test("delete root from tree with 2 children");
		ft::RBTree<std::string> rbtree;
		rbtree.insert(std::string("e"));
		test.unequal(rbtree._root, (Node*)NULL);
		rbtree.insert(std::string("f"));
		rbtree.insert(std::string("c"));
		rbtree.print_node(rbtree._root, true);
		rbtree.remove(std::string("e"));
		test.unequal(rbtree._root, (Node*)NULL);
		test.equal(rbtree._root->color, 'b');
		test.equal(*(rbtree._root->data), std::string("f"), "Root is now f");
		test.equal(testIsTreeValid(rbtree._root), true, "Tree is red/black");
		rbtree.print_node(rbtree._root, true);
	}
	{
		Test test("delete from tree with 2 children");
		ft::RBTree<std::string> rbtree;
		rbtree.insert(std::string("e"));
		test.unequal(rbtree._root, (Node*)NULL);
		rbtree.insert(std::string("f"));
		rbtree.insert(std::string("c"));
		rbtree.insert(std::string("a"));
		rbtree.insert(std::string("d"));
		rbtree.insert(std::string("j"));
		rbtree.print_node(rbtree._root, true);
		rbtree.remove(std::string("e"));
		test.unequal(rbtree._root, (Node*)NULL);
		test.equal(testIsTreeValid(rbtree._root), true, "Tree is red/black");
		rbtree.print_node(rbtree._root, true);
	}
}
