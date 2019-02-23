/*! \file main.cpp
    \brief A documented file.

    Craig Lawlor
    Feb 2019
*/
#include "Barrier.h"
#include <iostream>
#include <thread>
#include <vector>
/*! \mainpage Barrier Lab
  The code in this lab uses a Barrier with a mutex lock to stop threads accessing certain parts of the 
  code until the current thread has released the mutex lock. 
*/
/*! \class main
    \brief An Implementation of Threads Using Semaphores 

   Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 
*/
/*! \var static const int num_threads=// 100
    \brief The number of threads we intend to create
*/
static const int num_threads = 100;
/*! \fn barrierTask
    \brief An example of using a reusable barrier
    \params theBarrier a shared pointer to the barrier
    \params numLoops to hold the number of times the loop will run

    A thread will print an A along with the number of the loop held by i. The wait function of the Barrier 
    class is then called to stop threads printing b's. 
*/
void barrierTask(std::shared_ptr<Barrier> theBarrier, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Do first bit of task   
    std::cout << "A"<< i << std::endl; // added endl for clearer output
    //Barrier
    theBarrier->wait();
    //Do second half of task
    std::cout<< "B" << i << std::endl; // added endl for clearer output
  }
}

/*! \fn int main()
    \brief The eponymous main function
    \var vt a vector of threads
    \var aBarrier a shared pointer to the barrier
    
     Creates a vector of threads and a barrier. For each thread in the vector the barrierTask function 
     is called. The threads are then joined before exiting. 
*/
int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Barrier> aBarrier( new Barrier(num_threads));
  /**< Launch the threads  */
  for(std::thread& t: vt){
    t=std::thread(barrierTask,aBarrier,10);
  }
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << "Game over" << std::endl;
  return 0;
}
