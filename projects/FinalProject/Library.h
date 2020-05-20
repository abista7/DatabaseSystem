#pragma once

#include "Database.h"

class Library
{
	Database db;
	string host = "tcp://127.0.0.1:3306";
	string userName = "root";
	string password = "0987654321";
	string database = "Library";
	
public:

	Library()
	{
		db.connect(host, userName, password);
		if (db.getIsConnected())
		{
			if (db.ConnectDB(database) == 0)
			{
				db.createDatabase(database);
				db.ConnectDB(database);
				db.createTable("users", vector<string> {"id", "user_name", "user_password"}, vector<string> {"int auto_increment not null", "nvarchar(50) not null", "nvarchar(100) not null"}, "constraint pk_user_id primary key (id)");
				db.createTable("Author", vector<string> {"id", "author_name", "details"}, vector<string> {"int auto_increment not null", "nvarchar(50) not null", "nvarchar(100) not null"}, "constraint pk_author_id primary key (id)");
				db.createTable("Books", vector<string> {"id", "ISBN", "title", "publisher", "author_id"}, vector<string> {"int auto_increment not null", "bigint not null", "nvarchar(100) not null", "nvarchar(100) not null", "int not null"}, "constraint pk_book_id primary key (id), constraint fk_book_author foreign key (author_id) references Author (id) on update cascade on delete cascade");
			}
		}
	}

	void CreateAccount()
	{
		string name;
		string password;
		string rechkPassword;
		do {
			system("cls");
			cin.ignore();
			cout << "Enter name : ";
			getline(cin, name);
			cout << "Enter password : ";
			getline(cin, password);
			cout << "Re-Enter password : ";
			getline(cin, rechkPassword);
		} while (password != rechkPassword);
		if (!isUserExist(name, password))
			db.insert("users", vector<string> {"user_name", "user_password"}, vector<string> {name, password});
		else
			cout << "User already exist ..." << endl;
	}

	bool LogIn()
	{
		string name;
		string password;
		system("cls");
		cin.ignore();
		cout << "Enter name : ";
		getline(cin, name);
		cout << "Enter password : ";
		getline(cin, password);
		return isUserExist(name, password);
	}

	void Search()
	{
		string query;
		cout << "Enter Book by ISBN or title : ";
		cin.ignore();
		getline(cin, query);
		if (db.getIsConnected())
		{
			vector<vector<string>> res = db.select("Books as b join Author as a on a.id = b.author_id","b.title, b.ISBN, b.publisher, a.author_name, a.details","b.ISBN = '"+ query +"' or b.title ='" + query + "'");
			if (res.size() != 0)
			{
				for (size_t i = 0; i < res.size(); i++)
				{
					cout << "Title : " << res[i][0] << endl;
					cout << "ISBN : " << res[i][1] << endl;
					cout << "Publisher : " << res[i][2] << endl;
					cout << "Author Name : " << res[i][3] << endl;
					cout << "About author : " << res[i][4] << endl;
				}
			}
			else
			{
				cout << "No result Found ..." << endl;
			}
		}
	}

	void Insert()
	{
		if (db.getIsConnected()) 
		{
			string title;
			string ISBN;
			string author;
			string author_details;
			string publisher;
			cin.ignore();
			cout << "Enter Book title : ";
			getline(cin, title);
			cout << "Enter Book ISBN : ";
			getline(cin, ISBN);
			cout << "Enter Author Name : ";
			getline(cin, author);
			cout << "Enter about Author : ";
			getline(cin, author_details);
			cout << "Enter publisher : ";
			getline(cin, publisher);
			db.insert("Author", vector<string> {"author_name", "details"}, vector<string> {author, author_details});
			vector<vector<string>> id = db.select("Author", "id", " author_name = '" + author + "'");
			db.insert("Books", vector<string> {"ISBN", "title", "publisher","author_id"}, vector<string> {ISBN, title, publisher,id[0][0]});
		}
	}

	void Update()
	{
		if (db.getIsConnected())
		{
			string toUpdate;
			string title;
			string ISBN;
			string author;
			string author_details;
			string publisher;

			cin.ignore();
			cout << "Enter Book title or ISBN for update : ";
			getline(cin, toUpdate);

			cout << "Enter Book title : ";
			getline(cin, title);
			cout << "Enter Book ISBN : ";
			getline(cin, ISBN);
			cout << "Enter Author Name : ";
			getline(cin, author);
			cout << "Enter about Author : ";
			getline(cin, author_details);
			cout << "Enter publisher : ";
			getline(cin, publisher);

			db.update("Author join Books on Books.author_id = Author.id", vector<string> {"Books.ISBN", "Books.title", "Books.publisher", "Author.author_name", "Author.details"}, vector<string> {ISBN, title, publisher, author, author_details}, "Books.title = '" + toUpdate + "' or  Books.ISBN = '" + toUpdate + "'");
		}
	}

	void Remove()
	{
		string query;
		cin.ignore();
		cout << "Enter Book title or ISBN : ";
		getline(cin, query);
		db.Delete("Author", "Author join Books on Books.author_id = Author.id", "Books.title = '" + query + "' or Books.ISBN = '" + query + "'");
	}

	void Exit()
	{
		exit(0);
	}

private:

	bool isUserExist(string name, string password)
	{
		vector<vector<string>> res = db.select("users", "user_name, user_password");
		for (size_t i = 0; i < res.size(); i++)
		{
			if (res[i][0] == name && res[i][1] == password)
				return true;
		}
		return false;
	}
};


