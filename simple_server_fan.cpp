#include "simple_server_fan.h"

OCRepresentation FanResource::get()
{
	m_rep.setValue("state", m_state);
	return m_rep;
}

void FanResource::put(OCRepresentation& rep)
{
	try {
		if (rep.getValue("state", m_state))
			cout << "\t\t\t\t" << "state: " << m_state << endl;
		else
			cout << "\t\t\t\t" << "state not found in the representation" << endl;
	}
	catch (exception& e){
		cout << e.what() << endl;
	}
}

