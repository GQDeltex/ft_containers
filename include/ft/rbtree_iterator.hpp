#ifndef FT_SET_ITERATOR_H
# define FT_SET_ITERATOR_H

#include <ctime>
# include <functional>
# include <iterator>
# include <stdexcept>
# include "rbtree.hpp"


namespace ft {
	template<
		typename T,
		typename Comp = std::less<T>
	>class rbtree_iterator: public std::iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef T																						value_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::difference_type	difference_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::pointer			pointer;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::reference			reference;
			typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef Comp																					value_compare;

		protected:
			typedef Node<value_type>*	node_ptr;
			node_ptr					_node;
			node_ptr					_prev;
			value_compare				_comp;

		public:
			// Constructors
			rbtree_iterator(value_compare comp = value_compare()): _comp(comp) {
				this->_node = NULL;
				this->_prev = NULL;
			}

			rbtree_iterator(const node_ptr node, value_compare comp = value_compare(), const node_ptr prev=NULL): _node(node), _prev(prev) , _comp(comp){}

			operator rbtree_iterator<T const, Comp>() const {
				return rbtree_iterator<T const, Comp>((Node<value_type const>*)this->_node, this->_comp, (Node<value_type const>*)this->_prev);
			}

			rbtree_iterator(const rbtree_iterator& rbi): _node(rbi._node), _prev(rbi._prev), _comp(rbi._comp) {}

			// Assignment Operator
			rbtree_iterator& operator= (const rbtree_iterator& rbi) {
				this->_node = rbi._node;
				this->_comp = rbi._comp;
				this->_prev = rbi._prev;
				return *this;
			}

			// Destructor
			~rbtree_iterator() {}

			// Address
			node_ptr address() const {
				return this->_node;
			}

			// Dereference Operator
			reference operator*() const {
				if (this->_node == NULL || this->_node == (node_ptr)0xDEAD || this->_node == (node_ptr)0xBEEF)
					throw std::runtime_error("Cannot dereference iterator");
				return *(this->_node->data);
			}

			pointer operator->() const {
				if (this->_node == NULL || this->_node == (node_ptr)0xDEAD || this->_node == (node_ptr)0xBEEF)
					throw std::runtime_error("Cannot dereference iterator");
				return this->_node->data;
			}

			// Arithmetic Operators
			rbtree_iterator& operator++() {
				if (this->_node == NULL && this->_node != (node_ptr)0xDEAD)
					throw std::runtime_error("Cannot increment iterator");
				node_ptr target = this->__find_next_node(this->_node);
				if (target == NULL) {
					this->_prev = this->_node;
					this->_node = (node_ptr)0xDEAD;
					return *this;
				}
				this->_node = target;
				return *this;
			}

			rbtree_iterator operator++(int) {
				rbtree_iterator temp = *this;
				++(*this);
				return temp;
			}

			rbtree_iterator& operator--() {
				if (this->_node == NULL && this->_node != (node_ptr)0xBEEF)
					throw std::runtime_error("Cannot decrement iterator");
				node_ptr target = this->__find_previous_node(this->_node);
				if (target == NULL) {
					this->_prev = this->_node;
					this->_node = (node_ptr)0xBEEF;
					return *this;
				}
				this->_node = target;
				return *this;
			}

			rbtree_iterator operator--(int) {
				rbtree_iterator temp = *this;
				--(*this);
				return temp;
			}

			// Relational Operators
			bool operator==(const rbtree_iterator<value_type, value_compare>& rhs) {
				return this->_node == rhs._node;
			}

			bool operator!=(const rbtree_iterator<value_type, value_compare>& rhs) {
				return !(*this == rhs);
			}

		private:
			node_ptr __find_next_node(node_ptr target) {
				if (target == (node_ptr)0xBEEF)
					return this->_prev;
				node_ptr start = target;
				if (target->right_child != NULL) {
					target = target->right_child;
					while (target->left_child != NULL) {
						target = target->left_child;
					}
					return target;
				}
				if (target->parent != NULL) {
					while (target->parent != NULL) {
						if (this->_comp(*(target->parent->data), *(target->data)))
							target = target->parent;
						else
							break;
					}
					target = target->parent;
					if (target != start)
						return target;
				}
				return NULL;
			}

			node_ptr __find_previous_node(node_ptr target) {
				if (target == (node_ptr)0xDEAD)
					return this->_prev;
				if (target->left_child != NULL) {
					target = target->left_child;
					while (target->right_child != NULL)
						target = target->right_child;
					return target;
				}
				if (target->parent != NULL) {
					while (target->parent != NULL && this->_comp(*(target->data), *(target->parent->data)))
						target = target->parent;
					target = target->parent;
					return target;
				}
				return NULL;
			}
	};
}

#endif
