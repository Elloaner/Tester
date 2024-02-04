#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Person
{
protected:
	string FullName;
	string HomeAdress;
	string MobileNumber;
public:
	Person(string fname, string hadress, string mnum)
		: FullName(fname), HomeAdress(hadress), MobileNumber(mnum)
	{}
};

class User : public Person
{
private:
	string Login;
	string Password;
public:
	User()
		: Person("", "", ""), Login(""), Password("")
	{}

	User(string fname, string hadress, string mnum, string login, string password)
		: Person(fname, hadress, mnum), Login(login), Password(password)
	{}

	void Register()
	{
		cin.ignore();
		cout << "Enter your full name : ";
		getline(cin, FullName);
		cout << "Enter your home address : ";
		getline(cin, HomeAdress);
		cout << "Enter your mobile number : ";
		getline(cin, MobileNumber);
		string path = "data.txt";
		ifstream file(path);
		if (!file.is_open())
		{
			cout << "File failed to open" << endl;
			return;
		}
		cout << "Enter your login : ";
		getline(cin, Login);
		string line;
		while (getline(file, line))
		{
			if (line.find("Login : " + Login) != string::npos)
			{
				file.close();
				cout << "Login is already taken. Please choose a different login." << endl;
				return;
			}
		}
		file.close();
		cout << "Enter your password : ";
		getline(cin, Password);
		RegisterWrite();
	}

	bool LoginUser(string enteredLogin, string enteredPassword)
	{
		string path = "data.txt";
		ifstream file(path);
		if (!file.is_open())
		{
			cout << "File failed to open" << endl;
			return false;
		}
		string line;
		while (getline(file, line))
		{
			if (line.find("Login : " + enteredLogin) != string::npos)
			{
				getline(file, line);
				if (line.find("Password : " + enteredPassword) != string::npos)
				{
					file.close();
					return true;
				}
			}
		}
		file.close();
		return false;
	}

private:
	void RegisterWrite()
	{
		string path = "data.txt";
		fstream file;
		file.open(path, fstream::in | fstream::out | fstream::app);
		if (file.is_open())
		{
			file << "Full Name : " << FullName << endl;
			file << "Home Address : " << HomeAdress << endl;
			file << "Mobile Number : " << MobileNumber << endl;
			file << "Login : " << Login << endl;
			file << "Password : " << Password << endl;
			file << "------------------------" << endl;
			file.close();
		}
		else
		{
			cout << "File failed to open" << endl;
		}
	}
};