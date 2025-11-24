# OS_Assignment_Banker

**What**
- C++ implementation of the Banker's algorithm. Checks for safe state. If in safe state, prints safe sequence

**Where**
- Source: `bankers/bankers.cpp`
- Sample input: `bankers/input.txt`

Build and run
```bash
g++ bankers/bankers.cpp
```
- Run the program (it reads `bankers/input.txt` by default):
```bash
./a.out
```

Input format
- rows for matrix placed in curly brackets with values separated by commas. Parser looks for keyword in line (e.g. "allocation"). available is just vector no rows. Example `bankers/input.txt`:
```
allocation: {0,1,0}{2,0,0}{3,0,2}{2,2,1}{0,0,2}
max: {7,5,3}{3,3,2}{9,0,2}{2,2,2}{4,3,3}
available: {3,2,2}
```

Behavior / output
- Parses `allocation`, `max`, and `available`, computes Need = Max - Allocation, and runs the Banker's safety algorithm.
- Prints whether the system is in a safe state or not. If so, a safe sequence of processes is printed (e.g. `P1 -> P3 -> P0`).
- Example with given input from assignment showed below

![Snapshot](Bankers_SS.png)

---
