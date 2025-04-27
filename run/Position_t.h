#pragma once
#include "String_t.h"

/* Position class - 2D - x and y variables */
class Position_t {
public:
    int x, y;
    Position_t() : x(0), y(0) {};
    Position_t(int new_x, int new_y) : x(new_x), y(new_y) {};
    Position_t(const Position_t& otherPos) {
        x = otherPos.x;	y = otherPos.y;
    };
    Position_t(Position_t&& otherPos) noexcept {
        x = otherPos.x;	y = otherPos.y;
    };
    Position_t& operator=(const Position_t& otherPos) noexcept {
        x = otherPos.x;	y = otherPos.y;
        return *this;
    };
    Position_t& operator=(Position_t&& otherPos) noexcept {
        x = otherPos.x;	y = otherPos.y;
        return *this;
    };
    void Change_Position(int new_x, int new_y) {
        x = new_x;	y = new_y;
    };
    ~Position_t() {};
};

/* Compare Positions */
bool operator== (const Position_t& c1, const Position_t& c2) {
    return (c1.x == c2.x && c1.y == c2.y);
};

/* Compare Positions */
bool operator!= (const Position_t& c1, const Position_t& c2) {
    return !(c1.x == c2.x && c1.y == c2.y);
};

/* -- Going through the Map -- */
#define GO_RIGHT	0
#define GO_LEFT		1
#define GO_UP		2
#define GO_DOWN		3

#define NUMBEROFPOSSIBLEDIR4	4
//const int Dir4_x[NUMBEROFPOSSIBLEDIR4] = { 1, -1, 0, 0 };
//const int Dir4_y[NUMBEROFPOSSIBLEDIR4] = { 0, 0, -1, 1 };

const Position_t Dir4[NUMBEROFPOSSIBLEDIR4] = { {1, 0}, {-1, 0}, {0, -1}, {0, 1} };