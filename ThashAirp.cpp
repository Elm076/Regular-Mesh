//
// Created by Adrian on 11/12/2023.
//

#include "ThashAirp.h"
#include "math.h"

int ThashAirp::hash(unsigned long key, unsigned int attempt) {
    //h1(x)
    //int prime1 = 7079;
    //return ((key % maxElements) + (attempt*((key%prime1)+1)))%maxElements;

    //h2(x)
    //int prime2 = 997;
    //return ((key%maxElements)+(attempt*(prime2-(key%prime2)+1)))%maxElements;

    //h3(x)
    return (key%maxElements+attempt * (unsigned int)sqrt(key + attempt*attempt))%maxElements;

    //h4(x)
    //return (key+attempt*attempt)%maxElements;
}

unsigned long int ThashAirp::doubleDisp(unsigned long key, unsigned int attempt) const {
    //return (key % maxElements + attempt * (unsigned int)sqrt(key + attempt*attempt)) % maxElements;
    return ((key +attempt^2) % maxElements) + attempt * abs((int)((maxElements * (key * ((unsigned int)sqrt(5)-1)/2) % 1))) % maxElements;
}

int ThashAirp::nextPrime(int number) {
    bool isPrime = false;
    while(!isPrime){
        number++;
        bool check = true;
        for( unsigned int i = 2; i <= sqrt(number) and check; i++){
            if (number%i == 0){
                check == false;
            }
        }
        if (check){
            return number;
        }
    }
    return -1;
}





ThashAirp::ThashAirp():
        size(0),
        maxElements(0),
        maxCollisions(0),
        collisions10(0),
        totalCollisions(0),
        lambda(0)
{vector = std::vector<Square>();}

ThashAirp::ThashAirp(unsigned int _maxElements, float _lambda):
        size(0),
        maxCollisions(0),
        collisions10(0),
        totalCollisions(0)
{   maxElements = nextPrime(static_cast<int>(_maxElements/_lambda));
    vector = std::vector<Square>(maxElements);}

ThashAirp::ThashAirp(const std::vector<Square> &vector, unsigned int tableSize, unsigned int maxElements,
                     unsigned int maxCollisions, unsigned int collisions10, unsigned int totalCollision,
                     float lambda):
        vector(vector),
        size(tableSize),
        maxElements(maxElements),
        maxCollisions(maxCollisions),
        collisions10(collisions10),
        totalCollisions(totalCollisions),
        lambda(lambda)
{}

ThashAirp::ThashAirp(const ThashAirp &other):
        size(other.size),
        maxElements(other.maxElements),
        maxCollisions(other.maxCollisions),
        collisions10(other.collisions10),
        totalCollisions(other.totalCollisions),
        lambda(other.lambda)
{}

unsigned long ThashAirp::djb2(std::string str) {
    unsigned long hash = 5381;
    for(unsigned int i = 0; i < str.length(); i++){
        hash = ((hash << 5) + hash) + str[i];
    }
    return hash;
}

ThashAirp& ThashAirp::operator=(const ThashAirp &other) {
    if (this == &other){
        throw std::invalid_argument("--ERROR--In ThashAirp::operator= : Both objects are allocated in the same memory direction");
    }
    else{
        this->size              = other.size;
        this->maxElements       = other.maxElements;
        this->maxCollisions     = other.maxCollisions;
        this->collisions10      = other.collisions10;
        this->totalCollisions   = other.totalCollisions;
        this->lambda            = other.lambda;
        this->vector            = other.vector;
        return *this;
    }
}

bool ThashAirp::push(std::string &key, Airport &airport) {
    unsigned int attempt = 0;
    int index;
    index = hash(djb2(key),attempt);
    while (vector[index].state == taken){
        if (vector[index].airport.getIata() == key){
            return false;
        }
        attempt++;
        index = hash(djb2(key),attempt);
    }
    if (attempt > 10){
        collisions10++;
    }
    if (attempt > maxCollisions){
        maxCollisions = attempt;
    }
    totalCollisions += attempt;
    vector[index].airport = airport;
    vector[index].state = taken;
    size++;
    return true;
}

Airport* ThashAirp::search(std::string &key) {
    unsigned int attempt = 0;
    int index;
    index = hash(djb2(key),attempt);
    while (vector[index].state == taken or vector[index].state == deleted){
        if (vector[index].state == taken){
            if (vector[index].airport.getIata() == key){
                return &vector[index].airport;
            }
        }
        attempt++;
        index = hash(djb2(key),attempt);
    }
    return nullptr;
}

bool ThashAirp::pop(std::string &key) {
    unsigned int attempt = 0;
    int index;
    index = hash(djb2(key),attempt);
    while (vector[index].state == taken or vector[index].state == deleted){
        if (vector[index].state == taken){
            if (vector[index].airport.getIata() == key){
                vector[index].state == deleted;
                vector[index].airport = Airport();
                size--;
                return true;
            }
        }
        attempt++;
        index = hash(djb2(key),attempt);
    }
    return false;
}

std::vector<Airport> ThashAirp::getAirports() {
    std::vector<Airport> result;
    for (unsigned int i = 0; i < vector.size(); i++){
        if (vector[i].state == taken){
            result.push_back(vector[i].airport);
        }
    }
    return result;
}

unsigned int ThashAirp::getMaxColisiones() {
    return maxCollisions;
}

unsigned int ThashAirp::getNumMax10() {
    return collisions10;
}

float ThashAirp::getAverageCollisions() {
    return (float)totalCollisions/size;
}

unsigned int ThashAirp::getTotalCollisions() {
    return  totalCollisions;
}

float ThashAirp::getChargeFactor() {
    lambda = (float)size/maxElements;
    return lambda;
}

unsigned int ThashAirp::getSize() {
    return size;
}

