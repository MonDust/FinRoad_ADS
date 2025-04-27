#pragma once
#include "TheConstants.h"

/* GET SIZE OF A STRING IN FORM OF ARRAY OF CHARS */
size_t GetStringLength(const char* Str) {
    if (Str == nullptr) return 0;
    size_t i = 0;
    while (*Str != ENDOFSTRING) {
        Str++; i++;
    };
    return i;
};

/* COPY STRING FROM OTHERSTR TO MAINSTR (BOTH IN FORM OF ARRAY OF CHARS) */
void CopyString(char* mainStr, const char* otherStr) {
    if (mainStr == nullptr || otherStr == nullptr) perror("One of the strings is nullptr in CopyString");
    else {
        char* tmpStr = mainStr;
        while (*otherStr != ENDOFSTRING)
        {
            *tmpStr = *otherStr;
            tmpStr++; otherStr++;
        }
        *tmpStr = ENDOFSTRING;
    };
};

/* COPY STRING OTHERSTR FROM INDEX FROM UNTIL THE END */
char* CopyStringFrom(const char* otherStr, size_t From) {
    if (otherStr == nullptr) { perror("otherStr is nullptr in CopyStringFrom"); return nullptr; };
    size_t lengthOfStr = GetStringLength(otherStr), m = 0;
    char* newStr = new char[lengthOfStr + SPACEFORENDCHAR - From];
    for (size_t j = From; j < lengthOfStr; j++)
    {
        newStr[m] = otherStr[j];
        m++;
    }
    newStr[m] = ENDOFSTRING;
    return newStr;
};

/* COPY STRING FROM OTHERSTR TO MAINSTR UNTIL THE INDEX THE_END */
void CopyStringTo(char* mainStr, const char* otherStr, size_t To_End) {
    if (mainStr == nullptr || otherStr == nullptr) { perror("One of the strings is nullptr in CopyStringFrom"); return; };
    char* tmpStr = mainStr;
    size_t i = 0;
    while (*otherStr != ENDOFSTRING && i < To_End)
    {
        *tmpStr = *otherStr;
        tmpStr++; otherStr++;
        i++;
    }
    *tmpStr = ENDOFSTRING;
};

/* COMPARE STRING MAINSTR WITH OTHERSTR OMMITING SPACES, RETURN 1 IF THE SAME, 0 IF NOT, SKIP SPACES */
bool CompareString(const char* mainStr, const char* otherStr) {
    if(mainStr == nullptr || otherStr == nullptr) { perror("One of the strings is nullptr in CompareString"); return 0; };
    while (*mainStr != ENDOFSTRING) {
        if (*otherStr == ENDOFSTRING && *mainStr != SPACE) return 0;
        if (*mainStr != SPACE && *otherStr != SPACE)
        {
            if (*(mainStr) != *(otherStr)) return 0;
            mainStr++;
            otherStr++;
        }
        else {
            if (*mainStr == SPACE) mainStr++;
            if (*otherStr == SPACE) otherStr++;
        };
    };
    while (*otherStr != ENDOFSTRING) {
        if (*otherStr == SPACE) otherStr++;
        else return 0;
    };
    return 1;
};

/* MY STRING CLASS CONSISTING OF ARRAY OF CHARS */
class String_t {
private:
    char* str;
public:
    String_t();
    explicit String_t(char* otherArr);
    explicit String_t(const char otherArr[]);
    String_t(const String_t& otherStr);
    String_t(String_t&& otherStr) noexcept;
    String_t& operator=(const char* otherArr) noexcept;
    String_t& operator=(const String_t& otherStr) noexcept;
    String_t& operator=(String_t&& otherStr) noexcept;

    char operator[](int Index);

    char* GetString() { if (this) return str; else return (char*)""; };
    char* GetString() const { if (this) return str; else return (char*)""; };
    size_t GetSize() { return GetStringLength(str); };
    size_t GetSize() const { return GetStringLength(str); };

    size_t FindInString(const char Character) const;
    size_t FindInString(const char Character, size_t FromCharacter) const;
    size_t FindInString(const char* Character) const;
    size_t FindInString(const char* Character, size_t FromCharacter) const;

