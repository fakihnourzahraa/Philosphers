# philosopherss
-> create mutexes
-> create threads
-> join threads
-> hardcode single case

Thread 1: Lock fork_mutex
Thread 1: Read fork_status (available)
Thread 1: Take fork, set status to "taken"
Thread 1: Unlock fork_mutex
Thread 2: Lock fork_mutex ← Now it's safe
Thread 2: Read fork_status (taken) ← Correct state

Important:

Only the thread that locked the mutex should unlock it
Always unlock mutexes you've locked (avoid deadlocks)


Common Error Codes
Thread errors:

EAGAIN: Insufficient resources
EINVAL: Invalid parameters
EPERM: Permission denied

Mutex errors:

EBUSY: Mutex is locked (for destroy)
EDEADLK: Deadlock detected
EPERM: Thread doesn't own the mutex (for unlock)


pthread_create()
cint pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
                   void *(*start_routine)(void *), void *arg);
Parameters:

thread: Pointer to pthread_t variable that will store the thread ID
attr: Thread attributes (usually NULL for default attributes)
start_routine: Function pointer - the function the new thread will execute
arg: Argument passed to the start_routine function (usually a struct pointer)

Return Value:

0 on success
Error number on failure (positive integer, like EAGAIN, EINVAL, EPERM)

Example usage:
cpthread_t philosopher_thread;
int philosopher_id = 1;

// Creates thread that runs philosopher_routine with &philosopher_id as argument
int result = pthread_create(&philosopher_thread, NULL, philosopher_routine, &philosopher_id);
if (result != 0)
    // Handle error

pthread_join()
cint pthread_join(pthread_t thread, void **retval);
Parameters:

thread: The thread ID to wait for
retval: Pointer to store the return value of the joined thread (can be NULL)

Return Value:

0 on success
Error number on failure (EDEADLK, EINVAL, ESRCH)

What it does:

Blocks the calling thread until the specified thread terminates
Cleans up thread resources automatically
Like "waiting for someone to finish their work before continuing"

Example:
cpthread_t thread;
void *return_value;

pthread_create(&thread, NULL, some_function, NULL);
// Do other work...
pthread_join(thread, &return_value); // Wait for thread to finish

pthread_detach()
cint pthread_detach(pthread_t thread);
Parameters:

thread: The thread ID to detach

Return Value:

0 on success
Error number on failure (EINVAL, ESRCH)

What it does:

Marks thread for automatic cleanup when it terminates
You can't pthread_join() a detached thread
Like "fire and forget" - thread cleans up after itself

Important: Either join or detach every thread, otherwise you get resource leaks!0

Mutex Functions
pthread_mutex_init()
cint pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
Parameters:

mutex: Pointer to the mutex variable to initialize
attr: Mutex attributes (usually NULL for default)

Return Value:

0 on success
Error number on failure (EAGAIN, ENOMEM, EPERM, EINVAL)

Alternative: Can use PTHREAD_MUTEX_INITIALIZER for static initialization
cpthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_destroy()
cint pthread_mutex_destroy(pthread_mutex_t *mutex);
Parameters:

mutex: Pointer to the mutex to destroy

Return Value:

0 on success
Error number on failure (EBUSY, EINVAL)

Important:

Only destroy unlocked mutexes
Don't use the mutex after destroying it
Must destroy mutexes you initialized (except static ones)


pthread_mutex_lock()
cint pthread_mutex_lock(pthread_mutex_t *mutex);
Parameters:

mutex: Pointer to the mutex to lock

Return Value:

0 on success
Error number on failure (EINVAL, EDEADLK)

Behavior:

If mutex is available: Locks it immediately and returns
If mutex is locked: Blocks (waits) until it becomes available
Blocking call: Thread sleeps until mutex is free


pthread_mutex_unlock()
cint pthread_mutex_unlock(pthread_mutex_t *mutex);
Parameters:

mutex: Pointer to the mutex to unlock

Return Value:

0 on success
Error number on failure (EINVAL, EPERM)
