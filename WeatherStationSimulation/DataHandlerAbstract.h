#pragma once

#include <string>
#include <vector>

using namespace std;

class DataHandlerAbstract {
public:
    virtual void logData(double temperature, double humidity, double pressure, double windSpeed, double windDirection, const string& tableName, const string& cityName) = 0;
    virtual ~DataHandlerAbstract() {}
};
