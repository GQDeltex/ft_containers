#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <cstddef>
# include <memory>
# include <stdexcept>
# include <iostream>

# include "vector_iterator.hpp"
# include "reverse_iterator.hpp"
# include "is_integral.hpp"
# include "enable_if.hpp"
# include "compare.hpp"

namespace ft {
	template <typename T, typename Alloc = std::allocator<T> >
	class vector {
		public:
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::vector_iterator<T>							iterator;
			typedef ft::vector_iterator<const T>					const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef typename iterator::difference_type				difference_type;
			typedef size_t											size_type;

		protected:
			value_type*		_space;
			size_type		_data_size;
			size_type		_space_size;
			allocator_type	_alloc;

		public:
			// Constructors
			vector(const allocator_type& alloc = allocator_type()) {
				this->__init(alloc);
			}

			vector(
				size_type n,
				const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()
			) {
				this->__init(alloc);
				this->reserve(n);
				for (size_type i = 0; i < n; i++) {
					this->push_back(val);
				}
			}

			template <typename InputIterator>
			vector(
				InputIterator first,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
				const allocator_type& alloc = allocator_type()
			) {
				this->__init(alloc);
				for (; first != last; first++) {
					this->push_back(*first);
				}
			}

			vector(const vector& vec) {
				this->__init(vec._alloc);
				(*this) = vec;
			}

			// Operator =
			vector& operator=(const vector& vec) {
				if (this->_space_size > 0) {
					this->clear();
					this->_alloc.deallocate(this->_space, this->_space_size);
				}
				// Start with new
				this->_alloc = vec._alloc;
				this->_space = this->_alloc.allocate(vec._space_size);
				this->_space = this->__copy(this->_space, vec._space, vec._data_size);
				this->_data_size = vec._data_size;
				this->_space_size = vec._space_size;
				return (*this);
			}

			// Destructor
			~vector(void) {
				this->clear();
				this->_alloc.deallocate(this->_space, this->_space_size);
			}

			// Iterators
			iterator begin(void) {
				return iterator(this->_space);
			}

			const_iterator begin(void) const {
				return const_iterator(this->_space);
			}

			iterator end(void) {
				return iterator(this->_space + this->_data_size);
			}

			const_iterator end(void) const {
				return const_iterator(this->_space + this->_data_size);
			}

			reverse_iterator rbegin(void) {
				return reverse_iterator(this->end());
			}

			const_reverse_iterator rbegin(void) const {
				return const_reverse_iterator(this->end());
			}

			reverse_iterator rend(void) {
				return reverse_iterator(this->begin());
			}

			const_reverse_iterator rend(void) const {
				return const_reverse_iterator(this->begin());
			}

			// Capacity
			size_type size(void) const {
				return this->_data_size;
			}

			size_type max_size(void) const {
				return this->_alloc.max_size();
			}

			void resize(size_type n, value_type val = value_type()) {
				if (this->_data_size > n) {
					for (size_type i = n;i < this->_data_size; i++) {
						this->_alloc.destroy(&(this->_space[i]));
					}
					this->_data_size = n;
				} else if (this->_data_size < n) {
					this->reserve(n);
					for (size_type i = this->_data_size; i < n; i++) {
						this->push_back(val);
					}
				}
			}

			size_type capacity(void) const {
				return this->_space_size;
			}

			bool empty(void) const {
				return (this->_data_size == 0);
			}
			void reserve(size_type n) {
				if (n <= this->_space_size)
					return;
				value_type *new_space = this->_alloc.allocate(n);
				new_space = this->__copy(new_space, this->_space, this->_data_size);
				for (size_type i = 0; i < this->_data_size; i++) {
					this->_alloc.destroy(&(this->_space[i]));
				}
				this->_alloc.deallocate(this->_space, this->_space_size);
				this->_space = new_space;
				this->_space_size = n;
			}

			// Element access
			reference operator[](size_type n) {
				return this->_space[n];
			}

			const_reference operator[](size_type n) const {
				return this->_space[n];
			}

			reference at(size_type n) {
				if (n > this->_data_size)
					throw std::out_of_range("Index > data_size");
				return this->_space[n];
			}

			const_reference at(size_type n) const {
				if (n > this->_data_size)
					throw std::out_of_range("Index > data_size");
				return this->_space[n];
			}

			reference front(void) {
				return this->_space[0];
			}

			const_reference front(void) const {
				return this->_space[0];
			}

			reference back(void) {
				if (this->size() == 0)
					return this->_space[0];
				return this->_space[this->_data_size - 1];
			}

			const_reference back(void) const {
				if (this->size() == 0)
					return this->_space[0];
				return this->_space[this->_data_size - 1];
			}

			// Modifiers
			template <typename InputIterator>
			void assign(
				InputIterator first,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last
			) {
				this->clear();
				for (; first != last; first++) {
					this->push_back(*first);
				}
			}

			void assign(
				size_type n,
				const value_type& val
			) {
				this->clear();
				for (size_type i = 0; i < n; i++) {
					this->push_back(val);
				}
			}

