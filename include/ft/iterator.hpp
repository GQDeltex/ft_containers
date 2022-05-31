#ifndef FT_ITERATOR_H
# define FT_ITERATOR_H

#include <iterator>

namespace ft {
	template <
		class T
	> class iterator : std::iterator<std::random_access_iterator_tag, T> {
		public:
			typedef typename std::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::reference			reference;
		private:
			value_type *_ptr;
		public:
			iterator() {
				_ptr = NULL;
			}
			iterator(value_type *in) {
				_ptr = in;
			}
			const value_type&	operator*() const {
				return *_ptr;
			}
			iterator	operator++() {
				_ptr++;
				return *this;
			}
			iterator	operator++(int) {
				ft::iterator<T> temp = *this;
				_ptr++;
				return temp;
			}
	};
};

#endif
