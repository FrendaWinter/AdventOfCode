#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>
#include <unordered_set>

using namespace std;

int main(int argc, char *argv[])
{
    // Part 1
	vector<string> input;
	string filename = "data/input_day_07.txt";
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

	// Idea
	// Count number of operation n - 1
	// Binary number from 0 to n - 1, each number = operations order
	// 00 = {+ +}, 010 = {+ * +}
	// Count all possible result, add to result

	cout << "Result: " << result << endl;
}
