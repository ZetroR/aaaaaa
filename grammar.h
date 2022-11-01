#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "std_lib_facilities.h"
#include "tokens.h"
#include "variables.h"

double factorial(double n);


void clean_up_mess(Token_stream &ts);


double statement(Token_stream &ts, Symbol_table &vt);

double decloration(Token_stream &ts, Symbol_table &vt);			// ���������� ����������
double const_decloration(Token_stream &ts, Symbol_table &vt);	// ���������� ���������
double equasion(Token_stream &ts, Symbol_table &vt);			// ���������� ���������� ��������

double expression(Token_stream &ts, Symbol_table &vt);			// +, -
double term(Token_stream &ts, Symbol_table &vt);				// *, /
double power(Token_stream &ts, Symbol_table &vt);				// ^
double fact(Token_stream &ts, Symbol_table &vt);				// !
double primary(Token_stream &ts, Symbol_table &vt);				// (), {}, [], sqrt(), abs(), �����, ����������, +primary, -primary


#endif // GRAMMAR_H
