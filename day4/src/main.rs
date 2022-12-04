use std::{env, io};

fn parse(s: &str) -> (u32, u32) {
    let mut split = s.split('-');

    let left = split.next().unwrap().parse::<u32>().unwrap();
    let right = split.next().unwrap().parse::<u32>().unwrap();
    return (left, right);
}

fn part1(lines: &Vec<&str>) {
    let mut answer: u64 = 0;
    for line in lines {
        let mut split = line.split(",");
        let left = parse(&split.next().unwrap());
        let right = parse(&split.next().unwrap());
        if left.0 <= right.0 && left.1 >= right.1 || right.0 <= left.0 && right.1 >= left.1 {
            answer += 1;
        }
    }

    println!("PART 1: {answer}");
}

fn part2(lines: &Vec<&str>) {
    let mut answer: u64 = 0;
    for line in lines {
        let mut split = line.split(",");
        let left = parse(&split.next().unwrap());
        let right = parse(&split.next().unwrap());
        if left.0 <= right.0 && left.1 >= right.0 || right.0 <= left.0 && right.1 >= left.0 {
            answer += 1;
        }
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
