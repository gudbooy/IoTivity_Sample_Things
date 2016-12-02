#ifndef _SIMPLE_SERVER_HUMIDITY_
#define _SIMPLE_SERVER_HUMIDITY_
#include "resource.h"
class HumidityResource : public Resource
{
	public:
		HumidityResource()
			:m_name("Simple_Humid"), m_state(false), 
			m_humidity(0.0), Resource("/a/humidity", "core.humidity")
		{
			stop_thread = false;	
			m_rep.setValue("state", m_state);
			m_rep.setValue("humidity", m_humidity);
			m_rep.setValue("name", m_name);
		}
		~HumidityResource()
		{
			stop_thread = true;
			th->join();
		}
		void put(OCRepresentation& rep);
		OCRepresentation get();
		void* changeResourceRepresentation(void *param);
		void sensorValueRead(void*);
	private:
		bool stop_thread;
		std::string m_name;
		bool m_state;
		double m_humidity;
		std::string m_tempUri;
};

#endif /* _SIMPLE_SERVER_HUMIDITY_ */
