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
void printWeatherData(const string& cityName, double temperature, double humidity, double pressure, double windSpeed, double windDirection, DatabaseHandler& dbHandler, Logger& logger, const string& selectedTable);
void ApiDataResult(const json& weatherData, DatabaseHandler& dbHandler, Logger& logger, const string& selectedTable);
bool isValidLatitude(double latitude);
bool isValidLongitude(double longitude);