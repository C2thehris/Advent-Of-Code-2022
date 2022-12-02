use std::{env, io};

fn part1(lines: &Vec<&str>) {
    let mut answer: u64 = 0;
    for line in lines {
        let p1 = line.chars().nth(0).unwrap();
        let p2 = line.chars().nth(2).unwrap();
        answer += match p1 {
            'A' => match p2 {
                'X' => 4,
                'Y' => 8,
                'Z' => 3,
                _ => panic!(),
            },
            'B' => match p2 {
                'X' => 1,
                'Y' => 5,
                'Z' => 9,
                _ => panic!(),
            },
            'C' => match p2 {
                'X' => 7,
                'Y' => 2,
                'Z' => 6,
                _ => panic!(),
            },
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
        answer += match p1 {
            'A' => match p2 {
                'X' => 3,
                'Y' => 4,
                'Z' => 8,
                _ => panic!(),
            },
            'B' => match p2 {
                'X' => 1,
                'Y' => 5,
                'Z' => 9,
                _ => panic!(),
            },
            'C' => match p2 {
                'X' => 2,
                'Y' => 6,
                'Z' => 7,
                _ => panic!(),
            },
            _ => panic!(),
        };
    }

    println!("PART 1: {answer}");
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
