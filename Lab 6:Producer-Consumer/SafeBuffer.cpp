/*! \file SafeBuffer.cpp
    \brief A documented file.

    Craig Lawlor
    Mar 2019
*/
#include "SafeBuffer.h"

/*! \class SafeBuffer
    \brief An Implementation of a Safe Buffer

   Uses C++11 features such as mutex and condition variables to implement Semaphores in thread functions 
*/
/*! \fn SafeBuffer::SafeBuffer()
    \brief the constructor
    \var theMutex a shared semaphore
    \var theSemaphore a shared semaphore
*/
SafeBuffer::SafeBuffer(){
  theMutex = std::make_shared<Semaphore>(1);
  theSemaphore=std::make_shared<Semaphore>(0);
}

/*! \fn void SafeBuffer::push()
*/
int SafeBuffer::push(Event newEric){
  theMutex->Wait();
  theData.push_back(newEric);
  int size = theData.size();
  theSemaphore->Signal();
  theMutex->Signal();
  return size;
}

/*! \fn void SafeBuffer::pop()
*/
Event SafeBuffer::pop(){
  theSemaphore->Wait();
  theMutex->Wait();
  Event e = theData.back();
  theData.pop_back();
  theMutex->Signal();
  return e;
}