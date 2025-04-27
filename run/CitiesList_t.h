#pragma once
#include "Position_t.h"

/* Node - containing a City: a name and a pointer to the next City; pointer will initialized as nullptr */
class CityNode_t {
public:
    String_t name;
    Position_t PositionOftheCity;
    CityNode_t* next;
    bool IsCheckedDirection[NUMBEROFPOSSIBLEDIR4] = { 0, 0, 0, 0 };
    CityNode_t() : name(), PositionOftheCity({ -1, -1 }), next(nullptr) {};
    explicit CityNode_t(String_t CityName) : name(CityName), PositionOftheCity({ -1, -1 }), next(nullptr) {};
    CityNode_t(Position_t Position) : name(), PositionOftheCity(Position), next(nullptr) {};
    explicit CityNode_t(String_t CityName, Position_t Position) : name(CityName), PositionOftheCity(Position), next(nullptr) {};
    ~CityNode_t() {};
};

/* Singly linked list for CitiesList, containting head element of class City Node */
class CitiesList_t {
private:
    CityNode_t head;
public:
    CitiesList_t() : head() {};
    void PrintAll();
    void PrintCities();
    void MarkDirectionAsChecked(size_t Index, size_t Direction);
    CityNode_t* GetHead() { return &head; };
    const CityNode_t* GetHead() const { return &head; };
    CityNode_t* GetFirstCity();
    CityNode_t* GetLastCity();
    size_t GetListLength();
    CityNode_t* FindNodeAtIndex(size_t Index);
    CityNode_t* FindNodeByPosition(Position_t Pos);
    CityNode_t* FindNode(String_t CityName);
    size_t FindIndexOfNode(String_t CityName);
    size_t FindIndexOfNode(Position_t Pos);
    bool FindIfThereIsCity(String_t CityName);
    void AddNode(String_t CityName);
    void AddNode(Position_t Position);
    void AddNode(String_t CityName, Position_t Position);
    void AddNode(CityNode_t* CityNode);
    bool RemoveNodeBasedOnName(String_t CityName);
    void RemoveLast();
    void RemoveFirst();
    static void RemoveAfter(CityNode_t* Node);
    CityNode_t* operator[](size_t Index);

    CitiesList_t& operator=(const CitiesList_t& OtherCityList) noexcept;
    CitiesList_t& operator=(CitiesList_t&& OtherCityList) noexcept;
    void CopyTheCitiesList(CitiesList_t* OtherCityList);
    void AddTheCitiesList(CitiesList_t* OtherCityList);

    void RemoveCityList() {
        while (head.next) RemoveAfter(&head);
        head.next = nullptr;
    };
    ~CitiesList_t() {
        while (head.next) RemoveAfter(&head);
    };
};

/* Mark a certain direction as checked: right, left, up or down; Starting Position = 1 */
void CitiesList_t::MarkDirectionAsChecked(size_t Index, size_t Direction) {
    CityNode_t* CityNode = FindNodeAtIndex(Index);
    CityNode->IsCheckedDirection[Direction] = 1;
};

/* Get Last City Node */
CityNode_t* CitiesList_t::GetLastCity() {
    CityNode_t* tmp = &head;
    if (tmp->next) {
        while (tmp->next) {
            tmp = tmp->next;
        };
        return tmp;
    };
    return nullptr;
};

/* Get First City Node */
CityNode_t* CitiesList_t::GetFirstCity() {
    CityNode_t* tmp = &head;
    if (tmp->next) {
        return tmp->next;
    };
    return nullptr;
};

/* Copy the OtherCityList */
CitiesList_t& CitiesList_t::operator=(const CitiesList_t& OtherCityList) noexcept {
    if (&OtherCityList == nullptr) perror("OtherCityList is empty while trying to copy it in the CopyTheCitiesList");
    if (this == &OtherCityList) {
        return *this;
    };
    RemoveCityList();
    if (head.next == nullptr) {
        CityNode_t* tmp = OtherCityList.GetHead()->next;
        if (tmp != nullptr) {
            AddNode(tmp->name, tmp->PositionOftheCity);
            while (tmp->next) {
                AddNode(tmp->next->name, tmp->next->PositionOftheCity);
                tmp = tmp->next;
            };
        };
    }
    else perror("The List did not get removed while trying to Copy in the CopyTheCitiesList");
    return *this;
};

