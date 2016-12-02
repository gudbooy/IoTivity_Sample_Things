#include "simple_server_temp.h"

OCRepresentation TempResource::get()
{
	m_rep.setValue("state", m_state);
	mtx.lock();
	m_rep.setValue("temp", m_temp);
	mtx.unlock();
	return m_rep;
}

void TempResource::put(OCRepresentation& rep)
{
	mtx.lock();
	try {
		if (rep.getValue("state", m_state))
			cout << "\t\t\t\t" << "state: " << m_state << endl;
		else
			cout << "\t\t\t\t" << "state not found in the representation" << endl;

		if (rep.getValue("temp", m_temp))
			cout << "\t\t\t\t" << "temp: " << m_temp << endl;
		else
			cout << "\t\t\t\t" << "temp not found in the representation" << endl;
	}
	catch (exception& e){
		cout << e.what() << endl;
	}
	mtx.unlock();
}

void TempResource::sensorValueRead(void *param)
{
	while(!stop_thread)
	{
		sleep(3);
		mtx.lock();
			m_temp = 20.0 + rand() % 10;
			cout << "Temperature : " << m_temp << endl;
		mtx.unlock();
	}
}

void* TempResource::changeResourceRepresentation(void *param)
{	
	TempResource* this_ptr =  (TempResource*)param;	
	while(1)
	{
		sleep(2);
		if (gObservation)
		{
			
			OCStackResult result = OC_STACK_OK;

			std::shared_ptr<OCResourceResponse> resourceResponse =
			{std::make_shared<OCResourceResponse>()};

			resourceResponse->setErrorCode(200);
			resourceResponse->setResourceRepresentation(this_ptr->get(), DEFAULT_INTERFACE);

			result = OCPlatform::notifyListOfObservers( this_ptr->getHandle(),
					this_ptr->m_interestedObservers,
					resourceResponse);

			if(OC_STACK_NO_OBSERVERS == result)
			{
				cout << "No More observers, stopping notifications" << endl;
				gObservation = 0;
			}
		}

	}
	return NULL;
}


