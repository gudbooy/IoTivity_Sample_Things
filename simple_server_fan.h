#ifndef _SIMPLE_SERVER_FAN_H_
#define _SIMPLE_SERVER_FAN_H_

#include "resource.h"

class FanResource : public Resource
{
	public:
		FanResource() : m_name("Simple_Fan"), m_state(false), Resource("/a/fan", "core.fan")
		{
			m_rep.setValue("state", m_state);
			m_rep.setValue("name", m_name);
		}
		void put(OCRepresentation& rep);
		OCRepresentation get();
		void* changeResourceRepresentation(void *param) { return NULL; }
	private:
		std::string m_name;
		bool m_state;
};


#endif /* _SIMPLE_SERVER_HUMIDITY_H_ */

