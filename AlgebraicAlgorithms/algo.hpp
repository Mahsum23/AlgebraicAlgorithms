#pragma once

#include "lint.hpp"

double PowNaive(double n, size_t pow);
double PowMult(double n, size_t pow);
double PowTwoFactor(double n, size_t pow);

apa::lint FibNaive(apa::lint n);
apa::lint FibIter(apa::lint n);
size_t FibGoldenRatio(size_t n);
size_t FibMatrix(size_t n);

bool IsPrimeNaive(size_t n);
bool IsPrimeOnlyPrimesDivision(size_t n, std::vector<size_t>& primes);
size_t FindPrimeCountNaive(size_t n);
size_t FindPrimeCountDivPrime(size_t n);

int FindPrimeCountSieve(int n);
int FindPrimeCountSieveLinear(int n);
int FindPrimeCountSieveCompact(int n);

template <typename T>
class Matrix
{
public:
    Matrix(const std::vector<std::vector<T>>& values)
    {
        assert(values[0].size() == values.size());
        values_ = values;
        size_ = values_.size();
    }
    Matrix(std::vector<std::vector<T>>&& values)
    {
        assert(values[0].size() == values.size());
        values_ = std::move(values);
        size_ = values_.size();
    }

    std::vector<T>& operator[](int i)
    {
        return values_[i];
    }

    const std::vector<T>& operator[](int i) const
    {
        return values_[i];
    }

    Matrix operator*(const Matrix& other) const
    {
        assert(values_.size() == other.values_.size());
        std::vector<std::vector<T>> res = values_;
        for (int i = 0; i < values_.size(); ++i)
        {
            for (int j = 0; j < values_[0].size(); ++j)
            {
                T cur = 0;
                for (T k = 0; k < values_[0].size(); ++k)
                {
                    cur += values_[i][k] * other.values_[k][j];
                }
                res[i][j] = cur;
            }
        }
        return Matrix(std::move(res));
    }

    Matrix& operator*=(const Matrix& other)
    {
        *this = other * (*this);
        return *this;
    }

    Matrix Pow(int n)
    {
        Matrix res = Matrix::GetIdm(size_);
        Matrix cur = *this;
        while (n)
        {
            if (n % 2 == 1)
            {
                res *= cur;

            }
            cur *= cur;
            n /= 2;
        }
        return res;
    }

    int GetSize() const
    {
        return size_;
    }

    static Matrix GetIdm(int size)
    {
        std::vector<std::vector<T>> val(size, std::vector<T>(size, 0));
        for (int i = 0; i < size; ++i)
        {
            val[i][i] = 1;
        }
        return Matrix(val);
    }

private:
    std::vector<std::vector<T>> values_;
    size_t size_ = 0;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m)
{
    for (int i = 0; i < m.GetSize(); ++i)
    {
        for (int j = 0; j < m.GetSize(); ++j)
        {
            out << m[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}

