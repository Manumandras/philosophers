*This project has been created as part of the 42 curriculum by mmittelb.*

# philosophers

## Description

philosophers is an implementation of the classic Dining Philosophers problem in C, focused on concurrency, synchronization, and avoiding deadlocks and starvation.

This repository contains two independent implementations:

- `philo/` mandatory uses POSIX threads and mutexes. Each philosopher is a thread. Philosophers sit around a table and repeatedly take their left and right fork, eat, sleep, and think. Forks are individual mutexes and each fork mutex is shared between two neighboring philosophers.
- `philo_bonus/` bonus uses processes and POSIX semaphores. Each philosopher is a process. Forks are a shared pool in the middle of the table, implemented as one counting semaphore initialized to number_of_philosophers. Each eating phase consumes two semaphore units and releases them after eating.

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

Expected output:

- Every log line starts with a timestamp in milliseconds since program start.
- Format: `<ms_since_start> <id> <action>`.
- Printing is serialized to avoid interleaved output.

Optional debug tools.

```bash
valgrind --leak-check=full ./philo 5 800 200 200 2
valgrind --tool=helgrind ./philo 5 800 200 200 2
```

<br>

## Implementation overview

### `philo` mandatory

- One thread per philosopher.
- One mutex `pthread_mutex_t` per fork, shared by neighboring philosophers.
- Two monitor threads handle `death_flag` and `philos_satisfied_flag`.
- Optional fairness for odd counts using phased `permit` plus `done_eating` barrier.

### `philo_bonus` bonus

- One process per philosopher.
- Forks are a shared pool via one counting semaphore sem_t `forks`.
- Each child runs its own death monitor thread.
- Parent runs one fairness scheduler using per philosopher `permits` plus `done_eating` barrier.
- Parent reaps children and shuts down.

<br>

## Project structure

```text
.
├── philo/
│   ├── philo.c
│   ├── philo.h
│   ├── meals_and_death.c
│   ├── sceduler.c
│   └── ...
└── philo_bonus/
    ├── philo_bonus.c
    ├── philo_bonus.h
    ├── routine_bonus.c
    ├── sceduler_bonus.c
    ├── children_bonus.c
    └── ...
```

<br>

## Resources

## Resources

- **UNIX manual pages**, in particular:
  - `pthread_create`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`
  - `fork`, `waitpid`, `kill`
  - `sem_open`, `sem_close`, `sem_unlink`, `sem_wait`, `sem_post`


<br>

### Use of AI

AI tools were used as a **supporting resource** for:

- clarifying expected behavior and common pitfalls in the Dining Philosophers problem,
- discussing deadlock avoidance and fairness scheduling approaches,
- reviewing thread, process, mutex, and semaphore usage patterns,
- analyzing error paths and shutdown conditions,
- drafting and editing documentation.

All code was written and integrated by the project author.
