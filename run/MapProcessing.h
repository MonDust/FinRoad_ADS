#pragma once
#include "GetDistances.h"

/* ---------------------------------------- DIJIKSTRA ALGORITHM --------------------------------------------------- */

/* Find the shortest distance in the current row in Adjacency Matrix */
size_t FindShortestDistance(AdjacencyMatrix_t* TheMatrix, size_t Source, bool* IsVisited) {
    size_t Index = 0;
    size_t dist = 0, Shortest = 0;
    for (size_t i = 1; i <= TheMatrix->GetNumberOfCities(); i++) {
        dist = TheMatrix->GetAdjMatrix()[Source - STARTINGPOSITION][i - STARTINGPOSITION];
        if (dist != 0 && IsVisited[i - STARTINGPOSITION] == 0) {
            if (Shortest == 0) {
                Shortest = dist;
                Index = i;
            }
            else if (Shortest > dist) {
                Shortest = dist;
                Index = i;
            };
        };
    };
    return Index;
};

/* Dijikstra Algorithm that saves the distances into Adjacency Matrix, if already initialized the intersection of the same city = 1, otherwise = 0 */
void DijikstraAlgorithm(AdjacencyMatrix_t* TheMatrix, size_t Source) { /* TO DO: Make it save the road */
    size_t numCities = TheMatrix->GetNumberOfCities(), NumberOfVisited = 1;
    bool* IsVisited = new bool[numCities];
    for (size_t i = 0; i < numCities; i++) {
        if (i >= numCities) break;
        IsVisited[i] = 0;
    };
    //TheMatrix->Printall();
    IsVisited[Source - STARTINGPOSITION] = 1;
    CitiesList_t ListOfCities, FinalListOfCities;
    size_t** AdjMatrix = TheMatrix->GetAdjMatrix();

    size_t distance = 0, CurrentCity = Source;
    while (NumberOfVisited != numCities) {
        for (size_t j = 1; j <= numCities; j++) {
            distance = TheMatrix->GetAdjMatrix()[CurrentCity - STARTINGPOSITION][j - STARTINGPOSITION];
            if (distance != 0) {
                FinalListOfCities.AddTheCitiesList(&TheMatrix->GetRoadMatrix()[CurrentCity - STARTINGPOSITION][j - STARTINGPOSITION]);
                if (AdjMatrix[Source - STARTINGPOSITION][j - STARTINGPOSITION] == 0) {
                    AdjMatrix[Source - STARTINGPOSITION][j - STARTINGPOSITION] = AdjMatrix[Source - STARTINGPOSITION][CurrentCity - STARTINGPOSITION] + distance;
                    TheMatrix->GetRoadMatrix()[Source - STARTINGPOSITION][j - STARTINGPOSITION].CopyTheCitiesList(&FinalListOfCities);
                }
                else if (AdjMatrix[Source - STARTINGPOSITION][j - STARTINGPOSITION] > AdjMatrix[Source - STARTINGPOSITION][CurrentCity - STARTINGPOSITION] + distance) {
                    AdjMatrix[Source - STARTINGPOSITION][j - STARTINGPOSITION] = AdjMatrix[Source - STARTINGPOSITION][CurrentCity - STARTINGPOSITION] + distance;
                    TheMatrix->GetRoadMatrix()[Source - STARTINGPOSITION][j - STARTINGPOSITION].CopyTheCitiesList(&FinalListOfCities); // To final changes
                };
                FinalListOfCities.CopyTheCitiesList(&ListOfCities);
            };
        };
        CurrentCity = FindShortestDistance(TheMatrix, Source, IsVisited);
        if (CurrentCity == 0) break;
        NumberOfVisited++;

        ListOfCities.CopyTheCitiesList(&TheMatrix->GetRoadMatrix()[Source - STARTINGPOSITION][CurrentCity - STARTINGPOSITION]);
        ListOfCities.AddNode(TheMatrix->GetCityNodeByIndex(CurrentCity));
        FinalListOfCities.CopyTheCitiesList(&ListOfCities);

        IsVisited[CurrentCity - STARTINGPOSITION] = 1;
    };
    AdjMatrix[Source - STARTINGPOSITION][Source - STARTINGPOSITION] = 1;
    //TheMatrix->Printall();
    delete[] IsVisited;
};


/* ---------------------------------------- PRINT --------------------------------------------------- */

/* Print the Map */
void PrintMap(TheMapElement_t** TheMap, int width_x, int height_y) {
    printf("\n");
    for (int i = 0; i < width_x; i++) {
        for (int j = 0; j < height_y; j++) {
            printf("%c ", TheMap[i][j].Map);
        };
        printf("\n");
    };
};

/* ---------------------------------------- MAKING ADJACENCY MATRIX --------------------------------------------------- */


void ProcessTheMapByFindingTheEdges(Position_t MapSize, TheMapElement_t** TheMap, AdjacencyMatrix_t* TheMatrix) {
    size_t NumberOfCities = TheMatrix->GetNumberOfCities();
    for (int i = STARTINGPOSITION; i <= NumberOfCities; i++) {
        Position_t CityPos = TheMatrix->GetPositionOftheCityAtIndex(i);
        if (CityPos.x != -1) {
            GetDist(MapSize, TheMap, TheMatrix, CityPos, i);
        };
    };
};


/* ---------------------------------------- CITY NAME --------------------------------------------------- */

/* Check if char is a letter, returns 1 if is, returns 0 if is not */
bool CheckIsLetter(char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return 1;
    return 0;
};

