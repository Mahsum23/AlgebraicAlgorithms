#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include <chrono>
#include <numeric>
#include <format>

#include "LogDuration.hpp"
#include "Tester.hpp"
#include "algo.hpp"
#include "lint.hpp"

using namespace std::chrono;

void TestPow()
{
    {
        Tester<std::string(std::string, std::string), 2> tester("pow_tests", "Pow Naive",
            [](std::string arg1, std::string arg2)
            {
                return std::to_string(PowNaive(std::stod(arg1),
                    std::stoull(arg2)));
            });
        tester.Run();
    }
    {
        Tester<std::string(std::string, std::string), 2> tester("pow_tests", "Pow Mult",
            [](std::string arg1, std::string arg2)
            {
                return std::to_string(PowMult(std::stod(arg1),
                    std::stoull(arg2)));
            });
        tester.Run();
    }
    {
        Tester<std::string(std::string, std::string),2> tester("pow_tests", "Pow Two Factor", 
            [](std::string arg1, std::string arg2)
            {
                return std::to_string(PowTwoFactor(std::stod(arg1),
                    std::stoull(arg2)));
            });
        tester.Run();
    }
}

void TestFibo()
{
    {
        Tester<std::string(std::string), 1> tester("fibo_tests", "Naive Fibo",
            [](std::string str)
            {
                return std::to_string(FibNaive(strtoull(str.data(), NULL, 10)));
            });
        tester.Run();
    }
    {

        Tester<std::string(std::string), 1> tester("fibo_tests", "Iter Fibo",
            [](std::string str)
            {
                return std::to_string(FibIter(strtoull(str.data(), NULL, 10)));
            });
        tester.Run();
    }
    {
        Tester<std::string(std::string), 1> tester("fibo_tests", "Matrix Fibo",
            [](std::string str)
            {
                return std::to_string(FibMatrix(strtoull(str.data(), NULL, 10)));
            });
        tester.Run();
    }
    {
        Tester<std::string(std::string), 1> tester("fibo_tests", "Golden Ratio Fibo",
            [](std::string str)
            {
                return std::to_string(FibGoldenRatio(stoull(str)));
            });
        tester.Run();
    }
}

void TestSieve()
{
    {
        Tester<std::string(std::string), 1> tester("prime_count_tests", "Simple Sieve", 
            [](std::string str)
            {
                return std::to_string(FindPrimeCountSieve(strtoul(str.data(), NULL, 10)));
            });
        tester.Run();
    }
    {

        Tester<std::string(std::string), 1> tester("prime_count_tests", "Linear Sieve",
            [](std::string str)
            {
                return std::to_string(FindPrimeCountSieveLinear(strtoul(str.data(), NULL, 10)));
            });
        tester.Run();
    }
    {
        Tester<std::string(std::string), 1> tester("prime_count_tests", "Sieve Compact", 
            [](std::string str)
            {
                return std::to_string(FindPrimeCountSieveCompact(strtoul(str.data(), NULL, 10)));
            });
        tester.Run();
    }
}


int main()
{
    std::ofstream out;

    //std::cout << "============================================" << std::endl;
    //std::cout << "\t\t\t\tPOW\t\t\t\t" << std::endl;
    //std::cout << "============================================" << std::endl;
    //TestPow();

    //std::cout << "============================================" << std::endl;
    //std::cout << "\t\t\t\tSIEVE\t\t\t\t" << std::endl;
    //std::cout << "============================================" << std::endl;
    //TestSieve();

    std::cout << "============================================" << std::endl;
    std::cout << "\t\t\t\tFIBO\t\t\t\t" << std::endl;
    std::cout << "============================================" << std::endl;
    TestFibo();

    
    char c;
    std::cin >> std::ws;
    std::cin.get();
}

