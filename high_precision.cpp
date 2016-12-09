#include "high_precision.h"
#include <string>

hp_Number::hp_Number()
{
    value = "0.0";
    value.set_prec(DEFAULT_PRECISION);
}

hp_Number::hp_Number(std::string s)
{
    value = s.c_str();
    value.set_prec(DEFAULT_PRECISION);
}

hp_Number::hp_Number(int v)
{
    value = v;
    value.set_prec(DEFAULT_PRECISION);
}

hp_Number::hp_Number(double v)
{
    value = v;
    value.set_prec(DEFAULT_PRECISION);
}

hp_Number::hp_Number(const mpf_class v)
{
    value = v;
    value.set_prec(DEFAULT_PRECISION);
}

hp_Number hp_Number::operator +(const hp_Number& b)
{
    return hp_Number(value+b.getValue());
}
hp_Number hp_Number::operator -(const hp_Number& b)
{
    return hp_Number(value-b.getValue());
}
hp_Number hp_Number::operator *(const hp_Number& b)
{
    return hp_Number(value*b.getValue());
}
hp_Number hp_Number::operator /(const hp_Number& b)
{
    return hp_Number(value/b.getValue());
}

// hp_Number pow(int power)
// {
//     // return hp_Number(value.pow(power));
// }

const mpf_class& hp_Number::getValue() const
{
    return value;
}

std::string hp_Number::getString() const
{
    // mp_exp_t exp;
    // std::string significand = f.get_str(exp);
}

hp_Number& operator +=(const hp_Number& b)
{
    value += b.getValue();
    return this;
}
hp_Number& operator -=(const hp_Number& b)
{
    value -= b.getValue();
    return this;
}
hp_Number& operator *=(const hp_Number& b)
{
    value *= b.getValue();
    return this;
}
hp_Number& operator /=(const hp_Number& b)
{
    value /= b.getValue();
    return this;
}
