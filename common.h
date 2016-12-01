#ifndef _COMMON_H_
#define _COMMON_H_

#include <functional>
#include <unistd.h>
#include <pthread.h>
#include <mutex>
#include <condition_variable>

#include "OCPlatform.h"
#include "OCApi.h"
#include <iostream>

using namespace OC;
using namespace std;

class Resource
{
	public:
		virtual void createResource() = 0;
		virtual void put(OCRepresentation& rep) = 0;
		virtual OCRepresentation get() = 0;
		virtual OCRepresentation post(OCRepresentation& rep) = 0;
	private:
		virtual OCEntityHandlerResult entityHandler(std::shared_ptr<OCResourceRequest> request) = 0;

};	

#endif /*_COMMON_H_*/
