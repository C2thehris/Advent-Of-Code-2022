#include <bits/stdc++.h>

using namespace std;

typedef list<pair<long long, int>> Repr;
typedef Repr::iterator It;

Repr parseInput(const vector<string> &lines)
{
  Repr ret;
  int id = 0;
  for (const string &line : lines)
  {
    ret.emplace_back(stoi(line), id++);
  }
  return ret;
}

auto circle_next(Repr &l, const It it)
{
  It ret = it;
  ++ret;
  if (ret == l.end())
  {
    ret = l.begin();
  }
  return ret;
}

auto circle_prev(Repr &l, const It it)
{
  It ret = it;
  if (ret == l.begin())
  {
    ret = l.end();
  }
  --ret;
  return ret;
}

void print(const Repr &l)
{
  for (const auto &p : l)
  {
    cout << p.first << ' ';
  }
  cout << '\n';
}

Repr mix(const Repr &prev)
{
  const long long numElems = prev.size();

  Repr nums(prev);
  for (int i = 0; i < numElems; ++i)
  {
    auto it = nums.begin();
    while (it->second != i)
    {
      ++it;
    }
    auto numHops = it->first % (numElems - 1);
    auto dest = it;
    if (numHops > 0)
    {
      dest = circle_next(nums, dest);
      for (int i = 0; i < numHops; ++i)
      {
        dest = circle_next(nums, dest);
      }
    }
    else if (numHops < 0)
    {
      for (int i = 0; i > numHops; --i)
      {
        dest = circle_prev(nums, dest);
      }
    }

    nums.insert(dest, *it);
    it = nums.erase(it);
  }

  return nums;
}

void part1(vector<string> &lines)
{
  long long answer = 0;
  auto nums = parseInput(lines);
  nums = mix(nums);

  auto it = nums.begin();
  while (it->first != 0)
  {
    ++it;
  }

  it = circle_next(nums, it);
  for (int i = 1; i <= 3000; ++i)
  {
    if (i % 1000 == 0)
    {
      answer += it->first;
    }
    it = circle_next(nums, it);
  }

  cout << "PART 1: " << answer << endl;
}

void part2(vector<string> &lines)
{
  unsigned long long answer = 0;
  auto nums = parseInput(lines);
  for (auto &p : nums)
  {
    p.first *= 811589153l;
  }

  // print(nums);
  for (int i = 0; i < 10; ++i)
  {
    nums = mix(nums);
    // print(nums);
  }

  auto it = nums.begin();
  while (it->first != 0)
  {
    ++it;
  }

  it = circle_next(nums, it);
  for (int i = 1; i <= 3000; ++i)
  {
    if (i % 1000 == 0)
    {
      answer += it->first;
    }
    it = circle_next(nums, it);
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
