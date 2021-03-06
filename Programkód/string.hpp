#ifndef STRING_H
#define STRING_H

#include <iostream>

class String {
    char *pData;        ///< pointer az adatra
    size_t len;         ///< hossz lezáró nulla nélkül
public:
    /// Paraméter nélküli konstruktor:
    String() :pData(NULL), len(0) {}

    /// Sztring hosszát adja vissza.
    /// @return sztring tényleges hossza (lezáró nulla nélkül).
    size_t size() const { return len; }

    /// C-sztringet ad vissza
    /// @return pointer a tárolt, vagy azzal azonos tartalmú nullával lezárt sztring-re.
    const char* c_str() const {
    if(pData != NULL) {
        return pData;
    }
    return "\0";
}

String(char param);
String(const char* cstring);
String(const String &s);

String& operator=(const String& rhs_s);

String operator+(const String& rhs_s) const;
String operator+(const char rhs_c) const { return *this + String(rhs_c);}

String& operator+=(const String& rhs_s) {
    *this = *this + rhs_s;
    return *this;
}
String& operator+=(const char rhs_s) {
    *this = *this + rhs_s;
    return *this;
}

bool operator==(const String &s) const;
bool operator!=(const String &s) const;

~String();
};

std::ostream& operator<<(std::ostream& os, const String& s);

std::istream& operator>>(std::istream& is, String& s0);

bool getline(std::istream& is, String& s, char d);

int stoi(String& s);


#endif
