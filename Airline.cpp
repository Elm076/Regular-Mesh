//
// Created by fotop on 07/11/2023.
//

#include "Airline.h"

Airline::Airline() {
    id = 0;
    icao = "";
    name = "";
    country = "";
    active = false;
    airRoutes = std::deque<Route*>();
}

Airline::Airline(unsigned int _id, std::string _icao, std::string _name, std::string _country, bool _active):
    id(_id),
    icao(_icao),
    name(_name),
    country(_country),
    active(_active)
    {}

    Airline::Airline(std::string _icao):
    icao(_icao)
    {   id = 0;
        name = "";
        country = "";
        active = false;
    }
bool Airline::operator==(const Airline &other) {
    if (this->icao == other.icao)
        return true;
    return false;
}

bool Airline::operator!=(const Airline &other) {
    if (this->icao != other.icao)
        return true;
    return false;
}

bool Airline::operator<(const Airline &other) {
    if (this->icao < other.icao)
        return true;
    return false;
}

bool Airline::operator>(const Airline &other) {
    if (this->icao > other.icao)
        return true;
    return false;
}

std::ostream& operator<<(std::ostream &os, const Airline& object) {
    os << object.icao;
    return os;
}

const std::string &Airline::getIcao() const {
    return icao;
}

void Airline::setIcao(const std::string &icao) {
    Airline::icao = icao;
}

std::vector<Airport>& Airline::getOrigAirports() {
    std::vector<Airport> result;
    for(unsigned int i = 0; i < airRoutes.size(); i++){
        result.push_back(*airRoutes[i]->getOrigin());
    }

    return result;
}

std::vector<Route>& Airline::getAirportRoutes(std::string iataAirport) {
    std::vector<Route> result;
    for(unsigned int i = 0; i < airRoutes.size(); i++){
        if (airRoutes[i]->getOrigin()->getIata() == iataAirport
            or
            airRoutes[i]->getDestination()->getIata() == iataAirport)
            result.push_back(*airRoutes[i]);
    }
    return result;
}

void Airline::linkAirRoute(Route* r) {
    airRoutes.push_back(r);
}

bool Airline::isActive() const {
    return active;
}

unsigned int Airline::getId() const {
    return id;
}

const std::string &Airline::getName() const {
    return name;
}

const std::string &Airline::getCountry() const {
    return country;
}

Flight* Airline::addFlight(Flight fli) {
    std::string fliIcao(fli.getFlightNumb().substr(0,3));
    Flight nullFlight = Flight();
    if (fli == nullFlight or fliIcao != icao or fli.getAirline() != this)
        return nullptr;
    else{
        Flight newFlight(fli);
        auto new_insert = std::pair<std::string,Flight>(newFlight.getFlightNumb(),newFlight);
        flights.insert(new_insert);

        auto it = airRoutes.begin();

        while(it != airRoutes.end()){
            if (it.operator*()->getOrigin() == new_insert.second.getAirpOrig()
                and
                it.operator*()->getDestination() == new_insert.second.getAirpDest()){

                it.operator*()->addFlight(newFlight);
                break;
            }
            it++;
        }

        return &flights.find(fliIcao)->second;
    }
}

std::vector<Flight> Airline::getFlights(std::string fNumber) {
    std::vector<Flight> result;
    auto range = flights.equal_range(fNumber);

    for (auto it = range.first; it != range.second; it++){
        result.push_back(it->second);
    }
    return result;
}

std::vector<Flight> Airline::getFlights(const Date& beginDate, const Date& endDate) {
    std::vector<Flight> result;
    auto it = flights.begin();
    while (it != flights.end()){
        if(it->second.getDate() < endDate and !(it->second.getDate() < beginDate)){
            result.push_back(it->second);
        }
        it++;
    }
    return result;
}

void Airline::setDownAirline() {
    airRoutes = std::deque<Route*>();
}
