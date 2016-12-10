#ifndef _HIGH_PRECISION_H
#define _HIGH_PRECISION_H

#include <string>

#define DEFAULT_PRECISION 25
#define E "2.7182818284590452353602874713526624977572470936999595749669676277240766303535"

class hp_Number
{

public:
    std::string significand;
    int exponent;
    int sign;
    int precision = DEFAULT_PRECISION;

public:
    hp_Number();
    hp_Number(const std::string s);
    hp_Number(int v);
    hp_Number(double v);
    void format();
    bool isZero();
    void set_prec(unsigned int _precision);
    // const std::string& getValue() const;
    double getDouble() const;
    // ~hp_Number();
    hp_Number operator +(const hp_Number& b);
    hp_Number operator -(const hp_Number& b);
    hp_Number operator *(const hp_Number& b);
    hp_Number operator /(const hp_Number& b);
    hp_Number pow(int power);

    // std::string getString() const;
    // hp_Number& operator +=(const hp_Number& b);
    // hp_Number& operator -=(const hp_Number& b);
    // hp_Number& operator *=(const hp_Number& b);
    // hp_Number& operator /=(const hp_Number& b);
};
#endif
