#ifndef _TOTALHEAD_H_
#define _TOTALHEAD_H_

#include <iostream>
#include <vector>
#include <map>
#include <string.h>
#include <conio.h>
#include<fstream>
#define INF (1 << 31)
#define MAXLEN 100
using namespace std;
int idGiver; //为每个书籍分配唯一id
class Book;
class adminer;
class reader;
class Book
{
private:
    string name, bookClass, author;
    bool ifBorrowed, ifExist;
    int id; //书籍唯一的
    vector<string> *classification;
public:
    Book(string _name, int _id,string _author,vector<string> *v,bool _ifBorrowed,bool _ifDeleted);
    Book(const Book &b);
    ~Book() {delete classification;}
};
class People // 用于生成管理员和普通用户子类
{
private:
    string name, password;

public:
    People(string name, string pwd);
    ~People() {}
    string getName() { return name; }
    string getPwd() { return password; }
};
class adminer : public People
{
public:
    adminer(string name, string pwd) : People(name, pwd) {}
    void addUser();
    void addBorrow();
    void addReturn();
};
class reader : public People
{
private:
    vector<int> books;

public:
    reader(string name, string pwd, vector<int> v) : People(name, pwd)
    {
        for (int i = 0; i < v.size(); i++)
            books.push_back(v[i]);
    } //链表深拷贝
    void returnBook();
    void borrowBook();
};
class library
{
private:
    vector<adminer> adminers;
    vector<reader> readers;
    vector<Book> books;
    int root;    //当前用户是否为管理员
    int userNum; //用于找到用户数据
public:
    library();
    void login();
    void userMenu();
    void rootMenu();
    void bookListMenu();
    void listAllBook();
    void findBookByName();
    void findBookByAuthor();
    void findBookByID();
};

#endif
