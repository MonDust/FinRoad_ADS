#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
using namespace std;

/* MODES */
#define MODEZERO                0
#define MODEONE                 1

/* MAP */
#define THEROADMAP              '#'
#define THECITYMAP              '*'
#define NOTHINGMAP              '.'


/* NUMBERS */
#define BUFFERSTRING			100
#define STARTINGPOSITION        1
#define SPACEFORENDCHAR         1 /* SPACE NEED IN ARRAY FOR CHARCTER '\0' */

/* MISCELLANEOUS */
#define SPACE                   ' '
#define ENDLINE                 '\n'
#define HORIZONTALTAB			'\t'
#define ENDOFSTRING             '\0'
#define EMPTYSTR                ""

/* ---------------------- MAP PROCESSING ------------------------- */
/* -- Finding the name of City -- */
#define GOBACK                  0 /* go backward to find the name */
#define STAYSTILL               1 /* the name is one char long */
#define GOFORWARD               2 /* go forward to find the name */
#define THEWRONGDIR             3 /* that is not the start nor end of the city name */

#define NUMBEROFPOSSIBLEDIRECTIONS 3
const int Dir[NUMBEROFPOSSIBLEDIRECTIONS] = { -1, 0, 1 };