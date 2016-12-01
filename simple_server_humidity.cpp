#include "simple_server_humidity.h"

OCRepresentation HumidityResource::get()
{
	m_rep.setValue("state", m_state);
	m_rep.setValue("humidity", m_humidity);
	return m_rep;
}

void HumidityResource::put(OCRepresentation& rep)
{
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
}
