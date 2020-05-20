#pragma once
#include <fstream>
#include <iostream>
#include <vector>

#include <mysql_connection.h>

#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <Windows.h>

using namespace std;
using namespace sql;

class Database
{
	Driver* driver;
	Connection* connection;
	Statement* statement;
	ResultSet* resultSet;
	bool isConnected;
	fstream file;
	string database;

public:
	Database()
	{
		driver = NULL;
		connection = NULL;
		statement = NULL;
		resultSet = NULL;
		isConnected = false;
	}

	Database(string host, string userName, string password)
	{
		try
		{
			driver = get_driver_instance();
			connection = driver->connect(host, userName, password);
			isConnected = true;
			statement = connection->createStatement();
			cout << "Succesfully connected ..." << endl;
		}
		catch (const sql::SQLException& e)
		{
			isConnected = false;
			cout << "Cannot connected ..." << endl;
		}
	}

	~Database()
	{
		delete connection;
		delete statement;
		isConnected = false;
	}

	void connect(string host, string userName, string password)
	{
		if (!isConnected)
		{
			driver = get_driver_instance();
			connection = driver->connect(host, userName, password);
			isConnected = true;
			statement = connection->createStatement();
			cout << "Succesfully connected ..." << endl;
		}
		else
		{
			cout << "You have already connected ..." << endl;
		}
	}

	int ConnectDB(string databaseName)
	{
		if (isConnected)
		{
			try
			{
				connection->setSchema(databaseName);
				database = databaseName;
				cout << "Succesfully connected with database ..." << endl;				
				return 1;
			}
			catch (const sql::SQLException&)
			{
				cout << "Connot connect with Database ... " << endl;				
				if (isFileExist(databaseName))
				{
					Backup(databaseName);
					return 1;
				}
				else
				{
					cout << "No such database exist ..." << endl;
					return 0;
				}				
			}
		}
		else
		{
			cout << "You have not connected ..." << endl;
			return 0;
		}
	}

	int createDatabase(string databaseName)
	{
		if (isConnected)
		{
			try
			{
				string query = "create database " + databaseName + ";";
				statement->execute(query);
				cout << "Database created succesfully ..." << endl;						
				return 1;
			}
			catch (const sql::SQLException&)
			{
				cout << "Cannot create database ..." << endl;
				return 0;
			}
		}
		else
		{
			cout << "You have not connected ..." << endl;
			return 0;
		}
	}

	void createTable(string tableName, vector<string> attributeName, vector<string> dataTypes, string constrains)
	{
		if (isConnected)
		{
			try
			{
				if (attributeName.size() != dataTypes.size()) return;
				SQLString query = "create table " + tableName + " ( ";
				for (size_t i = 0; i < attributeName.size(); i++)
				{
					if (i != 0)
						query += ",";
					query += attributeName[i] + " " + dataTypes[i];
				}
				query += ", " + constrains + " );";
				statement->execute(query);
				cout << "Successfully created table ..." << endl;
			}
			catch (const sql::SQLException&)
			{
				cout << "Cannot create table ..." << endl;
			}
		}
		else
		{
			cout << "You have not connected ..." << endl;
		}
	}

	int insert(string tableName,vector<string> keys, vector<string> values)
	{
		if (isConnected)
		{
			try
			{
				SQLString query = "insert into " + tableName + "( ";
				for (size_t i = 0; i < keys.size(); i++)
				{
					if (i != 0)
						query += ",";
					query += keys[i];
				}
				query += ") values (";
				for (size_t i = 0; i < values.size(); i++)
				{
					if (i != 0)
						query += ",";
					query += "'" + values[i] + "'";
				}
				query += ");";
				int execute = statement->executeUpdate(query);
				if (execute)
				{
					cout << "Successfully insert into table ..." << endl;
					file.open(database.c_str(), ios::out | ios::app);
					file << query << endl;
					file.close();
					return execute;
				}
				else
				{
					cout << "Cannot insert into table ..." << endl;
					return execute;
				}
			}
			catch (const sql::SQLException& e)
			{
				cout << "Cannot insert into table ..." << endl;
				return -1;
			}
		}
		else
		{
			cout << "You are not connected with database ..." << endl;
			return -1;
		}
	}

	int Delete(string tableName, string where="1=1")
	{
		if (isConnected)
		{
			try
			{
				SQLString query = "delete from " + tableName + " where " + where;				
				int execute = statement->executeUpdate(query);
				if (execute)
				{
					cout << "Succesfully deleted from table ..." << endl;
					file.open(database.c_str(), ios::out | ios::app);
					file << query << endl;
					file.close();
					return execute;
				}
				else
				{
					cout << "Cannot delete from table ..." << endl;
					return execute;
				}
			}
			catch (const sql::SQLException&)
			{
				cout << "Cannot delete from table ..." << endl;
				return -1;
			}
		}
		else
		{
			cout << "You are not connected with database ..." << endl;
			return -1;
		}
	}

