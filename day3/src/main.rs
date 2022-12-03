use std::{collections::HashSet, env, io};

fn priority(c: char) -> u64 {
    if c.is_uppercase() {
        (c as u64) - ('A' as u64) + 27
    } else {
        (c as u64) - ('a' as u64) + 1
    }
}

fn find_common(line: String) -> char {
    let mut i: usize = 0;
    let mut set: HashSet<char> = HashSet::new();
    let mid = line.len() / 2;
    let mut it = line.chars();
    loop {
        if i == mid {
            break;
        }
        i += 1;
        set.insert(it.next().unwrap());
    }

    *set.intersection(&it.collect()).next().unwrap()
}

fn part1(lines: &Vec<&str>) {
    let mut answer: u64 = 0;
    for line in lines {
        answer += priority(find_common(line.to_string()));
    }

    println!("PART 1: {answer}");
}

fn part2(lines: &Vec<&str>) {
    let mut answer: u64 = 0;
    let mut i = 0;
    let mut set: HashSet<char> = HashSet::new();
    loop {
        if i == lines.len() {
            break;
        }
        if i % 3 == 0 {
            set = HashSet::from_iter(lines[i].chars());
        } else {
            let current = HashSet::from_iter(lines[i].chars());
            set = set.intersection(&current).copied().collect();

            if i % 3 == 2 {
                answer += priority(*set.iter().next().unwrap());
                set.clear();
            }
        }
        i += 1;
    }

    println!("PART 2: {answer}");
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
