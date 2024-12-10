#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>

using namespace std;

int main(int argc, char *argv[])
{
    // Part 2
    vector<string> input;
    string filename = "data/input_day_03.txt";
    ifstream input_file(filename);

    if (input_file.is_open())
    {
        string line;
        while (std::getline(input_file, line))
        {
            input.push_back(line);
        }
        input_file.close();
    }
    else
    {
        cerr << "Error when open file" << endl;
    }

    int mul = 0;
    std::string big_input;
    for (auto line : input){
        big_input += line;
    }
    std::regex word_regex("(mul\\(\\d{1,3},\\d{1,3}\\)|don't\\(\\)|do\\(\\))");
    bool enabled = true;

    for (auto it = std::sregex_iterator(big_input.begin(), big_input.end(), word_regex); it != std::sregex_iterator(); ++it)
    {
        std::string match = it->str();

        if (match == "do()")
        {
            enabled = true;
            continue;
        }
        else if (match == "don't()")
        {
            enabled = false;
            continue;
        }
        if (!enabled)
            continue;

        // cout << match << endl;
        std::vector<int> numbers;
        std::string temp;

        for (char c : match)
        {
            if (std::isdigit(c))
            {
                temp += c; // Build the number
            }
            else if (!temp.empty())
            {
                numbers.push_back(std::stoi(temp)); // Add number to the list
                temp.clear();                       // Reset temporary string
            }
        }
        if (!temp.empty())
        {
            numbers.push_back(std::stoi(temp));
        }

        mul += numbers[0] * numbers[1];
    }

    cout << "Result: " << mul << endl;
}