#ifndef WEATHERSTATIONAPI_H
#define WEATHERSTATIONAPI_H

#include <string>
#include <nlohmann/json.hpp>
#include <iostream>
#include <curl/curl.h>

using json = nlohmann::json;
using namespace std;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* data);
json getApiData(const string& apiKey, const string& str1, const string& str2, int ref);


#endif // WEATHERSTATIONAPI_H
