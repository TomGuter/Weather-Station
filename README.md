## Weather Station Project
Overview
This project is a Weather Station application written in C++. It collects weather data from the OpenWeatherMap and OpenCage APIs, logs it into a SQLite database, and provides various functionalities to interact with the data, including displaying, exporting, and calculating averages.

## Main Menu
![Alt text](https://github.com/TomGuter/Weather-Station/blob/main/weather_station_screenshots_examples/main%20menu.jpg?raw=true)

## Main menu Features Example:
You will be presented with a menu with the following options:
- Fetch weather data: Enter the city and country to fetch weather data from OpenWeatherMap and OpenCage Apis .
- Show logged data: Select a table to display the logged weather data.
- Export data to CSV: Select a table and provide a file path to export the data to a CSV file.
- Calculate statistics: Select a numerical column to calculate the statistics values like average.
- Data fetching: Follow the prompts to enter the country and city names. If you enter a space, it will be replaced with a hyphen to prevent issues.
- Show logged data: Select a table to display its data. The data will be formatted for readability.

  ## Getting real time data from APIs:
  ![Alt text](https://github.com/TomGuter/Weather-Station/blob/main/weather_station_screenshots_examples/simulation%20example1%20real%20time%20data.jpg?raw=true)


## Choose a table to start sampling real time time to the table until you stop it:
  ![Alt text](https://github.com/TomGuter/Weather-Station/blob/main/weather_station_screenshots_examples/simulation%20example1%20select%20a%20table%20from%20db.jpg?raw=true)

## Show logged data from a selected table:
  ![Alt text](https://github.com/TomGuter/Weather-Station/blob/main/weather_station_screenshots_examples/simulation%20example2%20imported%20data%20from%20database.jpg?raw=true)

## Choose a table and a column to calculate statistics
  ![Alt text](https://github.com/TomGuter/Weather-Station/blob/main/weather_station_screenshots_examples/simulation%20example2%20imported%20data%20from%20database.jpg?raw=true)

## Example of how the data is saved on database (SQLite)
  ![Alt text](https://github.com/TomGuter/Weather-Station/blob/main/weather_station_screenshots_examples/simulation%20example4%20imported%20table%20as%20csv%20file.jpg?raw=true)


# Requirements
- C++ compiler (e.g., GCC, Clang, or MSVC)
- SQLite library
- cURL library for API requests
- nlohmann/json library for JSON parsing
  
## Setup
Clone the repository: https://github.com/TomGuter/Weather-Station.git
- Install dependencies:
Ensure that you have the SQLite, cURL, and nlohmann/json libraries installed. Refer to their respective documentation for installation instructions.

## Build the project:
Compile the project using your preferred C++ compiler. Here is an example using g++:

Copy code
g++ -o weather_station main.cpp DatabaseHandler.cpp Logger.cpp WeatherStationAPI.cpp UserInterface.cpp -l sqlite3 -l curl -std=c++11
Run the application.

Usage:
- Start the application:
- Run the compiled binary to start the application.



## Code Structure:
1. main.cpp: Entry point of the application.
2. DatabaseHandler.h/.cpp: Handles database operations.
3. Logger.h/.cpp: Handles logging operations.
4. WeatherStationAPI.h/.cpp: Interacts with the OpenWeatherMap and Opencage APIs.
5. UserInterface.h/.cpp: Manages user interactions and the application menu.
6. DataHandlerAbstract.h: Abstract base class for data handlers.
7. DataSetting.h/.cpp: Set the Database file name.
8. WeatherStationFunctions.h/cpp: A list of functions that UserInterface can use.







