  
/*
	Author: Egor Promyshlennikov
	Date: 20 March 2021

    https://github.com/Epromee
*/
 
#include <iostream>
#include <string>
 
struct RA {
	const int value = 1337;
};
 
struct RB {
	const std::string value = "hello world";
};
 
struct RC {
	const char value = '@';
};
 
template <typename A, typename B, typename C>
struct CLOSURE_3 {
	template< template<class LA, class LB, class LC> class SEL >
	using $ = SEL<A, B, C>;
};
 
template <typename A, typename B, typename C>
using SEL_1 = A;
 
template <typename A, typename B, typename C>
using SEL_2 = B;
 
template <typename A, typename B, typename C>
using SEL_3 = C;
 
 
int main() {
 
	using test_type = CLOSURE_3<RA, RB, RC>;
 
	using test_a = test_type::$<SEL_1>;
	using test_b = test_type::$<SEL_2>;
	using test_c = test_type::$<SEL_3>;
 
	std::cout << test_a().value << '\n';
	std::cout << test_b().value << '\n';
	std::cout << test_c().value << '\n';
 
 
 
	using test_type2 = CLOSURE_3<RB, RC, RA>;
 
	using test_a2 = test_type2::$<SEL_1>;
	using test_b2 = test_type2::$<SEL_2>;
	using test_c2 = test_type2::$<SEL_3>;
 
	std::cout << test_a2().value << '\n';
	std::cout << test_b2().value << '\n';
	std::cout << test_c2().value << '\n';
 
	return 0;
}
