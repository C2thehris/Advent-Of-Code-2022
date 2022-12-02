use std::{env, io};

fn part1(lines: &Vec<&str>)  {
    let answer: u64 = 0;
  
    println!("PART 1: {answer}");
}

fn part2(lines: &Vec<&str>) {
    let answer: u64 = 0;
  
    println!("PART 2: {answer}");
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 2
    {
        panic!("Invalid Usage. Usage: ./[binary] [input]");
    }
  
    let read_result: io::Result<String> = std::fs::read_to_string(&args[1]);
    let Ok(unwrapped): Result<String, io::Error> = read_result else { panic!("Error reading {}", args[1]) };
    let lines: Vec<&str> = FromIterator::from_iter(unwrapped.split('\n'));

    part1(&lines);
    part2(&lines);
}
