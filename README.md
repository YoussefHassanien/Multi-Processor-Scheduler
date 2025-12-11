# Overview

## Multi-Processor Scheduler

## Overview

This project is a simulation of a multi-core processor scheduling system, designed to demonstrate and compare various CPU scheduling algorithms. It is implemented in C++ and provides a modular structure for experimenting with different scheduling strategies, including FCFS (First-Come-First-Serve), SJF (Shortest Job First), RR (Round Robin), and EDF (Earliest Deadline First). It also perform calculations related statistics such as load and utilization of each processor, the stolen processes, and the killed processes.

## Features

- **Multiple Scheduling Algorithms:** FCFS, SJF, RR, and EDF are implemented as separate modules.
- **Process and Processor Abstractions:** Encapsulates process and processor logic for extensibility.
- **Input/Output Handling:** Reads process/task data from input files and writes results to output files.
- **Data Structures:** Utilizes custom implementations of queues, linked lists, binary trees, and priority queues.
- **Simulation:** Simulates process scheduling, context switching, and processor management.
- **Extensible Design:** Easily add new scheduling algorithms or modify existing ones.

## File Structure

```
Data Structures Project/
├── BinaryTree.h         # Binary tree data structure
├── CyclicQueue.h        # Cyclic queue implementation
├── EDF.cpp/.h           # Earliest Deadline First scheduler
├── FCFS.cpp/.h          # First-Come-First-Serve scheduler
├── IO.cpp/.h            # Input/Output handling
├── LinkedList.h         # Linked list data structure
├── LinkedQueue.h        # Linked queue implementation
├── Node.h               # Node structure for lists/trees
├── PriorityNode.h       # Node for priority queue
├── PriorityQueue.h      # Priority queue implementation
├── Process.cpp/.h       # Process abstraction
├── Processor.cpp/.h     # Processor abstraction
├── RR.cpp/.h            # Round Robin scheduler
├── Scheduler.cpp/.h     # Scheduler core logic
├── SJF.cpp/.h           # Shortest Job First scheduler
├── SigKill.h            # Signal handling for process termination
├── TreeNode.h           # Tree node structure
├── UI_Info.cpp/.h       # User interface information
├── Source.cpp           # Main entry point
├── InputFile_*.txt      # Example input files
├── OutputFile.txt       # Output file
├── BigTestComboLarge.txt# Large test input
```

## Build Instructions

1. **Requirements:**
   - Windows OS
   - Visual Studio 2019 or later (with C++ support)
2. **Open the Solution:**
   - Open `Data Structures Project.sln` in Visual Studio.
3. **Build the Project:**
   - Select the desired configuration (Debug/Release, x64/x86).
   - Build the solution (Ctrl+Shift+B).
4. **Run the Program:**
   - Set `Source.cpp` as the startup file if needed.
   - Run (F5) or use the generated executable in `x64/Debug/` or `x64/Release/`.

## Usage

1. **Input Files:**
   - Place your process/task data in one of the `InputFile_*.txt` files or create your own.
   - The format should match the expected input as described in the code comments (see `IO.h` for details).
2. **Output:**
   - Results will be written to `OutputFile.txt` after simulation.
3. **Configuration:**
   - You can modify the scheduling algorithm or parameters by editing the relevant `.cpp`/`.h` files and rebuilding.

## Main Components

- **Scheduler:** Orchestrates the simulation and manages processors.
- **Processor:** Represents a CPU core, each running a scheduling algorithm.
- **Process:** Encapsulates process/task information.
- **Data Structures:** Custom implementations for queues, lists, and trees to support scheduling logic.

## Extending the Project

To add a new scheduling algorithm:

1. Create new `.cpp` and `.h` files for your algorithm (see `FCFS.cpp`/`.h` as a template).
2. Implement the required scheduling logic.
3. Register your scheduler in `Scheduler.cpp`.
4. Update the input/output handling if needed.

## Authors

- [Youssef Hassanien, Doha El Beltagy, Ayah Al Shahid, Chahd El Zalaki]

## License

This project is for educational purposes. Add a license if you intend to distribute or use it beyond personal/academic use.
