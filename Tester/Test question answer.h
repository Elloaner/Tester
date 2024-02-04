#pragma once
#include "Person and User.h"
#include <vector>

using namespace std;

class Answer
{
public:
	string text;
	bool correct;
	Answer(string text, bool correct)
		: text(text), correct(correct)
	{
		
	}
};

class Question
{
public:
	string text;
	vector<Answer> answers;

	virtual void check() = 0;
	virtual void show() = 0;
};

class OpenQuestion : public Question
{
public:
	OpenQuestion(string text)
	{
		this->text = text;
	}
	virtual void check() override
	{
		string userAnswer;
		cout << "Your answer: ";
		cin.ignore();
		getline(cin, userAnswer);

		if (isCorrectAnswer(userAnswer))
		{
			cout << "Correct Answer!" << endl;
		}
		else
		{
			cout << "Wrong Answer!" << endl;
		}
	}
	void show() override
	{
		cout << text << endl;
	}
private:
	bool isCorrectAnswer(const string& userAnswer)
	{
		return (userAnswer.find("correct") != string::npos);
	}
};



class Test : public Question
{
public:
	Test(string text, vector<Answer> answers)
	{
		this->text = text;
		this->answers = answers;
	}

	virtual void check() override
	{
		char userAnswer;
		cout << "Your answer (a, b, c, d): ";
		cin >> userAnswer;

		size_t index = userAnswer - 'a';

		if (index < answers.size() && answers[index].correct)
		{
			cout << "Correct Answer!" << endl;
		}
		else
		{
			cout << "Wrong Answer!" << endl;
		}
	};

	void show() override
	{
		cout << text << endl;
		char variant = 'a';
		for (size_t i = 0; i < 4; i++)
		{
			cout << variant++ << ") " << answers[i].text << " ";
		}
		cout << endl; cout << endl;
	}
};