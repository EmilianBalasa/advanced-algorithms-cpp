Exercise 2:

- Castle Defense Planner

## What This Program Does
This program calculates the minimum number of dragons Daenerys needs to station in a hierarchical city structure (modeled as a binary tree) to protect all cities. A dragon in a city protects itself, its parent, and its immediate children.

- How to Use It
1. Input: Provide the tree structure as a string. Use:
   - 0 for a city without a dragon.
   - null for missing nodes.

   Example input: [0,0,null,0,0]

2. Output: The program prints the number of dragons required. For the example above, the output is `1`.

- Key Features
- Parses complex tree structures from a string input.
- Uses a post-order traversal to optimize dragon placement.
- Handles empty trees and edge cases gracefully.

- Example
Input:
[0,0,null,0,0]

Output:
1


- Example
Input:
[0,0,null,0,null,0,null,null,0]

Output:
2