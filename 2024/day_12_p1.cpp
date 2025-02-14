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
vector<string> &garden;
int result = 0;

// Find area of char
vector<std::pair<int, int>> findArea(const std::pair<int, int> &p)
{
    char cmp = garden[p.first][p.second];
    vector<std::pair<int, int>> pArea;
}

// Mark area with dot
void markArea(const vector<std::pair<int, int>> &area)
{
    for (size_t i = 0; i < area.size(); i++)
    {
        garden[area[i].first][area[i].second] = '.';
    }
};

// Calculate perimeter
int calPerimeters(vector<string> garden, vector<std::pair<int, int>> area);

int main(int argc, char *argv[])
{
    vector<string> input;
    string filename = "data/input_test.txt";
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

    vector<string> garden = input;
    for (int i = 0; i < garden.size(); i++)
    {
        for (int j = 0; j < garden[i].length(); j++)
        {
            if (garden[i][j] != '.')
            {
                findArea(std::make_pair(i, j));
            }
        }
    }

    cout << "Result: " << result << endl;
}
