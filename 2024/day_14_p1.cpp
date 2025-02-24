
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include <map>
#include <regex>

using namespace std;

#define MAX_X 11
#define MAX_Y 7

void checkOutOfMap(int &newX, int &newY)
{
    if (newX < 0)
    {
        newX = MAX_X + newX;
    }

    if (newX > MAX_X)
    {
        newX = newX - MAX_X;
    }

    if (newY < 0)
    {
        newY = MAX_Y + newY;
    }

    if (newY > MAX_Y)
    {
        newY = newY - MAX_Y;
    }
}

void step(int &x, int &y, const int &vx, const int &vy)
{
    int newX, newY;
    if (vx > 0)
    {
        newX = x + vx;
        newY = y + vy;
    } else {
        newX = x - vx;
        newY = y - vy;
    }

    checkOutOfMap(newX, newY);
    x = newX;
    y = newY;
}

int calResult(const std::vector<std::pair<int, int>> &positions)
{
    int result = 1;
    
    if (x > 0 && x < MAX_X/2 && y > 0 && y <MAX_Y/2)
    {

    }

    if ()
    return result;
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
            input.push_back(line);
        }
        input_file.close();
    }
    else
    {
        cerr << "Error when open file" << endl;
    }

    int result = 0;
    std::vector<std::pair<int, int>> positions;
    std::vector<std::pair<int, int>> velocity;
    std::regex patternA("p=(-?\\d+),(-?\\d+).+$");
    std::regex patternB(".*?v=(-?\\d+),(-?\\d+)$");
    for (int i = 0; i < input.size(); i++)
    {

        std::smatch matches;

        if (std::regex_search(input[i], matches, patternA))
        {
            if (matches.size() == 3)
            {
                int x = std::stoi(matches[1].str());
                int y = std::stoi(matches[2].str());

                positions.push_back(std::make_pair(x, y));
            }
        }

        if (std::regex_search(input[i], matches, patternB))
        {
            if (matches.size() == 3)
            {
                int x = std::stoi(matches[1].str());
                int y = std::stoi(matches[2].str());

                velocity.push_back(std::make_pair(x, y));
            }
        }
    }

    for (int i = 0; i < MAX_X; i++)
    {
        step(positions[i].first, positions[i].second, velocity[i].first, velocity[i].second);
    }

    for (int i = 0; i < positions.size(); i++)
    {
        cout << positions[i].first << " " << positions[i].second << endl;
        cout << velocity[i].first << " " << velocity[i].second << endl;
    }
}