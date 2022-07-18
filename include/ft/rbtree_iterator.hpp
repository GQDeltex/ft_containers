#ifndef FT_SET_ITERATOR_H
# define FT_SET_ITERATOR_H

# include <functional>
# include <iterator>
# include <stdexcept>
# include "rbtree.hpp"


namespace ft {
	template<
		typename T,
		typename Comp = std::less<T>
	>class rbtree_iterator: public std::iterator<std::bidirectional_iterator_tag, T> {
		private:
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>	stditr;
		public:
			typedef T									value_type;
			typedef typename stditr::difference_type	difference_type;
			typedef typename stditr::pointer			pointer;
			typedef typename stditr::reference			reference;
			typedef typename stditr::iterator_category	iterator_category;
			typedef Comp				value_compare;
			typedef Node<value_type>*	node_ptr;
		protected:
			node_ptr		_node;
			node_ptr		_prev;
			value_compare	_comp;
		public:

			rbtree_iterator(value_compare comp = value_compare()) {
				this->_node = NULL;
				this->_comp = comp;
				this->_prev = NULL;
			}
			rbtree_iterator(const node_ptr node, value_compare comp = value_compare()) {
				this->_node = node;
				this->_comp = comp;
				this->_prev = NULL;
			}
			operator rbtree_iterator<T const>() const {
				return rbtree_iterator<T const>((Node<value_type const>*)this->_node);
			}
			rbtree_iterator(const rbtree_iterator& rbi) {
				*this = rbi;
			}
			rbtree_iterator& operator=(const rbtree_iterator& rbi) {
				this->_node = rbi._node;
				this->_comp = rbi._comp;
				this->_prev = rbi._prev;
				return *this;
			}
			~rbtree_iterator() {}

			friend bool	operator==(const rbtree_iterator& lhs, const rbtree_iterator& rhs) {
				return lhs._node == rhs._node;
			}

			reference	operator*() {
				if (this->_node == NULL || this->_node == (node_ptr)0xDEAD || this->_node == (node_ptr)0xBEEF)
					throw std::runtime_error("Cannot dereference iterator");
				return this->_node->data;
			}
			pointer		operator->() const {
				return &(operator*());
			}
			rbtree_iterator&	operator++() {
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
			rbtree_iterator		operator++(int) {
				if (this->_node == NULL && this->_node != (node_ptr)0xDEAD)
					throw std::runtime_error("Cannot increment iterator");
				ft::rbtree_iterator<value_type> temp = *this;
				node_ptr target = this->__find_next_node(this->_node);
				if (target == NULL) {
					this->_prev = this->_node;
					this->_node = (node_ptr)0xDEAD;
					return temp;
				}
				this->_node = target;
				return temp;
			}
			rbtree_iterator&	operator--() {
				if (this->_node == NULL && this->node != (node_ptr)0xBEEF)
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
			rbtree_iterator		operator--(int) {
				if (this->_node == NULL && this->_node != (node_ptr)0xBEEF)
					throw std::runtime_error("Cannot decrement iterator");
				ft::rbtree_iterator<value_type> temp = *this;
				node_ptr target = this->__find_previous_node(this->_node);
				if (target == NULL) {
					this->_prev = this->_node;
					this->_node = (node_ptr)0xBEEF;
					return temp;
				}
				this->_node = target;
				return temp;
			}
		private:
			node_ptr	__find_next_node(node_ptr target) {
				if (target == (node_ptr)0xBEEF)
					return this->_prev;
				node_ptr start = target;
				if (target->right_child != NULL) {
					target = target->right_child;
					while(target->left_child != NULL) {
						target = target->left_child;
					}
					return target;
				}
				if (target->parent != NULL) {
					while (target->parent != NULL) {
						if (this->_comp(target->parent->data, target->data))
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
			node_ptr	__find_previous_node(node_ptr target) {
				if (target == (node_ptr)0xDEAD)
					return this->_prev;
				node_ptr start = target;
				if (target->left_child != NULL) {
					target = target->left_child;
					while(target->right_child != NULL) {
						target = target->right_child;
					}
					return target;
				}
				if (target->parent != NULL) {
					while (target->parent != NULL) {
						if (this->_comp(target->data, target->parent->data))
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
	};
	template<
		typename T
	>bool operator!=(const rbtree_iterator<T>& lhs, const rbtree_iterator<T>& rhs) {
		return !(lhs == rhs);
	}
}

#endif
