#ifndef FT_PAIRS_H
# define FT_PAIRS_H
# include <ostream>

namespace ft {
	template <
		class T1,
		class T2
	> class pair {
		public:
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		pair() {
			this->first = first_type();
			this->second = second_type();
		};
		template <class U, class V> pair(const pair<U, V>& pr): first(pr.first), second(pr.second){
		}
		pair(const first_type& a, const second_type& b): first(a), second(b){
		}
		pair&	operator=(const pair& pr) {
			this->first = pr.first;
			this->second = pr.second;
			return *this;
		}
	};

	template<
		typename T1,
		typename T2
	>std::ostream& operator<<(std::ostream& out, const ft::pair<T1, T2> pr) {
		return out << "ft::pair(" << pr.first << "|" << pr.second << ")";
	}

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

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first==rhs.first && lhs.second==rhs.second;
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(lhs==rhs);
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(rhs<lhs);
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return rhs<lhs;
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
		return !(lhs<rhs);
	}
}

#endif
