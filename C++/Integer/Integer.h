// --------------------------
// projects/integer/Integer.h
// Copyright (C) 2014
// Glenn P. Downing
// --------------------------

#ifndef Integer_h
#define Integer_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>    // string
#include <vector>    // vector

using namespace std;


// -----------------
// shift_left_digits
// -----------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift left of the input sequence into the output sequence
 * ([b, e) << n) => x
 */
template <typename II, typename FI>
FI shift_left_digits (II b, II e, int n, FI x) {
    if(n < 0){
        II c = b;
        int size = 0;
        while(c != e){
            ++c;
            ++size;
        }
        assert(size >= -n);
        while(size > -n){
            *x = *b;
            ++b;
            ++x;
            --size;
        }
        return x;
    }
    FI y = copy(b, e, x);
    FI z = y;
    advance(z, n);
    fill(y, z, typename iterator_traits<II>::value_type());
    return z;
}

// ------------------
// shift_right_digits
// ------------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift right of the input sequence into the output sequence
 * ([b, e) >> n) => x
 */
template <typename II, typename FI>
FI shift_right_digits (II b, II e, int n, FI x) {
    return shift_left_digits(b, e, -n, x);
}

// -----------
// plus_digits
// -----------

/**
 * Both are treated as positive numbers
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the sum of the two input sequences into the output sequence
 * ([b1, e1) + [b2, e2)) => x
 */
template <typename BI1, typename BI2, typename FI>
FI plus_digits (BI1 b1, BI1 e1, BI2 b2, BI2 e2, FI x) {
    int c = 0;
    int size = 0;
    vector<int> temp;
    while(b1 != e1 || b2 != e2){
        if(b1 != e1 && b2 != e2){
            --e1;
            --e2;
            temp.push_back(*e1 + *e2);
        }
        else if(b1 != e1){
            --e1;
            temp.push_back(*e1);
        }
        else{
            --e2;
            temp.push_back(*e2);
        }
        if(c == 1)
            ++temp[size];
        if(temp[size] > 9){
            c = 1;
            temp[size] %= 10;
        }
        else
            c = 0;
        ++size;
    }
    //Take care of last carry
    if(c == 1){
        temp.push_back(typename iterator_traits<FI>::value_type());
        ++temp[size];
        ++size;
    }
    while(size > 0){
        --size;
        *x = temp[size];
        assert(*x >= 0 && *x < 10);
        ++x;
    }
    return x;
}


// ------------
// minus_digits
// ------------

/**
 * First must be greater than or equal to the second
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the difference of the two input sequences into the output sequence
 * ([b1, e1) - [b2, e2)) => x
 */
template <typename BI1, typename BI2, typename FI>
FI minus_digits (BI1 b1, BI1 e1, BI2 b2, BI2 e2, FI x) {
    int size = 0;
    int index = 0;
    BI1 a1 = b1;
    while(a1 != e1){
        ++a1;
        ++size;
    }
    vector<int> temp(size,0);
    while(b1 != e1){
        if(b2 != e2){
            --e1;
            --e2;
            if(*e1 < *e2){
                temp[index] += ((*e1 + 10) - *e2);
                --temp[index + 1];
            }
        else if(*e1 == *e2 && temp[index] < 0){
        temp[index] += ((*e1 + 10) - *e2);
                --temp[index + 1];
        }
            else
                temp[index] += (*e1 - *e2);
        }
        else{
            --e1;
            if(temp[index] + *e1 < 0){
                --temp[index + 1];
            temp[index] += (*e1 + 10);
        }
            else    
                temp[index] += (*e1);
        }
        ++index;
    }
    // Take care of leading 0's
    while(index > 0){
    if(temp[temp.size()-1] == 0){
        temp.pop_back();
        --index;
    }
    else
        index = -1;
    }
    size = temp.size();
    if(size == 0){ // is 0
        *x = typename iterator_traits<FI>::value_type();
    ++x;
    return x;
    }
    while(size > 0){
        --size;
        *x = temp[size];
        assert(*x >= 0 && *x < 10);
        ++x;
    }
    return x;
}

// -----------------
// multiplies_digits
// -----------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the product of the two input sequences into the output sequence
 * ([b1, e1) * [b2, e2)) => x
 */
