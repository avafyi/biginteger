/****************************************************************
 * BigInt.cpp -- big integer package for C++
 ****************************************************************/
#include <iostream>
#include "BigInt.h"

using namespace std;

/*****************************************************************
 * member functions for BigInt class
 *
 * Presently dummied up:
 * - does not implement integer values larger than the 'long' data
 *   type
 * - only operations related to '+' and '==' operator are defined
 * 
 *****************************************************************/

#if DEBUG
static unsigned long long nextId = 0; // counter to assign unique ids

// called whenever a new array is allocated
inline void printDebugNew(long long id) {
	if (id < 0 || id > 100000)
		cout << endl << "ERROR: GARBAGE ID BEING USED";
	cout << endl << "DEBUG: " << id << " new" << endl;
}

// called whenever an array is deleted
inline void printDebugDelete(long long id) {
	if (id < 0 || id > 100000)
		cout << endl << "ERROR: GARBAGE ID BEING USED";
	cout << endl << "DEBUG: " << id << " delete" << endl;
}
#endif;

// copy constructor
BigInt::BigInt(BigInt const& orig) {
	this->dataLength = orig.dataLength;
	// if infinity or undefined, set data to null
	if (this->dataLength <= 0) {
		this->data = NULL;
#if DEBUG
		// not allocating memory, so use a junk id
		this->id = -1;
#endif
	}
	else {
		// orig is a number, so copy the array
		this->data = new short[this->dataLength];
#if DEBUG
		this->id = nextId;
		nextId++;
		printDebugNew(id);
#endif
		for (int i = 0; i < orig.dataLength; i++) {
			this->data[i] = orig.data[i];
		}
	}
	this->neg = orig.neg;
}

// constructor where operand is a long
BigInt::BigInt(long num) {
	// if num is zero, set values manually
	if (num == 0) {
		neg = false;
		dataLength = 1;
		data = new short[1];
#if DEBUG
		this->id = nextId;
		nextId++;
		printDebugNew(id);
#endif
		data[0] = 0;
	}
	else {
		// num is nonzero, so...
		// set negative bool
		neg = (num < 0);
		// force num to positive for later
		if (neg) num *= -1;
		dataLength = 0;
		// just allocate the max possible number of
		// digits for a 64-bit long
		data = new short[19];
#if DEBUG
		this->id = nextId;
		nextId++;
		printDebugNew(id);
#endif
		while (num > 0) {
			// pull digits out of num one at a time
			data[dataLength] = num % 10;
			num /= 10;
			dataLength++;
		}
	}
}

// constructor for building a BigInt from existing array
BigInt::BigInt(int dataLengthIn, short *dataIn, bool negIn) {
	// copy values, setting the data pointer to the existing array
	dataLength = dataLengthIn;
	data = dataIn;
	neg = negIn;
#if DEBUG
	if (dataLength > 0) {
		id = nextId;
		nextId++;
		printDebugNew(id);
	}
	else {
		// not allocating memory, so use a junk id
		id = -1;
	}
#endif
	// ensure that zeros are positive
	if (dataLength == 1 && data[0] == 0) neg = false;
}
  
// destructor
BigInt::~BigInt() {
	// if data is pointing to an array, free it
	if (data != NULL) {
		delete[] data;
#if DEBUG
		printDebugDelete(id);
#endif
	}
}

// assignment operator
BigInt BigInt::operator=(BigInt const& src) {
	// if this was not undefined or infinity
	if (this->dataLength > 0) {
		// return old array to heap
		delete[] this->data;
#if DEBUG
		printDebugDelete(id);
#endif
	}

	this->dataLength = src.dataLength;

	// if source is not undefined or infinity
	if (this->dataLength > 0) {
		// allocate space and copy digits
		this->data = new short[this->dataLength];
#if DEBUG
		this->id = nextId;
		nextId++;
		printDebugNew(id);
#endif
		for (int i = 0; i < this->dataLength; i++) {
			this->data[i] = src.data[i];
		}
	}
	else {
		// source is undefined or infinity, so ignore data
		this->data = NULL;
	}
	this->neg = src.neg;
	return *this;
}

