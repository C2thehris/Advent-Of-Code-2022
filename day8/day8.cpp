#include <bits/stdc++.h>

using namespace std;

void part1(vector<string> &lines)
{
  unsigned long long answer = 0;
  vector<vector<int>> heights(lines.size(), vector<int>(lines[0].size(), 0));
  vector<vector<bool>> visible(lines.size(), vector<bool>(lines[0].size(), false));
  for (size_t i = 0; i < lines.size(); ++i)
  {
    for (size_t j = 0; j < lines[0].size(); ++j)
    {
      heights[i][j] = lines[i][j] - '0';
    }
  }
  for (size_t i = 0; i < heights.size(); ++i)
  {
    visible[i][0] = true;
    visible[i][heights[0].size() - 1] = true;
  }
  for (size_t i = 0; i < heights[0].size(); ++i)
  {
    visible[0][i] = true;
    visible[heights.size() - 1][i] = true;
  }

  for (size_t i = 1; i < heights.size() - 1; ++i)
  {
    int rowMax = heights[i][0];
    for (size_t j = 1; j < heights[0].size() - 1; ++j)
    {
      if (heights[i][j] > rowMax)
      {
        visible[i][j] = true;
        rowMax = heights[i][j];
      }
    }
    rowMax = heights[i][heights[0].size() - 1];
    for (size_t j = heights[0].size() - 1; j >= 1; --j)
    {
      if (heights[i][j] > rowMax)
      {
        visible[i][j] = true;
        rowMax = heights[i][j];
      }
    }
  }

  for (size_t j = 1; j < heights[0].size() - 1; ++j)
  {
    int rowMax = heights[0][j];
    for (size_t i = 1; i < heights.size() - 1; ++i)
    {
      if (heights[i][j] > rowMax)
      {
        visible[i][j] = true;
        rowMax = heights[i][j];
      }
    }
    rowMax = heights[heights.size() - 1][j];
    for (size_t i = heights.size() - 1; i >= 1; --i)
    {
      if (heights[i][j] > rowMax)
      {
        visible[i][j] = true;
        rowMax = heights[i][j];
      }
    }
  }

  for (size_t i = 0; i < heights.size(); ++i)
  {
    for (size_t j = 0; j < heights[0].size(); ++j)
    {
      answer += visible[i][j];
    }
  }

  cout << "PART 1: " << answer << endl;
}

unsigned long long computeVisible(const vector<vector<int>> &heights, int r, int c)
{
  unsigned long long res = 1;
  const int height = heights[r][c];
  int current = 0;
  for (int i = r - 1; i >= 0; --i)
  {
    ++current;
    if (heights[i][c] >= height)
    {
      break;
    }
  }
  res *= current;
  current = 0;
  for (int i = r + 1; i < heights.size(); ++i)
  {
    ++current;
    if (heights[i][c] >= height)
    {
      break;
    }
  }
  res *= current;
  current = 0;
  for (int i = c - 1; i >= 0; --i)
  {
    ++current;
    if (heights[r][i] >= height)
    {
      break;
    }
  }
  res *= current;
  current = 0;
  for (int i = c + 1; i < heights[0].size(); ++i)
  {
    ++current;
    if (heights[r][i] >= height)
    {
      break;
    }
  }
  res *= current;
  return res;
}

void part2(vector<string> &lines)
{
  unsigned long long answer = 0;
  vector<vector<int>> heights(lines.size(), vector<int>(lines[0].size(), 0));
  for (size_t i = 0; i < lines.size(); ++i)
  {
    for (size_t j = 0; j < lines[0].size(); ++j)
    {
      heights[i][j] = lines[i][j] - '0';
    }
  }

  for (size_t i = 0; i < heights.size(); ++i)
  {
    for (size_t j = 0; j < heights[0].size(); ++j)
    {
      answer = std::max(answer, computeVisible(heights, i, j));
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
