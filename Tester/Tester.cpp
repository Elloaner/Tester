#include "Person and User.h"
#include "Test question answer.h"
#include <Windows.h>

using namespace std;

void Quiz(vector<Question*>& questions);
void writeResultsToFile(const vector<Question*>& questions, const string& fileName);

int main()
{
	User user; short select{}; bool logged = false;
	do
	{
		cout << "\t\t\t1. Login\n\t\t\t2. Register" << endl;
		cin >> select;
		if (select == 1)
		{
			string login, password;
			cout << "Enter your login :" << endl;
			cin >> login;
			cout << "Enter your password :" << endl;
			cin >> password;
			if (user.LoginUser(login, password))
			{
				cout << "Logged in" << endl;
				Sleep(1000);
				logged = true;
				system("cls");
			}
			else
			{
				cout << "Wrong login or password" << endl;
				Sleep(1000);
				logged = false;
				system("cls");
			}
		}
		else if (select == 2)
		{
			user.Register();
			logged = false;
		}
		else
		{
			cout << "Wrong operation" << endl;
		}
	} while (logged != true);
	
	vector<Question*> questionsPuzzles
	{
		new Test(string("Clean,but not water,\nWhite, but not snow,\nSweet, but not ice cream.\nWhat is it?"),
			{ {"Salt", false}, {"Sugar", true}, {"Brown Sugar", false}, {"Sea Salt", false} }),
		new Test(string("What goes up when the rain comes down?"), { {"Umbrella", true}, {"Water", false}, {"Snow", false }, {"Ice", false}})
	};
	vector<Answer> Puzzles;
	vector<Question*> questionsMath
	{
		new Test(string("11 * 11"), { {"111", false}, {"101", false}, {"121", true}, {"131", false} }),
		new Test(string("55 + 44 + 33 + 22 + 11"), { {"165", true}, {"145", false}, {"163", false}, {"167", false} }),
		new Test(string("5(4 + 5)"), { {"60", false}, {"50", false}, {"40", false}, {"45", true} }),
		new Test(string("5 * 9/3"), { {"15", true}, {"3", false}, {"60", false}, {"24", false} }),
		new Test(string("3257 + 8549 - 1158"), { {"10638", false}, {"10648", true}, {"10658", false}, {"10668", false} }),
		new Test(string("2x - 7 = 11"), { {"x = 9", true}, {"x = 2", false}, {"8", false}, {"4", false} })
	};
	short selectCategory{};
	cout << "\t\tSelect your test\n1. Riddles\n2. Math" << endl;
	cin >> selectCategory;
	system("cls");
	if(selectCategory == 1)
	{
		Quiz(questionsPuzzles);
	}
	else if (selectCategory == 2)
	{
		Quiz(questionsMath);
	}
	else
	{
		cout << "Wrong operation" << endl;
	}
}

void Quiz(const vector<Question*>& questions) 
{
	for (size_t i = 0; i < questions.size(); i++) 
	{
		questions[i]->show();
		questions[i]->check();
		if (i < questions.size() - 1) {
			cout << "Press Enter to continue to the next question..." << endl;
			cin.ignore();
			cin.get();
			system("cls");
		}
	}
	writeResultsToFile(questions, "test_results.txt");
}

void writeResultsToFile(const vector<Question*>& questions, const string& fileName) 
{
	ofstream file(fileName);
	if (file.is_open()) 
	{
		file << "Test Results:\n";
		for (size_t i = 0; i < questions.size(); i++) 
		{
			file << "Question " << i + 1 << ": ";
			questions[i]->show();
			questions[i]->check();
			file << endl;
		}
		file.close();
		cout << "Test results have been written to the file." << endl;
	}
	else 
	{
		cerr << "Unable to open the file for writing." << endl;
	}
}