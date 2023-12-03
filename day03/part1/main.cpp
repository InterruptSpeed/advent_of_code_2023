// adventofcode.com/2023/day/3
//$clang++ main.cpp --std=c++17 -o main
//$./main

// output should be ? for input.txt

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string line;

    ifstream myfile("dev_input.txt");
    if (!myfile.is_open())
    {
        cout << "Unable to open file";
        return -1;
    }
    
    while (getline(myfile, line))
    {
        cout << line << endl;
    }
    myfile.close();

    return 0;
}