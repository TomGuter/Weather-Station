#include "DatabaseHandler.h"
#include "Logger.h"
#include <atomic>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "DataHandlerAbstract.h"
#include "WeatherStationFunctions.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "WeatherStationAPI.h"


using namespace std;

class UserInterface {
public:
	void ApplicationControl(const string& apiKey_openWeather, const string& apiKey_openCageData, DatabaseHandler& dbHandler, Logger& logger);
	void runSimulation(const string& lat, const string& lon, const string& selectedTable, int sleep, const string& apiKey_openWeather, DatabaseHandler& dbHandler, Logger& logger, atomic<bool>& running);
};