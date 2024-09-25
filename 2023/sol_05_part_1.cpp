#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include <sstream>
using namespace std;

void parse_input(const vector<string> &input, vector<tuple<string, string, string>> &output, string keyword) {
	bool flag = false;
	for (int i = 1; i < input.size(); i++) {
		string line = input[i];

		if (line == keyword + " map:") {
			flag = true;
			continue;
		}

		if (flag && !line.empty()) {
			stringstream ss(line);
			string des, source, result;
			ss >> des >> source >> result;
			output.push_back(make_tuple(des, source, result));
		}

		if (flag && line.empty()) {
			flag = false;
		}
	}
}

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
		/*cout << seed_list[i] << endl;*/
	}
	
	// Handle input seed to soil
	vector<tuple<string, string, string>> seed_to_soil;
	vector<tuple<string, string, string>> soil_to_fertilizer;
	vector<tuple<string, string, string>> fertilizer_to_water;
	vector<tuple<string, string, string>> water_to_light;
	vector<tuple<string, string, string>> light_to_temperature;
	vector<tuple<string, string, string>> temperature_to_humidity;
	vector<tuple<string, string, string>> humidity_to_location;

	parse_input(input, seed_to_soil, "seed-to-soil");
	parse_input(input, soil_to_fertilizer, "soil-to-fertilizer");
	parse_input(input, fertilizer_to_water, "fertilizer-to-water");
	parse_input(input, water_to_light, "water-to-light");
	parse_input(input, light_to_temperature, "light-to-temperature");
	parse_input(input, temperature_to_humidity, "temperature-to-humidity");
	parse_input(input, humidity_to_location, "humidity-to-location");

	cout << "Parsing input done" << endl;
	return 0;
}
