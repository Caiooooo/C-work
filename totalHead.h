#ifndef _TOTALHEAD_H_
#define _TOTALHEAD_H_

#include <iostream>
#include <vector>
#include <map>
#define INF (1 << 31)
#define MAXLEN 100
using namespace std;
void initData();
void login();
class Book // �������ɸ���������� ��ֱ��ʹ��
{
private:
    string name, bookNumber, bookClass, author;
    bool ifBorrowed;
    int id; //Ψһ��
public:
    Book(string _name, int id, string _bookClass, string _author);
    ~Book() {}
};
class People
{
private:
    string name, password;
    vector<int> book;

public:
    People(string name);
    ~People() {}
    void borrowBook(){};
    void returnBook(){};
};

#endif
