 
/*
	Author: Egor Promyshlennikov
	Date: 20 March 2021

    https://github.com/Epromee
*/

#include <iostream>
 
/* Integer packer defininion */
template <int I>
struct $I{
	constexpr static int V = I;
};
 
/* List definition */
template <class A, class... R>
struct List {
	using Tail = List<R...>;
	using Head = A;
	constexpr static int Size = 1 + Tail::Size;
 
	template <template <class ... LR > class T>
	using Apply = T<A, R... >;
};
 
template <class A>
struct List<A> {
	using Head = A;
	constexpr static int Size = 1;
 
	template <template <class ... LR > class T>
	using Apply = T<A>;
};
 
/* If definition */
template <int Cond, class A, class B>
struct IF { using $ = A; };
 
template <class A, class B>
struct IF<0, A, B> { using $ = B; };
 
/* EQ definition */
template <class A>
constexpr int isEqual(A a, A b) { return 1; };
 
template <class A, class B>
constexpr int isEqual(A a, B b) { return 0; };
 
template <class A, class B>
struct EQ { constexpr static int V = isEqual( A(), B() ); };
 
struct F{}; struct G{};
 
int main() {
 
	std::cout <<
		IF<
			EQ<$I<15>, $I<15>>::V,
			$I<1337>,
			$I<666>
		>::$::V
	<< '\n';
 
	std::cout <<
		IF<
			EQ<$I<4>, $I<8>>::V,
			$I<15>,
			$I<16>
		>::$::V
	<< '\n';
 
	return 0;
}
 
