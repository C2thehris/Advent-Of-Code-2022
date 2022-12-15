#include <bits/stdc++.h>

using namespace std;

pair<int, int> parsePoint(const string &view, int begin)
{
  int split = view.find(',', begin);
  return {std::stoi(view.substr(begin, split - begin)), std::stoi(view.substr(split + 1, view.find(' ', split)))};
}

set<pair<int, int>> parseLines(const vector<string> &lines, int &floor)
{
  floor = 0;
  set<pair<int, int>> ret;
  for (int k = 0; k < lines.size(); ++k)
  {
    const string &line = lines[k];
    int begin = 0;
    pair<int, int> current = parsePoint(line, begin);
    floor = max(floor, current.second);
    while (true)
    {
      begin = line.find('>', begin) + 2;
      if (begin == 1)
      {
        break;
      }
      pair<int, int> next = parsePoint(line, begin);
      if (current.first == next.first)
      {
        if (current.second <= next.second)
        {
          for (int i = current.second; i <= next.second; ++i)
          {
            ret.emplace(current.first, i);
          }
        }
        else
        {
          for (int i = current.second; i >= next.second; --i)
          {
            ret.emplace(current.first, i);
          }
        }
      }
      else
      {
        if (current.first <= next.first)
        {
          for (int i = current.first; i <= next.first; ++i)
          {
            ret.emplace(i, current.second);
          }
        }
        else
        {
          for (int i = current.first; i >= next.first; --i)
          {
            ret.emplace(i, current.second);
          }
        }
      }
      current = next;
      floor = max(floor, current.second);
    }
  }
  return ret;
}

void part1(vector<string> &lines)
{
  unsigned long long answer = 0;
  int floor;
  set<pair<int, int>> repr = parseLines(lines, floor);
  bool cont = true;
  while (cont)
  {
    pair<int, int> pos{500, 0};
    cont = false;
    while (pos.second <= floor)
    {
      if (!repr.count({pos.first, pos.second + 1}))
      {
        pos = {pos.first, pos.second + 1};
      }
      else if (!repr.count({pos.first - 1, pos.second + 1}))
      {
        pos = {pos.first - 1, pos.second + 1};
      }
      else if (!repr.count({pos.first + 1, pos.second + 1}))
      {
        pos = {pos.first + 1, pos.second + 1};
      }
      else
      {
        ++answer;
        repr.insert(pos);
        cont = true;
        break;
      }
    }
  }

  cout << "PART 1: " << answer << endl;
}

void part2(vector<string> &lines)
{
  unsigned long long answer = 0;
  int floor;
  set<pair<int, int>> repr = parseLines(lines, floor);
  floor += 2;
  while (true)
  {
    pair<int, int> pos{500, 0};
    while (true)
    {
      if (pos.second + 1 == floor)
      {
        repr.insert(pos);
        ++answer;
        break;
      }
      if (!repr.count({pos.first, pos.second + 1}))
      {
        pos = {pos.first, pos.second + 1};
      }
      else if (!repr.count({pos.first - 1, pos.second + 1}))
      {
        pos = {pos.first - 1, pos.second + 1};
      }
      else if (!repr.count({pos.first + 1, pos.second + 1}))
      {
        pos = {pos.first + 1, pos.second + 1};
      }
      else
      {
        ++answer;
        repr.insert(pos);
        break;
      }
    }
    if (pos.first == 500 && pos.second == 0)
    {
      break;
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
