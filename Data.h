//
// Created by 朱宸 on 2019/12/5.
//

#ifndef PROJECT9_DATA_H
#define PROJECT9_DATA_H

using namespace std;

class Data {
public:
    Data ();
    Data(string c, int poi, int pri, string pro, string v);
    friend ostream& operator<<(ostream& os, const Data& pr);
    friend bool operator >= (const Data& hr, const Data &d);
    friend bool operator < (const Data& hr, const Data &d);
    friend bool operator > (const Data& hr, const Data &d);
    friend bool operator <= (const Data& hr, const Data &d);
    Data& operator = (const Data &d);


    string country;
    int points;
    int price;
    string province;
    string variety;

};
#endif //PROJECT9_DATA_H
