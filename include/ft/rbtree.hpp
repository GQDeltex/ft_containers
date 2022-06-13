#ifndef FT_RBTREE_H
# define FT_RBTREE_H
# include "pairs.hpp"
# include <cstddef>
# include <iostream>
# include <stdexcept>

namespace ft {
	template <class T>
	class RBTree {
		public:
			struct Node {
				T		data;
				char	color;
				Node*	right_child;
				Node*	left_child;
				Node*	parent;
			};
			Node*	root;
			void	rotate_left(Node* target) {
				if (target->right_child == nullptr)
					throw std::runtime_error("Cannot rotate left with no right child");
				Node* x = target;
				Node* y = target->right_child;
				Node* p = target->parent;

				if (y->left_child != nullptr) {
					std::cout << "Has child, moving to x" << std::endl;
					x->right_child = y->left_child;
				}
				else {
					x->right_child = nullptr;
				}
				if (x->parent == nullptr) {
					std::cout << "Is root, replacing" << std::endl;
					this->root = y;
					y->parent = nullptr;
				}
				else if (p->left_child == x) {
					std::cout << "Is left_child, replacing" << std::endl;
					p->left_child = y;
					y->parent = p;
				}
				else {
					std::cout << "Is right_child, replacing" << std::endl;
					p->right_child = y;
					y->parent = p;
				}
				std::cout << "Setting new parent and child" << std::endl;
				x->parent = y;
				y->left_child = x;
			}
			void	rotate_right(Node *target) {
				if (target->left_child == nullptr)
					throw std::runtime_error("Cannot rotate right with no left child");
				Node* y = target;
				Node* x = target->left_child;
				Node* p = target->parent;

				if (x->right_child != nullptr) {
					std::cout << "Has child, moving to y" << std::endl;
					y->left_child = x->right_child;
				}
				else {
					y->left_child = nullptr;
				}
				if (y->parent == nullptr) {
					std::cout << "Is root, replacing" << std::endl;
					this->root = x;
					x->parent = nullptr;
				} else if (p->right_child == y) {
					std::cout << "Is right_child, replacing" << std::endl;
					p->right_child = x;
					x->parent = p;
				} else {
					std::cout << "Is left_child, replacing" << std::endl;
					p->left_child = x;
					x->parent = p;
				}
				std::cout << "Setting new parent and child" << std::endl;
				y->parent = x;
				x->right_child = y;
			}
			void rotate_left_right(Node* target) {
				if (target->left_child == nullptr)
					throw std::runtime_error("Cannot rotate left-right with no left child");
				if (target->left_child->right_child == nullptr)
					throw std::runtime_error("Cannot rotate left-right with no right child-child");
				Node* z = target;
				Node* x = target->left_child;

				rotate_left(x);
				rotate_right(z);
			}
			void rotate_right_left(Node* target) {
				if (target->right_child == nullptr)
					throw std::runtime_error("Cannot rotate right_left with no right child");
				if (target->right_child->left_child == nullptr)
					throw std::runtime_error("Cannot rotate right-left with no left child-child");
				Node* z = target;
				Node* x = target->right_child;

				rotate_right(x);
				rotate_left(z);
			}
			Node*	create_node(T data, Node* parent=nullptr) {
				Node* node = new Node;
				node->color = 'r';
				node->right_child = nullptr;
				node->left_child = nullptr;
				node->parent = parent;
				if (parent != nullptr) {
					if (parent->left_child == nullptr)
						parent->left_child = node;
					else if (parent->right_child == nullptr)
						parent->right_child = node;
					else
						throw std::runtime_error("No free child available");
				}
				node->data = data;
				return node;
			}
			void print_node(Node *target, bool recurse=false) {
				if (target->left_child != nullptr && recurse)
					print_node(target->left_child, recurse);
				if (target->right_child != nullptr && recurse)
					print_node(target->right_child, recurse);
				std::cout << "Node: " << target->data << std::endl;
				std::cout << "       Color: " << target->color << std::endl;
				std::cout << "      Parent: ";
				if (target->parent != nullptr)
					std::cout << target->parent->data << std::endl;
				else
					std::cout << "-" << std::endl;
				std::cout << "  Left Child: ";
				if (target->left_child != nullptr)
					std::cout << target->left_child->data << std::endl;
				else
					std::cout << "-" << std::endl;
				std::cout << " Right Child: ";
				if (target->right_child != nullptr)
					std::cout << target->right_child->data << std::endl;
				else
					std::cout << "-" << std::endl;
			}
	};
}

#endif
