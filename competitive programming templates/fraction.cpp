// requires bigInt.cpp
#include "bigInt.cpp"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct frac{
	bign num, den; // numerator / denominator

	frac(int x = 0, int y = 1) : num(bign(x)), den(bign(y)){}
	frac(bign x, bign y = 1) : num(x), den(y){}

	frac operator+(const frac& b){
		frac rs;
		rs.den = lcm(b.den, (*this).den);
		rs.num = (*this).num * (rs.den / (*this).den) + b.num * (rs.den / b.den);
		return rs;
	}

	frac operator-(const frac& b){
		frac rs;
		rs.den = lcm(b.den, (*this).den);
		rs.num = (*this).num * (rs.den / (*this).den) - b.num * (rs.den / b.den);
		return rs;
	}

	frac operator*(const frac& b){
		frac rs = frac((*this).num * b.num, (*this).den * b.den);
		bign gt = gcd(rs.num, rs.den);
		rs.num /= gt; rs.den /= gt;
		return rs;
	}

	frac operator/(const frac& b){
		frac fl = frac(b.den, b.num);
		return (*this) * fl;
	}

	frac operator+=(const frac& b){
		*this = *this + b;
		return *this;
	}
	frac operator-=(const frac& b){
		*this = *this - b;
		return *this;
	}
	frac operator*=(const frac& b){
		*this = *this * b;
		return *this;
	}
	frac operator/=(const frac& b){
		*this = *this / b;
		return *this;
	}

	bool operator<(const frac& b) const{
		return (*this).num * b.den < (*this).den * b.num;
	}
	bool operator>(const frac& b) const{
		return b < *this;
	}
	bool operator<=(const frac& b) const{
		return !(b < *this);
	}
	bool operator>=(const frac& b) const{
		return !(*this < b);
	}
	bool operator!=(const frac& b) const{
		return b < *this || *this < b;
	}
	bool operator==(const frac& b) const{
		return !(b != *this);
	}
};

frac rep(frac x){
	return frac(x.den, x.num);
}