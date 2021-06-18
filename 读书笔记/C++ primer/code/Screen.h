#include <iostream>

using namespace std;

class String;
istream& operator>>(istream &, String &);
ostream& operator<<(ostream &, const String &);

class String{
public:
    String(const char* = 0);
    String(const String&);

    ~String();

    String& operator= (const String &);
    String& operator= (const char*);

    String& operator+= (const String&);
    String& operator+= (const char*);

    char& operator[] (int) const; //const表示这个函数不会修改任何数据成员

    bool operator== (const char*) const;
    bool operator== (const String&) const;

    int size(){ return _size;}
    char* c_str(){ return _string;}


    int getCount(){ return count;}
private:
    static const int count = 0;
    // static const char name[10] = "vivo";

    int _size;
    char* _string;
};