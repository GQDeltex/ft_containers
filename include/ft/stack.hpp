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
	};
}

#endif
