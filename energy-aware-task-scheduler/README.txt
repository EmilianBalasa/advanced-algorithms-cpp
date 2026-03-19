- Energy-Efficient Task Scheduler

- What This Program Does
This program schedules tasks with dependencies and deadlines across multiple processor cores. Its goal is to minimize total energy consumption, while making sure all tasks are completed before their deadlines.
It detects strongly connected components (SCCs) in the task graph and handles parallel execution for tasks in cycles when possible.

- How to Use It
Prepare an input.txt file containing:

Task definitions (ID, workload, deadline).

Dependency pairs (task A must finish before task B).

Processor cores (speed and power).

It reads from input.txt.

It writes the result in output.txt.

- Key Features
Detects dependency cycles using Kosaraju’s algorithm.

Validates if a cycle can be scheduled on available cores.

Minimizes energy usage with best core-task assignment.

Prints the task schedule with timings and energy, or a failure reason.

- Example input.txt

4
1 100 3.0
2 400 4.0
3 100 6.0
4 200 7.0
3
1 2
1 3
2 4
2
50 10
200 100

- Example output.txt

--- Scheduling Results ---
Scheduele Table:
TaskID | CoreID | StartTime | EndTime | Energy
1 | 1 | 0.00 | 0.50 | 50.00
3 | 0 | 0.50 | 2.50 | 20.00
2 | 1 | 0.50 | 2.50 | 200.00
4 | 0 | 2.50 | 6.50 | 40.00
Minimum Total Energy Consumed: 310.00