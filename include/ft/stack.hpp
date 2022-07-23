#ifndef FT_STACK_H
# define FT_STACK_H

# include <cstddef>
# include "vector.hpp"

namespace ft {
	template <typename T, typename Container = ft::vector<T> >
	class stack {
		public:
			typedef T			value_type;
			typedef Container   container_type;
			typedef size_t		size_type;

		protected:
			container_type	c;

		public:
			// Constructors
			stack (const container_type& ctnr = container_type()): c(ctnr) {}

			// empty
			bool empty() const {
				return this->c.empty();
			}

			// size
			size_type size() const {
				return this->c.size();
			}

			// top
			value_type& top() {
				return this->c.back();
			}

			const value_type& top() const {
				return this->c.back();
			}

			// push
			void push(const value_type& val) {
				this->c.push_back(val);
			}

			// pop
			void pop() {
				this->c.pop_back();
			}

			// Relational Operators
			template <typename Type, typename Cont>
			bool operator==(const ft::stack<Type, Cont>& rhs) const {
				return this->c == rhs.c;
			}

			template <typename Type, typename Cont>
			bool operator!=(const ft::stack<Type, Cont>& rhs) const {
				return !(*this == rhs);
			}

			template <typename Type, typename Cont>
			bool operator<(const ft::stack<Type, Cont>& rhs) const {
				return this->c < rhs.c;
			}

			template <typename Type, typename Cont>
			bool operator>(const ft::stack<Type, Cont>& rhs) const {
				return rhs < *this;
			}
			template <typename Type, typename Cont>
			bool operator<=(const ft::stack<Type, Cont>& rhs) const {
				return !(rhs < *this);
			}
			template <typename Type, typename Cont>
			bool operator>=(const ft::stack<Type, Cont>& rhs) const {
				return !(*this < rhs);
			}
	};
}

#endif
