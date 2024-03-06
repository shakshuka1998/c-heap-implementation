# D-Ary Heap Implementation

## Introduction
This repository contains a C program for the implementation of a d-ary heap. A d-ary heap is a generalized version of a binary heap with 'd' children for each node, providing a flexible trade-off between the height of the tree and the number of children per node. This project was created for educational purposes as part of the data structures coursework at the Open University of Israel.

## Features
- **Dynamic 'd' value**: Users can specify the value of 'd' to determine the number of children per node in the heap.
- **Preloaded arrays**: The program includes 10 predefined arrays from which the heap can be built.
- **User interaction**: A simple CLI interface prompts the user to build heaps from the selected array and perform various heap operations.

## How to Use
1. **Set the 'd' value**: Upon starting the program, the user is prompted to enter the value for 'd'.
2. **Select an array**: The user is then asked to pick one of the 10 preloaded arrays to construct the heap.
3. **Build the heap**: The selected array is used to build the initial d-ary heap.
4. **Perform operations**: The user can then choose to perform the following actions on the heap:
   - `Insert key`: Add a new element to the heap.
   - `Increase key`: Increase the value of an element in the heap.
   - `Delete key`: Remove an element from the heap.
   - `Extract max`: Find and remove the maximum value from the heap.
   - `Exit`: Terminate the program.
5. **Repeat actions**: Except for 'Exit', after performing any action, the user will be prompted again to choose another action from the list.

## Getting Started
To run this program:
1. Clone the repository to your local machine.
2. Create a file that contains max 10 arrays (an array is numbers separated by a spaces)
3. Compile the C code using your preferred compiler. For example:
   gcc -o d-ary-heap main.c
4. Run the compiled executable:
   ./d-ary-heap

## Contributing
We welcome contributions from students and educators. Please feel free to fork this repository, make changes, and submit a pull request.

