#include <iostream>
#include <compare>

// https://devblogs.microsoft.com/cppblog/simplify-your-code-with-rocket-science-c20s-spaceship-operator/
// Three-way comparison operator

struct MyInt {
	int value;

	constexpr MyInt(int val) : value{val} {}
	
    auto operator<=>(const MyInt&) const = default;  // compiler-generated, implicit constexpr
    // auto operator<=>(const MyInt& rhs) const { return value <=> rhs.value; }  // user-defined
    
    // compiler generates and rewrites operator== independently of <=>, in an optimized way
    // bool operator==(const IntWrapper&) const = default;  // but no need to specify it
};

/* Rewritten expression (a <=> b) @ 0
For a < b compiler searches the type of a for an operator<=> and finds it. 
In such case, compiler is allowed to use the operator 
and rewrite the expression a < b as (a <=> b) < 0. 

<=> returns a negative, positive, or zero value (similar to strncmp and memcmp)
 */
constexpr bool isLt(const MyInt& a, const MyInt& b) {
    return a < b;
}

/* Synthesized expression 0 @ (b <=> a)
Compiler will try to use rewritten expression (42 <=> a) < 0 
but there is no conversion from IntWrapper to int to satisfy the left-hand side. 
Compiler creates the “synthesized” expression 0 < (a <=> 42)
and finds there is a conversion from int to IntWrapper through the converting constructor.
 */
constexpr bool isGt42(const MyInt& a) {
	return 42 < a;
}

struct Basics {
	int i;
	char c;
	float f;
	double d;
	auto operator<=>(const Basics&) const = default;
};

struct Arrays {
	int ai[1];
	char ac[2];
	float af[3];
	double ad[2][2];
	auto operator<=>(const Arrays&) const = default;
};

struct Bases : Basics, Arrays {
	auto operator<=>(const Bases&) const = default;
};

int spaceship(void)
{
    constexpr MyInt a(1);
	constexpr MyInt b(50);

	static_assert(a < b);  // (a <=> b) < 0;  // std::strong_ordering::less < 0
	static_assert((a <=> b) < 0);
	static_assert(a <= b);
    
    // Compare int and MyInt without implementing the operator myself
	static_assert(isGt42(b));
	const int i = 40;
    static_assert((i <=> a) > 0);

    constexpr Bases c = { { 0, 'c', 1.f, 1. },
                          { { 1 }, { 'a', 'b' }, { 1.f, 2.f, 3.f }, { { 1., 2. }, { 3., 4. } } } };
    constexpr Bases d = { { 0, 'c', 1.f, 1. },
                          { { 1 }, { 'a', 'b' }, { 1.f, 2.f, 3.f }, { { 1., 2. }, { 3., 4. } } } };
    static_assert(c == d);
    static_assert(!(c != d));
    static_assert(!(c < d));
    static_assert(c <= d);
    static_assert(!(c > d));
    static_assert(c >= d);
    
    return 0;
}