			void push_back(const value_type& val) {
				if (this->_data_size + 1 > this->_space_size) {
					if (this->_space_size == 0)
						this->_space_size++;
					this->reserve(this->_space_size * 2);
				}
				this->_alloc.construct(this->_space + this->_data_size, val);
				this->_data_size++;
			}

			void pop_back(void) {
				this->_alloc.destroy(this->_space + this->_data_size - 1);
				this->_data_size--;
			}

			iterator insert(
				iterator position,
				const value_type& val
			) {
				if (position == this->end()) {
					this->push_back(val);
					return iterator(this->_space + this->_data_size - 1);
				} else {
					vector backup(*this);
					size_type pos = 0;
					iterator it = this->begin();
					// Where are we actually?
					while (it != position && pos < this->_data_size) {
						it++;
						pos++;
					}
					// Oh pointer not in vector? Well, here comes the exception!
					if (pos == this->_data_size) {
						throw std::runtime_error("Not a valid pointer to this vector");
					}
					// Delete everything after where we want to insert
					for (size_type i = pos; i < backup._data_size; i++) {
						this->_alloc.destroy(this->_space + i);
					}
					// Update the _data_size to the last 'stable' element
					this->_data_size = pos;
					// Add the new element
					this->push_back(val);
					// Add back all the 'old' elements after that
					for (size_type i = pos; i < backup._data_size; i++) {
						this->push_back(backup[i]);
					}
					return iterator(this->_space + pos);
				}
			}

			void insert(
				iterator position,
				size_type n,
				const value_type& val
			) {
				for (size_type i = 0; i < n; i++) {
					position = this->insert(position, val);
					position++;
				}
			}

			template <typename InputIterator>
			void insert(
				iterator position,
				InputIterator first,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last
			) {
				for (; first != last; first++) {
					position = this->insert(position, *first);
					position++;
				}
			}

			iterator erase(iterator position) {
				return this->erase(position, position+1);
			}

			iterator erase(iterator first, iterator last) {
				vector<value_type> backup = *this;
				size_type start_pos = 0;
				size_type end_pos = 0;
				iterator it = this->begin();
				// Where are we actually?
				while (it != first && start_pos < this->_data_size) {
					it++;
					start_pos++;
				}
				end_pos = start_pos;
				while (it != last && end_pos <= this->_data_size) {
					it++;
					end_pos++;
				}
				// Oh pointer not in vector? Well, here comes the exception!
				if (start_pos == this->_data_size || end_pos > this->_data_size) {
					throw std::runtime_error("Not a valid pointer to this vector");
				}
				// Delete everything after where we want to erase
				for (size_type i = start_pos; i < end_pos; i++) {
					this->_alloc.destroy(this->_space + i);
				}
				// Update the _data_size to the last 'stable' element
				this->_data_size = start_pos;
				// Add back all the 'old' elements after that
				for (size_type i = end_pos; i < backup._data_size; i++) {
					this->push_back(backup[i]);
				}
				return iterator(this->_space + start_pos);
			}

			void swap(vector& vec) {
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

			void clear(void) {
				for (size_type i = 0; i < this->_data_size; i++) {
					this->_alloc.destroy(this->_space + i);
				}
				this->_data_size = 0;
			}

			// Allocator
			allocator_type get_allocator(void) const {
				return (this->_alloc);
			}

			// Relational Operators
			template <typename Type, typename Allocator>
			bool operator==(const ft::vector<Type, Allocator>& rhs) const {
				// If size doesn't match they can't be equal
				if (this->size() != rhs.size())
					return false;
				return ft::equal(this->begin(), this->end(), rhs.begin());
			}

			template <typename Type, typename Allocator>
			bool operator!=(const ft::vector<Type, Allocator>& rhs) const {
				return !(*this == rhs);
			}

			template <typename Type, typename Allocator>
			bool operator<(const ft::vector<Type, Allocator>& rhs) const {
				return ft::lexicographical_compare(this->begin(), this->end(), rhs.begin(), rhs.end());
			}

			template <typename Type, typename Allocator>
			bool operator>(const ft::vector<Type, Allocator>& rhs) const {
				return rhs < *this;
			}

			template <typename Type, typename Allocator>
			bool operator<=(const ft::vector<Type, Allocator>& rhs) const {
				return !(rhs < *this);
			}

			template <typename Type, typename Allocator>
			bool operator>=(const ft::vector<Type, Allocator>& rhs) const {
				return !(*this < rhs);
			}

		private:
			void __init(const allocator_type& alloc) {
				this->_data_size = 0;
				this->_space_size = 0;
				this->_alloc = alloc;
				this->_space = NULL;
			}

			value_type *__copy(value_type *dest, value_type *src, size_type len) {
				for (size_type i = 0; i < len; i++) {
					this->_alloc.construct(dest+i, src[i]);
				}
				return (dest);
			}
	};
}

// External Swap
template <typename T, typename Alloc>
void swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs) {
	lhs.swap(rhs);
}

#endif
