#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>

using namespace std;

const std::vector<std::pair<int, int>> directions = {
    {0, 1},  // Right
    {1, 0},  // Down
    {0, -1}, // Left
    {-1, 0}, // Up
    {1, 1},  // Down-Right
    {1, -1}, // Down-Left
    {-1, 1}, // Up-Right
    {-1, -1} // Up-Left
};

int search(const std::vector<std::string> &matrix, int x, int y, const std::string &word)
{
    if (matrix[x][y] != word[0])
        return 0;
    
    int count = 0;
    // Explore all 8 directions
    for (const auto &dir : directions)
    {
        bool is_xmas = true;
        // Reset positions for each direction
        int newX = x;
        int newY = y;
        for (int i = 1; i < word.length(); i++)
        {
            newX += dir.first;
            newY += dir.second;

            if (matrix[newX][newY] != word[i])
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
    // Part 1
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

    std::string word = "XMAS";
    for (size_t i = 3; i < input.size() - 3; ++i)
    {
        for (size_t j = 3; j < input[0].length() - 3; ++j) {
            result += search(input, i, j, word);
        }
    }
    cout << "Result: " << result << endl;
}