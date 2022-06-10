#ifndef FT_ENABLE_IF_H
# define FT_ENABLE_IF_H

namespace ft {
	template <
		bool,
		typename T = void
	> struct enable_if {};
	template <
		typename T
	> struct enable_if<true, T> {
		typedef T type;
	};
};

#endif