template <typename BI1, typename BI2, typename FI>
FI multiplies_digits (BI1 b1, BI1 e1, BI2 b2, BI2 e2, FI x) {
    vector< vector<int> > lookup;
    vector<int> n0; lookup.push_back(n0);
    vector<int> n1; lookup.push_back(n1);
    vector<int> n2; lookup.push_back(n2);
    vector<int> n3; lookup.push_back(n3);
    vector<int> n4; lookup.push_back(n4);
    vector<int> n5; lookup.push_back(n5);
    vector<int> n6; lookup.push_back(n6);
    vector<int> n7; lookup.push_back(n7);
    vector<int> n8; lookup.push_back(n8);
    vector<int> n9; lookup.push_back(n9);
    int sizeOfTop = 0;
    int sizeOfBot = 0;
    BI1 a1 = b1;
    BI2 a2 = b2;
    while(a1 != e1 || a2 != e2){
        if(a1 != e1){
            ++sizeOfTop;
            ++a1;
        }
        if(a2 != e2){
            ++a2;
            ++sizeOfBot;
        }
    }
    // Now I have the sizes of the top and bot
    for(int i = 0; i <= 9; ++i){
//cout << "On spot " << i << " in the lookup table:" << endl;
        vector<int> t(sizeOfBot+sizeOfTop, 0);
        // Fill the vector
        BI1 f1 = e1;
        int index = 0;
        while(b1 != f1){
            --f1;
            // Simple mult going backwards
            int m = i*(*f1);
            t[index] += (m % 10);
            if(t[index] > 9){
                ++t[index + 1];
                t[index] %= 10;
            }
            t[index + 1] += (m / 10);
            ++index;
        }
        // Remove 0s at the end
        while(t[t.size()-1] == 0 && t.size() > 1)
            t.pop_back();
//cout << "Digits are: ";
        while(t.size() > 0){
            lookup[i].push_back(t[t.size() - 1]);
//cout << t[t.size() - 1] << " ";
            t.pop_back();
        }
//cout << endl;
    }
    vector<int> total(1,0);
    // Now loop through and call the lookup, 
    // then left shift that answer, 
    // then add it to total
    int factor = 0;
    while(b2 != e2){
        --e2;
        //Lookup
	vector<int> part(lookup[*e2].size()+factor,0);
        // Left shift
        shift_left_digits (lookup[*e2].begin(), lookup[*e2].end(), factor, part.begin());
        vector<int> result(sizeOfBot+sizeOfTop, 0);
        vector<int>::iterator it = plus_digits(part.begin(), part.end(), total.begin(), total.end(), result.begin());
        // Remove ending zeros
        int rem = result.size() - (it-result.begin());
        for(int  i = 0; i < rem; ++i)
            result.pop_back();
        // Make total equal result
        total.clear();
        rem = result.size();
        for(int  i = 0; i < rem; ++i)
            total.push_back(result[i]);
        ++factor;
    }
    // Make x equal total
    int spot = 0;
    int tsize = total.size();
    while(spot < tsize){
        *x = total[spot];
        ++x;
        ++spot;
    }

    return x;
}




// --------------
// divides_digits
// --------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the division of the two input sequences into the output sequence
 * ([b1, e1) / [b2, e2)) => x
 */
