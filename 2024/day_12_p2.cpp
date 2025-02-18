#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include <map>

using namespace std;

vector<string> garden;
const std::vector<std::pair<int, int>> nearbyLand = {
    {-1, -1}, // Northwest
    {-1, 0},  // North
    {-1, 1},  // Northeast
    {0, 1},   // East
    {1, 1},   // Southeast
    {1, 0},   // South
    {1, -1},  // Southwest
    {0, -1},  // West
};

// Mapping for outer corner
const std::vector<string> outerCorner = {
    "x1xxxxx1",
    "x1x1xxxx",
    "xxx1x1xx",
    "xxxxx1x1",
};

int checkOuterCorner(const int &x, const int &y, const vector<std::pair<int, int>> &area)
{
    int cornerCount = 4;
    for (int i = 0; i < outerCorner.size(); i++)
    {
        for (int j = 0; j < outerCorner[i].length(); j++)
        {
            int newX = x + nearbyLand[j].first;
            int newY = y + nearbyLand[j].second;

            if (outerCorner[i][j] == '1')
            {
                if (std::find(area.begin(), area.end(), std::make_pair(newX, newY)) != area.end())
                {
                    cornerCount--;
                    break;
                }
            }

            if (outerCorner[i][j] == 'x')
            {
                continue;
            }
        }
    }
    return cornerCount;
}

// Mapping for inner corner
const std::vector<string> innerCorner = {
    "10xxxxx0", "x010xxxx", "xxx010xx", "xxxxx010"};

int checkInnerCorner(const int &x, const int &y, const vector<std::pair<int, int>> &area)
{
    int cornerCount = 4;
    for (int i = 0; i < innerCorner.size(); i++)
    {
        for (int j = 0; j < innerCorner[i].length(); j++)
        {
            int newX = x + nearbyLand[j].first;
            int newY = y + nearbyLand[j].second;

            if (innerCorner[i][j] == '1')
            {
                if (std::find(area.begin(), area.end(), std::make_pair(newX, newY)) != area.end())
                {
                    cornerCount--;
                    break;
                }
            }

            if (innerCorner[i][j] == '0')
            {
                if (std::find(area.begin(), area.end(), std::make_pair(newX, newY)) == area.end())
                {
                    cornerCount--;
                    break;
                }
            }

            if (innerCorner[i][j] == 'x')
            {
                continue;
            }
        }
    }
    return cornerCount;
}

const std::vector<std::pair<int, int>> directions = {
    {0, 1},  // Right
    {1, 0},  // Down
    {0, -1}, // Left
    {-1, 0}, // Up
};

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

// Count Corner
int calCorner(const vector<std::pair<int, int>> &area)
{
    int corners = 0;

    for (int i = 0; i < area.size(); i++)
    {
        corners += checkInnerCorner(area[i].first, area[i].second, area) + checkOuterCorner(area[i].first, area[i].second, area);
    }
    return corners;
}

// Cal price of the region.
int calPrice(const vector<std::pair<int, int>> &area)
{
    int areaSize = area.size();

    // Idea: Count corner instead of count side
    // https://www.reddit.com/r/adventofcode/comments/1hex153/2024_day_12_if_you_struggle_with_part_2/
    int corners = calCorner(area);

    return areaSize * corners;
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