/* Copy the OtherCityList */
CitiesList_t& CitiesList_t::operator=(CitiesList_t&& OtherCityList) noexcept {
    head.next = OtherCityList.GetHead()->next;
    OtherCityList.GetHead()->next = nullptr;
    return *this;
};

/* Copy the OtherCityList */
void CitiesList_t::CopyTheCitiesList(CitiesList_t* OtherCityList) {
    if (OtherCityList == nullptr) perror("OtherCityList is empty while trying to copy it in the CopyTheCitiesList");
    if (this == OtherCityList) {
        return;
    };
    RemoveCityList();
    if (head.next == nullptr) {
        CityNode_t* tmp = OtherCityList->GetHead();
        while (tmp->next) {
            AddNode(tmp->next->name, tmp->next->PositionOftheCity);
            tmp = tmp->next;
        };
        if (tmp != OtherCityList->GetHead()) {
            if (tmp != OtherCityList->GetLastCity()) perror("Did not copy the list to the end in the CopyTheCitiesList");
        };
    }
    else perror("The List did not get removed while trying to Copy in the CopyTheCitiesList");
};

void CitiesList_t::AddTheCitiesList(CitiesList_t* OtherCityList) {
    if (OtherCityList == nullptr) perror("OtherCityList is empty while trying to copy it in the CopyTheCitiesList");
    CityNode_t* tmp = OtherCityList->GetHead();
    while (tmp->next) {
        AddNode(tmp->next->name, tmp->next->PositionOftheCity);
        tmp = tmp->next;
    };
    if (tmp != OtherCityList->GetHead()) {
        if (tmp != OtherCityList->GetLastCity()) perror("Did not copy the list to the end in the CopyTheCitiesList");
    };
};


/* [] Operator on CitiesList, Starting position = 1 */
CityNode_t* CitiesList_t::operator[](size_t Index) {
    return FindNodeAtIndex(Index);
};

/* Print only the names of Cities - a road */
void CitiesList_t::PrintCities() {
    CityNode_t* tmp = &head;
    while (tmp->next) {
        if (tmp->next->name != nullptr) {
            printf(" %s", tmp->next->name.GetString());
        };
        tmp = tmp->next;
    };
};

/* Print all CitiesList in a list */
void CitiesList_t::PrintAll() {
    printf("CITIES LIST:\n");
    CityNode_t* tmp = &head;
    while (tmp->next) {
        printf("%s: %d %d\n", tmp->next->name.GetString(), tmp->next->PositionOftheCity.x, tmp->next->PositionOftheCity.y);
        tmp = tmp->next;
    };
};

/* Find out if there exists a City named CityName, if there is - return 1, otherwise return 0 */
bool CitiesList_t::FindIfThereIsCity(String_t CityName) {
    CityNode_t* tmp = &head;
    while (tmp->next) {
        if (tmp->next->name.CompareIfTheSame(CityName)) return 1;
        tmp = tmp->next;
    };
    return 0;
};

/* Get the length of the list */
size_t CitiesList_t::GetListLength() {
    size_t i = 0;
    CityNode_t* tmp = &head;
    while (tmp->next) {
        i++;
        tmp = tmp->next;
    };
    return i;
};

/* Find out if there exists a City named CityName, if there is - return the Node containing it, otherwise return nullptr */
CityNode_t* CitiesList_t::FindNode(String_t CityName) {
    CityNode_t* tmp = &head;
    while (tmp->next) {
        if (tmp->next->name.CompareIfTheSame(CityName)) return tmp->next;
        tmp = tmp->next;
    };
    return nullptr;
};

CityNode_t* CitiesList_t::FindNodeByPosition(Position_t Pos) {
    CityNode_t* tmp = &head;
    while (tmp->next) {
        if (tmp->next->PositionOftheCity == Pos) return tmp->next;
        tmp = tmp->next;
    };
    return nullptr;
};

/* returns 0 if not found, Starting position = 1 */
size_t CitiesList_t::FindIndexOfNode(String_t CityName) {
    CityNode_t* tmp = &head;
    size_t Index = STARTINGPOSITION;
    while (tmp->next) {
        if (tmp->next->name.CompareIfTheSame(CityName)) return Index;
        tmp = tmp->next;
        Index++;
    };
    return 0;
};

