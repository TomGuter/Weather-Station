#pragma once


#include "DataHandlerAbstract.h"
#include <string>

using namespace std;

class Logger : public DataHandlerAbstract {
public:
    Logger(const string& logFileName);
    virtual void logData(double temperature, double humidity, double pressure, double windSpeed, double windDirection, const string& tableName, const string& cityName) override;  
    virtual ~Logger();
private:
    string logFileName;
};
