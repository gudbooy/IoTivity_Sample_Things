#ifndef _SIMPLE_SERVER_LIGHT_H_
#define _SIMPLE_SERVER_LIGHT_H_

#include "resource.h"

class LightResource : public Resource
{
	public:
		LightResource()
			:m_name("Simple_Light"), m_state(false), Resource("/a/light", "core.light"), m_power(0)
		{
			m_rep.setValue("state", m_state);
			m_rep.setValue("power", m_power);
			m_rep.setValue("name", m_name);
		}
		void put(OCRepresentation& rep);
		OCRepresentation get();
		void* changeResourceRepresentation(void *param) { return NULL; }
	private:
		std::string m_name;
		bool m_state;
		int m_power;
};


#endif /* _SIMPLE_SERVER_LIGHT_H_ */
