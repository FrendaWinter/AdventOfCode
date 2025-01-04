#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <bitset>
#include <math.h>

using namespace std;

bool isCompacted(const vector<int> &a) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == -1 ) return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    // Part 1
	vector<string> input;
	string filename = "data/input_day_09.txt";
    ifstream input_file(filename);

    if (input_file.is_open())
    {
        string line;
        while (std::getline(input_file, line))
        {
			input.push_back(line);
		}
        input_file.close();
    }
    else
    {
        cerr << "Error when open file" << endl;
    }

    long long int result = 0;

    // Decrypt input to obtain disk map
    string s = input[0];
    vector<int> diskMap;
    int IDs = 0;
    for (int i = 0; i < s.length(); i++) {
        int n = s[i] - '0';
        if (i % 2 == 0) {
            for (int j = 0; j < n; j++) {
                diskMap.push_back(IDs);
            }
            IDs++;
        } else {
            for (int j = 0; j < n; j++) {
                diskMap.push_back(-1);
            }
        }
    }

    // Disk Map Compacting
    for (int x = diskMap.size() - 1; x >= 0; x--) {
        if (isCompacted(diskMap)) {
            break;
        }

        if (diskMap[x] != -1)
        {
            for (int y = 0; y < x; y++)
            {
                // Swap value of IDs ele to free space ele (-1)
                if (diskMap[y] == -1) {
                    diskMap[y] = diskMap[x];
                    diskMap.erase(diskMap.begin() + x);
                    break;
                }
            }
        } else {
            // Delete ele if it = -1 (free space)
            diskMap.erase(diskMap.begin() + x);
        }
    }

    // Cal hash
    for (int i = 0; i < diskMap.size(); i++)
    {
        if (diskMap[i] == -1) continue;

        result += i * diskMap[i];
    }

    cout << "Result: " << result << endl;
    }
