#ifndef _HIGH_PRECISION_H
#define _HIGH_PRECISION_H

#include <gmpxx.h>
#include <string>

#define DEFAULT_PRECISION 500
#define E "2.7182818284590452353602874713526624977572470936999595749669676277240766303535"

class hp_Number
{

private:
    mpf_class value;

public:
    hp_Number();
    hp_Number(const mpf_class v);
    hp_Number(const std::string s);
    hp_Number(int v);
    hp_Number(double v);
    const mpf_class& getValue() const;
    // ~hp_Number();
    hp_Number operator +(const hp_Number& b);
    hp_Number operator -(const hp_Number& b);
    hp_Number operator *(const hp_Number& b);
    hp_Number operator /(const hp_Number& b);
    // hp_Number pow(int power);

    std::string getString() const;
    hp_Number& operator +=(const hp_Number& b);
    hp_Number& operator -=(const hp_Number& b);
    hp_Number& operator *=(const hp_Number& b);
    hp_Number& operator /=(const hp_Number& b);

};
#endif
