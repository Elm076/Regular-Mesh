//
// Created by fotop on 27/09/2023.
//

#include "UTM.h"


UTM::UTM() {
    latitude = "-10000";
    longitude  = "-10000";
}

UTM::UTM(std::string _latitude, std::string _longitude) {
    latitude = _latitude;
    longitude = _longitude;
}

void UTM::setLatitude(std::string _latitude) {
    latitude = _latitude;
}

std::string UTM::getLatitude() const {
    return latitude;
}

void UTM::setLongitude(std::string _longitude) {
    longitude = _longitude;
}

std::string UTM::getLongitude() const {
    return longitude;
}

void UTM::setLocation(std::string _latitude, std::string _longitude) {
    latitude = _latitude;
    longitude = _longitude;
}

std::vector<std::string> UTM::getLocation() const {
    std::vector<std::string> location;
    location.push_back(latitude);
    location.push_back(longitude);
    return location;
}

