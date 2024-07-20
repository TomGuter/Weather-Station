#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <string>
#include <vector>
#include "DataHandlerAbstract.h"
#include <sqlite3.h>


using namespace std;

class DatabaseHandler : public DataHandlerAbstract {
public:
    DatabaseHandler(const string& dbName);
    ~DatabaseHandler();

    virtual void logData(double temperature, double humidity, double pressure, double windSpeed, double windDirection, const string& tableName, const string& cityName) override;
    void createTable(const string& tableName);
    void deleteTable(const string& tableName);
    void renameTable(const string& oldName, const string& newName);
    bool tableExists(const string& tableName);
    vector<string> getColumnNames(const string& tableName);  // New function
    vector<vector<string>> getTableData(const string& tableName);
    vector<string> getAllTables();
    double calculateAverageData(const string& tableName, const string& columnName);

    string selectTable();

private:
    sqlite3* db;
    string dbName;
    void executeSQL(const string& sql);
};

#endif
