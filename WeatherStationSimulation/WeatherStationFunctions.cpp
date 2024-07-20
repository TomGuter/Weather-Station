#include "WeatherStationFunctions.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

void displayMenu() {
    cout << "-----------------------" << endl;
    cout << "Weather Station" << endl;
    cout << "-----------------------" << endl;
    cout << "1. Start Simulation" << endl;
    cout << "2. Display Logged Data" << endl;
    cout << "3. Create New Table" << endl;
    cout << "4. Delete Table" << endl;
    cout << "5. Display All Tables" << endl;
    cout << "6. Rename Table" << endl;
    cout << "7. Calculate Average Data" << endl;  // New option
    cout << "8. Press 0 To Exit" << endl;
    cout << "Enter your choice: ";
    cout << endl << "-----------------------" << endl;
}


void simulateRandomWeatherData(DatabaseHandler& dbHandler, Logger& logger, const string& selectedTable) 
{
        double temperature = readTemperature();
        double humidity = readHumidity();
        double pressure = readPressure();
        double windSpeed = (rand() % 200) / 10.0; // Random wind speed between 0.0 and 20.0 m/s
        double windDirection = rand() % 360; // Random wind direction between 0� and 359�

        printWeatherData(selectedTable, temperature, humidity, pressure, windSpeed, windDirection, dbHandler, logger, selectedTable);

}


void printWeatherData(const string& cityName, double temperature, double humidity, double pressure, double windSpeed, double windDirection, DatabaseHandler& dbHandler, Logger& logger, const string& selectedTable)
{
    cout << "City: " << cityName << endl;
    cout << "Temperature: " << temperature << "C" << endl;
    cout << "Humidity: " << humidity << "%" << endl;
    cout << "Pressure: " << pressure << " hPa" << endl;
    cout << "Wind Speed: " << windSpeed << " m/s" << endl;
    cout << "Wind Direction: " << windDirection << "deg" << endl;
    cout << "----------------------------" << endl;

    dbHandler.logData(temperature, humidity, pressure, windSpeed, windDirection, selectedTable, cityName); // log the data to the database
    logger.logData(temperature, humidity, pressure, windSpeed, windDirection, selectedTable, cityName); // log the data to the relevent file output


}

void ApiDataResult(const json& weatherData, DatabaseHandler& dbHandler, Logger& logger, const string& selectedTable)
{
    string cityName = weatherData["name"];
    double temperature = weatherData["main"]["temp"] - 273.15; // converting to C
    double humidity = weatherData["main"]["humidity"];
    double pressure = weatherData["main"]["pressure"];
    double windSpeed = weatherData["wind"]["speed"];
    double windDirection = weatherData["wind"]["deg"];

    printWeatherData(cityName, temperature, humidity, pressure, windSpeed, windDirection, dbHandler, logger, selectedTable);

}

bool isValidLatitude(double latitude) {
    return latitude >= -90.0 && latitude <= 90.0;
}

bool isValidLongitude(double longitude) {
    return longitude >= -180.0 && longitude <= 180.0;
}



double readTemperature() {
    return (rand() % 30) - 10.0; // Random temperature between -10.0�C and 20.0�C
}

double readHumidity() {
    // Simulate humidity reading
    return rand() % 101; // Random humidity between 0% and 100%
}

double readPressure() {
    return (rand() % 1001) + 900.0; // Random pressure between 900.0 hPa and 1900.0 hPa
}

void userInputHandler(atomic<bool>& running) {
    cin.ignore();
    cin.get();
    running = false;
}
