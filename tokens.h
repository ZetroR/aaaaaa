#ifndef TOKENS_H
#define TOKENS_H
#include "std_lib_facilities.h"

class Token {
public:
	char kind;		// Разновидность лексемы
	double value;	// Для чисел: значение
	string name;	// Для переменных: имя

	// Инициализирует kind символом ch
	Token(char ch) : kind{ ch } {};

	// Инициализирует kind и value (для чисел)
	Token(char ch, double val) : kind{ ch }, value{ val } {};

	// Инициализирует kind и name (для переменных)
	Token(char ch, string n) : kind{ ch }, name{ n } {};
};

class Token_stream {
public:
	Token_stream() { }

	Token get();					// Получение лексемы.
	void putback(Token t);			// Возврат лексемы в поток.
	void ignore(char c);			// Игнорировать ввод лексем до следующей c
private:
	bool full{ false };				// Имеется ли лексема в буфере?
	Token buffer{ '\0' };			// Здесь хранится лексема после
									// возврата с помощью putback().
};


const char number = '8';	// t.kind==number означает, что t - число 
const char quit = 'q';		// t.kind==quit означает, что t - лексема выхода
const char print = ';';		// t.kind==print означает, что t - лексема печати
const char name = 'N';
const char let = 'L';
const char set = 'S';
const char constant = 'C';
const char sqrt_ = 's';
const char abs_ = 'a';

const string declkey = "let";
const string setkey = "set";
const string constdeclkey = "const";
const string sqrtkey = "sqrt";
const string abskey = "abs";

#endif // TOKEN_H