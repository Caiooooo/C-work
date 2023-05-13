#include "totalHead.h"
int main()
{
	library zlib;
	zlib.login();
}
int getNum(int start, int end) //检查非法输入
{
	string num;
	while (true)
	{
		getline(cin, num);
		if (to_string(end) == num)
			exit(0);
		for (int i = start; i < end; i++)
			if (to_string(i) == num)
				return i;
		cout << "非法输入,请重试!" << endl;
	}
}
// class function.cpp
void library::userMenu()
{
	cout << ("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\
*      图书销售管理系统      *\n\
*         1.借阅管理         *\n\
*         2.查看书籍         *\n\
*         3.注销             *\n\
*         4.退出             *\n\
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	switch (getNum(1, 4))
	{
	case 1:
		system("cls");
		break;
	case 2:
		bookListMenu();
		userMenu();
		break;
	case 3:
		system("cls");
		login();
		break;
	}
}
void library::rootMenu()
{
	cout << ("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\
*      图书销售管理系统      *\n\
*         1.书籍查看         *\n\
*         2.用户管理         *\n\
*         3.书籍管理         *\n\
*         4.注销             *\n\
*         5.退出             *\n\
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	switch (getNum(1, 5))
	{
	case 1:
		bookListMenu();
		rootMenu();
		break;
	case 4:
		system("cls");
		login();
		break;
	}
}

People::People(string _name, string pwd)
{
	name = _name;
	password = pwd;
}
library::library() //读入用户和书籍数据
{
	FILE *peopleData = fopen("user.txt", "rb");
	while (!feof(peopleData))
	{
		int root = 0;
		char name[100], password[100];
		if (fscanf(peopleData, "%s", name))
		{
			if (!strcmp(name, "-1"))
				break;
			fscanf(peopleData, "%s %d", password, &root);
			if (root)
			{
				adminer ROOT(name, password);
				adminers.push_back(ROOT);
			}
			else
			{
				int book;
				vector<int> books;
				fscanf(peopleData, "%d", &book);
				while (book != -1)
				{
					books.push_back(book);
					fscanf(peopleData, "%d", &book);
				}
				reader READER(name, password, books);
				readers.push_back(READER);
			}
		}
		else
			break;
	}
	fclose(peopleData);
	/*关于book，txt
	书籍数量
	书籍
	作者
	类别
	是否被借阅
	是否被删除
	*/
	ifstream in("book.txt");
	in >> idGiver;
	string bookName, bookAuthor;
	bool ifBorrow, ifDeleted;
	for (int i = 0; i < idGiver; i++)
	{
		getline(in, bookName);
		getline(in, bookName);
		getline(in, bookAuthor);
		vector<string> *ss = new vector<string>;
		string s;
		in >> s;
		while (s != "-1")
		{
			ss->push_back(s);
			in >> s;
		}
		in >> ifBorrow >> ifDeleted;
		Book b(bookName, i, bookAuthor, ss, ifBorrow, ifDeleted);
	}
}
void library::login()
{
	cout << "━━━━━━━━━━━━━━━━━━━━━━\n\
*   图书销售管理系统  *\n\
*      1.登录系统     *\n\
*      2.退出         *\n\
━━━━━━━━━━━━━━━━━━━━━━\n";
	getNum(1, 2); //只能返回1
	while (true)
	{
		string name, password;
		cout << "请输入账户名称：(默认管理员：root 默认普通用户：normal-user)" << endl;
		getline(cin, name);
		cout << "请输入账户密码：(默认密码：123456)" << endl;
		getline(cin, password);
		for (int i = 0; (unsigned)i < adminers.size(); i++)
		{
			if (name == adminers[i].getName() && password == adminers[i].getPwd())
			{
				root = 1;
				userNum = i;
				cout << "尊敬的" << name << "管理员,登陆成功!" << endl;
				_sleep(1000);
				// initBookData();
				system("cls");
				rootMenu();
			}
		} //登录管理员
		for (int i = 0; (unsigned)i < adminers.size(); i++)
		{
			if (name == readers[i].getName() && password == readers[i].getPwd())
			{
				root = 0;
				userNum = i;
				cout << "尊敬的" << name << "读者,登陆成功!" << endl;
				_sleep(1000);
				// initBookData();
				system("cls");
				userMenu();
			}
		} //登陆普通用户
		cout << "用户名或密码不正确，请重新输入！" << endl;
		_sleep(1000);
		system("cls");
		cout << "━━━━━━━━━━━━━━━━━━━━━━\n\
*   图书销售管理系统  *\n\
*      1.登录系统     *\n\
*      2.退出         *\n\
━━━━━━━━━━━━━━━━━━━━━━\n";
	}
}
Book::Book(string _name, int _id, string _author, vector<string> *v, bool _ifBorrowed, bool _ifDeleted)
{
	name = _name;
	id = _id;
	author = _author;
	classification = v;
	ifBorrowed = _ifBorrowed;
	ifExist = _ifDeleted;
}
Book::Book(const Book &b)
{
	name = b.name;
	id = idGiver++;
	author = b.author;
	for (int i = 0; i < (b.classification)->size(); i++)
		classification[i] = (b.classification)[i];
} //深拷贝
void library::bookListMenu()
{
	cout << "━━━━━━━━━━━━━━━━━━━━━━\n\
*     书籍查找界面    *\n\
*    1.通过书名查找   *\n\
*    2.通过作者查找   *\n\
*    3.通过类别查找   *\n\
*    4.列出在馆书籍   *\n\
*    5.返回上一界面   *\n\
*    6.退出          *\n\
━━━━━━━━━━━━━━━━━━━━━━\n";
	int ope = getNum(1, 6);
	switch (ope)
	{
	case 1:
		findBookByName();
		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:
		system("cls");
		return;
		break;
	}
}