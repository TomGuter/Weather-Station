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
    cout << "7. Calculate Average For Data" << endl;  // New option
    cout << "8. Press 0 To Exit" << endl;
    cout << "Enter your choice: ";
    
}


void simulateRandomWeatherData(DatabaseHandler& dbHandler, Logger& logger, const string& selectedTable) 
{
        double temperature = readTemperature();
        double humidity = readHumidity();
        double pressure = readPressure();
        double windSpeed = (rand() % 200) / 10.0; 
        double windDirection = rand() % 360; 

        cout << "Temperature: " << temperature << "C" << endl;
        cout << "Humidity: " << humidity << "%" << endl;
        cout << "Pressure: " << pressure << " hPa" << endl;
        cout << "Wind Speed: " << windSpeed << " m/s" << endl;
        cout << "Wind Direction: " << windDirection << "deg" << endl;
        cout << "----------------------------" << endl;
        //printWeatherData(selectedTable, temperature, humidity, pressure, windSpeed, windDirection, dbHandler, logger, selectedTable);

}

string replaceSpacesWithHyphens(const string& input) {
    string modifiedInput = input;
    replace(modifiedInput.begin(), modifiedInput.end(), ' ', '-');
    return modifiedInput;
}


void printWeatherData(
    const string& cityName, const string& country, double latitude, double longitude,
    double temperature, double feelsLike, double tempMin, double tempMax,
    double pressure, double humidity, double seaLevel, double groundLevel,
    double visibility, double windSpeed, double windDirection, double cloudiness,
    const string& weatherMain, const string& weatherDescription, const string& weatherIcon,
    int sunrise, int sunset, DatabaseHandler& dbHandler, Logger& logger, const string& selectedTable)
{
    cout << "City: " << cityName << ", " << country << endl;
    cout << "Coordinates: (" << latitude << ", " << longitude << ")" << endl;
    cout << "Temperature: " << temperature << "C" << endl;
    cout << "Feels Like: " << feelsLike << "C" << endl;
    cout << "Temp Min: " << tempMin << "C" << endl;
    cout << "Temp Max: " << tempMax << "C" << endl;
    cout << "Pressure: " << pressure << " hPa" << endl;
    cout << "Humidity: " << humidity << "%" << endl;
    cout << "Sea Level Pressure: " << seaLevel << " hPa" << endl;
    cout << "Ground Level Pressure: " << groundLevel << " hPa" << endl;
    cout << "Visibility: " << visibility << " meters" << endl;
    cout << "Wind Speed: " << windSpeed << " m/s" << endl;
    cout << "Wind Direction: " << windDirection << "deg" << endl;
    cout << "Cloudiness: " << cloudiness << "%" << endl;
    cout << "Weather: " << weatherMain << " (" << weatherDescription << ")" << endl;
    cout << "Sunrise: " << sunrise << endl;
    cout << "Sunset: " << sunset << endl;
    cout << "----------------------------" << endl;

    dbHandler.logData(temperature, feelsLike, tempMin, tempMax, pressure, humidity, seaLevel, groundLevel,
        visibility, windSpeed, windDirection, cloudiness, weatherMain, weatherDescription,
        weatherIcon, sunrise, sunset, cityName, country, latitude, longitude, selectedTable);
    logger.logData(temperature, feelsLike, tempMin, tempMax, pressure, humidity, seaLevel, groundLevel,
        visibility, windSpeed, windDirection, cloudiness, weatherMain, weatherDescription,
        weatherIcon, sunrise, sunset, cityName, country, latitude, longitude, selectedTable);
}


void ApiDataResult(const json& weatherData, DatabaseHandler& dbHandler, Logger& logger, const string& selectedTable)
{
    string cityName = weatherData["name"];
    string country = weatherData["sys"]["country"];
    double latitude = weatherData["coord"]["lat"];
    double longitude = weatherData["coord"]["lon"];
    double temperature = weatherData["main"]["temp"] - 273.15; // converting to C
    double feelsLike = weatherData["main"]["feels_like"] - 273.15; // converting to C
    double tempMin = weatherData["main"]["temp_min"] - 273.15; // converting to C
    double tempMax = weatherData["main"]["temp_max"] - 273.15; // converting to C
    double pressure = weatherData["main"]["pressure"];
    double humidity = weatherData["main"]["humidity"];
    double seaLevel = weatherData["main"].contains("sea_level") ? weatherData["main"]["sea_level"].get<double>() : 0;
    double groundLevel = weatherData["main"].contains("grnd_level") ? weatherData["main"]["grnd_level"].get<double>() : 0;
    double visibility = weatherData["visibility"];
    double windSpeed = weatherData["wind"]["speed"];
    double windDirection = weatherData["wind"]["deg"];
    double cloudiness = weatherData["clouds"]["all"];
    string weatherMain = weatherData["weather"][0]["main"];
    string weatherDescription = weatherData["weather"][0]["description"];
    string weatherIcon = weatherData["weather"][0]["icon"];
    int sunrise = weatherData["sys"]["sunrise"];
    int sunset = weatherData["sys"]["sunset"];

    printWeatherData(cityName, country, latitude, longitude, temperature, feelsLike, tempMin, tempMax,
        pressure, humidity, seaLevel, groundLevel, visibility, windSpeed, windDirection,
        cloudiness, weatherMain, weatherDescription, weatherIcon, sunrise, sunset,
        dbHandler, logger, selectedTable);
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
