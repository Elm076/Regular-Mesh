//
// Created by Adrian on 11/12/2023.
//

#ifndef HASH_TABLE_THASHAIRP_H
#define HASH_TABLE_THASHAIRP_H

#include "Airport.h"
#include "vector"


class ThashAirp {
private:

    enum State{
        empty = 0,
        taken = 1,
        deleted = 2
    };

    class Square{
    public:
        Airport airport;
        State state;

        Square():
            state(empty){}
    };

    std::vector<Square> vector;
    unsigned int size;
    unsigned int maxElements;
    unsigned int maxCollisions;
    unsigned int collisions10;
    unsigned int totalCollisions;
    float lambda;


    int hash(unsigned long key, unsigned int attempt);
    //comment this IMPORTANT
    unsigned long int doubleDisp(unsigned long int key,unsigned int attempt) const;

    int nextPrime(int number);


public:
    ThashAirp();

    ThashAirp(const std::vector<Square> &vector, unsigned int tableSize, unsigned int maxElements,
              unsigned int maxCollisions, unsigned int collisions10, unsigned int totalCollisions,
              float lambda);

    ThashAirp(unsigned int maxElements, float lambda=0.7);

    ThashAirp(const ThashAirp &other);

    unsigned long djb2(std::string str);

    ThashAirp& operator=(const ThashAirp &other);

    bool push(std::string &key, Airport &airport);

    Airport* search(std::string &clave);

    bool pop(std::string &key);

    unsigned int getSize();

    unsigned int getMaxColisiones();

    unsigned int getNumMax10();

    float getAverageCollisions();

    unsigned int getTotalCollisions();

    float getChargeFactor();

    unsigned int getSizeTable();

    void showTableState();

    std::vector<Airport> getAirports();

    ~ThashAirp() = default;

};


#endif //HASH_TABLE_THASHAIRP_H
