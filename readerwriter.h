#ifndef RW_H
#define RW_H
#include <semaphore.h>

typedef struct rwlock_t {
  sem_t lock; // binary semaphore (basic lock)
  sem_t writelock; // used to allow ONE writer or MANY readers
  sem_t readlock; // used to prevent starvation of readers/writers
  int readers; // count of readers reading in critical section
}
rwlock_t;

void rwlock_init(rwlock_t * rw);

void rwlock_acquire_readlock(rwlock_t * rw);

void rwlock_release_readlock(rwlock_t * rw);

void rwlock_acquire_writelock(rwlock_t * rw);

void rwlock_release_writelock(rwlock_t * rw);
#endif