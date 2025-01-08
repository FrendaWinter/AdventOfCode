#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include <map>

using namespace std;

const std::vector<std::pair<int, int>> directions = {
    {0, 1},  // Right
    {1, 0},  // Down
    {0, -1}, // Left
    {-1, 0}, // Up
};

// Find area of char
vector<std::pair<int, int>> findArea(vector<string> &garden, const int &x, const int &y) {

}

// Mark area with dot
void markArea(vector<string> &garden, vector<std::pair<int, int>> area) {

}

// Calculate perimeter
int calPerimeters(vector<string> garden, vector<std::pair<int, int>> area) {

}

int main(int argc, char *argv[])
{
    vector<string> input;
    string filename = "data/input_day_12.txt";
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

    int result = 0;
    std::map<char, int> areas;
    std::map<char, int> perimeters;
    // Init value
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].length(); j++)
        {
            if (areas.count(input[i][j]) > 0)
            {
                areas[input[i][j]]++;
            }
            else
            {
                areas[input[i][j]] = 1;
                perimeters[input[i][j]] = 0;
            }
        }
    }

    vector<string> garden = input;

    cout << "Result: " << result << endl;
}
