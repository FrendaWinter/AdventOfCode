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
    // Part 1
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
    for (auto line : input)
    {
        std::smatch m;
        std::regex e("mul\\(\\d{1,3},\\d{1,3}\\)");

        while (std::regex_search (line,m,e)) {
            for (auto x:m) {
                std::vector<int> numbers;
                std::string temp;

                // Extract numbers from the string
                for (char c : (std::string)x) {
                    if (std::isdigit(c)) {
                        temp += c; // Build the number
                    } else if (!temp.empty()) {
                        numbers.push_back(std::stoi(temp)); // Add number to the list
                        temp.clear(); // Reset temporary string
                    }
                }
                if (!temp.empty()) { // Add the last number if it exists
                    numbers.push_back(std::stoi(temp));
                }

                mul += numbers[0] * numbers[1];
            }

            line = m.suffix().str();
        }
    }
    cout << "Result: " << mul << endl;
}