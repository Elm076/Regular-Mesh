

#include <iostream>
#include <string>
#include <ctime>
#include "Dynamic_container.h"
#include "Airport.h"
#include "VuelaFlight.h"

/**
 * @author Adrián González Pérez agp00118@red.ujaen.es
 */

int main() {
    std::cout << ".....Start of the program ....." << std::endl;


    VuelaFlight dataBase("..\\aeropuertos_v3.csv", "..\\rutas_v1.csv", "..\\aerolineas_v1.csv");
    std::cout << std::endl;
    std::cout << "The max num of airports ubicated in a quadrant is " << dataBase.maxAirportsInQuadrant() << std::endl;
    std::cout << "The average num of airports ubicated per quadrant is " << dataBase.averageAirportsPerQuadrant() << std::endl;
    /*
    dataBase.showTableState();

    Airport airpToSearch = dataBase.searchAirport("00AS");
    if(&airpToSearch) {
        std::cout   << "AIRPORT FOUND-- His data:" << std::endl <<
                    "Name " << airpToSearch.getName() << std::endl <<
                    "Type " << airpToSearch.getType() << std::endl <<
                    "Country " << airpToSearch.getCountryIso() << std::endl <<
                    "Continent " << airpToSearch.getContinent() << std::endl;

        dataBase.deleteAirport("00AS");
        dataBase.showTableState();
        if(!&dataBase.searchAirport("00AS")){
            dataBase.addAirport(airpToSearch);
        }
        dataBase.showTableState();
    }

    dataBase.deleteInactiveAirports();
    dataBase.showTableState();

    */
    std::cout << "----- End of the program -----" << std::endl;
}