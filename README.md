# philosophers

_This project has been created as part of the 42 curriculum by molasz-a._

> Part of [42 Barcelona — molasz-a](https://github.com/Molasz/42), a monorepo centralizing every project completed at 42 Barcelona.

## Description

**philosophers** is a classic synchronization problem from the 42 curriculum that explores the concepts of threads, processes, mutexes, and semaphores. The project is based on the "Dining Philosophers problem," where a number of philosophers sit at a round table and alternate between thinking and eating.

The challenge is to implement a solution where philosophers can eat without causing deadlocks (where everyone is waiting for a fork and no one can eat) or starvation (where a philosopher is perpetually denied access to forks).

The project is divided into two parts:
- **Mandatory part (`philo`):** Solves the problem using threads and mutexes.
- **Bonus part (`philo_bonus`):** Solves the problem using processes and semaphores.

---

## The Problem

- A number of philosophers are sitting at a round table.
- There is one fork between each pair of philosophers.
- To eat, a philosopher must pick up both their left and right forks.
- Philosophers can be in one of three states: thinking, eating, or sleeping.

## Architecture

![Skills](https://skillicons.dev/icons?i=c,linux)

### Mandatory Part (`philo`)

The mandatory part uses **pthreads** (POSIX threads) to represent the philosophers and **mutexes** to protect the forks. Each philosopher is a thread, and each fork is a mutex. A monitoring thread is used to check for philosopher deaths.

```
philosophers.c  → Main logic, initialization.
threads.c       → Thread creation and management.
death.c         → Death monitoring logic.
forks.c         → Fork management (locking/unlocking mutexes).
utils.c         → Utility functions (time, printing state).
```

### Bonus Part (`philo_bonus`)

The bonus part uses **processes** (created with `fork()`) to represent the philosophers and **semaphores** for synchronization. The forks are represented by a semaphore, and additional semaphores are used for managing the print output and program termination.

```
philosophers.c  → Main logic, process creation.
process.c       → Process creation and management.
death.c         → Death monitoring and process termination.
forks.c         → Fork management (using semaphores).
utils.c         → Utility functions.
```

---

## ⚙️ Instructions

### Mandatory Part (`philo`)

```bash
# Navigate to the philo directory
cd philo

# Compile the project
make

# Run the simulation
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Bonus Part (`philo_bonus`)

```bash
# Navigate to the philo_bonus directory
cd philo_bonus

# Compile the project
make

# Run the simulation
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

---

_molasz-a · 42 Barcelona_