	int Delete(string tables, string tableName, string where = "1=1")
	{
		if (isConnected)
		{
			try
			{
				SQLString query = "delete " + tables +" from " + tableName + " where " + where;
				int execute = statement->executeUpdate(query);
				if (execute)
				{
					cout << "Succesfully deleted from table ..." << endl;
					file.open(database.c_str(), ios::out | ios::app);
					file << query << endl;
					file.close();
					return execute;
				}
				else
				{
					cout << "Cannot delete from table ..." << endl;
					return execute;
				}
			}
			catch (const sql::SQLException&)
			{
				cout << "Cannot delete from table ..." << endl;
				return -1;
			}
		}
		else
		{
			cout << "You are not connected with database ..." << endl;
			return -1;
		}
	}


	vector<vector<string>> select(string tableName, string columns="*", string where="1=1")
	{
		if (isConnected)
		{
			try
			{
				vector<vector<string>> result;
				SQLString query = "select " + columns +" from " + tableName + " where " + where + ";";
				resultSet = statement->executeQuery(query);
				if (resultSet)
				{
					while (resultSet->next())
					{
						vector<string> temp;
						for (int i = 1; i <= resultSet->getMetaData()->getColumnCount(); i++)
						{
							temp.push_back(resultSet->getString(i));
						}
						result.push_back(temp);
					}
					cout << "Successfully retrive data ... " << endl;
					delete resultSet;
					return result;
				}
				else
				{
					cout << "cannot select from table ... " << endl;
					return vector<vector<string>>();
				}
			}
			catch (const sql::SQLException&)
			{
				cout << "cannot select from table ... " << endl;
				return vector<vector<string>>();
			}
		}
		else
		{
			cout << "You are not connected with database ..." << endl;
			return vector<vector<string>>();
		}
	}

	int update(string tableName, vector<string> keys, vector<string> values, string where = "1=1")
	{
		if (isConnected)
		{
			try
			{
				if (keys.size() != values.size()) return -1;
				SQLString query = "update " + tableName + " set ";
				for (size_t i = 0; i < keys.size(); i++)
				{
					if (i != 0)
						query += ",";
					query += keys[i] + " = '" + values[i]+"'";
				}
				query += " where " + where;
				int execute = statement->executeUpdate(query);
				if (execute)
				{
					cout << "Successfully update into table ..." << endl;
					file.open(database.c_str(), ios::out | ios::app);
					file << query << endl;
					file.close();
					return execute;
				}
				else
				{
					cout << "Cannot upadte into table ..." << endl;
					return execute;
				}
			}
			catch (const sql::SQLException&)
			{
				cout << "Cannot upadte into table ..." << endl;
				return -1;

			}
		}
		else
		{
			cout << "You are not connected with database ..." << endl;
			return -1;
		}
	}

	bool getIsConnected() const
	{
		return isConnected;
	}

	void close()
	{
		if (isConnected)
		{
			try
			{
				connection->close();
				isConnected = false;
				cout << "Succesfully close connection " << endl;
			}
			catch (const sql::SQLException&)
			{
				cout << "Cannot close connection ..." << endl;
			}
		}
		else
		{
			cout << "You are not connected ..." << endl;
		}
	}

	void executeQuery(SQLString query)
	{
		try
		{
			statement->executeUpdate(query);
		}
		catch (const sql::SQLException& e)
		{
			cout << "# ERR: SQLException in " << __FILE__ << " ";
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			/* what() (derived from std::runtime_error) fetches error message */
			cout << "# ERR: " << e.what() << endl;
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		}
	}


private:
	bool isFileExist(string fileName)
	{
		file.open(fileName.c_str(), ios::in | ios::out);
		bool is = file.is_open();
		file.close();
		return is;
	}

	void Backup(string databaseName)
	{
		system("cls");
		file.open(databaseName.c_str(), ios::in);
		cout << "Preparing database ..." << endl;
		Sleep(2000);
		createDatabase(databaseName);
		ConnectDB(databaseName);
		createTable("users", vector<string> {"id", "user_name", "user_password"}, vector<string> {"int auto_increment not null", "nvarchar(50) not null", "nvarchar(100) not null"}, "constraint pk_user_id primary key (id)");
		createTable("Author", vector<string> {"id", "author_name", "details"}, vector<string> {"int auto_increment not null", "nvarchar(50) not null", "nvarchar(100) not null"}, "constraint pk_author_id primary key (id)");
		createTable("Books", vector<string> {"id", "ISBN", "title", "publisher", "author_id"}, vector<string> {"int auto_increment not null", "bigint not null", "nvarchar(100) not null", "nvarchar(100) not null", "int not null"}, "constraint pk_book_id primary key (id), constraint fk_book_author foreign key (author_id) references Author (id) on update cascade on delete cascade");
		while (!file.eof())
		{
			string temp;
			getline(file, temp);
			executeQuery(temp);
		}
		file.close();
		cout << "Please wait ... " << endl;
		Sleep(3000);
		database = databaseName;
	}
	
};