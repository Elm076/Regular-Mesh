//
// Created by fotop on 19/11/2023.
//

#ifndef STL_AIRPORT_FLIGHT_H
#define STL_AIRPORT_FLIGHT_H

#include "Airline.h"
#include "Airport.h"
#include "fecha.h"

typedef Fecha Date;
class Airline;

class Flight {
private:
    std::string flightNumb;
    std::string plane;
    std::string weatherData;
    Date date;
    Airline *airline;
    Airport *airpOrig;
    Airport *airpDest;

public:
    Flight();

    Flight(const std::string &_flightNumb,Airline *airline, Airport *airpOrig, Airport *airpDest, const std::string &_plane, const std::string &_weatherData, const Date &_date);

    Flight(const std::string &_flightNumb, Airport *airpOrig, Airport *airpDest, const std::string &_plane, const std::string &_weatherData, const Date &_date);

    Flight(const Flight& other);

    void setAirline(Airline *airline);

    void setAirpOrig(Airport *airpOrig);

    const Date &getDate() const;

    void setAirpDest(Airport *airpDest);

    const std::string &getFlightNumb() const;

    Airline *getAirline() const;

    Airport *getAirpOrig() const;

    Airport *getAirpDest() const;

    bool operator==(Flight& other);

    const std::string & getWeatherData() const;

    const std::string &getPlane() const;
};



#endif //STL_AIRPORT_FLIGHT_H
