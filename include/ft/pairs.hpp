#ifndef FT_PAIRS_H
# define FT_PAIRS_H

namespace ft {
	template <
		class T1,
		class T2
	> struct pair {
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;
	};

	template <
		class T1,
		class T2
	> pair<T1, T2>	make_pair(
						T1 x,
						T2 y
					) {
						pair<T1, T2> pr;
						pr.first = x;
						pr.second = y;
						return (pr);
					}
}

#endif
