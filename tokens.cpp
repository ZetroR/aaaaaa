#include "tokens.h"


void  Token_stream::putback(Token t)
// �����������: � ������� ��� �� ������ ������� ������ Token
{
	if (full) { error("putback(): ������ ��������"); }
	buffer = t;
	full = true;
}

Token Token_stream::get()
{	// ������ �������� �� cin � ����������� Token
	if (full) { full = false;  return buffer; }

	char ch; cin.get(ch);

	while (ch == ' ') { cin.get(ch); }

	switch (ch) {
	case '\n':
	{
		return Token{ print };
	}
	case '=':									// ��� ����������
	case print:									// ��� ������ 
	case quit:									// ��� ������
	case '(': case ')':							// |
	case '[': case ']':							// | ->  ������������� ������
	case '{': case '}':							// |
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':									// ������� �� �������
	case '!':									// ���������
	case '^':									// �������
	{
		return Token{ ch };		// ������ ������� ������������ ��� ����
	}
	// �������� �������:
	case '.':									// ����� � ��������� ������ ����� ���������� � ����� 
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9': {
		cin.putback(ch);
		double val;
		cin >> val;
		return Token{ number, val }; }
	// �������� ���� ����������:
	default: {
		if (isalpha(ch)) 
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) { s += ch; }
			cin.putback(ch);

			// �������� �� �������� ����� ��������
			if (s == constdeclkey) { return Token{ constant }; }
			if (s == declkey) { return Token{ let }; }
			if (s == setkey) { return Token{ set }; }
			if (s == sqrtkey) { return Token{ sqrt_ }; }
			if (s == abskey) { return Token{ abs_ }; }
			return Token{ name, s };	// ����� ����������

		}
	}
		error("�������� �������");
	}
}

void  Token_stream::ignore(char c)
// ���������� ���� �� ��� ��� ���� �� �������� ������ c
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch = 0;
	while (cin >> ch) { if (c == ch) return; }
}