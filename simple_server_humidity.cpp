#include "simple_server_humidity.h"

OCRepresentation HumidityResource::get()
{
	m_rep.setValue("state", m_state);
	mtx.lock();
	m_rep.setValue("humidity", m_humidity);
	mtx.unlock();
	return m_rep;
}

void HumidityResource::put(OCRepresentation& rep)
{
	mtx.lock();
	try{
		if (rep.getValue("state", m_state))
			cout << "\t\t\t\t" << "state: " << m_state << endl;
		else
			cout << "\t\t\t\t" << "state not found in the representation" << endl;
		
		if (rep.getValue("humidity", m_humidity))
			cout << "\t\t\t\t" << "humidity: " << m_humidity << endl;
		else
			cout << "\t\t\t\t" << "humidity not found in the representation" << endl;
	}
	catch(exception& e)
	{
		cout << e.what() << endl;
	}
	mtx.unlock();
}

void HumidityResource::sensorValueRead(void *param)
{
	while(!stop_thread)
	{
		sleep(3);
		mtx.lock();
			m_humidity =(rand()%100)/100.0;
			cout << "Humidity : " << m_humidity << endl;
		mtx.unlock();
	}
}

void * HumidityResource::changeResourceRepresentation(void * param)
{
	HumidityResource* this_ptr =  (HumidityResource*)param;
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
