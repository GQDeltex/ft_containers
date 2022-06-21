#ifndef FT_SET_H
# define FT_SET_H
# include <cstddef>
# include <iterator>
# include <memory>

# include "iterator.hpp"
# include "pairs.hpp"

namespace ft {
	template <
		class T,
		class Compare = std::less<T>,
		class Alloc = std::allocator<T>
	> class set {
		public:
			typedef T									key_type;
			typedef T									value_type;
			typedef Compare								key_compare;
			typedef Compare								value_compare;
			typedef Alloc								allocator_type;
			typedef typename allocator_type::reference	reference;
			typedef const reference						const_reference;
			typedef typename allocator_type::pointer	pointer;
			typedef const pointer						const_pointer;
			typedef ft::iterator<T>						iterator;
			typedef const iterator						const_iterator;
			typedef std::reverse_iterator<iterator>		reverse_iterator;
			typedef	const reverse_iterator				const_reverse_iterator;
			typedef ptrdiff_t							difference_type;
			typedef size_t								size_type;

		// Constructors
									set (
										const key_compare& comp = key_compare(),
										const allocator_type& alloc = allocator_type()
									);
									template<
										class InputIterator
									> set (
										InputIterator first,
										InputIterator last,
										const key_compare& comp = key_compare(),
										const allocator_type& alloc = allocator_type()
									);
									set (const set& x);
		// Destructor
									~set();
		// Assignment operator
			set&					operator=(const set& x);
		// Iterators
			iterator				begin();
			const_iterator			begin();
			iterator				end();
			const_iterator			end();
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin();
			reverse_iterator		rend();
			const_reverse_iterator	rend();
		// Capacity
			bool					empty() const;
			size_type				size() const;
			size_type				max_size() const;
		// Modifiers
			ft::pair<iterator,bool>	insert(const value_type& val);
			iterator				insert(
										iterator position,
										const value_type& val
									);
			template<
			class InputIterator
			> void					insert(
										InputIterator	first,
										InputIterator	last
									);
			void					erase(iterator position);
			size_type				erase(const value_type& val);
			void					erase(iterator first, iterator last);
			void					swap(set& x);
			void					clear();
		// Observers
			key_compare				key_comp() const;
			value_compare			value_comp() const;
		// Operations
			iterator				find(const value_type& val) const;
			size_type				count(const value_type& val) const;
			iterator				lower_bound(const value_type& val) const;
			iterator				upper_bound(const value_type& val) const;
			ft::pair<
				iterator,
				iterator
			>						equal_range(const value_type& val) const;
		// Allocator
			allocator_type			get_allocator() const;
	};
}

#endif
