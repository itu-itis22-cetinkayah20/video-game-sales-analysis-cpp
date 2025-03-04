

# Video Game Sales Analysis

## Overview

This project is designed to analyze video game sales data using different tree data structures. The project reads sales data from CSV files, processes it using Red-Black Trees (RBT) and Binary Search Trees (BST), and provides insights such as best-selling publishers in different regions. The goal is to efficiently handle and analyze video game sales data.

### Tree Data Structures Used

- **Red-Black Tree (RBT)**: A balanced binary search tree that ensures the tree remains balanced after insertions and deletions.
    - **Insertion**: Inserts nodes while maintaining the Red-Black Tree properties.
    - **Search**: Searches for nodes based on publisher names.
    - **Rotation**: Performs left and right rotations to maintain balance.

- **Binary Search Tree (BST)**: A binary tree where each node has at most two children, and the left child is less than the parent node, while the right child is greater.
    - **Insertion**: Inserts nodes based on publisher names.
    - **Search**: Searches for nodes based on publisher names.

## Features

- **Read Sales Data**: Read video game sales data from CSV files.
- **Create Nodes**: Create tree nodes from the data.
- **Analyze Data**: Analyze sales data to find best-selling publishers.
- **Error Handling**: Handle file reading errors gracefully.

---

## **Project Structure**

```
/video-game-sales-analysis-cpp/
│── analysis-BST/             # BST analysis project
│   │── bin/                  # Compiled binaries for BST
│   │── data/                 # CSV files with sales data for BST
│   │   │── VideoGames.csv    # Video game sales data
│   │── include/              # Header files for BST
│   │── src/                  # Source code for BST
│   │   │── solution_BST_tree.cpp # Binary Search Tree implementation
│── analysis-RBT/             # RBT analysis project
│   │── bin/                  # Compiled binaries for RBT
│   │── data/                 # CSV files with sales data for RBT
│   │   │── VideoGames.csv    # Video game sales data
│   │── include/              # Header files for RBT
│   │── src/                  # Source code for RBT
│   │   │── solution_RBT_tree.cpp # Red-Black Tree implementation
│── README.md                 # Documentation
```

---

## **Getting Started**

### **Prerequisites**

- **C++ Compiler**: Ensure you have a C++ compiler installed (e.g., g++, clang).
- **Docker**: Docker is not required for this project but it is better to use.

### **Installation**

1. **Clone the repository**
        - You can clone the repository using git or download it from Code, Download ZIP
```sh
git clone https://github.com/itu-itis22-cetinkayah20/video-game-sales-analysis-cpp.git
```

2. **Build the project**
```sh
cd video-game-sales-analysis-cpp/analysis-BST 
-----------------------------------------------
cd video-game-sales-analysis-cpp/analysis-RBT
-----------------------------------------------
g++ src/solution_BST_tree.cpp -o bin/solution_BST
-------------------------------------------------
g++ src/solution_RBT_tree.cpp -o bin/solution_RBT
```

### **Running the Application**
- The application will process the sales data and output the analysis results.
- You can activate the commented code blocks in `main.cpp` to observe the execution times of different tree operations.
```sh
./bin/solution_BST data/VideoGames.csv 
----------------------------------------
./bin/solution_RBT data/VideoGames.csv 
```

## **Technologies Used**

- **C++**: Core programming language for processing sales data.
- **CSV**: Format for input and output data files.

## **Usage**

- **Analyze Sales Data**: Run the application to analyze sales data from the CSV files.
- **Modify Data**: Update the CSV files with new sales data and re-run the application to see updated results.

---

## **Contributing**
Contributions are welcome! Please fork the repository and submit a pull request.

---

## **License**

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software, either in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this software dedicate any and all copyright interest in the software to the public domain. We make this dedication for the benefit of the public at large and to the detriment of our heirs and successors. We intend this dedication to be an overt act of relinquishment in perpetuity of all present and future rights to this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>
