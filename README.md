# Hot Reloading in C
Hot reloading: change behavior, no restart.

## How to Run

1. Compile the main program.
```bash
clang -Wall -Wextra -o main main.c
```

2. Run the program.
```bash
./main
```

3. While the progam is running.
- Modify the behavior of a function in `lib.c` (e.g., change an `add` function
  to perform `multiplication`).
- **Do not change the function signature while editing `lib.c`.(changing the
  return type won't cause an error but may result in unexpected behaviour)**
- Press `r` in the console where the program is running to reload the changes.
