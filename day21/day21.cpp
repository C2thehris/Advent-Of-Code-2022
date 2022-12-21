#include <bits/stdc++.h>

using namespace std;

typedef unordered_map<string, vector<string>> operation_map;
typedef unordered_map<string, set<string>> dependency_map;

operation_map parseInput(vector<string> &lines)
{
  operation_map ret;
  for (const auto &line : lines)
  {
    int colon = line.find(':');
    string monkey = line.substr(0, colon);
    string op = line.substr(colon + 2);
    int space = op.find(' ');
    if (space == -1)
    {
      ret[monkey] = {op};
    }
    else
    {
      string firstTarget = op.substr(0, space);
      string operation = string{op[space + 1]};
      string secondTarget = op.substr(space + 3);
      ret[monkey] = {firstTarget, operation, secondTarget};
    }
  }
  return ret;
}

dependency_map calculateDependencies(const operation_map &ops)
{
  dependency_map ret;
  for (const auto &[monkey, operation] : ops)
  {
    string target = monkey;
    ret[target];
    if (operation.size() > 1)
    {
      ret[operation[0]].insert(target);
      ret[operation[2]].insert(target);
    }
  }
  return ret;
}

long long computeOperation(long long leftOperand, char op, long long rightOperand)
{
  switch (op)
  {
  case '+':
    return leftOperand + rightOperand;
  case '-':
    return leftOperand - rightOperand;
  case '*':
    return leftOperand * rightOperand;
  case '/':
    return leftOperand / rightOperand;
  default:
    throw new logic_error("");
  }
}

void tryOperation(unordered_map<string, long long> &results, const dependency_map &dependencies, const operation_map &operations, string monkey, const vector<string> &operation)
{
  if (operation.size() == 1)
  {
    results[monkey] = stoi(operation[0]);
  }
  else
  {
    auto first_it = results.find(operation[0]);
    auto second_it = results.find(operation[2]);
    if (first_it != results.end() && second_it != results.end())
    {
      results[monkey] = computeOperation(first_it->second, operation[1][0], second_it->second);
    }
  }
  if (results.find(monkey) != results.end())
  {
    for (const auto &dependent : dependencies.at(monkey))
      tryOperation(results, dependencies, operations, dependent, operations.at(dependent));
  }
}

void part1(vector<string> &lines)
{
  long long answer = 0;
  auto monkeyOperations = parseInput(lines);
  auto dependencies = calculateDependencies(monkeyOperations);
  unordered_map<string, long long> results;
  for (const auto &[monkey, operation] : monkeyOperations)
    tryOperation(results, dependencies, monkeyOperations, monkey, operation);

  answer = results["root"];
  cout << "PART 1: " << answer << endl;
}

long long computeMissing(long long result, long long rValue, const vector<string> &operation, bool left)
{
  if (left)
  {
    switch (operation[1][0])
    {
    case '+':
      return result - rValue;
    case '-':
      return -1 * (result - rValue);
    case '*':
      return result / rValue;
    case '/':
      return rValue / result;
    };
  }
  else
  {
    switch (operation[1][0])
    {
    case '+':
      return result - rValue;
    case '-':
      return result + rValue;
    case '*':
      return result / rValue;
    case '/':
      return result * rValue;
    };
  }
  throw new logic_error("");
}

long long fill_missing(const operation_map &monkeyOperations, unordered_map<string, long long> &results, string root)
{
  string present_op, missing_op;
  auto root_it = results.find(monkeyOperations.at(root)[0]);
  bool left;
  if (root_it == results.end())
  {
    left = false;
    present_op = monkeyOperations.at(root)[2];
    missing_op = monkeyOperations.at(root)[0];
  }
  else
  {
    left = true;
    present_op = monkeyOperations.at(root)[0];
    missing_op = monkeyOperations.at(root)[2];
  }
  results[missing_op] = computeMissing(results[root], results[present_op], monkeyOperations.at(root), left);

  if (missing_op == "humn")
  {
    return results[missing_op];
  }
  return fill_missing(monkeyOperations, results, missing_op);
}

void part2(vector<string> &lines)
{
  unsigned long long answer = 0;
  auto monkeyOperations = parseInput(lines);
  monkeyOperations.erase("humn");
  auto dependencies = calculateDependencies(monkeyOperations);

  unordered_map<string, long long> results;
  for (const auto &[monkey, operation] : monkeyOperations)
    tryOperation(results, dependencies, monkeyOperations, monkey, operation);

  string present_op, missing_op;

  auto root_it = results.find(monkeyOperations["root"][0]);
  if (root_it == results.end())
  {
    present_op = monkeyOperations["root"][2];
    missing_op = monkeyOperations["root"][0];
  }
  else
  {
    present_op = monkeyOperations["root"][0];
    missing_op = monkeyOperations["root"][2];
  }
  results[missing_op] = results[present_op];
  answer = fill_missing(monkeyOperations, results, missing_op);

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
