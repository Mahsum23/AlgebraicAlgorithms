#pragma once

#include <iostream>
#include <string>
#include <set>
#include <regex>
#include <filesystem>
#include <functional>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <optional>

namespace fs = std::filesystem;
using namespace std::literals;


class Tester
{
public:

    Tester(const std::string& folder, const std::string & in_ext, const std::string& out_ext, std::function<std::string(std::string)> function)
        : in_ext_(in_ext), out_ext_(out_ext), function_(function), folder_(folder)
    {

    }

    void Run()
    {
        std::set<fs::path, AlphaNumSort> files;
        for (const auto& file : fs::directory_iterator(fs::path(folder_)))
        {
            std::string in_filename = file.path().string();
            if (file.path().filename().string().find(in_ext_) != std::string::npos)
            {
                files.insert(file);
            }
            
        }
        for (const auto& file : files)
        {
            {
                std::ifstream in_file(file.string());
                std::string in_line;
                getline(in_file, in_line);

                std::string out_filename = folder_ + "\\" + file.stem().string() + out_ext_;
                std::ifstream out_file(out_filename);
                std::string out_line;
                getline(out_file, out_line);
                std::string result = function_(in_line);
                if (result == out_line)
                {
                    std::cout << file.filename() << ": " << "PASSED" << std::endl;
                    std::cout << "\tExpected: " << out_line << "\n\tResult: " << result << std::endl << std::endl;
                }
                else
                {
                    std::cout << file.filename() << ": " << "FAILED" << std::endl;
                    std::cout << "\tINPUT: " << in_line << std::endl;
                    std::cout << '\t' << "SHOULD BE: " << out_line << "\n\tRESULT: " << result << std::endl << std::endl;
                }
                std::cout << "=======================================================\n\n";
            }
        }
    }

private:

    struct AlphaNumSort
    {
        std::optional<int> GetFirstNumber(const std::string& s) const
        {
            auto start = std::find_if(s.begin(), s.end(), [](char c) { return std::isdigit(c); });
            if (start == s.end())
                return std::nullopt;
            auto end = std::find_if(start + 1, s.end(), [](char c) { return std::isdigit(c); });
            return std::stoi(s.substr(start - s.begin(), (end - s.begin()) - (start - s.begin()) + 1));
        }

        bool operator()(const fs::path& p1, const fs::path& p2) const
        {
            std::string s1 = p1.string();
            std::string s2 = p2.string();
            auto num1 = GetFirstNumber(p1.string());
            auto num2 = GetFirstNumber(p2.string());
            if (!num1 || !num2)
                return s1 < s2;
            return num1 < num2;
        }
    };


    std::string in_ext_;
    std::string out_ext_;
    std::string folder_;
    std::function<std::string(std::string)> function_;
};