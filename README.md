*This project has been created as part of the 42 curriculum by mmittelb.*

# philosophers

## Description

philosophers is an implementation of the classic Dining Philosophers problem in C, focused on concurrency, synchronization, fairness, and avoiding deadlocks and starvation.

This repository contains three implementations:

- `philo/` mandatory uses POSIX threads and mutexes. Each philosopher is a thread. Philosophers sit around a table and repeatedly take their left and right fork, eat, sleep, and think. Forks are individual mutexes and each fork mutex is shared between two neighboring philosophers.
- `philo_bonus/` uses processes and POSIX semaphores. Each philosopher runs in its own process. Forks are represented as a shared pool, implemented with a counting semaphore initialized to the number of philosophers. To eat, a philosopher acquires two semaphore units and releases them again after eating.
- `philo_check_neighbours/` is an alternative thread-based version where philosophers check their direct neighbors before trying to eat. Instead of relying on a dedicated scheduler, each philosopher decides locally whether it is allowed to continue. This creates a decentralized fairness mechanism.

<br>

## Platform support

This project is developed for Unix-like systems, primarily Linux. It relies on POSIX APIs, standard Unix system calls, and a Makefile-based build system, so it is generally not intended to run natively on Windows without adaptation. On Windows, the recommended way to build and run it is through WSL.

<br>

## Instructions

### Build

Mandatory version.

```bash
cd philo
make
```

Bonus version.

```bash
cd philo_bonus
make
```

Neighbour-check version.

```bash
cd philo_check_neighbours
make
```

### Run

Arguments.

- `number_of_philosophers`
- `time_to_die` in ms
- `time_to_eat` in ms
- `time_to_sleep` in ms
- optional `number_of_meals`

Mandatory example:

```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
```

Bonus example:

```bash
./philo_bonus 5 800 200 200
./philo_bonus 5 800 200 200 7
```

Neighbour-check example:

```bash
./philo_check_neighbours 5 800 200 200
./philo_check_neighbours 5 800 200 200 7
```

Expected output:

- Every log line starts with a timestamp in milliseconds since program start.
- Format: `<ms_since_start> <id> <action>`.
- Actions include taking forks, eating, sleeping, thinking, and death detection.
- Output is serialized to avoid interleaved prints.


Optional debug tools:

```bash
valgrind --leak-check=full ./philo 5 800 200 200 2
valgrind --tool=helgrind ./philo 5 800 200 200 2
```

Note: Valgrind support is generally limited to Linux. On macOS, use other debugging or leak-checking tools if needed.

<br>

## Implementation overview

### `philo` mandatory

- One thread per philosopher.
- One `pthread_mutex_t` per fork, shared by neighboring philosophers.
- Two monitor threads handle death detection and optional meal completion.
- Fairness is coordinated by a third monitor thread using scheduler logic.

### `philo_bonus` bonus

- One process per philosopher.
- Forks are a shared pool via one counting semaphore `forks`.
- Each child runs its own death monitor thread.
- The parent process coordinates fairness through a third monitor thread and handles shutdown.

### `philo_check_neighbours`

- Same overall implementation as the mandatory version, except for the fairness logic.
- There is no separate scheduler deciding turns.
- Instead, each philosopher checks the meal counters of the left and right neighbors before eating.
- A philosopher may proceed only if both neighbors have eaten at least as many times.

<br>

## Project structure

```text
.
├── philo/
│   ├── philo.c
│   ├── philo.h
│   ├── monitors.c
│   ├── scheduler.c
│   └── ...
├── philo_bonus/
│   ├── philo_bonus.c
│   ├── philo_bonus.h
│   ├── routine_bonus.c
│   ├── scheduler_bonus.c
│   ├── children_bonus.c
│   └── ...
└── philo_check_neighbours/
    ├── Makefile
    ├── philo.c
    ├── philo.h
    ├── routine.c
    ├── forks.c
    ├── monitors.c
    └── ...
```

Executable names:

- `philo`
- `philo_bonus`
- `philo_check_neighbours`

<br>

## Resources

- **UNIX manual pages**, in particular:
  - `pthread_create`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`
  - `fork`, `waitpid`, `kill`
  - `sem_open`, `sem_close`, `sem_unlink`, `sem_wait`, `sem_post`

<br>

## Visualizer

For a visual demonstration of the Dining Philosophers problem, see the [Philosophers Visualizer](https://nafuka11.github.io/philosophers-visualizer/).

You can use it with this project by copying and pasting the program output into the visualizer.
This makes it easier to follow the execution flow and observe philosopher behavior.