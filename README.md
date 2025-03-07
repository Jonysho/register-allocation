# Graph Coloring Algorithm

## Overview
This program implements a **graph coloring algorithm** to assign colors to nodes in an interference graph, minimizing color conflicts between connected nodes. Nodes are ranked by the number of neighbors (descending), with ties broken by node ID.

## Features
- Reads an interference graph from an input file.
- Orders nodes by neighbor count (descending), then by node ID.
- Assigns colors (A-Z) to nodes, ensuring no connected nodes share the same color.
- Outputs color assignments to a file.
- Handles errors for invalid inputs and file operations.

## Input Format
The input file should list nodes and their interferences in the following format:
```
1,2,3
2,1,4
3,1,5
4,2
5,3
```

- Each line represents a node followed by its interfering nodes, separated by commas.
- **Constraints**:
  - Nodes must be **positive integers**.
  - Maximum of **50 nodes**.
  - At least **one interference**.
  - Only digits, commas, and newlines are allowed.

## Output Format
The output file lists nodes with assigned colors in ascending order:
```
1A
2B
3C
4A
5B
```
- Each line contains a node number followed by its assigned color.

## Usage
### Compilation
```sh
g++ -std=c++11 -o main main.cpp
Execution

./main <input_file> <output_file>

Example
./main input.txt output.txt
```
Error Handling
Displays an error message and exits if:

The input file contains invalid characters.

There are issues opening the input/output file.

The algorithm fails to assign a color.

Example Walkthrough
Input (input.txt)

```
1,2,3
2,1,4
3,1,5
4,2
5,3
```
Output (output.txt)
```
1A
2B
3C
4A
5B
```
