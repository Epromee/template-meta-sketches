 
/*
	Author: Egor Promyshlennikov
	Date: 20 March 2021
 
	This program yields first few prime numbers,
	and then _fails_ the compilation.
 
	The algorithm is _ineffective_ and used for demonstrational purposes.
	Implementive sieves in template meta would take much more time.
*/
 
/* If definition */
template <int Cond, class A, class B>
struct IF { using $ = A; };
 
template <class A, class B>
struct IF<0, A, B> { using $ = B; };
 
/* I figured out that the compilation takes less time, when using different List for reverse operations */
template <int LR, int ... R>
struct ReversableList {
	using Reverse = typename ReversableList<R ... > :: Reverse :: template InsertBack <LR>;
	template <int NEW> using InsertBack = ReversableList<LR, R ... , NEW>;
};
 
template <int R>
struct ReversableList<R>{
	using Reverse = ReversableList<R>;
	template <int NEW> using InsertBack = ReversableList<R, NEW>;
};
 
 
/* List definition */ 
template <int LR, int ... R >
struct List {
	template <int NEW> using Insert = List<NEW, LR, R ...>;
	template <int ITEM> constexpr static int Divs = (ITEM % LR == 0) ? 1 : List<R ... > :: template Divs<ITEM>;
	using Child = List<R ... >;
	using ChildPrimeFilter = typename Child::PrimeOnly;
	using ChildPrimeFilterAdd = typename ChildPrimeFilter :: template Insert<LR>;
	constexpr static int ChildDivs = Child :: template Divs<LR>;
	using PrimeOnly = typename IF< ChildDivs, ChildPrimeFilter, ChildPrimeFilterAdd> :: $;
	using Reversable = ReversableList<LR, R...>;
};
 
template <int R>
struct List<R> {
	template <int NEW> using Insert = List<NEW, R>;
	template <int ITEM> constexpr static int Divs = (ITEM % R == 0);
	using PrimeOnly = List<R>;
	using Reversable = ReversableList<R>;
};
 
template <int C>
struct ListGen {
	using ThisList = typename ListGen<C - 1> :: ThisList :: template Insert<C>;
};
 
template <>
struct ListGen<2> {
	using ThisList = List<2>;
};
 
 
int main() {
 
	using MyType = ListGen<400>::ThisList :: PrimeOnly :: Reversable :: Reverse;
 
	MyType :: trigger_failure;	// FAIL THE COMPILATION
 
	return 0;
}
