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
	protected:
		OCRepresentation m_rep;
		OCResourceHandle m_resourceHandle;
		ObservationIds m_interestedObservers;
		std::string m_uri;
		std::string m_resourceTypeName;
		int gObservation;
	public:
		Resource(const char* uri, const char* resourceTypeName) : m_uri(uri),
		m_resourceTypeName(resourceTypeName)
		{
				gObservation = 0;
				m_rep.setUri(m_uri);
		}
		void createResource();
		virtual void put(OCRepresentation& rep) = 0;
		virtual	OCRepresentation get() = 0;
		static void* changeResourceRepresentation_ptr(void *this_ptr)
		{
				return ((Resource*)this_ptr)->changeResourceRepresentation(this_ptr);
		}
		virtual void* changeResourceRepresentation(void *param) = 0;
		OCResourceHandle getHandle();	
	private:
		OCEntityHandlerResult entityHandler(std::shared_ptr<OCResourceRequest> request);

};	

#endif /*_RESOURCE_H_*/
