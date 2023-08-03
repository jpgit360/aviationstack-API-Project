#ifndef AVIATION_DATA_GUARD
#define AVIATION_DATA_GUARD
#include "json/json.h"
#include <unordered_map>
#include <chrono>
#include <iostream>
#include <fstream>
//multithreading libraries
#include <omp.h>
#include <mutex>
enum Airport_Event {
    ARRIVAL,
    DEPARTURE
};

struct Airport_Data {
    std::string airport;
    std::string timezone;
    std::string iata;
    std::string icao;
    std::string terminal;
    std::string gate;
    std::string delay;
    std::string scheduled;
    std::string estimated;
    std::string actual;
    std::string estimated_runway;
    std::string actual_runway;
    Airport_Event type;
};

struct Flight_Data {
    std::string flight_date;
    std::string flight_status;
    std::string flight_number;
    std::string flight_iata;
    std::string flight_icao;
    std::string airline_name;
    std::string airline_iata;
    std::string airline_icao;
    Airport_Data departure_data;
    Airport_Data arrival_data;
};

// function headers
Json::Value readJsonFile(std::string fileName);
void loadData(Json::Value jsonData);
std::string jsonValueToString(Json::Value jsonData);
void printUmm(std::unordered_multimap<std::string, Flight_Data> umm);
void searchByAirline(std::string);
void searchByAirport(std::string);

// Define mutex objects to protect shared variables
extern std::mutex airline_mutex;
extern std::mutex airport_mutex;
extern std::unordered_multimap<std::string, Flight_Data> airline_multimap;
extern std::unordered_multimap<std::string, Flight_Data> airport_multimap;


#endif