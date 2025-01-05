#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <bitset>
#include <math.h>

enum blockType {
    File,
    Free
};

typedef struct{
    blockType type;
    int size;
    int data;
} block;

using namespace std;

int main(int argc, char *argv[])
{
    // Part 2
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
    vector<block> diskMap;
    int IDs = 0;
    for (int i = 0; i < s.length(); i++) {
        int n = s[i] - '0';
        if (i % 2 == 0) {
            diskMap.push_back({File, n, IDs});
            IDs++;
        } else {
            diskMap.push_back({Free, n, -1});
        }
    }

    // Compacting
    for (int i = diskMap.size() - 1; i >= 0; i--) {
        if (diskMap[i].type == File) {
            for (int j = 0; j < i; j ++) {
                // Found empty space to put file in
                if (diskMap[j].type == Free && diskMap[i].size <= diskMap[j].size) {
                    // Decrease size of the free space that take the file
                    diskMap[j].size -= diskMap[i].size;

                    // Increase size of the free space block that be extend when file move
                    int x = i;
                    while (diskMap[x].type != Free) {
                        x--;
                    }
                    diskMap[x].size += diskMap[i].size;

                    // Insert file to free space
                    diskMap.insert(diskMap.begin() + j, diskMap[i]);
                    
                    // Delete file block at old index
                    diskMap.erase(diskMap.begin() + i + 1);

                    break;
                }
            }
        }
    }

    // Display the contents of the vector
    // for (const auto& blk : diskMap) {
    //     std::cout << "Type: " << (blk.type == File ? "File" : "Free")
    //               << ", Size: " << blk.size
    //               << ", Data: " << blk.data << std::endl;
    // }

    // Cal checksum
    int diskIndex = 0;
    for (int i = 0; i < diskMap.size(); i++) {
        for (int j = 0; j < diskMap[i].size; j++) {
            if (diskMap[i].type == File) {
                result += diskIndex * diskMap[i].data;
            }
            diskIndex++;
        }
    }
    cout << "Result: " << result << endl;
}
