//
// Created by fotop on 07/11/2023.
//

#ifndef AVL_AIRLINE_H
#define AVL_AIRLINE_H

#include <string>
#include <vector>
#include <map>
#include <deque>
#include "Route.h"
#include "Flight.h"
#include "fecha.h"

typedef Fecha Date;

class Route;

class Airline {
private:
    unsigned int id;
    std::string icao;
    std::string name;
    std::string country;
    bool active;
    std::multimap<std::string,Flight> flights;
    std::deque<Route*> airRoutes;
public:

    Airline();

    Airline(unsigned int _id, std::string _icao, std::string _name,
            std::string _country, bool _active);

    Airline(std::string _icao);

    bool operator!=(const Airline& other);

    bool operator==(const Airline& other);

    bool operator>(const Airline& other);

    bool operator<(const Airline& other);

    friend std::ostream& operator<<(std::ostream &os, const Airline& object);

    const std::string &getIcao() const;

    unsigned int getId() const;

    const std::string &getName() const;

    const std::string &getCountry() const;

    bool isActive() const;

    void setIcao(const std::string &icao);

    std::vector<Airport>& getOrigAirports();

    std::vector<Route>& getAirportRoutes(std::string iataAirport);

    void linkAirRoute(Route* r);

    Flight* addFlight(Flight);

    std::vector<Flight> getFlights(std::string fNumber);

    std::vector<Flight> getFlights(const Date& beginDate, const Date& endDate);

    void setDownAirline();
};


#endif //AVL_AIRLINE_H
