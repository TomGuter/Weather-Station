#pragma once


#include "DataHandlerAbstract.h"
#include <string>

using namespace std;

class Logger : public DataHandlerAbstract {
public:
    Logger(const string& logFileName);
    virtual void logData(
        double temperature, double feelsLike, double tempMin, double tempMax,
        double pressure, double humidity, double seaLevel, double groundLevel,
        double visibility, double windSpeed, double windDirection, double cloudiness,
        const string& weatherMain, const string& weatherDescription, const string& weatherIcon,
        int sunrise, int sunset, const string& cityName, const string& country,
        double latitude, double longitude, const string& tableName) override;
    virtual ~Logger();
private:
    string logFileName;
};
