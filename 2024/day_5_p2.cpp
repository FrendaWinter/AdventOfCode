#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>
#include <unordered_set>

using namespace std;

std::pair<std::unordered_set<int>, std::unordered_set<int>> orders[100];
std::vector<std::vector<int>> pages;

std::vector<int> splitStringToIntVector(const std::string& input, char delimiter) {
    std::vector<int> result;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        result.push_back(std::stoi(token)); // Convert each substring to an integer
    }

	return result;
}

bool isCorrectOrder(const int &i)
{
	std::vector<int> page = pages[i];

	for (int x = 0; x < page.size(); x++) {
		for (int j = x + 1; j < page.size(); j++) {
			if (find(orders[page[x]].first.begin(), orders[page[x]].first.end(), page[j]) != orders[page[x]].first.end())
			{
				return false;
			}
		}

		for (int k = 0; k < x; k++)
		{
			if (find(orders[page[x]].second.begin(), orders[page[x]].second.end(), page[k]) != orders[page[x]].second.end())
			{
				return false;
			}
		}
	}
	return true;
}

void fixPage(const int &i) {
	std::vector<int> page = pages[i];
	
	for (int x = 0; x < page.size(); x++)
	{
		for (int j = x + 1; j < page.size(); j++)
		{
			if (find(orders[page[x]].first.begin(), orders[page[x]].first.end(), page[j]) != orders[page[x]].first.end())
			{
				std::swap(page[x], page[j]);
				x = 0;
			}
		}

		for (int k = 0; k < x; k++)
		{
			if (find(orders[page[x]].second.begin(), orders[page[x]].second.end(), page[k]) != orders[page[x]].second.end())
			{
				std::swap(page[x], page[k]);
				x = 0;
			}
		}
	}

	pages[i] = page;
}

int main(int argc, char *argv[])
{
    // Part 2
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

	for (int i = 0; i < 100; ++i)
	{
		if (!orders[i].first.empty() || !orders[i].second.empty())
		{ // Print only non-empty pairs
			std::cout << "orders[" << i << "]:\n";

			std::cout << "  First set: ";
			for (int num : orders[i].first)
			{
				std::cout << num << " ";
			}
			std::cout << "\n";

			std::cout << "  Second set: ";
			for (int num : orders[i].second)
			{
				std::cout << num << " ";
			}
			std::cout << "\n";
		}
	}

	for (int i = 0; i < pages.size(); i++) {
		if (isCorrectOrder(i)) {
			continue;
		} else {
			// If not correct order, fix the page and count result.
			fixPage(i);
			result += pages[i][pages[i].size() / 2];
		}
	}

    cout << "Result: " << result << endl;
}
