#pragma once
#include "AdjacencyMatrix_t.h"

void PrintDistancesMap(Position_t MapSize, TheMapElement_t** TheMap) {
    for (int i = 0; i < MapSize.x; i++) {
        for (int j = 0; j < MapSize.y; j++) {
            cout << TheMap[i][j].Dist << " ";
            if (TheMap[i][j].Dist >= 10) cout << " ";
            if (TheMap[i][j].Dist >= 100) cout << " ";
        };
        cout << "\n";
    };
    cout << "\n\n";
};

void GetDist(Position_t MapSize, TheMapElement_t** TheMap, AdjacencyMatrix_t* TheMatrix, Position_t TheStartCityPosition, size_t IndexOfStartCity) {
    /* change so it's only cleaning at first and only one initialization */
    CitiesList_t PositionsToBeChecked; Position_t CurrentPos;
    for (size_t i = 0; i < MapSize.x; i++) {
        for (size_t j = 0; j < MapSize.y; j++) {
            TheMap[i][j].Dist = 0;
        };
    };

    PositionsToBeChecked.AddNode(TheStartCityPosition);

    while (PositionsToBeChecked.GetListLength() != 0) {
        CurrentPos = PositionsToBeChecked.GetFirstCity()->PositionOftheCity;
        PositionsToBeChecked.RemoveFirst();
        for (int i = 0; i < NUMBEROFPOSSIBLEDIR4; i++) {
            Position_t Pos2 = { CurrentPos.x + Dir4[i].x, CurrentPos.y + Dir4[i].y };
            if (Pos2.x >= 0 && Pos2.y >= 0 && Pos2.x < MapSize.x && Pos2.y < MapSize.y) {
                if (Pos2 != TheStartCityPosition) {
                    if (TheMap[Pos2.x][Pos2.y].Map == THEROADMAP) {
                        if (TheMap[Pos2.x][Pos2.y].Dist == 0 || TheMap[Pos2.x][Pos2.y].Dist > TheMap[CurrentPos.x][CurrentPos.y].Dist + 1) {
                            TheMap[Pos2.x][Pos2.y].Dist = TheMap[CurrentPos.x][CurrentPos.y].Dist + 1;
                            PositionsToBeChecked.AddNode(Pos2);
                        };
                    }
                    else if (TheMap[Pos2.x][Pos2.y].Map == THECITYMAP) {
                        size_t IndexOfCity = TheMatrix->FindAnIndexOftheCity(Pos2);
                        size_t** AdjMatrix = TheMatrix->GetAdjMatrix();
                        if (AdjMatrix[IndexOfStartCity - STARTINGPOSITION][IndexOfCity - STARTINGPOSITION] == 0 || AdjMatrix[IndexOfStartCity - STARTINGPOSITION][IndexOfCity - STARTINGPOSITION] > TheMap[CurrentPos.x][CurrentPos.y].Dist + 1) {
                            //cout << "MAR: ";
                            //cout << TheMatrix->GetCityNodeByIndex(IndexOfStartCity)->name.GetString() << " " << TheMatrix->GetCityNodeByIndex(IndexOfCity)->name.GetString() << "\n";
                            //cout << AdjMatrix[IndexOfStartCity - STARTINGPOSITION][IndexOfCity - STARTINGPOSITION] << "\n";//<< TheMap[CurrentPos.x][CurrentPos.y].Dist + 1 << "\n\n";
                            AdjMatrix[IndexOfStartCity - STARTINGPOSITION][IndexOfCity - STARTINGPOSITION] = TheMap[CurrentPos.x][CurrentPos.y].Dist + 1;
                            AdjMatrix[IndexOfCity - STARTINGPOSITION][IndexOfStartCity - STARTINGPOSITION] = TheMap[CurrentPos.x][CurrentPos.y].Dist + 1;
                        };
                    };
                };
            };
        };
    };
};





// save the intersections <- !! + save the visited + four neightbours at a time
// make it so at once it gets the value of all of them 
// maybe add int to map- how far are they from the node / BST, the point first to the map first
// also to cities save the already checked direction
// so it will assign value to every one of those roade elements
// there needs to be a clinning after? no not really !!!
// distance as coordinates what i mean checked firstttttttttttttttttttttttttttt
// or maybe go toward the city who knows = probably not