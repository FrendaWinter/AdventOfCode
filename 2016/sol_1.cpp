#include <iostream>
#include <string>
#include <vector>

#include "utils.cpp"

using namespace std;

int main() {
  vector<string> lines = readFileLines("./data/input_1.txt");

  if (lines.empty()) {
    cerr << "File is emmpty" << endl;
    return 1;
  }

  vector<string> directions = split(lines[0], ",");

  for(auto i : directions)
    cout << i << endl;
  return 0;
}
