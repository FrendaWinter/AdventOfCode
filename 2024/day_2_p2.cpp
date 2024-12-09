#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

bool is_vector_safe(std::vector<int> &tmp) {
    bool is_incr = true;
    bool is_safe = true;
    if (tmp[0] > tmp[1])
    {
        is_incr = false;
    }

    if (is_incr)
    {
        for (int i = 1; i < tmp.size(); i++)
        {
            if (tmp[i] < tmp[i - 1] || tmp[i] - tmp[i - 1] > 3 || tmp[i] == tmp[i - 1])
            {
                is_safe = false;
            }
        }
    }

    if (!is_incr)
    {
        for (int i = 1; i < tmp.size(); i++)
        {
            if (tmp[i] > tmp[i - 1] || tmp[i - 1] - tmp[i] > 3 || tmp[i] == tmp[i - 1])
            {
                is_safe = false;
            }
        }
    }

    return is_safe;
}

void print_vector(vector<int> myVector)
{
    for (int num : myVector)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    // Part 2
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

        bool is_safe = true;
        while (iss >> num)
        {
            tmp.push_back(num);
        }

        if (is_vector_safe(tmp)) {
            safe += is_safe;
            continue;
        }

        for (int i = 2; i < tmp.size(); i++)
        {
            std::vector<int> subVector(tmp.begin(), tmp.begin() + i + 1);
            if (!is_vector_safe(subVector))
            {
                std::vector<int> tmp_1 = tmp;
                tmp_1.erase(tmp_1.begin() + i);
                if (is_vector_safe(tmp_1))
                {
                    safe += is_safe;
                    break;
                }

                std::vector<int> tmp_2 = tmp;
                tmp_2.erase(tmp_2.begin() + (i - 1));
                if (is_vector_safe(tmp_2))
                {
                    safe += is_safe;
                    break;
                }

                std::vector<int> tmp_3 = tmp;
                tmp_3.erase(tmp_3.begin() + (i - 2));
                if (is_vector_safe(tmp_3))
                {
                    safe += is_safe;
                    break;
                }
            }
        }
    }

    cout << "Result: " << safe << endl;
}