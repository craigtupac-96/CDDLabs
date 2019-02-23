/*! \file main.cpp
    \brief A documented file.

    Craig Lawlor
    Feb 2019
*/
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <chrono>
/*! \mainpage Rendezvous Lab
  The code in this lab demonstrates a rendezvous by using a semaphores to make the first thread wait for the 
  second thread at a certain point before exiting
*/
/*! \class main
    \brief An Implementation of a Rendezvous using Semaphores

   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads

*/
/*! \fn taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay)
    \brief displays a message that is split in to 2 sections to show how a rendezvous works
    \param firstSem the first shared seaphore
    \param secondSem the second shared semaphore
    \param delay holds the time to delay

    Displays a message that the first task arrived and then sends a signal to allow the second task to exit
*/
void taskOne(std::shared_ptr<Semaphore> firstSem,std::shared_ptr<Semaphore>  secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task One has arrived! "<< std::endl;
  firstSem->Signal();
  std::cout << "Task One has left!"<<std::endl;
}
/*! \fn taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay)
    \brief displays a message that is split in to 2 sections to show how a rendezvous works
    \param firstSem the first shared seaphore
    \param secondSem the second shared semaphore
    \param delay holds the time to delay

    Displays a message that the second task has arrived and sends a wait to stop the thread fro exiting until 
    it receives a signal from the other thread
*/
void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task Two has arrived "<<std::endl;
  firstSem->Wait();
  std::cout << "Task Two has left "<<std::endl;
}

/*! \fn int main()
    \brief The eponymous main function
    \var threadOne the first thread
    \var threadTwo the second thread
    \var sem1 the first shared semaphore 
    \var sem2 the second shared semaphore 
    \var taskOneDelay the first delay 
    \var taskTwoDelay the second delay
    
     Creates two threads and sends each to one of the above functions with the shared semaphores.
     Then joins the threads and exits
*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem1( new Semaphore);
  std::shared_ptr<Semaphore> sem2( new Semaphore);
  int taskOneDelay=5;
  int taskTwoDelay=1;
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,sem1,sem2,taskTwoDelay);
  threadTwo=std::thread(taskOne,sem1,sem2,taskOneDelay);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
