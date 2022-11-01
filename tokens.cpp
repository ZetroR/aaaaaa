#include "tokens.h"


void  Token_stream::putback(Token t)
// Предусловие: в буффере нет ни одного объекта класса Token
{
	if (full) { error("putback(): буффер заполнен"); }
	buffer = t;
	full = true;
}

Token Token_stream::get()
{	// Чтение символов из cin и составление Token
	if (full) { full = false;  return buffer; }

	char ch; cin.get(ch);

	while (ch == ' ') { cin.get(ch); }

	switch (ch) {
	case '\n':
	{
		return Token{ print };
	}
	case '=':									// Для переменных
	case print:									// Для вывода 
	case quit:									// Для выхода
	case '(': case ')':							// |
	case '[': case ']':							// | ->  Разновидности скобок
	case '{': case '}':							// |
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':									// Остаток от деления
	case '!':									// Факториал
	case '^':									// Степень
	{
		return Token{ ch };		// Каждый литерал представляет сам себя
	}
	// Числовой литерал:
	case '.':									// Число с плавающей точкой может начинаться с точки 
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9': {
		cin.putback(ch);
		double val;
		cin >> val;
		return Token{ number, val }; }
	// Комманда либо переменная:
	default: {
		if (isalpha(ch)) 
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) { s += ch; }
			cin.putback(ch);

			// Является ли введённое слово командой
			if (s == constdeclkey) { return Token{ constant }; }
			if (s == declkey) { return Token{ let }; }
			if (s == setkey) { return Token{ set }; }
			if (s == sqrtkey) { return Token{ sqrt_ }; }
			if (s == abskey) { return Token{ abs_ }; }
			return Token{ name, s };	// Токен переменной

		}
	}
		error("Неверная лексема");
	}
}

void  Token_stream::ignore(char c)
// Игнорируем ввод до тех пор пока не встретим символ c
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch = 0;
	while (cin >> ch) { if (c == ch) return; }
}