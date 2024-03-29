#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <algorithm>
#include <cstdint>
#include <functional>
#include <fstream>
#include <iosfwd>
#include <stdexcept>
#include <string>
#include <vector>

struct big_integer
{
private:
    static const int BASE = 1'000'000'000;
    static const int digits_ = 9;
    std::vector<int32_t> data_;
    bool sign_ = false;
    bool is_zero() const;

public:
    std::vector<int32_t> data();
    big_integer();                                                         
    big_integer(big_integer const& other);                                 
    big_integer(int a);                                                    
    explicit big_integer(std::string const& str);                          
    ~big_integer();                                                        
                                                                           
    big_integer& operator=(big_integer const& other);                      

    big_integer& add(big_integer const& rhs);
    big_integer& sub(big_integer const& rhs);
    big_integer& mul(big_integer const& rhs);
    std::pair<big_integer, big_integer> division(big_integer const& rhs);
    big_integer abs() const;
    template<typename T>
    big_integer& logical_op(big_integer const& rhs, T const& op);

    big_integer& operator+=(big_integer const& rhs);
    big_integer& operator-=(big_integer const& rhs);
    big_integer& operator*=(big_integer const& rhs);
    big_integer& operator/=(big_integer const& rhs);
    big_integer& operator%=(big_integer const& rhs);

    big_integer& operator&=(big_integer const& rhs);
    big_integer& operator|=(big_integer const& rhs);
    big_integer& operator^=(big_integer const& rhs);

    big_integer& operator<<=(int rhs);
    big_integer& operator>>=(int rhs);

    big_integer operator+() const;
    big_integer operator-() const;
    big_integer operator~() const;

    big_integer& operator++();
    big_integer operator++(int);

    big_integer& operator--();
    big_integer operator--(int);

    friend bool operator==(big_integer const& a, big_integer const& b);
    friend bool operator!=(big_integer const& a, big_integer const& b);
    friend bool operator<(big_integer const& a, big_integer const& b);
    friend bool operator>(big_integer const& a, big_integer const& b);
    friend bool operator<=(big_integer const& a, big_integer const& b);
    friend bool operator>=(big_integer const& a, big_integer const& b);

    friend std::string to_string(big_integer const& a);
};

big_integer operator+(big_integer a, big_integer const& b);
big_integer operator-(big_integer a, big_integer const& b);
big_integer operator*(big_integer a, big_integer const& b);
big_integer operator/(big_integer a, big_integer const& b);
big_integer operator%(big_integer a, big_integer const& b);

big_integer operator&(big_integer a, big_integer const& b);
big_integer operator|(big_integer a, big_integer const& b);
big_integer operator^(big_integer a, big_integer const& b);

big_integer operator<<(big_integer a, int b);
big_integer operator>>(big_integer a, int b);

bool operator==(big_integer const& a, big_integer const& b);
bool operator!=(big_integer const& a, big_integer const& b);
bool operator<(big_integer const& a, big_integer const& b);
bool operator>(big_integer const& a, big_integer const& b);
bool operator<=(big_integer const& a, big_integer const& b);
bool operator>=(big_integer const& a, big_integer const& b);

std::string to_string(big_integer const& a);
std::ostream& operator<<(std::ostream& s, big_integer const& a);

#endif

