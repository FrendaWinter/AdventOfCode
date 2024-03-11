#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

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
