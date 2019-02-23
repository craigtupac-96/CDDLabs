/*! \file main.cpp
    \brief A documented file.

    Craig Lawlor
    Feb 2019
*/
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
/*! \mainpage Mutual Exclusion Lab
  The code in this lab will use a semaphore to put a lock around a loop to stop other threads accessing it
  while a thread is using it. When the thread has completed it's business it signals to allow the next 
  thread in
*/
/*! \class main
    \brief An Implementation of Threads Using Semaphores 

   Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 
*/
/*! \var static const int num_threads=// 100
    \brief The number of threads we intend to create
*/
static const int num_threads = 100;
/*! \var int sharedVariable=// 100
    \brief The int that will be incremented
*/
int sharedVariable=0;

/*! \fn updateTask
    \brief An Implementation of Mutual Exclusion using Semaphores

   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads

*/
/*! \fn updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates)
    \brief displays a message that is split in to 2 sections to show how a rendezvous works
    \param firstSem a pointer to the first shared semaphore
    \param numUpdates to hold the limit for the loop

    The firstSem will lock the loop with a Wait() call which will not allow another thread to use the loop until 
    it Signals when finished. The shared variable will increment 1000 times for each of the 100 threads
*/
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates){

  firstSem->Wait();
  for(int i=0;i<numUpdates;i++){      
      sharedVariable++;
  }
  firstSem->Signal();

}

/*! \fn int main()
    \brief The eponymous main function
    \var vt a vector of threads
    \var aSemaphore a shared semaphore
    
     Creates a vector of threads and a semaphore. For each thread in the vector the updatetask function is 
     called. The threads are then joined before exiting.
*/
int main(void){
  std::vector<std::thread> vt(num_threads);
  /**< Unless the semaphore is set to 1 the program will stall */
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore(1));
  /**< Launch the threads  */
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
