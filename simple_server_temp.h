#ifndef _SIMPLE_SERVER_TEMP_H_
#define _SIMPLE_SERVER_TEMP_H_

#include "resource.h"
class TempResource : public Resource
{
	public:
		std::string m_name;
		bool m_state;
		double m_temp;
		std::string m_tempUri;
		OCResourceHandle m_resourceHandle;
		OCRepresentation m_tempRep;
		ObservationIds m_interestedObservers;

	public:
		TempResource()
			:m_name("Simple Temp"), m_state(false), m_temp(0.0), m_tempUri("/a/light")
		{
			m_tempRep.setUri(m_tempUri);
			m_tempRep.setValue("state", m_state);
			m_tempRep.setValue("temp", m_temp);
			m_tempRep.setValue("name", m_name);

		}
		void createResource();
		void put(OCRepresentation& rep);
		OCRepresentation get();

	private:
		OCEntityHandlerResult entityHandler(std::shared_ptr<OCResourceRequest> request);
};

#endif /*_SIMPLE_SERVER_TEMP_H_ */
