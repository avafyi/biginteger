/****************************************************************
 * BigInt.h -- include-file for big integer package
 ****************************************************************/
#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>

// Set debug on or off. If on, it will assign a unique id to
// every allocated array and print a debug message whenever an
// array is allocated or deleted.
#define DEBUG 0

/*****************************************************************
 * BigInt class
 *
 * Presently dummied up:
 * - does not implement integer values larger than the 'long' data
 *   type
 * - only operations related to '+' and '==' operator are defined
 *
 *****************************************************************/

class BigInt {
private:
	short *data; // our numeric data array
	int dataLength; // length of data array
	bool neg; // boolean flag for negative number
#if DEBUG
	unsigned long long id; // unique id for debug printing
#endif

	// constructor for building a BigInt from existing array
	BigInt(int dataLengthIn, short *dataIn, bool negIn);

	// binary summation
	BigInt sum(BigInt const& other) const;

	// binary difference
	BigInt difference(BigInt const& other) const;

	// absolute value
	BigInt abs() const;

	// helper method to compare absolute values (used for efficiency)
	bool absGreaterThan(BigInt const& other) const;

	// helper method to quickly multiply by 10
	BigInt multBy10() const;

	// helper method to divide with remainder
	BigInt divide(BigInt const& other, BigInt &remainder) const;

public:
	// copy constructor
	BigInt(BigInt const& orig);

	// constructor where data value is passed as a long
	BigInt(long num);

	// destructor
	~BigInt();

	BigInt operator=(BigInt const& src);

	//// assignment operator
	//BigInt BigInt::operator=(BigInt const& other);

	// binary '+' operator
	BigInt operator+(BigInt const& other) const;

	// binary '-' operator
	BigInt operator-(BigInt const& other) const;

	// binary '*' operator
	BigInt operator*(BigInt const& other) const;

	// binary '/' operator
	BigInt operator/(BigInt const& other) const;

	// binary '%' operator
	BigInt operator%(BigInt const& other) const;

	// unary '+' operator
	BigInt operator+() const;

	// unary '-' operator
	BigInt operator-() const;

	// prefix '++' operator
	BigInt operator++();

	// postfix '++' operator
	BigInt operator++(int dummy);

	// prefix '--' operator
	BigInt operator--();

	// postfix '--' operator
	BigInt operator--(int dummy);

	// compound addition-assignment operator
	BigInt operator+=(BigInt const& other);

	// compound subtraction-assignment operator
	BigInt operator-=(BigInt const& other);

	// compound multiplication-assignment operator
	BigInt operator*=(BigInt const& other);

	// compound division-assignment operator
	BigInt operator/=(BigInt const& other);

	// compound mod-assignment operator
	BigInt operator%=(BigInt const& other);

	// compound addition-assignment operator for long
	inline BigInt operator+=(long const& num) {
		return *this = *this + BigInt(num);
	}

	// compound subtraction-assignment operator for long
	inline BigInt operator-=(long const& num) {
		return *this = *this - BigInt(num);
	}

	// compound multiplication-assignment operator for long
	inline BigInt operator*=(long const& num) {
		return *this = *this * BigInt(num);
	}

	// compound division-assignment operator for long
	inline BigInt operator/=(long const& num) {
		return *this = *this / BigInt(num);
	}

	// compound mod-assignment operator for long
	inline BigInt operator%=(long const& num) {
		return *this = *this % BigInt(num);
	}

	// equality operation
	bool operator==(BigInt const& other) const;

	// equality operation
	bool operator!=(BigInt const& other) const;

	// equality operation
	bool operator>(BigInt const& other) const;

	// equality operation
	bool operator>=(BigInt const& other) const;

	// equality operation
	bool operator<(BigInt const& other) const;

	// equality operation
	bool operator<=(BigInt const& other) const;

	// output-stream operator for BigInt (non-member function)
	friend std::ostream & operator<<(std::ostream& os, const BigInt& num);
};

// addition operator where left operand is a long
inline BigInt operator+(long num, BigInt const& val) {
	return BigInt(num) + val;
}

// addition operator where right operand is a long
inline BigInt operator+(BigInt const& val, long num) {
	return val + BigInt(num);
}

// subtraction operator where left operand is a long
inline BigInt operator-(long num, BigInt const& val) {
	return BigInt(num) - val;
}

// subtraction operator where right operand is a long
inline BigInt operator-(BigInt const& val, long num) {
	return val - BigInt(num);
}

// multiplication operator where left operand is a long
inline BigInt operator*(long num, BigInt const& val) {
	return BigInt(num) * val;
}

// multiplication operator where right operand is a long
inline BigInt operator*(BigInt const& val, long num) {
	return val * BigInt(num);
}

// division operator where left operand is a long
inline BigInt operator/(long num, BigInt const& val) {
	return BigInt(num) / val;
}

// division operator where right operand is a long
inline BigInt operator/(BigInt const& val, long num) {
	return val / BigInt(num);
}

// mod operator where left operand is a long
inline BigInt operator%(long num, BigInt const& val) {
	return BigInt(num) % val;
}

// mod operator where right operand is a long
inline BigInt operator%(BigInt const& val, long num) {
	return val % BigInt(num);
}

// equality operator where left operand is a long
inline bool operator==(long num, BigInt const& val) {
	return BigInt(num) == val;
}

// equality operator where right operand is a long
inline bool operator==(BigInt const& val, long num) {
	return val == BigInt(num);
}

// inequality operator where left operand is a long
inline bool operator!=(long num, BigInt const& val) {
	return BigInt(num) != val;
}

// inequality operator where right operand is a long
inline bool operator!=(BigInt const& val, long num) {
	return val != BigInt(num);
}

// greater-than operator where left operand is a long
inline bool operator>(long num, BigInt const& val) {
	return BigInt(num) > val;
}

// greater-than operator where right operand is a long
inline bool operator>(BigInt const& val, long num) {
	return val > BigInt(num);
}

// greater-than-or-equal operator where left operand is a long
inline bool operator>=(long num, BigInt const& val) {
	return BigInt(num) >= val;
}

// greater-than-or-equal operator where right operand is a long
inline bool operator>=(BigInt const& val, long num) {
	return val >= BigInt(num);
}

// less-than operator where left operand is a long
inline bool operator<(long num, BigInt const& val) {
	return BigInt(num) < val;
}

// less-than operator where right operand is a long
inline bool operator<(BigInt const& val, long num) {
	return val < BigInt(num);
}

// less-than-or-equal operator where left operand is a long
inline bool operator<=(long num, BigInt const& val) {
	return BigInt(num) <= val;
}

// less-than-or-equal operator where right operand is a long
inline bool operator<=(BigInt const& val, long num) {
	return val <= BigInt(num);
}

#endif
