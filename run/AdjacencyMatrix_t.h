#pragma once
#include "CitiesList_t.h"

/* Map element - the symbol of element and a bool indicating if it has been visited */
class TheMapElement_t {
public:
    char Map = SPACE;
    size_t Dist = 0;
    TheMapElement_t() {};
    ~TheMapElement_t() {};
};

/* The class containing the ListOfCities and the number of them (NumberOfCities) in the Map, constains also the Adjacency Matrix of distances between cities */
/* and TheRoad - that is a matrix which elements are kistofcities which would be the path between cities */
class AdjacencyMatrix_t {
private:
    CitiesList_t ListOfCities;
    size_t** AdjMatrix;
    CitiesList_t** TheRoad;
    size_t NumberOfCities = 0;
public:
    AdjacencyMatrix_t() {
        AdjMatrix = nullptr;
        TheRoad = nullptr;
    };
    void Printall();
    void PrintCities();
    void InitializeMatrix();
    void DeleteMatrix();
    void AddCity(String_t CityName);
    void AddCity(String_t CityName, Position_t Pos);
    size_t FindAnIndexOftheCity(String_t CityName);
    size_t FindAnIndexOftheCity(Position_t Pos);
    Position_t GetPositionOftheCityAtIndex(size_t Index);
    size_t** GetAdjMatrix() { return AdjMatrix; };
    CitiesList_t** GetRoadMatrix() { return TheRoad; };
    String_t GetNameOftheCityAtIndex(size_t Index);
    CityNode_t* operator[](size_t Index);
    CityNode_t* GetCityNodeByName(String_t CityName);
    CityNode_t* GetCityNodeByPosition(Position_t Pos);
    CityNode_t* GetCityNodeByIndex(size_t Index);
    size_t GetNumberOfCities() { return NumberOfCities; };
    ~AdjacencyMatrix_t() {
        if (AdjMatrix != nullptr) {
            for (size_t i = 0; i < NumberOfCities; i++) {
                delete[] AdjMatrix[i];
            };
            delete[] AdjMatrix;
        };
        if (TheRoad != nullptr) {
            for (size_t i = 0; i < NumberOfCities; i++) {
                delete[] TheRoad[i];
            };
            delete[] TheRoad;
        };
    };
};

/* Print only names of Cities - the Road */
void AdjacencyMatrix_t::PrintCities() {
    ListOfCities.PrintCities();
};

/* Print all Information about the Adjacency Matrix */
void AdjacencyMatrix_t::Printall() {
    ListOfCities.PrintAll();
    printf("\n");
    for (int i = 0; i < NumberOfCities; i++) {
        for (int j = 0; j < NumberOfCities; j++) {
            printf("%zu ", AdjMatrix[i][j]);
        };
        printf("\n");
    };
};

/* Get node by name, returns nullptr if no node like that */
CityNode_t* AdjacencyMatrix_t::GetCityNodeByName(String_t CityName) {
    return ListOfCities.FindNode(CityName);
};

/* Get node by position, returns nullptr if no node found */
CityNode_t* AdjacencyMatrix_t::GetCityNodeByPosition(Position_t Pos) {
    return ListOfCities.FindNodeByPosition(Pos);
};

/* returns 0 if not found, Starting position = 1 */
size_t AdjacencyMatrix_t::FindAnIndexOftheCity(String_t CityName) {
    return ListOfCities.FindIndexOfNode(CityName);
};

/* returns 0 if not found, Starting position = 1 */
size_t AdjacencyMatrix_t::FindAnIndexOftheCity(Position_t Pos) {
    return ListOfCities.FindIndexOfNode(Pos);
};

/* returns position of the city at index, if not found or the city does not has assigned position returns {-1, -1}, Starting position = 1 */
Position_t AdjacencyMatrix_t::GetPositionOftheCityAtIndex(size_t Index) {
    CityNode_t* tmp = ListOfCities.FindNodeAtIndex(Index);
    if (tmp) return tmp->PositionOftheCity;
    return { -1, -1 };
};

/* Returns name of the city at index Index, Starting position = 1 */
String_t AdjacencyMatrix_t::GetNameOftheCityAtIndex(size_t Index) {
    String_t Str;
    CityNode_t* tmp = ListOfCities.FindNodeAtIndex(Index);
    if (tmp) return tmp->name;
    return Str;
};

/* Returns City Node at index Index, Starting position = 1 */
CityNode_t* AdjacencyMatrix_t::GetCityNodeByIndex(size_t Index) {
    return ListOfCities[Index];
};

/* operator [], Starting Index = 1 */
CityNode_t* AdjacencyMatrix_t::operator[](size_t Index) {
    return ListOfCities[Index];
};

/* Add the city to the list */
void AdjacencyMatrix_t::AddCity(String_t CityName) {
    ListOfCities.AddNode(CityName);
    NumberOfCities++;
};

/* Add the city to the list */
void AdjacencyMatrix_t::AddCity(String_t CityName, Position_t Pos) {
    ListOfCities.AddNode(CityName, Pos);
    NumberOfCities++;
};

/* Delete the adj matrix */
void AdjacencyMatrix_t::DeleteMatrix() {
    if (AdjMatrix != nullptr) {
        for (size_t i = 0; i < NumberOfCities; i++) {
            delete[] AdjMatrix[i];
        };
        delete[] AdjMatrix;
    };
    if (TheRoad != nullptr) {
        for (size_t i = 0; i < NumberOfCities; i++) {
            delete[] TheRoad[i];
        };
        delete[] TheRoad;
    };
    AdjMatrix = nullptr;
    TheRoad = nullptr;
};

/* Initialize the adj matrix */
void AdjacencyMatrix_t::InitializeMatrix() {
    DeleteMatrix();
    AdjMatrix = new size_t * [NumberOfCities];
    for (size_t i = 0; i < NumberOfCities; i++) {
        AdjMatrix[i] = new size_t[NumberOfCities];
        for (size_t j = 0; j < NumberOfCities; j++) {
            AdjMatrix[i][j] = 0;
        };
    };

    TheRoad = new CitiesList_t * [NumberOfCities];
    for (size_t i = 0; i < NumberOfCities; i++) {
        TheRoad[i] = new CitiesList_t[NumberOfCities];
    };
};