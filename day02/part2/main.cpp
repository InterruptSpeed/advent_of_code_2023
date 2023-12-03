// adventofcode.com/2023/day/2#part2
//$clang++ main.cpp --std=c++17 -o main
//$./main

// output should be 69110 for input.txt

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <regex>
using namespace std;

template <typename T, size_t n>
void printArray(const array<T, n> a)
{
    for(size_t i = 0; i < n; i++)
        cout << '\t' << a[i] << endl;
}

template <typename T>
void printVector(const vector<T> v)
{
    for (auto x : v)
        cout << '\t' << x << endl;
}

string trim(string str){
    return regex_replace(str, regex("(^[ ]+)|([ ]+$)"),"");
}

vector<string> extractTokens(const string str, const char delim = ':')
{
    vector<string> tokens;

    size_t prev_pos = 0;
    size_t found = 0;
    while (found < str.length()) {
        found = str.find(delim, prev_pos);

        if (found > str.length()) {
            tokens.push_back(trim(str.substr(prev_pos)));   
            break;
        } else {
            tokens.push_back(trim(str.substr(prev_pos, found - prev_pos)));
            prev_pos = found + 1;
        }
    }

    return tokens;
}

class Cubes {
    private:
        size_t m_r;
        size_t m_g;
        size_t m_b;
    
    public:
        Cubes(size_t r, size_t g, size_t b) : m_r{r}, m_g{g}, m_b{b} {}

        void update(const string colour, const size_t value) {
            if (colour == "red") {
                if (value > m_r)
                    m_r = value;
            } else if (colour == "green") {
                if (value > m_g)
                    m_g = value;
            } else if (colour == "blue") {
                if (value > m_b)
                    m_b = value;
            } else {
                cout << colour.length() << endl;
                cout << colour << endl;
                throw domain_error("invalid colour");
            }
        }

        size_t getR() { return m_r; }
        size_t getG() { return m_g; }
        size_t getB() { return m_b; }

        size_t getPower() {
            return m_r * m_g * m_b;
        }

        friend ostream& operator<<(ostream& os, const Cubes& cubes) {
            os << cubes.m_r << " red, " << cubes.m_g << " green, and " << cubes.m_b << " blue cubes for a total power of " << endl;
            return os;
        }

        friend bool operator<=(const Cubes& lhs, const Cubes& rhs)
        {
            return (lhs.m_r <= rhs.m_r) && (lhs.m_g <= rhs.m_g) && (lhs.m_b <= rhs.m_b);
        }

        friend bool operator==(const Cubes& lhs, const Cubes& rhs)
        {
            return (lhs.m_r == rhs.m_r) && (lhs.m_g == rhs.m_g) && (lhs.m_b == rhs.m_b);
        }
};

class Bag {
    public:
        Bag(size_t game_id, size_t num_reveals, Cubes cubes_revealed) : m_game_id(game_id), m_num_reveals(num_reveals), m_cubes_revealed(cubes_revealed){}
        static Bag create(const string line);
        friend ostream& operator<<(ostream& os, const Bag& bag);

        auto getGameID() {
            return m_game_id;
        }

        auto getCubesRevealed() {
            return m_cubes_revealed;
        }

    private:
        size_t m_game_id;
        size_t m_num_reveals;
        Cubes m_cubes_revealed;
};

Bag Bag::create(const string line) {
    size_t id = 0;
    Cubes cubes_revealed{0, 0, 0};

    vector<string> tokens = extractTokens(line);
    if (tokens.size() != 2)
        throw domain_error("invalid input line");

    // game section
    const string game_section = trim(tokens.front());
    //cout << game_section << endl;
    
    regex game_id_regex("(\\d+)$");
    auto game_id_begin = sregex_iterator(game_section.begin(), game_section.end(), game_id_regex);
    auto game_id_end = sregex_iterator();

    for (sregex_iterator i = game_id_begin; i != game_id_end; ++i)
    {
        smatch match = *i;
        id = stoi(match.str());
    }

    // reveals section
    const string reveals_section = trim(tokens.back());
    //cout << reveals_section << endl;
    tokens = extractTokens(reveals_section, ';');

    //printVector<string>(tokens);
    for (auto reveal: tokens) {
        auto samples = extractTokens(reveal, ',');
        for (auto sample: samples) {
            auto qty_clr = extractTokens(sample, ' ');
            cubes_revealed.update(qty_clr.back(), stoi(qty_clr.front()));
        }
    }
    return Bag{id, tokens.size(), cubes_revealed};
}

ostream& operator<<(ostream& os, const Bag& bag) {
    os << "\tAfter " << bag.m_num_reveals << " reveals, the bag in game " << bag.m_game_id << " contains minimum " << bag.m_cubes_revealed << ".";
    return os;
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

    ifstream myfile("input.txt");
    if (!myfile.is_open())
    {
        cout << "Unable to open file";
        return -1;
    }
    
    Bag elf_bag{0, 1, Cubes{12, 13, 14}};

    size_t sum_of_ids = 0;
    size_t sum_of_power = 0;
    while (getline(myfile, line))
    {
        cout << line << endl;
        auto bag = Bag::create(line);
        cout << bag << endl;
        cout << bag.getCubesRevealed().getPower() << endl;
        if (bag.getCubesRevealed() <= elf_bag.getCubesRevealed())
            sum_of_ids += bag.getGameID();
            sum_of_power += bag.getCubesRevealed().getPower();
    }
    myfile.close();
    
    cout << "sum of possible ids: " << sum_of_ids << endl;
    cout << "sum of power: " << sum_of_power << endl;

    return 0;
}