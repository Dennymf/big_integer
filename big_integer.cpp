#include "big_integer.h"

bool big_integer::is_zero() const
{
    return data_.size() == 1 && data_[0] == 0;
}

std::vector<int> big_integer::data()
{
    return data_;
}

big_integer::big_integer()
    : data_({ 0 }), sign_(false) {}

big_integer::big_integer(big_integer const& other)
    : data_(other.data_), sign_(other.sign_) {}

big_integer::big_integer(int a)
{
    if (a < 0)
    {
        sign_ = true;
        a *= -1;
    }
    
    if (a < BASE)
    {
        data_.push_back(a);
    }
    else
    {
        data_.push_back(a / 10);
        data_.push_back(a % 10);
    }
}

big_integer::big_integer(std::string const& str)
{
    if (str[0] == '-')
    {
        sign_ = true;
    }

    int start = (sign_ ? 1 : 0);
    for (size_t i = str.size(); i > start; i -= digits_)
    {
        if ((int)(i - digits_) > start)
        {
            data_.push_back(std::stoi(str.substr(i - digits_, digits_)));
        }
        else
        {
            data_.push_back(std::stoi(str.substr(start, i - start)));
            break;
        }
    }
}

big_integer::~big_integer() = default;

big_integer& big_integer::operator=(big_integer const& other) = default;

big_integer& big_integer::add(big_integer const& rhs)
{
    int over = 0;
    bool less = (*this < rhs);

    for (size_t i = 0; i < std::min(data_.size(), rhs.data_.size()); ++i)
    {
        data_[i] = rhs.data_[i] + data_[i] + over;
        over = data_[i] / BASE;
        data_[i] %= BASE;
    }
    for (size_t i = std::min(data_.size(), rhs.data_.size()); i < std::max(data_.size(), rhs.data_.size()); ++i)
    {
        if (less)
        {
            data_.push_back(rhs.data_[i]);
            over = data_[i] / BASE;
            data_[i] %= BASE;
        }
        data_[i] += over;
        over = data_[i] / BASE;
        data_[i] %= BASE;
    }
    if (over > 0)
    {
        data_.push_back(over);
    }
    return *this;
}

big_integer& big_integer::sub(big_integer const& rhs)
{
    big_integer this_abs = this->abs();
    big_integer rhs_abs = rhs.abs();
    big_integer mx = this_abs > rhs_abs ? *this : rhs;
    big_integer mn = this_abs < rhs_abs ? *this : rhs;
    bool neg = (this_abs < rhs_abs) && (this->sign_ == rhs.sign_);

    for (size_t i = 0; i < mx.data_.size(); ++i)
    {
        if (mx.data_[i] < mn.data_[i])
        {
            mx.data_[i] += BASE;
            size_t j = i + 1;
            while (mx.data_[j] == 0)
            {
                mx.data_[j] = BASE - 1;
            }
            mx.data_[j]--;
        }
        mx.data_[i] -= mn.data_[i];
    }
    if (neg)
    {
        mx.sign_ = !mx.sign_;
    }
    *this = mx;

    return *this;
}

big_integer& big_integer::mul(big_integer const& rhs)
{
    big_integer cur = big_integer();
    cur.sign_ = false;

    for (size_t i = 0; i < rhs.data_.size(); ++i)
    {
        big_integer tmp = big_integer();
        if (i)
        {
            for (size_t j = 0; j < i - 1; ++j)
            {
                tmp.data_.push_back(0);
            }
            for (size_t j = 0; j < data_.size(); ++j)
            {
                tmp.data_.push_back(data_[j]);
            }
        }
        else
        {
            tmp = *this;
        }
        tmp.sign_ = false;
        int64_t over = 0;
        for (size_t j = 0; j < tmp.data_.size(); ++j)
        {
            int64_t t = tmp.data_[j];
            t *= rhs.data_[i] + over;
            over = t / BASE;
            tmp.data_[j] = t % BASE;
        }
        if (over)
        {
            tmp.data_.push_back(over);
        }
        cur += tmp;
    }
    cur.sign_ =  (this->sign_ != rhs.sign_);
    *this = cur;
    return *this;
}

big_integer big_integer::abs() const
{
    big_integer tmp = *this;
    tmp.sign_ = false;
    return tmp;
}

big_integer& big_integer::operator+=(big_integer const& rhs)
{
    return (sign_ == rhs.sign_ ? add(rhs) : sub(rhs));
}

big_integer& big_integer::operator-=(big_integer const& rhs)
{
    return (sign_ == rhs.sign_ ? sub(rhs) : add(rhs));
}

