# Philosophers

This is a simulation of a classic problem in computer science known as the Dining Philosophers problem. In this problem, a number of philosophers sit at a round table and alternate between thinking, eating, and sleeping. They share a bowl of spaghetti in the middle of the table, but there are only as many forks as there are philosophers, so they must take turns using the forks to eat.

![Philosophers-image](https://media.geeksforgeeks.org/wp-content/uploads/dining_philosopher_problem.png)

## Usage

Clone the repository and navigate to the project directory. Use the `make` command to compile the simulation program. To run the simulation, use the following command:
```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```
- number_of_philosophers: The number of philosophers and forks at the table.
- time_to_die: The maximum time in milliseconds a philosopher can go without eating before they die.
- time_to_eat: The time in milliseconds it takes a philosopher to eat.
- time_to_sleep: The time in milliseconds a philosopher spends sleeping.
- number_of_times_each_philosopher_must_eat (optional): The number of times each philosopher must eat before the simulation stops.

The program outputs messages describing the state of each philosopher at any given time, such as when they take a fork, start eating, start sleeping, or die. The messages are printed to the standard output, with each message prefixed by a timestamp in milliseconds.

Here is the sample input and output. Use this awesome [visualizer](https://nafuka11.github.io/philosophers-visualizer/) for better understanding of the simulation.

![philo-output](https://user-images.githubusercontent.com/73651474/231336218-b2e4a420-9582-4eff-b24a-89ceb7dae7e0.png)

## Implementation

This project has two parts: the mandatory part (philo) and the bonus part (philo_bonus).

### Mandatory Part

The mandatory part is implemented using threads and mutexes. Each philosopher is a separate thread, and there is one mutex for each fork to prevent the philosophers from duplicating forks.

### Bonus Part

The bonus part is implemented using processes and semaphores. All the forks are placed in the middle of the table and represented by a semaphore. Each philosopher is a separate process, and the main process is not a philosopher.

## Credit
This project was completed as part of the curriculum of the Ecole 42 program. The instructions for the project were provided by the school.
