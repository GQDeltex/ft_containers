#ifndef FT_REVERSE_ITERATOR_H
# define FT_REVERSE_ITERATOR_H

# include <iterator>
# include <exception>
# include <stdexcept>

namespace ft {
	template <
		class Iterator
	> class reverse_iterator {
		public:
			typedef Iterator	iterator_type;
			typedef ft::iterator_traits<iterator_type>::iterator_category	category;
			typedef	ft::iterator_traits<iterator_type>::value_type			value_type;
			typedef ft::iterator_traits<iterator_type>::difference_type		difference_type;
			typedef	ft::iterator_traits<iterator_type>::pointer				pointer;
			typedef ft::iterator_traits<iterator_type>::reference			reference;
		// Constructors
			reverse_iterator();
			reverse_iterator(iterator_type it);
			template<
				class Iter
			> reverse_iterator(const reverse_iterator<Iter>& rev_it);
			iterator_type	base() const;
			reference	operator*() const;
			reverse_iterator	operator+(difference_type n) const;
			reverse_iterator&	operator++();
			reverse_iterator	operator++(int);
			reverse_iterator&	operator+=(difference_type n);
			reverse_iterator	operator-(difference_type n) const;
			reverse_iterator&	operator--();
			reverse_iterator	operator--(int);
			reverse_iterator&	operator-=(difference_type n);
			pointer	operator->() const;
			reference	operator[](difference_type n) const;

	};
	template <class Iterator>
	  bool operator== (const reverse_iterator<Iterator>& lhs,
					   const reverse_iterator<Iterator>& rhs);

	template <class Iterator>
	  bool operator!= (const reverse_iterator<Iterator>& lhs,
					   const reverse_iterator<Iterator>& rhs);


	template <class Iterator>
	  bool operator<  (const reverse_iterator<Iterator>& lhs,
					   const reverse_iterator<Iterator>& rhs);


	template <class Iterator>
	  bool operator<= (const reverse_iterator<Iterator>& lhs,
					   const reverse_iterator<Iterator>& rhs);


	template <class Iterator>
	  bool operator>  (const reverse_iterator<Iterator>& lhs,
					   const reverse_iterator<Iterator>& rhs);


	template <class Iterator>
	  bool operator>= (const reverse_iterator<Iterator>& lhs,
					   const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	  reverse_iterator<Iterator> operator+ (
				 typename reverse_iterator<Iterator>::difference_type n,
				 const reverse_iterator<Iterator>& rev_it);
	template <class Iterator>
	  typename reverse_iterator<Iterator>::difference_type operator- (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs);
};

#endif
