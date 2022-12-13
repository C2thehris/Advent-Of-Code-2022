const ordered = function (lhs, rhs) {
  let lhsNum = false;
  if (Number.isInteger(lhs)) {
    lhsNum = true;
  }
  let rhsNum = false;
  if (Number.isInteger(rhs)) {
    rhsNum = true;
  }
  if (lhsNum && rhsNum) {
    return lhs - rhs;
  }
  if (lhsNum) {
    lhs = [lhs];
  }
  if (rhsNum) {
    rhs = [rhs];
  }

  for (let i = 0; i < lhs.length; ++i) {
    if (i >= rhs.length) {
      return 1;
    }
    const res = ordered(lhs[i], rhs[i]);
    if (res !== 0) {
      return res;
    }
  }
  if (lhs.length < rhs.length) {
    return -1;
  }
  return 0;
};

function part1 (lines) {
  let ans = 0;
  const asData = lines.map((line) => {
    if (line === '') {
      return '';
    }
    return JSON.parse(line);
  });

  let pair = 1;
  for (let i = 0; i < asData.length; i += 3) {
    if (ordered(asData[i], asData[i + 1]) < 0) {
      ans += pair;
    }
    ++pair;
  }

  console.log(`Part 1: ${ans}`);
}

function part2 (lines) {
  let ans = 1;
  const asData = lines.filter((line) => line !== '').map((line) => {
    if (line === '') {
      return '';
    }
    return JSON.parse(line);
  });
  asData.push([[2]], [[6]]);
  asData.sort(ordered);

  asData.forEach((row, i) => {
    if (row.length === 1 && Array.isArray(row[0]) && row[0].length === 1 && (row[0][0] === 2 || row[0][0] === 6)) {
      ans *= (i + 1);
    }
  });

  console.log(`Part 2: ${ans}`);
}

const fs = require('fs');

if (process.argv.length < 3) {
  console.error('Invalid Usage.\nUsage: node template.js [input file]');
  process.exit(1);
}

fs.readFile(process.argv[2], 'ascii', (err, data) => {
  if (err) throw err;
  part1(data.split('\n'));
  part2(data.split('\n'));
});
