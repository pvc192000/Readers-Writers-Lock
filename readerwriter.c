#include "readerwriter.h"
void rwlock_init(rwlock_t * rw) {
  rw -> readers = 0;
  sem_init( & rw -> lock, 0, 1);
  sem_init( & rw -> writelock, 0, 1);
  sem_init( & rw -> readlock, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t * rw) {
  sem_wait(&rw -> readlock); // both the functions acquire_readlock and acquire_writelock wait on this semaphore. It acts as queue of threads, reducing the chance of starvation of either writers or readers.
  sem_wait( & rw -> lock); //provides mutual exclusion amongst reader threads
  rw -> readers++;
  if (rw -> readers == 1)
    sem_wait( & rw -> writelock); // first reader acquires writelock
  sem_post(&rw -> readlock);
  sem_post( & rw -> lock);

}

void rwlock_release_readlock(rwlock_t * rw) {
  sem_wait( & rw -> lock); //provides mutual exclusion amongst reader threads
  rw -> readers--;
  if (rw -> readers == 0)
    sem_post( & rw -> writelock); // last reader releases writelock
  sem_post( & rw -> lock);
}

void rwlock_acquire_writelock(rwlock_t * rw) {
  sem_wait( & rw -> readlock); // both the functions acquire_readlock and acquire_writelock wait on this semaphore. It acts as queue of threads, reducing the chance of starvation of either writers or readers.
  sem_wait(&rw -> writelock);
  sem_post( & rw -> readlock);
}

void rwlock_release_writelock(rwlock_t * rw) {

  sem_post( & rw -> writelock);
}
