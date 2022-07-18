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

namespace ft {
	template <
		class T,
		class Compare = std::less<T>,
		class Alloc = std::allocator<T>
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
			typedef ft::rbtree_iterator<value_type, value_compare>			iterator;
			typedef ft::rbtree_iterator<const value_type, value_compare>	const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef ptrdiff_t												difference_type;
			typedef size_t													size_type;

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
			iterator				begin() {
										return iterator(this->tree.begin());
									}
			const_iterator			begin() const {
										return const_iterator(this->tree.begin());
									}
			iterator				end() {
										return iterator(this->tree.end());
									}
			const_iterator			end() const {
										return const_iterator(this->tree.end());
									}
			reverse_iterator		rbegin() {
										return reverse_iterator(this->tree.end());
									}
			const_reverse_iterator	rbegin() const {
										return const_reverse_iterator(this->tree.end());
									}
			reverse_iterator		rend() {
										return reverse_iterator(this->tree.begin());
									}
			const_reverse_iterator	rend() const {
										return const_reverse_iterator(this->tree.begin());
									}
		// Capacity
			bool					empty() const {
										return this->size() == 0;
									}
			size_type				size() const {
										return this->tree.size();
									}
			size_type				max_size() const {
										return this->tree.max_size();
									}
		// Modifiers
			ft::pair<iterator,bool>	insert(const value_type& val) {
										try {
											this->tree.insert(val);
										} catch (const std::exception& e) {
											return ft::make_pair<iterator,bool>(this->find(val), false);
										}
										return ft::make_pair<iterator,bool>(this->find(val), true);
									}
			iterator				insert(
										iterator position,
										const value_type& val
									) {
										(void)position;
										try {
											this->tree.insert(val);
										} catch (const std::exception& e) {
											// Just ignore the error
										}
										return this->find(val);

									}
			template<
			class InputIterator
			> void					insert(
										InputIterator	first,
										typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last
									) {
										for(;first!=last;first++) {
											this->insert(*first);
										}
									}
			void					erase(iterator position) {
										try {
											this->tree.remove(*position);
										} catch (const std::exception& e) {
											// Ignore
										}
										std::cout << "Done erasing" << std::endl;
									}
			size_type				erase(const value_type& val) {
										try {
											this->tree.remove(val);
										} catch (const std::exception& e) {
											return 0;
										}
										return 1;
									}
			void					erase(iterator first, iterator last) {
										set<value_type, value_compare, allocator_type> temp(*this);
										for(;first!=last;first++) {
											try {
												temp.tree.remove(*first);
											} catch (const std::exception& e) {
												// Ignore
											}
										}
										*this = temp;
									}
			void					swap(set& x) {
										this->tree.swap(x.tree);
									}
			void					clear() {
										this->erase(this->begin(), this->end());
									}
		// Observers
			key_compare				key_comp() const;
			value_compare			value_comp() const;
		// Operations
			iterator				find(const value_type& val) const {
										return iterator(this->tree.find(val));
									}
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
