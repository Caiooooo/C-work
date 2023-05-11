#include "totalHead.h"
int main()
{
    vector<People> Readers;
    initData();
    People a("add");
    Readers.push_back(a);
    Readers[0].borrowBook();
}
void initData()
{
}
