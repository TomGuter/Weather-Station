#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "DataHandlerAbstract.h"
#include "DatabaseHandler.h"
#include "Logger.h"
#include "WeatherStationFunctions.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "WeatherStationAPI.h"
#include "UserInterface.h"

using namespace std;


void UserInterface::ApplicationControl(const string& apiKey_openWeather, const string& apiKey_openCageData, DatabaseHandler& dbHandler, Logger& logger)
{
    string lat;
    string lon;
    string city;
    string country;
    string currentTable;


    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    atomic<bool> running(false);
    int sleep = 5;

    while (true) {
        displayMenu();
        char choice;
        cin >> choice;
        cout << endl << "-----------------------" << endl;


        switch (choice) {
        case '1': {

            string selectedTable = dbHandler.selectTable();
            if (selectedTable.empty()) {
                cout << "No valid table selected. Please select a valid table." << endl;
                break;
            }

            cout << "Choose simulation type:" << endl;
            cout << "1. Random Data For Practice (without logging data to the database...)" << endl;
            cout << "2. Specific Latitude and Longitude" << endl;
            cout << "3. Specific Country and City" << endl;
            cout << "Enter your choice: " << endl;
            cout << "-----------------------" << endl;
            int simChoice;
            cin >> simChoice;

            if (simChoice == 1) {
                cout << "Enter logging time in seconds: ";
                cin >> sleep;

                running = true;
                cout << endl << "Simulation is running. Press Enter to stop." << endl;
                thread inputThread(userInputHandler, ref(running));

                while (running) {
                    simulateRandomWeatherData(dbHandler, logger, selectedTable);

                    for (int i = 0; i < sleep; ++i) {
                        this_thread::sleep_for(chrono::seconds(1));
                        if (!running) break; // Check if simulation should stop
                    }
                }
                inputThread.join();
            }
            else if (simChoice == 2) {
                try {
                    cout << "Enter latitude: ";
                    cin >> lat;
                    bool res = isValidLatitude(stod(lat));
                    if (!res) {
                        cerr << "Wrong latitude!" << endl;
                        break;
                    }

                    cout << "Enter longitude: ";
                    cin >> lon;
                    res = isValidLongitude(stod(lon));
                    if (!res) {
                        cerr << "Wrong longitude!" << endl;
                        break;
                    }
                }
                catch (const invalid_argument&) {
                    cerr << "Invalid input! Please enter a valid number." << endl;
                    break;
                }
                catch (const out_of_range&) {
                    cerr << "Input is out of range! Please enter a valid number." << endl;
                    break;
                }

                cout << "Enter logging data measurement time in seconds: ";
                cin >> sleep;

                running = true;
                cout << endl << "Simulation is running. Press Enter to stop." << endl;
                thread inputThread(userInputHandler, ref(running));

                runSimulation(lat, lon, selectedTable, sleep, apiKey_openWeather, dbHandler, logger, running);

                inputThread.join(); // wait for user input thread to finish
            }
            else if (simChoice == 3) {
                try {
                    cout << "Enter country: ";
                    cin.ignore(); // clear the input buffer 
                    getline(cin, country); // use getline to handle multi-word input
                    country = replaceSpacesWithHyphens(country);

                    cout << "Enter city name: ";
                    getline(cin, city); // Use getline to handle multi-word input
                    city = replaceSpacesWithHyphens(city);

                    cout << "Enter logging time in seconds: ";
                    cin >> sleep;

                    if (sleep <= 0) {
                        throw invalid_argument("Sleep must be a number greater than 0.");
                    }

                    json coordinates = getApiData(apiKey_openCageData, city, country, 2);

                    if (coordinates.is_null() || coordinates["results"].empty()) {
                        throw runtime_error("Failed to get coordinates for the location: " + city + ", " + country);
                    }

                    string lat = to_string(coordinates["results"][0]["geometry"]["lat"].get<double>());
                    string lon = to_string(coordinates["results"][0]["geometry"]["lng"].get<double>());

                    cout << "Latitude: " << lat << endl;
                    cout << "Longitude: " << lon << endl;

                    running = true;
                    cout << endl << "Simulation is running. Press Enter to stop." << endl;
                    thread inputThread(userInputHandler, ref(running));

                    runSimulation(lat, lon, selectedTable, sleep, apiKey_openWeather, dbHandler, logger, running);

                    inputThread.join(); // wait for user input thread to finish
                }
                catch (const invalid_argument& e) {
                    cerr << "Input Error: " << e.what() << endl;
                }
                catch (const runtime_error& e) {
                    cerr << "Runtime Error: " << e.what() << endl;
                }
                catch (const exception& e) {
                    cerr << "An unexpected error occurred: " << e.what() << endl;
                }
                catch (...) {
                    cerr << "An unknown error occurred." << endl;
                }
            }

            else {
                cout << "Invalid choice! Please try again." << endl;
            }

            break;
        }
        case '2': {
            // select a table before displaying data
            string selectedTable = dbHandler.selectTable();
            if (selectedTable.empty()) {
                cout << "No valid table selected. Please select a valid table." << endl;
                break;
            }

            // retrieve and display data from the selected table
            vector<vector<string>> data = dbHandler.getTableData(selectedTable);

            if (data.empty()) {
                cout << "No data available in the selected table." << endl;
            }
            else {
                cout << "Data from table '" << selectedTable << "':" << endl;

                // display column headers
                const vector<string>& headers = dbHandler.getColumnNames(selectedTable);
                for (const auto& row : data) {
                    for (size_t i = 0; i < headers.size(); ++i) {
                        cout << headers[i] << ": " << row[i];
                        if (i < headers.size() - 1) {
                            cout << ", ";
                        }
                    }
                    cout << endl;
                    cout << "_________________________________________________________" << endl;
                    cout << endl;
                }

            }

            break;
        }
        case '3': {
            // Create new table
            string newTable;
            cout << "Enter the name of the new table: ";
            cin >> newTable;
            dbHandler.createTable(newTable);
            currentTable = newTable;
            break;
        }
        case '4': {

            string tableToDelete;
            cout << "Enter the name of the table to delete: ";
            cin >> tableToDelete;
            if (dbHandler.tableExists(tableToDelete)) {
                dbHandler.deleteTable(tableToDelete);
                cout << tableToDelete << " Deleted... " << endl;
            }
            else {
                cout << " Syntax error, " << tableToDelete << " doesn't exist... " << endl;
            }
            break;
        }
        case '5': {
            // display all tables
            vector<string> tables = dbHandler.getAllTables();
            cout << "Existing Tables:" << endl;
            for (const auto& table : tables) {
                cout << "- " << table << endl;
            }
            break;
        }
        case '6': {
            // rename a table
            string oldTableName, newTableName;
            cout << "Enter the name of the table to rename: ";
            cin >> oldTableName;
            cout << "Enter the new name for the table: ";
            cin >> newTableName;
            dbHandler.renameTable(oldTableName, newTableName);
            if (currentTable == oldTableName) {
                currentTable = newTableName;
            }
            break;
        }
        case '7': {
            // print a specific table
            string selectedTable = dbHandler.selectTable();
            if (selectedTable.empty()) {
                cout << "No valid table selected. Please select a valid table." << endl;
                break;
            }

            vector<string> columns = dbHandler.getColumnNames(selectedTable);
            cout << "Available columns: " << endl;
            for (size_t i = 0; i < columns.size(); ++i) {
                cout << i + 1 << ". " << columns[i] << endl;
            }

            cout << "Enter the number of the column to calculate average: ";
            size_t colChoice;
            cin >> colChoice;

            if (colChoice < 1 || colChoice > columns.size()) {
                cout << "Invalid choice! Please try again." << endl;
            }
            else {
                string columnName = columns[colChoice - 1];
                double avgData = dbHandler.calculateAverageData(selectedTable, columnName);
                cout << "Average " << columnName << " for table '" << selectedTable << "': " << avgData << endl;
            }

            break;
        }
        case '8': {
            string selectedTable = dbHandler.selectTable();
            if (selectedTable.empty()) {
                cout << "No valid table selected. Please select a valid table." << endl;
                break;
            }

            dbHandler.exportTableToCSV(selectedTable);

            break;
        }
        case '0': {
            running = false;
            cout << "1. press 1 or everything except 2 if you want to continue the program" << endl;
            cout << "2. press 2 if you want to exit and finish" << endl;
            cin >> choice;
            switch (choice)
            {
            case '1': {
                break;
            }
            default:
                cout << "Exiting program..." << endl;
                return;
            }
            break;
        }
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}


void UserInterface::runSimulation(const string& lat, const string& lon, const string& selectedTable, int sleep, const string& apiKey_openWeather, DatabaseHandler& dbHandler, Logger& logger, atomic<bool>& running) {
    while (running) {
        json weatherData = getApiData(apiKey_openWeather, lat, lon, 1);
        if (!weatherData.empty()) {
            ApiDataResult(weatherData, dbHandler, logger, selectedTable);
        }
        else {
            cerr << "Failed to fetch weather data or data structure mismatch!" << endl;
        }

        for (int i = 0; i < sleep; ++i) {
            this_thread::sleep_for(chrono::seconds(1));
            if (!running) {
                break;
            }

        }
    }
}











