# Project README

This README provides an overview of the project structure and execution process. The project is organized into different folders, each serving a specific purpose.

## Folder Structure:

### 1. instances
This folder contains CSV files representing the temporal complexity of each algorithm. The "ALL" suffix indicates results when all algorithms operate on the same graph. Additionally, this directory contains input and output files for instances.

### 2. report
The "report" folder contains the PDF document detailing the project report.

### 3. src
The "src" folder is crucial for project execution, housing the main program file and essential function libraries.

### a. exact - constructive - local_search - tabu_search
These folders contain the source code for each of the algorithms. 

#### b. model
The "model" folder contains functions used for each of the exact, constructive, local, and tabu search methods.

#### c. main.cpp
This file is the main executable that runs various algorithms found in different folders. 

To customize the execution, refer to the `#define` statements from line 10 to 25. To choose a specific algorithm (Exact, Constructive, Local, Tabu, or All), uncomment the corresponding line under the "algorithm choice" section. 

To enable input and/or output file creation, uncomment the relevant `#define` statements (note: creating many files is resource-intensive; use caution).


## Execution Parameters (main.cpp, lines 35-40):

1. `N_base`: Choose the number of vertices to start the iteration.
2. `maxIterations`: Define the end point of the iteration.
3. `probEdges`: Set the probability of creating an edge between two vertices.
4. `step`: Determine the increment for the vertex count at each iteration.

## Running the Program:

1. Open `main.cpp`.
2. Adjust the `#define` statements based on your preferences (algorithm choice, file creation).
3. Set the execution parameters (N_base, maxIterations, probEdges, step) in the specified section (lines 35-40).
4. Save the changes.
5. Compile and run the program.

Note: Exercise caution when enabling file creation, especially for input and output files, it will create many files.