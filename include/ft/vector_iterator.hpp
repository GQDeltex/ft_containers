#ifndef FT_VECTOR_ITERATOR_H
# define FT_VECTOR_ITERATOR_H

# include <exception>
#include <iterator>
# include <stdexcept>

# include "iterator_traits.hpp"

namespace ft {
	template <
		class T
	> class vector_iterator: std::iterator<std::random_access_iterator_tag, T> {
		private:
			typedef typename std::iterator<std::random_access_iterator_tag, T>	stditr;
		public:
			typedef T									value_type;
			typedef typename stditr::difference_type	difference_type;
			typedef typename stditr::pointer			pointer;
			typedef typename stditr::reference			reference;
			typedef typename stditr::iterator_category	iterator_category;
		protected:
			value_type	*_ptr;
		public:
								vector_iterator() {
									_ptr = NULL;
								}
								vector_iterator(value_type *in) {
									_ptr = in;
								}
								vector_iterator(const vector_iterator& it) {
									*this = it;
								}
			const vector_iterator&		operator=(const vector_iterator& it) {
									this->_ptr = it._ptr;
									return *this;
								}
			value_type&	operator*() const {
									if (_ptr == NULL)
										throw std::runtime_error("Cannot dereference NULL Pointer");
									return *_ptr;
								}
			vector_iterator			operator++() {
									if (_ptr == NULL)
										throw std::runtime_error("Cannot increment NULL Pointer");
									_ptr++;
									return *this;
								}
			vector_iterator			operator++(int) {
									if (_ptr == NULL)
										throw std::runtime_error("Cannot increment NULL Pointer");
									ft::vector_iterator<T> temp = *this;
									_ptr++;
									return temp;
								}
			vector_iterator			operator--() {
									if (_ptr == NULL)
										throw std::runtime_error("Cannot decrement NULL Pointer");
									_ptr--;
									return *this;
								}
			vector_iterator			operator--(int) {
									if (_ptr == NULL)
										throw std::runtime_error("Cannot decrement NULL Pointer");
									ft::vector_iterator<T> temp = *this;
									_ptr--;
									return temp;
								}
			value_type			operator[](difference_type n) {
									if (_ptr == NULL)
										throw std::runtime_error("Cannot dereference NULL Pointer");
									return *(_ptr + n);
								}
			vector_iterator			operator+=(int n) {
									this->_ptr += n;
									return *this;
								}
			vector_iterator			operator-=(int n) {
									this->_ptr -= n;
									return *this;
								}
			vector_iterator			operator+(const int&n) {
									vector_iterator temp(*this);
									temp._ptr += n;
									return temp;
								}
			friend vector_iterator		operator+(const int&n, const vector_iterator<T>&it) {
									vector_iterator temp(it);
									temp._ptr += n;
									return temp;
								}
			vector_iterator			operator-(const int&n) {
									vector_iterator temp(*this);
									temp._ptr -= n;
									return temp;
								}
			friend vector_iterator		operator-(const int&n, const vector_iterator<T>&it) {
									vector_iterator temp(it);
									temp._ptr -= n;
									return temp;
								}
			friend int			operator-(const vector_iterator<T>&lhs, const vector_iterator<T>&rhs) {
									return lhs._ptr - rhs._ptr;
								}
			friend bool			operator==(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
									return (lhs._ptr == rhs._ptr);
								}
			friend bool			operator!=(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
									return !(lhs == rhs);
								}
			friend bool			operator<(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
									return (lhs._ptr < rhs._ptr);
								}
			friend bool			operator>(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
									return (rhs < lhs);
								}
			friend bool			operator<=(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
									return !(rhs < lhs);
								}
			friend bool			operator>=(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
									return !(lhs < rhs);
								}
	};
};

#endif
