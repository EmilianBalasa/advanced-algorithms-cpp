# Advanced Algorithmic Engines in C++

## Overview
A repository containing three advanced algorithmic solutions developed in C++. These engines solve complex optimization, scheduling, and graph-based problems using custom data structures, tree traversals, and state-space exploration techniques.

## Modules Included

### 1. Energy-Aware Task Scheduler (energy-aware-task-scheduler)
A core scheduling engine that assigns dependent computational tasks across heterogeneous processing cores.
* **Goal:** Minimize total energy consumption while meeting strict execution deadlines.
* **Under the hood:** Models tasks using Directed Acyclic Graphs (DAGs). Implements cycle detection algorithms to resolve direct mutual dependencies and utilizes state-space search to find the optimal execution path.

### 2. Hierarchical Node Coverage Optimizer (tree-coverage-optimizer)
An algorithm designed to find the minimum dominating set in a hierarchical structure.
* **Goal:** Ensure every node in the hierarchy is either directly covered or adjacent to a covered node using the minimum number of resources.
* **Under the hood:** Utilizes recursive tree traversal and dynamic programming concepts to evaluate node states and optimize resource placement.

### 3. Universal Sequence Generator (universal-sequence-generator)
An algorithm that generates the shortest possible universal string containing all possible combinations of a given length and character set.
* **Goal:** Brute-force optimization by generating a sliding-window sequence.
* **Under the hood:** Uses graph theory (Eulerian paths on directed graphs) and stack-based iterative traversals to construct the most memory-efficient output sequence.

## Technical Highlights
* **Language:** C++
* **Concepts:** Graph Theory, DAGs, Minimum Dominating Sets, State-Space Exploration, Cycle Detection.
