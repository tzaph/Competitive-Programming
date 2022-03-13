#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long

ll gcd(ll a, ll b){
	if(a < b) swap(a, b);
	if(b == 0) return a;
	return gcd(b, a % b);
}

ll lcm(ll a, ll b){
	return a * b / gcd(a, b);
}

struct frac{
	ll num, den; // numerator / denominator

	frac(ll x = 0, ll y = 1) : num(x), den(y){}

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
		ll gt = gcd(rs.num, rs.den);
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