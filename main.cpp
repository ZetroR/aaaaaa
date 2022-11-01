#include "std_lib_facilities.h"
#include "tokens.h"
#include "variables.h"
#include "grammar.h"


const string prompt = "> ";
const string result = "= ";
const string entery_message =
"Добро пожаловать в программу-калькулятор! \n"
"Вводите выражения с числами с плавающей точкой. \n"
"Возможные действия: \n"
"      > операции +, -, *, /, ^, % и ! \n"
"      > встроенныe функции sqrt() и abs() \n"
"      > объявление обявление и использование пременных (let x = ...) и констант (const x = ...) \n"
"      > изменение значения переменных (set x = ...)"
"      > скобки (), {}, [] \n"
"----------------------------------------------------------------------------------------------- \n"
"Для завершение ввода введите \";\" или нажмите Enter \n"
"Для выхода из программы введите \"q\" \n";

Symbol_table vt;
Token_stream ts;

void calculate() 
{
	cout << entery_message;

	while (cin)
	try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) { t = ts.get(); }
		if (t.kind == quit) { return; }
		ts.putback(t);
		cout << result << statement(ts, vt) << '\n';
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
		clean_up_mess(ts);
	
	}
}
 
int main() {
	setlocale(LC_ALL, "Russian");

	vt.define("pi", 3.1415926535, true);
	vt.define("e",  2.7182818284, true);

	try
	{

		calculate();
		keep_window_open();
		return 0;
	}
	catch (exception& e)
	{
		cerr << e.what() << '\n';
		keep_window_open("~~");
		return 1;
	}
	catch (...)
	{
		cerr << "исключение" << '\n';
		keep_window_open("~~");
		return 2;
	}
}