#pragma once
#include <string>
#include <vector>

using namespace std;

class DataHandlerAbstract {
public:
    virtual void logData(
        double temperature, double feelsLike, double tempMin, double tempMax,
        double pressure, double humidity, double seaLevel, double groundLevel,
        double visibility, double windSpeed, double windDirection, double cloudiness,
        const string& weatherMain, const string& weatherDescription, const string& weatherIcon,
        int sunrise, int sunset, const string& cityName, const string& country,
        double latitude, double longitude, const string& tableName) = 0;
    virtual ~DataHandlerAbstract() {}
};