template <typename II1, typename II2, typename FI>
FI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, FI x) {
    vector<int> c;
    vector<int> a2;
    while(b2 != e2){
        a2.push_back(*b2);
        ++b2;
    }
    bool firstTime = true;
    int size2 = a2.size();
    while(b1 != e1){
        assert(b1 != e1);
        int pushed = c.size();
        while(pushed <= size2 && (pushed < size2 || !firstTime) && b1 != e1){
            // Add next digits to c
            c.push_back(*b1);
            ++b1;
            ++pushed;
        }
        assert(pushed > 0);
        if(firstTime && b1 != e1){
            int i = 0;
        bool stop = false;
            while(i < pushed && !stop){
                if(c[i] < a2[i]){
                    c.push_back(*b1);
                    stop = true;
                    ++b1;
                }
                else if(c[i] > a2[i]){
                    stop = true;
                }
            ++i;
            }
        }
        firstTime = false;
        // Now c and II2 are the same size
        // Check if 0
        int index = 0;
        int sizec = c.size();
        int value = 0;
        bool printed = false;
        bool next = false;
        while(!printed){
            if(value > 9){
                cout << "We have failed" << endl;
                return x;
            }
        sizec = c.size();
        sizec = c.size();
        // Check if c is less than a2       
            index = 0;
            next = false;
            sizec = c.size();
            if(sizec == size2){
                while(index < sizec && !printed && !next){
                    if(c[index] < a2[index] && !printed){
                        *x = value;
            ++x;
                        printed = true;
                    }
                    else if(c[index] > a2[index])
                        next = true;
                    ++index;
                }
            }
            else if(sizec < size2){
                *x = value;
                ++x;
                printed = true;
            }
            // If it was greater than, so not printed
            if(!printed){
                // Subtract once from c
                vector<int> result(c.size() , 0);
                vector<int>::iterator it = minus_digits(c.begin(), c.end(), a2.begin(), a2.end(), result.begin());
                //Remove extra spots at end
                int rem = result.size() - (it-result.begin());
                for(int  i = 0; i < rem; ++i)
                    result.pop_back();
                
                // Make c into result
                index = 0;
                c.clear();
                if(!(result.size() == 1 && result[0] == 0)){
                    int sizer = result.size();
                    while(index < sizer){
                        c.push_back(result[index]);
                        ++index;
                    }
                }
                else
                firstTime = true;
            }
        ++value;
        }
    }            
    return x;


}

// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer {
    // -----------
    // operator ==
    // -----------

    /**
     *  Equal equals
     *  @param lhs  the left Integer called by reference, constant  
     *  @param rhs  the right Integer called by reference, constant 
     *  @return     a bool indicating if the lhs and rhs are equal
     */
    friend bool operator == (const Integer& lhs, const Integer& rhs) {
        if(lhs.sign != rhs.sign)
            return false;        
        if(lhs._x.size() != rhs._x.size())
            return false;
        assert(lhs.sign == rhs.sign);
        assert(lhs._x.size() == rhs._x.size());
        int size = lhs._x.size();
        for(int i = 0; i < size; ++i){
            if(lhs._x[i] != rhs._x[i])
                return false;
        }
        return true;
    }

    // -----------
    // operator !=
    // -----------

    /**
     *  Not equals
     *  @param lhs  the left Integer called by reference, constant 
     *  @param rhs  the right Integer called by reference, constant 
     *  @return     a bool indicating if the lhs and rhs are not equal
     */
    friend bool operator != (const Integer& lhs, const Integer& rhs) {
        return !(lhs == rhs);}

    // ----------
    // operator <
    // ----------

    /**
     *  Less than
     *  @param lhs  the left Integer called by reference, constant 
     *  @param rhs  the right Integer called by reference, constant 
     *  @return     a bool indicating if the lhs is less than the rhs
     */
    friend bool operator < (const Integer& lhs, const Integer& rhs) {
        if(lhs.sign && !rhs.sign)
            return false;
        if(!lhs.sign && rhs.sign)
            return true;
        assert(lhs.sign == rhs.sign);
        // Both positive
        if(lhs.sign && rhs.sign){
            if(lhs._x.size() < rhs._x.size())
                return true;
            else if(lhs._x.size() > rhs._x.size())
                return false;
            else{
                //Same # of digits
                int size = lhs._x.size();
                for(int i = 0; i < size; ++i){
                    if(lhs._x[i] < rhs._x[i])
                        return true;
                    else if(lhs._x[i] > rhs._x[i])
                        return false;
                }
            }
            return false;
        }
        else{ // Both Negative
            if(lhs._x.size() < rhs._x.size())
                return false;
            else if(lhs._x.size() > rhs._x.size())
                return true;
            else{
                //Same # of digits
                int size = lhs._x.size();
                for(int i = 0; i < size; ++i){
                    if(lhs._x[i] < rhs._x[i])
                        return false;
                    else if(lhs._x[i] > rhs._x[i])
                        return true;
                }
            }
            return false;
        }
    }

    // -----------
    // operator <=
    // -----------

    /**
     *  Less than or equals
     *  @param lhs  the left Integer called by reference, constant 
     *  @param rhs  the right Integer called by reference, constant 
     *  @return     a bool indicating if the lhs is less than or equal to the rhs
     */
    friend bool operator <= (const Integer& lhs, const Integer& rhs) {
        return !(rhs < lhs);}

    // ----------
    // operator >
    // ----------

    /**
     *  Greater than
     *  @param lhs  the left Integer called by reference, constant 
     *  @param rhs  the right Integer called by reference, constant 
     *  @return     a bool indicating if the lhs is greater than the rhs
     */
    friend bool operator > (const Integer& lhs, const Integer& rhs) {
        return (rhs < lhs);}

    // -----------
    // operator >=
    // -----------

    /**
     *  Greater than or equals
     *  @param lhs  the left Integer called by reference, constant 
     *  @param rhs  the right Integer called by reference, constant 
     *  @return     a bool indicating if the lhs is greater than or equal to the rhs
     */
    friend bool operator >= (const Integer& lhs, const Integer& rhs) {
        return !(lhs < rhs);}

    // ----------
    // operator +
    // ----------

    /**
     *  Addition
     *  @param lhs  the left Integer called by value
     *  @param rhs  the right Integer called by reference, constant 
     *  @return     an Integer representing the sum of the lhs and rhs
     */
    friend Integer operator + (Integer lhs, const Integer& rhs) {
        return lhs += rhs;}

    // ----------
    // operator -
    // ----------

    /**
     *  Subtraction
     *  @param lhs  the left Integer called by value
     *  @param rhs  the right Integer called by reference, constant 
     *  @return     an Integer representing the lhs minus the rhs
     */
    friend Integer operator - (Integer lhs, const Integer& rhs) {
        return lhs -= rhs;}

    // ----------
    // operator *
    // ----------

    /**
     *  Multiplication
     *  @param lhs  the left Integer called by value
     *  @param rhs  the right Integer called by reference, constant 
     *  @return     an Integer representing the lhs times the rhs
     */
    friend Integer operator * (Integer lhs, const Integer& rhs) {
        return lhs *= rhs;}

    // ----------
    // operator /
    // ----------

    /**
     *  Division
     *  @param lhs  the left Integer called by value
     *  @param rhs  the right Integer called by reference, constant 
     *  @return     an Integer representing the lhs divided by the rhs
     *  @throws invalid_argument if (rhs == 0)
     */
    friend Integer operator / (Integer lhs, const Integer& rhs) {
        return lhs /= rhs;}

    // ----------
    // operator %
    // ----------

    /**
     *  Modulo
     *  @param lhs  the left Integer called by value
     *  @param rhs  the right Integer called by reference, constant 
     *  @return     an Integer representing the lhs mod the rhs
     *  @throws invalid_argument if (rhs <= 0)
     */
    friend Integer operator % (Integer lhs, const Integer& rhs) {
        return lhs %= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     *  Left digit shift
     *  @param lhs  the left Integer called by value
     *  @param rhs  an int amount for lhs to be shifted
     *  @return     an Integer representing the lhs shifted rhs times to the left
     *  @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator << (Integer lhs, int rhs) {
        return lhs <<= rhs;}

    // -----------
    // operator >>
    // -----------

    /**
     *  Right digit shift
     *  @param lhs  the left Integer called by value
     *  @param rhs  an int amount for lhs to be shifted
     *  @return     an Integer representing the lhs shifted rhs times to the right
     *  @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator >> (Integer lhs, int rhs) {
        return lhs >>= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     *  Insert output
     *  @param lhs  an ostream called by reference
     *  @param rhs  the right Integer called by reference, constant 
     *  @return     an ostream with the rhs written to it
     */
    friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
    if(rhs.sign == false){
        lhs << "-";
    }
    int size = rhs._x.size();
    for(int i = 0; i < size; ++i){
            lhs << rhs._x[i];
        }
        return lhs;
    }

    // ---
    // abs
    // ---

    /**
     *  Absolute value
     *  @param x    an Integer called by value 
     *  @return     an Integer representing |x|
     */
    friend Integer abs (Integer x) {
        return x.abs();}

    // ---
    // pow
    // ---

    /**
     *  Power
     *  @param x    an Integer called by value 
     *  @param e    an int to be the exponent
     *  @return     an Integer representing x^e
     *  @throws invalid_argument if ((x == 0) && (e == 0)) || (e < 0)
     */
    friend Integer pow (Integer x, int e) {
        return x.pow(e);

    }

    private:
        // ----
        // data
        // ----

        C _x; // the backing container
        bool sign; // if positive sign = true, negative sign = false;

    private:
        // -----
        // valid
        // -----

        bool valid () const { // class invariant
            int size = _x.size();
        if(size == 0)
        return false;
        int i = 0;
        while(i < size){
        if(_x.at(i) > 9 || _x.at(i) < 0)
            return false;
        ++i;    
        }    
            return true;
    }

    public:
        // ------------
        // constructors
        // ------------

        /**
         *  Creates an Integer from an int value given
         */
        Integer (int value) {
            sign = true;
            if(value < 0){
                sign = false;
                value = -value;
            }
            if(value == 0)
        _x.push_back(0);
            if(value != 0){
            vector<int> v;
                while(value > 0){
                    v.push_back(value%10);
                    value = value / 10;
                }
                while(v.size() > 0){
                    _x.push_back(v[v.size()-1]);
                    v.pop_back();
                } 
            }
            assert(valid());
        }

        /**
         *  Creates an Integer from a string
         *  @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            int size = value.size();
            if (size == 0)
                throw std::invalid_argument("Integer()");
            int i = 0;
            if(value.at(i) == '-'){
                ++i;
                sign = false;
            }
            while(i < size){
                _x.push_back(value.at(i)-'0');
        ++i;
            }
            if (!valid())
                throw std::invalid_argument("Integer()");
        }

        // Default copy, destructor, and copy assignment.
        // Integer (const Integer&);
        // ~Integer ();
        // Integer& operator = (const Integer&);

        // ----------
        // operator -
        // ----------

        /**
         *  Negation
         *  @return     the negated version of this Integer
         *  Integer not changed
         */
        Integer operator - () const {
            // Flip the sign if the value isn't 0
            if(this->_x.at(0) == 0)
                return Integer(0);
            Integer x = *this;
            x.sign = !(x.sign);
            return x;
        }

        // -----------
        // operator ++
        // -----------

        /**
         *  Pre-increment
         *  @return     the Integer after the increment
         *  This Integer is increased by 1
         */
        Integer& operator ++ () {
            *this += 1;
            return *this;}

        /**
         *  Post-increment
         *  @return     the Integer before the increment
         *  This Integer is increased by 1
         */
        Integer operator ++ (int) {
            Integer x = *this;
            ++(*this);
            return x;}

        // -----------
        // operator --
        // -----------

        /**
         *  Pre-decrement
         *  @return     the Integer after the decrement
         *  This Integer is decreased by 1
         */
        Integer& operator -- () {
            *this -= 1;
            return *this;}

        /**
         *  Post-decrement
         *  @return     the Integer before the decrement
         *  This Integer is decreased by 1
         */
        Integer operator -- (int) {
            Integer x = *this;
            --(*this);
            return x;}

        // -----------
        // operator +=
        // -----------

        /**
         *  Plus-equals
         *  @param rhs  an Integer called by reference, constant 
         *  @return     the Integer plus the rhs
         *  This Integer is increased by rhs
         */
        Integer& operator += (const Integer& rhs) {
        Integer x = *this;
            typename C::iterator it;
            int size;
            // Same sign, you plus_digits and don't mess with sign
            if((this->sign && rhs.sign) || (!this->sign && !rhs.sign)){
                this->_x.push_back(0);
                size = this->_x.size();
                it = plus_digits (x._x.begin(), x._x.end(), rhs._x.begin(), rhs._x.end(), this->_x.begin());
                //Remove extra zero
                if(it - this->_x.begin() != size)
                    this->_x.pop_back();
                return *this;
            }
            // If this positive and rhs negative
            else if(this->sign && !rhs.sign){
                size = this->_x.size();
                if(-(*this) < rhs){ // this - rhs
                    it = minus_digits (x._x.begin(), x._x.end(), rhs._x.begin(), rhs._x.end(), this->_x.begin());
                }
                else if((-*this) > rhs){ // rhs - this and this becomes -
                    it = minus_digits (rhs._x.begin(), rhs._x.end(), x._x.begin(), x._x.end(), this->_x.begin());
                    this->sign = false;
                }
                else{
                    *this = Integer(0);
                    return *this;
                }
                while((it - this->_x.begin()) < size){
                        this->_x.pop_back();
                        --size;
                }
                return *this;
            }
            // If this negative and rhs positive
            else{
                size = this->_x.size();
                if((-*this) > rhs){ // this - rhs
                    it = minus_digits (x._x.begin(), x._x.end(), rhs._x.begin(), rhs._x.end(), this->_x.begin());
                }
                else if((-*this) < rhs){ //rhs - this and this becomes +
                    it = minus_digits (rhs._x.begin(), rhs._x.end(), x._x.begin(), x._x.end(), this->_x.begin());
                    this->sign = true;
                }
                else{
                    *this = Integer(0);
                    return *this;
                }
                while((it - this->_x.begin()) < size){
                        this->_x.pop_back();
                        --size;
                }
                return *this;
            }
        }


        // -----------
        // operator -=
        // -----------

        /**
         *  Minus-equals
         *  @param rhs  an Integer called by reference, constant 
         *  @return     the Integer minus the rhs
         *  This Integer is decreased by rhs
         */
        Integer& operator -= (const Integer& rhs) {
            Integer x = *this;
            typename C::iterator it;
            int size;
            // Different signs, you plus_digits and don't mess with sign
            if((!this->sign && rhs.sign) || (this->sign && !rhs.sign)){
                this->_x.push_back(0);
                size = this->_x.size();
                it = plus_digits (x._x.begin(), x._x.end(), rhs._x.begin(), rhs._x.end(), this->_x.begin());
                //Remove extra zero
                if(it - this->_x.begin() != size)
                    this->_x.pop_back();
                return *this;
            }
            // If both positive
            else if(this->sign && rhs.sign){
                size = this->_x.size();
                if(*this > rhs){ // this - rhs
                    it = minus_digits (x._x.begin(), x._x.end(), rhs._x.begin(), rhs._x.end(), this->_x.begin());
                }
                else if(*this < rhs){ // rhs - this and this becomes -
                    it = minus_digits (rhs._x.begin(), rhs._x.end(), x._x.begin(), x._x.end(), this->_x.begin());
                    this->sign = false;
                }
                else{
                    *this = Integer(0);
                    return *this;
                }
                while((it - this->_x.begin()) < size){
                        this->_x.pop_back();
                        --size;
                }
                return *this;
            }
            // If both negative
            else{
                size = this->_x.size();
                if(*this < rhs){ // this - rhs
                    it = minus_digits (x._x.begin(), x._x.end(), rhs._x.begin(), rhs._x.end(), this->_x.begin());
                }
                else if(*this > rhs){ //rhs - this and this becomes +
                    it = minus_digits (rhs._x.begin(), rhs._x.end(), x._x.begin(), x._x.end(), this->_x.begin());
                    this->sign = true;
                }
                else{
                    *this = Integer(0);
                    return *this;
                }
                while((it - this->_x.begin()) < size){
                        this->_x.pop_back();
                        --size;
                }
                return *this;
            }
        }

        // -----------
        // operator *=
        // -----------

        /**
         *  Times-equals
         *  @param rhs  an Integer called by reference, constant 
         *  @return     the Integer times the rhs
         *  This Integer is multiplied by the rhs
         */
        Integer& operator *= (const Integer& rhs) {
            if((!this->sign && rhs.sign) || (this->sign && !rhs.sign))
                this->sign = false;
            else
                this->sign = true;
            Integer x = *this;
            int size = this->_x.size() + rhs._x.size();
            while(size > 0){
                this->_x.push_back(0);
                --size;
            }
            size = this->_x.size();
            typename C::iterator it = multiplies_digits (x._x.begin(), x._x.end(), rhs._x.begin(), rhs._x.end(), this->_x.begin());
            while((it - this->_x.begin()) < size){
                this->_x.pop_back();
                --size;
            }
            return *this;
        }

        // -----------
        // operator /=
        // -----------

        /**
         *  Divide-equals
         *  @param rhs  an Integer called by reference, constant 
         *  @return     the Integer divided by the rhs
         *  This Integer is divided by the rhs
         *  @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (const Integer& rhs) {
            if(rhs == Integer(0))
                throw std::invalid_argument("Integer()");
            if((!this->sign && rhs.sign) || (this->sign && !rhs.sign))
                this->sign = false;
            else
                this->sign = true;
            Integer x = *this;
            int size = this->_x.size();
            typename C::iterator it = divides_digits (x._x.begin(), x._x.end(), rhs._x.begin(), rhs._x.end(), this->_x.begin());
            while((it - this->_x.begin()) < size){
                this->_x.pop_back();
                --size;
            }
            return *this;
        }

        // -----------
        // operator %=
        // -----------

        /**
         *  Mod-equals
         *  @param rhs  an Integer called by reference, constant 
         *  @return     the Integer mod the rhs
         *  This Integer is taken mod the rhs
         *  @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (const Integer& rhs) {
        if(rhs <= Integer(0))
                throw std::invalid_argument("Integer()");
            bool flip = !(this->sign);
            // Keep divide equals until less than rhs
            this->sign = true;
        while(*this > rhs){
                *this -= rhs;
            }
            // if sign is negative add rhs to the original answer
            if(flip)
                *this = rhs - *this;
            return *this;
    }
        // ------------
        // operator <<=
        // ------------

        /**
         *  Left-shift-equals
         *  @param n    an int for this to be shifted by 
         *  @return     the Integer shifted to the left n times
         *  This Integer is shifted to left n times
         */
        Integer& operator <<= (int n) {
            Integer x = *this;
        if(n > 0){
                // Add
                for(int i = 0; i < n; ++i)
                    this->_x.push_back(0);
        }
            else if(n < 0){
                //Remove
                for(int i = 0; i < (-n); ++i){
                    if(this->_x.size() > 1)
            this->_x.pop_back();
        }
            }
            else{
                return *this;
            }
            shift_left_digits(x._x.begin(), x._x.end(), n, this->_x.begin());            
        return *this;
        }

        // ------------
        // operator >>=
        // ------------

        /**
         *  Right-shift-equals
         *  @param n    an int for this to be shifted by 
         *  @return     the Integer shifted to the right n times
         *  This Integer is shifted to right n times
         */
        Integer& operator >>= (int n) {
            Integer x = *this;
            if(n < 0){
                // Add n spots
                for(int i = 0; i < (-n); ++i)
                    this->_x.push_back(0);
            }
            else if(n > 0){
                //Remove n digits
                for(int i = 0; i < n; ++i){
                    if(this->_x.size() > 1) 
            this->_x.pop_back();
        }
            }
            else{
                return *this;
            }
            shift_right_digits(x._x.begin(), x._x.end(), n, this->_x.begin());            
            return *this;
        }

        // ---
        // abs
        // ---

        /**
         *  Absolute value
         *  @return     the absolute value of the Integer
         *  This Integer is set to its absolute value
         */
        Integer& abs () {
            this->sign = true;
            return *this;
        }

        // ---
        // pow
        // ---

        /**
         *  Power
         *  @param n    an int to be used as exponent
         *  @return     the Integer to the power of e
         *  This Integer equals itself to power of e
         *  @throws invalid_argument if ((this == 0) && (e == 0)) or (e < 0)
         */
        Integer& pow (int e) {
	    if(e < 0 || (*this == Integer(0) && e == 0)){
                throw std::invalid_argument("Integer()");
            }
            if (e == 0){
                *this = Integer(1);
                return *this;
            }   
        
         /*   Integer x = *this;
            while(e > 1){
                *this *= x;
                --e;
            }  
            return *this;            
	*/
            Integer x = *this;
            Integer o = *this;
            const Integer p = x.pow(e / 2);
            const Integer q = p * p;
            if (e & 1)
                *this = q * o;
            else
                *this = q;
            return *this;
    }};

#endif // Integer_h
