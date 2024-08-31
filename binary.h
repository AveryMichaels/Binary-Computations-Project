#pragma once
#include <string>

using namespace std;

class Binary {
private:
    string* arr;
    int pos;
public:
    Binary(const int);
    ~Binary();
    void push(string);
    string operator[](int);
    bool isBinary(string&);
    void addLeadingZeros(const int);
    string addZeros(string, string);
    void removeZeros(string&);
    void swap(int, int);
    void swap(string&, string&);
    string add(const int);
    string add(string*, const int);
    string subtract(const int);
    string subtract(string*, const int);
    string multiply(const int);
    string divide(const int);
};