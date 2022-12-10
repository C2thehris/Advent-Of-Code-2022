#include <bits/stdc++.h>

using namespace std;

int getDist(const pair<int, int> &head, const pair<int, int> &tail)
{
  return std::max(std::abs(head.first - tail.first), std::abs(head.second - tail.second));
}

void moveTail(set<pair<int, int>> &tailVisits, char dir, int dist, pair<int, int> &headPos, pair<int, int> &tailPos)
{
  for (int i = 0; i < dist; ++i)
  {
    switch (dir)
    {
    case 'U':
      ++headPos.second;
      break;
    case 'D':
      --headPos.second;
      break;
    case 'L':
      --headPos.first;
      break;
    case 'R':
      ++headPos.first;
      break;
    }
    if (getDist(headPos, tailPos) >= 2)
    {
      switch (dir)
      {
      case 'U':
        tailPos = {headPos.first, headPos.second - 1};
        break;
      case 'D':
        tailPos = {headPos.first, headPos.second + 1};
        break;
      case 'L':
        tailPos = {headPos.first + 1, headPos.second};
        break;
      case 'R':
        tailPos = {headPos.first - 1, headPos.second};
        break;
      }
    }
    tailVisits.insert(tailPos);
  }
}

void moveBigTail(set<pair<int, int>> &tailVisits, char dir, int dist, std::array<pair<int, int>, 10> &rope)
{
  for (int i = 0; i < dist; ++i)
  {
    pair<int, int> tempPrev = rope[0];
    switch (dir)
    {
    case 'U':
      ++rope[0].second;
      break;
    case 'D':
      --rope[0].second;
      break;
    case 'L':
      --rope[0].first;
      break;
    case 'R':
      ++rope[0].first;
      break;
    }

    for (size_t j = 1; j < 10; ++j)
    {
      if (getDist(rope[j - 1], rope[j]) >= 2)
      {
        auto diffX = rope[j].first - rope[j - 1].first;
        auto diffY = rope[j].second - rope[j - 1].second;
        if (diffX != 0)
        {
          diffX /= std::abs(diffX);
        }
        if (diffY != 0)
        {
          diffY /= std::abs(diffY);
        }
        rope[j].first -= diffX;
        rope[j].second -= diffY;
      }
      else
      {
        break;
      }
    }
    tailVisits.insert(rope[9]);
  }
}

void part1(vector<string> &lines)
{
  set<pair<int, int>> tailVisits;
  pair<int, int> head{0, 0};
  pair<int, int> tail{0, 0};
  for (const string &line : lines)
  {
    const char dir = line[0];
    const int dist = std::stoi(line.substr(2));
    moveTail(tailVisits, dir, dist, head, tail);
  }

  cout << "PART 1: " << tailVisits.size() << endl;
}

void part2(vector<string> &lines)
{
  set<pair<int, int>> tailVisits;
  std::array<pair<int, int>, 10> rope = {};
  for (const string &line : lines)
  {
    const char dir = line[0];
    const int dist = std::stoi(line.substr(2));
    moveBigTail(tailVisits, dir, dist, rope);
  }

  cout << "PART 2: " << tailVisits.size() << endl;
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
