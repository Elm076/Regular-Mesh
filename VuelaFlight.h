//
// Created by fotop on 24/10/2023.
//

#ifndef PR1_CD_VUELAFLIGHT_H
#define PR1_CD_VUELAFLIGHT_H

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <map>
#include <set>
#include "ThashAirp.h"
#include "Airport.h"
#include "Route.h"
#include "Airline.h"
#include "Flight.h"

class VuelaFlight {
private:
    ThashAirp airports = ThashAirp(76368,0.7);
    std::multimap<std::string,Route> origRoutes;
    std::multimap<std::string,Route*> destRoutes;
    std::map<std::string,Airline> airlines;
public:
    VuelaFlight() = default;

    VuelaFlight(std::string airports_file, std::string routes_file, std::string airlines_file);

    const std::multimap<std::string,Route> &getOrigRoutes() const;

    const std::multimap<std::string,Route> &getDestRoutes() const;

    Airport& searchAirport(std::string iataAirport);

    unsigned int getNumAirports();

    Route& origDestRoutesSearch(const std::string& airportIataOrig, const std::string& airportIataDest);

    std::vector<Route> origRoutesSearch(std::string airportIataOrig);

    std::vector<Airport> countryAirportSearch(std::string country);

    void addNewRoute(std::string origAirportIata, std::string destAirportIata, std::string airline);

    Airline& searchAirline(std::string airlineIcao);

    //std::vector<Airline> searchActiveAirline();

    bool flightRegister(std::string fNmber, std::string origAirpIata, std::string destAirpIata, std::string plane, std::string weatherData, Date f);

    void loadFlights(std::string file);

    std::vector<Flight> searchFlights(std::string fNumber);

    std::vector<Flight> flightsOperatedBy(std::string icaoAirline, Date dat);

    std::set<std::string> searchFlightsDestAirp(std::string origCountry, std::string iataDestAirp);

    const std::vector<Airport> getAirports();

    const ThashAirp getAirportsHash();

    void deleteAirport(std::string iataAirport);

    void addAirport(Airport& airp);

    void deleteInactiveAirports();

    void showTableState();

};



#endif //PR1_CD_VUELAFLIGHT_H
