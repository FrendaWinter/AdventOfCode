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
  // Counts the occurrences of character 'c' in string 'a'
  return std::count(a.begin(), a.end(), c);
}
int main(int argc, char *argv[]) {
  // Part 1 
  vector<string> input;
  string filename = "data/test_data_07.txt";
  ifstream input_file(filename);

  if (input_file.is_open()) {
    // Read each line from the file and store it in the 'input' vector
    string line;
    while (std::getline(input_file, line)) {
      input.push_back(line);
    }
    input_file.close();
  } else {
    // Print error message if the file cannot be opened
    cerr << "Error when open file" << endl;
  }

  // Initialize result and various hand categories for poker hands
  long result = 0;
  vector<std::pair<string, string>> fourOfKind;
  vector<std::pair<string, string>> fullHouse;
  vector<std::pair<string, string>> threeOfKind;
  vector<std::pair<string, string>> twoPair;
  vector<std::pair<string, string>> onePair;
  vector<std::pair<string, string>> highCard;

  // Process each line from the input
  for (auto line : input) {
    // Find the position of the first space character
    size_t pos = line.find(' ');

    // Split the line into two parts based on the space character
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

    if (charSet.size() == 3) {
      int max = 0;
      for (const char c : first_part) {
        if ( countInString(c, first_part) > max) {
          max = countInString(c, first_part);
        }
      }

      if (max == 3) {
        threeOfKind.push_back(std::make_pair(first_part, second_part));
      }
      
      if (max == 2) {
        twoPair.push_back(std::make_pair(first_part, second_part));
      }
    }

    if (charSet.size() == 4) {
      onePair.push_back(std::make_pair(first_part, second_part));
    }

    if (charSet.size() == 5) {
      highCard.push_back(std::make_pair(first_part, second_part));
    }
  }

  std::sort(fourOfKind.begin(), fourOfKind.end(), [](const auto &a, const auto &b) {
    for (int i = 0; i < 5; i++) {
      if (a.first[i] != b.first[i])
        return getRank(a.first[i]) < getRank(b.first[i]);
    }
    return false;
  });

  int rank = 1001 - 1 - fourOfKind.size();

  for (int i = 0; i < fourOfKind.size(); i++) {
    result += std::stoi(fourOfKind[i].second) * rank;
    rank++;
  }

  std::sort(fullHouse.begin(), fullHouse.end(), [](const auto &a, const auto &b) {
    for (int i = 0; i < 5; i++) {
      if (a.first[i] != b.first[i])
        return getRank(a.first[i]) < getRank(b.first[i]);
    }
    return false;
  });

  rank = 1001 - 1 - fourOfKind.size() - fullHouse.size();

  for (int i = 0; i < fullHouse.size(); i++) {
    result += std::stoi(fullHouse[i].second) * rank;
    rank++;
  }

  std::sort(threeOfKind.begin(), threeOfKind.end(), [](const auto &a, const auto &b) {
    for (int i = 0; i < 5; i++) {
      if (a.first[i] != b.first[i])
        return getRank(a.first[i]) < getRank(b.first[i]);
    }
    return false;
  });

  rank = 1001 - 1 - fourOfKind.size() - fullHouse.size() - threeOfKind.size();

  for (int i = 0; i < threeOfKind.size(); i++) {
    result += std::stoi(threeOfKind[i].second) * rank;
    rank++;
  }

  std::sort(twoPair.begin(), twoPair.end(), [](const auto &a, const auto &b) {
    for (int i = 0; i < 5; i++) {
      if (a.first[i] != b.first[i])
        return getRank(a.first[i]) < getRank(b.first[i]);
    }
    return false;
  });

  rank = 1001 - 1 - fourOfKind.size() - fullHouse.size() - threeOfKind.size() - twoPair.size();

  for (int i = 0; i < twoPair.size(); i++) {
    result += std::stoi(twoPair[i].second) * rank;
    rank++;
  }

  std::sort(onePair.begin(), onePair.end(), [](const auto &a, const auto &b) {
    for (int i = 0; i < 5; i++) {
      if (a.first[i] != b.first[i])
        return getRank(a.first[i]) < getRank(b.first[i]);
    }
    return false;
  });

  rank = 1001 - 1 - fourOfKind.size() - fullHouse.size() - threeOfKind.size() - twoPair.size() - onePair.size();

  for (int i = 0; i < onePair.size(); i++) {
    result += std::stoi(onePair[i].second) * rank;
    rank++;
  }

  std::sort(highCard.begin(), highCard.end(), [](const auto &a, const auto &b) {
    for (int i = 0; i < 5; i++) {
      if (a.first[i] != b.first[i])
        return getRank(a.first[i]) < getRank(b.first[i]);
    }
    return false;
  });

  rank = 1001 - 1 - fourOfKind.size() - fullHouse.size() - threeOfKind.size() - twoPair.size() - onePair.size() - highCard.size(); 

  for (int i = 0; i < highCard.size(); i++) {
    result += std::stoi(highCard[i].second) * rank;
    rank++;
  }

  cout << "Part 1: " << result << endl;
}   