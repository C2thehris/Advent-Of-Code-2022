#include <bits/stdc++.h>

using namespace std;

void part1(vector<string> &lines)
{
  unsigned long long answer = 0;
  int x = 1;
  size_t cycle = 0;
  int nextToCount = 20;
  for (size_t i = 0; i < lines.size(); ++i)
  {
    int v = 0;
    const string &line = lines[i];
    if (line == "")
    {
      continue;
    }
    if (line[0] == 'n')
    {
      ++cycle;
    }
    else
    {
      v = stoi(line.substr(5));
      ++cycle;
      if (cycle >= nextToCount)
      {
        nextToCount += 40;
        answer += x * cycle;
      }
      ++cycle;
    }
    if (cycle >= nextToCount)
    {
      nextToCount += 40;
      answer += x * cycle;
    }
    x += v;
  }

  cout << "PART 1: " << answer << endl;
}

void updateScreen(std::array<std::array<char, 40>, 6> &screen, int x, int cycle)
{
  const int row = cycle / 40;
  const int col = cycle % 40;
  if (x - 1 <= col && col <= x + 1)
  {
    screen[row][col] = '#';
  }
  else
  {
    screen[row][col] = '.';
  }
}

void print(const std::array<std::array<char, 40>, 6> &screen)
{
  for (size_t i = 0; i < 6; ++i)
  {
    for (size_t j = 0; j < 40; ++j)
    {
      cout << screen[i][j] << ' ';
    }
    cout << '\n';
  }
}

void part2(vector<string> &lines)
{
  int x = 1;
  size_t cycle = 0;
  int nextToCount = 20;
  std::array<std::array<char, 40>, 6> screen;

  for (size_t i = 0; i < lines.size(); ++i)
  {
    int v = 0;
    const string &line = lines[i];
    if (line == "")
    {
      continue;
    }
    if (line[0] != 'n')
    {
      v = stoi(line.substr(5));
      updateScreen(screen, x, cycle);
      ++cycle;
    }
    updateScreen(screen, x, cycle);
    ++cycle;
    x += v;
  }

  cout << "PART 2: " << endl;
  print(screen);
}

int main(int argc, char const *argv[])
{
  if (argc != 2)
  {
    cerr << "Invalid Usage. Usage: ./[binary] [input]" << endl;
    exit(EXIT_FAILURE);
  }

  string current;
  vector<string> lines;

  ifstream istr(argv[1]);

  while (getline(istr, current))
  {
    if (current == "\n")
      break;
    lines.push_back(current);
  }

  part1(lines);
  part2(lines);

  return EXIT_SUCCESS;
}
