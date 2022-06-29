#ifndef FT_SET_H
# define FT_SET_H
# include <cstddef>
# include <iterator>
# include <memory>

# include "rbtree.hpp"
# include "rbtree_iterator.hpp"
# include "pairs.hpp"

namespace ft {
	template <
		class T,
		class Compare = std::less<T>,
		class Alloc = std::allocator<T>
	> class set {
		public:
			typedef T										key_type;
			typedef T										value_type;
			typedef Compare									key_compare;
			typedef Compare									value_compare;
			typedef Alloc									allocator_type;
			typedef typename allocator_type::reference		reference;
			typedef const reference							const_reference;
			typedef typename allocator_type::pointer		pointer;
			typedef const pointer							const_pointer;
			typedef ft::rbtree_iterator<value_type>			iterator;
			typedef ft::rbtree_iterator<const value_type>	const_iterator;
			typedef std::reverse_iterator<iterator>			reverse_iterator;
			typedef	const reverse_iterator					const_reverse_iterator;
			typedef ptrdiff_t								difference_type;
			typedef size_t									size_type;

		protected:
			ft::RBTree<value_type, value_compare>	tree;

		public:
		// Constructors
									set (
										const key_compare& comp = key_compare(),
										const allocator_type& alloc = allocator_type()
										) {
										this->tree = ft::RBTree<value_type, value_compare>(comp, alloc);
									}
									template<
										class InputIterator
									> set (
										InputIterator first,
										InputIterator last,
										const key_compare& comp = key_compare(),
										const allocator_type& alloc = allocator_type()
										) {
										this->tree = ft::RBTree<value_type, value_compare>(comp, alloc);
										for (;first != last;first++) {
											this->tree.insert(*first);
										}
									}
									set (const set& x) {
										*this = x;
									}
		// Destructor
									~set() {}
		// Assignment operator
									set&					operator=(const set& x) {
										this->tree = x.tree;
										return *this;
									}
		// Iterators
			iterator				begin();
			const_iterator			begin() const;
			iterator				end();
			const_iterator			end() const;
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin() const;
			reverse_iterator		rend();
			const_reverse_iterator	rend() const;
		// Capacity
			bool					empty() const {
				return this->size() == 0;
			}
			size_type				size() const {
				return this->tree.size();
			}
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
