# Process

process is an instance of a program in execution.

Program Code (Text Section) – The actual code that is to be executed.

Program Counter (PC) – Keeps track of which instruction to execute next.

Stack – Contains temporary data like function parameters, return addresses, and local variables.

Heap – Used for dynamic memory allocation during runtime.

Data Section – Contains global variables.

Registers – Hold data and instructions that the CPU is currently using.

Process ID (PID) – A unique identifier for each process.

To view current shell process id

```
echo $$
```

# What is IPC?

IPC stands for Inter-Process Communication.
It refers to mechanisms that allow processes to communicate with each other and synchronize their actions.

| IPC Type                | Description                                                                                 |
| ----------------------- | ------------------------------------------------------------------------------------------- |
| **Pipes**               | Unidirectional communication between related processes.                                     |
| **Named Pipes (FIFOs)** | Like pipes, but can be used between **unrelated** processes.                                |
| **Message Queues**      | Allow processes to send and receive messages via the kernel.                                |
| **Shared Memory**       | Fastest IPC — processes share a memory region. Requires synchronization (e.g., semaphores). |
| **Semaphores**          | Used to manage access to shared resources (synchronization).                                |
| **Sockets**             | Allow communication between processes over a network or on the same machine.                |
| **Signals**             | Used to notify a process that an event has occurred.                                        |

Structure of System V Shared Memory

    shmget(): Creates or accesses a shared memory segment.

    shmat(): Attaches the shared memory to the process's address space.

    shmdt(): Detaches the shared memory from the process.

    shmctl(): Performs operations like deletion, status checks, etc.
