#ifndef FT_ITERATOR_H
# define FT_ITERATOR_H

# include <iterator>
# include <exception>

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
		protected:
			value_type *_ptr;
		public:
			iterator() {
				_ptr = NULL;
			}
			iterator(value_type *in) {
				_ptr = in;
			}
			iterator(const iterator& it) {
				*this = it;
			}
			const iterator& operator=(const iterator& it) {
				this->_ptr = it._ptr;
				return *this;
			}
			const value_type&	operator*() const {
				if (_ptr == NULL)
					throw std::runtime_error("Cannot dereference NULL Pointer");
				return *_ptr;
			}
			iterator	operator++() {
				if (_ptr == NULL)
					throw std::runtime_error("Cannot dereference NULL Pointer");
				_ptr++;
				return *this;
			}
			iterator	operator++(int) {
				if (_ptr == NULL)
					throw std::runtime_error("Cannot dereference NULL Pointer");
				ft::iterator<T> temp = *this;
				_ptr++;
				return temp;
			}
	};
};

#endif