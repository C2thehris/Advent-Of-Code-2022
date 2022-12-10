use std::{env, io};

fn part1(lines: &Vec<&str>) {
    let answer: u64 = 0;
    let mut i = 0;

    let lineLen = lines[0].len();
    let cratesLen = (lineLen / 4) + 1;
    let mut crates = Vec::new();
    crates.resize(cratesLen, Vec::<char>::new());
    loop {
        if lines[i] == "" {
            break;
        }
        let mut j = 0;
        let len = lines[i].len();
        for c in lines[i].chars() {
            if len == j {
                break;
            }
            if c.is_alphabetic() {
                crates[j / 4].push(c);
            }
            j += 1;
        }
        i += 1;
    }
    i += 1;

    crates.iter_mut().for_each(|p| p.reverse());

    loop {
        if lines[i].trim() == "" {
            break;
        }
        let mut it = lines[i].split(" ");
        let count = it.nth(1).unwrap().parse::<usize>().unwrap();
        let origin = it.nth(1).unwrap().parse::<usize>().unwrap() - 1;
        let dest = it.nth(1).unwrap().parse::<usize>().unwrap() - 1;

        let mut j = 0;
        loop {
            if j == count {
                break;
            }
            let from = match crates[origin].pop() {
                Some(val) => val,
                None => break,
            };
            crates[dest].push(from);
            j += 1;
        }
        i += 1;
    }

    let mut result = String::from("");
    for cr in crates {
        match cr.last() {
            Some(val) => result.push(*val),
            _ => (),
        }
    }

    println!("PART 1: {result}");
}

fn part2(lines: &Vec<&str>) {
    let mut i = 0;

    let lineLen = lines[0].len();
    let cratesLen = (lineLen / 4) + 1;
    let mut crates = Vec::new();
    crates.resize(cratesLen, Vec::<char>::new());
    loop {
        if lines[i] == "" {
            break;
        }
        let mut j = 0;
        let len = lines[i].len();
        for c in lines[i].chars() {
            if len == j {
                break;
            }
            if c.is_alphabetic() {
                crates[j / 4].push(c);
            }
            j += 1;
        }
        i += 1;
    }
    i += 1;

    crates.iter_mut().for_each(|p| p.reverse());

    loop {
        if lines[i].trim() == "" {
            break;
        }
        let mut it = lines[i].split(" ");
        let count = it.nth(1).unwrap().parse::<usize>().unwrap();
        let origin = it.nth(1).unwrap().parse::<usize>().unwrap() - 1;
        let dest = it.nth(1).unwrap().parse::<usize>().unwrap() - 1;

        let mut j = 0;
        let mut queue = vec![];
        loop {
            if j == count {
                break;
            }
            let from = match crates[origin].pop() {
                Some(val) => val,
                None => break,
            };
            queue.push(from);
            j += 1;
        }
        j = 0;
        loop {
            if j == count {
                break;
            }
            crates[dest].push(queue.pop().unwrap());
            j += 1;
        }

        i += 1;
    }

    let mut result = String::from("");
    for cr in crates {
        match cr.last() {
            Some(val) => result.push(*val),
            _ => (),
        }
    }

    println!("PART 2: {result}");
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 2 {
        panic!("Invalid Usage. Usage: ./[binary] [input]");
    }

    let read_result: io::Result<String> = std::fs::read_to_string(&args[1]);
    let Ok(unwrapped): Result<String, io::Error> = read_result else { panic!("Error reading {}", args[1]) };
    let lines: Vec<&str> = FromIterator::from_iter(unwrapped.split('\n'));

    part1(&lines);
    part2(&lines);
}