// binary summation
BigInt BigInt::sum(BigInt const& other) const {
	// if either operand is undefined, return undefined
	if (dataLength == -1) return *this;
	if (other.dataLength == -1) return other;
	// if either operand is infinity, return infinity
	if (dataLength == 0 || other.dataLength == 0) return BigInt(0, NULL, neg);

	// find max possible length of sum
	int tempLength = (this->dataLength > other.dataLength) ? this->dataLength + 1 : other.dataLength + 1;

	short *resultArr = new short[tempLength];
	short carry = 0;
	short sum, thisDigit, otherDigit;

	// sum digits from right to left, carrying appropriately
	for (int i = 0; i < tempLength; i++) {
		// if we run out of digits in either number, use a 0
		thisDigit = (i < this->dataLength) ? this->data[i] : 0;
		otherDigit = (i < other.dataLength) ? other.data[i] : 0;
		// sum the digits, including a possible carry
		sum = thisDigit + otherDigit + carry;
		if (sum > 9) {
			carry = 1;
			sum -= 10;
		}
		else {
			carry = 0;
		}
		resultArr[i] = sum;
	}

	// count the leading zeros in the sum
	int leadingZeros = 0;
	while (resultArr[(tempLength - leadingZeros) - 1] == 0) {
		leadingZeros++;
	}
	if (leadingZeros == tempLength) leadingZeros--;

	return BigInt(tempLength - leadingZeros, resultArr, this->neg);
}

// binary difference
BigInt BigInt::difference(BigInt const& other) const {
	// if either operand is undefined, return undefined
	if (dataLength == -1) return *this;
	if (other.dataLength == -1) return other;
	// infinity-infinity is undefined
	if (dataLength == 0 && other.dataLength == 0) return BigInt(-1, NULL, false);
	// if infinity-number or number-infinity, then return infinity
	if (dataLength == 0) return *this;
	if (other.dataLength == 0) return BigInt(0, NULL, !neg);

	// find max possible length of difference
	int tempLength = (this->dataLength > other.dataLength) ? this->dataLength : other.dataLength;

	BigInt top = NULL, bottom = NULL;

	bool resultNeg = NULL;
	
	// put the larger absolute value on "top"
	// (as if doing it by hand)
	if (other.absGreaterThan(*this)) {
		top = other;
		bottom = BigInt(*this);
		resultNeg = !top.neg;
	}
	else {
		top = *this;
		bottom = BigInt(other);
		resultNeg = top.neg;
	}
	
	short *resultArr = new short[tempLength];
	short carry = 0;
	short diff, topDigit, bottomDigit;

	// subtract digits from right to left, carrying
	// by adding one to the next "bottom" digit
	for (int i = 0; i < tempLength; i++) {
		// if we run out of digits in either number, use a 0
		topDigit = (i < top.dataLength) ? top.data[i] : 0;
		bottomDigit = (i < bottom.dataLength) ? bottom.data[i] : 0;
		// carry along the "bottom" number
		diff = topDigit - (bottomDigit + carry);
		if (diff < 0) {
			diff += 10;
			carry = 1;
		}
		else {
			carry = 0;
		}

		resultArr[i] = diff;
	}

	// count the leading zeros in the difference
	int leadingZeros = 0;
	while (resultArr[(tempLength - leadingZeros) - 1] == 0) {
		leadingZeros++;
	}
	if (leadingZeros == tempLength) {
		// account for a difference of zero
		leadingZeros--;
		resultNeg = false;
	}

	return BigInt(tempLength - leadingZeros, resultArr, resultNeg);
}

// absolute value
BigInt BigInt::abs() const {
	// copy this and set sign to positive
	BigInt absValue = BigInt(*this);
	absValue.neg = false;
	return absValue;
}

// compare absolute values
bool BigInt::absGreaterThan(BigInt const& other) const {
	// compare length
	if (this->dataLength > other.dataLength) {
		return true;
	}
	if (other.dataLength > this->dataLength) {
		return false;
	}

	// same length, so compare by digit (MSD first)
	for (int i = this->dataLength - 1; i >= 0; i--) {
		if (this->data[i] > other.data[i]) return true;
		if (this->data[i] < other.data[i]) return false;
	}

	// abs vals are equal
	return false;
}

// quickly multiply by 10
BigInt BigInt::multBy10() const {
	// check that this is non-zero
	if (this->dataLength != 1 || *this != BigInt(0)) {
		// copy to a new array with a zero added to the end
		short *resultArr = new short[dataLength + 1];
		resultArr[0] = 0;
		for (int i = 0; i < dataLength; i++) {
			resultArr[i + 1] = this->data[i];
		}

		return BigInt(dataLength + 1, resultArr, neg);
	}
	else {
		// 0*10 = 0, so just return 0
		return *this;
	}
}

