#ifndef TOKENS_H
#define TOKENS_H
#include "std_lib_facilities.h"

class Token {
public:
	char kind;		// ������������� �������
	double value;	// ��� �����: ��������
	string name;	// ��� ����������: ���

	// �������������� kind �������� ch
	Token(char ch) : kind{ ch } {};

	// �������������� kind � value (��� �����)
	Token(char ch, double val) : kind{ ch }, value{ val } {};

	// �������������� kind � name (��� ����������)
	Token(char ch, string n) : kind{ ch }, name{ n } {};
};

class Token_stream {
public:
	Token_stream() { }

	Token get();					// ��������� �������.
	void putback(Token t);			// ������� ������� � �����.
	void ignore(char c);			// ������������ ���� ������ �� ��������� c
private:
	bool full{ false };				// ������� �� ������� � ������?
	Token buffer{ '\0' };			// ����� �������� ������� �����
									// �������� � ������� putback().
};


const char number = '8';	// t.kind==number ��������, ��� t - ����� 
const char quit = 'q';		// t.kind==quit ��������, ��� t - ������� ������
const char print = ';';		// t.kind==print ��������, ��� t - ������� ������
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