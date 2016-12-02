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


}
