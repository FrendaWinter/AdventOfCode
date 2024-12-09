#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

int main(int argc, char *argv[])
{
    // Part 1
    vector<string> input;
    string filename = "data/input_day_02.txt";
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

    int safe = 0;
    for (auto line : input)
    {
        std::vector<int> tmp;

        std::istringstream iss(line); // Create a string stream for the line
        int num;
        while (iss >> num)
        {                       // Extract integers from the line
            tmp.push_back(num); // Add them to the vector
        }

        bool is_incr = true;
        bool is_safe = true;
        if (tmp[0] > tmp[1]) {
            is_incr = false;
        }

        if (is_incr) {
            for (int i = 0; i < tmp.size() - 1; i ++) {
                if (tmp[i] > tmp[i + 1] || tmp[i + 1] - tmp[i] > 3 || tmp[i + 1] == tmp[i])
                {
                    is_safe = false;
                }
            }
        }

        if (!is_incr)
        {
            for (int i = 0; i < tmp.size() - 1; i++)
            {
                if (tmp[i] < tmp[i + 1] || tmp[i] - tmp[i + 1] > 3 || tmp[i + 1] == tmp[i])
                {
                    is_safe = false;
                }
            }
        }

        safe += is_safe;
    }

    cout << "Result: " << safe << endl;
}