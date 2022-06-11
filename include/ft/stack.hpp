#ifndef FT_STACK_H
# define FT_STACK_H

# include "vector.hpp"

namespace ft {
	template <
		class T,
		class Container = ft::vector<T>
	> class stack {
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		protected:
			container_type	cont;

		public:
			// Constructors
								stack (
									const container_type& ctnr = container_type()
								) {
									this->cont = ctnr;
								}
			// empty
			bool				empty() const {
									return this->cont.empty();
								}
			// size
			size_type			size() const {
									return this->cont.size();
								}
			// top
			value_type&			top() {
									return this->cont.back();
								}
			const value_type&	top() const {
									return this->cont.back();
								}
			// push
			void				push(
									const value_type& val
								) {
									this->cont.push_back(val);
								}
			// pop
			void				pop() {
									this->cont.pop_back();
								}
	};
}

#endif