big_integer& big_integer::operator*=(big_integer const& rhs)
{
    return mul(rhs);
}

//big_integer& big_integer::operator/=(big_integer const& rhs)
//{
//    return *this;
//}
//
//big_integer& big_integer::operator%=(big_integer const& rhs)
//{
//    return *this;
//}
//
//big_integer& big_integer::operator&=(big_integer const& rhs)
//{
//    return *this;
//}
//
//big_integer& big_integer::operator|=(big_integer const& rhs)
//{
//    return *this;
//}
//
//big_integer& big_integer::operator^=(big_integer const& rhs)
//{
//    return *this;
//}
//
//big_integer& big_integer::operator<<=(int rhs)
//{
//    return *this;
//}
//
//big_integer& big_integer::operator>>=(int rhs)
//{
//    return *this;
//}
//
big_integer big_integer::operator+() const
{
    big_integer tmp(*this);
    tmp.sign_ = false;
    return tmp;
}

big_integer big_integer::operator-() const
{
    if (is_zero())
    {
        return *this;
    }
    big_integer tmp(*this);
    tmp.sign_ = !tmp.sign_;
    return tmp;
}

big_integer big_integer::operator~() const
{

    return -(*this) -= big_integer(1);
}

big_integer& big_integer::operator++()
{
    return *this += big_integer(1);
}

big_integer big_integer::operator++(int)
{
    big_integer tmp(*this);
    ++(*this);
    return tmp;
}

big_integer& big_integer::operator--()
{
    return *this -= big_integer(1);
}

big_integer big_integer::operator--(int)
{
    big_integer tmp(*this);
    --(*this);
    return tmp;
}

big_integer operator+(big_integer a, big_integer const& b)
{
    return a += b;
}

big_integer operator-(big_integer a, big_integer const& b)
{
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const& b)
{
    return a *= b;
}

//big_integer operator/(big_integer a, big_integer const& b)
//{
//    return a;
//}
//
//big_integer operator%(big_integer a, big_integer const& b)
//{
//    return a;
//}
//
//big_integer operator&(big_integer a, big_integer const& b)
//{
//    return a;
//}
//
//big_integer operator|(big_integer a, big_integer const& b)
//{
//    return a |= b;
//}
//
//big_integer operator^(big_integer a, big_integer const& b)
//{
//    return a;
//}
//
//big_integer operator<<(big_integer a, int b)
//{
//    return a <<= b;
//}
//
//big_integer operator>>(big_integer a, int b)
//{
//    return a;
//}
//
bool operator==(big_integer const& a, big_integer const& b)
{
    if (a.sign_ != b.sign_ || a.data_.size() != b.data_.size())
    {
        return false;
    }
    for (size_t i = 0; i < a.data_.size(); ++i)
    {
        if (a.data_[i] != b.data_[i])
        {
            return false;
        }
    }
    return true;
}

bool operator!=(big_integer const& a, big_integer const& b)
{
    return !(a == b);
}

bool operator<(big_integer const& a, big_integer const& b)
{
    if (a.sign_ != b.sign_)
    {
        return a.sign_ > b.sign_;
    }
    if (a.data_.size() != b.data_.size())
    {
        return a.sign_ ? a.data_.size() > b.data_.size() : a.data_.size() < b.data_.size();
    }
    for (size_t i = 0; i < a.data_.size(); ++i)
    {
        if (a.data_[i] != b.data_[i])
        {
            return a.sign_ ? a.data_[i] > b.data_[i] : a.data_[i] < b.data_[i];
        }
    }
    return false;
}

bool operator>(big_integer const& a, big_integer const& b)
{
    return !(a <= b);
}

bool operator<=(big_integer const& a, big_integer const& b)
{
    return (a < b) || (a == b);
}

bool operator>=(big_integer const& a, big_integer const& b)
{
    return !(a < b);
}

std::string to_string(big_integer const& a)
{
    std::string out;
    if (a.sign_)
    {
        if (a.data_.size() > 1 || !a.is_zero())
        {
            out = "-";
        }
    }
    for (int i = a.data_.size() - 1; i >= 0; i--)
    {
        std::string tmp = std::to_string(a.data_[i]);
        while (tmp.size() < a.digits_ && (i != a.data_.size() - 1))
        {
            tmp = "0" + tmp;
        }
        out += tmp;
    }
    return out;
}

//std::ostream& operator<<(std::ostream & s, big_integer const& a)
//{
//    return s << to_string(a);
//}