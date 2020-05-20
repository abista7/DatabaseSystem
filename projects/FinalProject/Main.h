#pragma once

#include <Windows.h>
#include "Library.h"


class Run
{
	Library library;
public:
	Run()
	{
		while (true)
		{
			system("cls");
			cout << "Enter 1 For Create Account. " << endl;
			cout << "Enter 2 For Log in. " << endl;
			cout << "Enter 3 For Exit. " << endl;
			char option;
			cin >> option;
			switch (option)
			{
			case '1':
				library.CreateAccount();
				break;
			case '2':
				if (library.LogIn())
					run();
				else
					cout << "Invalid Account ... " << endl;
				break;
			case '3':
				library.Exit();
				break;
			default:
				cout << "Press a valid Option ..." << endl;
				break;
			}
			cout << "Please wait .... " << endl;
			Sleep(5000);
		}		
	}

private:

	void run()
	{
		while (true)
		{
			system("cls");
			switch (menu())
			{
			case '1':
				library.CreateAccount();
				break;
			case '2':
				if (library.LogIn())
					cout << "Successfully Log in ..." << endl;
				else
					cout << "Cannot Log in ..." << endl;
				break;
			case '3':
				library.Search();
				break;
			case '4':
				library.Insert();
				break;
			case '5':
				library.Update();
				break;
			case '6':
				library.Remove();
				break;
			case '7':
				library.Exit();
				break;
			default:
				cout << "Press a valid Option ..." << endl;
				break;
			}
			cout << "Please wait .... " << endl;
			Sleep(5000);
		}
	}

	char menu()
	{
		cout << "Press 1 for Create Account." << endl;
		cout << "Press 2 for Log in." << endl;
		cout << "Press 3 for Search." << endl;
		cout << "Press 4 for Insert." << endl;
		cout << "Press 5 for Update." << endl;
		cout << "Press 6 for Delete." << endl;
		cout << "Press 7 for Exit." << endl;
		char option;
		cin >> option;
		return option;
	}
};