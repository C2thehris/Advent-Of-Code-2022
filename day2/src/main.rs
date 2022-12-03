use std::{env, io};

fn part1(lines: &Vec<&str>) {
    let mut answer: u64 = 0;
    for line in lines {
        let p1 = line.chars().nth(0).unwrap();
        let p2 = line.chars().nth(2).unwrap();
        answer += match (p1, p2) {
            ('A', 'X') => 4,
            ('A', 'Y') => 8,
            ('A', 'Z') => 3,
            ('B', 'X') => 1,
            ('B', 'Y') => 5,
            ('B', 'Z') => 9,
            ('C', 'X') => 7,
            ('C', 'Y') => 2,
            ('C', 'Z') => 6,
            _ => panic!(),
        };
    }

    println!("PART 1: {answer}");
}

fn part2(lines: &Vec<&str>) {
    let mut answer: u64 = 0;
    for line in lines {
        let p1 = line.chars().nth(0).unwrap();
        let p2 = line.chars().nth(2).unwrap();
        answer += match (p1, p2) {
            ('A', 'X') => 3,
            ('A', 'Y') => 4,
            ('A', 'Z') => 8,
            ('B', 'X') => 1,
            ('B', 'Y') => 5,
            ('B', 'Z') => 9,
            ('C', 'X') => 2,
            ('C', 'Y') => 6,
            ('C', 'Z') => 7,
            _ => panic!(),
        };
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
