#include "Test.hpp"
#include "../include/ft/rbtree_iterator.hpp"

void TestRBTreeIterator(void) {
	{
		Test test("Default Constructor");
		ft::rbtree_iterator<char> it;
		try {
			*it;
			test.equal(true, false, "Can not dereference");
		} catch (const std::exception& e) {
			// nothing
		}
	}
	{
		Test test("Constructor from RBTree");
		ft::RBTree<char> rbt;
		rbt.insert('g');
		rbt.insert('x');
		ft::rbtree_iterator<char> it(rbt.begin());
		test.equal(*it, 'g');
	}
	{
		Test test("Constructor from Iterator");
		ft::RBTree<char> rbt;
		rbt.insert('g');
		rbt.insert('x');
		ft::rbtree_iterator<char> it(rbt.begin());
		test.equal(*it, 'g');
		ft::rbtree_iterator<char> it2(it);
		test.equal(*it2, 'g');
	}
	{
		Test test("Arithmetic");
		ft::RBTree<char> rbt;
		rbt.insert('g');
		rbt.insert('x');
		rbt.insert('h');
		ft::rbtree_iterator<char> it(rbt.begin());
		test.equal(*it, 'g');
		it++;
		test.equal(*it, 'h');
		it++;
		test.equal(*it, 'x');
		it++;
		try {
			*it;
			test.equal(true, false, "Cannot dereference NULL");
		} catch (const std::exception& e) {
			// Nothing
		}
		it--;
		test.equal(*it, 'x');
		it--;
		test.equal(*it, 'h');
		it--;
		test.equal(*it, 'g');
		it--;
		try {
			*it;
			test.equal(true, false, "Cannot dereference NULL");
		} catch (const std::exception& e) {
			// Nothing
		}
		it++;
		test.equal(*it, 'g');
	}
}
