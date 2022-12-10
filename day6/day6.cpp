#include <bits/stdc++.h>

using namespace std;

bool unique(deque<char> &q)
{
  for (size_t i = 0; i < q.size(); ++i)
  {
    for (size_t j = i + 1; j < q.size(); ++j)
    {
      if (q[i] == q[j])
        return false;
    }
  }
  return true;
}

void part1(vector<string> &lines)
{
  auto answer = 0ull;
  deque<char> q;

  q.push_back(lines[0][0]);
  q.push_back(lines[0][1]);
  q.push_back(lines[0][2]);
  size_t i = 3;
  for (; i < lines[0].length(); ++i)
  {
    q.push_back(lines[0][i]);
    if (unique(q))
    {
      answer = i + 1;
      break;
    }
    // cout << q[0] << ' ' << q[1] << ' ' << q[2] << ' ' << q[3] << '\n';
    q.pop_front();
  }

  cout << "PART 1: " << answer << endl;
}

void part2(vector<string> &lines)
{
  auto answer = 0ull;
  deque<char> q;

  size_t i = 0;
  for (; i < 13; ++i)
  {
    q.push_back(lines[0][i]);
  }
  for (; i < lines[0].length(); ++i)
  {
    q.push_back(lines[0][i]);
    if (unique(q))
    {
      answer = i + 1;
      break;
    }
    q.pop_front();
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
