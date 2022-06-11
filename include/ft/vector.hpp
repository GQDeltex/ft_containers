#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <cstddef>
# include <memory>
# include <stdexcept>

# include <iostream>

# include "iterator.hpp"
# include "reverse_iterator.hpp"
# include "is_integral.hpp"
# include "enable_if.hpp"
# include "compare.hpp"

namespace ft {
	template <
		class T,
		class Alloc = std::allocator<T>
	> class vector {
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::iterator<T>								iterator;
			typedef const iterator								const_iterator;
			typedef typename ft::reverse_iterator<T>			reverse_iterator;
			typedef const reverse_iterator						const_reverse_iterator;
			typedef typename iterator::difference_type			difference_type;
			typedef size_t										size_type;

		protected:
			value_type*											_space;
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
										typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
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
											this->clear();
											this->_alloc.deallocate(this->_space, this->_space_size);
										}
										// Start with new
										this->_alloc = vec._alloc;
										this->_space = this->_alloc.allocate(vec._space_size);
										this->_space = this->__copy(this->_space, vec._space, vec._data_size);
										this->_data_size = vec._data_size;
										this->_space_size = vec._space_size;
										this->__debug("Assingment success");
										return (*this);
									}

			// Iterator
			iterator				begin(void) {
										this->__debug("Getting begin iterator");
										return iterator(this->_space);
									}
			const_iterator			begin(void) const {
										return iterator(this->_space);
									}
			iterator				end(void) {
										this->__debug("Getting end iterator");
										return iterator(this->_space + this->_data_size);
									}
			const_iterator			end(void) const {
										return iterator(this->_space + this->_data_size);
									}
			reverse_iterator		rbegin(void) {
										this->__debug("Getting rbegin reverse_iterator");
										return reverse_iterator(this->_space + this->_data_size - 1);
									}
			const_reverse_iterator	rbegin(void) const {
										return reverse_iterator(this->_space + this->_data_size - 1);
									}
			reverse_iterator		rend(void) {
										this->__debug("Getting rend reverse_iterator");
										return reverse_iterator(this->_space - 1);
									}
			const_reverse_iterator	rend(void) const {
										return reverse_iterator(this->_space - 1);
									}
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
									) {
										this->__debug("Resizing Vector");
										if (this->_data_size > n) {
											this->__debug("Truncating vector, deleting other elements");
											for (size_type i = n;i < this->_data_size; i++) {
												this->_alloc.destroy(&(this->_space[i]));
											}
											this->_data_size = n;
										} else if (this->_data_size < n) {
											this->__debug("Extending vector with val");
											reserve(n);
											for(size_type i = this->_data_size; i < n; i++) {
												push_back(val);
											}
										}
									}
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
										if (n < 0)
											throw std::runtime_error("Index < 0");
										if (n > this->_data_size)
											throw std::runtime_error("Index > data_size");
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
										if (this->size() == 0)
											return this->_space[0];
										return this->_space[this->_data_size - 1];
									}
			const_reference			back(void) const {
										if (this->size() == 0)
											return this->_space[0];
										return this->_space[this->_data_size - 1];
									}

			// Modifiers
			template <
				class InputIterator
			> void					assign(
										InputIterator first,
										typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last
									) {
										this->__debug("Assigning from Iterator");
										this->clear();
										for(;first != last; first++) {
											this->push_back(*first);
										}
									}
			void					assign(
										size_type n,
										const value_type& val
									) {
										this->__debug("Assigning from value/type");
										this->clear();
										for(size_type i = 0;i < n;i++) {
											this->push_back(val);
										}
									}
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
										this->_alloc.construct(this->_space + this->_data_size, val);
										this->__debug("Constructed. Updating meta");
										this->_data_size++;
									}
			void					pop_back(void) {
										this->__debug("Deleting last element");
										this->_alloc.destroy(this->_space + this->_data_size - 1);
										this->_data_size--;
									}
			iterator				insert(
										iterator position,
										const value_type& val
									) {
										this->__debug("Inserting single element");
										if (position == this->end()) {
											this->push_back(val);
											return iterator(this->_space + this->_data_size - 1);
										} else {
											vector<value_type> backup = *this;
											size_type pos = 0;
											iterator it = this->begin();
											// Where are we actually?
											while(it != position && pos < this->_data_size) {
												it++;
												pos++;
											}
											// Oh pointer not in vector? Well, here comes the exception!
											if (pos == this->_data_size) {
												throw std::runtime_error("Not a valid pointer to this vector");
											}
											// Delete everything after where we want to insert
											for(size_type i = pos; i < backup._data_size; i++) {
												this->_alloc.destroy(this->_space + i);
											}
											// Update the _data_size to the last 'stable' element
											this->_data_size = pos;
											// Add the new element
											this->push_back(val);
											// Add back all the 'old' elements after that
											for(size_type i = pos; i < backup._data_size; i++) {
												this->push_back(backup[i]);
											}
											return iterator(this->_space + pos);
										}
									}
			void					insert(
										iterator position,
										size_type n,
										const value_type& val
									) {
										this->__debug("Inserting multipe elements");
										for (size_type i=0; i < n; i++) {
											position = this->insert(position, val);
											position++;
										}
									}
			template <
				class InputIterator
			> void					insert(
										iterator position,
										InputIterator first,
										typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last
									) {
										this->__debug("Inserting from Iterator");
										for (; first != last; first++) {
											position = this->insert(position, *first);
											position++;
										}
									}
			iterator				erase(
										iterator position
									) {
										this->__debug("Erase single Element");
										return this->erase(position, position+1);
									}
			iterator				erase(
										iterator first,
										iterator last
									) {
										this->__debug("Erase range of Elements");
										vector<value_type> backup = *this;
										size_type start_pos = 0;
										size_type end_pos = 0;
										iterator it = this->begin();
										// Where are we actually?
										while(it != first && start_pos < this->_data_size) {
											it++;
											start_pos++;
										}
										end_pos = start_pos;
										while(it != last && end_pos <= this->_data_size) {
											it++;
											end_pos++;
										}
										// Oh pointer not in vector? Well, here comes the exception!
										if (start_pos == this->_data_size || end_pos > this->_data_size) {
											throw std::runtime_error("Not a valid pointer to this vector");
										}
										// Delete everything after where we want to erase
										for(size_type i = start_pos; i < end_pos; i++) {
											this->_alloc.destroy(this->_space + i);
										}
										// Update the _data_size to the last 'stable' element
										this->_data_size = start_pos;
										// Add back all the 'old' elements after that
										for(size_type i = end_pos; i < backup._data_size; i++) {
											this->push_back(backup[i]);
										}
										return iterator(this->_space + start_pos);
									}
			void					swap(vector& vec) {
										this->__debug("Swapping vectors");
										value_type	*backup_space = vec._space;
										size_type	backup_data_size = vec._data_size;
										size_type	backup_space_size = vec._space_size;
										vec._space = this->_space;
										vec._data_size = this->_data_size;
										vec._space_size = this->_space_size;
										this->_space = backup_space;
										this->_data_size = backup_data_size;
										this->_space_size = backup_space_size;
									}
			void					clear(void) {
										this->__debug("Clearing Vector!");
										for(size_type i = 0;i < this->_data_size;i++) {
											this->_alloc.destroy(this->_space + i);
										}
										this->_data_size = 0;
									}

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
										this->__debug("--> INIT <--");
									}
			void					__debug(const std::string& msg) {
										(void)msg;
										//std::cout << "\e[1;33m" << msg << "\e[0m" << std::endl;
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
	class T,
	class Alloc
> bool	operator==(
			const ft::vector<T, Alloc>& lhs,
			const ft::vector<T, Alloc>& rhs
		) {
			// If size doesn't match they can't be equal
			if (lhs.size() != rhs.size())
				return false;
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}
template<
	class T,
	class Alloc
>bool	operator!=(
			const ft::vector<T, Alloc>& lhs,
			const ft::vector<T, Alloc>& rhs
		) {
			return !(lhs == rhs);
		}
template<
	class T,
	class Alloc
>bool	operator< (
			const ft::vector<T, Alloc>& lhs,
			const ft::vector<T, Alloc>& rhs
		) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
template<
	class T,
	class Alloc
>bool	operator<=(
			const ft::vector<T, Alloc>& lhs,
			const ft::vector<T, Alloc>& rhs
		) {
			return !(rhs < lhs);
		}
template<
	class T,
	class Alloc
>bool	operator> (
			const ft::vector<T, Alloc>& lhs,
			const ft::vector<T, Alloc>& rhs
		) {
			return rhs < lhs;
		}
template<
	class T,
	class Alloc
>bool	operator>=(
			const ft::vector<T, Alloc>& lhs,
			const ft::vector<T, Alloc>& rhs
		) {
			return !(lhs < rhs);
		}
template<
	class T,
	class Alloc
>void	swap(
			ft::vector<T, Alloc>& lhs,
			ft::vector<T, Alloc>& rhs
		) {
			lhs.swap(rhs);
		}
#endif
