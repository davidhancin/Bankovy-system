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
	void draw(int);
	int retdeposit() const;
	void showaccount() const;

};

void bank::openaccount()
{
	cout << "\n\n\tZadajte číslo účtu: ";
	cin >> anum;
	cout << "\n\n\tZadajte meno: ";
	cin >> name;
	cout << "\n\n\tZadajte vklad: ";
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

void bank::draw(int x)
{
	balance -= x;
}

int bank::retdeposit() const
{
	return balance;
}

void bank::showaccount() const
{
	cout << "\nČíslo účtu : " << anum;
	cout << "\nMeno majiteľa účtu : ";
	cout << name;
	cout << "\nZostatok : " << balance;
}

void create_account();
void uvod();
void display_all();
void delete_account(int);
void deposit_withdraw(int, int);

//HLAVNA FUNKCIA 

int main()
{
	setlocale(LC_ALL, "");
	int n;
	char ch;
	uvod();

	do
	{

		system("cls");
		cout << "\n\n\t       MENU";
		cout << "\n\n\t01. Vytvoriť účet" << endl;
		cout << "\n\n\t02. Zavrieť účet" << endl;
		cout << "\n\n\t03. Zobraziť všetky účty" << endl;
		cout << "\n\n\t04. Vklad na účet" << endl;
		cout << "\n\n\t05. Výber z účtu" << endl;
		cout << "\n\n\t06. Exit" << endl;
		cout << "\n\n\tVyber možnosť (1-6) " << endl;
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			create_account();
			break;
		case '2':
			cout << "\n\n\tZadajte číslo účtu : ";
			cin >> n;
			delete_account(n);
			break;
			break;
		case '3':
			display_all();
			break;
		case '4':
			cout << "\n\n\tZadajte číslo účtu : "; cin >> n;
			deposit_withdraw(n, 1);
			break;
		case '5':
			cout << "\n\n\tZadajte číslo účtu : "; cin >> n;
			deposit_withdraw(n, 2);
			break;
		case '6':
			cout << "\n\n\tPekný deň" << endl;
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

	cout << "\n\n\t\tZOZNAM UCTOV\n\n";
	cout << "====================================================\n";
	cout << "čis.uč.     Meno           Zostatok\n";
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
		cout << "\n\n\tNeexistujú žiadne účty";
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
	cout << "\n\n\tZáznam bol odstránený";
}


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	bank ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(bank));
		if (ac.retacno() == n)
		{
			ac.showaccount();
			if (option == 1)
			{
				cout << "\n\n\tVKLAD ";
				cout << "\n\nZadajte čiastku ktorá sa má vložiť";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tVYBER";
				cout << "\n\nZadajte čiastku ktorá sa má vybrať";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				ac.draw(amt);


			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(bank));
			cout << "\n\n\t Záznam bol aktualizovaný";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Účet nebol nájdený ";
}