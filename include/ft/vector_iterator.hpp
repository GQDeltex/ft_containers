#ifndef FT_VECTOR_ITERATOR_H
# define FT_VECTOR_ITERATOR_H

# include <exception>
# include <iterator>
# include <stdexcept>
# include <iostream>

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
										this->_ptr = NULL;
									}
									vector_iterator(value_type *in) {
										this->_ptr = in;
									}
									vector_iterator(const vector_iterator& it) {
										*this = it;
									}
									operator vector_iterator<T const>() const {
										return vector_iterator<T const>(this->_ptr);
									}
			const vector_iterator&	operator=(const vector_iterator& it) {
										this->_ptr = it._ptr;
										return *this;
									}
			reference				operator*() const {
										if (this->_ptr == NULL)
											throw std::runtime_error("Cannot dereference NULL Pointer");
										return *(this->_ptr);
									}
			pointer					operator->() const {
										return &(operator*());
									}
			vector_iterator&		operator++() {
										if (this->_ptr == NULL)
											throw std::runtime_error("Cannot increment NULL Pointer");
										this->_ptr++;
										return *this;
									}
			vector_iterator			operator++(int) {
										if (this->_ptr == NULL)
											throw std::runtime_error("Cannot increment NULL Pointer");
										vector_iterator temp = *this;
										this->_ptr++;
										return temp;
									}
			vector_iterator&		operator--() {
										if (this->_ptr == NULL)
											throw std::runtime_error("Cannot decrement NULL Pointer");
										this->_ptr--;
										return *this;
									}
			vector_iterator			operator--(int) {
										if (this->_ptr == NULL)
											throw std::runtime_error("Cannot decrement NULL Pointer");
										vector_iterator temp = *this;
										this->_ptr--;
										return temp;
									}
			reference				operator[](difference_type n) {
										if (this->_ptr == NULL)
											throw std::runtime_error("Cannot dereference NULL Pointer");
										return *(this->_ptr + n);
									}
			vector_iterator&		operator+=(const difference_type& n) {
										this->_ptr += n;
										return *this;
									}
			vector_iterator&		operator-=(const difference_type& n) {
										this->_ptr -= n;
										return *this;
									}
			vector_iterator			operator+(const difference_type& n) const {
										vector_iterator temp(*this);
										temp += n;
										return temp;
									}
			friend vector_iterator	operator+(const difference_type& n, const vector_iterator& it) {
										vector_iterator temp(it);
										temp += n;
										return temp;
									}
			vector_iterator			operator-(const difference_type& n) const {
										vector_iterator temp(*this);
										temp -= n;
										return temp;
									}
			friend vector_iterator	operator-(const difference_type& n, const vector_iterator<T>& it) {
										vector_iterator temp(it);
										temp -= n;
										return temp;
									}
			friend difference_type	operator-(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
										return lhs._ptr - rhs._ptr;
									}
			friend bool				operator==(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
										return (lhs._ptr == rhs._ptr);
									}
			friend bool				operator!=(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
										return !(lhs == rhs);
									}
			friend bool				operator<(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
										return (lhs._ptr < rhs._ptr);
									}
			friend bool				operator>(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
										return (rhs < lhs);
									}
			friend bool				operator<=(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
										return !(rhs < lhs);
									}
			friend bool				operator>=(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs) {
										return !(lhs < rhs);
									}
	};
};

#endif
