#ifndef FT_MAP_H
# define FT_MAP_H

#include <__functional_base>
# include <cstddef>
# include <memory>

# include "pairs.hpp"
# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"

namespace ft {
	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Alloc = std::allocator<ft::pair<const Key, T> >
	> class map {
		public:
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef pair<const key_type, mapped_type>						value_type;
		private:
			class value_compare : std::binary_function<value_type, value_type, bool> {
				protected:
					Compare	comp;
					value_compare	(Compare c) : comp(c) {}
				public:
					typedef bool				result_type;
					typedef value_type			first_argument_type;
					typedef	value_type			second_arument_type;
					result_type operator() (const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					}
			};
		public:
			typedef Compare													key_compare;
			typedef value_compare											value_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef ft::rbtree_iterator<value_type>							iterator;
			typedef const iterator											const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef const reverse_iterator									const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t													size_type;

		// Constructors
										map (
											const key_compare& comp = key_compare(),
											const allocator_type& alloc = allocator_type()
										);
										template <
											class InputIterator
										> map (
											InputIterator first,
											InputIterator last,
											const key_compare& comp = key_compare(),
											const allocator_type& alloc = allocator_type()
										);
										map (const map& x);
		// Destructor
										~map();
		// Assignment operator
			map&						operator= (const map&x);
		// Iterators
			iterator					begin();
			const_iterator				begin() const;
			iterator					end();
			const_iterator				end() const;
			reverse_iterator			rbegin();
			const_reverse_iterator		rbegin() const;
			reverse_iterator			rend();
			const_reverse_iterator		rend() const;
		// Capacity
			bool						empty() const;
			size_type					size() const;
			size_type					max_size() const;
		// Element Access
			mapped_type&				operator[] (const key_type& k);
		// Modifiers
			pair<iterator, bool>		insert(const value_type& val);
			iterator					insert(
											iterator position,
											const value_type& val
										);
			template<
				class InputIterator
			> void						insert(
											InputIterator first,
											InputIterator last
										);
			void						erase(iterator position);
			size_type					erase(const key_type& k);
			void						erase(iterator first, iterator last);
			void						swap(map& x);
			void						clear();
		// Observers
			key_compare					key_comp() const;
			value_compare				value_comp() const;
		// Operations
			iterator					find(const key_type& k);
			const_iterator				find(const key_type& k) const;
			size_type					count(const key_type& k) const;
			iterator					lower_bound(const key_type& k);
			const_iterator				lower_bound(const key_type& k) const;
			iterator					upper_bound(const key_type& k);
			const_iterator				upper_bound(const key_type& k) const;
			pair<iterator, iterator>	equal_range(const key_type& k);
			pair<
				const_iterator,
				const_iterator
			>							equal_range(const key_type& k) const;
		// Allocator
			allocator_type				get_allocator() const;
	};
}

#endif
