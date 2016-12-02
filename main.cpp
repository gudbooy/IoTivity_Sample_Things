#include "simple_server_temp.h"
#include "simple_server_humidity.h"

static const char* SVR_DB_FILE_NAME = "./oic_svr_db_server.dat";

static FILE* client_open(const char* /*path*/, const char *mode)
{
	return fopen(SVR_DB_FILE_NAME, mode);
}

int main(void)
{
	TempResource *myTemp = NULL;
	HumidityResource *myHumidity = NULL;
	OCPersistentStorage ps {client_open, fread, fwrite, fclose, unlink };
	PlatformConfig cfg {
			OC::ServiceType::InProc,
			OC::ModeType::Server,
			"0.0.0.0", // By setting to "0.0.0.0", it binds to all available interfaces
			0,         // Uses randomly available port
			OC::QualityOfService::LowQos,
			&ps
	};
	OCPlatform::Configure(cfg);
	try
	{
		// Create the instance of the resource class
		myTemp = new TempResource();
		myHumidity = new HumidityResource();
		// Invoke createResource function of class light.
		myTemp->createResource();
		std::cout << "Created resource. Temp" << std::endl;

		// A condition variable will free the mutex it is given, then do a non-
		// intensive block until 'notify' is called on it.  In this case, since we
		// don't ever call cv.notify, this should be a non-processor intensive version
		// of while(true);
		std::mutex blocker;
		std::condition_variable cv;
		std::unique_lock<std::mutex> lock(blocker);
		std::cout <<"Waiting" << std::endl;
		cv.wait(lock, []{return false;});
	}
	catch(OCException &e)
	{
		std::cout << "OCException in main : " << e.what() << endl;
	}
	if(myTemp != NULL)
		delete myTemp;
	if(myHumidity != NULL)
		delete myHumidity;

	return 0;
}
