#define _CRT_SECURE_NO_WARNINGS
#include "Logger.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;

Logger::Logger(const string& logFileName) : logFileName(logFileName) {}

Logger::~Logger() {}

void Logger::logData(
    double temperature, double feelsLike, double tempMin, double tempMax,
    double pressure, double humidity, double seaLevel, double groundLevel,
    double visibility, double windSpeed, double windDirection, double cloudiness,
    const string& weatherMain, const string& weatherDescription, const string& weatherIcon,
    int sunrise, int sunset, const string& cityName, const string& country,
    double latitude, double longitude, const string& tableName) {
    ofstream logFile(logFileName, ios_base::app);
    if (logFile.is_open()) {
        auto now = chrono::system_clock::now();
        auto in_time_t = chrono::system_clock::to_time_t(now);
        logFile << put_time(localtime(&in_time_t), "%Y-%m-%d %X") << " - "
            << "City: " << cityName << ", "
            << "Temperature: " << temperature << "�C, "
            << "Humidity: " << humidity << "%, "
            << "Pressure: " << pressure << " hPa, "
            << "Wind Speed: " << windSpeed << " m/s, "
            << "Wind Direction: " << windDirection << "�" << endl;
        logFile.close();
    }
    else {
        cerr << "Unable to open log file!" << endl;
    }
}



