//
// Created by Adrian on 18/12/2023.
//

#ifndef HASH_TABLE_REGULARMESH_H
#define HASH_TABLE_REGULARMESH_H

#include <list>
#include <vector>
#include <limits>

template<typename T>
class RegularMesh {
private:
    template<typename U>
    class Square{
    public:
        std::list<U> elements;
        friend class RegularMesh<T>;

        Square(): elements(0) {}

        void push(const U &data) { elements.push_back(data); }

        T *search(const U &data) {
            typename std::list<U>::iterator it;
            it = elements.begin();
            for (; it != elements.end(); ++it){
                if (*it == data)
                    return &(*it);
            }
            return 0;
        }

        bool pop(const T &data){
            typename std::list<T>::iterator it;
            it = elements.begin();
            for (; it != elements.end(); ++it){
                if (*it == data) {
                    elements.erase(it);
                    return true;
                }
            }
            return false;
        }
    };

    unsigned int size, nDiv;
    float xMin, yMin, xMax, yMax; // Tamaño real global
    float squareSizeX, squareSizeY; // Tamaño real de cada casilla
    std::vector<std::vector<Square<T> > > mesh; // Vector 2D de casillas

    Square<T> *getSquare(float x, float y);

public:
    RegularMesh();

    RegularMesh(float aXMin, float aYMin, float aXMax, float aYMax, int aNDiv);

    void push(float x, float y, const T &dato);

    T *search(float x, float y, const T &dato);

    bool pop(float x, float y, const T &dato);

    unsigned int maxElementsPerSquare();

    float averageElementsPerSquare();
};

template<typename T>
RegularMesh<T>::RegularMesh():
    nDiv(0),
    size(0),
    xMin(0),
    xMax(0),
    yMin(0),
    yMax(0),
    squareSizeX(0),
    squareSizeY(0),
    mesh()
{}

template<typename T>
RegularMesh<T>::RegularMesh(float aXMin, float aYMin, float aXMax, float aYMax, int aNDiv) :
        xMin(aXMin), yMin(aYMin), xMax(aXMax), yMax(aYMax){
    squareSizeX = (xMax - xMin)/aNDiv;
    squareSizeY = (yMax - yMin)/aNDiv;
    nDiv = aNDiv;
    size = 0;
    mesh.insert(mesh.begin(), aNDiv, std::vector<Square<T> >(aNDiv));
}

template<typename T>
RegularMesh<T>::Square<T> *RegularMesh<T>::getSquare(float x, float y) {
    int i = (x - xMin) / squareSizeX;
    int j = (y - yMin) / squareSizeY;
    return &mesh[i][j];
}

template<typename T>
void RegularMesh<T>::push(float x, float y, const T& dato){
    Square<T> *sq = getSquare(x,y);
    sq->push(dato);
    size++;
}

template<typename T>
T* RegularMesh<T>::search(float x, float y, const T &data) {
    Square<T> sq = getSquare(x,y);
    return sq.search(data);
}

template<typename T>
bool RegularMesh<T>::pop(float x, float y, const T& dato){
    Square<T> *sq = getSquare(x,y);
    return sq->pop(dato);
}

template<typename T>
unsigned int RegularMesh<T>::maxElementsPerSquare() {
    float max = std::numeric_limits<float>::min();
    for(float i = xMin; i < xMax; i += squareSizeX){
        for(float j = yMin; j < yMax; j += squareSizeY){
            Square<T>* iterationSquare = getSquare(i,j);
            if (iterationSquare->elements.size() > max)
                max = iterationSquare->elements.size();
        }
    }
    return max;
}

template<typename T>
float RegularMesh<T>::averageElementsPerSquare() {
    float result = (float)size/(nDiv*nDiv);
    return result;
}
#endif //HASH_TABLE_REGULARMESH_H
