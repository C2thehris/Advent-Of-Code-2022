#include <bits/stdc++.h>

using namespace std;

enum Material
{
  ORE = 0,
  CLAY = 1,
  OBSIDIAN = 2,
  GEODE = 3
};

// namespace Material
// {
//   const int ORE = 0;
//   const int CLAY = 1;
//   const int OBSIDIAN = 2;
//   const int GEODE = 3;
// };

typedef vector<unordered_map<Material, int>> Blueprint;

int findDigit(const string &line, int begin)
{
  for (int i = begin; i < line.size(); ++i)
  {
    if (line[i] >= '0' && line[i] <= '9')
      return i;
  }
  return -1;
}

vector<Blueprint> parseInput(const vector<string> &lines)
{
  vector<Blueprint> blueprints;
  for (const string &line : lines)
  {
    int colon = line.find(':');
    int begin = findDigit(line, colon);
    int end = line.find(' ', begin);
    int oreRobotOreCount = stoi(line.substr(begin, end - begin));
    begin = findDigit(line, end);
    end = line.find(' ', begin);
    int clayRobotOreCount = stoi(line.substr(begin, end - begin));
    begin = findDigit(line, end);
    end = line.find(' ', begin);
    int obsidianRobotOreCount = stoi(line.substr(begin, end - begin));
    begin = findDigit(line, end);
    end = line.find(' ', begin);
    int obsidianRobotClayCount = stoi(line.substr(begin, end - begin));
    begin = findDigit(line, end);
    end = line.find(' ', begin);
    int geodeRobotOreCount = stoi(line.substr(begin, end - begin));
    begin = findDigit(line, end);
    end = line.find(' ', begin);
    int geodeRobotObsidianCount = stoi(line.substr(begin, end - begin));
    Blueprint current(4);
    current[0][Material::ORE] = oreRobotOreCount;
    current[0][Material::CLAY] = 0;
    current[0][Material::OBSIDIAN] = 0;
    current[1][Material::ORE] = clayRobotOreCount;
    current[1][Material::CLAY] = 0;
    current[1][Material::OBSIDIAN] = 0;
    current[2][Material::ORE] = obsidianRobotOreCount;
    current[2][Material::CLAY] = obsidianRobotClayCount;
    current[2][Material::OBSIDIAN] = 0;
    current[3][Material::ORE] = geodeRobotOreCount;
    current[3][Material::CLAY] = 0;
    current[3][Material::OBSIDIAN] = geodeRobotObsidianCount;

    blueprints.push_back(current);
  }
  return blueprints;
}

string getState(int oreCount, int clayCount, int obsidianCount, int oreRobot,
                int clayRobot, int obsidianRobot, int time)
{
  stringstream s;
  s << oreCount << ", " << clayCount << ", " << obsidianCount << ", "
    << oreRobot << ", " << clayRobot << ", " << obsidianRobot << ", "
    << time;
  return s.str();
}

bool craftable(array<int, 3> resources,
               const unordered_map<Material, int> &required)
{
  int required_ore = required.at(Material::ORE);
  if (required_ore != 0 && resources[0] < required_ore)
  {
    return false;
  }
  int required_clay = required.at(Material::CLAY);
  if (required_clay != 0 && resources[1] < required_clay)
  {
    return false;
  }
  int required_obsidian = required.at(Material::OBSIDIAN);
  if (required_obsidian != 0 && resources[2] < required_obsidian)
  {
    return false;
  }

  return true;
}

array<int, 3> craft(const array<int, 3> &initial, const unordered_map<Material, int> &recipe)
{
  return {initial[0] - recipe.at(Material::ORE), initial[1] - recipe.at(Material::CLAY), initial[2] - recipe.at(Material::OBSIDIAN)};
}

