#ifndef FT_RBTREE_H
# define FT_RBTREE_H
# include "pairs.hpp"
# include <cstddef>
# include <iostream>
# include <stdexcept>
# include <memory>

namespace ft {

	template<
		typename T
	>struct Node {
		T			data;
		char		color;
		Node*		right_child;
		Node*		left_child;
		Node*		parent;
	};

	template <
		class T,
		class Compare = std::less<T>,
		class Alloc = std::allocator<Node<T> >
	>class RBTree {
		public:
			typedef T					value_type;
			typedef Alloc				allocator_type;
			typedef Compare				value_compare;
			typedef size_t				size_type;

		protected:
			typedef Node<value_type>*	node_ptr;

			value_compare	_comp;
			size_type		_size;
			allocator_type	_alloc;

		private:
			node_ptr	__copy_deep(node_ptr target) {
				if (target == NULL)
					return NULL;
				node_ptr new_node = this->create_node(target->data);
				this->_size--; // Fix runaway size
				new_node->color = target->color;
				new_node->left_child = __copy_deep(target->left_child);
				if (new_node->left_child != NULL)
					new_node->left_child->parent = new_node;
				new_node->right_child = __copy_deep(target->right_child);
				if (new_node->right_child != NULL)
					new_node->right_child->parent = new_node;
				return new_node;
			}

		public:
			node_ptr			_root;

			RBTree(
				const value_compare& comp = value_compare(),
				const allocator_type& alloc = allocator_type()
			) {
				this->_root = NULL;
				this->_size = 0;
				this->_comp = comp;
				this->_alloc = alloc;
			}
			RBTree(const RBTree& rbt) {
				*this = rbt;
			}
			RBTree&	operator=(const RBTree& rbt) {
				this->_root = this->__copy_deep(rbt._root);
				this->_size = rbt._size;
				this->_comp = rbt._comp;
				this->_alloc = rbt._alloc;
				return *this;
			}
			size_type	size() const {
				return this->_size;
			}
			void	insert(T data) {
				node_ptr new_node = create_node(data);
				if (this->_root == NULL) {
					std::cout << "Is now root node" << std::endl;
					new_node->color = 'b';
					this->_root = new_node;
					return;
				}
				node_ptr current_node = this->_root;
				while (1) {
					node_ptr* leaf = NULL;
					if (this->_comp(current_node->data, new_node->data)) {
						std::cout << "Left tree" << std::endl;
						leaf = &(current_node->left_child);
					} else if (this->_comp(new_node->data, current_node->data)) {
						std::cout << "Right tree" << std::endl;
						leaf = &(current_node->right_child);
					} else {
						throw std::runtime_error("Node already exists");
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
			node_ptr	__bst_find_delete(node_ptr target) {
				std::cout << "BST DELETE" << std::endl;
				node_ptr D = target;
				// Step 1
				if (this->__num_children(D) != 2) {
					std::cout << "Less than 2 children" << std::endl;
					node_ptr F = D->right_child;
					if (D->left_child != NULL)
						F = D->left_child;
					// Step 2
					if (D == this->_root) {
						return D;
					}
					// Step 3
					node_ptr G = D->parent;
					if (D == G->left_child)
						G->left_child = F;
					else
						G->right_child = F;
					if (F != NULL)
						F->parent = G;
					return D;
				}
				std::cout << "2 Children" << std::endl;
				// Step 4
				node_ptr E = this->__find_leftmost(D->right_child);
				std::cout << "Node is: " << D->data << std::endl;
				std::cout << "Node to switch with: " << E->data << std::endl;
				node_ptr G = E->parent;

				// Save the data
				D->data = E->data;
				this->print_node(this->_root, true);
				std::cout << "         " << std::endl;

				// Get the (maybe) remaining child
				node_ptr F = E->right_child;
				if (G == E->right_child)
					F = E->left_child;

				// Replace node with child
				if (E == G->left_child)
					G->left_child = F;
				else
					G->right_child = F;
				if (F != NULL)
					F->parent = G;

				this->print_node(this->_root, true);

				return E;
			}
			node_ptr	__find_leftmost(node_ptr target) {
				if (target->left_child != NULL) {
					return this->__find_leftmost(target->left_child);
				}
				return target;
			}
			void	remove(T data) {
				std::cout << "Removing node" << std::endl;
				node_ptr target = this->__find_node(this->_root, data);
				if (target == NULL)
					throw std::runtime_error("Cannot find Node");
				// Do recursive BST delete (which results in the to be deleted
				// node having a maximum of 1 children)
				target = this->__bst_find_delete(target);
				// target is root and has no children
				if (target == this->_root && this->__num_children(target) == 0) {
					std::cout << "target is root and has no children" << std::endl;
					delete_node(target);
					this->_root = NULL;
					return;
				}
				// target is black and has one child
				if (this->__num_children(target) == 1) {
					std::cout << "Target is black and has one child" << std::endl;
					node_ptr parent = target->parent;
					node_ptr child = NULL;
					if (target->left_child != NULL)
						child = target->left_child;
					else
						child = target->right_child;
					child->color = 'b';
					if (target == parent->left_child)
						parent->left_child = child;
					else
						parent->right_child = child;
					child->parent = parent;
					delete_node(target);
					return;
				}
				// target is red and has no children
				if (target->color == 'r' && this->__num_children(target) == 0) {
					std::cout << "Target is red and has no children" << std::endl;
					delete_node(target);
					return;
				}
				// target is not root has no children and is black
				if (target != this->_root && this->__num_children(target) == 0 && target->color == 'b') {
					std::cout << "target is not root and has no children and is black" << std::endl;
					this->maintain_remove(target);
					delete_node(target);
					return;
				}
			}
			void	maintain_remove(node_ptr target) {
				std::cout << "Maintaining tree after removal" << std::endl;
				while (1) {
					std::cout << "--> Looping <--" << std::endl;
					this->print_node(this->_root, true);
					std::cout << "-->         <--" << std::endl;
					// L0
					if (target == this->_root) {
						std::cout << "L0" << std::endl;
						break;
					}
					node_ptr parent = target->parent;
					node_ptr sibling = parent->left_child;
					node_ptr close = sibling->right_child;
					node_ptr distant = sibling->left_child;
					if (target == parent->left_child) {
						sibling = parent->right_child;
						close = sibling->left_child;
						distant = sibling->right_child;
					}
					// L1
					// parent and sibling and close and distand if they exist are black
					if (
							parent->color == 'b'
							&& sibling->color == 'b'
							&& !(close != NULL && close->color == 'r')
							&& !(distant != NULL && distant->color == 'r')
					   ) {
						std::cout << "L1" << std::endl;
						sibling->color = 'r';
						target = parent;
						continue;
					}
					// L2
					// sibling is red
					if (sibling->color == 'r') {
						std::cout << "L2" << std::endl;
						// dir-rotation
						if (target == parent->left_child)
							rotate_left(parent);
						else
							rotate_right(parent);
						// Invert color of parent
						if (parent->color == 'r')
							parent->color = 'b';
						else
							parent->color = 'r';
						// Invert color of sibling
						if (sibling->color == 'r')
							sibling->color = 'b';
						else
							sibling->color = 'r';
						continue;
					}
					// L3
					// parent is red, but sibling and close and distant are black if they exist
					if (
						parent->color == 'r'
						&& sibling->color == 'b'
						&& !(close != NULL && close->color == 'r')
						&& !(distant != NULL && distant->color == 'r')
					) {
						std::cout << "L3" << std::endl;
						// Invert color of parent
						if (parent->color == 'r')
							parent->color = 'b';
						else
							parent->color = 'r';
						// Invert color of sibling
						if (sibling->color == 'r')
							sibling->color = 'b';
						else
							sibling->color = 'r';
						break;
					}
					// L4
					// sibling is black, close is red, distant (if exists) is black
					if (
						sibling->color == 'b'
						&& close->color == 'r'
						&& !(distant != NULL && distant->color == 'r')
				    ) {
						std::cout << "L4" << std::endl;
						// not-dir rotation
						if (target == parent->left_child)
							rotate_right(sibling);
						else
							rotate_left(sibling);
						// Invert color of sibling
						if (sibling->color == 'r')
							sibling->color = 'b';
						else
							sibling->color = 'r';
						// Invert color of close
						if (close->color == 'r')
							close->color = 'b';
						else
							close->color = 'r';
						continue;
					}
					// L5
					// sibling is black, distant is red
					if (
						sibling->color == 'b'
						&& distant->color == 'r'
				    ) {
						std::cout << "L5" << std::endl;
						// dir-rotation around parent
						if (target == parent->left_child)
							rotate_left(parent);
						else
							rotate_right(parent);
						sibling->color = parent->color;
						parent->color = 'b';
						distant->color = 'b';
						break;
					}
				}
				std::cout << "Done rebalancing" << std::cout;
			}
			short	__num_children(node_ptr target) {
				short result = 0;
				if (target->right_child != NULL)
					result++;
				if (target->left_child != NULL)
					result++;
				return result;
			}
			node_ptr	__find_node(node_ptr target, T data) {
				node_ptr found = NULL;
				// Not smaller or larget == equal
				if ((!this->_comp(data, target->data)) && (!this->_comp(target->data, data)))
					return target;
				if (target->left_child != NULL && this->_comp(target->data, data)) {
					found = __find_node(target->left_child, data);
					if (found != NULL)
						return found;
				}
				if (target->right_child != NULL && this->_comp(data, target->data)) {
					found = __find_node(target->right_child, data);
					if (found != NULL)
						return found;
				}
				return found;
			}
			void	__recolor(node_ptr target) {
				char newcolor = 'r';
				if (target->color == 'r')
					newcolor = 'b';
				if (target->left_child != NULL) {
					target->left_child->color = newcolor;
					this->__recolor(target->left_child);
				}
				if (target->right_child != NULL) {
					target->right_child->color = newcolor;
					this->__recolor(target->right_child);
				}
			}
			void	maintain_insert(node_ptr target) {
				std::cout << "Maintaining Red-Black constraint" << std::endl;
				while (1) {
					// Setup done
					std::cout << "--> Start Loop <--" << std::endl;
					this->print_node(this->_root, true);
					std::cout << "-->            <--" << std::endl;

					// E0
					// target ist root
					if (target == this->_root) {
						std::cout << "E0" << std::endl;
						break;
					}

					node_ptr parent = target->parent;

					// E5
					// parent ist root
					if (parent == this->_root) {
						std::cout << "E5" << std::endl;
						parent->color = 'b';
						this->__recolor(parent);
						break;
					}

					node_ptr grand = parent->parent;
					node_ptr uncle = NULL;
					if (parent == grand->left_child)
						uncle = grand->right_child;
					else
						uncle = grand->left_child;

					// E1
					// parent ist schwarz
					if (parent->color == 'b') {
						std::cout << "E1" << std::endl;
						break;
					}

					if (uncle != NULL) {
						// E2
						// uncle und parent sind rot
						if (parent->color == 'r' && uncle->color == 'r') {
							std::cout << "E2" << std::endl;
							parent->color = 'b';
							uncle->color = 'b';
							grand->color = 'r';
							target = grand;
							continue;
						}
					}
					// Uncle is black or non-existent and parent is red

					// E3
					// keinen oder schwarzen onkel
					// target is inner child
					if (target == parent->right_child && parent == grand->left_child) {
						std::cout << "E3 lc" << std::endl;
						rotate_left(parent);
						target = parent;
						continue;
					}
					if (target == parent->left_child && parent == grand->right_child) {
						std::cout << "E3 rc" << std::endl;
						rotate_right(parent);
						target = parent;
						continue;
					}
					// E4
					// keinen oder schwarzen onkel
					// target is outer child
					if (target == parent->left_child && parent == grand->left_child) {
						std::cout << "E4 lc" << std::endl;
						rotate_right(grand);
						// Invert grandparent color
						if (grand->color == 'r')
							grand->color = 'b';
						else
							grand->color = 'r';
						// Inver parent color
						if (parent->color == 'r')
							parent->color = 'b';
						else
							parent->color = 'r';
						continue;
					}
					if (target == parent->right_child && parent == grand->right_child) {
						std::cout << "E4 rc" << std::endl;
						rotate_left(grand);
						// Invert grandparent color
						if (grand->color == 'r')
							grand->color = 'b';
						else
							grand->color = 'r';
						// Inver parent color
						if (parent->color == 'r')
							parent->color = 'b';
						else
							parent->color = 'r';
						continue;
					}
				}
				std::cout << "Done balancing" << std::endl;
			}
			void	rotate_left(node_ptr target) {
				std::cout << "Rotate Left" << std::endl;
				if (target->right_child == NULL)
					throw std::runtime_error("Cannot rotate left with no right child");
				node_ptr x = target;
				node_ptr y = target->right_child;
				node_ptr p = target->parent;

				if (y->left_child != NULL) {
					std::cout << "Has child, moving to x" << std::endl;
					x->right_child = y->left_child;
				}
				else {
					x->right_child = NULL;
				}
				if (x->parent == NULL) {
					std::cout << "Is root, replacing" << std::endl;
					this->_root = y;
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
			void	rotate_right(node_ptr target) {
				std::cout << "Rotate Right" << std::endl;
				if (target->left_child == NULL)
					throw std::runtime_error("Cannot rotate right with no left child");
				node_ptr y = target;
				node_ptr x = target->left_child;
				node_ptr p = target->parent;

				if (x->right_child != NULL) {
					std::cout << "Has child, moving to y" << std::endl;
					y->left_child = x->right_child;
				}
				else {
					y->left_child = NULL;
				}
				if (y->parent == NULL) {
					std::cout << "Is root, replacing" << std::endl;
					this->_root = x;
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
			void rotate_left_right(node_ptr target) {
				std::cout << "Rotate Left-Right" << std::endl;
				if (target->left_child == NULL)
					throw std::runtime_error("Cannot rotate left-right with no left child");
				if (target->left_child->right_child == NULL)
					throw std::runtime_error("Cannot rotate left-right with no right child-child");
				node_ptr z = target;
				node_ptr x = target->left_child;

				rotate_left(x);
				rotate_right(z);
			}
			void rotate_right_left(node_ptr target) {
				std::cout << "Rotate Right-Left" << std::endl;
				if (target->right_child == NULL)
					throw std::runtime_error("Cannot rotate right_left with no right child");
				if (target->right_child->left_child == NULL)
					throw std::runtime_error("Cannot rotate right-left with no left child-child");
				node_ptr z = target;
				node_ptr x = target->right_child;

				rotate_right(x);
				rotate_left(z);
			}
			node_ptr	create_node(T data) {

				node_ptr node = this->_alloc.allocate(1);
				this->_alloc.construct(node);
				//node_ptr node = new Node;
				node->color = 'r';
				node->right_child = NULL;
				node->left_child = NULL;
				node->parent = NULL;
				node->data = data;
				this->_size++;
				return node;
			}
			void print_node(node_ptr target, bool recurse=false) {
				if (target == NULL) {
					std::cout << "### Tree empty ###" << std::endl;
					return;
				}
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
			void	delete_node(node_ptr target, bool recurse = false) {
				if (target == NULL)
					return;
				if (target->left_child != NULL && recurse)
					delete_node(target->left_child, recurse);
				if (target->right_child != NULL && recurse)
					delete_node(target->right_child, recurse);
				this->_alloc.destroy(target);
				this->_alloc.deallocate(target, 1);
				this->_size--;
			}
			~RBTree() {
				this->delete_node(this->_root, true);
			}
	};
}

#endif
