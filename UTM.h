

#ifndef PR1_CD_UTM_H
#define PR1_CD_UTM_H

/**
 * @author Adrián González Pérez agp00118@red.ujaen.es
 */

#include "vector"
#include <string>

/**
 * @brief Class to store global coordinates in objects (latitude and longitude)
 * @class UTM class
 */
class UTM {
private:
    std::string latitude;
    std::string longitude;

public:
    UTM();
    UTM(std::string _latitude, std::string _longitude);
    void setLatitude(std::string _latitude);
    void setLongitude(std::string _longitude);
    void setLocation(std::string _latitude, std::string _longitude);
    std::string getLatitude() const;
    std::string getLongitude() const;
    std::vector<std::string> getLocation() const;



};


#endif //PR1_CD_UTM_H
