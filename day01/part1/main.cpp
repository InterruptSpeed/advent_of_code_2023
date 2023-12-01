// adventofcode.com/2023/day/1
//$clang++ main.cpp -o main
//$./main

// output should be 54338 for input.txt

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

void printVector(const vector<char> v)
{
    for (auto x : v)
        cout << x << " ";
    cout << endl;
}

vector<char> extractDigits(const string str)
{
    vector<char> digits;

    regex digit_regex("(\\d)");
    auto digits_begin = sregex_iterator(str.begin(), str.end(), digit_regex);
    auto digits_end = sregex_iterator();

    for (sregex_iterator i = digits_begin; i != digits_end; ++i)
    {
        smatch match = *i;
        char match_str = match.str().front();
        digits.push_back(match_str);
    }
    //printVector(digits);
    return digits;
}

int extractCalibrationValue(const vector<char> digits)
{
    //cout << digits.size() << endl;
    if (digits.size())
    {
        //cout << digits.front() << " " << digits.back() << endl;
        string calibration_value{digits.front(), digits.back()};
        cout << "Calibration Value is: " << stoi(calibration_value) << endl;
        return stoi(calibration_value);
    }
    return -1;
}

int main()
{
    string line;

    size_t total_calibration_value = 0;

    ifstream myfile("input.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            vector<char> digits = extractDigits(line);
            int calibration_value = extractCalibrationValue(digits);
            if (calibration_value > -1)
            {
                total_calibration_value += calibration_value;
            }
        }
        cout << "Sum of all of the calibration values: " << total_calibration_value << endl;
        myfile.close();
    }

    else
        cout << "Unable to open file";

    return 0;
}