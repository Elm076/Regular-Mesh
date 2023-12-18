

#include "Airport.h"

/**
 * @brief Default constructor; All empty
 * @return Empty object of Airport
 */
Airport::Airport() {
    id = 0;
    iata = "";
    type = "";
    name = "";
    location = UTM();
    continent = "";
    country_iso = "";
}

/**
 * @brief Constructor that uses id to be built
 * @param _id id to construct Airport.id
 * @return Airport object with an specific id
 */
Airport::Airport(int _id) {
    this->id = _id;
    iata = "";
    type = "";
    name = "";
    location = UTM();
    continent = "";
    country_iso = "";
}

Airport::Airport(std::string _iata) {
    id = 0;
    this->iata = _iata;
    type = "";
    name = "";
    location = UTM();
    continent = "";
    country_iso = "";
}

/**
 * @brief Constructor that initialize all the attributes specified in param values
 * @param _id
 * @param _iata
 * @param _type
 * @param _name
 * @param _location
 * @param _continent
 * @param _country_iso
 * @return Airport object created with all the param values
 */
Airport::Airport(int _id, std::string _iata, std::string _type, std::string _name, UTM _location,
                 std::string _continent, std::string _country_iso) {
    id = _id;
    iata = _iata;
    type = _type;
    name = _name;
    location = _location;
    continent = _continent;
    country_iso = _country_iso;
}

const int &Airport::getId() const {
    return id;
}

void Airport::setId(const int &id) {
    Airport::id = id;
}

const std::string &Airport::getIata() const {
    return iata;
}

void Airport::setIata(const std::string &_iata) {
    Airport::iata = _iata;
}

const std::string &Airport::getType() const {
    return type;
}

void Airport::setType(const std::string &type) {
    Airport::type = type;
}

const std::string &Airport::getName() const {
    return name;
}

void Airport::setName(const std::string &name) {
    Airport::name = name;
}

const UTM &Airport::getLocation() const {
    return location;
}

void Airport::setLocation(const UTM &location) {
    Airport::location = location;
}

const std::string &Airport::getContinent() const {
    return continent;
}

void Airport::setContinent(const std::string &continent) {
    Airport::continent = continent;
}

const std::string &Airport::getCountryIso() const {
    return country_iso;
}

void Airport::setCountryIso(const std::string &countryIso) {
    country_iso = countryIso;
}

/**
 * @brief < operator that compares two Airport objects by their ids
 * @param origin Airport object
 * @return TRUE if this->id is lower than origin.id value. FALSE if not
 */
bool Airport::operator<(const Airport &origin) {
    if (this->iata < origin.iata) {
        return true;
    }
    return false;

}

/**
 * @brief < operator that compares two Airport objects by their ids
 * @param origin Airport object
 * @return TRUE if this->id is greater than origin.id value. FALSE if not
 */
bool Airport::operator>(const Airport &origin) {
    if (this->iata > origin.iata) {
        return true;
    }
    return false;

}

/**
 * @brief < operator that compares two Airport objects by their ids
 * @param origin Airport object
 * @return True if this->id is equal that origin.id value. FALSE if not
 */
bool Airport::operator==(const Airport &origin) {
    if (this->iata == origin.iata){
        return true;
    }
    return false;
}


