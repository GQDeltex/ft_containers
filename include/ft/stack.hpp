#ifndef FT_STACK_H
# define FT_STACK_H

# include <cstddef>
# include "vector.hpp"

namespace ft {
	template <
		class T,
		class Container = ft::vector<T>
	> class stack {
		public:
			typedef T			value_type;
			typedef Container   container_type;
			typedef size_t		size_type;

		protected:
			container_type	c;

		public:
			// Constructors
								stack (
									const container_type& ctnr = container_type()
								) {
									this->c = ctnr;
								}
			// empty
			bool				empty() const {
									return this->c.empty();
								}
			// size
			size_type			size() const {
									return this->c.size();
								}
			// top
			value_type&			top() {
									return this->c.back();
								}
			const value_type&	top() const {
									return this->c.back();
								}
			// push
			void				push(
									const value_type& val
								) {
									this->c.push_back(val);
								}
			// pop
			void				pop() {
									this->c.pop_back();
								}
			friend bool			operator== (
									const ft::stack<T,Container>& lhs,
									const ft::stack<T,Container>& rhs
								) {
									return lhs.c == rhs.c;
								}
			friend bool			operator< (
									const ft::stack<T,Container>& lhs,
									const ft::stack<T,Container>& rhs
								) {
									return (lhs.c < rhs.c);
								}
	};
	template<
		class T,
		class Container
	> bool			operator!= (
						const ft::stack<T,Container>& lhs,
						const ft::stack<T,Container>& rhs
					) {
						return !(lhs == rhs);
					}
	template<
		class T,
		class Container
	>bool			operator> (
						const ft::stack<T,Container>& lhs,
						const ft::stack<T,Container>& rhs
					) {
						return rhs < lhs;
					}
	template<
		class T,
		class Container
	>bool			operator<= (
						const ft::stack<T,Container>& lhs,
						const ft::stack<T,Container>& rhs
					) {
						return !(lhs > rhs);
					}
	template<
		class T,
		class Container
	>bool			operator>= (
						const ft::stack<T,Container>& lhs,
						const ft::stack<T,Container>& rhs
					) {
						return !(lhs < rhs);
					}
}

#endif
