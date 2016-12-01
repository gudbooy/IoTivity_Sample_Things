#ifndef _RESOURCE_H_
#define _RESOURCE_H_

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
		virtual void createResource();
		virtual void put(OCRepresentation& rep);
		virtual OCRepresentation get();
	private:
		virtual OCEntityHandlerResult entityHandler(std::shared_ptr<OCResourceRequest> request);

};	

#endif /*_RESOURCE_H_*/
