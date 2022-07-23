#ifndef FT_VECTOR_ITERATOR_H
# define FT_VECTOR_ITERATOR_H

# include <exception>
# include <iterator>
# include <stdexcept>
# include <iostream>

# include "iterator_traits.hpp"

namespace ft {
	template <typename T>
	class vector_iterator: std::iterator<std::random_access_iterator_tag, T> {
		public:
			typedef T																						value_type;
			typedef typename std::iterator<std::random_access_iterator_tag, value_type>::difference_type	difference_type;
			typedef typename std::iterator<std::random_access_iterator_tag, value_type>::pointer			pointer;
			typedef typename std::iterator<std::random_access_iterator_tag, value_type>::reference			reference;
			typedef typename std::iterator<std::random_access_iterator_tag, value_type>::iterator_category	iterator_category;

		protected:
			value_type	*_ptr;

		public:
			// Constructors
			vector_iterator() {
				this->_ptr = NULL;
			}

			vector_iterator(value_type *in): _ptr(in) {}

			vector_iterator(const vector_iterator& it): _ptr(it._ptr) {}

			operator vector_iterator<T const>() const {
				return vector_iterator<T const>(this->_ptr);
			}

			// Assignment Operator
			const vector_iterator& operator= (const vector_iterator& it) {
				this->_ptr = it._ptr;
				return *this;
			}

			// Destructor
			~vector_iterator() {}

			// Dereference Operators
			reference operator*() const {
				if (this->_ptr == NULL)
					throw std::runtime_error("Cannot dereference NULL Pointer");
				return *(this->_ptr);
			}

			pointer operator->() const {
				return &(operator*());
			}

			reference operator[](difference_type n) {
				if (this->_ptr == NULL)
					throw std::runtime_error("Cannot dereference NULL Pointer");
				return *(this->_ptr + n);
			}

			// Arithmetic Operators
			vector_iterator& operator++() {
				if (this->_ptr == NULL)
					throw std::runtime_error("Cannot increment NULL Pointer");
				this->_ptr++;
				return *this;
			}

			vector_iterator operator++(int) {
				vector_iterator temp(*this);
				++(*this);
				return temp;
			}

			vector_iterator& operator--() {
				if (this->_ptr == NULL)
					throw std::runtime_error("Cannot decrement NULL Pointer");
				this->_ptr--;
				return *this;
			}

			vector_iterator operator--(int) {
				vector_iterator temp(*this);
				--(*this);
				return temp;
			}

			vector_iterator& operator+=(const difference_type& n) {
				this->_ptr += n;
				return *this;
			}

			vector_iterator& operator-=(const difference_type& n) {
				this->_ptr -= n;
				return *this;
			}

			vector_iterator operator+(const difference_type& n) const {
				vector_iterator temp(*this);
				temp += n;
				return temp;
			}

			vector_iterator operator-(const difference_type& n) const {
				vector_iterator temp(*this);
				temp -= n;
				return temp;
			}

			template <typename Iter>
			difference_type operator-(const vector_iterator<Iter>& rhs) const {
				return (this->_ptr - rhs._ptr);
			}

			// Relational Operators
			template <typename Iter>
			bool operator==(const vector_iterator<Iter>& rhs) const {
				return (this->_ptr == rhs._ptr);
			}

			template <typename Iter>
			bool operator!=(const vector_iterator<Iter>& rhs) const {
				return !(*this == rhs);
			}

			template <typename Iter>
			bool operator<(const vector_iterator<Iter>& rhs) const {
				return (this->_ptr < rhs._ptr);
			}

			template <typename Iter>
			bool operator>(const vector_iterator<Iter>& rhs) const {
				return (rhs < *this);
			}

			template <typename Iter>
			bool operator<=(const vector_iterator<Iter>& rhs) const {
				return !(rhs < *this);
			}

			template <typename Iter>
			bool operator>=(const vector_iterator<Iter>& rhs) const {
				return !(*this < rhs);
			}
	};

	// External Arithmetic Operators
	template <typename T>
	ft::vector_iterator<T> operator-(const typename ft::vector_iterator<T>::difference_type& n, const ft::vector_iterator<T>& it) {
		ft::vector_iterator<T> temp(it);
		temp -= n;
		return temp;
	}

	template <typename T>
	ft::vector_iterator<T> operator+(const typename ft::vector_iterator<T>::difference_type& n, const ft::vector_iterator<T>& it) {
		ft::vector_iterator<T> temp(it);
		temp += n;
		return temp;
	}
}

#endif
