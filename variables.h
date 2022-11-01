#ifndef VARIABLES_H
#define VARIABLES_H
#include "std_lib_facilities.h"

class Variable {
public:
	string name;
	double value;
	bool is_const = false;

	Variable(string n, double v, bool c) : name{ n }, value{ v }, is_const{ c } {};
};

class Symbol_table
{
public:
	vector<Variable> var_table;

	double get(string s);
	void set(string s, double d);
	bool is_declared(string var);
	double define(string var, double val, bool cnst);
};

#endif // VARIABLES_H