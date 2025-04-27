#include "MapProcessing.h"


void ProcessTheInstructions(AdjacencyMatrix_t* TheMatrix) {
    size_t NumberOfFlights = 0, NumberOfQueries = 0;        size_t Source = 0, Destination = 0, Time = 0;
    String_t CityNameSource, CityNameDestination;
    size_t** AdjMatrix = TheMatrix->GetAdjMatrix();

    scanf_s("%zu", &NumberOfFlights);
    char BufferString1[BUFFERSTRING];
    char BufferString2[BUFFERSTRING];

    for (size_t i = 0; i < NumberOfFlights; i++) {
        scanf_s(" %s %s %zu", BufferString1, BUFFERSTRING, BufferString2, BUFFERSTRING, &Time);
        CityNameSource = BufferString1;
        CityNameDestination = BufferString2;
        Source = TheMatrix->FindAnIndexOftheCity(CityNameSource);
        Destination = TheMatrix->FindAnIndexOftheCity(CityNameDestination);
        if (AdjMatrix[Source - STARTINGPOSITION][Destination - STARTINGPOSITION] == 0 || AdjMatrix[Source - STARTINGPOSITION][Destination - STARTINGPOSITION] > Time) {
            AdjMatrix[Source - STARTINGPOSITION][Destination - STARTINGPOSITION] = Time;
        };
    };
    //TheMatrix->Printall(); // TO DO: Print the Adjacency Matrix to see if it has been updated.

    size_t Mode = 0;
    //size_t numCities = TheMatrix->GetNumberOfCities();

    scanf_s("%zu", &NumberOfQueries);
    for (size_t i = 0; i < NumberOfQueries; i++) {
        scanf_s(" %s %s %zu", BufferString1, BUFFERSTRING, BufferString2, BUFFERSTRING, &Mode);
        CityNameSource = BufferString1;
        CityNameDestination = BufferString2;
        Source = TheMatrix->FindAnIndexOftheCity(CityNameSource);
        Destination = TheMatrix->FindAnIndexOftheCity(CityNameDestination);
        //cout << "\n" << BufferString1 << Source << " " << BufferString2 << Destination << "\n";
        if (Source == Destination || Source == 0 || Destination == 0) {
            //cout << BufferString1 << " " << BufferString2 << "\n";
            //cout << Source << " " << Destination << "\n\n";
            printf("0\n");
        }
        else {
            if (AdjMatrix[Source - STARTINGPOSITION][Source - STARTINGPOSITION] != 1) {
                DijikstraAlgorithm(TheMatrix, Source);
            };
            if (Mode == MODEZERO) {
                printf("%zu", AdjMatrix[Source - STARTINGPOSITION][Destination - STARTINGPOSITION]);
                //TheMatrix->Printall();
            }
            else if (Mode == MODEONE) {
                printf("%zu", AdjMatrix[Source - STARTINGPOSITION][Destination - STARTINGPOSITION]);
                TheMatrix->GetRoadMatrix()[Source - STARTINGPOSITION][Destination - STARTINGPOSITION].PrintCities();
            };
            printf("\n");
        };
    };
    //TheMatrix->Printall();
};

void ProcessTheInput(AdjacencyMatrix_t* TheMatrix) {
    int width_x, height_y;
    char c;
    scanf_s("%d", &height_y);
    scanf_s("%d", &width_x);
    TheMapElement_t** TheMap = InitializeTheMap(width_x, height_y);

    for (size_t i = 0; i < width_x; i++) {
        for (size_t j = 0; j < height_y; j++) {
            scanf_s(" %c", &c, (unsigned)sizeof(c));
            TheMap[i][j].Map = c;
        };
    };
    cout << "MapProcessed";
    FindTheCitiesinMap({ width_x, height_y }, TheMap, TheMatrix);

    //TheMatrix->Printall();
    //PrintMap(TheMap, width_x, height_y);

    DeleteTheMap(width_x, height_y, TheMap);
    ProcessTheInstructions(TheMatrix);
};

int main() {
    AdjacencyMatrix_t TheMatrix;
    cout << "main";
    ProcessTheInput(&TheMatrix);
};


/*
        CitiesList_t CityList;
        CitiesList_t City2;
        Position_t x;
        CityList.AddNode((String_t)"raz", x);
        CityList.AddNode((String_t)"dwa", x);
        CityList.AddNode((String_t)"trzy", x);
        CityList.PrintAll();
        CityList.RemoveLast();
        CityList.PrintAll();
        CityList.AddNode((String_t)"cztery", x);
        CityList.PrintAll();
        cout << CityList.GetListLength() << " " << CityList.GetLastCity()->name.GetString();

        //CityList.CopyTheCitiesList(&City2);
        //cout << CityList.GetListLength();
        //CityList.PrintAll();

*/