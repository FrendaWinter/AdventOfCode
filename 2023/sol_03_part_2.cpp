#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

bool is_number (char c) {
	return c >= '0' && c <= '9';
}

void add_gear_2_sides(vector<string> &gears,const string s, int j) {
	string a = "", b = "";
	for ( int i = 1; i < 4;i++) {
		if (is_number (s[j -i])) {
			a += s[j - i];
		}

		else break;
	}

	for (int i = 1; i < 4; i++) {
		if (is_number (s[j + i])) {
			b += s[j + i];
		}
		
		else break;
	}

	reverse(a.begin(), a.end());
	gears.push_back(a);
	gears.push_back(b);
}

void add_gear_left(vector<string> &gears, const string s, int j) {
	string a = "";
	for (int i = 1; i < 4; i++) {
		if (is_number(s[j - i])) {
			a += s[j - i];
		}
		else break;
	}
	reverse(a.begin(), a.end());
	gears.push_back(a);
}

void add_gear_right(vector<string> &gears, const string s, int j) {
	string a = "";
	for (int i = 1; i < 4; i++) {
		if (is_number(s[j + i])) {
			a += s[j + i];
		}
		else break;
	}
	gears.push_back(a);
}


int main(int argc, char *argv[]) {
	// Part 2
	vector<string> input;
	string filename = "data/test_data_03.txt";
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

	string dots(140, '.');
	input.push_back(dots);
	input.insert(input.begin(), dots);

	int result = 0;
	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < input[i].size(); j++) {
			if (input[i][j] == '*') {
				vector<string> gears;

				// Get the gears around the current * up, full number
				// eg: 123
				//     .*.
				if (is_number(input[i - 1][j - 1]) && is_number(input[i - 1][j]) && is_number(input[i - 1][j + 1])) {
					gears.push_back(input[i - 1].substr(j - 1, 3));
				}
				
				// Get the gears around the current * down, full number
				// eg: .*.
				//     123
				if (is_number(input[i + 1][j - 1]) && is_number(input[i + 1][j]) && is_number(input[i + 1][j + 1])) {
					gears.push_back(input[i + 1].substr(j - 1, 3));
				}

				// Get the gears around the current * up, 2 sides
				// eg: 1.2
				//	   .*.
				if (is_number(input[i - 1][j - 1]) && is_number(input[i - 1][j+ 1]) && input[i - 1][j] == '.') {
					add_gear_2_sides(gears, input[i - 1], j);
				}

				// Get the gears around the current * down, 2 sides
				// eg: .*.
				//     1.2
				if (is_number(input[i + 1][j - 1]) && is_number(input[i + 1][j + 1]) && input[i + 1][j] == '.') {
					add_gear_2_sides(gears, input[i + 1], j);
				}

				// Get the gears around the current * up left 1 number
				// eg: 1..
				//     .*.
				if (is_number(input[i - 1][j - 1]) && input[i - 1][j] == '.' && input[i - 1][j + 1] == '.') {
					add_gear_left(gears, input[i - 1], j);
				}

				// Get the gears around the current * up right 1 number
				// eg: ..1
				//     .*.
				if (is_number(input[i - 1][j + 1]) && input[i - 1][j] == '.' && input[i - 1][j - 1] == '.') {
					add_gear_right(gears, input[i - 1], j);
				}

				// Get the gears around the current * down left 1 number
				// eg: .*.
				//     1..
				if (is_number(input[i + 1][j - 1]) && input[i + 1][j] == '.' && input[i + 1][j + 1] == '.') {
					add_gear_left(gears, input[i + 1], j);
				}

				// Get the gears around the current * down right 1 number
				// eg: .*.
				//     ..1
				if (is_number(input[i + 1][j + 1]) && input[i + 1][j] == '.' && input[i + 1][j - 1] == '.') {
					add_gear_right(gears, input[i + 1], j);
				}

				// Get the gears around the current * left and a number
				// eg: 1*.
				if (is_number(input[i][j - 1])) {
					add_gear_left(gears, input[i], j);
				}
				
				// Get the gears around the current * right and a number
				// eg: .*1
				if (is_number(input[i][j + 1])) {
					add_gear_right(gears, input[i], j);
				}

				// Get the gears around the current * up, left 2 number
				// eg: 12.
				//     .*.
				if (is_number(input[i - 1][j]) && is_number(input[i - 1][j - 1]) && input[i - 1][j + 1] == '.') {
					add_gear_left(gears, input[i - 1], j + 1);
				}

				// Get the gears around the current * up, right 2 number
				// eg: .12
				//     .*.
				if (is_number(input[i - 1][j]) && is_number(input[i - 1][j + 1]) && input[i - 1][j - 1] == '.') {
					add_gear_right(gears, input[i - 1], j - 1);
				}

				// Get the gears around the current * down, left 2 number
				// eg: .*.
				//	   12.
				if (is_number(input[i + 1][j]) && is_number(input[i + 1][j - 1]) && input[i + 1][j + 1] == '.') {
					add_gear_left(gears, input[i + 1], j + 1);
				}

				// Get the gears around the current * down, right 2 number
				// eg: .*.
				//     .12
				if (is_number(input[i + 1][j]) && is_number(input[i + 1][j + 1]) && input[i + 1][j - 1] == '.') {
					add_gear_right(gears, input[i + 1], j - 1);
				}

				// Get the gears around the current * up, 1 number middle
				// eg: .1.
				//     .*.
				if (is_number(input[i - 1][j]) && input[i - 1][j - 1] == '.' && input[i - 1][j + 1] == '.') {
					string tmp(1, input[i - 1][j]);
					gears.push_back(tmp);
				}

				// Get the gears around the current * down, 1 number middle
				// eg: .*.
				//     .1.
				if (is_number(input[i + 1][j]) && input[i + 1][j - 1] == '.' && input[i + 1][j + 1] == '.') {
					string tmp(1, input[i + 1][j]);
					gears.push_back(tmp);
				}

				string c = "";

				c += input[i - 1][j - 1];
				c += input[i - 1][j];
				c += input[i - 1][j + 1];
				c += input[i][j - 1];
				c += input[i][j];
				c += input[i][j + 1];
				c += input[i + 1][j - 1];
				c += input[i + 1][j];
				c += input[i + 1][j + 1];
				
				cout << c << endl;

				if (gears.size() < 2) {
					// No gear ratio for this *
					cout << "No gear ratio for this *" << endl;
					continue;
				}
				
				int gear_ratio = 1;
				for (auto gear : gears) {
					cout << gear << " ";
					gear_ratio *= stoi(gear);
				}
				result += gear_ratio;
				cout << endl;
			}
		}
	}
	cout << "Part 2: " << result << endl;
	return 0;
}