// helper for division/remainder
BigInt BigInt::divide(BigInt const& other, BigInt &remainder) const {
	// if either operand is undefined, return undefined
	if (dataLength == -1) {
		remainder = *this;
		return *this;
	}
	if (other.dataLength == -1) {
		remainder = other;
		return other;
	}
	// if divide by zero, return infinity (or undefined if 0/0)
	if (other == 0) {
		if (*this == 0) {
			// 0/0, return undefined
			remainder = BigInt(-1, NULL, false);
			return BigInt(-1, NULL, false);
		}
		else {
			// infinity/0, return infinity
			remainder = BigInt(0);
			return BigInt(0, NULL, neg);
		}
	}
	// if infinity/infinity, return undefined
	if (dataLength == 0 && other.dataLength == 0) {
		remainder = BigInt(-1, NULL, false);
		return BigInt(-1, NULL, false);
	}
	// if infinity/number, return infinity
	if (dataLength == 0) {
		remainder = BigInt(0);
		return BigInt(0, NULL, neg != other.neg);
	}
	// if number/infinity, return 0
	if (other.dataLength == 0) {
		remainder = BigInt(0);
		return BigInt(0);
	}

	short *resultArr = new short[dataLength];
	remainder = BigInt(0);
	bool resultNeg = (this->neg != other.neg);
	// get absolute value for later comparisons
	BigInt otherAbs = other.abs();

	// do long division
	for (int i = 0; i < dataLength; i++) {
		// pull the next digit down from the dividend
		remainder = remainder.multBy10();
		remainder += BigInt(data[(dataLength - 1) - i]);
		// count how many times divisor goes into remainder
		int divisorCount = 0;
		while (remainder >= otherAbs) {
			remainder -= otherAbs;
			divisorCount++;
		}
		// put the count into the quotient
		resultArr[(dataLength - 1) - i] = divisorCount;
	}

	// count the leading zeros in the quotient
	int leadingZeros = 0;
	while (resultArr[(dataLength - leadingZeros) - 1] == 0) {
		leadingZeros++;
	}
	if (leadingZeros == dataLength) {
		// account for a quotient of zero
		leadingZeros--;
		resultNeg = false;
	}

	return BigInt(dataLength - leadingZeros, resultArr, resultNeg);
}

// binary addition
BigInt BigInt::operator+(BigInt const& other) const {
	// call appropriate helper based on signs
	if (this->neg == other.neg) {
		return sum(other);
	}
	else {
		return difference(other);
	}
}

// binary subtraction
BigInt BigInt::operator-(BigInt const& other) const {
	// call appropriate helper based on signs
	if (this->neg == other.neg) {
		return difference(other);
	}
	else {
		return sum(other);
	}
}

// binary multiplication
BigInt BigInt::operator*(BigInt const& other) const {
	// if either operand is undefined, return undefined
	if (dataLength == -1) return *this;
	if (other.dataLength == -1) return other;
	// infinity * 0 = undefined
	if ((dataLength == 0 && other == 0) || (*this == 0 && other.dataLength == 0)) return BigInt(-1, NULL, false);
	// infinity * (anything else) = infinity
	if (dataLength == 0 || other.dataLength == 0) return BigInt(0, NULL, neg != other.neg);

	// if either operand is zero, return zero
	if (*this == 0) return *this;
	if (other == 0) return other;

	BigInt result(0), top = NULL, bottom = NULL;

	// find the larger abs value and put it on "top"
	// (as if we were doing mult by hand)
	if (other.absGreaterThan(*this)) {
		top = other;
		bottom = BigInt(*this);
	}
	else {
		top = *this;
		bottom = BigInt(other);
	}

	// var to hold partial product
	BigInt resultPartBig = BigInt(0);

	int carry, quot;

	// for each digit in "bottom" number, multiply it
	// by the entire top number (adding zeros appropriately)
	// and add that to our result
	for (int j = 0; j < bottom.dataLength; j++) {
		// reset the partial product BigInt
		resultPartBig.dataLength = top.dataLength;
		delete[] resultPartBig.data;
#if DEBUG
		printDebugDelete(resultPartBig.id);
#endif
		resultPartBig.data = new short[top.dataLength + 1];
#if DEBUG
		resultPartBig.id = nextId;
		nextId++;
		printDebugNew(resultPartBig.id);
#endif
		carry = 0;
		// multiply next bottom digit by top BigInt
		for (int i = 0; i < top.dataLength; i++) {
			quot = bottom.data[j] * top.data[i] + carry;
			if (quot > 9) {
				carry = quot / 10;
				quot %= 10;
			}
			else {
				carry = 0;
			}
			resultPartBig.data[i] = quot;
		}
		if (carry > 0) {
			// account for possible extra carry
			resultPartBig.data[top.dataLength] = carry;
			resultPartBig.dataLength++;
		}

		// add zeros to the end of our partial product appropriately
		for (int times10count = 0; times10count < j; times10count++) {
			resultPartBig = resultPartBig.multBy10();
		}

		result += resultPartBig;
	}

	result.neg = (this->neg != other.neg);
	return result;
}

