#include <iostream>
#include <string>
#include <vector>

#include "utils.cpp"

using namespace std;

int main()
{
  vector<string> lines = readFileLines("./data/input_1.txt");

  if (lines.empty())
  {
    cerr << "File is emmpty" << endl;
    return 1;
  }

  vector<string> directions = split(lines[0], ", ");

  int x, y = 0;

  for (int i = 0; i < directions.size(); i++)
  {
    string direction = directions[i].substr(0, 1);

    string step = directions[i].substr(1, directions[i].length() - 1);

    // cout << direction << " " << step << endl;
    int stepLength = std::stoi(step);

    int di = 1;
    // if odd -> Change y -> Dir -
    // if even -> Change x -> Dir +

    if (i % 2 == 0)
    {
      if (direction == "R")
      {
        x += di * stepLength;
        di *= -1;
      }
      else
      {
        x -= di * stepLength;
        di *= -1;
      }
    }
    else
    {
      if (direction == "R")
      {
        y += di * stepLength;
        di *= -1;
      }
      else
      {
        y -= di * stepLength;
        di *= -1;
      }
    }
  }
  cout << x + y;
}
