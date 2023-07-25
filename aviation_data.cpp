#include "aviation_data.h"

int main() {
    std::ifstream file("sample.json");
    
    Json::Value jsonData; // create json object

    // parse the json file into json data object
    file >> jsonData;
    file.close();

    auto start_time = std::chrono::high_resolution_clock::now();
    loadData(jsonData);
    auto curr_time = std::chrono::high_resolution_clock::now();
    auto wall_clock = std::chrono::duration_cast<std::chrono::duration<double>> (curr_time - start_time);
    std::cout << "load took " << wall_clock.count() << " seconds" << std::endl;

    //printUmm(airport_multimap);
    //printUmm(airline_multimap);
    //searchByAirline("SAS");
    searchByAirport("Sydney Kingsford Smith Airport");

    return 0;
}

void loadData(Json::Value jsonData) {
    int data_size = jsonData["data"].size();

    for(int i = 0; i < data_size; i++) {
        Json::Value data_elem = jsonData["data"][i];
        Airport_Data departure_data;
        Airport_Data arrival_data;
        Flight_Data flight_data;

        departure_data.airport = jsonValueToString(data_elem["departure"]["airport"]);
        departure_data.iata = jsonValueToString(data_elem["departure"]["iata"]);
        departure_data.icao = jsonValueToString(data_elem["departure"]["icao"]);
        departure_data.terminal = jsonValueToString(data_elem["departure"]["terminal"]);
        departure_data.gate = jsonValueToString(data_elem["departure"]["gate"]);
        departure_data.delay = jsonValueToString(data_elem["departure"]["delay"]);
        departure_data.scheduled = jsonValueToString(data_elem["departure"]["scheduled"]);
        departure_data.estimated = jsonValueToString(data_elem["departure"]["estimated"]);
        departure_data.actual = jsonValueToString(data_elem["departure"]["actual"]);
        departure_data.estimated_runway = jsonValueToString(data_elem["departure"]["estimated_runway"]);
        departure_data.actual_runway = jsonValueToString(data_elem["departure"]["actual_runway"]);
        departure_data.type = DEPARTURE;
        
        arrival_data.airport = jsonValueToString(data_elem["arrival"]["airport"]);
        arrival_data.iata = jsonValueToString(data_elem["arrival"]["iata"]);
        arrival_data.icao = jsonValueToString(data_elem["arrival"]["icao"]);
        arrival_data.terminal = jsonValueToString(data_elem["arrival"]["terminal"]);
        arrival_data.gate = jsonValueToString(data_elem["arrival"]["gate"]);
        arrival_data.delay = jsonValueToString(data_elem["arrival"]["delay"]);
        arrival_data.scheduled = jsonValueToString(data_elem["arrival"]["scheduled"]);
        arrival_data.estimated = jsonValueToString(data_elem["arrival"]["estimated"]);
        arrival_data.actual = jsonValueToString(data_elem["arrival"]["actual"]);
        arrival_data.estimated_runway = jsonValueToString(data_elem["arrival"]["estimated_runway"]);
        arrival_data.actual_runway = jsonValueToString(data_elem["arrival"]["actual_runway"]);
        arrival_data.type = ARRIVAL;

        flight_data.flight_date = jsonValueToString(data_elem["flight_date"]);
        flight_data.flight_status = jsonValueToString(data_elem["flight_status"]);
        flight_data.flight_number = jsonValueToString(data_elem["flight"]["number"]);
        flight_data.flight_iata = jsonValueToString(data_elem["flight"]["iata"]);
        flight_data.flight_icao = jsonValueToString(data_elem["flight"]["icao"]);
        flight_data.airline_name = jsonValueToString(data_elem["airline"]["name"]);
        flight_data.airline_iata = jsonValueToString(data_elem["airline"]["iata"]);
        flight_data.airline_icao = jsonValueToString(data_elem["airline"]["icao"]);
        flight_data.departure_data = departure_data;
        flight_data.arrival_data = arrival_data;

        // insert to airline map
        airline_multimap.insert(std::make_pair(flight_data.airline_name, flight_data));

        // insert to airport map, will contain both departure and arrival airports
        // space complexity O(2n) -> O(n)
        airport_multimap.insert(std::make_pair(flight_data.departure_data.airport, flight_data));
        airport_multimap.insert(std::make_pair(flight_data.arrival_data.airport, flight_data));
    }
}

std::string jsonValueToString(Json::Value jsonData) {
    // Convert json data to a json string
    Json::StreamWriterBuilder writer;
    std::string jsonString = Json::writeString(writer, jsonData);

    //extra string cleaning by removing ""
    std::string quote_str = "\"";
    std::string::size_type i = jsonString.find(quote_str);
    while(i != std::string::npos) {
        jsonString.erase(i, quote_str.length());
        i = jsonString.find(quote_str, i);
    }
    return jsonString;
}

// Utility function to print unordered_multimap
void printUmm(std::unordered_multimap<std::string, Flight_Data> umm) {
    auto it = umm.begin(); // begin() returns iterator to first element of map
    for (; it != umm.end(); it++){
        std::cout << "<" << it->first << ", " << it->second.flight_number
             << ">  ";
        std::cout << std::endl;
    }
}

void searchByAirline(std::string airline_input) {
    // multi element search
    auto range = airline_multimap.equal_range(airline_input);
    for(auto it = range.first; it != range.second; it++) {
        std::cout << it->first << " " << it->second.arrival_data.airport << std::endl;
    }
}

void searchByAirport(std::string airport_input) {
    auto range = airport_multimap.equal_range(airport_input);
    for(auto it = range.first; it != range.second; it++) {
        std::cout << it->first << " " << it->second.flight_number << std::endl;
    }
}