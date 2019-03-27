#pragma once
#include <vector>

using namespace std;

template <typename tElems, int sizeMatr = 0>
class Matrix
{
public:
	Matrix();
	~Matrix() = default;
	Matrix<tElems, sizeMatr> operator+(const Matrix<tElems, sizeMatr>&) const&;
	Matrix<tElems, sizeMatr> operator-(const Matrix<tElems, sizeMatr>&) const&;
	Matrix<tElems, sizeMatr> operator*(const Matrix<tElems, sizeMatr>&) const&;
	Matrix<tElems, sizeMatr> operator=(const Matrix<tElems, sizeMatr>&)&;
	tElems determ() const&;
	Matrix<tElems, sizeMatr> reverse() const&;
	friend ostream& operator<< <tElems>(ostream&, const Matrix<tElems, sizeMatr>&);
	friend istream& operator>> <tElems>(istream&, Matrix<tElems, sizeMatr>&);
private:
	vector<vector<tElems>> matr;
};

template <typename tElems, int sizeMatr>
Matrix<tElems, sizeMatr>::Matrix()
{
	matr.resize(sizeMatr);
	for (int i = 0; i < sizeMatr; i++)
		matr[i].resize(sizeMatr);
}

template <typename tElems, int sizeMatr>
Matrix<tElems, sizeMatr> Matrix<tElems, sizeMatr>::operator+(const Matrix<tElems, 
	sizeMatr>& right) const&
{
	Matrix<tElems, sizeMatr> res;
	for (int i = 0; i < sizeMatr; i++)
	{
		for (int j = 0; j < sizeMatr; j++)
			res.matr[i][j] = matr[i][j] + right.matr[i][j];
	}
	return res;
}

template <typename tElems, int sizeMatr>
Matrix<tElems, sizeMatr> Matrix<tElems, sizeMatr>::operator-(const Matrix<tElems, 
	sizeMatr>& right) const&
{
	Matrix<tElems, sizeMatr> res;
	for (int i = 0; i < sizeMatr; i++)
	{
		for (int j = 0; j < sizeMatr; j++)
			res.matr[i][j] = matr[i][j] - right.matr[i][j];
	}
	return res;
}

template <typename tElems, int sizeMatr>
Matrix<tElems, sizeMatr> Matrix<tElems, sizeMatr>::operator*
(const Matrix<tElems, sizeMatr>& right) const&
{
	Matrix<tElems> res;
	for (int i = 0; i < sizeMatr; i++)
	{
		for (int j = 0; j < sizeMatr; j++)
		{
			res.matr[i][j] = 0;
			for (int k = 0; k < sizeMatr; k++)
				res.matr[i][j] = res.matr[i][j] + matr[i][k] * right.matr[k][j];
		}
	}
	return res;
}

template <typename tElems, int sizeMatr>
Matrix<tElems, sizeMatr> Matrix<tElems, sizeMatr>::operator=(const Matrix<tElems, sizeMatr>& right)&
{
	for (int i = 0; i < sizeMatr; i++)
	{
		for (int j = 0; j < sizeMatr; j++)
			matr[i][j] = right.matr[i][j];
	}
	return *this;
}

template <typename tElems, int sizeMatr>
tElems Matrix<tElems, sizeMatr>::determ() const&
{
	Matrix<tElems, sizeMatr> mt = *this;
	tElems res = 1;
	for (int i = 0; i < sizeMatr - 1; i++)
	{
		if (mt.matr[i][i] == 0)
			res = res * -1;
		int tmp = i;
		while (mt.matr[tmp][i] == 0 && tmp < sizeMatr)
			tmp++;
		if (tmp == sizeMatr)
		{
			res = 0;
			return res;
		}
		for (int j = 0; j < sizeMatr; j++)
		{
			tElems tmpMean = mt.matr[i][j];
			mt.matr[i][j] = mt.matr[tmp][j];
			mt.matr[tmp][j] = tmpMean;
		}
		for (int k = i + 1; k < sizeMatr; k++)
		{
			tElems koef = mt.matr[k][i] / mt.matr[i][i];
			for (int j = i; j < sizeMatr; j++)
				mt.matr[k][j] = mt.matr[k][j] - mt.matr[i][j] * koef;
		}
		res = res * mt.matr[i][i];
	}
	return res * mt.matr[sizeMatr - 1][sizeMatr - 1];
}

template <typename tElems, int sizeMatr>
Matrix<tElems, sizeMatr> Matrix<tElems, sizeMatr>::reverse() const&
{
	tElems det = determ();
	if (det == 0)
		throw std::logic_error("Determinant = 0.");
	Matrix<tElems, sizeMatr> res, mt = *this;
	for (int i = 0; i < sizeMatr; i++)
	{
		for (int j = 0; j < sizeMatr; j++)
		{
			if (i == j)
				res.matr[i][j] = 1;
			else
				res.matr[i][j] = 0;
		}
	}
	for (int i = 0; i < sizeMatr - 1; i++)
	{
		int tmp = i;
		while (matr[tmp][i] == 0 && tmp < sizeMatr)
			tmp++;
		for (int j = 0; j < sizeMatr; j++)
		{
			tElems tmpMean = mt.matr[i][j];
			mt.matr[i][j] = mt.matr[tmp][j];
			mt.matr[tmp][j] = tmpMean;
			tmpMean = res.matr[i][j];
			res.matr[i][j] = res.matr[tmp][j];
			res.matr[tmp][j] = tmpMean;
		}
		tElems tmpKoef = mt.matr[i][i];
		for (int j = 0; j < sizeMatr; j++)
		{
			mt.matr[i][j] = mt.matr[i][j] / tmpKoef;
			res.matr[i][j] = res.matr[i][j] / tmpKoef;
		}
		for (int k = i + 1; k < sizeMatr; k++)
		{
			tElems koef = mt.matr[k][i];
			for (int j = 0; j < sizeMatr; j++)
			{
				mt.matr[k][j] = mt.matr[k][j] - mt.matr[i][j] * koef;
				res.matr[k][j] = res.matr[k][j] - res.matr[i][j] * koef;
			}
		}
	}
	tElems tmpKoef = mt.matr[sizeMatr - 1][sizeMatr - 1];
	for (int j = 0; j < sizeMatr; j++)
	{
		mt.matr[sizeMatr - 1][j] = mt.matr[sizeMatr - 1][j] / tmpKoef;
		res.matr[sizeMatr - 1][j] = res.matr[sizeMatr - 1][j] / tmpKoef;
	}
	for (int i = sizeMatr - 1; i > 0; i--)
	{
		for (int k = i - 1; k >= 0; k--)
		{
			tElems koef = mt.matr[k][i];
			for (int j = 0; j < sizeMatr; j++)
				res.matr[k][j] = res.matr[k][j] - res.matr[i][j] * koef;
		}
	}
	return res;
}

template <typename tElems, int sizeMatr>
istream& operator>> (istream& in, Matrix<tElems, sizeMatr>& mt)
{
	for (int i = 0; i < sizeMatr; i++)
	{
		for (int j = 0; j < sizeMatr; j++)
			in >> mt.matr[i][j];
	}
	return in;
}

template <typename tElems, int sizeMatr>
ostream& operator<< (ostream& out, const Matrix<tElems, sizeMatr>& mt)
{
	for (int i = 0; i < sizeMatr; i++)
	{
		for (int j = 0; j < sizeMatr; j++)
			out << mt.matr[i][j] << " ";
		out << endl;
	}
	return out;
}