# 🍽️ DiningPhilosophers-IPC-Mutex

A C++ simulation of the classic **Dining Philosophers Problem** implemented across multiple **Windows Processes** using **Named Mutexes** for inter-process synchronization.

## Project Structure

The project consists of two distinct programs:

1.  **`HostCoordinator.cpp` (The Host/Coordinator):** Responsible for creating the shared Mutex resources and launching the individual philosopher processes.
2.  **`PhilosopherProcess.cppp` (The Philosopher):** The logic for a single philosopher. Five instances of the compiled philosopher code are run concurrently.

## Execution Flow

1.  **Resource Initialization:** The Host process creates 5 named Mutexes: `"String 0"` through `"String 4"`. These names serve as identifiers for the shared "chopsticks."
2.  **Process Launch:** The Host process launches 5 child processes (instances of the Philosopher executable), passing a unique ID (1 to 5) as a command-line argument to each.
3.  **Philosopher Logic:** Each Philosopher process attempts to "eat" 1,000,000 times by acquiring the two necessary chopsticks (Mutexes) identified by their ID.
4.  **Synchronization:** Windows Named Mutexes (`CreateMutexA` with a name) are used, allowing multiple, unrelated processes to reference and synchronize access to the same shared resource handles.
5.  **Completion:** The Host waits for all 5 Philosopher processes to terminate, and the Philosopher processes report when they have finished eating.

## Implementation Detail: Mutex Naming

* The Host creates Mutexes named `"String 0"` to `"String 4"`.
* A Philosopher with ID $N$ (passed as argument) attempts to use Mutexes based on $N$ and $N \pmod 5$.

## ⚠️ Known Issue / Deviation from Classic Problem

The current implementation of the Philosopher process (`PhilosopherProcess.cpp`) contains a significant bug in its synchronization logic:

```cpp
// ... inside PhilosopherProcess.cpp
// Both MTX[0] and MTX[1] are assigned the handle for the Mutex named "String num"
for (int i = 0; i < 2; i++)
    MTX[i] = CreateMutexA(NULL, FALSE, N1);
