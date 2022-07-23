#ifndef FT_PAIRS_H
# define FT_PAIRS_H

# include <ostream>

namespace ft {
	template <class T1, class T2>
	class pair {
		public:
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;

			// Constructors
			pair() {
				this->first = first_type();
				this->second = second_type();
			};

			template <class U, class V>
			pair(const pair<U, V>& pr): first(pr.first), second(pr.second){}

			pair(const first_type& a, const second_type& b): first(a), second(b){}

			// Assignment Operator
			pair&	operator=(const pair& pr) {
				this->first = pr.first;
				this->second = pr.second;
				return *this;
			}

			// Destructor
			~pair() {}

			// Relational Operators
			template <class Type1, class Type2>
			bool operator==(const pair<Type1,Type2>& rhs) const {
				return this->first == rhs.first && this->second == rhs.second;
			}

			template <class Type1, class Type2>
			bool operator!=(const pair<Type1,Type2>& rhs) const {
				return !(*this == rhs);
			}

			template <class Type1, class Type2>
			bool operator<(const pair<Type1,Type2>& rhs) const {
				return this->first < rhs.first || (!(rhs.first < this->first) && this->second < rhs.second);
			}

			template <class Type1, class Type2>
			bool operator>(const pair<Type1,Type2>& rhs) const {
				return rhs < *this;
			}

			template <class Type1, class Type2>
			bool operator<=(const pair<Type1,Type2>& rhs) const {
				return !(rhs < *this);
			}

			template <class Type1, class Type2>
			bool operator>=(const pair<Type1,Type2>& rhs) const {
				return !(*this < rhs);
			}
	};

	template <class T1, class T2> pair<T1, T2>
	make_pair(T1 x, T2 y) {
		pair<T1, T2> pr(x, y);
		return (pr);
	}
}

#endif
