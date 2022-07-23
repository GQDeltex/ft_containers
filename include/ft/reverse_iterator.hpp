#ifndef FT_REVERSE_ITERATOR_H
# define FT_REVERSE_ITERATOR_H

# include <iterator>
# include <exception>
# include <stdexcept>
# include <iostream>

# include "iterator_traits.hpp"

namespace ft {
	template <typename Iterator>
	class reverse_iterator {
		public:
			typedef Iterator														iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;
			typedef	typename ft::iterator_traits<iterator_type>::value_type			value_type;
			typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
			typedef	typename ft::iterator_traits<iterator_type>::pointer			pointer;
			typedef typename ft::iterator_traits<iterator_type>::reference			reference;

		protected:
			iterator_type	_itr;

		public:
			// Constructors
			reverse_iterator() {
				this->_itr = iterator_type();
			}

			reverse_iterator(iterator_type it): _itr(it) {}

			template <typename Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it): _itr(rev_it.base()) {}

			// Assignment Operator
			const reverse_iterator& operator= (const reverse_iterator& rev_it) {
				this->_itr = rev_it._itr;
				return *this;
			}

			// Destructor
			~reverse_iterator() {}

			// Base
			iterator_type base() const {
				return this->_itr;
			}

			// Dereference Operators
			reference operator*() const {
				iterator_type temp(this->_itr);
				--temp;
				return *(temp);
			}

			pointer operator->() const {
				return &(operator*());
			}

			reference operator[](const difference_type& n) const {
				iterator_type temp(this->_itr);
				temp--;
				return *(temp - n);
			}

			// Arithmetic Operators
			reverse_iterator& operator++() {
				this->_itr--;
				return *this;
			}

			reverse_iterator operator++(int) {
				iterator_type temp(this->_itr);
				++(*this);
				return temp;
			}

			reverse_iterator& operator--() {
				this->_itr++;
				return *this;
			}

			reverse_iterator operator--(int) {
				iterator_type	temp(this->_itr);
				--(*this);
				return temp;
			}

			reverse_iterator& operator+=(difference_type n) {
				this->_itr -= n;
				return *this;
			}

			reverse_iterator& operator-=(difference_type n) {
				this->_itr += n;
				return *this;
			}

			reverse_iterator operator+(const difference_type& n) const {
				return this->_itr - n;
			}

			reverse_iterator operator-(difference_type n) const {
				return this->_itr + n;
			}

			template <typename Iter>
			difference_type operator-(const reverse_iterator<Iter>& rhs) {
				return rhs.base() - this->base();
			}

			// Relational Operators
			template <typename Iter>
			bool operator==(const reverse_iterator<Iter>& rhs) const {
				return this->base() == rhs.base();
			}

			template <typename Iter>
			bool operator!=(const reverse_iterator<Iter>& rhs) const {
				return !(*this == rhs);
			}

			template <typename Iter>
			bool operator<(const reverse_iterator<Iter>& rhs) const {
				return this->base() > rhs.base();
			}

			template <typename Iter>
			bool operator>(const reverse_iterator<Iter>& rhs) const {
				return rhs < *this;
			}

			template <typename Iter>
			bool operator<=(const reverse_iterator<Iter>& rhs) const {
				return !(rhs < *this);
			}

			template <typename Iter>
			bool operator>=(const reverse_iterator<Iter>& rhs) const {
				return !(*this < rhs);
			}
	};

	// External Arithmetic Operators
	template <typename Iterator>
	ft::reverse_iterator<Iterator> operator+(const typename ft::reverse_iterator<Iterator>::difference_type& n, const ft::reverse_iterator<Iterator>& it) {
		return it.base() - n;
	}

	template <typename Iterator>
	ft::reverse_iterator<Iterator> operator-(const typename ft::reverse_iterator<Iterator>::difference_type& n, const ft::reverse_iterator<Iterator>& it) {
		return it.base() + n;
	}

}

#endif
