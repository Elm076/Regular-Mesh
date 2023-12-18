

#ifndef PR1_CD_AIRPORT_H
#define PR1_CD_AIRPORT_H

/**
 * @author Adrián González Pérez agp00118@red.ujaen.es
 */

#include <string>
#include <iostream>
#include "UTM.h"

/**
 * @brief Airport class. It will store id, iata, type, name, location, continent and country iso associated to an airport
 * @class Class to store airports
 */
class Airport {
private:
    int id;
    std::string iata;
    std::string type;
    std::string name;
    UTM location;
    std::string continent;
    std::string country_iso;
public:
    Airport();
    explicit Airport(int _id);
    explicit Airport(std::string _iata);
    Airport(int _id, std::string _iata, std::string _type, std::string _name, UTM _location, std::string _continent, std::string _country_iso);

    const int &getId() const;
    void setId(const int &id);

    const std::string &getIata() const;
    void setIata(const std::string &_iata);

    const std::string &getType() const;
    void setType(const std::string &type);

    const std::string &getName() const;
    void setName(const std::string &name);

    const UTM &getLocation() const;
    void setLocation(const UTM &location);

    const std::string &getContinent() const;
    void setContinent(const std::string &continent);

    const std::string &getCountryIso() const;
    void setCountryIso(const std::string &countryIso);

    bool operator<(const Airport& origin);
    bool operator>(const Airport& origin);
    bool operator==(const Airport& origin);

};


#endif //PR1_CD_AIRPORT_H
