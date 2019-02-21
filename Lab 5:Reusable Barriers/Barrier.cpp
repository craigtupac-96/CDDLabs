// Barrier.cpp --- 
// 
// Filename: Barrier.cpp
// Description: 
// Author: Joseph
// Maintainer: 
// Created: Tue Jan  8 12:14:02 2019 (+0000)
// Version: 
// Package-Requires: ()
// Last-Updated: Tue Jan  8 12:15:21 2019 (+0000)
//           By: Joseph
//     Update #: 2
// URL: 
// Doc URL: 
// Keywords: 
// Compatibility: 
// 
// 

// Commentary: 
// 
// 
// 
// 

// Change Log:
// 
// 
// 
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
// 

// Code:
#include "Semaphore.h"
#include "Barrier.h"
#include <iostream>
//using namespace std;
Barrier::~Barrier() {}

Barrier::Barrier(int numThreads) :numThreads(numThreads),
				   mutexLock(std::shared_ptr<Semaphore>(new Semaphore(1))),
				   firstSem(std::shared_ptr<Semaphore>(new Semaphore(0))),
				   secondSem(std::shared_ptr<Semaphore>(new Semaphore(1))){
  // no body to love
}

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

