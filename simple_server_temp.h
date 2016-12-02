#ifndef _SIMPLE_SERVER_TEMP_H_
#define _SIMPLE_SERVER_TEMP_H_

#include "resource.h"
class TempResource : public Resource
{
	public:
		TempResource()
			:m_name("Simple_Temp"), m_state(false), m_temp(0.0), Resource("/a/temp", "core.temp")
		{
			m_rep.setValue("state", m_state);
			m_rep.setValue("temp", m_temp);
			m_rep.setValue("name", m_name);
		}
  	void put(OCRepresentation& rep);
		OCRepresentation get();
		void* changeResourceRepresentation(void *param);
	private:
		std::string m_name;
		bool m_state;
		double m_temp;
};

#endif /*_SIMPLE_SERVER_TEMP_H_ */