/* Direction that the City Name is written, if the letter is not first nor it is last -> THEWRONGDIR(irection), else either one letter city, or go right or go left to get the rest of the name */
size_t DirectionOfTheCityName(Position_t MapSize, Position_t Pos, TheMapElement_t** TheMap) {
    size_t Direction = STAYSTILL;
    if (Pos.y + 1 < MapSize.y) {
        if (CheckIsLetter(TheMap[Pos.x][Pos.y + 1].Map)) {
            Direction = GOFORWARD;
        };
    };
    if (Pos.y - 1 >= 0) {
        if (CheckIsLetter(TheMap[Pos.x][Pos.y - 1].Map)) {
            if (Direction == STAYSTILL) Direction = GOBACK;
            else Direction = THEWRONGDIR;
        };
    };
    //if (Direction != THEWRONGDIR) cout << Direction << " " << TheMap[Pos.x][Pos.y].Map << "\n";
    return Direction;
};

/* Find the Name of The City in the matrix, returns an empty string if not found */
String_t FindTheName(size_t Direction, Position_t MapSize, Position_t StartPosition, TheMapElement_t** TheMap) {
    char BufferArr[BUFFERSTRING] = {}; BufferArr[0] = '\n';
    String_t Str; bool Flag = 0;
    if (Direction == THEWRONGDIR) return Str; /* if the direction is wrong */
    Position_t CurrPosition = StartPosition;
    char c = TheMap[CurrPosition.x][CurrPosition.y].Map;
    while (c != THEROADMAP && c != THECITYMAP && c != NOTHINGMAP) {
        for (size_t j = 0; j < BUFFERSTRING - SPACEFORENDCHAR; j++) {
            if (CurrPosition.y + Dir[Direction] <= MapSize.y && CurrPosition.y + Dir[Direction] >= 0) {
                if (c != THEROADMAP && c != THECITYMAP && c != NOTHINGMAP) {

                    BufferArr[j] = c;
                    BufferArr[j + 1] = ENDOFSTRING;

                    if (Direction == STAYSTILL) {
                        Flag = 1;       break;
                    };
                    CurrPosition.y += Dir[Direction];
                    c = TheMap[CurrPosition.x][CurrPosition.y].Map;
                }
                else {
                    Flag = 1;       break;
                };
            }
            else {
                Flag = 1;       break;
            };
        };
        Str.AddStr(BufferArr);
        if (Flag) break;
    };
    if (Direction == GOBACK) {
        Str.ReverseStr();
    };
    return Str;
};

/* The whole function for finding the name of the city, will search in 8 direction of the city */
String_t FindTheCityName(Position_t MapSize, Position_t Pos, TheMapElement_t** TheMap) {
    String_t CityName;
    size_t Direction; int Pos_x, Pos_y;
    bool Flag = 0;
    for (size_t i = 0; i < NUMBEROFPOSSIBLEDIRECTIONS; i++) {
        for (size_t j = 0; j < NUMBEROFPOSSIBLEDIRECTIONS; j++) {
            Pos_x = Pos.x + Dir[i]; Pos_y = Pos.y + Dir[j];
            if (Pos_x < MapSize.x && Pos_y < MapSize.y && Pos_x >= 0 && Pos_y >= 0) {
                if (CheckIsLetter(TheMap[Pos_x][Pos_y].Map)) {
                    Direction = DirectionOfTheCityName(MapSize, { Pos_x,Pos_y }, TheMap);
                    CityName = FindTheName(Direction, MapSize, { Pos_x,Pos_y }, TheMap);
                    if (CityName[0] != ENDOFSTRING) {
                        Flag = 1; break;
                    };
                };
            };
        };
        if (Flag) break;
    };
    return CityName;
};

/* Find the Citites in the Map and then procede to function that makes Adjacency Matrix */
void FindTheCitiesinMap(Position_t MapSize, TheMapElement_t** TheMap, AdjacencyMatrix_t* TheMatrix) {
    String_t CityName;
    for (int i = 0; i < MapSize.x; i++) {
        for (int j = 0; j < MapSize.y; j++) {
            if (TheMap[i][j].Map == THECITYMAP) {
                CityName = FindTheCityName(MapSize, { i,j }, TheMap);
                if (CityName[0] != ENDOFSTRING) {
                    TheMatrix->AddCity(CityName, { i,j });
                };
            };
        };
    };
    cout << "Found Names";
   // TheMatrix->Printall();
    TheMatrix->InitializeMatrix();
    cout << "DOTHIS";
    ProcessTheMapByFindingTheEdges(MapSize, TheMap, TheMatrix);
};

/* ---------------------------------------- THE MAP --------------------------------------------------- */

/* Initialize the map, which is a 2D array of chars */
char** InitializeTheMapChar(int width_x, int height_y) {
    char** TheMap = new char* [width_x];
    for (int i = 0; i < width_x; i++) {
        TheMap[i] = new char[height_y];
    };
    return TheMap;
};

TheMapElement_t** InitializeTheMap(int width_x, int height_y) {
    TheMapElement_t** TheMap = new TheMapElement_t * [width_x];
    for (int i = 0; i < width_x; i++) {
        TheMap[i] = new TheMapElement_t[height_y];
    };
    return TheMap;
};

/* Delete the map, when not needed */
void DeleteTheMap(int width_x, int height_y, TheMapElement_t** TheMap) {
    for (int i = 0; i < width_x; i++) {
        delete[] TheMap[i];
    };
    delete[] TheMap;
};