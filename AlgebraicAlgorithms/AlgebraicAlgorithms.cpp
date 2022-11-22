#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include <chrono>
#include <numeric>

#include "LogDuration.hpp"
#include "Tester.hpp"

using namespace std::chrono;

double PowNaive(double n, int pow)
{
    double res = 0;
    while (pow--)
    {
        res *= n;
    }
    return res;
}

double PowMult(double n, int pow)
{
    int two_pow_cnt = 0; int t = pow;
    int two_pow = 1;
    while (t > 1)
    {
        two_pow_cnt += 1;
        two_pow *= 2;
        t /= 2;
    }
    double res = n;
    for (; two_pow_cnt > 0; --two_pow_cnt)
    {
        res *= res;
    }
    for (int i = 0; i < pow - two_pow; ++i)
    {
        res *= n;
    }
    return res;
}


double PowTwoFactor(double n, int pow)
{
    double res = 1; double cur = n;
    while (pow)
    {
        if (pow % 2 == 1)
        {
            res *= cur;
        }
        cur *= cur;
        pow /= 2;
    }
    return res;
}

size_t FibNaive(size_t n)
{
    if (n < 2)
    {
        return n;
    }
    return FibNaive(n - 1) + FibNaive(n - 2);
}

size_t FibIter(size_t n)
{
    if (n < 2)
        return n;
    size_t prev2 = 0;
    size_t prev = 1;
    size_t cur = 1;
    while (--n)
    {
        prev2 = prev;
        prev = cur;
        cur = prev + prev2;
    }
    return prev;
}

size_t FibGoldenRatio(size_t n)
{
    long double phi = (sqrtl(5) + 1) / 2;
    return powl(phi, n) / sqrtl(5) + 1 / 2.;
}

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

size_t FibMatrix(size_t n)
{
    if (n < 2)
        return n;
    Matrix<size_t> m({ {0,1}, {1,1} });
    return m.Pow(n+1)[0][0];
}

bool IsPrimeNaive(size_t n)
{
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    for (int i = 2; i < n; ++i)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
size_t FindPrimeCountNaive(size_t n)
{
    size_t cnt = 0;
    for (int i = 2; i <= n; ++i)
    {
        if (IsPrimeNaive(i))
            ++cnt;
    }
    return cnt;
}

bool IsPrimeOnlyPrimesDivision(size_t n, std::vector<size_t>& primes)
{
    if (n == 1)
        return false;
    if (n == 2)
        return true;
    for (size_t i = 0; primes[i] <= sqrt(n); ++i)
    {
        if (n % primes[i] == 0)
            return false;
    }
    primes.push_back(n);
    return true;
}

size_t FindPrimeCountDivPrime(size_t n)
{
    size_t cnt = 0;
    std::vector<size_t> primes{ 2 };
    for (size_t i = 2; i <= n; ++i)
    {
        cnt += IsPrimeOnlyPrimesDivision(i, primes);
    }
    return cnt;
}

int FindPrimeCountSieve(int n)
{
    LOG_DURATION("PRIME SIEVE FOR N = " + std::to_string(n) + "\n");
    std::vector<int> v(n+1, true);
    for (size_t i = 2; i * i <= n; ++i)
    {
        if (v[i])
        {
            for (size_t j = i * i; j <= n; j += i)
            {
                v[j] = false;
            }
        }
    }
    return std::accumulate(v.begin() + 2, v.end(), 0);
}

int FindPrimeCountSieveLinear(int n)
{
    if (n > 1e8)
    {
        std::cout << "Cowardly refusing to run memory intensive Linear Sieve on input " + std::to_string(n) << std::endl;
        return -1;
    }
    LOG_DURATION("PRIME SIEVE LINEAR FOR N = " + std::to_string(n) + "\n");
    std::vector<int> lp(n + 1, 0);
    std::vector<int> pr;
    for (int i = 2; i <= n; ++i)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(lp[i]);
        }
        for (int j = 0; i * pr[j] <= n; ++j)
        {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i])
                break;
        }
    }
    return pr.size();
}

int FindPrimeCountSieveCompact(int n)
{
    LOG_DURATION("PRIME SIEVE COMPACT FOR N = " + std::to_string(n) + "\n");
    std::vector<bool> v(n + 1, true);
    for (size_t i = 2; i * i <= n; ++i)
    {
        if (v[i])
        {
            for (size_t j = i * i; j <= n; j += i)
            {
                v[j] = false;
            }
        }
    }
    return std::accumulate(v.begin() + 2, v.end(), 0);
}

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

int main()
{   
    {
        
        Tester tester("prime_count_tests", ".in", ".out", [](std::string str)
            {
                return std::to_string(FindPrimeCountSieveLinear(strtoul(str.data(), NULL, 10)));
            });
        tester.Run();
    }
    {
        Tester tester("prime_count_tests", ".in", ".out", [](std::string str)
            {
                return std::to_string(FindPrimeCountSieve(strtoul(str.data(), NULL, 10)));
            });
        tester.Run();
    }
    {
        Tester tester("prime_count_tests", ".in", ".out", [](std::string str)
            {
                return std::to_string(FindPrimeCountSieveCompact(strtoul(str.data(), NULL, 10)));
            });
        tester.Run();
    }
    {
        LOG_DURATION("PRIME NAIVE");
        //std::cout << FindPrimeCountNaive(n) << std::endl;
    }

    char c;
    std::cin >> std::ws;
    std::cin.get();
}
