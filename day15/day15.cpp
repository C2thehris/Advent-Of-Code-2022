#include <bits/stdc++.h>

using namespace std;

int manhattanDistance(pair<int, int> lhs, pair<int, int> rhs)
{
  return std::abs(lhs.first - rhs.first) + std::abs(lhs.second - rhs.second);
}

pair<int, int> parseLine(const string &line, int target)
{
  int begin = line.find('=');
  int end = line.find(',');
  int xSensor = std::stoi(line.substr(begin + 1, end - begin - 1));
  begin = line.find('=', begin + 1);
  end = line.find(',', end + 1);
  int ySensor = std::stoi(line.substr(begin + 1, end - begin + 1));
  begin = line.find('=', begin + 1);
  end = line.find(',', end + 1);
  int xBeacon = std::stoi(line.substr(begin + 1, end - begin + 1));
  begin = line.find('=', begin + 1);
  int yBeacon = std::stoi(line.substr(begin + 1));

  return {xSensor, manhattanDistance({xSensor, ySensor}, {xBeacon, yBeacon}) - abs(ySensor - target)};
}

void part1(vector<string> &lines)
{
  unsigned long long answer = 0;
  set<pair<int, int>> blocked;

  for (const string &line : lines)
  {
    auto [center, radius] = parseLine(line, 10);
    // auto [center, radius] = parseLine(line, 2000000);
    if (radius < 0)
    {
      continue;
    }
    pair<int, int> entry = {center - radius, center + radius};
    blocked.insert(entry);
  }

  int rightMost = INT32_MIN;
  for (const pair<int, int> &r : blocked)
  {
    int left = max(rightMost, r.first);
    int count = r.second - left;
    if (count > 0)
    {
      answer += count;
    }
    rightMost = max(rightMost, r.second);
  }

  cout << "PART 1: " << answer << endl;
}

pair<int, int> getCoords(const string &line, int target)
{
  int begin = line.find('=');
  int end = line.find(',');
  int xSensor = std::stoi(line.substr(begin + 1, end - begin - 1));
  begin = line.find('=', begin + 1);
  end = line.find(',', end + 1);
  int ySensor = std::stoi(line.substr(begin + 1, end - begin + 1));
  return {xSensor, ySensor};
}

vector<pair<int, int>> getEntryVector(const multimap<int, pair<int, int>> &m)
{
  vector<pair<int, int>> ret;
  ret.reserve(m.size());
  for (auto entry : m)
  {
    ret.push_back(entry.second);
  }
  return ret;
}

unsigned long long calculateFrequency(int y, int x)
{
  return x * 4000000ull + y;
}

void part2(vector<string> &lines)
{
  unsigned long long answer = 0;
  const int MIN_COORD = 0;
  // const int MAX_COORD = 20;
  const int MAX_COORD = 4000000;
  multimap<int, pair<int, int>> sensorToBounds;
  for (const string &line : lines)
  {
    auto [center, radius] = parseLine(line, MIN_COORD);
    auto [xSensor, ySensor] = getCoords(line, MIN_COORD);
    pair<int, int> entry = {xSensor - radius, xSensor + radius};
    sensorToBounds.emplace(ySensor, entry);
  }

  for (int i = MIN_COORD; i <= MAX_COORD; ++i)
  {
    int rightMost = MIN_COORD;
    int blockCount = 0;
    vector<pair<int, int>> blocked = getEntryVector(sensorToBounds);
    sort(blocked.begin(), blocked.end());
    for (const pair<int, int> &r : blocked)
    {
      if (r.second < r.first)
        continue;
      int left = max(rightMost, r.first);
      int right = min(r.second, MAX_COORD);
      int count = right - left;
      if (count > 0)
      {
        blockCount += count;
      }
      rightMost = max(rightMost, right);
    }
    if (blockCount < MAX_COORD - MIN_COORD)
    {
      vector<bool> present(MAX_COORD - MIN_COORD + 1, false);
      for (const pair<int, int> &r : blocked)
      {
        if (r.second < r.first)
          continue;
        int left = r.first;
        int right = r.second;
        int uBound = min(right, MAX_COORD);
        for (int j = max(left, MIN_COORD); j <= uBound; ++j)
        {
          present[j] = true;
        }
      }
      for (int j = 0; j < present.size(); ++j)
      {
        if (!present[j])
        {
          answer = calculateFrequency(i, j);
        }
      }
    }

    for (auto &p : sensorToBounds)
    {
      if (i < p.first)
      {
        p.second.first -= 1;
        p.second.second += 1;
      }
      else
      {
        p.second.first += 1;
        p.second.second -= 1;
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
