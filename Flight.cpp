//
// Created by fotop on 19/11/2023.
//

#include "Flight.h"

Flight::Flight() {
    flightNumb = "";
    plane = "";
    weatherData = "";
    date = Date();
    airline = nullptr;
    airpOrig = nullptr;
    airpDest = nullptr;
}

Flight::Flight(const std::string &_flightNumb, Airline *airline, Airport *airpOrig, Airport *airpDest,
               const std::string &_plane, const std::string &_weatherData, const Date &_date) : flightNumb(_flightNumb),
                                                                                           plane(_plane),
                                                                                           weatherData(_weatherData),
                                                                                           date(_date),
                                                                                           airline(airline),
                                                                                           airpOrig(airpOrig),
                                                                                           airpDest(airpDest) {}

Flight::Flight(const std::string &_flightNumb, Airport *_airpOrig, Airport *_airpDest, const std::string &_plane, const std::string &_weatherData, const Date &_date) :
        flightNumb(_flightNumb), airpOrig(_airpOrig), airpDest(_airpDest), plane(_plane), weatherData(_weatherData), date(_date) {}

Flight::Flight(const Flight &other) {
    if (this != &other){
        this->flightNumb = other.flightNumb;
        this->plane = other.plane;
        this->weatherData = other.weatherData;
        this->date = other.date;
        this->airline = other.airline;
        this->airpOrig = other.airpOrig;
        this->airpDest = other.airpDest;
    }
    else
        throw std::invalid_argument("---ERROR--- in Flight(const Flight &other): Both objects are allocated in the same place.");
}

void Flight::setAirline(Airline *airline) {
    Flight::airline = airline;
}

void Flight::setAirpOrig(Airport *airpOrig) {
    Flight::airpOrig = airpOrig;
}

void Flight::setAirpDest(Airport *airpDest) {
    Flight::airpDest = airpDest;
}

const std::string &Flight::getFlightNumb() const {
    return flightNumb;
}

Airline *Flight::getAirline() const {
    return airline;
}

Airport *Flight::getAirpOrig() const {
    return airpOrig;
}

Airport *Flight::getAirpDest() const {
    return airpDest;
}

bool Flight::operator==(Flight &other) {
    if (this->flightNumb == other.flightNumb)
        return true;
    return false;
}

const std::string & Flight::getWeatherData() const {
    return weatherData;
}

const Date &Flight::getDate() const {
    return date;
}

const std::string &Flight::getPlane() const {
    return plane;
}
