#include "simple_server_temp.h"

OCRepresentation TempResource::get()
{
	m_rep.setValue("state", m_state);
	m_rep.setValue("temp", m_temp);

	return m_rep;
}

void TempResource::put(OCRepresentation& rep)
{
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
	int count = 1;
	TempResource* this_ptr =  (TempResource*)param;	
	while(1)
	{
		sleep(3);
		if (gObservation)
		{
			if(count % 2 == 1){
				m_temp += rand()%5;
				count = 2;
			}
			else{
				m_temp -= rand()%5;
				count = 1;
			}
			OCStackResult result = OC_STACK_OK;

			result = OCPlatform::notifyAllObservers(this_ptr->getHandle());
			
			if(OC_STACK_NO_OBSERVERS == result)
			{
				cout << "No More observers, stopping notifications" << endl;
				gObservation = 0;
			}
		}

	}
	return NULL;
}


