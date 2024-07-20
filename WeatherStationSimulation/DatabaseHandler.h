#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <string>
#include <vector>
#include "DataHandlerAbstract.h"
#include <sqlite3.h>
#include <windows.h>  
#include <commdlg.h>
#include <string>


using namespace std;

class DatabaseHandler : public DataHandlerAbstract {
public:
    DatabaseHandler(const string& dbName);
    ~DatabaseHandler();

    virtual void logData(
        double temperature, double feelsLike, double tempMin, double tempMax,
        double pressure, double humidity, double seaLevel, double groundLevel,
        double visibility, double windSpeed, double windDirection, double cloudiness,
        const string& weatherMain, const string& weatherDescription, const string& weatherIcon,
        int sunrise, int sunset, const string& cityName, const string& country,
        double latitude, double longitude, const string& tableName) override;
    void createTable(const string& tableName);
    void deleteTable(const string& tableName);
    void renameTable(const string& oldName, const string& newName);
    bool tableExists(const string& tableName);
    vector<string> getColumnNames(const string& tableName);  // New function
    vector<vector<string>> getTableData(const string& tableName);
    vector<string> getAllTables();
    double calculateAverageData(const string& tableName, const string& columnName);
    string selectTable();
    void exportTableToCSV(const string& tableName);


private:
    sqlite3* db;
    string dbName;
    void executeSQL(const string& sql);
};

#endif
