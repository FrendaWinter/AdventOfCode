#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include <sstream>
using namespace std;

int main(int argc, char *argv[]) {
	// Part 2
	vector<string> input;
	string filename = "data/test_data_05.txt";
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

	// Handle seed input
	string seeds = input[0];
	seeds = seeds.substr(7);

	istringstream ss(seeds);
	string word;

	vector<string> seed_list;
	while (ss >> word) {
		seed_list.push_back(word);
	}

	// Out put seed list
	for (int i = 0; i < input.size(); i++) {
		cout << seed_list[i] << endl;
	}
	
	// Handle input seed to soil
	vector<tuple<string, string, string>> seed_to_soil;

	bool is_sToS = false;
	for (int i = 1; i < input.size(); i++) {
		string line = input[i];

		if (line == "seed-to-soil map:") {
			is_sToS = true;
			continue;
		}

		if (is_sToS && line[0] >= '0' && line[0] <= '9') {
			stringstream ss(line);
			cout << line << endl;
			string seed, soil, result;
			ss >> seed >> soil >> result;
			seed_to_soil.push_back(make_tuple(seed, soil, result));
		}

		if (is_sToS && line == "\n") {
			is_sToS = false;
		}
	}

	for (int i = 0; i < seed_to_soil.size(); i++) {
		cout << get<0>(seed_to_soil[i]) << " " << get<1>(seed_to_soil[i]) << " " << get<2>(seed_to_soil[i]) << endl;
	}

	cout << endl;
	return 0;
}
