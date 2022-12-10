#include <bits/stdc++.h>

using namespace std;

string getPath(const vector<string> &path)
{
  string result;
  for (const string &s : path)
  {
    result += s + "/";
  }
  return result;
}

int seekDirIndex(const vector<string> &input, const string &subDirPath)
{
  vector<string> path;
  for (int i = 0; i < input.size(); ++i)
  {
    if (input[i].size() > 0 && input[i][0] == '$' && input[i][2] == 'c')
    {
      if (input[i][5] == '.')
      {
        path.pop_back();
      }
      else
      {
        path.push_back(input[i].substr(5));
      }
      if (getPath(path) == subDirPath)
      {
        return i + 2;
      }
    }
  }
  return -1;
}

long long dirSize(unordered_map<string, long long> &sizes, vector<string> &path, vector<string> &input, int currentInput)
{
  string cwd = getPath(path);
  long long size = 0;

  vector<string> subDirs;
  while (currentInput < input.size() && input[currentInput][0] != '$')
  {
    if (input[currentInput].length() > 3 && input[currentInput][0] == 'd')
    {
      subDirs.push_back(input[currentInput].substr(4));
    }
    else
    {
      size += std::stoi(input[currentInput].substr(0, input[currentInput].find(' ')));
    }
    ++currentInput;
  }

  for (const string &subDir : subDirs)
  {
    path.push_back(subDir);
    size += dirSize(sizes, path, input, seekDirIndex(input, getPath(path)));
    path.pop_back();
  }

  sizes[cwd] = size;
  return size;
}

void part1(vector<string> &lines)
{
  unsigned long long answer = 0;
  unordered_map<string, long long> sizes;
  vector<string> path{"/"};
  dirSize(sizes, path, lines, 2);

  for (const auto &[s, size] : sizes)
  {
    if (size < 100000)
    {
      answer += size;
    }
  }

  cout << "PART 1: " << answer << endl;
}

void part2(vector<string> &lines)
{
  long long answer;
  long long largestRemaining = 0;
  unordered_map<string, long long> sizes;
  vector<string> path{"/"};
  auto total = dirSize(sizes, path, lines, 2);
  constexpr long long FREE_REQUIRED = 70000000 - 30000000;

  for (const auto &[s, size] : sizes)
  {
    if (total - size <= FREE_REQUIRED)
    {
      if (total - size > largestRemaining)
      {
        answer = size;
        largestRemaining = total - size;
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
