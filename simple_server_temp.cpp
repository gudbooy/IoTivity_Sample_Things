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
void* TempResource::changeResourceRepresentation(void *param)
{

}
