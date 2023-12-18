//
// Created by fotop on 22/10/2023.
//

#ifndef PR1_CD_ROUTE_H
#define PR1_CD_ROUTE_H

#include <iostream>
#include "Airport.h"
#include "Airline.h"
#include <list>
#include "Flight.h"

class Airline;
class Flight;
class Route {
private:

    Airport* origin;
    Airport* destination;
    Airline* company;
    std::list<Flight*> flightRoute;

public:

    Route() {
        origin = nullptr;
        destination = nullptr;
        company = nullptr;
        flightRoute = std::list<Flight*>();
    }

    Route(Airline* company, Airport* _origin, Airport* _destination);

    Route(const Route& other);

    const std::string &getCompany() const;

    void setAirline(const std::string &airline);

    Airport *getOrigin() const;

    void setOrigin(Airport *origin);

    Airport *getDestination() const;

    void setDestination(Airport *destination);

    unsigned int getFlightsNum();

    std::list<Flight*> getFlights();

    bool addFlight(Flight& fli);

    ~Route();

};


#endif //PR1_CD_ROUTE_H
