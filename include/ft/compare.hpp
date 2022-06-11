#ifndef FT_COMPARE_H
# define FT_COMPARE_H

namespace ft {
	template <
		class InputIterator1,
		class InputIterator2
	> bool	equal(
				InputIterator1 first1,
				InputIterator1 last1,
				InputIterator2 first2
			) {
				while (first1 != last1) {
					if (!(*first1 == *first2))
						return false;
					first1++;
					first2++;
				}
				return true;
			}

	template <
		class InputIterator1,
		class InputIterator2,
		class BinaryPredicate
	> bool	equal(
				InputIterator1	first1,
				InputIterator1	last1,
				InputIterator2	first2,
				BinaryPredicate	pred
			) {
				while (first1 != last1) {
					if (!(pred(*first1, *first2)))
						return false;
					first1++;
					first2++;
				}
				return true;
			}

	template <
		class InputIterator1,
		class InputIterator2
	> bool	lexicographical_compare(
				InputIterator1 first1,
				InputIterator1 last1,
				InputIterator2 first2,
				InputIterator2 last2
			) {
				while (first1 != last1) {
					// Are we at the end?
					if (first2 == last2)
						return false;
					// Is 2 smaller than 1
					else if (*first2 < *first1)
						return false;
					// Is 1 smaller than 2 (what we actually want to check)
					else if (*first1 < *first2)
						return true;
					first1++;
					first2++;
				}
				return (first2 != last2);
			}

	template <
		class InputIterator1,
		class InputIterator2,
		class Compare
	> bool	lexicographical_compare(
				InputIterator1	first1,
				InputIterator1	last1,
				InputIterator2	first2,
				InputIterator2	last2,
				Compare			comp
			) {
				while (first1 != last1) {
					// Are we at the end?
					if (first2 == last2)
						return false;
					// Is 2 smaller than 1
					else if (comp(*first2, *first1))
						return false;
					// Is 1 smaller than 2 (what we actually want to check)
					else if (comp(*first1, *first2))
						return true;
					first1++;
					first2++;
				}
				return (first2 != last2);
			}
}

#endif
