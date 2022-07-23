#ifndef FT_SET_H
# define FT_SET_H

# include <cstddef>
# include <iterator>
# include <memory>

# include "rbtree.hpp"
# include "rbtree_iterator.hpp"
# include "reverse_iterator.hpp"
# include "pairs.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"
# include "compare.hpp"

namespace ft {
	template <
		typename T,
		typename Compare = std::less<T>,
		typename Alloc = std::allocator<T>
	> class set {
		public:
			typedef T														key_type;
			typedef T														value_type;
			typedef Compare													key_compare;
			typedef Compare													value_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef const reference											const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef const pointer											const_pointer;
			typedef ft::rbtree_iterator<const value_type, value_compare>	iterator;
			typedef ft::rbtree_iterator<const value_type, value_compare>	const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef ptrdiff_t												difference_type;
			typedef size_t													size_type;

		protected:
			ft::RBTree<value_type, value_compare, allocator_type>	_tree;
			value_compare											_comp;
			allocator_type											_alloc;

		public:
			// Constructors
			set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
				this->_tree = ft::RBTree<value_type, value_compare, allocator_type>(comp, alloc);
				this->_comp = comp;
				this->_alloc = alloc;
			}

			template<typename InputIterator>
			set (
				InputIterator first,
				InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()
			) {
				this->_tree = ft::RBTree<value_type, value_compare, allocator_type>(comp, alloc);
				for (; first != last; first++) {
					this->_tree.insert(*first);
				}
				this->_comp = comp;
				this->_alloc = alloc;
			}

			set (const set& x) {
				*this = x;
			}

			// Assignment operator
			set& operator=(const set& x) {
				this->_tree = x._tree;
				this->_comp = x._comp;
				this->_alloc = x._alloc;
				return *this;
			}

			// Destructor
			~set() {}

			// Iterators
			iterator begin() {
				return iterator(this->_tree.begin());
			}

			const_iterator begin() const {
				return const_iterator(this->_tree.begin());
			}

			iterator end() {
				return iterator(this->_tree.end());
			}

			const_iterator end() const {
				return const_iterator(this->_tree.end());
			}

			reverse_iterator rbegin() {
				return reverse_iterator(this->_tree.end());
			}

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(this->_tree.end());
			}

			reverse_iterator rend() {
				return reverse_iterator(this->_tree.begin());
			}

			const_reverse_iterator rend() const {
				return const_reverse_iterator(this->_tree.begin());
			}

			// Capacity
			bool empty() const {
				return this->size() == 0;
			}

			size_type size() const {
				return this->_tree.size();
			}

			size_type max_size() const {
				return this->_tree.max_size();
			}

			// Modifiers
			ft::pair<iterator,bool> insert(const value_type& val) {
				try {
					this->_tree.insert(val);
				} catch (const std::exception& e) {
					return ft::make_pair<iterator,bool>(this->find(val), false);
				}
				return ft::make_pair<iterator,bool>(this->find(val), true);
			}

			iterator insert(iterator position, const value_type& val) {
				(void)position;
				try {
					this->_tree.insert(val);
				} catch (const std::exception& e) {
					// Just ignore the error
				}
				return this->find(val);
			}

			template<typename InputIterator>
			void insert(
				InputIterator	first,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last
			) {
				for (; first != last; first++) {
					this->insert(*first);
				}
			}

			void erase(iterator position) {
				try {
					this->_tree.remove(*position);
				} catch (const std::exception& e) {
					// Ignore
				}
			}

			size_type erase(const value_type& val) {
				try {
					this->_tree.remove(val);
				} catch (const std::exception& e) {
					return 0;
				}
				return 1;
			}

			void erase(iterator first, iterator last) {
				set<value_type, value_compare, allocator_type> temp(*this);
				for (; first != last; first++) {
					try {
						temp._tree.remove(*first);
					} catch (const std::exception& e) {
						// Ignore
					}
				}
				*this = temp;
			}

			void swap(set& x) {
				this->_tree.swap(x._tree);
			}

			void clear() {
				this->erase(this->begin(), this->end());
			}

			// Observers
			key_compare key_comp() const {
				return this->_comp;
			}

			value_compare value_comp() const {
				return this->_comp;
			}

			// Operations
			iterator find(const value_type& val) const {
				return iterator(this->_tree.find(val));
			}

			size_type count(const value_type& val) const {
				if (this->_tree.find(val) == this->_tree.end())
					return 0;
				return 1;
			}

			iterator lower_bound(const value_type& val) {
				iterator it = this->begin();
				iterator end = this->end();
				for (; it != end; it++) {
					if (this->_comp(*it, val) == false)
						break;
				}
				return it;
			}

			const_iterator lower_bound(const value_type& val) const {
				const_iterator it = this->begin();
				const_iterator end = this->end();
				for (; it != end; it++) {
					if (this->_comp(*it, val) == false)
						break;
				}
				return it;
			}

			iterator upper_bound(const value_type& val) {
				iterator it = this->begin();
				iterator end = this->end();
				for (; it != end; it++) {
					if (this->_comp(val, *it) == true)
						break;
				}
				return it;
			}

			const_iterator upper_bound(const value_type& val) const {
				const_iterator it = this->begin();
				const_iterator end = this->end();
				for (; it != end; it++) {
					if (this->_comp(val, *it) == true)
						break;
				}
				return it;
			}

			ft::pair<iterator, iterator> equal_range(const value_type& val) {
				return ft::make_pair(this->lower_bound(val), this->upper_bound(val));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const value_type& val) const {
				return ft::make_pair(this->lower_bound(val), this->upper_bound(val));
			}

			// Allocator
			allocator_type get_allocator() const {
				return this->_alloc;
			}

			bool operator==(const set& rhs) const {
				if (this->size() != rhs.size())
					return false;
				return ft::equal(this->begin(), this->end(), rhs.begin());
			}

			bool operator!=(const set& rhs) const {
				return !(*this == rhs);
			}

			bool operator< (const set& rhs) const {
				return ft::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end(), this->_comp);
			}

			bool operator> (const set& rhs) const {
				return rhs < *this;
			}

			bool operator<=(const set& rhs) const {
					return !(rhs < *this);
			}

			bool operator>=(const set& rhs) const {
				return !(*this < rhs);
			}
	};
}

#endif
