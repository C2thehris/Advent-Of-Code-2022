#include <bits/stdc++.h>

using namespace std;

bool atMost1(int current, int next)
{
  if (current == 'S')
  {
    current = 'a';
  }
  if (next == 'E')
  {
    next = 'z';
  }
  return next - current <= 1;
}

vector<pair<int, int>> getNeighbors(const vector<string> &map, const char currentElev, pair<int, int> currentCoords)
{
  auto [x, y] = currentCoords;
  vector<pair<int, int>> ans;
  if (x > 0 && atMost1(currentElev, map[x - 1][y]))
  {
    ans.emplace_back(x - 1, y);
  }
  if (x < map.size() - 1 && atMost1(currentElev, map[x + 1][y]))
  {
    ans.emplace_back(x + 1, y);
  }
  if (y > 0 && atMost1(currentElev, map[x][y - 1]))
  {
    ans.emplace_back(x, y - 1);
  }
  if (y < map[0].size() - 1 && atMost1(currentElev, map[x][y + 1]))
  {
    ans.emplace_back(x, y + 1);
  }
  return ans;
}

unsigned long long performBFS(const vector<string> &lines, vector<vector<int>> &bfs, int i, int j)
{
  queue<pair<int, int>> bfsQ;
  bfsQ.emplace(i, j);
  bfs[i][j] = 0;

  while (!bfsQ.empty())
  {
    const auto current = bfsQ.front();
    bfsQ.pop();
    const vector<pair<int, int>> eligibleNeighbors = getNeighbors(lines, lines[current.first][current.second], current);
    for (const auto &neighbor : eligibleNeighbors)
    {
      if (bfs[neighbor.first][neighbor.second] == -1 || bfs[current.first][current.second] + 1 < bfs[neighbor.first][neighbor.second])
      {
        bfs[neighbor.first][neighbor.second] = bfs[current.first][current.second] + 1;
        bfsQ.push(neighbor);
        if (lines[neighbor.first][neighbor.second] == 'E')
        {
          return bfs[neighbor.first][neighbor.second];
        }
      }
    }
  }
  return INT32_MAX;
}

void part1(vector<string> &lines)
{
  unsigned long long answer = 0;
  std::vector<std::vector<int>> bfs(lines.size(), vector<int>(lines[0].size(), -1));

  for (size_t i = 0; i < lines.size(); ++i)
  {
    for (size_t j = 0; j < lines[0].size(); ++j)
    {
      if (lines[i][j] == 'S')
      {
        answer = performBFS(lines, bfs, i, j);
        break;
      }
    }
  }

  cout << "PART 1: " << answer << endl;
}

void part2(vector<string> &lines)
{
  unsigned long long answer = UINT64_MAX;
  for (int i = 0; i < lines.size(); ++i)
  {
    std::vector<std::vector<int>> bfs(lines.size(), vector<int>(lines[0].size(), -1));

    for (size_t i = 0; i < lines.size(); ++i)
    {
      for (size_t j = 0; j < lines[0].size(); ++j)
      {
        if (lines[i][j] == 'a')
        {
          answer = min(answer, performBFS(lines, bfs, i, j));
        }
      }
    }
  }

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