/* returns 0 if not found, Starting position = 1 */
size_t CitiesList_t::FindIndexOfNode(Position_t Pos) {
    CityNode_t* tmp = &head;
    size_t Index = STARTINGPOSITION;
    while (tmp->next) {
        if (tmp->next->PositionOftheCity == Pos) return Index;
        tmp = tmp->next;
        Index++;
    };
    return 0;
};

/* Find Node at index Index; Returns the City Node, if not found returns nullptr; starting Position = 1 */
CityNode_t* CitiesList_t::FindNodeAtIndex(size_t Index) {
    CityNode_t* tmp = &head;
    size_t i = STARTINGPOSITION;
    while (tmp->next) {
        if (Index == i) return tmp->next;
        i++; tmp = tmp->next;
    };
    return nullptr;
};

/* Add new Node at the end of the list */
void CitiesList_t::AddNode(String_t CityName) {
    CityNode_t* newNode = new CityNode_t(CityName);
    CityNode_t* tmp = &head;
    while (tmp->next) tmp = tmp->next;
    tmp->next = newNode;
};

/* Add new Node at the end of the list */
void CitiesList_t::AddNode(Position_t Position) {
    CityNode_t* newNode = new CityNode_t(Position);
    CityNode_t* tmp = &head;
    while (tmp->next) tmp = tmp->next;
    tmp->next = newNode;
};

/* Add new Node at the end of the list */
void CitiesList_t::AddNode(String_t CityName, Position_t Position) {
    CityNode_t* newNode = new CityNode_t(CityName, Position);
    CityNode_t* tmp = &head;
    while (tmp->next) tmp = tmp->next;
    tmp->next = newNode;
};

/* Add new Node at the end of the list */
void CitiesList_t::AddNode(CityNode_t* CityNode) {
    if (CityNode) {
        AddNode(CityNode->name, CityNode->PositionOftheCity);
    };
};

/* Remove Node if it has the name n, returns 1 if succesfully removed, otherwise returns 0 */
bool CitiesList_t::RemoveNodeBasedOnName(String_t CityName) {
    CityNode_t* tmp = &head;
    while (tmp->next) {
        if (tmp->next->name.CompareIfTheSame(CityName)) {
            RemoveAfter(tmp);
            return 1;
        };
        tmp = tmp->next;
    };
    return 0;
};

/* Remove Node After the given Node */
void CitiesList_t::RemoveAfter(CityNode_t* Node) {
    if (Node == nullptr) {
        return;
    };
    CityNode_t* tmp = Node->next;
    if (Node->next) {
        Node->next = Node->next->next;
        tmp->next = nullptr;
        delete tmp;
    };
};

void  CitiesList_t::RemoveFirst() {
    CityNode_t* tmp = &head;
    if (tmp->next) {
        RemoveAfter(tmp);
    };
};

/* Remove the last Node */
void CitiesList_t::RemoveLast() {
    CityNode_t* tmp = &head;
    if (tmp->next) {
        if (tmp->next->next) {
            while (tmp->next->next) {
                tmp = tmp->next;
            };
            RemoveAfter(tmp);
        }
        else RemoveAfter(tmp);
    };
};


/* COMPARISONS */

bool operator== (const CityNode_t& c1, const CityNode_t& c2) {
    return c1.name == c2.name;
};

bool operator!= (const CityNode_t& c1, const CityNode_t& c2) {
    return c1.name != c2.name;
};

bool operator== (const CityNode_t& c1, const char* c2) {
    if (c2 == nullptr) return 0;
    return c1.name == c2;
};

bool operator!= (const CityNode_t& c1, const char* c2) {
    if (c2 == nullptr) return 1;
    return c1.name != c2;
};

bool operator== (const char* c1, const CityNode_t& c2) {
    if (c1 == nullptr) return 0;
    return c1 == c2.name;
};

bool operator!= (const char* c1, const CityNode_t& c2) {
    if (c1 == nullptr) return 1;
    return c1 != c2.name;
};

bool operator== (const CityNode_t& c1, const String_t& c2) {
    return c1.name == c2;
};

bool operator!= (const CityNode_t& c1, const String_t& c2) {
    return c1.name != c2;
};

bool operator== (const String_t& c1, const CityNode_t& c2) {
    return c1 == c2.name;
};

bool operator!= (const String_t& c1, const CityNode_t& c2) {
    return c1 != c2.name;
};