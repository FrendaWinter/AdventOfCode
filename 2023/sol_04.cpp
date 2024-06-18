#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <sstream>
using namespace std;

int main (int argc, char *argv[]) {
  // Part 2
  vector<string> input;
  string filename = "data/test_data_04.txt";
  ifstream input_file(filename);

  if (input_file.is_open())
  {
    string line;
    while (std::getline(input_file, line)) {
      input.push_back(line);
    }
    input_file.close();
  } else {
    cerr << "Error when open file" << endl;
  }

  int result[188];
  int result_index = 0;
  for (auto line : input) {
    line = line.erase(0, 10);
    size_t pos = line.find('|');

    string first_part = line.substr(0, pos);
    string second_part = line.substr(pos + 1);
    
    int card[10];
    int numbers[25];

    stringstream ss(first_part);
    int number;

    int index = 0;
    while(ss >> number) {
      card[index] = number;
      index++;
    }

    index = 0;
    ss.str("");
    ss.clear();
    ss.str(second_part);

    while(ss >> number) {
      numbers[index] = number;
      index++;
    }

    int loto = 0;

    for (int i = 0; i < 25; i++) {
      for (int j = 0; j < 10; j++) {
        if(numbers[i] == card[j]) {
          loto++;
        }
      }
    }
    result[result_index] = loto;
    result_index++;
  }

  int count_array[188];
  for (int i = 0; i < 188; i++) {
    count_array[i] = 1; 
  }
  for (int i = 0; i < 188; i++) {
    for (int j = i + 1; j < i + 1 + result[i]; j++) {
      count_array[j] = count_array[j] + count_array[i];
    }
  }

  int total = 0;
  for (int i = 0; i < 188; i++) {
    cout << count_array[i] << " ";
    total += count_array[i];
  }
  
  cout << endl;
  cout << total << endl;
  return 0;
}
