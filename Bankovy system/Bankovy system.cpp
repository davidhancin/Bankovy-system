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


class bank
{
	int anum;
	char name[30];
	long balance;


public:
	void openaccount();
	void report() const;
	void dep(int);
	int retacno() const;


};

void bank::openaccount()
{
	cout << "\n\n\tEnter Account Number: ";
	cin >> anum;
	cout << "\n\n\tEnter Name: ";
	cin >> name;
	cout << "\n\n\tEnter  Balance: ";
	cin >> balance;
}


void bank::report() const
{
	cout << anum << setw(10) << " " << name << setw(10) << " " << setw(6) << balance << endl;
}

void bank::dep(int x)
{
	balance += x;
}

int bank::retacno() const
{
	return anum;
}


void create_account();
void uvod();
void display_all();
void delete_account(int);


//HLAVNA FUNKCIA 

int main()
{
	int n;
	char ch;
	uvod();

	do
	{

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
			create_account();
			break;
		case '2':
			cout << "\n\n\tEnter The account Number : ";
			cin >> n;
			delete_account(n);
			break;
			break;
		case '3':
			display_all();
			break;
		case '4':
			create_account();
			break;
		case '5':
			create_account();
			break;
		case '6':
			cout << "\n\n\tHave a nice day" << endl;
			break;

		}
		cin.ignore();
		cin.get();
	} while (ch != '6');
	return 0;
}



void create_account()
{
	bank ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.openaccount();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(bank));
	outFile.close();
}


void display_all()
{
	bank ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);

	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "Ac.num.     NAME           Balance\n";
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(bank)))
	{
		ac.report();
	}
	inFile.close();
}


void delete_account(int n)
{
	bank ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "\n\n\tThere are no accounts";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(bank)))
	{
		if (ac.retacno() != n)
		{
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(bank));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\n\tRecord Deleted ..";
}
