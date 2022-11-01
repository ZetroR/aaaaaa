#include "variables.h"


double Symbol_table::get(string s)
// ���������� �������� ���������� � ������ s
{
	for (const Variable& v : var_table) {
		if (v.name == s) { return v.value; }
	}
	error("get: ������������� ���������� ", s);
}

void Symbol_table::set(string s, double d)
// ����������� ������� s ���� Variable �������� d
{
	for (Variable& v : var_table) if (v.name == s && !v.is_const) {
		v.value = d;
		return;
	}
	error("set: ���������� �� ���������� ��� �������� ���������� ", s);
}

bool Symbol_table::is_declared(string var)
// ���� �� ���������� var � ������� var_ ta�le?
{
	for (const Variable& v : var_table) {
		if (v.name == var) { return true; }
	}
	return false;

}

double Symbol_table::define(string var, double val, bool cnst)
// ��������� const ����(var, val) � ������ var_ table
{
	if (is_declared(var)) { error(var, " ��������� ����������"); }
	var_table.push_back(Variable(var, val, cnst));
	return val;
}