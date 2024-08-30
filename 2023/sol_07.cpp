#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// Function to get the rank of a character
int getRank(char c) {
  // Define the rank map
  std::unordered_map<char, int> rankMap = {
      {'A', 13}, {'K', 12}, {'Q', 11}, {'J', 10}, {'T', 9}, {'9', 8}, {'8', 7},
      {'7', 6},  {'6', 5},  {'5', 4},  {'4', 3},  {'3', 2}, {'2', 1}};
  return rankMap[c];
}

int countInString(const char &c, const string &a) {
  return std::count(a.begin(), a.end(), c);
}

bool compareHand(std::pair<string, string> a, std::pair<string, string> b) {
  /*cout << "a: " << a.first << endl;*/
  /*cout << "b: " << b.first << endl;*/
  for (int i = 0; i < 5; i++) {
    if (getRank(a.first[i]) < getRank(b.first[i]))
      return true;
  }
  return false;
}

int main(int argc, char *argv[]) {
  // Part 1
  vector<string> input;
  string filename = "data/test_data_07.txt";
  ifstream input_file(filename);

  if (input_file.is_open()) {
    string line;
    while (std::getline(input_file, line)) {
      input.push_back(line);
    }
    input_file.close();
  } else {
    cerr << "Error when open file" << endl;
  }

  long result = 0;
  vector<std::pair<string, string>> fourOfKind;
  vector<std::pair<string, string>> fullHouse;

  for (auto line : input) {
    size_t pos = line.find(' ');

    string first_part = line.substr(0, pos);
    string second_part = line.substr(pos + 1);

    std::set<char> charSet;

    for (const char c : first_part) {
      charSet.insert(c);
    }

    if (charSet.size() == 1) {
      // Only one hand with five of kind, so adding it directly to result
      result += std::stoi(second_part) * 1000;
    }

    if (charSet.size() == 2) {
      if (countInString(first_part[0], first_part) == 1 ||
          countInString(first_part[0], first_part) == 4) {
        fourOfKind.push_back(std::make_pair(first_part, second_part));
      }

      if (countInString(first_part[0], first_part) == 2 ||
          countInString(first_part[0], first_part) == 3) {
        fullHouse.push_back(std::make_pair(first_part, second_part));
      }
    }
  }

  std::sort(fourOfKind.begin(), fourOfKind.end(), compareHand);
  for (int i = 0; i < fourOfKind.size(); i++) {
    cout << fourOfKind[i].first << endl;
  }
  cout << "Result:" << result << endl;
}
