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
        data_.push_back(a % 10);
        data_.push_back(a / BASE);
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
    bool less = (this->abs() < rhs.abs());

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
            data_.push_back(rhs.data_[i] + over);
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

    for (size_t i = 0; i < mn.data_.size(); ++i)
    {
        if (mx.data_[i] < mn.data_[i])
        {
            mx.data_[i] += BASE;
            size_t j = i + 1;
            while (mx.data_[j] == 0)
            {
                mx.data_[j] = BASE - 1;
                ++j;
            }
            mx.data_[j]--;
            if (mx.data_[j] == 0)
            {
                mx.data_.erase(mx.data_.begin() + j);
            }
        }
        mx.data_[i] -= mn.data_[i];
    }
    while (mx.data_.size() > 1 && mx.data_.back() == 0)
    {
        mx.data_.pop_back();
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
            t = t * rhs.data_[i] + over;
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

std::pair<big_integer, big_integer> big_integer::division(big_integer const& rhs)
{
    if (rhs.is_zero())
    {
        throw std::runtime_error("Runtime error: division by zero");
    }

    big_integer a(*this);
    big_integer b(rhs);
    bool ans_sign = a.sign_ != b.sign_;
    a.sign_ = false;
    b.sign_ = false;

    if (a < b)
    {
        return { big_integer(), *this };
    }

    std::vector<int32_t> tmp_data;
    big_integer div;
    big_integer mod;
    div.data_.clear();

    for (size_t i = a.data_.size() - 1;; --i)
    {
        tmp_data.push_back(a.data_[i]);
        big_integer tmp_big;
        tmp_big.data_.clear();
        std::reverse(tmp_data.begin(), tmp_data.end());
        for (size_t j = 0; j < tmp_data.size(); ++j)
        {
            tmp_big.data_.push_back(tmp_data[j]);
        }
        std::reverse(tmp_data.begin(), tmp_data.end());
        if (tmp_big >= b)
        {
            tmp_data.clear();
            size_t l = 0, r = BASE;
            while (l + 1 < r)
            {
                size_t m = (l + r) / 2;
                big_integer tmp(b);
                tmp *= m;
                if (tmp_big >= tmp)
                {
                    l = m;
                }
                else
                {
                    r = m;
                }
            }
            div *= big_integer(BASE);
            div += l;
            mod = tmp_big - (b * l);
            if (!mod.is_zero())
            {
                for (size_t j = mod.data_.size() - 1;; --j)
                {
                    tmp_data.push_back(mod.data_[j]);
                    if (j == 0)
                    {
                        break;
                    }
                }
            }
        }
        if (i == 0)
        {
            break;
        }
        mod.data_.clear();
    }
    div.sign_ = ans_sign;
    if (this->sign_)
    {
        mod.sign_ = true;
    }
    return { div, mod };
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

big_integer& big_integer::operator/=(big_integer const& rhs)
{
    *this = division(rhs).first;
    return *this;
}

big_integer& big_integer::operator%=(big_integer const& rhs)
{
    *this = division(rhs).second;
    return *this;
}

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

big_integer operator/(big_integer a, big_integer const& b)
{
    return a /= b;
}

big_integer operator%(big_integer a, big_integer const& b)
{
    return a %= b;
}

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
    for (size_t i = a.data_.size() - 1;; --i)
    {
        if (a.data_[i] != b.data_[i])
        {
            return a.sign_ ? a.data_[i] > b.data_[i] : a.data_[i] < b.data_[i];
        }
        if (i == 0)
        {
            break;
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