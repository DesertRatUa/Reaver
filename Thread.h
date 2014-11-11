/*
 * Thread
 *
 *  Created on: 10 но€б. 2014 г.
 *      Author: maximm
 */

#ifndef THREAD_
#define THREAD_

#include <thread>
#include <mutex>
#include <vector>

typedef std::unique_ptr<std::thread> ThreadPtr;
typedef std::vector<ThreadPtr> ThreadVct;

#endif /* THREAD_ */
