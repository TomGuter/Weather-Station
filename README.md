Weather Station Project
Overview
This project is a Weather Station application written in C++. It collects weather data from the OpenWeatherMap API, logs it into a SQLite database, and provides various functionalities to interact with the data, including displaying, exporting, and calculating averages.

Features
Fetch weather data from the OpenWeatherMap API.
Log data into a SQLite database.
Display weather data in a readable format.
Export data to a CSV file.
Calculate average values for numerical data columns.
User-friendly command-line interface.
Requirements
C++ compiler (e.g., GCC, Clang, or MSVC)
SQLite library
cURL library for API requests
nlohmann/json library for JSON parsing
Setup
Clone the repository:

sh
Copy code
git clone https://github.com/yourusername/weather-station.git
cd weather-station
Install dependencies:
Ensure that you have the SQLite, cURL, and nlohmann/json libraries installed. Refer to their respective documentation for installation instructions.

Build the project:
Compile the project using your preferred C++ compiler. Here is an example using g++:

sh
Copy code
g++ -o weather_station main.cpp DatabaseHandler.cpp Logger.cpp WeatherStationAPI.cpp UserInterface.cpp -l sqlite3 -l curl -std=c++11
Run the application:

sh
Copy code
./weather_station
Usage
Start the application:
Run the compiled binary to start the application.

Main menu:
You will be presented with a menu with the following options:

Fetch weather data: Enter the city and country to fetch weather data from OpenWeatherMap.
Show logged data: Select a table to display the logged weather data.
Export data to CSV: Select a table and provide a file path to export the data to a CSV file.
Calculate averages: Select a numerical column to calculate the average value.
Exit: Exit the application.
Data fetching:
Follow the prompts to enter the country and city names. If you enter a space, it will be replaced with a hyphen to prevent issues.

Show logged data:
Select a table to display its data. The data will be formatted for readability.

Export data to CSV:
Select a table and provide a file path to save the CSV file. Ensure the path is valid to prevent errors.

Calculate averages:
Select a table and a numerical column to calculate the average value.

Code Structure
main.cpp: Entry point of the application.
DatabaseHandler.h/.cpp: Handles database operations.
Logger.h/.cpp: Handles logging operations.
WeatherStationAPI.h/.cpp: Interacts with the OpenWeatherMap API.
UserInterface.h/.cpp: Manages user interactions and the application menu.
DataHandlerAbstract.h: Abstract base class for data handlers.
