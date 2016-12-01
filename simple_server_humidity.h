#ifndef _SIMPLE_SERVER_HUMIDITY_
#define _SIMPLE_SERVER_HUMIDITY_
#include "resource.h"
class HumidityResource : public Resource
{
	public:
		HumidityResource()
			:m_name("Simple_Humid"), m_state(false), 
			m_humidity(0.0), Resource("/a/humid", "core.humidity")
		{
			m_rep.setValue("state", m_state);
			m_rep.setValue("humidity", m_humidity);
			m_rep.setValue("name", m_name);
		}
		void put(OCRepresentation& rep);
		OCRepresentation get();

	private:
		std::string m_name;
		bool m_state;
		double m_humidity;
		std::string m_tempUri;
};

#endif /* _SIMPLE_SERVER_HUMIDITY_ */
