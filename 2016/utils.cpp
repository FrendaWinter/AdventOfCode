#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// for string delimiter
std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

vector<string> readFileLines(const string& filename) {
  ifstream inputFile(filename);
  vector<string> lines;

  // Check if file is open
  if (!inputFile.is_open()) {
    cerr << "Error opening file: " << filename << endl;
    return lines; // Return empty vector on error
  }

  string line;
  while (getline(inputFile, line)) {
    lines.push_back(line);
  }

  inputFile.close();
  return lines;
}
