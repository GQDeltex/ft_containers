#ifndef FT_REVERSE_ITERATOR_H
# define FT_REVERSE_ITERATOR_H

# include <iterator>
# include <exception>

namespace ft {
	template <
		class T
	> class reverse_iterator : std::iterator<std::random_access_iterator_tag, T> {
		public:
			typedef typename std::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::reference			reference;
		protected:
			value_type	*_ptr;
		public:
								reverse_iterator() {
									_ptr = NULL;
								}
								reverse_iterator(value_type *in) {
									_ptr = in;
								}
								reverse_iterator(const reverse_iterator& it) {
									*this = it;
								}
			const reverse_iterator&		operator=(const reverse_iterator& it) {
									this->_ptr = it._ptr;
									return *this;
								}
			const value_type&	operator*() const {
									if (_ptr == NULL)
										throw std::runtime_error("Cannot dereference NULL Pointer");
									return *_ptr;
								}
			reverse_iterator			operator++() {
									if (_ptr == NULL)
										throw std::runtime_error("Cannot increment NULL Pointer");
									_ptr--;
									return *this;
								}
			reverse_iterator			operator++(int) {
									if (_ptr == NULL)
										throw std::runtime_error("Cannot increment NULL Pointer");
									ft::reverse_iterator<T> temp = *this;
									_ptr--;
									return temp;
								}
			reverse_iterator			operator--() {
									if (_ptr == NULL)
										throw std::runtime_error("Cannot decrement NULL Pointer");
									_ptr++;
									return *this;
								}
			reverse_iterator			operator--(int) {
									if (_ptr == NULL)
										throw std::runtime_error("Cannot decrement NULL Pointer");
									ft::reverse_iterator<T> temp = *this;
									_ptr++;
									return temp;
								}
			value_type			operator[](difference_type n) {
									if (_ptr == NULL)
										throw std::runtime_error("Cannot dereference NULL Pointer");
									return *(this->_ptr - n);
								}
			reverse_iterator			operator+=(int n) {
									this->_ptr -= n;
									return *this;
								}
			reverse_iterator			operator-=(int n) {
									this->_ptr += n;
									return *this;
								}
			friend reverse_iterator		operator+(const reverse_iterator<T>&it, const int&n) {
									reverse_iterator temp(it);
									temp._ptr -= n;
									return temp;
								}
			friend reverse_iterator		operator+(const int&n, const reverse_iterator<T>&it) {
									reverse_iterator temp(it);
									temp._ptr -= n;
									return temp;
								}
			friend reverse_iterator		operator-(const reverse_iterator<T>&it, const int&n) {
									reverse_iterator temp(it);
									temp._ptr += n;
									return temp;
								}
			friend reverse_iterator		operator-(const int&n, const reverse_iterator<T>&it) {
									reverse_iterator temp(it);
									temp._ptr += n;
									return temp;
								}
			friend int			operator-(const reverse_iterator<T>&lhs, const reverse_iterator<T>&rhs) {
									return rhs._ptr - lhs._ptr;
								}
			friend bool			operator==(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) {
									return (lhs._ptr == rhs._ptr);
								}
			friend bool			operator!=(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) {
									return !(lhs == rhs);
								}
			friend bool			operator<(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) {
									return (lhs._ptr < rhs._ptr);
								}
			friend bool			operator>(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) {
									return (rhs < lhs);
								}
			friend bool			operator<=(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) {
									return !(rhs < lhs);
								}
			friend bool			operator>=(const reverse_iterator<T>& lhs, const reverse_iterator<T>& rhs) {
									return !(lhs < rhs);
								}
	};
};

#endif
