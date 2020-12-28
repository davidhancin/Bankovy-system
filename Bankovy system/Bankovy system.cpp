#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;


void uvod()
{
	cout << "\n\n\t------------------";
	cout << "\n\n\t     BANKOVY";
	cout << "\n\n\t     SYSTEM";
	cout << "\n\n\t   David Hancin";
	cout << "\n\n\t------------------";
	cin.get();
}

int acno;
char name[30];
long balance;

void OpenAccount()
{
	cout << "Enter Account Number: ";
	cin >> acno;
	cout << "Enter Name: ";
	cin >> name;
	cout << "Enter  Balance: ";
	cin >> balance;
}


int main()
{
	char ch;
	uvod();


	system("cls");
	cout << "\n\n\t       MENU";
	cout << "\n\n\t01. OPEN ACCOUNT" << endl;
	cout << "\n\n\t02. CLOSE ACCOUNT" << endl;
	cout << "\n\n\t03. SHOW ALL ACCOUNTS" << endl;
	cout << "\n\n\t04. DEPOSIT IN ACCOUNT" << endl;
	cout << "\n\n\t05. WITHDRAW FROM ACCOUNT" << endl;
	cout << "\n\n\t06. EXIT" << endl;
	cout << "\n\n\tSelect Your Option (1-6) " << endl;
	cin >> ch;
	system("cls");
	switch (ch)
	{
	case '1':
		OpenAccount();
		break;
	}



	return 0;
}
