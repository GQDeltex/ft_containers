#ifndef FT_MAP_H
# define FT_MAP_H

# include <cstddef>
# include <memory>

# include "pairs.hpp"
# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"
# include "rbtree_iterator.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"

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
			typedef ft::pair<const key_type, mapped_type>					value_type;
			typedef Compare													key_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef size_t													size_type;

		private:
			class value_compare : std::binary_function<value_type, value_type, bool> {
				friend class map;
				protected:
					key_compare	comp;
					// Constructor
					value_compare(key_compare c): comp(c) {}
				public:
					value_compare(): comp(key_compare()) {}
					typedef bool				result_type;
					typedef value_type			first_argument_type;
					typedef	value_type			second_argument_type;
					result_type operator() (const first_argument_type& x, const second_argument_type& y) const {
						return comp(x.first, y.first);
					}
			};

		public:
			typedef ft::rbtree_iterator<value_type, value_compare>			iterator;
			typedef ft::rbtree_iterator<const value_type, value_compare>	const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;

		protected:
			ft::RBTree<value_type, value_compare, allocator_type>	_tree;
			key_compare								_comp_key;
			value_compare							_comp_val;
			allocator_type							_alloc;

		public:
		// Constructors
										map (
											const key_compare& comp = key_compare(),
											const allocator_type& alloc = allocator_type()
										) {
											this->_comp_key = comp;
											this->_comp_val = value_compare(this->_comp_key);
											this->_alloc = alloc;
											this->_tree = ft::RBTree<value_type, value_compare, allocator_type>(this->_comp_val, this->_alloc);
										}
										template <
											class InputIterator
										> map (
											InputIterator first,
											InputIterator last,
											const key_compare& comp = key_compare(),
											const allocator_type& alloc = allocator_type()
										) {
											this->_comp_key = comp;
											this->_comp_val = value_compare(this->_comp_key);
											this->_alloc = alloc;
											this->_tree = ft::RBTree<value_type, value_compare, allocator_type>(this->_comp_val, this->_alloc);
											for(; first != last; first++) {
												this->_tree.insert(*first);
											}
										}
										map (const map& x) {
											*this = x;
										}
		// Destructor
										~map() {}
		// Assignment operator
			map&						operator= (const map&x) {
											this->_comp_key = x._comp_key;
											this->_comp_val = x._comp_val;
											this->_alloc = x._alloc;
											this->_tree = x._tree;
											return *this;
										}
		// Iterators
			iterator					begin() {
											return iterator(this->_tree.begin());
										}
			const_iterator				begin() const {
											return const_iterator(this->_tree.begin());
										}
			iterator					end() {
											return iterator(this->_tree.end());
										}
			const_iterator				end() const {
											return const_iterator(this->_tree.end());
										}
			reverse_iterator			rbegin() {
											return reverse_iterator(this->_tree.end());
										}
			const_reverse_iterator		rbegin() const {
											return const_reverse_iterator(this->_tree.end());
										}
			reverse_iterator			rend() {
											return reverse_iterator(this->_tree.begin());
										}
			const_reverse_iterator		rend() const {
											return const_reverse_iterator(this->_tree.begin());
										}
		// Capacity
			bool						empty() const {
											return this->size() == 0;
										}
			size_type					size() const {
											return this->_tree.size();
										}
			size_type					max_size() const {
											return this->_tree.max_size();
										}
		// Element Access
			mapped_type&				operator[] (const key_type& k) {
											try {
												this->_tree.insert(ft::make_pair(k, mapped_type()));
											} catch (const std::exception& e) {
												//Ignore
											}
											return this->_tree.find(ft::make_pair(k, mapped_type()));
										}
		// Modifiers
			ft::pair<iterator, bool>	insert(const value_type& val) {
											try {
												this->_tree.insert(ft::pair<const key_type, mapped_type>(val.first, val.second));
											} catch(const std::exception& e) {
												return ft::pair<iterator,bool>(this->find(val.first), false);
											}
											return ft::pair<iterator,bool>(this->find(val.first), true);
										}
			iterator					insert(
											iterator position,
											const value_type& val
										) {
											(void)position;
											try {
												this->_tree.insert(val);
											} catch (const std::exception& e) {
												//Ignore
											}
											return this->find(val.first);
										}
			template<
				class InputIterator
			> void						insert(
											InputIterator first,
											typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last
										) {
											for(;first!=last;first++) {
												this->insert(*first);
											}
										}
			void						erase(iterator position) {
											try {
												this->_tree.remove(*position);
											} catch (const std::exception& e) {
												//Ignore
											}
										}
			size_type					erase(const key_type& k) {
											try {
												this->_tree.remove(ft::make_pair(k, mapped_type()));
											} catch (const std::exception& e) {
												return 0;
											}
											return 1;
										}
			void						erase(iterator first, iterator last) {
											map temp(*this);
											for(;first!=last;first++) {
												try {
													temp._tree.remove(*first);
												} catch (const std::exception& e) {
													// Ignore
												}
											}
											*this = temp;
										}
			void						swap(map& x) {
											this->_tree.swap(x._tree);
										}
			void						clear() {
											this->erase(this->begin(), this->end());
										}
		// Observers
			key_compare					key_comp() const {
											return this->_comp_key;
										}
			value_compare				value_comp() const {
											return this->_comp_val;
										}
		// Operations
			iterator					find(const key_type& k) {
											return iterator(this->_tree.find(ft::pair<const key_type, mapped_type>(k, mapped_type())));
										}
			const_iterator				find(const key_type& k) const {
											return iterator(this->_tree.find(ft::pair<const key_type, mapped_type>(k, mapped_type())));
										}
			size_type					count(const key_type& k) const {
											if (this->_tree.find(this->find(k)) == this->_tree.end())
												return 0;
											return 1;
										}
			iterator					lower_bound(const key_type& k) {
											const_iterator it = this->begin();
											const_iterator end = this->end();
											for(;it!=end;it++) {
												if (this->_comp(*it, ft::make_pair(k, mapped_type())) == false)
													break;
											}
											return it;
										}
			const_iterator				lower_bound(const key_type& k) const {
											const_iterator it = this->begin();
											const_iterator end = this->end();
											for(;it!=end;it++) {
												if (this->_comp(*it, ft::make_pair(k, mapped_type())) == false)
													break;
											}
											return it;
										}
			iterator					upper_bound(const key_type& k) {
											const_iterator it = this->begin();
											const_iterator end = this->end();
											for(;it!=end;it++) {
												if (this->_comp(ft::make_pair(k, mapped_type()), *it) == true)
													break;
											}
											return it;
										}
			const_iterator				upper_bound(const key_type& k) const {
											const_iterator it = this->begin();
											const_iterator end = this->end();
											for(;it!=end;it++) {
												if (this->_comp(ft::make_pair(k, mapped_type()), *it) == true)
													break;
											}
											return it;
										}
			ft::pair<
				iterator,
				iterator
			>							equal_range(const key_type& k) {
											return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
										}
			ft::pair<
				const_iterator,
				const_iterator
			>							equal_range(const key_type& k) const {
											return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
										}
		// Allocator
			allocator_type				get_allocator() const {
											return this->_alloc;
										}
	};
}

#endif
