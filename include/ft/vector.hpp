#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <cstddef>
# include <iterator>
# include <memory>

# include <iostream>

# include "iterator.hpp"

namespace ft {
	template <
		class T
	> class vector {
		public:
			typedef T											value_type;
			typedef std::allocator<T>							allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::iterator<T>								iterator;
			typedef const iterator								const_iterator;
			typedef typename std::reverse_iterator<iterator>	reverse_iterator;
			typedef const reverse_iterator						const_reverse_iterator;
			typedef std::iterator_traits<iterator>				difference_type;
			typedef size_t										size_type;

		protected:
			value_type*											_space;
			value_type*											_end_data;
			size_type											_data_size;
			size_type											_space_size;
			allocator_type										_alloc;

		public:
			// Constructor
									vector(
										const allocator_type& alloc = allocator_type()
									) {
										this->__debug("Default Constructor");
										this->__init(alloc);
									}
									vector(
										size_type n,
										const value_type& val = value_type(),
										const allocator_type& alloc = allocator_type()
									) {
										this->__debug("Fill Constructor");
										this->__init(alloc);
										this->reserve(n);
										for(size_type i = 0;i < n;i++) {
											this->push_back(val);
										}
									}
			template <
				class InputIterator
			>						vector(
										InputIterator first,
										InputIterator last,
										const allocator_type& alloc = allocator_type()
									) {
										this->__debug("Range Constructor");
										this->__init(alloc);
										while(first != last) {
											this->push_back(*first);
											first++;
										}
									}
									vector(
										const vector& vec
										) {
										this->__debug("Copy Constructor");
										this->__init(vec._alloc);
										(*this) = vec;
									}

			// Destructor
									~vector(void) {
										this->__debug("Destructing Vector");
										for(size_type i=0;i<this->_data_size;i++) {
											this->_alloc.destroy(this->_space + i);
										}
										this->_alloc.deallocate(this->_space, this->_space_size);
									}

			// Operator =
			vector&					operator=(
										const vector& vec
									) {
										this->__debug("Assignment operator called");
										if (this->_space_size > 0) {
											this->__debug("Freeing old existing space");
											this->_alloc.deallocate(this->_space, this->_space_size);
										}
										// Start with new
										this->_alloc = vec._alloc;
										this->_space = this->_alloc.allocate(vec._space_size);
										this->_space = this->__copy(this->_space, vec._space, vec._data_size);
										this->_data_size = vec._data_size;
										this->_space_size = vec._space_size;
										this->_end_data = this->_space + this->_data_size;
										this->__debug("Assingment success");
										return (*this);
									}

			// Iterator
			iterator				begin(void) {
										this->__debug("Getting begin iterator");
										return iterator(this->_space);
									}
			const_iterator			begin(void) const {
										this->__debug("Getting const begin iterator");
										return iterator(this->_space);
									}
			iterator				end(void) {
										this->__debug("Getting end iterator");
										return iterator(this->_space + this->_data_size);
									}
			const_iterator			end(void) const {
										this->__debug("Getting const end iterator");
										return iterator(this->_space + this->_data_size);
									}
			reverse_iterator		rbegin(void);
			const_reverse_iterator	rbegin(void) const;
			reverse_iterator		rend(void);
			const_reverse_iterator	rend(void) const;

			// Capacity
			size_type				size(void) const {
										return this->_data_size;
									}
			size_type				max_data_size(void) const {
										return this->_alloc.max_data_size();
									}
			void					resize(
										size_type n,
										value_type val = value_type()
									);
			size_type				capacity(void) const {
										return this->_space_size;
									}
			bool					empty(void) const {
										return (this->_data_size == 0);
									}
			void					reserve(
										size_type n
									) {
										this->__debug("Request for space");
										if (n <= this->_space_size)
											return;

										this->__debug("More space needed");
										value_type *new_space = this->_alloc.allocate(n);
										new_space = this->__copy(new_space, this->_space, this->_data_size);
										for (size_type i = 0;i<this->_data_size;i++) {
											this->_alloc.destroy(&(this->_space[i]));
										}
										this->_alloc.deallocate(this->_space, this->_space_size);
										this->_space = new_space;

										this->_end_data = this->_space+this->_data_size;
										this->_space_size = n;
										this->__debug("Allocation success");
									}

			// Element access
			reference				operator[](
										size_type n
									) {
										return this->_space[n];
									}
			const_reference			operator[](
										size_type n
									) const {
										return this->_space[n];
									}
			reference				at(
										size_type n
									) {
										return this->_space[n];
									}
			const_reference			at(
										size_type n
									) const {
										return this->_space[n];
									}
			reference				front(void) {
										return this->_space[0];
									}
			const_reference			front(void) const {
										return this->_space[0];
									}
			reference				back(void) {
										if (this->size > 0)
											return this->_space[0];
										return this->_space[this->_data_size - 1];
									}
			const_reference			back(void) const {
										if (this->size > 0)
											return this->_space[0];
										return this->_space[this->_data_size - 1];
									}

			// Modifiers
			template <
				class InputIterator
			> void					assign(
										InputIterator first,
										InputIterator last
									);
			void					assign(
										size_type n,
										const value_type& val
									);
			void					push_back(
										const value_type& val
									) {
										this->__debug("push_back called");
										if (this->_data_size + 1 > this->_space_size) {
											if (this->_space_size == 0)
												this->_space_size++;
											this->reserve(this->_space_size * 2);
										}
										this->__debug("Construct new element at end");
										this->_alloc.construct(this->_end_data, val);
										this->__debug("Constructed. Updating meta");
										this->_end_data++;
										this->_data_size++;
									}
			void					pop_back(void);
			iterator				insert(
										iterator position,
										const value_type& val
									);
			void					insert(
										iterator position,
										size_type n,
										const value_type& val
									);
			template <
				class InputIterator
			> void					insert(
										iterator position,
										InputIterator first,
										InputIterator last
									);
			iterator				erase(
										iterator position
									);
			iterator				erase(
										iterator first,
										iterator last
									);
			void					swap(vector& vec);
			void					clear(void);

			// Allocator
			allocator_type			get_allocator(void) const {
				return (this->_alloc);
			}
		private:
			void					__init(const allocator_type& alloc) {
										this->_data_size = 0;
										this->_space_size = 0;
										this->_alloc = alloc;
										this->_space = NULL;
										this->_end_data = NULL;
										this->__debug("--> INIT <--");
									}
			void					__debug(const std::string& msg) {
										std::cout << "\e[1;33m" << msg << "\e[0m" << std::endl;
									}
			value_type				*__copy(value_type *dest, value_type *src, size_type len) {
										if (len > 0) {
											this->__debug("Already have elements, copying");
											for(size_type i=0;i<len;i++) {
												this->_alloc.construct(dest+i, src[i]);
											}
										}
										return (dest);
									}
	};
}

// Non-member operators
template<
	class T
> bool	operator==(
			const ft::vector<T>& lhs,
			const ft::vector<T>& rhs
		);
template<
	class T
>bool	operator!=(
			const ft::vector<T>& lhs,
			const ft::vector<T>& rhs
		);
template<
	class T
>bool	operator< (
			const ft::vector<T>& lhs,
			const ft::vector<T>& rhs
		);
template<
	class T
>bool	operator<=(
			const ft::vector<T>& lhs,
			const ft::vector<T>& rhs
		);
template<
	class T
>bool	operator> (
			const ft::vector<T>& lhs,
			const ft::vector<T>& rhs
		);
template<
	class T
>bool	operator>=(
			const ft::vector<T>& lhs,
			const ft::vector<T>& rhs
		);
template<
	class T
>void	swap(
			ft::vector<T>& lhs,
			ft::vector<T>& rhs
		);

#endif
