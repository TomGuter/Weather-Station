// DataHandlerFactory.h
#pragma once
#include <string>
#include "DatabaseHandler.h"
#include "Logger.h"

//a class that provides methods to create instances of DatabaseHandler and Logger.
class DataHandlerFactory {
public:
    static DatabaseHandler createDatabaseHandler(const std::string& dbName);
    static Logger createLogger(const std::string& logFileName);
};
