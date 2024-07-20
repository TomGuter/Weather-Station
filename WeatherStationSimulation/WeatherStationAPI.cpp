#include "WeatherStationAPI.h"


using namespace std;

// Callback function to handle the data received from the API call
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* data) {
    data->append((char*)contents, size * nmemb);
    return size * nmemb;
}



json getApiData(const string& apiKey, const string& str1, const string& str2, int ref) {
    CURL* curl;
    CURLcode res;
    string readBuffer;
    string url;

    curl = curl_easy_init();
    curl = curl_easy_init();
    if (curl) {
        if (ref == 1) {
            url = "https://api.openweathermap.org/data/2.5/weather?lat=" + str1 + "&lon=" + str2 + "&appid=" + apiKey;
        }
        else if (ref == 2) {
            url = "https://api.opencagedata.com/geocode/v1/json?q=" + str1 + "%2C+" + str2 + "&key=" + apiKey;
        }

        // Set the URL and callback function
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            return json(); // Return empty JSON object on failure
        }
    }
    else {
        cerr << "Failed to initialize CURL" << endl;
        return json(); // Return empty JSON object on failure
    }

    return json::parse(readBuffer);
}