    bool CompareIfTheSame(char* otherArr) { return CompareString(str, otherArr); };
    bool CompareIfTheSame(const String_t& otherStr) { return CompareString(str, otherStr.str); };
    bool CompareIfTheSame(String_t&& otherStr) { return CompareString(str, otherStr.str); };

    void CopyStr(const char* otherArr);
    void CopyStr(const String_t& otherStr);
    void CopyStr(String_t&& otherStr);
    void CopyStr(const char* otherArr, size_t From);
    void CopyStr(const String_t& otherStr, size_t From);
    void CopyStr(const char* otherArr, size_t From, size_t To);
    void CopyStr(const String_t& otherStr, size_t From, size_t To);
    void AddStr(const char* otherArr);

    void ReverseStr();

    char* ReturnStringUntil(size_t To);

    ~String_t() {
        if (str) delete[] str;
    };
};

/* Reverse the string */
void String_t::ReverseStr() {
    size_t size = GetSize();
    size_t halfsize = (size - (size % 2)) / 2;
    char tmp;

    for (int i = 0; i < halfsize; i++) {
        tmp = str[i];
        str[i] = str[size - 1 - i];
        str[size - 1 - i] = tmp;
    };
};

/* Get a letter at index Index, Starting Position = 0 */
char String_t::operator[](int Index) {
    return str[Index];
};

/* Compare Strings */
bool operator== (const String_t& c1, const String_t& c2) {
    return CompareString(c1.GetString(), c2.GetString());
};

/* Compare Strings */
bool operator!= (const String_t& c1, const String_t& c2) {
    return !CompareString(c1.GetString(), c2.GetString());
};

/* Compare array of chars and String */
bool operator== (const char* c1, const String_t& c2) {
    if (c1 == nullptr) return 0;
    return CompareString(c1, c2.GetString());
};

/* Compare array of chars and String */
bool operator!= (const char* c1, const String_t& c2) {
    if (c1 == nullptr) return 1;
    return !CompareString(c1, c2.GetString());
};

/* Compare String and array of chars */
bool operator== (const String_t& c1, const char* c2) {
    if (c2 == nullptr) return 0;
    return CompareString(c1.GetString(), c2);
};

/* Compare String and array of chars */
bool operator!= (const String_t& c1, const char* c2) {
    if (c2 == nullptr) return 1;
    return !CompareString(c1.GetString(), c2);
};

/* COPY STRING UNTIL INDEX TO, WILL RETURN THE STRING TO AN INDEX TO AND DELETE THAT PART WITH ELEMENT INDEX TO FROM STRING */
char* String_t::ReturnStringUntil(size_t To) {
    char* otherStr = new char[To];
    CopyStringTo(otherStr, str, To - STARTINGPOSITION);
    str = CopyStringFrom(str, To);
    return otherStr;
};

/* EMPTY CONSTRUCTOR WILL INITIALIZE ARRAY OF CHARS AS SIZE 1 */
String_t::String_t() {
    str = new char[1];  str[0] = ENDOFSTRING;
};

/* CONSTRUCTOR INITIALIZING ARRAY OF CHARS AS OTHER ARRAY OF CHARS */
String_t::String_t(char* otherArr) {
    if (otherArr == nullptr) {
        str = new char[1];  str[0] = ENDOFSTRING;
    }
    else {
        str = new char[GetStringLength(otherArr) + SPACEFORENDCHAR];
        CopyString(str, otherArr);
    }
};

/* CONSTRUCTOR INITIALIZING ARRAY OF CHARS FROM TABLE OF CHARS */
String_t::String_t(const char otherArr[]) {
    size_t sizeOfArr = GetStringLength(otherArr);
    if (sizeOfArr == 0) {
        str = new char[1];  str[0] = ENDOFSTRING;
    }
    else {
        str = new char[sizeOfArr + SPACEFORENDCHAR];
        CopyString(str, otherArr);
    }
};

/* CONSTRUCTOR INITIALIZING ARRAY OF CHARS FROM A STRING */
String_t::String_t(const String_t& otherStr) {
    str = new char[GetStringLength(otherStr.str) + SPACEFORENDCHAR];
    CopyString(str, otherStr.str);
};

