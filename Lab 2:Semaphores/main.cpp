/*! \file main.cpp
    \brief A documented file.

    Craig Lawlor
    Feb 2019
*/
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>
/*! \mainpage Semaphores Lab
  The code in this lab uses a semaphore to control the output order of the 
  two functions.
*/
/*! \class main
    \brief An Implementation of Threads Using Semaphores 

   Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 
*/
/*! \fn void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay)
    \brief Displays a message first. To allow the taskTwo function to run its code this function must call the Signal 
    \param theSemaphore to call the Wait() and Signal() functions of the Semaphore calss
    \param delay time to sleep
*/
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal();
}
/*! \fn void taskTwo(std::shared_ptr<Semaphore> theSemaphore)
    \brief  displays a message second. By calling the Wait function the code will not run until the Signal function
  is called from the taskOne function 
    \param theSemaphore to call the Wait() and Signal() functions of the Semaphore calss
*/
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore->Wait();
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}

/*! \fn int main()
    \brief The eponymous main function
    \var threadOne the first thread
    \var threadTwo the second thread
    \var sem a shared semaphore 
    \var taskOneDelay an int to hold the delay time
    
     Creates two threads and sends each to one of the above functions. 
     Then joins the threads and exits.
*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);
  /**< Launch the threads  */
  int taskOneDelay=5;
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  std::cout << "Launched from the main\n";
   /**< Wait for the threads to finish */
  threadOne.join();
  threadTwo.join();
  return 0;
}
