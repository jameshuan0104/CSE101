/*
*James Huang, hhuan143
*2023 spring CSE101 PA#6
*BigInteger.cpp
*writes the functions of BigInteger.cpp
*/
#include<string>
#include<iostream>
#include<stdexcept>
#include<stdlib.h>
#include"BigInteger.h"
#include"List.h"
#include <ctype.h>
#include <algorithm> 

const long base = 1000000000;
const int power = 9;

BigInteger::BigInteger(){
	signum = 0;
	List digits;
}

BigInteger::BigInteger(long x){
	if (x > 0){
		signum = 1;
	}else if (x < 0){
		signum = -1;
		x = std::abs(x);
	}else{
		signum = 0;
		digits.insertBefore(0);
		return;
	}
	//digits.moveFront();
	std::string str = "";
	str = std::to_string(x);
	//std::cout<<str<<std::endl;
	//std::cout << std::stol(str) << std::endl;
	//std::cout<<"meow"<<std::endl;
	while(1){
		if (str.length() <= power){
			//std::cout<<"meow"<<std::endl;
			digits.insertAfter(std::stol(str) % base);
			//std::cout<<"long"<<digits<<std::endl;
			return;
		}else{
			digits.insertAfter(std::stol(str) % base);
			str = str.substr(0, (str.length() - power));
			//std::cout<<str<<std::endl;
		}
	}
	//std::cout<<digits<<std::endl;
}
// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
// 
BigInteger::BigInteger(std::string s){
	//std::cout << "meow" << std::endl;
	// BigInteger I = BigInteger(string)
	if (s[0] == '-' || s[0] == '+'){
		for (unsigned int i = 1; i < s.length(); i++){
			if (!isdigit(s[i])){
				throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
			}
		}
		if (s[0] == '-'){
			signum = -1;
		}else{
			signum = 1;
		}
		reverse(s.begin() + 1, s.end());// +123 -> +321
		std::string temp = "";
		for (unsigned int i = 1; i < s.length(); i++){
			temp += s[i];
			if(i % power == 0){
				reverse(temp.begin(), temp.end()); // 123 -> 321
				digits.insertBefore(std::stol(temp));
				digits.moveFront();
				temp = "";
			}
			else if (i == s.length() - 1){
				reverse(temp.begin(), temp.end());
				digits.insertBefore(std::stol(temp));
				temp = "";
			}
		}
	}else{
		for (unsigned int i = 0; i < s.length(); i++){
			if (!isdigit(s[i])){
				throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
			}
		}
		reverse(s.begin(), s.end());
		std::string temp = "";
		for (unsigned int i = 0; i < s.length(); i++){
			temp += s[i];
			if((i + 1) % power == 0){
				reverse(temp.begin(), temp.end());
				//std::cout << temp << std::endl;
				digits.insertBefore(std::stol(temp));
				digits.moveFront();
				temp = "";
			}
			else if (i == s.length() - 1){
				reverse(temp.begin(), temp.end());
				digits.insertBefore(std::stol(temp));
				temp = "";
			}
		}
		signum = 1;
	}
	//00 09 22 12 01
	digits.moveFront();
	while(digits.position() < digits.length()){
		if (digits.position() == digits.length() - 1){
			if (digits.peekNext() == 0){
				signum = 0;
				digits.insertBefore(0);
			}
		}
		if (digits.moveNext() == 0){
			digits.eraseBefore();
		}else{
			break;
		}

	}
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    this->signum = N.signum;
    this->digits = N.digits;
}

// // Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
	return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
	List A = this->digits;
	List B = N.digits;
	//std::cout << "meow = "<<this->signum << std::endl;


	if(this->signum != N.signum){
		if (this->signum > N.signum){
			return 1;
		}else{
			return -1;
		}
	}else{
		//std::cout << "meow = "<<this->signum << std::endl;
		if (this->signum == 0){
			//std::cout << "meow" << std::endl;
			return 0;
		}else if (this->signum == 1){
			//both postivie
			if (A.length() > B.length()){
				return 1;
			}else if(A.length() < B.length()){
				return -1;
			}else{
				A.moveFront();
				B.moveFront();
				//std::cout << "meow" << std::endl;
				while(A.position() < A.length()){
					//std::cout << "A = "<< A.peekNext() << std::endl;
					//std::cout << "B = "<< B.peekNext() << std::endl;
					if (A.peekNext() > B.peekNext()){
						return 1;
					}else if(A.peekNext() < B.peekNext()){
						return -1;
					}else{
						A.moveNext();
						B.moveNext();
					}
				}
				return 0;
			}
		}else{
			// both negative
			if (A.length() > B.length()){
				return -1;
			}else if(A.length() < B.length()){
				return 1;
			}else{
				A.moveFront();
				B.moveFront();
				while(A.position() < A.length()){
					if (A.peekNext() > B.peekNext()){
						return -1;
					}else if (A.peekNext() < B.peekNext()){
						return 1;
					}else{
						A.moveNext();
						B.moveNext();
					}
				}
				return 0;
			}

		}
	}
}

// // Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
	digits.clear();
	signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
	if (signum == 0){
		return;
	}
	if (signum == 1){
		signum = -1;
	}else{
		signum = 1;
	}
}

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
    // iterate through the list of L
    L.moveFront();
    while(L.position() < L.length()){
    	long x = L.moveNext();
    	if (x != 0){
    		L.eraseBefore();
    		L.insertBefore(x * -1);
    	}

    }
    //cout << digits << endl;
        // set a variable "x" of type ListElement to get the data of the next element of L  
        // if x is 0 then continue
        // then delete the element
        // instead insert the same data "x" but negative
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
    ListElement x, y;
    S.clear();
    A.moveBack();
    B.moveBack();
    //std::cout << "sumList A = " << A << std::endl;
	//std::cout << "sumList B = " << B << std::endl;
    while (A.position() > 0 && B.position() > 0){
    	x = A.movePrev();
    	y = B.movePrev();
    	//std::cout << "x = " << x << std::endl;
    	//std::cout << "y = " << y << std::endl;
    	//std::cout << "x +y*sign = " << x+sgn*y << std::endl;
    	S.insertAfter(x + (y * sgn));

    }
    while (A.position() > 0){
    	x = A.movePrev();
    	S.insertAfter(x);
    }
    while (B.position() > 0){
   	 	y = B.movePrev();
   	 	S.insertAfter(y * sgn);
    }

}

// normalizeList()
// Performs carries from right to left (least to most significant 
// digits), then returns the sign of the resulting integer. Used 
// by add(), sub() and mult().
int normalizeList(List& L){
	int sgn;
	ListElement q, r;
	ListElement num, carry = 0;
	
	L.moveBack(); 
	while (L.position() > 0){
		num = L.movePrev();
		num += carry;
		q = num / base; //498 / 100 = 4
		r = num % base; //498 % 100 = 98

		if (r < 0){
			num = r + base;
			carry = q - 1;
		}else{
			num = r;
			carry = q;
		}
		//std::cout << "L = " << L << std::endl;
		L.setAfter(num);
		//std::cout << "L = " << L << std::endl;
		if (L.position() == 0){
			if (carry > 0){
				L.insertBefore(0);
			}else if(carry < 0){
				L.insertBefore(carry);
				break;
			}
		}
	}
	//std::cout << "normalizeList = " << L << std::endl;
	//std::cout << "meow1 " << std::endl;
   //delete leading zeros
	L.moveFront();
	while (L.position() < L.length()){
        // eliminate/erase all leading zeros
        if (L.moveNext() == 0){
        	L.eraseBefore();
        }else{
        	break;
        }
	}


	if (L.length() != 0){
		if (L.front() > 0){
			sgn = 1;
		}else if (L.front() < 0){
			sgn = -1;
			negateList(L);
			normalizeList(L);
		}
	}else{
		sgn = 0;
	}
   	return sgn;

}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
	L.moveBack();
	for (int i = 0; i < p; i++){
		L.insertBefore(0);
	}
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
	if (m != 1){
		L.moveFront();
		while(L.position() < L.length()){
			ListElement x = L.moveNext();
			if (x != 0){
				L.eraseBefore();
				L.insertBefore(x * m);
			}
		}
	}
}


// // BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
	BigInteger sum;
	int sign;

	List A = this->digits;
    List B = N.digits;
	List& L = sum.digits;

	if (this->signum == N.signum){
		//std::cout << "AAAAA in add " << A << std::endl;
		//std::cout << "BBBBB in add" << B << std::endl;
		sumList(L, A, B, 1);
		normalizeList(L);
		sum.signum = this->signum;
	}else{
		//std::cout << "AAAAA in add " << A << std::endl;
		//std::cout << "BBBBB in add" << B << std::endl;
		sumList(L, A, B, -1);
		sign = normalizeList(L);
		sum.signum = sign * this->signum;
	}
	return sum;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
	BigInteger A = BigInteger(N);//copy constructor!!!
	A.negate();
	BigInteger diff = this->add(A);
	return diff;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{

	int col = 0;
	ListElement b;
	BigInteger scalarM;
	BigInteger prod;

	List A = this->digits;
	List B = N.digits;
	List C = A;

	prod.signum = this->signum * N.signum;

	if (this->signum == 0 || N.signum == 0){
		prod = BigInteger(0);
		return prod;
	}

	B.moveBack();
	while (B.position() > 0){
		C = A;
		b = B.movePrev();
		if (b == 0){
			C.clear();
		}else{
			scalarMultList(C, b);
			normalizeList(C);
			shiftList(C, col);
			scalarM.digits = C;
			scalarM.signum = this->signum;
			prod += scalarM;
			normalizeList(C);
		}
		col++;
	}
	prod.signum = this->signum * N.signum;
	return prod;

}

// Other Functions ---------------------------------------------------------

//to_string()
//Returns a string representation of this BigInteger consisting of its
//base 10 digits. If this BigInteger is negative, the returned string 
//will begin with a negative sign '-'. If this BigInteger is zero, the
//returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
	//std::cout << digits.length() << std::endl;
	if (digits.length() == 0){
		//std::cout << "meow" << std::endl;
		std::string s = "0";
		return s;
	}
	digits.moveFront();
	if (digits.peekNext() == 0){
		std::string s = "0";
		//std::cout << s << std::endl;
		return s;
	}else{
		std::string s = "";
		if (signum == -1){
			s += "-";
		}
		for(digits.moveFront(); digits.position() < digits.length(); digits.moveNext()){
			int len = std::to_string(digits.peekNext()).length();
			if (len < power && digits.position() != 0){
				for (int i = 0; i < (power - len); i++){
					s += "0";
				}
			} 
			s += std::to_string(digits.peekNext());
			
		}

		return s;
	}
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
	return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
	return A.compare(B) == 0;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
	return A.compare(B) < 0;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
	return A.compare(B) <= 0;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
	return A.compare(B) > 0;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
	return A.compare(B) >= 0;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
	return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
	A = A.add(B);
	return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
	return A.sub(B);

}

// // operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
	A = A.sub(B);
	return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
	return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
	A = A.mult(B);
	return A;
}


