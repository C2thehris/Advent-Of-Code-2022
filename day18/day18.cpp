#include <bits/stdc++.h>

using namespace std;

typedef set<tuple<int, int, int>> World;

World parseInput(const vector<string> &lines)
{
  World ret;
  for (const string &cube : lines)
  {
    int begin = 0;
    int end = cube.find(',');
    int x = stoi(cube.substr(begin, end));
    begin = end + 1;
    end = cube.find(',', begin);
    int y = stoi(cube.substr(begin, end - begin));
    begin = end + 1;
    end = cube.find(',', begin);
    int z = stoi(cube.substr(begin, end - begin));

    ret.emplace(x, y, z);
  }

  return ret;
}

int calculateSurfaceArea(const World &w)
{
  int answer = 0;
  for (const auto &[x, y, z] : w)
  {
    for (int i = -1; i <= 1; i += 2)
    {
      auto next = make_tuple(x + i, y, z);
      if (w.count(next) == 0)
      {
        answer += 1;
      }
    }
    for (int i = -1; i <= 1; i += 2)
    {
      auto next = make_tuple(x, y + i, z);
      if (w.count(next) == 0)
      {
        answer += 1;
      }
    }
    for (int i = -1; i <= 1; i += 2)
    {
      auto next = make_tuple(x, y, z + i);
      if (w.count(next) == 0)
      {
        answer += 1;
      }
    }
  }
  return answer;
}

void part1(vector<string> &lines)
{
  World w = parseInput(lines);
  unsigned long long answer = calculateSurfaceArea(w);

  cout << "PART 1: " << answer << endl;
}

vector<tuple<int, int, int>> getNeighbors(const tuple<int, int, int> &current)
{
  vector<tuple<int, int, int>> ret;
  auto x = get<0>(current);
  auto y = get<1>(current);
  auto z = get<2>(current);
  for (int i = -1; i <= 1; i += 2)
  {
    auto newPos = x + i;
    if (newPos >= 0 && newPos <= 20)
    {
      ret.emplace_back(newPos, y, z);
    }
  }
  for (int i = -1; i <= 1; i += 2)
  {
    auto newPos = y + i;
    if (newPos >= 0 && newPos <= 20)
    {
      ret.emplace_back(x, newPos, z);
    }
  }
  for (int i = -1; i <= 1; i += 2)
  {
    auto newPos = z + i;
    if (newPos >= 0 && newPos <= 20)
    {
      ret.emplace_back(x, y, newPos);
    }
  }
  return ret;
}

void part2(vector<string> &lines)
{
  World w = parseInput(lines);
  queue<tuple<int, int, int>> q;
  q.emplace(0, 0, 0);
  World bfs;
  bfs.emplace(0, 0, 0);
  while (!q.empty())
  {
    auto front = q.front();
    q.pop();
    auto neighbors = getNeighbors(front);
    for (const auto &neighbor : neighbors)
    {
      if (w.count(neighbor) == 0 && bfs.count(neighbor) == 0)
      {
        bfs.insert(neighbor);
        q.push(neighbor);
      }
    }
  }
  for (int i = 0; i < 20; ++i)
  {
    for (int j = 0; j < 20; ++j)
    {
      for (int k = 0; k < 20; ++k)
      {
        auto current = make_tuple(i, j, k);
        if (bfs.count(current) == 0)
        {
          w.emplace(current);
        }
      }
    }
  }

  unsigned long long answer = calculateSurfaceArea(w);
  cout << "PART 2: " << answer << endl;
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
