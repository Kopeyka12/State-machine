// laba2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Rule.h"
#include "Language.h"
#include <iostream>

using namespace std;


enum State1 { H, N, P, S};
void Analizator1(string text) {
	State1 now = State1::H;
	int count = 0;
	string res = "";

	do {
		// проверка выхода за пределы индексации
		if (count < text.length()) {
			switch (now) {
			case State1::H: {
				if (text[count] == '1')
					now = State1::N;
				else if (text[count] == '0')
					now = State1::N;
				break;
			}
			case State1::N: {
				if (text[count] == '1')
					now = State1::N;
				else if (text[count] == '0')
					now = State1::N;
				else if (text[count] == '.')
					now = State1::P;
				break;
			}
			case State1::P: {
				if (text[count] == '0')
					now = State1::S;
				else if (text[count] == '1')
					now = State1::S;
				break;
			}
			case State1::S:
			{
				if (text[count] == '0')
					now = State1::S;
				else if (text[count] == '1')
					now = State1::S;
				break;
			}
			default:
				break;
			}

			if (now == 1)
			{
				res += "N";
				res += " ";
			}
			else if (now == 2)
			{
				res += "P";
				res += " ";
			}
			else if (now == 3)
			{
				res += "S";
				res += " ";
			}
			count++;
		}
		else {
			break;
		}
	} while (text[count] > text.length()); // now != State::S &&

	cout << res << std::endl;
}

enum State { H2, A, B, S2, ER };
void Analizator2(string text) {
	State now = State::H2;
	int count = 0;
	string res = "";

	do {
		// проверка выхода за пределы индексации
		if (count < text.length()) {
			switch (now) {
			case State::H2: {
				if (text[count] == '1')
					now = State::A;
				else if (text[count] == '0')
					now = State::A;
				else
					now = State::ER;
				break;
			}
			case State::A: {
				if (text[count] == '1')
					now = State::A;
				else if (text[count] == '0')
					now = State::A;
				else if (text[count] == '+')
					now = State::B;
				else if (text[count] == '-')
					now = State::B;
				else if (text[count] == '\u00A7')
					now = State::S2;
				else
					now = State::ER;
				break;
			}
			case State::B: {
				if (text[count] == '0')
					now = State::A;
				else if (text[count] == '1')
					now = State::A;
				else now = State::ER;
				break;
			}
			case State::S2:
			{
				break;
			}
			default:
				break;
			}

			if (now == 1)
			{
				res += "A";
				res += " ";
			}
			else if (now == 2)
			{
				res += "B";
				res += " ";
			}
			else if (now == 3)
			{
				res += "S";
				res += " ";
			}
			
			count++;
		}
		else {
			break;
		}
	} while (now != State::ER && now != State::S2); // now != State::S &&

	cout << res << std::endl;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Вторая лабораторная работа." << endl;
	
	cout << "Задание 1." << endl;

	list<Rule> dict1 = {
	Rule("S", "S0"),
	Rule("S", "S1"),
	Rule("S", "P0"),
	Rule("S", "P1"),
	Rule("P", "N."),
	Rule("N", "0"),
	Rule("N", "1"),
	Rule("N", "N0"),
	Rule("N", "N1")
	};

	PrintRules(dict1);

	cout << endl << "Анализатор:" << endl;
	cout << "Цевочка 11.010" << endl;
	Analizator1("11.010");
	
	cout << "Цевочка 0.1" << endl;
	Analizator1("0.1");
	
	cout << "Цевочка 01." << endl;
	Analizator1("01.");

	cout << "Цевочка 100" << endl;
	Analizator1("100");

	
	
	cout << endl << "Задание 2." << endl;
	cout << endl << "Подпункт a)" << endl;
	cout << "Анализатор:" << endl;
	cout << "Цевочка 1011\u00A7" << endl;
	Analizator2("1011\u00A7");
	cout << "Цевочка 10+011\u00A7" << endl;
	Analizator2("10+011\u00A7");
	cout << "Цевочка 0-101+1\u00A7" << endl;
	Analizator2("0-101+1\u00A7");

	cout << endl<< "Подпункт б)" << endl;
	list<Rule> dict2 = {
	Rule("S", "\u00A7A"),
	Rule("A", "A1"),
	Rule("A", "A0"),
	Rule("A", "B0"),
	Rule("A", "B1"),
	Rule("A", "0"),
	Rule("A", "1"),
	Rule("B", "A+"),
	Rule("B", "A-")
	};

	PrintRules(dict2);

	cout << "Грамматика: G: ({1, 0, +, -}, {A, B, S}, P, S)" << endl;
	
	
	
	
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
