// adventofcode.com/2023/day/3
//$clang++ main.cpp --std=c++17 -o main
//$./main

// build with debug:
//$clang++ main.cpp --std=c++17 -o main -g
//$lldb main

// breakpoint set -n isPartNumber
// breakpoint list
// r <- run
// s <- step
// c <- continue
// n <- step over
// breakpoint set -f main.cpp -l 65
// print <variable_name>

// output should be 539713 for input.txt

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
using namespace std;

string trim(string str){
    return regex_replace(str, regex("(^[ ]+)|([ ]+$)"),"");
}

template <typename T>
void printVector(const vector<T> v)
{
    for (auto x : v)
        cout << x << " ";
    cout << endl;
}

class Schematic {
    public:
        Schematic(vector<string> lines, vector<size_t> part_numbers) : m_lines{lines}, m_part_numbers{part_numbers}{}
        static Schematic create(const vector<string> lines);
        auto getLines() { return m_lines; }
        auto getPartNumbers() { return m_part_numbers; }
        size_t size() { return m_lines.size(); }
        void visualize(ostream& os);
        size_t sumPartNumbers() {
            size_t total = 0;
            for (auto x: m_part_numbers)
                total += x;
            return total;
        }

    private:
        vector<string> m_lines;
        vector<size_t> m_part_numbers;

        static vector<size_t> extractPartNumbers(vector<string> lines);
        static bool isPartNumber(const string match, const size_t pos, const vector<string> neighbours);
};
void Schematic::visualize(ostream& os) {
for (auto x: getLines()) {
        os << x << endl;
    }
}

Schematic Schematic::create(const vector<string> lines) {
    return Schematic{lines, extractPartNumbers(lines)};
}

bool Schematic::isPartNumber(const string match, const size_t pos, const vector<string> neighbours){
    //regex symbol_regex("#|\\$|\\*|\\+");
    // regex is anything that is not a digit or decimal!!
    regex symbol_regex("[^\\d\\.]");
    for (auto line: neighbours) {
        
        string adjacent_str;
        if (pos == 0) {
            adjacent_str = line.substr(pos, match.length() + 2);
        }
        else {
            adjacent_str = line.substr(pos - 1, match.length() + 2);
        }
        cout << adjacent_str << endl;

        if (regex_search(adjacent_str, symbol_regex))
            return true;
    }
    
    return false;
}

vector<size_t> Schematic::extractPartNumbers(vector<string> lines) {
    vector<size_t> part_numbers;

    for (size_t line_no = 0; line_no < lines.size(); line_no++)
    {
        auto line = lines[line_no];

        regex digit_regex("(\\d+)");
        auto digits_begin = sregex_iterator(line.begin(), line.end(), digit_regex);
        auto digits_end = sregex_iterator();

        for (sregex_iterator i = digits_begin; i != digits_end; ++i)
        {
            smatch match = *i;
            cout << match.str() << " found at " << match.position() << " in line " << line_no << ": " << line << endl;

            if (line_no > 0) {
                auto prev_line = lines[line_no - 1];
            }
            auto first = lines.begin() + line_no - 1;
            if (line_no == 0)
                first = lines.begin() + line_no;
            auto last = lines.begin() + line_no + 2;
            if ((line_no + 1) == lines.size())
                last = lines.begin() + line_no + 1;

            if (isPartNumber(match.str(), match.position(), vector<string>(first, last)))
                part_numbers.push_back(stoi(match.str()));
        }
    }

    return part_numbers;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << '[';
    for (size_t i = 0, e = v.size(); i != e; ++i) {
        os << '"' << v[i] << '"';
        if (i + 1 != e)
            os << ", ";
    }
    os << ']';
    return os;
}

int main()
{
    string line;

    vector<string> lines;
    ifstream myfile("input.txt");
    if (!myfile.is_open())
    {
        cout << "Unable to open file";
        return -1;
    }
    
    while (getline(myfile, line))
    {
        lines.push_back(trim(line));
    }
    myfile.close();

    auto schematic = Schematic::create(lines);
    schematic.visualize(cout);
    cout << schematic.size() << endl;

    cout << schematic.getLines() << endl;
    cout << schematic.getPartNumbers() << endl;
    cout << "sum of part numbers: " << schematic.sumPartNumbers() << endl;
    
    return 0;
}