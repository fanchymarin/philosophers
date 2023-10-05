# Philosophers - ⭐Grade 125/100

#### Grade rating
- ✅ = Okay project
- ⭐ = Outstanding project

This program simulates the dining philosophers problem, where a group of philosophers sit at a round table, alternately eating, thinking, or sleeping, while avoiding starvation and ensuring no two philosophers can eat simultaneously with the limited forks available. 
The program aims to provide a safe and synchronized dining philosophers simulation using threads and processes scenarios, while adhering to the specified rules.

## Mandatory Part

- Each philosopher is implemented as a thread.
- There is one fork between each pair of philosophers. A mutex protects the state of each fork to prevent duplication.
- The program takes the following arguments:
  - `number_of_philosophers`: Number of philosophers and forks.
  - `time_to_die` (in milliseconds): Maximum time since the last meal or simulation start before a philosopher dies.
  - `time_to_eat` (in milliseconds): Time it takes for a philosopher to eat, requiring two forks.
  - `time_to_sleep` (in milliseconds): Time a philosopher spends sleeping.
  - `[number_of_times_each_philosopher_must_eat]` (optional): If specified, the simulation stops when all philosophers have eaten at least this many times; otherwise, it stops when a philosopher dies.
- Each philosopher is assigned a number from 1 to `number_of_philosophers`.
- Output messages include:
  - `timestamp_in_ms X has taken a fork`
  - `timestamp_in_ms X is eating`
  - `timestamp_in_ms X is sleeping`
  - `timestamp_in_ms X is thinking`
  - `timestamp_in_ms X died`
- Philosophers' state messages are not mixed with others.
- A message announcing a philosopher's death is displayed 1 ms after the actual death.

## Bonus Part

- Each philosopher is implemented as a process.
- All forks are placed in the middle of the table and managed using semaphores.
- The main process does not participate as a philosopher, but as an orchestrator.


