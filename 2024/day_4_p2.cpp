#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>

using namespace std;

const std::vector<std::pair<int, int>> positions = {
    {-1, -1}, // Up-Left
    {-1, 1},  // Up-Right
    {1, 1},   // Down-Right
    {1, -1}   // Down-Left
};

const std::vector<string> orders = {
    // Order of word match the positions Up-Left -> Up-Right -> Down-Right -> Down-Left
    "SSMM",
    "MSSM",
    "MMSS",
    "SMMS"};

int search(const std::vector<std::string> &matrix, int x, int y)
{
    int count = 0;
    // Explore all 4 word orders
    for (const auto &order : orders)
    {
        bool is_xmas = true;
        for (int i = 0; i < positions.size(); i++)
        {
            // Reset positions
            int newX = x;
            int newY = y;
            newX += positions[i].first;
            newY += positions[i].second;

            if (matrix[newX][newY] != order[i])
            {
                is_xmas = false;
                break;
            }
        }
        if (is_xmas) count++;
    }
    return count;
}

int main(int argc, char *argv[])
{
    // Part 2
    vector<string> input;
    string filename = "data/input_day_04.txt";
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
    // Step 1: Add three row to the beginning and end of the vector
    input.insert(input.begin(), 3, std::string(146, '.')); // Add 3 at the beginning
    input.insert(input.end(), 3, std::string(146, '.'));   // Add 3 at the end

    // Step 2: For each real input string (skip the first and last 3 elements), add "..." at the beginning and end of the string
    for (size_t i = 3; i < input.size() - 3; ++i)
    {
        std::string border = "...";
        input[i] = border + input[i] + border;
    }

    for (size_t i = 3; i < input.size() - 3; ++i)
    {
        for (size_t j = 3; j < input[0].length() - 3; ++j) {
            if (input[i][j] == 'A')
                result += search(input, i, j);
        }
    }
    cout << "Result: " << result << endl;
}