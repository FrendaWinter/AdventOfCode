#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

std::vector<std::string> split(std::string s, std::string delimiter)
{
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
	{
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

vector<string> readFileLines(const string &filename)
{
	ifstream inputFile(filename);
	vector<string> lines;

	// Check if file is open
	if (!inputFile.is_open())
	{
		cerr << "Error opening file: " << filename << endl;
		return lines; // Return empty vector on error
	}

	string line;
	while (getline(inputFile, line))
	{
		lines.push_back(line);
	}

	inputFile.close();
	return lines;
}

const std::vector<std::tuple<int, int, int, int, int, int>> direction_map = {
	// Format: direction, right of direction, left of direction.
	{0, 1, 1, 0, -1, 0},  // Up
	{1, 0, 0, -1, 0, 1},  // Right
	{0, -1, -1, 0, 1, 0}, // Down
	{-1, 0, 0, 1, 0, -1}  // Left
};

int main()
{
	vector<string> lines = readFileLines("./data/input.txt");

	if (lines.empty())
	{
		cerr << "File is emmpty" << endl;
		return 1;
	}

	vector<string> turns = split(lines[0], ", ");

	int x, y = 0;

	std::pair<int, int> direction = {0, 1};

	vector<std::pair<int, int>> locationHistory;
	locationHistory.push_back(direction);

	for (int i = 0; i < turns.size(); i++)
	{
		string action = turns[i].substr(0, 1);

		int stepLength = std::stoi(turns[i].substr(1, turns[i].length() - 1));

		for (auto direc : direction_map)
		{
			// Next if not match direction
			if (std::get<0>(direc) != direction.first || std::get<1>(direc) != direction.second)
			{
				continue;
			}
			if (action == "R")
			{
				// Take steps
				for (int step = 0; step < stepLength; step++)
				{
					x += std::get<2>(direc);
					y += std::get<3>(direc);

					if (std::find(locationHistory.begin(), locationHistory.end(), std::make_pair(x, y)) != locationHistory.end())
						goto end;
					else
						locationHistory.push_back(std::make_pair(x, y));
				}
				// Change current direction
				direction.first = std::get<2>(direc);
				direction.second = std::get<3>(direc);

				break;
			}

			if (action == "L")
			{
				// Take steps
				for (int step = 0; step < stepLength; step++)
				{
					x += std::get<4>(direc);
					y += std::get<5>(direc);

					if (std::find(locationHistory.begin(), locationHistory.end(), std::make_pair(x, y)) != locationHistory.end())
						goto end;
					else
						locationHistory.push_back(std::make_pair(x, y));
				}
				// Change current direction
				direction.first = std::get<4>(direc);
				direction.second = std::get<5>(direc);
				break;
			}
		}
	}

end:
	cout << x << " " << y << endl;
}
