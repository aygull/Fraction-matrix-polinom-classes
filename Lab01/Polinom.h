#pragma once
#include <list>
#include <algorithm>
#include "Monom.h"

template <typename tKoef, typename tGrade>
class Polinom
{
public:
	Polinom() = default;
	~Polinom() = default;

	void addMonom(tKoef, tGrade, char)&;

	Polinom<tKoef, tGrade> operator+(const Polinom<tKoef, tGrade>&) const&;
	Polinom<tKoef, tGrade> operator-(const Polinom<tKoef, tGrade>&) const&;
	Polinom<tKoef, tGrade> operator*(const Polinom<tKoef, tGrade>&) const&;
	Polinom<tKoef, tGrade> operator/(Polinom<tKoef, tGrade>&) const&;
	Polinom<tKoef, tGrade> operator%(Polinom<tKoef, tGrade>&) const&;
	Polinom<tKoef, tGrade> operator^(tGrade) const&;

	Polinom<tKoef, tGrade> defference() const&;
	tKoef mean(const tKoef&) const&;
	Polinom<tKoef, tGrade> superPos(const Polinom<tKoef, tGrade>&) const&;
	
	friend ostream& operator<< <tKoef, tGrade>(ostream&, const Polinom&);

private:
	list<Monom<tKoef, tGrade>> myList;
};

template <typename tKoef, typename tGrade>
void Polinom<tKoef, tGrade>::addMonom(tKoef k, tGrade deg, char symb)&
{
	Monom<tKoef, tGrade> tmpMon(k, deg, symb);
	myList.push_back(tmpMon);
}

template <typename tKoef, typename tGrade>
Polinom<tKoef, tGrade> Polinom<tKoef, tGrade>::operator+
(const Polinom<tKoef, tGrade>& right) const&
{
	Polinom<tKoef, tGrade> res;
	for (auto it = myList.begin(); it != myList.end(); it++)
	{
		for (auto jt = right.myList.begin(); jt != right.myList.end(); jt++)
			res.addMonom(*it + *jt);
	}
	for (auto jt = right.myList.begin(); jt != right.myList.end(); jt++)
	{
		if (find(res.myList.begin(), res.myList.end(), *jt) == res.myList.end())
			res.addMonom(*jt);
	}
	res.myList.sort();
	return res;
}

template <typename tKoef, typename tGrade>
Polinom<tKoef, tGrade> Polinom<tKoef, tGrade>::operator- 
(const Polinom<tKoef, tGrade>& right) const&
{
	Polinom<tKoef, tGrade> res;
	for (auto it = myList.begin(); it != myList.end(); it++)
	{
		for (auto jt = right.myList.begin(); jt != right.myList.end(); jt++)
			res.addMonom(*it - *jt);
	}
	for (auto jt = right.myList.begin(); jt != right.myList.end(); jt++)
	{
		if (find(res.myList.begin(), res.myList.end(), *jt) == res.myList.end())
			res.addMonom(*jt);
	}
	res.myList.sort();
	return res;
}

template <typename tKoef, typename tGrade>
Polinom<tKoef, tGrade> Polinom<tKoef, tGrade>::operator* 
(const Polinom<tKoef, tGrade>& right) const&
{
	Polinom<tKoef, tGrade> res;
	for (auto it = myList.begin(); it != myList.end(); it++)
	{
		for (auto jt = right.myList.begin(); jt != right.myList.end(); jt++)
			res.addMonom(*it * *jt);
	}
	res.myList.sort();
	return res;
}

template <typename tKoef, typename tGrade>
Polinom<tKoef, tGrade> Polinom<tKoef, tGrade>::operator/ 
(Polinom<tKoef, tGrade>& right) const&
{
	Polinom<tKoef, tGrade> res = *this;
	for (auto it = myList.begin(); it != myList.end(); it++)
	{
		if (*it > *right.myList.begin())
			break;
		Monom<tKoef, tGrade> tmpMon = *it / *right.myList.begin();
		res.myList.push_back(tmpMon);
		Polinom<tKoef, tGrade> tmpRight = right;
		for (auto jt = tmpRight.myList.begin(); jt != tmpRight.myList.end(); jt++)
			*jt = *jt * tmpMon;
		res = res - tmpRight;
	}
	return res;
}


template <typename tKoef, typename tGrade>
Polinom<tKoef, tGrade> Polinom<tKoef, tGrade>::operator% 
(Polinom<tKoef, tGrade>& right) const&
{
	Polinom<tKoef, tGrade> fullPart = *this / right;
	return (*this - fullPart * right);
}

template <typename tKoef, typename tGrade>
Polinom<tKoef, tGrade> Polinom<tKoef, tGrade>::operator^
(tGrade deg) const&
{
	Polinom<tKoef, tGrade> basePol = *this;
	Polinom<tKoef, tGrade> res = *this;
	for (auto i = 1; i < abs(deg); i++)
		res = res * basePol;
	return res;
}

template <typename tKoef, typename tGrade>
Polinom<tKoef, tGrade> Polinom<tKoef, tGrade>::defference() const&
{
	Polinom<tKoef, tGrade> res;
	for (auto it = myList.begin(); it != myList.end(); it++)
		res.addMonom((*it).proizv());
	return res;
}

template <typename tKoef, typename tGrade>
tKoef Polinom<tKoef, tGrade>::mean(const tKoef& x) const&
{
	tKoef result = 0;
	for (auto it = myList.begin(); it != myList.end(); it++)
		result += (*it).mean(x);
	return result;
}

template <typename tKoef, typename tGrade>
Polinom<tKoef, tGrade> Polinom<tKoef, tGrade>::superPos
(const Polinom<tKoef, tGrade>& right) const&
{
	Polinom<tKoef, tGrade> result;
	for (auto it = myList.begin(); it != myList.end(); it++)
	{
		tGrade tmpDeg = (*it).getDeg();
		Polinom<tKoef, tGrade> tmpRes = right ^ tmpDeg;
		tKoef k = (*it).getKoef();
		for (auto jt = tmpRes.myList.begin(); jt != tmpRes.myList.end(); jt++)
			*jt = *jt * k;
		result = result + tmpRes;
	}
	return result;
}

template <typename tKoef, typename tGrade>
ostream& operator<<(ostream& out, const Polinom<tKoef, tGrade>& fr)
{
	fr.myList.sort();
	for (auto it : fr.myList)
		out << it;
	return out;
}