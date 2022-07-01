#ifndef FT_SET_ITERATOR_H
# define FT_SET_ITERATOR_H

# include <iterator>

namespace ft {
	template<
		typename T
	>class rbtree_iterator: std::iterator<T, std::bidirectional_iterator_tag> {
		public:
			typedef T	value_type;

			rbtree_iterator() {}
			rbtree_iterator(const rbtree_iterator& rbi);
			rbtree_iterator& operator=(const rbtree_iterator& rbi) {
				(void)rbi;
				return *this;
			}
			~rbtree_iterator() {}

			friend bool	operator==(const rbtree_iterator& lhs, const rbtree_iterator& rhs) {
				return false;
			}


			value_type	operator*(const rbtree_iterator& rbi);
			rbtree_iterator&	operator++();
			rbtree_iterator&	operator++(int);
			rbtree_iterator&	operator--();
			rbtree_iterator&	operator--(int);
	};
	template<
		typename T
	>bool operator!=(const rbtree_iterator<T>& lhs, const rbtree_iterator<T>& rhs) {
		return !(lhs == rhs);
	}
}

#endif
