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

vector<string> garden;
void markArea(const std::pair<int, int> &p);

void harvestArea(const char &cmp, const std::pair<int, int> &p, vector<std::pair<int, int>> &area)
{
    markArea(p);

    // Recursion to find all match
    for (int i = 0; i < directions.size(); i++)
    {
        int x = p.first + directions[i].first;
        int y = p.second + directions[i].second;

        if (x < 0 || x >= garden.size() || y < 0 || y >= garden[0].size())
        {
            continue;
        }

        if (garden[x][y] == cmp)
        {
            area.push_back(std::make_pair(x, y));
            harvestArea(cmp, std::make_pair(x, y), area);
        }
    }
}

// Find region that have the same char
vector<std::pair<int, int>> findArea(const std::pair<int, int> &p)
{
    char cmp = garden[p.first][p.second];
    vector<std::pair<int, int>> pArea;
    pArea.push_back(p);
    // Mark all land that have the same char with .
    harvestArea(cmp, p, pArea);

    return pArea;
}

// Mark area with dot
void markArea(const std::pair<int, int> &p)
{
    garden[p.first][p.second] = '.';
};

// Calculate perimeter
int calPerimeter(const vector<std::pair<int, int>> &area)
{
    int perimeter = 0;

    for (int i = 0; i < area.size(); i++)
    {
        int fourAngle = 4;
        for (int j = 0; j < directions.size(); j++)
        {

            int x = area[i].first + directions[j].first;
            int y = area[i].second + directions[j].second;

            if (x < 0 || x >= garden.size() || y < 0 || y >= garden[0].size())
            {
                continue;
            }

            if (std::find(area.begin(), area.end(), std::make_pair(x, y)) != area.end())
            {
                fourAngle--;
            }
        }
        perimeter += fourAngle;
    }
    return perimeter;
}

// Cal price of the region.
int calPrice(const vector<std::pair<int, int>> &area)
{
    int areaSize = area.size();

    int perimeter = calPerimeter(area);

    return areaSize * perimeter;
}

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
            garden.push_back(line);
        }
        input_file.close();
    }
    else
    {
        cerr << "Error when open file" << endl;
    }

    int result = 0;
    for (int i = 0; i < garden.size(); i++)
    {
        for (int j = 0; j < garden[i].length(); j++)
        {
            if (garden[i][j] != '.')
            {
                // Find region
                vector<std::pair<int, int>> pArea = findArea(std::make_pair(i, j));
                // Cal price of that region and add to result
                result += calPrice(pArea);
            }
        }
    }

    cout << "Result: " << result << endl;
}
