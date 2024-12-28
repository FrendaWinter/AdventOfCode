#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>

#include <sstream>
using namespace std;

void parse_input(const vector<string> &input, vector<tuple<string, string, string>> &output, string keyword) {
	bool flag = false;
	for (uint64_t i = 1; i < input.size(); i++) {
		string line = input[i];

		if (line == keyword + " map:") {
			flag = true;
			continue;
		}

		if (flag && !line.empty()) {
			stringstream ss(line);
			string des, source, range;
			ss >> des >> source >> range;
			output.push_back(make_tuple(des, source, range));
		}

		if (flag && line.empty()) {
			flag = false;
		}
	}
}

vector<uint64_t> map_input_to_output(const vector<tuple<string, string, string>> &input, vector<uint64_t> &output) {
	for (uint64_t i = 0; i < output.size(); i++) {
		for (uint64_t j = 0; j < input.size(); j++) {
			uint64_t des = stoull(get<0>(input[j]));
			uint64_t source = stoull(get<1>(input[j]));
			uint64_t range = stoull(get<2>(input[j]));

			if (output[i] >= source && output[i] <= source + range) {
				output[i] = des + (output[i] - source);
				break;
			}
		}
	}

	return output;
}

uint64_t find_min (const vector<uint64_t> &input) {
	uint64_t min = input[0];
	for (uint64_t i = 1; i < input.size(); i++) {
		if (input[i] < min) {
			min = input[i];
		}
	}

	return min;
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

	// Mapping  
	vector<uint64_t> result_list;
	for (uint64_t i = 0; i < seed_list.size(); i++) {
		if (i % 2 == 0) {
			uint64_t start = stoull(seed_list[i]);
			uint64_t range_of_seed = stoull(seed_list[i+1]);
			for (uint64_t j = start; j <= start + range_of_seed; j++) {
				result_list.push_back(j);
			}
		}
	}

	cout << "Mapping seed list done" << endl;

	result_list = map_input_to_output(seed_to_soil, result_list);
	result_list = map_input_to_output(soil_to_fertilizer, result_list);
	result_list = map_input_to_output(fertilizer_to_water, result_list);
	result_list = map_input_to_output(water_to_light, result_list);
	result_list = map_input_to_output(light_to_temperature, result_list);
	result_list = map_input_to_output(temperature_to_humidity, result_list);
	result_list = map_input_to_output(humidity_to_location, result_list);

	cout << "Process done" << endl;
	cout << "Part 2: " << find_min(result_list) << endl;

	return 0;
}
