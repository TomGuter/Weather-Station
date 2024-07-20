#include "DatabaseHandler.h"
#include <iostream>
#include <vector>

using namespace std;


DatabaseHandler::DatabaseHandler(const string& dbName) : dbName(dbName) {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
    }
    else {
        cout << "Opened database successfully" << endl;
    }
}

DatabaseHandler::~DatabaseHandler() {
    if (db) {
        sqlite3_close(db);
    }
}

void DatabaseHandler::createTable(const string& tableName) {
    string sql = "CREATE TABLE IF NOT EXISTS " + tableName + " ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "TEMPERATURE REAL, "
        "FEELS_LIKE REAL, "
        "TEMP_MIN REAL, "
        "TEMP_MAX REAL, "
        "PRESSURE REAL, "
        "HUMIDITY REAL, "
        "SEA_LEVEL REAL, "
        "GROUND_LEVEL REAL, "
        "VISIBILITY REAL, "
        "WIND_SPEED REAL, "
        "WIND_DIRECTION REAL, "
        "CLOUDINESS REAL, "
        "WEATHER_MAIN TEXT, "
        "WEATHER_DESCRIPTION TEXT, "
        "WEATHER_ICON TEXT, "
        "SUNRISE INTEGER, "
        "SUNSET INTEGER, "
        "CITY_NAME TEXT, "
        "COUNTRY TEXT, "
        "LATITUDE REAL, "
        "LONGITUDE REAL, "
        "TIMESTAMP DATETIME DEFAULT CURRENT_TIMESTAMP);";
    executeSQL(sql);
}


void DatabaseHandler::logData(
    double temperature, double feelsLike, double tempMin, double tempMax,
    double pressure, double humidity, double seaLevel, double groundLevel,
    double visibility, double windSpeed, double windDirection, double cloudiness,
    const string& weatherMain, const string& weatherDescription, const string& weatherIcon,
    int sunrise, int sunset, const string& cityName, const string& country,
    double latitude, double longitude, const string& tableName)
{
    string sql = "INSERT INTO " + tableName + " ("
        "TEMPERATURE, FEELS_LIKE, TEMP_MIN, TEMP_MAX, PRESSURE, HUMIDITY, SEA_LEVEL, GROUND_LEVEL, "
        "VISIBILITY, WIND_SPEED, WIND_DIRECTION, CLOUDINESS, WEATHER_MAIN, WEATHER_DESCRIPTION, WEATHER_ICON, "
        "SUNRISE, SUNSET, CITY_NAME, COUNTRY, LATITUDE, LONGITUDE) VALUES ("
        + to_string(temperature) + ", " + to_string(feelsLike) + ", " + to_string(tempMin) + ", " + to_string(tempMax) + ", "
        + to_string(pressure) + ", " + to_string(humidity) + ", " + to_string(seaLevel) + ", " + to_string(groundLevel) + ", "
        + to_string(visibility) + ", " + to_string(windSpeed) + ", " + to_string(windDirection) + ", " + to_string(cloudiness) + ", '"
        + weatherMain + "', '" + weatherDescription + "', '" + weatherIcon + "', "
        + to_string(sunrise) + ", " + to_string(sunset) + ", '" + cityName + "', '" + country + "', "
        + to_string(latitude) + ", " + to_string(longitude) + ");";
    executeSQL(sql);
}


vector<string> DatabaseHandler::getAllTables() { 
    vector<string> tables;
    string sql = "SELECT name FROM sqlite_master WHERE type='table';";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* text = sqlite3_column_text(stmt, 0);
            if (text) {
                tables.push_back(reinterpret_cast<const char*>(text));
            }
        }
        sqlite3_finalize(stmt);
    }
    else {
        cerr << "Failed to fetch tables: " << sqlite3_errmsg(db) << endl;
    }

    return tables;
}

bool DatabaseHandler::tableExists(const string& tableName) {
    string query = "SELECT name FROM sqlite_master WHERE type='table' AND name='" + tableName + "';";
    sqlite3_stmt* stmt;
    bool exists = false;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = true;
        }
        sqlite3_finalize(stmt);
    }
    else {
        cerr << "Failed to check if table exists." << endl;
    }

    return exists;
}

vector<string> DatabaseHandler::getColumnNames(const string& tableName) {
    vector<string> columnNames;
    string sql = "PRAGMA table_info(" + tableName + ");";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            columnNames.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        }
    }
    else {
        cerr << "Failed to retrieve column names: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    return columnNames;
}

vector<vector<string>> DatabaseHandler::getTableData(const string& tableName)
{
    vector<vector<string>> data;
    string sql = "SELECT * FROM " + tableName + ";";

    // Execute the SQL query and retrieve data
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        int colCount = sqlite3_column_count(stmt);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            vector<string> row;
            for (int i = 0; i < colCount; ++i) {
                row.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)));
            }
            data.push_back(row);
        }
        sqlite3_finalize(stmt);
    }
    else {
        cerr << "Failed to retrieve data from table: " << sqlite3_errmsg(db) << endl;
    }

    return data;

}

double DatabaseHandler::calculateAverageData(const string& tableName, const string& columnName) 
{
    string sql = "SELECT AVG(" + columnName + ") FROM " + tableName + ";";
    sqlite3_stmt* stmt;
    double averageData = 0.0;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            averageData = sqlite3_column_double(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    return averageData;
}




void DatabaseHandler::deleteTable(const string& tableName) {
    string sql = "DROP TABLE IF EXISTS " + tableName + ";";
    executeSQL(sql);
}

void DatabaseHandler::renameTable(const string& oldName, const string& newName) {
    // Check if table names are valid
    if (oldName.empty() || newName.empty() || oldName == newName) {
        cerr << "Invalid table names provided." << endl;
        return;
    }

    // Check if the old table exists
    if (!tableExists(oldName)) {
        cerr << "Table " << oldName << " does not exist." << endl;
        return;
    }

    // Create the SQL query to rename the table
    string query = "ALTER TABLE \"" + oldName + "\" RENAME TO \"" + newName + "\";";

    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        cerr << "Failed to rename table: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
    else {
        cout << "Table renamed successfully." << endl;
    }
}

string DatabaseHandler::selectTable() {
    vector<string> tables = getAllTables();
    if (tables.empty()) {
        cout << "No tables available." << endl;
        return "";
    }

    cout << "Available Tables:" << endl;
    for (size_t i = 0; i < tables.size(); ++i) {
        cout << i + 1 << ". " << tables[i] << endl;
    }
    cout << "-----------------------" << endl;

    int choice;
    cout << "Enter the number of the table to select: ";
    cin >> choice;

    if (choice < 1 || choice > tables.size()) {
        cout << "Invalid choice. Please try again." << endl;
        cout << "-----------------------" << endl;
        return "";
    }
    else {
        string selectedTable = tables[choice - 1];
        cout << "Selected table: " << selectedTable << endl;
        cout << "-----------------------" << endl;
        return selectedTable;
    }

    
}



void DatabaseHandler::executeSQL(const string& sql) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}
