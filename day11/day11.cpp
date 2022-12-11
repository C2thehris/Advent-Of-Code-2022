#include <bits/stdc++.h>
#include <utility>

using namespace std;

class Monkey
{
  deque<int> m_items;
  std::function<long long(long long)> operation;
  std::function<bool(long long)> test;
  std::array<int, 2> m_targets;
  int inspections = 0;
  int mod;
  bool m_worry;

public:
  Monkey(const vector<string> &lines, bool worry) : m_worry(worry)
  {
    int begin = 18;
    int end = 0;
    const string &items = lines[0];
    while (end != -1)
    {
      end = items.find(',', begin);
      if (end == -1)
      {
        m_items.push_back(std::stoi(items.substr(begin)));
        break;
      }
      else
      {
        m_items.push_back(std::stoi(items.substr(begin, end - begin)));
      }
      begin = end + 2;
    }
    const char op = lines[1][23];
    if (lines[1][25] == 'o')
    {
      operation = std::function<long long(long long)>{[op](long long old) -> long long
                                                      {
                                                        switch (op)
                                                        {
                                                        case '+':
                                                          return old + old;
                                                        case '-':
                                                          return 0;
                                                        case '*':
                                                          return old * old;
                                                        case '/':
                                                          return 1;
                                                        default:
                                                          __builtin_unreachable();
                                                        }
                                                      }};
    }
    else
    {
      const int val = std::stoi(lines[1].substr(25));
      operation = std::function<long long(long long)>{[op, val](long long old) -> long long
                                                      {
                                                        switch (op)
                                                        {
                                                        case '+':
                                                          return old + val;
                                                        case '-':
                                                          return old - val;
                                                        case '*':
                                                          return old * val;
                                                        case '/':
                                                          return old / val;
                                                        default:
                                                          __builtin_unreachable();
                                                        }
                                                      }};
    }
    const int divisor = std::stoi(lines[2].substr(21));
    mod = divisor;
    test = std::function<bool(long long)>{
        [divisor](long long val) -> bool
        {
          return val % divisor == 0;
        }};
    m_targets[0] = std::stoi(lines[3].substr(29));
    m_targets[1] = std::stoi(lines[4].substr(30));
  }

  void add(int val)
  {
    m_items.push_back(val);
  }

  int count() const
  {
    return m_items.size();
  }

  pair<int, long long> inspect()
  {
    ++inspections;
    auto ne = operation(m_items.front());
    if (ne < 0)
    {
      cerr << "HI" << endl;
    }
    m_items.pop_front();
    if (m_worry)
    {
      ne /= 3;
    }

    if (test(ne))
    {
      return {m_targets[0], ne};
    }
    else
    {
      return {m_targets[1], ne};
    }
  }

  int getMod()
  {
    return mod;
  }

  int inspectCount() const
  {
    return inspections;
  }
};

vector<Monkey> parseInput(const vector<string> &lines, bool worry3)
{
  vector<Monkey> monkeys;
  for (int i = 0; i < lines.size(); i += 7)
  {
    vector<string> monkeyInput;
    for (int j = i + 1; j < i + 7; ++j)
    {
      monkeyInput.push_back(lines[j]);
    }
    monkeys.emplace_back(monkeyInput, worry3);
  }
  return monkeys;
}

void part1(vector<string> &lines)
{
  vector<Monkey> monkeys = parseInput(lines, true);

  for (size_t i = 0; i < 20; ++i)
  {
    for (int j = 0; j < monkeys.size(); ++j)
    {
      Monkey &monkey = monkeys[j];
      while (monkey.count())
      {
        auto target = monkey.inspect();
        monkeys[target.first].add(target.second);
      }
    }
  }

  std::array<int, 2> largest = {};
  for (int i = 0; i < monkeys.size(); ++i)
  {
    auto inspections = monkeys[i].inspectCount();
    if (inspections > largest[0])
    {
      largest[0] = inspections;
    }
    sort(largest.begin(), largest.end());
  }

  cout << "PART 1: " << largest[0] * largest[1] << endl;
}

void part2(vector<string> &lines)
{
  vector<Monkey> monkeys = parseInput(lines, false);
  int mod = 1;
  for (int i = 0; i < monkeys.size(); ++i)
  {
    mod = lcm(mod, monkeys[i].getMod());
  }

  for (size_t i = 0; i < 10000; ++i)
  {
    for (int j = 0; j < monkeys.size(); ++j)
    {
      Monkey &monkey = monkeys[j];
      while (monkey.count())
      {
        auto target = monkey.inspect();
        monkeys[target.first].add((target.second % mod));
      }
    }
  }

  std::array<int, 2> largest = {};
  for (int i = 0; i < monkeys.size(); ++i)
  {
    auto inspections = monkeys[i].inspectCount();
    if (inspections > largest[0])
    {
      largest[0] = inspections;
    }
    sort(largest.begin(), largest.end());
  }
  unsigned long long answer;
  answer = largest[0];
  answer *= largest[1];

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
