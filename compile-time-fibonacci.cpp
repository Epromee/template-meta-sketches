 
/*
	Author: Egor Promyshlennikov
	Date: 20 March 2021

    https://github.com/Epromee
*/
 
 
/* Normal list*/
template <long long LR, long long ... R>
struct List {
	using Reverse = typename List<R ... > :: Reverse :: template Insert <LR>;
	template <long long NEW> using Insert = List<LR, R ... , NEW>;
	using Tail = List<R ... >;
};
 
template <long long R> 
struct List<R> {
	using Reverse = List<R>;
	template <long long NEW> using Insert = List<R, NEW>;
};
 
/* Lits of fibonacci */
template <long long F, long long F_, long long ... R >
struct FibList {
	using Next = FibList<(F + F_), F, F_, R...>;
	using ToList = List<F, F_, R...>;
};
 
template <long long N>
struct EnumFibList {
	using FL = typename EnumFibList<N - 1> :: FL :: Next;
};
 
template <>
struct EnumFibList<1> {
	using FL = FibList<1, 0, 0>;
};
 
 
int main() {
 
	/* Enter fibonaccy number from 1 to needed value (until overflow) */
	using instance = EnumFibList<80> :: FL :: ToList :: Reverse :: Tail :: Tail;
 
	/* Let's make it fail anyways*/
	instance::not_a_member_of_instance;
 
	return 0;
}
