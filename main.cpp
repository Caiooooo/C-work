#include "totalHead.h"
int main()
{
	library zlib;
	zlib.login();
}
int getNum(int start, int end) //���Ƿ�����
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
		cout << "�Ƿ�����,������!" << endl;
	}
}
// class function.cpp
void library::userMenu()
{
	cout << ("����������������������������������������������������������\n\
*      ͼ�����۹���ϵͳ      *\n\
*         1.���Ĺ���         *\n\
*         2.�鿴�鼮         *\n\
*         3.ע��             *\n\
*         4.�˳�             *\n\
����������������������������������������������������������\n");
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
	cout << ("����������������������������������������������������������\n\
*      ͼ�����۹���ϵͳ      *\n\
*         1.�鼮�鿴         *\n\
*         2.�û�����         *\n\
*         3.�鼮����         *\n\
*         4.ע��             *\n\
*         5.�˳�             *\n\
����������������������������������������������������������\n");
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
library::library() //�����û����鼮����
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
	/*����book��txt
	�鼮����
	�鼮
	����
	���
	�Ƿ񱻽���
	�Ƿ�ɾ��
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
	cout << "��������������������������������������������\n\
*   ͼ�����۹���ϵͳ  *\n\
*      1.��¼ϵͳ     *\n\
*      2.�˳�         *\n\
��������������������������������������������\n";
	getNum(1, 2); //ֻ�ܷ���1
	while (true)
	{
		string name, password;
		cout << "�������˻����ƣ�(Ĭ�Ϲ���Ա��root Ĭ����ͨ�û���normal-user)" << endl;
		getline(cin, name);
		cout << "�������˻����룺(Ĭ�����룺123456)" << endl;
		getline(cin, password);
		for (int i = 0; (unsigned)i < adminers.size(); i++)
		{
			if (name == adminers[i].getName() && password == adminers[i].getPwd())
			{
				root = 1;
				userNum = i;
				cout << "�𾴵�" << name << "����Ա,��½�ɹ�!" << endl;
				_sleep(1000);
				// initBookData();
				system("cls");
				rootMenu();
			}
		} //��¼����Ա
		for (int i = 0; (unsigned)i < adminers.size(); i++)
		{
			if (name == readers[i].getName() && password == readers[i].getPwd())
			{
				root = 0;
				userNum = i;
				cout << "�𾴵�" << name << "����,��½�ɹ�!" << endl;
				_sleep(1000);
				// initBookData();
				system("cls");
				userMenu();
			}
		} //��½��ͨ�û�
		cout << "�û��������벻��ȷ�����������룡" << endl;
		_sleep(1000);
		system("cls");
		cout << "��������������������������������������������\n\
*   ͼ�����۹���ϵͳ  *\n\
*      1.��¼ϵͳ     *\n\
*      2.�˳�         *\n\
��������������������������������������������\n";
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
} //���
void library::bookListMenu()
{
	cout << "��������������������������������������������\n\
*     �鼮���ҽ���    *\n\
*    1.ͨ����������   *\n\
*    2.ͨ�����߲���   *\n\
*    3.ͨ��������   *\n\
*    4.�г��ڹ��鼮   *\n\
*    5.������һ����   *\n\
*    6.�˳�          *\n\
��������������������������������������������\n";
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