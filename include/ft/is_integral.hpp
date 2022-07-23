#ifndef IS_INTEGRAL_H
# define IS_INTEGRAL_H

namespace ft {
	template <
		class T
	> struct is_integral {
		typedef T	value_type;
		const static bool	value = false;

		operator value_type() {
			return value;
		}

		value_type operator()() {
			return value;
		}
	};

	template<>
	struct is_integral<bool> {
		const static bool value = true;
	};

	template<>
	struct is_integral<char> {
		const static bool value = true;
	};

	template<>
	struct is_integral<wchar_t> {
		const static bool value = true;
	};

	template<>
	struct is_integral<signed char> {
		const static bool value = true;
	};

	template<>
	struct is_integral<short> {
		const static bool value = true;
	};

	template<>
	struct is_integral<int> {
		const static bool value = true;
	};

	template<>
	struct is_integral<long> {
		const static bool value = true;
	};

	template<>
	struct is_integral<long long> {
		const static bool value = true;
	};

	template<>
	struct is_integral<unsigned char> {
		const static bool value = true;
	};

	template<>
	struct is_integral<unsigned short> {
		const static bool value = true;
	};

	template<>
	struct is_integral<unsigned int> {
		const static bool value = true;
	};

	template<>
	struct is_integral<unsigned long> {
		const static bool value = true;
	};

	template<>
	struct is_integral<unsigned long long> {
		const static bool value = true;
	};
};

#endif
