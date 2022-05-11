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
		public:
			// Constructor
									vector(
										const allocator_type& alloc = allocator_type()
									);
									vector(
										size_type n,
										const value_type& val = value_type(),
										const allocator_type& alloc = allocator_type()
									);
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
									~vector(void);
			// Operator =
			vector&					operator=(
									const vector& vec
									);
			// Iterators
			iterator				begin(void);
			const_iterator			begin(void) const;
			iterator				end(void);
			const_iterator			end(void) const;
			reverse_iterator		rbegin(void);
			const_reverse_iterator	rbegin(void) const;
			reverse_iterator		rend(void);
			const_reverse_iterator	rend(void) const;
			// Capacity
			size_type				size(void) const;
			size_type				max_size(void) const;
			void					resize(
										size_type n,
										value_type val = value_type()
									);
			size_type				capacity(void) const;
			bool					empty(void) const;
			void					reserve(
										size_type n
									);
			// Element access
			reference				operator[](
										size_type n
									);
			const_reference			operator[](
										size_type n
									) const;
			reference				at(
										size_type n
									);
			const_reference			at(
										size_type n
									) const;
			reference				front(void);
			const_reference			front(void) const;
			reference				back(void);
			const_reference			back(void) const;
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
									);
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