/* CONSTRUCTO INITIALIZING ARRAY OF CHARS FROM A STRING */
String_t::String_t(String_t&& otherStr) noexcept {
    str = otherStr.str;
    otherStr.str = nullptr;
};

/* FIND A CHAR IN A STRING, WILL RETURN THE POSITION;
STARTING POSITION = 1; WILL RETURN 0 IF NOT FOUND */
size_t String_t::FindInString(const char Character) const {
    size_t i = 0;
    while (str[i] != ENDOFSTRING) {
        if (str[i] == Character) return i + STARTINGPOSITION;
        i++;
    };
    return 0;
};

/* FIND IN STRING STARTING FROM AN INDEX FromCharacter, WILL RETURN THE POSITION;
STARTING POSITION = 1; WILL RETURN 0 IF NOT FOUND*/
size_t String_t::FindInString(const char Character, size_t FromCharacter) const {
    size_t i = FromCharacter - STARTINGPOSITION;
    while (str[i] != ENDOFSTRING) {
        if (str[i] == Character) return i + STARTINGPOSITION;
        i++;
    };
    return 0;
};

/* FIND AN ARRAY OF CHARS IN STRING; STARTING POSITION = 1;
WILL RETURN 0 IF NOT FOUND */
size_t String_t::FindInString(const char* Character) const {
    if (Character == nullptr) { perror("Character is nullptr in FindInString"); return 0; };
    size_t i = 0;
    while (str[i] != ENDOFSTRING) {
        size_t j = 0, IndexOfArray = i;
        if (Character[j] == ENDOFSTRING) break;
        while (Character[j] != ENDOFSTRING) {
            if (str[i] != Character[j] || str[i] == ENDOFSTRING) { i++; break; } /* if not matching break */
            i++;
            j++;
        };
        if (Character[j] == ENDOFSTRING) return IndexOfArray + STARTINGPOSITION;
    };
    return 0;
};

/* FIND AN ARRAY OF CHARS IN STRING STARTING FROM AN INDEX FromCharacter;
STARTING POSITION = 1; WILL RETURN 0 IF NOT FOUND */
size_t String_t::FindInString(const char* Character, size_t FromCharacter) const {
    if (Character == nullptr) { perror("Character is nullptr in FindInString"); return 0; };
    size_t i = FromCharacter - STARTINGPOSITION;
    while (str[i] != ENDOFSTRING) {
        size_t j = 0, IndexOfArray = i;
        if (Character[j] == ENDOFSTRING) break;
        while (Character[j] != ENDOFSTRING) {
            if (str[i] != Character[j] || str[i] == ENDOFSTRING) { i++; break; } /* if not matching break */
            i++;
            j++;
        };
        if (Character[j] == ENDOFSTRING) return IndexOfArray + STARTINGPOSITION;
    };
    return 0;
};

/* MERGE STRING THE STR AND OTHERARR (ARRAY OF CHARS) */
void String_t::AddStr(const char* otherArr) {
    if (otherArr == nullptr) { perror("otherArr is nullptr in AddStr"); return; };
    size_t StrLength = GetStringLength(str);

    char* newStr = new char[StrLength + SPACEFORENDCHAR];
    CopyString(newStr, str);

    delete[] str;
    str = new char[StrLength + GetStringLength(otherArr) + SPACEFORENDCHAR];
    CopyString(str, newStr);
    delete[] newStr;

    CopyString(&(str[StrLength]), otherArr);
};

/* COPYING STRING FROM OTHERARR */
void String_t::CopyStr(const char* otherArr) {
    if (otherArr == nullptr) { perror("otherArr is nullptr in CopyStr"); return; };
    if (str) delete[] str;
    str = new char[GetStringLength(otherArr) + SPACEFORENDCHAR];
    CopyString(str, otherArr);
};

/* COPYING STRING FROM OTHERSTR */
void String_t::CopyStr(const String_t& otherStr) {
    if (&otherStr != this) { /* We don't want to copy the same string -> delete it */
        if (str) delete[] str;
        str = new char[GetStringLength(otherStr.str) + SPACEFORENDCHAR];
        CopyString(str, otherStr.str);
    };
};

