#ifndef FT_REVERSE_ITERATOR_H
# define FT_REVERSE_ITERATOR_H

# include <iterator>
# include <exception>
# include <stdexcept>
# include <iostream>

# include "iterator_traits.hpp"

namespace ft {
	template <
		class Iterator
	> class reverse_iterator {
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
			reverse_iterator(iterator_type it) {
				this->_itr = it;
			}
			template<
				class Iter
			> reverse_iterator(const reverse_iterator<Iter>& rev_it) {
				this->_itr = rev_it.base();
			}
			iterator_type	base() const {
				return this->_itr;
			}
			reference	operator*() const {
				iterator_type temp(this->_itr);
				--temp;
				return *(temp);
			}
			pointer	operator->() const {
				return &(operator*());
			}
			reference	operator[](const difference_type& n) const {
				iterator_type temp(this->_itr);
				temp--;
				return *(temp - n);
			}
			reverse_iterator	operator+(const difference_type& n) const {
				return this->_itr - n;
			}
			friend reverse_iterator	operator+(const difference_type& n, const reverse_iterator& it) {
				return it._itr - n;
			}
			reverse_iterator&	operator++() {
				this->_itr--;
				return *this;
			}
			reverse_iterator	operator++(int) {
				iterator_type temp(this->_itr);
				this->_itr--;
				return temp;
			}
			reverse_iterator&	operator+=(difference_type n) {
				this->_itr -= n;
				return *this;
			}
			reverse_iterator	operator-(difference_type n) const {
				return this->_itr + n;
			}
			friend reverse_iterator	operator-(const difference_type& n, const reverse_iterator& it) {
				return it._itr + n;
			}
			reverse_iterator&	operator--() {
				this->_itr++;
				return *this;
			}
			reverse_iterator	operator--(int) {
				iterator_type	temp(this->_itr);
				this->_itr++;
				return temp;
			}
			reverse_iterator&	operator-=(difference_type n) {
				this->_itr += n;
				return *this;
			}
			template <class Iter>
			bool operator== (const reverse_iterator<Iter>& rhs) const {
				return this->base() == rhs.base();
			};
			template <class Iter>
			bool operator!= (const reverse_iterator<Iter>& rhs) const {
				return !(*this == rhs);
			};
			template <class Iter>
			bool operator< (const reverse_iterator<Iter>& rhs) const {
				return this->base() > rhs.base();
			};
			template <class Iter>
			bool operator> (const reverse_iterator<Iter>& rhs) const {
				return rhs < *this;
			};
			template <class Iter>
			bool operator<= (const reverse_iterator<Iter>& rhs) const {
				return !(rhs < *this);
			};
			template <class Iter>
			bool operator>= (const reverse_iterator<Iter>& rhs) const {
				return !(*this < rhs);
			};
			template <class Iter>
			difference_type operator- (
				const reverse_iterator<Iter>& rhs
			) {
				return rhs.base() - this->base();
			};
	};

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it
	) {
		return rev_it.base() - n;
	};
};

#endif
