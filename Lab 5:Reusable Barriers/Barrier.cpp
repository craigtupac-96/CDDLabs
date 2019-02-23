/*! \file Barrier.cpp
    \brief A documented file.

    Craig Lawlor
    Feb 2019
*/
#include "Semaphore.h"
#include "Barrier.h"
#include <iostream>
/*! \class Barrier
    \brief An Implementation of a Barrier

   Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 
*/
/*! \fn Barrier::~Barrier()
    \brief the destructor
*/
Barrier::~Barrier() {}

/*! \fn Barrier::Barrier(int numThreads) :numThreads(numThreads)
    \brief the constructor
    \params numThreads the number of threads
    \params mutexLock a shared semaphore
    \param firstSem a shared semaphore
    \param secondSem a shared semaphore

    There is no body in the constructor
*/
Barrier::Barrier(int numThreads) :numThreads(numThreads),
				   mutexLock(std::shared_ptr<Semaphore>(new Semaphore(1))),
				   firstSem(std::shared_ptr<Semaphore>(new Semaphore(0))),
				   secondSem(std::shared_ptr<Semaphore>(new Semaphore(1))){
}

/*! \fn void Barrier::wait()
    \brief The barrier wait function uses a mutex lock to stop threads from accessing certain
    parts of the code until until the lock opens. An if statement for when the count is at min 
    and max is protected by the mutex lock. These if statements have semaphores inside them. 

    If the count is at max (numThreads), the secondSem waits and firstSem signals. 
    If the count is at min (0), the firstSem waits and the secondSem signals. 
*/
void Barrier::wait(){
  // mutex set to 1 to allow the first thread through
  // Wait will then block the next thread until signal
  mutexLock->Wait(); // mutexLock = 0
  // increase thread count
  count++;
  
  if(count == numThreads) {
    secondSem->Wait();
    firstSem->Signal();
  }
  // business done, open the lock for the next thread
   mutexLock->Signal(); // mutexLock = 1
 
  firstSem->Wait();
  firstSem->Signal();

  // close lock
  mutexLock->Wait();

  count--;
  if(count == 0) {
    firstSem->Wait();
    secondSem->Signal();
  }
  // business done, open the lock for the next thread
  mutexLock->Signal();

  secondSem->Wait();
  secondSem->Signal();
}


// Barrier.cpp ends here

