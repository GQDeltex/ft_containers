#ifndef IS_INTEGRAL_H
# define IS_INTEGRAL_H

# include <type_traits>

namespace ft {
	template <
		class T
	> struct is_integral {
		const static bool value = false;
		typedef T value_type;
		operator value_type() {
			return value;
		}
		value_type operator()() {
			return value;
		}
	};
	template<> struct is_integral<bool> {
		const static bool value = true;
	};
	template<> struct is_integral<char> {
		const static bool value = true;
	};
	template<> struct is_integral<char16_t> {
		const static bool value = true;
	};
	template<> struct is_integral<char32_t> {
		const static bool value = true;
	};
	template<> struct is_integral<wchar_t> {
		const static bool value = true;
	};
	template<> struct is_integral<short> {
		const static bool value = true;
	};
	template<> struct is_integral<int> {
		const static bool value = true;
	};
	template<> struct is_integral<long> {
		const static bool value = true;
	};
	template<> struct is_integral<long long> {
		const static bool value = true;
	};
};

#endif
