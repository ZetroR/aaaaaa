#include "variables.h"


double Symbol_table::get(string s)
// Возвращает значение переменной с именем s
{
	for (const Variable& v : var_table) {
		if (v.name == s) { return v.value; }
	}
	error("get: неопределённая переменная ", s);
}

void Symbol_table::set(string s, double d)
// Присваивает объекту s типа Variable значение d
{
	for (Variable& v : var_table) if (v.name == s && !v.is_const) {
		v.value = d;
		return;
	}
	error("set: переменная не определена или является константой ", s);
}

bool Symbol_table::is_declared(string var)
// Есть ли переменная var в векторе var_ taЬle?
{
	for (const Variable& v : var_table) {
		if (v.name == var) { return true; }
	}
	return false;

}

double Symbol_table::define(string var, double val, bool cnst)
// Добавляем const пару(var, val) в вектор var_ table
{
	if (is_declared(var)) { error(var, " повторное объявление"); }
	var_table.push_back(Variable(var, val, cnst));
	return val;
}