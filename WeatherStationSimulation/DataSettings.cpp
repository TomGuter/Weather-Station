#include "DataSettings.h"


string DataSettings::get_apiKey_openWeather()
{
	return apiKey_openWeather;
}

string DataSettings::get_apiKey_openCageData()
{
	return apiKey_openCageData;
}

void DataSettings::set_apiKey_openWeather(const string& apiKey_openWeather)
{
	this->apiKey_openWeather = apiKey_openWeather;
}

void DataSettings::set_get_apiKey_openCageData(const string& apiKey_openCageData)
{
	this->apiKey_openCageData = apiKey_openCageData;
}
