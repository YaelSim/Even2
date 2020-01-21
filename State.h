//
// Created by yael on 14/01/2020.
//

#ifndef EVEN2_STATE_H
#define EVEN2_STATE_H

#include <vector>

template <class T>
class State {
private:
    T vertexIndex;
    double vertexValue; //This field actually represents the COST of each vertex
    double subCost;
    State* fatherVertex;
    bool isVisited;
    int xPosition;
    int yPosition;
public:
    State(T indexOfVertex, double valOfVertex) {
        this->vertexIndex =  indexOfVertex;
        this->vertexValue = valOfVertex;
        this->subCost = valOfVertex;
        this->fatherVertex = nullptr;
        isVisited = false;
        this->xPosition = -1;
        this->yPosition = -1;
    }

    State* getFatherVertex() {
        return this->fatherVertex;
    }

    void setSubCost(double cost) {
        this->subCost = cost;
    }

    double getSubCost() {
        return this->subCost;
    }

    void setFatherVertex(State<T>* state) {
        this->fatherVertex = state;
    }

    T getVertexIndex() {
        return this->vertexIndex;
    }

    double getVertexValue() {
        return this->vertexValue;
    }

    void setIsVisited(bool visited) {
        this->isVisited = visited;
    }

    bool getIsVisited() {
        return this->isVisited;
    }

    bool isEqual(State<T>* state) {
        if (state->getVertexValue() == this->getVertexValue()) {
            if (state->getIsVisited() == this->getIsVisited()) {
                if (state->getVertexIndex() == this->getVertexIndex()) {
                    return true;
                }
            }
        }
        return false;
    }

    int getX() {
        //T vertex = this->vertexIndex;
        //this->xPosition = stoi(vertex.substr(0, vertex.find(',')));
        return this->xPosition;
    }

    int getY() {
        //T vertex = this->vertexIndex;
        //this->yPosition = stoi(vertex.substr(vertex.find(',') + 1));
        return this->yPosition;
    }

    void setXAndYPositions(int x, int y) {
        this->xPosition = x;
        this->yPosition = y;
    }
};

#endif //EVEN2_STATE_H
