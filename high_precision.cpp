#include "high_precision.h"
#include <string>
#include <algorithm>
#include <assert.h>

#define asciiOffset 0x30

void stringNumberBasicOperation(std::string a_significand,std::string b_significand, std::string &result_significand, bool isAdd);
void stringNumberBasicOperation_mul(std::string a_significand, char b, std::string& result_significand);

hp_Number::hp_Number()
{
    exponent = 0;
    significand = "0";
    sign = 1;
}

hp_Number::hp_Number(std::string s)
{
    exponent = 0;
    significand = "0";
    sign = 1;

    if(s[0]=='-'){
        sign = -1;
        s = s.substr(1);
    }
    size_t pointIndex = s.find('.');
    //　最后一位不是小数点，断言
    assert(pointIndex!=s.length()-1);

    // 没有小数点，则pointIndex=s.size()
    pointIndex = (pointIndex==std::string::npos)?s.length():pointIndex;
    exponent = pointIndex;
    if(pointIndex < s.length()){
        s.erase(pointIndex,1);
    }

    significand = s;
    format();
}

void hp_Number::format()
{
    if(isZero()){
        exponent = 0;
        significand = "0";
        sign = 1;
        return;
    }

    int i=0;
    for(char& c : significand){
        if(c=='0'){
            i++;
        }
        else{
            break;
        }
    }
    if(i!=0){
        exponent -= i;
        significand = significand.substr(i);
    }
    if(significand.length()>precision)
    {
        significand = significand.substr(0,precision);
    }
}

bool hp_Number::isZero()
{
    for(char& c : significand){
        if(c!='0'){
            return false;
        }
    }
    return true;
}

void hp_Number::set_prec(unsigned int _precision)
{
    precision = _precision;
}

hp_Number hp_Number::operator +(const hp_Number& b)
{
    hp_Number result;

    int a_exponent = exponent, b_exponent = b.exponent;
    std::string a_significand = significand, b_significand = b.significand;

    // 对齐小数点
    int _exp=std::max(a_exponent,b_exponent);
    a_significand = std::string(_exp - a_exponent,'0') + a_significand;
    b_significand = std::string(_exp - b_exponent,'0') + b_significand;
    a_exponent = b_exponent = _exp;

    result.exponent = _exp;

    // 开始计算
    std::string result_significand;

    // 同号相加，异号相减
    bool isAdd = false;
    if(sign==b.sign){
        isAdd = true;
    }

    // 进行字符形式的减法时可能会有交换
    int extraSign = 1;

    // 补到相同长度
    size_t tmpLength = std::max(a_significand.length(),b_significand.length());
    a_significand += std::string(tmpLength - a_significand.length(),'0');
    b_significand += std::string(tmpLength - b_significand.length(),'0');

    stringNumberBasicOperation(a_significand,b_significand,result_significand,isAdd);
    if(result_significand[0]=='-'){
        extraSign = -1;
        result_significand = result_significand.substr(1);
    }
    result.exponent += result_significand.length() - tmpLength;
    result.sign = sign*extraSign;
    result.significand = result_significand;
    result.format();

    return result;
}

hp_Number hp_Number::operator -(const hp_Number& b)
{
    hp_Number tmp = b;
    tmp.sign *= -1;
    return *this+tmp;
}

hp_Number hp_Number::operator *(const hp_Number& b)
{
    hp_Number result;
    result.sign = sign*b.sign;
    result.exponent = exponent+b.exponent;
    std::string result_significand;

    std::string a_significand = significand, b_significand = b.significand;
    for(int i=b_significand.length()-1;i>=0;i--){
        std::string term_significand;
        stringNumberBasicOperation_mul(a_significand,b_significand[i],term_significand);
        term_significand += std::string(b_significand.length()-1-i,'0');

        assert(result_significand.length()<=term_significand.length());
        result_significand = std::string(term_significand.length()-result_significand.length(),'0') + result_significand;

        std::string tmpResult;
        stringNumberBasicOperation(term_significand,result_significand,tmpResult,true);
        result_significand = tmpResult;
    }
    result.significand = result_significand;
    result.exponent += result.significand.length() - a_significand.length() - b_significand.length();
    result.format();

    return result;
}

