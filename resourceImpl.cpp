#include "simple_server_temp.h"

void TempResource::createResource()
{
	std::string resourceURI = this->m_tempUri;
	std::string resourceTypeName = "core.temp";
	std::string resourceInterface = DEFAULT_INTERFACE;
	uint8_t resourceProperty;
	resourceProperty = OC_DISCOVERABLE | OC_OBSERVABLE;
	EntityHandler cb = std::bind(&TempResource::entityHandler, this, placeholders::_1);

	OCStackResult result = OCPlatform::registerResource(
			m_resourceHandle, resourceURI, resourceTypeName,
			resourceInterface, cb, resourceProperty);

	if (OC_STACK_OK != result)
	{
		cout << "Resource creation was unsuccessful\n";
	}
}

void TempResource::put(OCRepresentation& rep)
{
	try
	{

	}
	catch (exception& e)
	{

	}
}

OCRepresentation TempResource::get()
{	

	this->m_tempRep.setValue("temp", this->m_temp);
	return this->m_tempRep;
}

OCEntityHandlerResult TempResource::entityHandler(std::shared_ptr<OCResourceRequest> request)
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
				ehResult = OC_EH_OK;

			}
			else if(requestType == "PUT")
			{
				cout << "PUT Request\n";
				ehResult = OC_EH_OK;

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
		}
	}
	else
		cout << "Request Invalid\n";

	return ehResult;
}
