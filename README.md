# FindRoad_ADS
## Description
Project for Algorithms and Data Structures course.

## Instruction
A rectangular map divided into squares is given. Each field on the map can be empty (impassable), be part of a road (passable in both directions), or be a city (passable like a road). The name of each city is given on the map, and each letter occupies one field (the field with the letter is impassable). Moving through one field takes one minute. We can only move between fields adjacent by sides. Additionally, selected cities are connected by one-way air connections. The name of a city will be adjacent (by side or corner) to the city with the first or last letter of the name.
The name will be unambiguously assigned to the city. There will be no number or letter before or after the name of the city (if there is such a field).

Implementation notes:

- Standard string class and other standard library containers cannot be used.
- You can use C++ elements such as classes, references, etc.
- One can implement their own string class.
- Code readability is important, and comments (which are of course allowed) do not necessarily ensure it.
- Smartpointers from standard library are forbidden, but you can still implement your own smartpointer class.
- Please remember to free memory when deleting elements of the implemented data structures.

### Examples:

This can be:

    *GDANSK....OPOLE....RUMIA
    ...*GDYNIA......*....*...
    *SOPOT.............*....*
    ...PUCK*.*KRAKOW.REDA.HEL

## Full information about the project
Results and full instruction available in Instructions.txt.

Tests available in test folder.

## Author
O. Paszkiewicz 2023
