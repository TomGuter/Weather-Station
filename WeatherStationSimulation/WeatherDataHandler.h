#ifndef WEATHERDATAHANDLER_H
#define WEATHERDATAHANDLER_H

#include "DatabaseHandler.h"

class WeatherDataHandler : public DatabaseHandler {
public:
    WeatherDataHandler(const std::string& dbName);
    void logData(double temperature, double humidity, double pressure, double windSpeed, double windDirection, const std::string& tableName);
};

#endif // WEATHERDATAHANDLER_H
