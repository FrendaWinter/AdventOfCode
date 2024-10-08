#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// This function returns the rank of a given character based on a predefined rank map.
int getRank(char c) {
    // Define the rank map
    std::unordered_map<char, int> rankMap = {
            {'A', 13}, {'K', 12}, {'Q', 11}, {'T', 10}, {'9', 9}, {'8', 8},
            {'7', 7},  {'6', 6},  {'5', 5},  {'4', 4},  {'3', 3}, {'2', 2}, {'J', 1}};
    return rankMap[c];
}

// This function returns the number of times a given character appears in a string.
int countInString(const char &c, const string &a) {
    return std::count(a.begin(), a.end(), c);
}

int main(int argc, char *argv[]) {
    // Main function to process the input file and categorize the hands
    // Reads the input file, categorizes the hands into different poker hand types,
    // sorts them, calculates the result based on the rank, and prints the result.

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
    vector<std::pair<string, string>> fiveOfKind;
    vector<std::pair<string, string>> fourOfKind;
    vector<std::pair<string, string>> fullHouse;
    vector<std::pair<string, string>> threeOfKind;
    vector<std::pair<string, string>> twoPair;
    vector<std::pair<string, string>> onePair;
    vector<std::pair<string, string>> highCard;

    for (auto line : input) {
        size_t pos = line.find(' ');

        string first_part = line.substr(0, pos);
        string second_part = line.substr(pos + 1);

        std::set<char> charSet;

        for (const char c : first_part) {
            charSet.insert(c);
        }

        if (charSet.size() == 1) {
            fiveOfKind.push_back(std::make_pair(first_part, second_part));
        }

        if (charSet.size() == 2) {
            if (first_part.find('J') != string::npos) {
                fiveOfKind.push_back(std::make_pair(first_part, second_part));
            } else {
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

        if (charSet.size() == 3) {
            int max = 0;
            for (const char c : first_part) {
                if ( countInString(c, first_part) > max) {
                    max = countInString(c, first_part);
                }
            }

            if (max == 3) {
                if (first_part.find('J') != string::npos) {
                    fourOfKind.push_back(std::make_pair(first_part, second_part));
                } else {
                    threeOfKind.push_back(std::make_pair(first_part, second_part));
                }
            }
            
            if (max == 2) {
                if (first_part.find('J') != string::npos && countInString('J', first_part) == 1) {
                    fullHouse.push_back(std::make_pair(first_part, second_part));
                } else if (first_part.find('J') != string::npos && countInString('J', first_part) == 2) {
                    fourOfKind.push_back(std::make_pair(first_part, second_part));
                } else {
                    twoPair.push_back(std::make_pair(first_part, second_part));
                }
            }
        }

        if (charSet.size() == 4) {
            if (first_part.find('J') != string::npos) {
                threeOfKind.push_back(std::make_pair(first_part, second_part));
            } else {
                onePair.push_back(std::make_pair(first_part, second_part));
            }
        }

        if (charSet.size() == 5) {
            if (first_part.find('J') != string::npos) {
                onePair.push_back(std::make_pair(first_part, second_part));
            } else {
                highCard.push_back(std::make_pair(first_part, second_part));
            }
        }
    }

    std::sort(fiveOfKind.begin(), fiveOfKind.end(), [](const auto &a, const auto &b) {
        for (int i = 0; i < 5; i++) {
            if (a.first[i] != b.first[i])
                return getRank(a.first[i]) < getRank(b.first[i]);
        }
        return false;
    });

    int rank = 1001 - fiveOfKind.size();

    for (int i = 0; i < fiveOfKind.size(); i++) {
        result += std::stoi(fiveOfKind[i].second) * rank;
        rank++;
    }

    std::sort(fourOfKind.begin(), fourOfKind.end(), [](const auto &a, const auto &b) {
        for (int i = 0; i < 5; i++) {
            if (a.first[i] != b.first[i])
                return getRank(a.first[i]) < getRank(b.first[i]);
        }
        return false;
    });

    rank = 1001 - fiveOfKind.size() - fourOfKind.size();

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

    rank = 1001 - fiveOfKind.size() - fourOfKind.size() - fullHouse.size();

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

    rank = 1001 - fiveOfKind.size() - fourOfKind.size() - fullHouse.size() - threeOfKind.size();

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

    rank = 1001 - fiveOfKind.size() - fourOfKind.size() - fullHouse.size() - threeOfKind.size() - twoPair.size();

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

    rank = 1001 - fiveOfKind.size() - fourOfKind.size() - fullHouse.size() - threeOfKind.size() - twoPair.size() - onePair.size();

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

    rank = 1001 - fiveOfKind.size() - fourOfKind.size() - fullHouse.size() - threeOfKind.size() - twoPair.size() - onePair.size() - highCard.size(); 

    for (int i = 0; i < highCard.size(); i++) {
        result += std::stoi(highCard[i].second) * rank;
        rank++;
    }

    cout << "Part 2: " << result << endl;
}