/* COPYING STRING FROM OTHERSTR */
void String_t::CopyStr(String_t&& otherStr) {
    str = otherStr.str;
    otherStr.str = nullptr;
};


/* COPYING STRING FROM OTHERARR, STARTING FROM INDEX FROM; STARTING POSITION = 1 */
void String_t::CopyStr(const char* otherArr, size_t From) {
    if (otherArr == nullptr) { perror("otherArr is nullptr in CopyStr"); return; };
    if (str) delete[] str;
    str = new char[GetStringLength(otherArr) - From + STARTINGPOSITION + SPACEFORENDCHAR];
    CopyString(str, &(otherArr[From - STARTINGPOSITION]));
};

/* COPYING STRING FROM OTHERSTR, STARTING FROM INDEX FROM; STARTING POSITION = 1 */
void String_t::CopyStr(const String_t& otherStr, size_t From) {
    if (&otherStr != this) {
        if (str) delete[] str;
        str = new char[GetStringLength(otherStr.str) - From + STARTINGPOSITION + SPACEFORENDCHAR];
        CopyString(str, &(otherStr.str[From - STARTINGPOSITION]));
    }
    else {
        if (str) {
            size_t sizeOfStr = GetSize();
            char* newStr = new char[sizeOfStr + SPACEFORENDCHAR];
            CopyString(newStr, str);
            delete[] str;
            str = new char[sizeOfStr - From + SPACEFORENDCHAR + STARTINGPOSITION];
            CopyString(str, &(newStr[From - STARTINGPOSITION]));
            delete[] newStr;
        };
    };
};

/* COPYING STRING FROM OTHERARR, STARTING FROM INDEX FROM TO INDEX TO; STARTING POSITION = 1 */
void String_t::CopyStr(const char* otherArr, size_t From, size_t To) {
    if (otherArr == nullptr) { perror("otherArr is nullptr in CopyStr"); return; };
    if (str) delete[] str;
    size_t SizeOfString = To - From + STARTINGPOSITION;
    str = new char[SizeOfString + SPACEFORENDCHAR];
    CopyStringTo(str, &(otherArr[From - STARTINGPOSITION]), SizeOfString);
};

/* COPYING STRING FROM OTHERSTR, STARTING FROM INDEX FROM TO INDEX TO; STARTING POSITION = 1 */
void String_t::CopyStr(const String_t& otherStr, size_t From, size_t To) {
    size_t SizeOfString = To - From + STARTINGPOSITION;
    if (&otherStr != this) {
        if (str) delete[] str;
        str = new char[SizeOfString + SPACEFORENDCHAR];
        CopyStringTo(str, &(otherStr.str[From - STARTINGPOSITION]), SizeOfString);
    }
    else {
        if (str) {
            size_t sizeOfNewStr = GetSize();
            char* newStr = new char[sizeOfNewStr + SPACEFORENDCHAR];
            CopyString(newStr, str);
            delete[] str;
            str = new char[SizeOfString + SPACEFORENDCHAR];
            CopyStringTo(str, &(newStr[From - STARTINGPOSITION]), SizeOfString);
            delete[] newStr;
        };
    };
};

/* COPY STRING: STR = OTHERARR */
String_t& String_t::operator=(const char* otherArr) noexcept {
    if (otherArr == nullptr) { perror("otherArr is nullptr in operator="); return *this; };
    if (str) delete[] str;
    str = new char[GetStringLength(otherArr) + SPACEFORENDCHAR];
    CopyString(str, otherArr);
    return *this;
};

/* COPY STRING: STR = OTHERSTR */
String_t& String_t::operator=(const String_t& otherStr) noexcept {
    if (&otherStr != this) { /* CHANGED: added self-assigment check */
        if (str) delete[] str;
        str = new char[GetStringLength(otherStr.str) + SPACEFORENDCHAR];
        CopyString(str, otherStr.str);
    };
    return *this;
};

/* COPY STRING: STR = OTHERARR */
String_t& String_t::operator=(String_t&& otherStr) noexcept {
    str = otherStr.str;
    otherStr.str = nullptr;
    return *this;
};