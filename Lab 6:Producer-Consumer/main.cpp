/*! \file main.cpp
    \brief A documented file.

    Craig Lawlor
    Mar 2019
*/
#include "Event.h"
#include "SafeBuffer.h"
#include <iostream>
#include <thread>
#include <vector>

/*! \mainpage Barrier Lab
  The code in this lab uses a Safe Buffer
*/
/*! \var static const int num_threads=// 5
    \brief The number of threads we intend to create
*/
static const int num_threads = 5; 
const int size=5;

/*! \class main
    \brief An Implementation of a Safe Buffer for producer and consumer

   Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 
*/

/*! \fn producer
    \brief Creating events for the buffer
    \params theBuffer a shared pointer to the barrier
    \params numLoops to hold the number of times the loop will run
*/
void producer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Produce event and add to buffer
    Event e;
    theBuffer->push(e);
  }
}//producer

/*! \fn consumer
    \brief Taking events from the buffer to consume
    \params theBuffer a shared pointer to the barrier
    \params numLoops to hold the number of times the loop will run
*/
void consumer(std::shared_ptr<SafeBuffer> theBuffer, int numLoops){

  for(int i=0;i<numLoops;++i){
    //Produce event and add to buffer
    Event e= theBuffer->pop();
    e.consume();
  }
}//consumer

/*! \fn int main()
    \brief The eponymous main function
    \var producers a vector of threads
    \var consumers a vector of threads
    \var aBuffer a shared pointer to the barrier
    
     Creates 2 vectors of threads and a buffer. For each thread in each vector the barrierTask function 
     is called. The threads are then joined before exiting for producer and consumer. 
*/
int main(void){

  std::vector<std::thread> producers(num_threads);
  std::vector<std::thread> consumers(num_threads);
  std::shared_ptr<SafeBuffer> aBuffer( new SafeBuffer());
  /**< Launch the threads  */
  for(std::thread& p: producers){
    p=std::thread(producer,aBuffer,10);
  }

  for(std::thread& c: consumers){
    c=std::thread(consumer,aBuffer,10);
  }

  /**< Join the threads with the main thread */
  for (auto& p :producers){
      p.join();
  }
  for (auto& c :consumers){
      c.join();
  }

  std::cout  << std::endl;
  return 0;
}