hp_Number hp_Number::operator /(const hp_Number& _b)
{
    // 防止有效为高位有零
    format();
    hp_Number b=_b;
    b.format();
    assert(!b.isZero());

    hp_Number result;
    result.sign = sign*b.sign;
    result.exponent = exponent-b.exponent;
    std::string result_significand;

    std::string a_significand = significand, b_significand = b.significand;
    // 补到相同长度
    size_t tmpLength = std::max(a_significand.length(),b_significand.length());
    a_significand += std::string(tmpLength - a_significand.length(),'0');
    b_significand += std::string(tmpLength - b_significand.length(),'0');

    // 余数初始化为被除数
    std::string remainder = a_significand;

    // 开始计算有效值部分，迭代一次求出一位商
    for(int i=0;i<precision+5;i++){
        assert(remainder.length() <= b_significand.length()+1);

        // 商的估计
        int quotient;
        // 余数位数比除数少，则该位商取零
        if(remainder.length()<b_significand.length()){
            quotient=0;
        }
        // 余数位数比除数多1
        else if(remainder.length()==b_significand.length()+1){
            int r=(remainder[0]-asciiOffset)*10+remainder[1]-asciiOffset;
            quotient = r/(b_significand[0]-asciiOffset);
            if(quotient>9){
                quotient = 9;
            }
        }
        // 相同，则估计为高位相除
        else{
            quotient = (remainder[0]-asciiOffset)/(b_significand[0]-asciiOffset);
        }

        std::string product;
        // 商的确定
        while(1){
            // 商已经为0了，直接跳到后面
            if(quotient==0){
                goto newRemainder;
            }

            // 商不是0，得到乘积
            stringNumberBasicOperation_mul(b_significand,quotient+asciiOffset,product);
            // 乘积比余数大，商减一
            if((product.length() >= remainder.length()) && (product.length()>remainder.length() || remainder.compare(product)<0)){
                quotient -= 1;
                continue;
            }
            // 乘积比余数小或等于，余数减乘积得到新余数
            else{
                // 补零到等长
                product = std::string(remainder.length()-product.length(),'0') + product;
                std::string tmpRemainder;
                assert(remainder.length() == product.length());
                // 作差得到新余数
                stringNumberBasicOperation(remainder,product,tmpRemainder,false);
                assert(tmpRemainder[0]!='-');
                remainder = tmpRemainder;
            }
            newRemainder:
                // 去掉余数开始的零，可能会全部去掉，说明计算结束了
                int j=0;
                for(char& c:remainder){
                    if(c!='0'){
                        break;
                    }
                    j++;
                }
                remainder=remainder.substr(j);

                // 余数末尾加一个0，开始新一位商的计算
                remainder+=std::string(1,'0');

            // 商加入字符串
            result_significand+=std::string(1,(char)(quotient+asciiOffset));
            break;
        }
    }
    result.significand = result_significand;
    result.exponent += 1;
    result.format();
    return result;
}

hp_Number hp_Number::pow(int power)
{
    hp_Number tmpProduct("1");
    for(int i=0;i<std::abs(power);i++)
    {
        tmpProduct = tmpProduct*(*this);
    }
    if(power<0)
    {
        tmpProduct = hp_Number("1")/tmpProduct;
    }
    return tmpProduct;
}

// const mpf_class& hp_Number::getValue() const
// {
//     return value;
// }
//
// std::string hp_Number::getString() const
// {
//     // mp_exp_t exp;
//     // std::string significand = f.get_str(exp);
// }
//
// hp_Number& operator +=(const hp_Number& b)
// {
//     value += b.getValue();
//     return this;
// }
// hp_Number& operator -=(const hp_Number& b)
// {
//     value -= b.getValue();
//     return this;
// }
// hp_Number& operator *=(const hp_Number& b)
// {
//     value *= b.getValue();
//     return this;
// }
// hp_Number& operator /=(const hp_Number& b)
// {
//     value /= b.getValue();
//     return this;
// }

void stringNumberBasicOperation(std::string a_significand,std::string b_significand, std::string &result_significand, bool isAdd)
{
    assert(a_significand.length()==b_significand.length());
    size_t tmpLength = a_significand.length();
    int sign = 1;

    if(isAdd){
        // 加法
        // 进位
        char CF = 0;
        for(int i=tmpLength-1;i>=0;i--)
        {
            char _a = a_significand[i]-asciiOffset, _b = b_significand[i]-asciiOffset;
            char r = _a + _b + CF;
            CF = 0;
            if(r>=10){
                r -= 10;
                CF = 1;
            }
            result_significand = std::string(1,(char)(r+asciiOffset)) + result_significand;
        }
        if(CF==1){
            result_significand = std::string(1,(char)(CF+asciiOffset)) + result_significand;
            CF = 0;
        }
    }
    else{
        // 减法
        // 找到较大的一个
        std::string greater,littler;
        if(a_significand.compare(b_significand)>=0){
            greater = a_significand;
            littler = b_significand;
            sign = 1;
        }
        else{
            greater = b_significand;
            littler = a_significand;
            sign = -1;
        }
        // 借位
        char CF = 0;
        for(int i=tmpLength-1;i>=0;i--)
        {
            char _a = greater[i]-asciiOffset, _b = littler[i]-asciiOffset;
            char r = _a - CF - _b;
            CF = 0;
            if(r<0){
                r += 10;
                CF = 1;
            }
            result_significand = std::string(1,(char)(r+asciiOffset)) + result_significand;
        }
        // 还有借位，那一定是出错了，结束
        assert(CF==0);
    }
    if(sign==-1)
    {
        result_significand = std::string(1,'-') + result_significand;
    }
}

void stringNumberBasicOperation_mul(std::string a_significand, char b, std::string& result_significand)
{
    char carry = 0;
    char _b = b - asciiOffset;
    std::string &term_significand = result_significand;

    term_significand = "";
    for(int j=a_significand.length()-1;j>=0;j--){
        char _a = a_significand[j]-asciiOffset;
        char r = _a * _b + carry;
        carry = 0;
        carry = r/10;
        r = r%10;
        term_significand = std::string(1,(char)(r+asciiOffset)) + term_significand;
    }
    if(carry!=0){
        term_significand = std::string(1,(char)(carry+asciiOffset)) + term_significand;
        carry = 0;
    }
}

double hp_Number::getDouble() const
{
    double _significand = std::stod(std::string("0.") + significand);
    _significand *= std::pow(10,exponent);
    return _significand;
}