// binary division
BigInt BigInt::operator/(BigInt const& other) const {
	// temp var to hold remainder
	BigInt temp = NULL;
	return this->divide(other, temp);
}

// binary mod
BigInt BigInt::operator%(BigInt const& other) const {
	BigInt remainder = NULL;
	// set the remainder using the divide function
	BigInt temp = this->divide(other, remainder);
	return remainder;
}

// compound addition-assignment operator
BigInt BigInt::operator+=(BigInt const& other) {
	return *this = *this + other;
}

// compound subtraction-assignment operator
BigInt BigInt::operator-=(BigInt const& other) {
	return *this = *this - other;
}

// compound multiplication-assignment operator
BigInt BigInt::operator*=(BigInt const& other) {
	return *this = *this * other;
}

// compound division-assignment operator
BigInt BigInt::operator/=(BigInt const& other) {
	return *this = *this / other;
}

// compound mod-assignment operator
BigInt BigInt::operator%=(BigInt const& other) {
	return *this = *this % other;
}

// prefix '++' operator
BigInt BigInt::operator++() {
	return *this = *this + BigInt(1);
}

// postfix '++' operator
BigInt BigInt::operator++(int dummy) {
	return *this = *this + BigInt(1);
}

// prefix '--' operator
BigInt BigInt::operator--() {
	return *this = *this - BigInt(1);
}

// postfix '--' operator
BigInt BigInt::operator--(int dummy) {
	return *this = *this - BigInt(1);
}


// unary '+' operator
BigInt BigInt::operator+() const {
	return *this;
}

// unary '-' operator
BigInt BigInt::operator-() const {
	if (*this != 0) {
		// copy number and flip the sign
		BigInt result = BigInt(*this);
		result.neg = !result.neg;
		return result;
	}
	else {
		return *this;
	}
}

// equality operator
bool BigInt::operator==(BigInt const& other) const {
	// check lengths
	if (this->dataLength != other.dataLength) return false;

	// same lengths, so check signs
	if (this->neg != other.neg) return false;

	// same signs, so compare digits
	for (int i = 0; i < this->dataLength; i++) {
		if (this->data[i] != other.data[i]) return false;
	}

	// numbers are equal
	return true;
}

// inequality operator
bool BigInt::operator!=(BigInt const& other) const {
	return !(*this == other);
}

// greater-than operator
bool BigInt::operator>(BigInt const& other) const {
	// check signs
	if (this->neg && !other.neg) return false;
	if (other.neg && !this->neg) return true;

	// same sign, so check length
	bool bothNeg = (this->neg && other.neg);
	if (this->dataLength > other.dataLength) {
		return bothNeg ? false : true;
	}
	if (other.dataLength > this->dataLength) {
		return bothNeg ? true : false;
	}

	// same sign, same length, so compare by digit (MSD first)
	for (int i = this->dataLength - 1; i >= 0; i--) {
		if (this->data[i] > other.data[i]) return true;
		if (this->data[i] < other.data[i]) return false;
	}

	// numbers are equal
	return false;
}

// greater-than-or-equal operator
bool BigInt::operator>=(BigInt const& other) const {
	return !(*this < other);
}

// less-than operator
bool BigInt::operator<(BigInt const& other) const {
	// check signs
	if (this->neg && !other.neg) return true;
	if (other.neg && !this->neg) return false;

	// same sign, so check length
	bool bothNeg = (this->neg && other.neg);
	if (this->dataLength > other.dataLength) {
		return bothNeg ? true : false;
	}
	if (other.dataLength > this->dataLength) {
		return bothNeg ? false : true;
	}

	// same sign, same length, so compare by digit (MSD first)
	for (int i = this->dataLength - 1; i >= 0; i--) {
		if (this->data[i] > other.data[i]) return false;
		if (this->data[i] < other.data[i]) return true;
	}

	// numbers are equal
	return false;
}

// less-than-or-equal operator
bool BigInt::operator<=(BigInt const& other) const {
	return !(*this > other);
}

// output-stream operator for BigInt (non-member function)
ostream & operator<<(ostream& os, const BigInt& num) {
	if (num.dataLength == -1) {
		os << "**UNDEFINED**";
	}
	else {
		if (num.neg) os << "-";
		if (num.dataLength == 0) {
			os << "INFINITY";
		}
		else {
			// print each digit
			for (int i = num.dataLength - 1; i >= 0; i--) {
				os << (short)num.data[i];
			}
		}
	}
	return os;
}
