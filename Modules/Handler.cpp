#include "stdafx.h"
#include "Handler.h"
#include <iostream>
#include <string>
#include "Fraction.h"
#include "Integer.h"
#include "Polynomial.h"

using namespace std;
void Handler(int params_count, char* params[]) {
	string type = string(params[1]);
	string op = string(params[2]);
	
	if (params_count < 7) std::cout << "Недостаточно аргументов - неверный ввод\n";

	else if (type == "F" || type == "A") {
		Fraction to_print = get_F_val(params).RED_Q_Q();
		if (type == "A") to_print.nom = TRANS_N_Z(to_print.nom.ABS_Z_N());
		if (to_print.INT_Q_B()) to_print.nom.printNum();
		else to_print.print();
	}

	else if (type == "P") {
		int counter = 0;
		Polynomial p1 = get_P(params, op, counter);
		counter += 1;
		Polynomial p2 = get_P(params, op, counter);

		get_P_val(p1,p2,op).printPolynomial();
	}	
}

Fraction get_F_val(char* params[]) {
	char op = params[6][0];
	if (string(params[6]).length() == 2 && op == '/' && params[6][1] == '/') op = '|';

	Integer n1(params[2]), n2(params[4]);
	Natural d1(params[3]), d2(params[5]), one(1);
	Fraction num1(n1, d1), num2(n2, d2);

	if (op == '+') return ADD_QQ_Q(num1, num2);
	else if (op == '-') return SUB_QQ_Q(num1, num2).RED_Q_Q();
	else if (op == '/') return DIV_QQ_Q(num1, num2).RED_Q_Q();
	else if (op == '*') return MUL_QQ_Q(num1, num2).RED_Q_Q();
	else if (op == '%') {
		Fraction temp = DIV_QQ_Q(num1, num2);
		return Fraction(MOD_ZZ_Z(temp.nom, TRANS_N_Z(temp.den)), one);
	}
	else if (op == '|') {
		Fraction temp = DIV_QQ_Q(num1, num2);
		return Fraction(DIV_ZZ_Z(temp.nom, TRANS_N_Z(temp.den)), one);
	}
	else if (op == 'K') {
		if (num1.INT_Q_B() && num2.INT_Q_B()) {
			num1 = num1.RED_Q_Q(); num2 = num2.RED_Q_Q();
			Natural temp = LCM_NN_N(num1.TRANS_Q_Z().ABS_Z_N(), num2.TRANS_Q_Z().ABS_Z_N());
			return Fraction(temp, one);
		}
		else cout << "Поиск НОК осуществляется лишь у целых и натуральных чисел\n";
		exit(0);
	}
	else if (op == 'D') {
		if (num1.INT_Q_B() && num2.INT_Q_B()) {
			num1 = num1.RED_Q_Q(); num2 = num2.RED_Q_Q();
			Natural temp = GCF_NN_N(n1.ABS_Z_N(), n2.ABS_Z_N());
			return Fraction(temp, one);
		}
		else cout << "Поиск НОД осуществляется лишь у целых и натуральных чисел\n";
		exit(0);
	}
}


Polynomial get_P(char* params[], string op, int &counter) {
	long coeff_count = 0, main_deg = stoi(params[5 + counter]);
	
	Fraction* coeffs = (Fraction*)malloc((main_deg + 1) * sizeof(Fraction));
		
	for (int i = 0; i <= main_deg; i++) coeffs[i] = Fraction();

	while(true) {
		if (params[3 + counter] == op) {
			return Polynomial(main_deg, coeffs); }
		long deg = stoi(params[5 + counter]);
		Integer n(params[3 + counter]);
		Natural d(params[4 + counter]), one(1);
		Fraction num(n, d);
		coeffs[deg] = num;
		counter += 3;
	}
	return Polynomial(main_deg, coeffs);
}

Polynomial get_P_val(Polynomial a, Polynomial b, string op) {
	if (op == "+") return ADD_PP_P(a, b);

	if (op == "-") return SUB_PP_P(a, b);

	if (op == "*") return MUL_PP_P(a, b);

	if (op == "/") return DIV_PP_P(a, b);

}