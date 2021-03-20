 
constexpr int not_prim_cont = 0;
constexpr int nil_prim_cont = 1;
constexpr int int_prim_cont = 2;
constexpr int type_prim_cont = 3;
 
/* IF definition */
template <int Cond, class A, class B>
struct IF { using $ = A; };
 
template <class A, class B>
struct IF<0, A, B> { using $ = B; constexpr static int PT = not_prim_cont; };
 
/* EQ definition */
template <class A>
constexpr int isEqual(A a, A b) { return 1; };
 
template <class A, class B>
constexpr int isEqual(A a, B b) { return 0; };
 
template <class A, class B>
struct EQ { constexpr static int V = isEqual( A(), B() ); constexpr static int PT = not_prim_cont; };
 
/* Nothing packer defininion */
struct $N{
	constexpr static int PT = nil_prim_cont;	// shows it's a primitive type Int container
};
 
/* Integer packer defininion */
template <int I>
struct $I{
	constexpr static int V = I;
	constexpr static int PT = int_prim_cont;	// shows it's a primitive type Int container
};
 
/* Conversions */
struct EmptyIntListView;
 
template <int LT, int ... T>
struct IntListView {
	template <int NEW> using InsertFront = IntListView<NEW, LT, T...>;
};
 
template <int LT>
struct IntListView<LT>{
	template <int NEW> using InsertFront = IntListView<NEW, LT>;
};
 
struct EmptyIntListView{
	template <int NEW> using InsertFront = IntListView<NEW>;
};
 
/* Type packer defininion */
template <class T>
struct $T{
	using V = T;
	constexpr static int PT = type_prim_cont;	// shows it's a primitive type Type container
};
 
struct EmptyList;
 
template <class A, class... R>
struct List {
	using Tail = List<R...>;
	using Head = A;
	constexpr static int Size = 1 + Tail::Size;
 
	template <template <class ... LR > class T>
	using Apply = T<A, R... >;
 
	using Reverse = typename List<R ... > :: Reverse :: template InsertBack <A>;
	template <class NEW> using InsertBack = List<A, R ... , NEW>;
	template <class NEW> using InsertFront = List<NEW, A, R... >;
 
	constexpr static int PT = not_prim_cont;	// shows it's not a primitive type container
 
	using __FilterSub$I = typename List<R...> :: Filter$I;
	using __FilterSub$Iadd = typename __FilterSub$I :: template InsertFront<A>;
	using Filter$I = typename IF<A::PT == int_prim_cont, __FilterSub$Iadd, __FilterSub$I> :: $;
};
 
template <class A>
struct List<A> {
	using Head = A;
	using Tail = EmptyList;
	constexpr static int Size = 1;
 
	template <template <class ... LR > class T>
	using Apply = T<A>;
 
	using Reverse = List<A>;
	template <class NEW> using InsertBack = List<A, NEW>;
	template <class NEW> using InsertFront = List<NEW, A>;
 
	constexpr static int PT = not_prim_cont;	// shows it's not a primitive type container
 
	using Filter$I = typename IF<A::PT == int_prim_cont, List<A>, EmptyList> :: $;
};
 
/* List definition */
struct EmptyList {
	using Tail = EmptyList;
	using Head = $N;
	constexpr static int Size = 0;
 
	//template <template <class ... LR > class T>
	//using Apply = T;
 
	using Reverse = EmptyList;
	template <class NEW> using InsertBack = List<NEW>;
	template <class NEW> using InsertFront = List<NEW>;
 
	constexpr static int PT = not_prim_cont;	// shows it's not a primitive type container
 
	using Filter$I = EmptyList;
};
 
 
 
int main() {
 
	// your code goes here
	using test_type = List< $I<2>, $T<int>, $T<float>, $N, $N, $I<4> > :: InsertBack< $I<1337> > :: InsertFront< $I<666> >;
 
	test_type :: fail;
 
	using test_type_2 = test_type :: Filter$I;
	test_type_2 :: fail;
 
	return 0;
}
