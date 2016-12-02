//#include "simple_server_temp.h"
#include "resource.h"
void Resource::createResource()
{
	std::string resourceTypeName = 	m_resourceTypeName;
	std::string resourceURI = m_uri;
	std::string resourceInterface = DEFAULT_INTERFACE;
	uint8_t resourceProperty;
	resourceProperty = OC_DISCOVERABLE | OC_OBSERVABLE;
	EntityHandler cb = std::bind(&Resource::entityHandler, this, placeholders::_1);

	OCStackResult result = OCPlatform::registerResource(
			m_resourceHandle, resourceURI, resourceTypeName,
			resourceInterface, cb, resourceProperty);

	if (OC_STACK_OK != result)
	{
		cout << "Resource creation was unsuccessful\n";
	}
}

OCResourceHandle Resource::getHandle()
{
	return m_resourceHandle;
}

OCEntityHandlerResult Resource::entityHandler(std::shared_ptr<OCResourceRequest> request)
{
	cout << "\tIn Server CPP entity handler:\n";
	OCEntityHandlerResult ehResult = OC_EH_ERROR;
	if(request)
	{
		std::string requestType = request->getRequestType();
		int requestFlag = request->getRequestHandlerFlag();
		if(requestFlag & RequestHandlerFlag::RequestFlag)
		{
			cout << "\t\trequestFlag : Request\n";		
			auto pResponse = std::make_shared<OC::OCResourceResponse>();
			pResponse->setRequestHandle(request->getRequestHandle());
			pResponse->setResourceHandle(request->getResourceHandle());

			// Check for query params (if any)
			QueryParamsMap queries = request->getQueryParameters();

			if (!queries.empty())
			{
				std::cout << "\nQuery processing upto entityHandler" << std::endl;
			}
			for (auto it : queries)
			{
				std::cout << "Query key: " << it.first << " value : " << it.second
					<< std:: endl;
			}
			if(requestType == "GET")
			{
				cout << "GET Request\n";
				pResponse->setErrorCode(200);
				pResponse->setResponseResult(OC_EH_OK);
				pResponse->setResourceRepresentation(get());
				if(OC_STACK_OK == OCPlatform::sendResponse(pResponse)){
					ehResult = OC_EH_OK;
				}
			}
			else if(requestType == "PUT")
			{
				cout << "PUT Request\n";
				OCRepresentation rep = request->getResourceRepresentation();	
				put(rep);
				pResponse->setErrorCode(200);
				pResponse->setResponseResult(OC_EH_OK);
				pResponse->setResourceRepresentation(get());
				if(OC_STACK_OK == OCPlatform::sendResponse(pResponse))
				{
					ehResult = OC_EH_OK;
				}
			}
			else if(requestType == "DELETE")
			{
				cout << "Delete Request\n";
				ehResult = OC_EH_OK;
			}

		}
		if(requestFlag & RequestHandlerFlag::ObserverFlag)
		{
			cout << "Observe Request\n";
			ObservationInfo observationInfo = request->getObservationInfo();
			if(ObserveAction::ObserveRegister == observationInfo.action)
			{
				m_interestedObservers.push_back(observationInfo.obsId);
			}
			else if(ObserveAction::ObserveUnregister == observationInfo.action)
			{
				 m_interestedObservers.erase(std::remove(
							 											m_interestedObservers.begin(),
							 											m_interestedObservers.end(),
							 											observationInfo.obsId),
						 												m_interestedObservers.end());
			}
			pthread_t threadId;
			cout << "\t\trequestFlag : Observer\n";
			gObservation = 1;
			static int startedThread = 0;
			if(!startedThread)
			{
				 pthread_create (&threadId, NULL, &Resource::changeResourceRepresentation_ptr, 
						 this);

				 startedThread = 1;
			}
			ehResult = OC_EH_OK;
		}
	}
	else
		cout << "Request Invalid\n";

	return ehResult;
}
