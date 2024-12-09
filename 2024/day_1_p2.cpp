#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

int main(int argc, char *argv[])
{
    // Part 2
    vector<string> input;
    string filename = "data/input_day_01.txt";
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

    std::vector<int> left;
    std::vector<int> right;

    int a[100000] = {0};

    for (auto line : input)
    {
        int first_part = std::stoi(line.substr(0, 5));
        int second_part = std::stoi(line.substr(8));

        auto it_left = std::lower_bound(left.begin(), left.end(), first_part);
        auto it_right = std::lower_bound(right.begin(), right.end(), second_part);

        left.insert(it_left, first_part);
        right.insert(it_right, second_part);

        a[second_part] += 1;
    }

    long total = 0;
    for (int i = 0; i < left.size(); i++) {
        total += (left[i] * a[left[i]]);
    }
    cout << "Total: " << total << endl;
}