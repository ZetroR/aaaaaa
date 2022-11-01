#include "grammar.h"


double factorial(double n)
{
	double res = 1;

	for (int i = 1; i <= n; ++i) { res *= i; }
	return res;
}

void clean_up_mess(Token_stream &ts) { ts.ignore(print); }



double statement(Token_stream &ts, Symbol_table &vt)
{
	Token t = ts.get();
	switch (t.kind) {
	case set: {
		return equasion(ts, vt);
	}
	case let: {
		return decloration(ts, vt);
	}
	case constant: {
		return const_decloration(ts, vt);
	}
	default: {
		ts.putback(t);
		return expression(ts, vt);
	}
	}
}


double const_decloration(Token_stream &ts, Symbol_table &vt)
{
	Token t = ts.get();
	if (t.kind != name) { error("в объ€влении ожидаетс€ им€ константы"); }
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') { error("пропущен символ = в объ€влении ", var_name); }

	double d = expression(ts, vt);
	vt.define(var_name, d, true);
	return d;
}

double equasion(Token_stream &ts, Symbol_table &vt)
{
	Token t = ts.get();
	if (t.kind != name) { error(" в присвоении ожидаетс€ им€ переменной"); }
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') { error("пропущен символ = в присвоении ", var_name); }

	double d = expression(ts, vt);
	vt.set(var_name, d);
	return d;
}

double decloration(Token_stream &ts, Symbol_table &vt)
{
	Token t = ts.get();
	if (t.kind != name) { error("в объ€влении ожидаетс€ им€ переменной"); }
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') { error("пропущен символ = в объ€влении ", var_name); }

	double d = expression(ts, vt);
	vt.define(var_name, d, false);
	return d;
}


double expression(Token_stream &ts, Symbol_table &vt)
{
	double left = term(ts, vt);
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '+':
		{
			left += term(ts, vt);
			t = ts.get();
			break;
		}
		case '-':
		{
			left -= term(ts, vt);
			t = ts.get();
			break;
		}
		default:
		{
			ts.putback(t);
			return left;
		}
		}
	}
}

double term(Token_stream &ts, Symbol_table &vt)
{
	double left = power(ts, vt);
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*': {
			left *= power(ts, vt);
			t = ts.get();
			break;
		}
		case '/': {
			double d = power(ts, vt);
			if (d == 0) { error("ƒеление на нуль"); }

			left /= d;
			t = ts.get();
			break;
		}
		case '%': {
			double d = power(ts, vt);
			if (d == 0) { error(""); }
			left = left - d * int(left / d);
			t = ts.get();
			break;
		}
		default:
		{
			ts.putback(t);
			return left;
		}
		}
	}
}

double power(Token_stream &ts, Symbol_table &vt)
{
	double left = fact(ts, vt);
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '^': {
			double d = fact(ts, vt);
			if (d != int(d)) { error("pow: значение степени не €вл€етс€ целым числом ", d); }

			left = pow(left, d);
			t = ts.get();
			break;
		}
		default:
		{
			ts.putback(t);
			return left;
		}
		}
	}
}

double fact(Token_stream &ts, Symbol_table &vt)
{
	double left = primary(ts, vt);
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '!': {
			left = factorial(left);
			t = ts.get();
			break;
		}
		default:
		{
			ts.putback(t);
			return left;
		}
		}
	}
}

double primary(Token_stream &ts, Symbol_table &vt)
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression(ts, vt);
		t = ts.get();
		if (t.kind != ')') { error("“ребуетс€ ')'"); }
		return d;
	}
	case '[':
	{
		double d = expression(ts, vt);
		t = ts.get();
		if (t.kind != ']') { error("“ребуетс€ ']'"); }
		return d;
	}
	case '{':
	{
		double d = expression(ts, vt);
		t = ts.get();
		if (t.kind != '}') { error("“ребуетс€ '}'"); }
		return d;
	}
	case sqrt_:
	{
		double d = primary(ts, vt);
		if (d < 0) { error("sqrt: число под корнем сеньше нул€, а именно ", d); }
		return sqrt(d);
	}
	case abs_: {
		return abs(primary(ts, vt)); }
	case number: {
		return t.value; }
	case name: {
		return vt.get(t.name);
	}
	case '-': {
		return -primary(ts, vt); }
	case '+': {
		return primary(ts, vt); }
	default: {error("“ребуетс€ первичное выражение"); }
	}
}