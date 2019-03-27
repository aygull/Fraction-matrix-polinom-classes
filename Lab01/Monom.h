#pragma once

using namespace std;

template <typename tKoef, typename tGrade>
class Monom
{
public:
	Monom() = default;
	Monom(tKoef, tGrade, char);
	~Monom() = default;

	bool operator< (const Monom<tKoef, tGrade>&) const&;
	bool operator> (const Monom<tKoef, tGrade>&) const&;
	Monom<tKoef, tGrade> operator+ (const Monom<tKoef, tGrade>&) const&;
	Monom<tKoef, tGrade> operator- (const Monom<tKoef, tGrade>&) const&;
	Monom<tKoef, tGrade> operator* (const Monom<tKoef, tGrade>&) const&;
	Monom<tKoef, tGrade> operator* (tKoef) const&;
	Monom<tKoef, tGrade> operator/ (const Monom<tKoef, tGrade>&) const&;
	Monom<tKoef, tGrade> proizv() const&;
	tKoef mean(const tKoef&) const&;
	tGrade getDeg() const&;
	tKoef getKoef() const& { return koef; }
	bool operator== (const Monom<tKoef, tGrade>&) const&;
	friend ostream& operator<< <tKoef, tGrade>(ostream&, const Monom&);

private:
	tKoef koef;
	tGrade degree;
	char c;
};

template <typename tKoef, typename tGrade>
Monom<tKoef, tGrade>::Monom(tKoef k, tGrade deg, char symb)
{
	koef = k;
	degree = deg;
	c = symb;
}

template <typename tKoef, typename tGrade>
Monom<tKoef, tGrade> Monom<tKoef, tGrade>::operator+ 
(const Monom<tKoef, tGrade>& right) const&
{
	if (degree == right.degree && c == right.c)
		koef += right.koef;
	return *this;
}

template <typename tKoef, typename tGrade>
Monom<tKoef, tGrade> Monom<tKoef, tGrade>::operator- 
(const Monom<tKoef, tGrade>& right) const&
{
	Monom<tKoef, tGrade> res = *this;
	if (degree == right.degree && c == right.c)
		res.koef -= right.koef;
	return res;
}

template <typename tKoef, typename tGrade>
Monom<tKoef, tGrade> Monom<tKoef, tGrade>::operator* 
(const Monom<tKoef, tGrade>& right) const&
{
	Monom<tKoef, tGrade> res = *this;
	res.koef = res.koef * right.koef;
	if (c == right.c)
		res.degree += right.degree;
	return res;
}

template <typename tKoef, typename tGrade>
Monom<tKoef, tGrade> Monom<tKoef, tGrade>::operator* (tKoef k) const&
{
	return Monom(koef * k, degree, c);
}

template <typename tKoef, typename tGrade>
Monom<tKoef, tGrade> Monom<tKoef, tGrade>::proizv() const&
{
	koef *= degree;
	degree--;
	return Monom(koef * degree, degree - 1, c);
}

template <typename tKoef, typename tGrade>
tKoef Monom<tKoef, tGrade>::mean(const tKoef& x) const&
{
	return (koef * pow(x, degree));
}

template <typename tKoef, typename tGrade>
Monom<tKoef, tGrade> Monom<tKoef, tGrade>::operator/
(const Monom<tKoef, tGrade>& right) const&
{
	Monom<tKoef, tGrade> tmpMon;
	tmpMon.koef = koef / right.koef;
	tmpMon.degree = degree - right.degree;
	tmpMon.c = c;
	return tmpMon;
}

template <typename tKoef, typename tGrade>
bool Monom<tKoef, tGrade>::operator< (const Monom<tKoef, tGrade>& right) const&
{
	if (c != right.c)
		return c < right.c;
	else if (degree != right.degree) 
		return degree > right.degree;
	return false;
}

template <typename tKoef, typename tGrade>
bool Monom<tKoef, tGrade>::operator> (const Monom<tKoef, tGrade>& right) const&
{
	if (c != right.c) return c > right.c;
	else return degree < right.degree;
}

template <typename tKoef, typename tGrade>
bool Monom<tKoef, tGrade>::operator== (const Monom<tKoef, tGrade>& right) const&
{
	return (degree == right.degree && c == right.c);
}

template <typename tKoef, typename tGrade>
tGrade Monom<tKoef, tGrade>::getDeg() const&
{
	return degree;
}

template <typename tKoef, typename tGrade>
ostream& operator<< (ostream& out, const Monom<tKoef, tGrade> &mon)
{
	if (mon.koef > 0)
		out << "+";
	out << mon.koef << mon.c << "^" << mon.degree;
	return out;
}
