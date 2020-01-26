//
// Created by yael and linoy on 14/01/2020.
//

#include "Matrix.h"

//Constructor
Matrix::Matrix(vector<string> matrixVec) {
    this->startOfSearchState = nullptr;
    this->endOfSearchState = nullptr;
    this->numOfRows = 0;
    this->numOfCols = 0;
    // call build
    this->matrixMap = this->buildMatrix(matrixVec);
}

//Getter of startOfSearch
State<string> *Matrix::getInitialState() {
    return this->startOfSearchState;
}

//This method returns true if a given state equals to the endOfSearchState
bool Matrix::isGoalState(State<string>* state) {
    return (state->getVertexIndex() == this->endOfSearchState->getVertexIndex());
}

//This method returns a vector of all possible states according to the given currState.
// (state will be defined possible if it's adjacent to the currState and if its' vertex value isn't (-1).
std::vector<State<string>*> Matrix::getAllPossibleStates(State<string>* currState) {
    vector<State<string>*> vec;
    string indexAsString = currState->getVertexIndex();
    int row, col;
    row = stoi(indexAsString.substr(0, indexAsString.find(',')));
    col = stoi(indexAsString.substr((indexAsString.find(',') + 1)));
    //Check borders of rows (from bottom)
    if((row - 1) >= 0) {
        string key = to_string(row - 1) + "," + to_string(col);
        State<string>* getState = this->matrixMap[key];
        if(getState->getVertexValue() != -1) {
            vec.push_back(getState);
        }
    }
    //Check borders of rows (maximum)
    if((row + 1) < this->numOfRows) {
        string key = to_string(row + 1) + "," + to_string(col);
        State<string>* getState = this->matrixMap[key];
        if(getState->getVertexValue() != -1) {
            vec.push_back(getState);
        }
    }
    //Check borders of columns (from bottom)
    if((col - 1) >= 0) {
        string key = to_string(row) + "," + to_string(col - 1);
        State<string>* getState = this->matrixMap[key];
        if(getState->getVertexValue() != -1) {
            vec.push_back(getState);
        }
    }
    //Check borders of columns (maximum)
    if((col + 1) < this->numOfCols) {
        string key = to_string(row) + "," + to_string(col + 1);
        State<string>* getState = this->matrixMap[key];
        if(getState->getVertexValue() != -1) {
            vec.push_back(getState);
        }
    }
    return vec;
}

//This method creates a map according to the given matrixVec.
//This method is called from the Matrix constructor.
unordered_map<string, State<string> *> Matrix::buildMatrix(vector<string> matVec) {
    unordered_map<string, State<string>*> matMap;
    int startFlag = 0;
    string key;
    auto i = matVec.begin();
    while(i != matVec.end()) {
        //Check if buffer is the last 2 lines (the search coordinates) and save them
        if(isItSearchCoordinate(*i)) {
            if(startFlag == 0) {
                setStartOfSearchState(matMap[*i]);
                startFlag = 1;
            } else {
                setEndOfSearchState(matMap[*i]);
                startFlag = 0;
            }
        } else {
            //replace all the commas to spaces. later on we'll remove those spaces - don't worry.
            replace((*i).begin(), (*i).end(), ',', ' ');
            stringstream ss(*i);
            vector<string> array;
            int temp;
            int currentCol = 0;
            while (ss >> temp) {
                array.push_back(to_string(temp));
            }
            auto indexArr = array.begin();
            while (indexArr != array.end()) {
                string currKey = to_string(this->numOfRows) + "," + to_string(currentCol);
                string currValue = *indexArr;

                //Create a tempState according to the currKey and the value in double of currValue.
                State<string>* tempState = new State<string>(currKey, stod(currValue));
                tempState->setXAndYPositions(this->numOfRows, currentCol);
                matMap[currKey] = tempState;

                currentCol++;
                indexArr++;
            }
            this->numOfCols = currentCol;
            this->numOfRows++;
        }
        i++;
    }
    return matMap;
}

//This is a regex function that will return true if a given string is in the following format: "int,int"
bool Matrix::isItSearchCoordinate(string check) {
    regex searchCoordinatesPattern("^[0-9]+(,[0-9]+)$");
    return regex_match(check, searchCoordinatesPattern);
}

void Matrix::setStartOfSearchState(State<string>* state) {
    this->startOfSearchState = state;
}

void Matrix::setEndOfSearchState(State<string>* state) {
    this->endOfSearchState = state;
}

State<string> *Matrix::getGoalState() {
    return this->endOfSearchState;
}
