// adventofcode.com/2023/day/1#part2
//$clang++ main.cpp --std=c++17 -o main
//$./main

// output should be 53389 for input.txt

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
using namespace std;

void printVector(const vector<char> v)
{
    for (auto x : v)
        cout << x << " ";
    cout << endl;
}

vector<char> extractDigits(string str)
{
    cout << str << endl;
    // regex isn't happy with overlapping words like one eight being oneight
    // preprocess the string
    map<string, string> word_overlap_map{{"oneight", "oneeight"}, {"twone", "twoone"}, {"threeight", "threeeight"}, {"fiveight", "fiveeight"}, {"eightwo", "eighttwo"}, {"eighthree", "eightthree"}, {"eighten", "eightten"}, {"nineight", "nineeight"}};
    for (auto const& [key, val] : word_overlap_map){
        str = regex_replace(str, regex(key), val);
    }   

    map<string, char> word_digit_map{{"zero", '0'}, {"one", '1'}, {"two", '2'}, {"three", '3'}, {"four", '4'}, {"five", '5'}, {"six", '6'}, {"seven", '7'}, {"eight", '8'}, {"nine", '9'}};
    vector<char> digits;

    // TODO: build regex from map keys plus \d ??
    regex digit_regex("(\\d|zero|one|two|three|four|five|six|seven|eight|nine)");
    auto digits_begin = sregex_iterator(str.begin(), str.end(), digit_regex);
    auto digits_end = sregex_iterator();

    cout << str << endl;
    for (sregex_iterator i = digits_begin; i != digits_end; ++i)
    {
        smatch match = *i;
        string match_str = match.str();       
        if (word_digit_map.find(match_str) == word_digit_map.end()) { 
            // not found in map; must be a single digit
            digits.push_back(match_str.front());
        } else {
            digits.push_back(word_digit_map[match_str]);
        }       
    }
    printVector(digits);
    return digits;
}

int extractCalibrationValue(const vector<char> digits)
{
    cout << digits.size() << endl;
    if (digits.size())
    {
        cout << digits.front() << " " << digits.back() << endl;
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
            
           cout << "**********" << endl;
        }
        cout << "Sum of all of the calibration values: " << total_calibration_value << endl;
        myfile.close();
    }

    else
        cout << "Unable to open file";

    return 0;
}