// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "gtest/gtest.h"

#include "Integer.h"

// -----------
// TestInteger
// -----------

// -----------------
// shift_left_digits
// -----------------


TEST(Integer, shift_left_digits_1) {
    const int a[] = {2, 3, 4};
    const int b[] = {2, 3, 4, 0, 0};
          int x[10];
    const int* p = shift_left_digits(a, a + 3, 2, x);
    ASSERT_EQ(5, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

TEST(Integer, shift_left_digits_2) {
    const int a[] = {2, 3, 4, 5, 6};
    const int b[] = {2, 3, 4, 5, 6};
          int x[10];
    const int* p = shift_left_digits(a, a + 5, 0, x);
    ASSERT_EQ(5, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

TEST(Integer, shift_left_digits_3) {
    const int a[] = {2, 3, 4};
    const int b[] = {2, 3};
          int x[10];
    const int* p = shift_left_digits(a, a + 3, -1, x);
    ASSERT_EQ(2, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}



// ------------------
// shift_right_digits
// ------------------

TEST(Integer, shift_right_digits_1) {
    const int a[] = {2, 3, 4};
    const int b[] = {2};
          int x[10];
    const int* p = shift_right_digits(a, a + 3, 2, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

TEST(Integer, shift_right_digits_2) {
    const int a[] = {2, 3, 4};
    const int b[] = {2, 3, 4};
          int x[10];
    const int* p = shift_right_digits(a, a + 3, 0, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

TEST(Integer, shift_right_digits_3) {
    const int a[] = {2, 3, 4};
    const int b[] = {2, 3, 4, 0};
          int x[10];
    const int* p = shift_right_digits(a, a + 3, -1, x);
    ASSERT_EQ(4, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));}

// -----------
// plus_digits
// -----------

TEST(Integer, plus_digits_1) {
    const int a[] = {2, 3, 4};
    const int b[] = {5, 6, 7};
    const int c[] = {8, 0, 1};
          int x[10];
    const int* p = plus_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, plus_digits_2) {
    const int a[] = {2, 3, 4};
    const int b[] = {0};
    const int c[] = {2, 3, 4};
          int x[10];
    const int* p = plus_digits(a, a + 3, b, b + 1, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, plus_digits_3) {
    const int a[] = {9, 9, 9, 9};
    const int b[] = {1, 1};
    const int c[] = {1, 0, 0, 1, 0};
          int x[10];
    const int* p = plus_digits(a, a + 4, b, b + 2, x);
    ASSERT_EQ(5, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

// ------------
// minus_digits
// ------------

TEST(Integer, minus_digits_1) {
    const int a[] = {8, 0, 1};
    const int b[] = {5, 6, 7};
    const int c[] = {2, 3, 4};
          int x[10];
    const int* p = minus_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, minus_digits_2) {
    const int a[] = {1, 0, 0, 0, 0};
    const int b[] = {1};
    const int c[] = {9, 9, 9, 9};
          int x[10];
    const int* p = minus_digits(a, a + 5, b, b + 1, x);
    ASSERT_EQ(4, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, minus_digits_3) {
    const int a[] = {9, 9, 9};
    const int b[] = {9, 9, 9};
    const int c[] = {0};
          int x[10];
    const int* p = minus_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}    


TEST(Integer, minus_digits_4) {
    const int a[] = {1, 3, 6, 0};
    const int b[] = {5, 6, 7};
    const int c[] = {7, 9, 3};
          int x[10];
    const int* p = minus_digits(a, a + 4, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

// -----------------
// multiplies_digits
// -----------------

TEST(Integer, multiplies_digits_1) {
    const int a[] = {2, 3, 4};
    const int b[] = {5, 6, 7};
    const int c[] = {1, 3, 2, 6, 7, 8};
          int x[10];
    const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
    ASSERT_EQ(6, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, multiplies_digits_2) {
    const int a[] = {2, 3, 4};
    const int b[] = {0};
    const int c[] = {0};
          int x[10];
    const int* p = multiplies_digits(a, a + 3, b, b + 1, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

TEST(Integer, multiplies_digits_3) {
    const int a[] = {2, 3, 4};
    const int b[] = {1, 2, 3, 4};
    const int c[] = {2, 8, 8, 7, 5, 6};
          int x[10];
    const int* p = multiplies_digits(a, a + 3, b, b + 4, x);
    ASSERT_EQ(6, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}


TEST(Integer, multiplies_digits_4) {
    const int a[] = {4, 0, 9, 6};
    const int b[] = {4, 0, 9, 6};
    const int c[] = {1, 6, 7, 7, 7, 2, 1, 6};
          int x[10];
    const int* p = multiplies_digits(a, a + 4, b, b + 4, x);
    ASSERT_EQ(8, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}


// --------------
// divides_digits
// --------------

TEST(Integer, divides_digits_1) {
    const int a[] = {1, 3, 2, 6, 7, 8};
    const int b[] = {5, 6, 7};
    const int c[] = {2, 3, 4};
          int x[10];
    const int* p = divides_digits(a, a + 6, b, b + 3, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

    TEST(Integer, divides_digits_2) {
    const int a[] = {5, 6, 7};
    const int b[] = {1, 3, 2, 6, 7, 8};
    const int c[] = {0};
          int x[10];
    const int* p = divides_digits(a, a + 3, b, b + 6, x);
    ASSERT_EQ(1, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

    TEST(Integer, divides_digits_3) {
    const int a[] = {1, 2, 3};
    const int b[] = {6};
    const int c[] = {2, 0};
          int x[10];
    const int* p = divides_digits(a, a + 3, b, b + 1, x);
    ASSERT_EQ(2, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, c));}

// -----------
// constructor
// -----------

TEST(Integer, constructor_1) {
    try {
        const Integer<int> x("abc");
        ASSERT_TRUE(false);}
    catch (std::invalid_argument& e) {
        ASSERT_STREQ("Integer()", e.what());}}

TEST(Integer, constructor_2) {
    try {
        const Integer<int> x("10");}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, constructor_3) {
    try {
        const Integer<int> x(10);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// ---
// abs
// ---

TEST(Integer, abs_1) {
    try {
        Integer<int>  x = -98765;
        Integer<int>& y = x.abs();
        ASSERT_EQ(98765, x);
        ASSERT_EQ(&x,    &y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, abs_2) {
    try {
        const Integer<int> x = -98765;
        const Integer<int> y = abs(x);
        ASSERT_EQ(-98765, x);
        ASSERT_EQ( 98765, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, abs_3) {
    try {
        const Integer<int> x = 0;
        const Integer<int> y = abs(x);
    ASSERT_EQ(0, x);
        ASSERT_EQ(0, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}        

// --------
// equal_to
// --------

TEST(Integer, equal_to_1) {
    try {
        const Integer<int> x = 98765;
        const Integer<int> y = 98765;
        ASSERT_TRUE(x == y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, equal_to_2) {
    try {
        const Integer<int> x = -98765;
        const Integer<int> y = 98765;
        ASSERT_FALSE(x == y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, equal_to_3) {
    try {
        const Integer<int> x = 345645;
        const Integer<int> y = 8979;
        ASSERT_FALSE(x == y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// --------
// less_than
// --------

TEST(Integer, less_than_1) {
    try {
        const Integer<int> x = 98764;
        const Integer<int> y = 98765;
        ASSERT_TRUE(x < y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, less_than_2) {
    try {
        const Integer<int> x = -98765;
        const Integer<int> y = -100;
        ASSERT_TRUE(x < y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, less_than_3) {
    try {
        const Integer<int> x = -1000;
        const Integer<int> y = 1000;
        ASSERT_TRUE(x < y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}



// --------
// negation
// --------

TEST(Integer, negation_1) {
    try {
        const Integer<int> x = 98765;
        const Integer<int> y = -x;
        ASSERT_EQ(-98765, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, negation_2) {
    try {
        const Integer<int> x = -98765;
        const Integer<int> y = -x;
        ASSERT_EQ(98765, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, negation_3) {
    try {
        const Integer<int> x = 0;
        const Integer<int> y = -x;
        ASSERT_EQ(0, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}


// --------
// plus_equals
// --------

TEST(Integer, plus_equals_1) {
    try {
        Integer<int> x = -123;
        const Integer<int> y = -234;
        Integer<int> z = x+=y;
        ASSERT_EQ(x, -357);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, plus_equals_2) {
    try {
        Integer<int> x = -234;
        const Integer<int> y = 123;
        Integer<int> z = x+=y;
        ASSERT_EQ(x, -111);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, plus_equals_3) {
    try {
        Integer<int> x = -123;
        const Integer<int> y = 234;
        Integer<int> z = x+=y;
        ASSERT_EQ(x, 111);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// --------
// minus_equals
// --------

TEST(Integer, minus_equals_1) {
    try {
        Integer<int> x = -123;
        const Integer<int> y = -234;
        Integer<int> z = (x-=y);
        ASSERT_EQ(x, 111);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, minus_equals_2) {
    try {
        Integer<int> x = -234;
        const Integer<int> y = -123;
        Integer<int> z = x-=y;
        ASSERT_EQ(x, -111);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, minus_equals_3) {
    try {
        Integer<int> x = 123;
        const Integer<int> y = -234;
        Integer<int> z = x-=y;
        ASSERT_EQ(x, 357);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}


// --------
// times_equals
// --------

TEST(Integer, times_equals_1) {
    try {
        Integer<int> x = 123;
        const Integer<int> y = 234;
        Integer<int> z = x*=y;
        ASSERT_EQ(x, 28782);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, times_equals_2) {
    try {
        Integer<int> x = 123;
        const Integer<int> y = 0;
        Integer<int> z = x*=y;
        ASSERT_EQ(x, 0);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, times_equals_3) {
    try {
        Integer<int> x = 123;
        const Integer<int> y = -234;
        Integer<int> z = x*=y;
        ASSERT_EQ(x, -28782);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, times_equals_4) {
    try {
        Integer<int> x = 4096;
        const Integer<int> y = 4096;
        Integer<int> z = x*=y;
        ASSERT_EQ(x, 16777216);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}



// --------
// divide_equals
// --------

TEST(Integer, divide_equals_1) {
    try {
        Integer<int> x = 222;
        const Integer<int> y = 111;
        Integer<int> z = x/=y;
        ASSERT_EQ(x, 2);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, divide_equals_2) {
    try {
        Integer<int> x = -123;
        const Integer<int> y = 0;
        Integer<int> z = x/=y;
        ASSERT_TRUE(false);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(true);}}

TEST(Integer, divide_equals_3) {
    try {
        Integer<int> x = 223;
        const Integer<int> y = -2;
        Integer<int> z = x/=y;
        ASSERT_EQ(x, -111);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}


// --------
// mod_equals
// --------

TEST(Integer, mod_equals_1) {
    try {
    Integer<int> x = 123;
        const Integer<int> y = 10;
        Integer<int> z = x%=y;
        ASSERT_EQ(x, 3);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, mod_equals_2) {
    try {
        Integer<int> x = -123;
        const Integer<int> y = 10;
        Integer<int> z = x%=y;
        ASSERT_EQ(x, 7);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, mod_equals_3) {
    try {
        Integer<int> x = 123;
        const Integer<int> y = -234;
        Integer<int> z = x%=y;
        ASSERT_TRUE(false);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(true);}}

// --------
// left_shift_equals
// --------

TEST(Integer, left_shift_equals_1) {
    try {
        Integer<int> x = -123;
        int y = 2;
        Integer<int> z = (x <<= y);
        ASSERT_EQ(x, -12300);
        ASSERT_EQ(z, -12300);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, left_shift_equals_2) {
    try {
        Integer<int> x = -123;
        int y = 0;
        Integer<int> z = (x <<= y);
        ASSERT_EQ(x, -123);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, left_shift_equals_3) {
    try {
        Integer<int> x = 123;
        int y = -2;
        Integer<int> z = (x <<= y);
        ASSERT_EQ(x, 1);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// --------
// right_shift_equals
// --------

TEST(Integer, right_shift_equals_1) {
    try {
        Integer<int> x = -123;
        int y = 2;
        Integer<int> z = (x >>= y);
        ASSERT_EQ(x, -1);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, right_shift_equals_2) {
    try {
        Integer<int> x = -123;
        int y = 0;
        Integer<int> z = (x >>= y);
        ASSERT_EQ(x, -123);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, right_shift_equals_3) {
    try {
        Integer<int> x = 123;
        int y = -2;
        Integer<int> z = (x >>= y);
        ASSERT_EQ(x, 12300);
        ASSERT_EQ(x, z);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}


// ------
// output
// ------

TEST(Integer, output_1) {
    try {
        const Integer<int> x = 10;
        std::ostringstream out;
        out << x;
        ASSERT_EQ("10", out.str());}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, output_2) {
    try {
        const Integer<int> x = -123;
        std::ostringstream out;
        out << x;
        ASSERT_EQ("-123", out.str());}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, output_3) {
    try {
        const Integer<int> x = 0;
        std::ostringstream out;
        out << x;
        ASSERT_EQ("0", out.str());}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

// ---
// pow
// ---

TEST(Integer, pow_1) {
    try {
        Integer<int>       x = 2;
        const int          e = 24;
        Integer<int>&      y = x.pow(e);
    ASSERT_EQ(      24,  e);
        ASSERT_EQ(16777216,  x);
        ASSERT_EQ(  &x, &y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, pow_2) {
    try {
        const Integer<int> x = -9;
        const int          e =  5;
        const Integer<int> y = pow(x, e);
        ASSERT_EQ(    -9, x);
        ASSERT_EQ(     5, e);
        ASSERT_EQ(-59049, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}

TEST(Integer, pow_3) {
    try {
        const Integer<int> x =  -7;
        const int          e =  -1;
        const Integer<int> y = pow(x, e);
        ASSERT_TRUE(false);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(true);}} 


TEST(Integer, pow_4) {
    try {
        const Integer<int> x = 2;
        const int          e = 15;
        const Integer<int> y = pow(x, e);
        ASSERT_EQ(      2, x);
        ASSERT_EQ(     15, e);
        ASSERT_EQ(32768, y);}
    catch (std::invalid_argument& e) {
        ASSERT_TRUE(false);}}


       
