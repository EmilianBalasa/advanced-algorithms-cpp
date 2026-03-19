Exercise 1:

- Digital Combo Lock Solver

- What This Program Does
This program generates the shortest possible sequence of digits to guarantee that a digital combination lock will open,
no matter what the secret code is. For example, if the lock requires a 3-digit code, this program creates a sequence
where every possible 3-digit combination appears in order.

- How to Use It
1. Input: Run the program and enter two numbers:
   - n (the length of the secret code, e.g., 3)
   - k (the range of digits, e.g., 2 for digits 0-1)

   Example input: 3 2

2. Output: The program prints the shortest sequence. For n=2 and k=2, the output might be `00110`.

- Key Features
- Handles codes up to 4 digits and digit ranges up to 10.
- Uses a mathematical approach (de Bruijn graphs) to ensure efficiency.
- Works for edge cases like single-digit codes (e.g., n=1 outputs all digits).

- Example
Input:
2 2

Output:
00110

