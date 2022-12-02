use std::{env, io};

fn part1(lines: &Vec<&str>) {
    let mut answer: u64 = 0;
    let mut current: u64 = 0;
    for line in lines {
        let string_line: String = line.to_string();
        if string_line.eq("") {
            answer = std::cmp::max(answer, current);
            current = 0;
        } else {
            current += string_line.parse::<u64>().unwrap();
        }
    }
    answer = std::cmp::max(answer, current);

    println!("PART 1: {answer}");
}

fn part2(lines: &Vec<&str>) {
    let mut current: u64 = 0;
    let mut largest: Vec<u64> = vec![0, 0, 0];
    for line in lines {
        if (*line).eq("") {
            if current > largest[0] {
                largest[0] = current;
                largest.sort();
            }
            current = 0;
        } else {
            current += line.parse::<u64>().unwrap();
        }
    }
    if current > largest[0] {
        largest[0] = current;
    }

    let answer: u64 = largest[0] + largest[1] + largest[2];
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
