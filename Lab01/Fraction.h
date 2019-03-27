#pragma once
#include <iostream>
#include <ctime>

using namespace std;


template <typename tNum, typename tDiv>
class Fraction
{
public:
	Fraction() = default;
	~Fraction() = default;
	Fraction(tNum, tDiv);
	Fraction<tNum, tDiv> operator+(const Fraction<tNum, tDiv>&) const&;
	Fraction<tNum, tDiv> operator-(const Fraction<tNum, tDiv>&) const&;
	Fraction<tNum, tDiv> operator*(const Fraction<tNum, tDiv>&) const&;
	Fraction<tNum, tDiv> operator/(const Fraction<tNum, tDiv>&) const&;
	Fraction<tNum, tDiv> operator=(const Fraction<tNum, tDiv>&)&;
	Fraction<tNum, tDiv> operator=(const tNum&)&;
	Fraction<tNum, tDiv> operator*(const tNum&) const&;
	void nod()&;
	bool operator==(const tNum&) const;
	friend ostream& operator<< <tNum, tDiv>(ostream&, const Fraction&);
	friend istream& operator>> <tNum, tDiv>(istream&, Fraction&);
private:
	tNum num;
	tDiv divider;
};

template <typename tNum, typename tDiv>
Fraction<tNum, tDiv>::Fraction(tNum newNum, tDiv newDiv)
{
	if (newDiv == 0)
		throw std::logic_error("Division by zero.");
	num = newNum;
	divider = newDiv;
	nod();
}

template <typename tNum, typename tDiv>
Fraction<tNum, tDiv> Fraction<tNum, tDiv>::operator+(const Fraction<tNum, tDiv>& right) const&
{
	tNum newNum = num * right.divider;
	tDiv newDiv = divider * right.divider;
	newNum += right.num * divider;
	return Fraction(newNum, newDiv);
}

template <typename tNum, typename tDiv>
Fraction<tNum, tDiv> Fraction<tNum, tDiv>::operator-(const Fraction<tNum, tDiv>& right) const&
{
	tNum newNum = num * right.divider;
	tDiv newDiv = divider * right.divider;
	newNum -= right.num * divider;
	return Fraction(newNum, newDiv);
}

template <typename tNum, typename tDiv>
Fraction<tNum, tDiv> Fraction<tNum, tDiv>::operator*(const Fraction<tNum, tDiv>& right) const&
{
	tNum newNum = num * right.num;
	tNum newDiv = divider * right.divider;
	return Fraction(newNum, newDiv);
}

template <typename tNum, typename tDiv>
Fraction<tNum, tDiv> Fraction<tNum, tDiv>::operator/(const Fraction<tNum, tDiv>& right) const&
{
	tNum newNum = num * right.divider;
	tDiv newDiv = divider * right.num;
	return Fraction(newNum, newDiv);
}

template <typename tNum, typename tDiv>
ostream& operator<<(ostream& out, const Fraction<tNum, tDiv>& fr)
{
	out << fr.num << "/" << fr.divider;
	return out;
}

template <typename tNum, typename tDiv>
istream& operator>>(istream& in, Fraction<tNum, tDiv>& fr)
{
	in >> fr.num >> fr.divider;
	if (fr.divider == 0)
		throw std::logic_error("Division by zero.");
	return in;
}

template <typename tNum, typename tDiv>
Fraction<tNum, tDiv> Fraction<tNum, tDiv>::operator=(const Fraction<tNum, tDiv>& right)&
{
	num = right.num;
	divider = right.divider;
	return *this;
}

template <typename tNum, typename tDiv>
Fraction<tNum, tDiv> Fraction<tNum, tDiv>::operator=(const tNum& koef)&
{
	num = koef;
	divider = 1;
	return *this;
}

template <typename tNum, typename tDiv>
Fraction<tNum, tDiv> Fraction<tNum, tDiv>::operator*(const tNum& koef) const&
{
	return Fraction(num * koef, divider);
}

template <typename tNum, typename tDiv>
bool Fraction<tNum, tDiv>::operator==(const tNum& koef) const
{
	return (num == koef && divider == 1);
}

template <typename tNum, typename tDiv>
void Fraction<tNum, tDiv>::nod()&
{
	tNum tmpNum = abs(num);
	tDiv tmpDiv = abs(divider);
	while (tmpNum > 0 && tmpDiv > 0)
	{
		if (tmpNum > tmpDiv)
			tmpNum -= tmpDiv;
		else
			tmpDiv -= tmpNum;
	}
	num /= (tmpDiv + tmpNum);
	divider /= (tmpDiv + tmpNum);
}