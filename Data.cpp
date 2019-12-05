//
// Created by 朱宸 on 2019/12/5.
//
#include <string>
#include <iostream>
#include "Data.h"

using namespace std;

Data::Data() {
    country = "";
    points = 0;
    price = 0;
    province = "";
    variety = "";
}
Data::Data(string c, int poi, int pri, string pro, string v) {
    country = c;
    points = poi;
    price =pri;
    province = pro;
    variety = v;

}

ostream& operator<<(ostream& os, const Data& pr) {
    os << pr.country << ": " << pr.points<< ", " << pr.price<< "," << pr.province << ", "<< pr.variety;
    return os;
}


bool operator < (const Data& hr, const Data &d){
    return hr.price <d.price;
}
bool operator <= (const Data& hr, const Data &d) {
    return hr.price <= d.price;
}

bool operator>=(const Data& hr, const Data &d) {
    return hr.price>=d.price;
}
bool operator>(const Data& hr, const Data &d) {
    return hr.price>d.price;
}
Data& Data:: operator=(const Data &d){
    Data temp (d);

    swap(temp.country, country);
    swap(temp.points, points);
    swap(temp.price, price);
    swap(temp.province, province);
    swap(temp.variety, variety);

    return *this;
}

