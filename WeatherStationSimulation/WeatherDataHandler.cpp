#define _CRT_SECURE_NO_WARNINGS
#include "WeatherDataHandler.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>

WeatherDataHandler::WeatherDataHandler(const std::string& dbName) : DatabaseHandler(dbName) {}

void WeatherDataHandler::logData(double temperature, double humidity, double pressure, double windSpeed, double windDirection, const std::string& tableName) {
    // Log to file
    std::ofstream logFile("weather_data.log", std::ios_base::app);
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        logFile << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << " - "
            << "Temperature: " << temperature << "°C, "
            << "Humidity: " << humidity << "%, "
            << "Pressure: " << pressure << " hPa, "
            << "Wind Speed: " << windSpeed << " m/s, "
            << "Wind Direction: " << windDirection << "°" << std::endl;
        logFile.close();
    }
    else {
        std::cerr << "Unable to open log file!" << std::endl;
    }

    // Log to SQLite database
    std::string sql = "INSERT INTO " + tableName + " (timestamp, temperature, humidity, pressure, wind_speed, wind_direction) VALUES (datetime('now', 'localtime'), ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_double(stmt, 1, temperature);
    sqlite3_bind_double(stmt, 2, humidity);
    sqlite3_bind_double(stmt, 3, pressure);
    sqlite3_bind_double(stmt, 4, windSpeed);
    sqlite3_bind_double(stmt, 5, windDirection);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}
