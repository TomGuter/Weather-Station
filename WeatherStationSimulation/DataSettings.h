#pragma once
#include <string>

using namespace std;

class DataSettings {
public:
	DataSettings() = default;
	string get_apiKey_openWeather();
	string get_apiKey_openCageData();
	void set_apiKey_openWeather(const string& apiKey_openWeather);
	void set_get_apiKey_openCageData(const string& apiKey_openCageData);


public:
	string apiKey_openWeather;
	string apiKey_openCageData;


};