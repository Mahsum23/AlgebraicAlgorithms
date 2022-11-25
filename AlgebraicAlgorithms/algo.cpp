#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include <chrono>
#include <numeric>

#include "algo.hpp"


using namespace std::chrono;

double PowNaive(double n, size_t pow)
{
    double res = 1;
    while (pow--)
    {
        res *= n;
    }
    return res;
}

double PowMult(double n, size_t pow)
{
    int two_pow_cnt = 0; size_t t = pow;
    size_t two_pow = 1;
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


double PowTwoFactor(double n, size_t pow)
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
    if (n > 50)
    {
        std::cout << "too long to compute by naive fibo..." << std::endl;
        return 0;
    }
    if (n < 2)
    {
        return n;
    }
    return FibNaive(n - 1) + FibNaive(n - 2);
}

size_t FibIter(size_t n)
{
    if (n == 100)
    {
        std::cout << 100;
    }
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



size_t FibMatrix(size_t n)
{
    if (n < 2)
        return n;
    Matrix<size_t> m({ {0,1}, {1,1} });
    return m.Pow(n + 1)[0][0];
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
    
    std::vector<int> v(n + 1, true);
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
    //LOG_DURATION(std::format("{} FOR N = ", __FUNCTION__) + std::to_string(n) + "\n");
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