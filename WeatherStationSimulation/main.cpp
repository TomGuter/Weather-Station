#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "DataHandlerAbstract.h"
#include "DatabaseHandler.h"
#include "Logger.h"
#include "WeatherStationFunctions.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "WeatherStationAPI.h"
#include "UserInterface.h"
#include "DataSettings.h"




using json = nlohmann::json;
using namespace std;


int main() {



    
    UserInterface userInterface;
    DataSettings dataS;
    dataS.set_apiKey_openWeather("685ddc100fd1246dc97f46a1c991b59a");
    dataS.set_get_apiKey_openCageData("9bcc4a626b1141bf83072a2ae96c9a14");

    string apiKey_openWeather = dataS.get_apiKey_openWeather();
    string apiKey_openCageData = dataS.get_apiKey_openCageData();

    DatabaseHandler dbHandler("weather_database.db");
    Logger logger("weather_database.log");

    userInterface.ApplicationControl(apiKey_openWeather, apiKey_openCageData, dbHandler, logger);

    return 0;


}
