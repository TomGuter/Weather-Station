#pragma once

#include <iostream>
#include <cstdlib>
#include <atomic>
#include "DatabaseHandler.h"
#include "Logger.h"
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void displayMenu();
double readTemperature();
double readHumidity();
double readPressure();
void userInputHandler(atomic<bool>& running);
void simulateRandomWeatherData(DatabaseHandler& dbHandler, Logger& logger, const string& selectedTable);
void printWeatherData(
    const string& cityName, const string& country, double latitude, double longitude,
    double temperature, double feelsLike, double tempMin, double tempMax,
    double pressure, double humidity, double seaLevel, double groundLevel,
    double visibility, double windSpeed, double windDirection, double cloudiness,
    const string& weatherMain, const string& weatherDescription, const string& weatherIcon,
    int sunrise, int sunset, DatabaseHandler& dbHandler, Logger& logger, const string& selectedTable);
void ApiDataResult(const json& weatherData, DatabaseHandler& dbHandler, Logger& logger, const string& selectedTable);
bool isValidLatitude(double latitude);
bool isValidLongitude(double longitude);
string replaceSpacesWithHyphens(const string& input);
