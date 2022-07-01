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
	>class rbtree_iterator: std::iterator<T, std::bidirectional_iterator_tag> {
		public:
			typedef T					value_type;
			typedef Comp				value_comp;
			typedef Node<value_type>*	node_ptr;
		protected:
			node_ptr	_node;
			value_comp	_comp;
		public:

			rbtree_iterator(value_comp comp = value_comp()) {
				this->_node = NULL;
				this->_comp = comp;
			}
			rbtree_iterator(const node_ptr node, value_comp comp = value_comp()) {
				this->_node = node;
				this->_comp = comp;
			}
			rbtree_iterator(const rbtree_iterator& rbi) {
				*this = rbi;
			}
			rbtree_iterator& operator=(const rbtree_iterator& rbi) {
				this->_node = rbi._node;
				this->_comp = rbi._comp;
				return *this;
			}
			~rbtree_iterator() {

			}

			friend bool	operator==(const rbtree_iterator& lhs, const rbtree_iterator& rhs) {
				return lhs._node == rhs._node;
			}

			value_type	operator*() {
				if (this->_node == NULL)
					throw std::runtime_error("Cannot dereference NULL iterator");
				return this->_node->data;
			}
			rbtree_iterator&	operator++() {
				if (this->_node == NULL)
					throw std::runtime_error("Cannot increment NULL iterator");
				// increment
				return *this;
			}
			rbtree_iterator&	operator++(int) {
				if (this->_node == NULL)
					throw std::runtime_error("Cannot increment NULL iterator");
				ft::rbtree_iterator<value_type> temp = *this;
				// increment
				return temp;
			}
			rbtree_iterator&	operator--() {
				if (this->_node == NULL)
					throw std::runtime_error("Cannot decrement NULL iterator");
				// decrement
				return *this;
			}
			rbtree_iterator&	operator--(int) {
				if (this->_node == NULL)
					throw std::runtime_error("Cannot decrement NULL iterator");
				ft::rbtree_iterator<value_type> temp = *this;
				// decrement
				return temp;
			}
	};
	template<
		typename T
	>bool operator!=(const rbtree_iterator<T>& lhs, const rbtree_iterator<T>& rhs) {
		return !(lhs == rhs);
	}
}

#endif
