#ifndef _SIMPLE_SERVER_TEMP_H_
#define _SIMPLE_SERVER_TEMP_H_

#include "resource.h"
class TempResource : public Resource
{
	public:
		TempResource()
			:m_name("Simple_Temp"), m_state(false), m_temp(0.0), Resource("/a/temp", "core.temp")
		{
			stop_thread = false;
			m_rep.setValue("state", m_state);
			m_rep.setValue("temp", m_temp);
			m_rep.setValue("name", m_name);
		}
	  ~TempResource()
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
		double m_temp;
};

#endif /*_SIMPLE_SERVER_TEMP_H_ */
