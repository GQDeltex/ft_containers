#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <cstddef>
# include <memory>

namespace ft {
	template <
		class T,
		class Alloc=std::allocator<T>
	> class vector {
		private:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename value_type::iterator				iterator;
			typedef typename value_type::const_iterator			const_iterator;
			typedef typename value_type::reverse_iterator		reverse_iterator;
			typedef typename value_type::const_reverse_iterator	const_reverse_iterator;
			typedef typename iterator::difference_type			difference_type;
			typedef size_t										size_type;
			value_type*											_data;
			size_type											_size;
			allocator_type										_alloc;
		public:
			// Constructor
									vector(
										const allocator_type& alloc = allocator_type()
									) {
										this->_size = 0;
										this->_data = NULL;
										this->_alloc = alloc;
									}
									vector(
										size_type n,
										const value_type& val = value_type(),
										const allocator_type& alloc = allocator_type()
									) {
										this->_size = n;
										this->_alloc = alloc;
										this->_data = this->_alloc.allocate(this->_size);
										for(size_type i = 0;i < this->_size;i++) {
											this->_alloc.construct(&(this->_data[i]), val);
										}
									}
			template <
				class InputIterator
			>						vector(
										InputIterator first,
										InputIterator last,
										const allocator_type& alloc = allocator_type()
									);
									vector(
										const vector& vec
									);

			// Destructor
									~vector(void) {
										this->_alloc.deallocate(this->_data, this->_size);
									}

			// Operator =
			vector&					operator=(
									const vector& vec
									);

			// Iterator
			iterator				begin(void);
			const_iterator			begin(void) const;
			iterator				end(void);
			const_iterator			end(void) const;
			reverse_iterator		rbegin(void);
			const_reverse_iterator	rbegin(void) const;
			reverse_iterator		rend(void);
			const_reverse_iterator	rend(void) const;

			// Capacity
			size_type				size(void) const {
										return this->_size;
									}
			size_type				max_size(void) const {
										return this->_alloc.max_size();
									}
			void					resize(
										size_type n,
										value_type val = value_type()
									);
			size_type				capacity(void) const;
			bool					empty(void) const {
										return (this->_size == 0);
									}
			void					reserve(
										size_type n
									);

			// Element access
			reference				operator[](
										size_type n
									) {
										return this->_data[n];
									}
			const_reference			operator[](
										size_type n
									) const {
										return this->_data[n];
									}
			reference				at(
										size_type n
									) {
										return this->_data[n];
									}
			const_reference			at(
										size_type n
									) const {
										return this->_data[n];
									}
			reference				front(void) {
										return this->_data[0];
									}
			const_reference			front(void) const {
										return this->_data[0];
									}
			reference				back(void) {
										if (this->size > 0)
											return this->_data[0];
										return this->_data[this->_size - 1];
									}
			const_reference			back(void) const {
										if (this->size > 0)
											return this->_data[0];
										return this->_data[this->_size - 1];
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
										value_type*	new_data;
										new_data = this->_alloc.allocate(this->_size + 1);
										size_type i = 0;
										if (this->_data) {
											for (;i<this->_size;i++) {
												this->_alloc.construct(&(new_data[i]), this->_data[i]);
											}
											this->_alloc.deallocate(this->_data, this->_size);
										}
										this->_alloc.construct(&(new_data[i]), val);
										this->_data = new_data;
										this->_size++;
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
			allocator_type			get_allocator(void) const;

			// Non-member operators
			friend bool				operator==(
										const vector& lhs,
										const vector& rhs
									);
			friend bool				operator!=(
										const vector& lhs,
										const vector& rhs
									);
			friend bool				operator< (
										const vector& lhs,
										const vector& rhs
									);
			friend bool				operator<=(
										const vector& lhs,
										const vector& rhs
									);
			friend bool				operator> (
										const vector& lhs,
										const vector& rhs
									);
			friend bool				operator>=(
										const vector& lhs,
										const vector& rhs
									);
			friend void				swap(
										vector& lhs,
										vector& rhs
									);
	};
}


#endif
