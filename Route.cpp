//
// Created by fotop on 22/10/2023.
//

#include "Route.h"

const std::string &Route::getCompany() const {
    return company->getIcao();
}

void Route::setAirline(const std::string &airline) {
    Route::company->setIcao(airline);
}

Airport *Route::getOrigin() const {
    return origin;
}

void Route::setOrigin(Airport *origin) {
    Route::origin = origin;
}

Airport *Route::getDestination() const {
    return destination;
}

void Route::setDestination(Airport *destination) {
    Route::destination = destination;
}

Route::Route(Airline* _company, Airport* _origin, Airport* _destination) :
        company(_company),
        origin(_origin),
        destination(_destination)
{}

Route::Route(const Route &other) {
    this->company = other.company;
    this->origin = other.origin;
    this->destination = other.destination;
    this->company = other.company;
}

unsigned int Route::getFlightsNum() {
    return flightRoute.size();
}

bool Route::addFlight(Flight& fli) {
    if (company == fli.getAirline()
        and
        origin == fli.getAirpOrig()
        and
        destination == fli.getAirpDest()) {

        flightRoute.push_back(&fli);
        return true;
    }
    return false;
}

std::list<Flight*> Route::getFlights() {
    return flightRoute;
}

Route::~Route() = default;
