#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>
#include <unordered_set>

using namespace std;

vector<string> mapArea;

const std::vector<std::pair<int, int>> directions = {
	{0, 1},	 // Right
	{1, 0},	 // Down
	{0, -1}, // Left
	{-1, 0}, // Up
};

bool isOutOfMap(std::pair<int, int> position, std::pair<int, int> direction, const std::pair<int, int> &border)
{
	position.first += direction.first;
	position.second += direction.second;
	if (position.first >= border.first || position.first < 0) return true;
	if (position.second >= border.second || position.second < 0)
		return true;
	return false;
}

std::pair<int, int> turnRight(std::pair<int, int> direction)
{
	// Right, turn to Down
	if (direction == std::pair<int, int>{0, 1}) {
		return std::pair<int, int> { 1, 0 };
	}

	// Left, turn to Up
	if (direction == std::pair<int, int>{0, -1})
	{
		return std::pair<int, int>{-1, 0};
	}

	// Up, turn to Right
	if (direction == std::pair<int, int>{-1, 0})
	{
		return std::pair<int, int>{0, 1};
	}

	// Down, turn to Left
	if (direction == std::pair<int, int>{1, 0})
	{
		return std::pair<int, int>{0, -1};
	}

	return std::pair<int, int>();
}

bool isCounterObstructions(std::pair<int, int> position, std::pair<int, int> direction)
{
	// cout << position.first << " " << position.second << endl;
	if (mapArea[position.first + direction.first][position.second + direction.second] == '#')
	{
		return true;
	}
	return false;
}

int main(int argc, char *argv[])
{
    // Part 1
    
    string filename = "data/input_day_06.txt";
    ifstream input_file(filename);

    if (input_file.is_open())

    {
        string line;
        while (std::getline(input_file, line))
        {
			mapArea.push_back(line);
		}
        input_file.close();
    }
    else
    {
        cerr << "Error when open file" << endl;
    }

    int result = 0;

	std::pair<int, int> border = std::make_pair(mapArea.size(), mapArea[0].length());

	std::pair<int, int> firstPosition;
	for (int i = 0; i < border.first; i++)
	{
		for (int j = 0; j < border.second; j++)
		{
			if (mapArea[i][j] == '^')
			{
				firstPosition = std::make_pair(i, j);
				break;
			}
		}
	}

	for (int i = 0; i < border.first; i++)
	{
		for (int j = 0; j < border.second; j++)
		{
			std::pair<int, int> position = firstPosition;
			std::pair<int, int> direction = std::make_pair(-1, 0);

			if (mapArea[i][j] == '.')
				mapArea[i][j] = '#';
			else continue;

			int step = 0;
			while (!isOutOfMap(position, direction, border))
			{
				if (isCounterObstructions(position, direction))
				{
					direction = turnRight(direction);
				}
				position.first += direction.first;
				position.second += direction.second;
				step++;
				if (step > 10000) {
					result++;
					break;
				}
			}
			mapArea[i][j] = '.';
		}
	}

	cout << "Result: " << result << endl;
}