long long solve(unordered_map<string, int> &memos, const Blueprint &blueprint, const array<int, 3> &limits,
                array<int, 3> resources, int oreRobot,
                int clayRobot, int obsidianRobot, int time)
{
  if (time == 0)
  {
    return 0;
  }
  const string state = getState(resources[0], resources[1], resources[2], oreRobot, clayRobot, obsidianRobot, time);
  auto it = memos.find(state);
  if (it != memos.end())
  {
    return it->second;
  }

  long long best = 0;
  if (oreRobot < limits[0] && craftable(resources, blueprint[0]))
  {
    auto afterCraft = craft(resources, blueprint[0]);
    afterCraft[0] += oreRobot;
    afterCraft[1] += clayRobot;
    afterCraft[2] += obsidianRobot;
    best = max(best, solve(memos, blueprint, limits, afterCraft, oreRobot + 1, clayRobot, obsidianRobot, time - 1));
  }
  if (clayRobot < limits[1] && craftable(resources, blueprint[1]))
  {
    auto afterCraft = craft(resources, blueprint[1]);
    afterCraft[0] += oreRobot;
    afterCraft[1] += clayRobot;
    afterCraft[2] += obsidianRobot;
    best = max(best, solve(memos, blueprint, limits, afterCraft, oreRobot, clayRobot + 1, obsidianRobot, time - 1));
  }
  if (obsidianRobot < limits[2] && craftable(resources, blueprint[2]))
  {
    auto afterCraft = craft(resources, blueprint[2]);
    afterCraft[0] += oreRobot;
    afterCraft[1] += clayRobot;
    afterCraft[2] += obsidianRobot;
    best = max(best, solve(memos, blueprint, limits, afterCraft, oreRobot, clayRobot, obsidianRobot + 1, time - 1));
  }
  if (craftable(resources, blueprint[3]))
  {
    auto afterCraft = craft(resources, blueprint[3]);
    afterCraft[0] += oreRobot;
    afterCraft[1] += clayRobot;
    afterCraft[2] += obsidianRobot;
    best = max(best, solve(memos, blueprint, limits, afterCraft, oreRobot, clayRobot, obsidianRobot, time - 1) + time - 1);
  }
  resources[0] += oreRobot;
  resources[1] += clayRobot;
  resources[2] += obsidianRobot;
  best = max(best, solve(memos, blueprint, limits, resources, oreRobot, clayRobot, obsidianRobot, time - 1));

  memos[state] = best;
  return best;
}

void part1(vector<string> &lines)
{
  long long answer = 0;
  auto blueprints = parseInput(lines);
  long long i = 1;
  for (const auto &blueprint : blueprints)
  {
    unordered_map<string, int> memos;
    array<int, 3> limits = {};
    for (int i = 0; i < 4; ++i)
    {
      limits[0] = max(limits[0], blueprint[i].at(Material::ORE));
      limits[1] = max(limits[1], blueprint[i].at(Material::CLAY));
      limits[2] = max(limits[2], blueprint[i].at(Material::OBSIDIAN));
    }

    answer += solve(memos, blueprint, limits, {0, 0, 0}, 1, 0, 0, 24) * i;
    ++i;
  }

  cout << "PART 1: " << answer << endl;
}

void part2(vector<string> &lines)
{
  long long answer = 1;
  auto blueprints = parseInput(lines);
  long long i = 1;
  for (const auto &blueprint : blueprints)
  {
    cerr << to_string(i) << '\r';
    if (i > 3)
      break;
    unordered_map<string, int> memos;
    array<int, 3> limits = {};
    for (int i = 0; i < 4; ++i)
    {
      limits[0] = max(limits[0], blueprint[i].at(Material::ORE));
      limits[1] = max(limits[1], blueprint[i].at(Material::CLAY));
      limits[2] = max(limits[2], blueprint[i].at(Material::OBSIDIAN));
    }

    answer *= solve(memos, blueprint, limits, {0, 0, 0}, 1, 0, 0, 32);
    ++i;
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
