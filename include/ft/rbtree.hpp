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
			bool	(*comp)(T, T);
			RBTree(bool (*f)(T, T) = NULL) {
				this->root = NULL;
				this->comp = this->default_comp;
				if (f != NULL)
					this->comp = f;
			}
			bool	static default_comp(T lhs, T rhs) {
				return lhs < rhs;
			}
			void	insert(T data) {
				Node* new_node = create_node(data);
				if (this->root == NULL) {
					new_node->color = 'b';
					this->root = new_node;
					return;
				}
				Node* current_node = this->root;
				while (1) {
					Node** leaf = NULL;
					if (this->comp(current_node->data, new_node->data)) {
						std::cout << "Left tree" << std::endl;
						leaf = &(current_node->left_child);
					} else {
						std::cout << "Right tree" << std::endl;
						leaf = &(current_node->right_child);
					}
					if (*leaf == NULL) {
						std::cout << "Found NULL, inserting" << std::endl;
						*leaf = new_node;
						new_node->parent = current_node;
						break;
					} else {
						std::cout << "Traversing deeper" << std::endl;
						current_node = *leaf;
						continue;
					}
				}
				this->maintain_insert(new_node);
			}
			void	maintain_insert(Node* target) {
				if (target->parent == NULL) {
					std::cout << "Nothing to do, there is no parent" << std::endl;
					return;
				}
				if (target->parent->parent == NULL) {
					std::cout << "Nothing to do, there is no grandparent" << std::endl;
					return;
				}
				std::cout << "Maintaining Red-Black constraint" << std::endl;
				while (target->parent->color != 'b') {
					std::cout << "Looping" << std::endl;
					this->print_node(this->root, true);
					if (target->parent == target->parent->parent->left_child) {
						if (target->parent->parent->right_child->color == 'r') {
							std::cout << "Case I" << std::endl;
							target->parent->parent->right_child->color = 'b';
							target->parent->parent->left_child->color = 'b';
							target->parent->parent->color = 'r';
							target = target->parent->parent;
						} else {
							if (target == target->parent->right_child) {
								std::cout << "Case II" << std::endl;
								target = target->parent;
								this->rotate_left(target);
							}
							std::cout << "Case III" << std::endl;
							target->parent->color = 'b';
							target->parent->parent->color = 'r';
							this->rotate_right(target->parent->parent);
						}
					} else {
						if (target->parent->parent->left_child->color == 'r') {
							std::cout << "Case IV" << std::endl;
							target->parent->parent->left_child->color = 'b';
							target->parent->parent->right_child->color = 'b';
							target->parent->parent->color = 'r';
							target = target->parent->parent;
						} else {
							std::cout << "Case V" << std::endl;
							if (target == target->parent->left_child) {
								target = target->parent;
								this->rotate_right(target);
							}
							target->parent->color = 'b';
							target->parent->parent->color = 'r';
							this->rotate_left(target->parent->parent);
						}
					}
					if (target->parent == NULL) {
						std::cout << "Target is root node, done balancing" << std::cout;
						return;
					}
				}
				this->root->color = 'b';
				std::cout << "Done balancing" << std::endl;
			}
			void	rotate_left(Node* target) {
				std::cout << "Rotate Left" << std::endl;
				if (target->right_child == NULL)
					throw std::runtime_error("Cannot rotate left with no right child");
				Node* x = target;
				Node* y = target->right_child;
				Node* p = target->parent;

				if (y->left_child != NULL) {
					std::cout << "Has child, moving to x" << std::endl;
					x->right_child = y->left_child;
				}
				else {
					x->right_child = NULL;
				}
				if (x->parent == NULL) {
					std::cout << "Is root, replacing" << std::endl;
					this->root = y;
					y->parent = NULL;
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
				std::cout << "Rotate Right" << std::endl;
				if (target->left_child == NULL)
					throw std::runtime_error("Cannot rotate right with no left child");
				Node* y = target;
				Node* x = target->left_child;
				Node* p = target->parent;

				if (x->right_child != NULL) {
					std::cout << "Has child, moving to y" << std::endl;
					y->left_child = x->right_child;
				}
				else {
					y->left_child = NULL;
				}
				if (y->parent == NULL) {
					std::cout << "Is root, replacing" << std::endl;
					this->root = x;
					x->parent = NULL;
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
				std::cout << "Rotate Left-Right" << std::endl;
				if (target->left_child == NULL)
					throw std::runtime_error("Cannot rotate left-right with no left child");
				if (target->left_child->right_child == NULL)
					throw std::runtime_error("Cannot rotate left-right with no right child-child");
				Node* z = target;
				Node* x = target->left_child;

				rotate_left(x);
				rotate_right(z);
			}
			void rotate_right_left(Node* target) {
				std::cout << "Rotate Right-Left" << std::endl;
				if (target->right_child == NULL)
					throw std::runtime_error("Cannot rotate right_left with no right child");
				if (target->right_child->left_child == NULL)
					throw std::runtime_error("Cannot rotate right-left with no left child-child");
				Node* z = target;
				Node* x = target->right_child;

				rotate_right(x);
				rotate_left(z);
			}
			Node*	create_node(T data) {
				Node* node = new Node;
				node->color = 'r';
				node->right_child = NULL;
				node->left_child = NULL;
				node->parent = NULL;
				node->data = data;
				return node;
			}
			void print_node(Node *target, bool recurse=false) {
				if (target->left_child != NULL && recurse)
					print_node(target->left_child, recurse);
				std::cout << "Node: " << target->data << std::endl;
				std::cout << "       Color: " << target->color << std::endl;
				std::cout << "      Parent: ";
				if (target->parent != NULL)
					std::cout << target->parent->data << std::endl;
				else
					std::cout << "-" << std::endl;
				std::cout << "  Left Child: ";
				if (target->left_child != NULL)
					std::cout << target->left_child->data << std::endl;
				else
					std::cout << "-" << std::endl;
				std::cout << " Right Child: ";
				if (target->right_child != NULL)
					std::cout << target->right_child->data << std::endl;
				else
					std::cout << "-" << std::endl;
				if (target->right_child != NULL && recurse)
					print_node(target->right_child, recurse);
			}
			void	delete_node(Node *target) {
				if (target->left_child != NULL)
					delete_node(target->left_child);
				if (target->right_child != NULL)
					delete_node(target->right_child);
				delete target;
			}
			~RBTree() {
				this->delete_node(this->root);
			}
	};
}

#endif
