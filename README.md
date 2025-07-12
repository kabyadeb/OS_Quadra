# OS_Quadra
## Find Docs By Using man
```
man pipe
man shmget
man msgget
man fork
man read
```
| Section | Description                                       |
| ------- | ------------------------------------------------- |
| 1       | User commands (`ls`, `grep`, etc.)                |
| 2       | System calls (`open()`, `read()`, `fcntl()` etc.) |
| 3       | Library functions (`printf()`, `malloc()`)        |
| 4       | Special files (`/dev/null`)                       |
| 5       | File formats                                      |
| 7       | Misc (conventions, protocols)                     |
| 8       | Admin commands                                    |


# 1. System V IPC

System V IPC is the older IPC mechanism from UNIX System V (1980s).
## ✅ Features:

    Message Queues (msgget, msgsnd, msgrcv)

    Semaphores (semget, semop, semctl)

    Shared Memory (shmget, shmat, shmdt)

## 🔧 Characteristics:

    Uses integer keys (IPC keys) to identify resources.

    Resources are persistent: they stay even after processes exit, unless removed.

    Managed using tools like ipcs and ipcrm.

    Requires manual cleanup.

    Not namespace-aware (not container-friendly).


#  2. POSIX IPC

POSIX IPC is newer and standardized in POSIX.1b. It's designed to be simpler and more modern than System V.
## ✅ Features:

    Message Queues: mq_open, mq_send, mq_receive

    Semaphores: sem_open, sem_post, sem_wait

    Shared Memory: shm_open, mmap

## 🔧 Characteristics:

    Uses string names (like /myshm, /mysem) instead of integer keys.

    Resources are often temporary — removed on close/unlink.

    Easier to use and more portable across modern UNIX systems.

    Supports file descriptor-style handles.

    Namespace-aware (can work better in containers).
    
    
    
    | Flag          | Used In                            | Meaning                                                        |
| ------------- | ---------------------------------- | -------------------------------------------------------------- |
| `IPC_CREAT`   | `msgget()`, `shmget()`, `semget()` | **Create** the IPC object if it does not exist.                |
| `IPC_EXCL`    | Same as above                      | Used **with `IPC_CREAT`**: fail if object **already exists**.  |
| `IPC_NOWAIT`  | `msgsnd()`, `msgrcv()`, etc.       | **Don't block**; return an error if the operation would block. |
| `IPC_RMID`    | `msgctl()`, `shmctl()`, `semctl()` | **Remove** the IPC object (queue, memory segment, etc.).       |
| `IPC_STAT`    | `msgctl()`, `shmctl()`, `semctl()` | Get current **status** info about the object.                  |
| `IPC_SET`     | Same                               | Set object’s **permission and ownership** fields.              |
| `IPC_PRIVATE` | `msgget()`, `shmget()`, `semget()` | Creates a **private (unique)** object not shared with others.  |


The value 0666 is a Unix file permission mode, written in octal (base-8).
```
6 = 4 + 2 → read (4) + write (2) = rw-
```

| User (owner) | Group     | Others    |
| ------------ | --------- | --------- |
| `rw-` (6)    | `rw-` (6) | `rw-` (6) |

0666 = rw-rw-rw-

0600 = rw------- (only owner can read/write)

0777 = rwxrwxrwx (read/write/execute for all — not used for IPC)



# What is Shared Memory?

Shared memory allows multiple processes to access the same region of memory. It is:

   - Allocated by the kernel

   - Mapped into the address space of processes

   - Very fast (no kernel-user data copy overhead like pipes/message queues)

   - Must be synchronized manually (with semaphores, mutexes, etc.)
  
  
#  How Shared Memory Works (System V)

| Function   | Purpose                                             |
| ---------- | --------------------------------------------------- |
| `shmget()` | Create or get a shared memory segment               |
| `shmat()`  | Attach the shared memory to process's address space |
| `shmdt()`  | Detach shared memory from the process               |
| `shmctl()` | Control shared memory (e.g., delete it)             |


# System Call Details

1. `int shmget(key_t key, size_t size, int shmflg);`

   - Creates or accesses a shared memory segment.

   - key: Unique identifier (use ftok() or constant)

   - size: Size in bytes

   - shmflg: Flags and permissions (e.g., IPC_CREAT | 0666)
   
 2. `void* shmat(int shmid, const void *shmaddr, int shmflg);`

   - Attaches the shared memory segment to your process's address space.

   - Returns a pointer to the shared memory.

3. `int shmdt(const void *shmaddr);`

    - Detaches the shared memory from your process.


4. `int shmctl(int shmid, int cmd, struct shmid_ds *buf);`

    - Used to control or delete the shared memory.

   -  Common commands:
```
        IPC_RMID: Remove the shared memory segment

        IPC_STAT: Get info

        IPC_SET: Set info
```
