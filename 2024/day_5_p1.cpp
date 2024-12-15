#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>
#include <unordered_set>

using namespace std;

std::vector<int> splitStringToIntVector(const std::string& input, char delimiter) {
    std::vector<int> result;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        result.push_back(std::stoi(token)); // Convert each substring to an integer
    }

	return result;
}

bool is_on_the_left(const std::vector<int> &vec, const int &i) {
	for (int j = 0; j < i; j++) {
		if ( std::find(vec.begin(), vec.end(), vec[i]) == vec.end() ) {
			return false;
		}
	}
	return true;
}
int main(int argc, char *argv[])
{
    // Part 1
    vector<string> input;
    string filename = "data/input_day_05.txt";
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

	std::pair<std::unordered_set<int>, std::unordered_set<int>> orders[100];
	std::vector<std::vector<int>> pages;
	for (auto line : input)
	{
		int delimiterPos = line.find("|");

		if (delimiterPos != std::string::npos) 
		{
			string firstPart = line.substr(0, delimiterPos);
			string secondPart = line.substr(delimiterPos + 1);

			int firstNum = std::stoi(firstPart);
			int secondNum = std::stoi(secondPart);

			orders[firstNum].second.insert(secondNum);
			orders[secondNum].first.insert(firstNum);
			
			continue;
		}

		delimiterPos = line.find(",");

		if (delimiterPos != std::string::npos)
		{
			std::vector<int> tmp;	

			tmp = splitStringToIntVector(line, ',');
			pages.push_back(tmp);
		}
	}
	
	
	for (auto page : pages) {
		int tmp[100] = {0};

		for (auto pageNum : page) {
			tmp[pageNum] = 2;
		}

		for (int i = 0; i < page.size(); i++)
		{
			if (orders[page[i]].first.empty() && orders[page[i]].second.empty())
			{
				tmp[page[i]] = 1;
				result += page[i];
			}

//			if (!is_on_the_left(page, i)) break;

		}
	}
    cout << "Result: " << result << endl;
}
