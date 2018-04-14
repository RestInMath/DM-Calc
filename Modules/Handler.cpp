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

	if (params_count < 7) std::cout << "Недостаточно аргументов - неверный ввод\n";

	else if (type == "F" || type == "A") {
		Fraction to_print = get_F_val(params).RED_Q_Q();
		if (type == "A") to_print.nom = TRANS_N_Z(to_print.nom.ABS_Z_N());
		if (to_print.INT_Q_B()) to_print.nom.printNum();
		else to_print.print();
	}

	else if (type == "P") {
		get_P_val(params_count, params).printPolynomial();
	}	

}

Fraction get_F_val(char* params[]) {
	char op = params[6][0];
	if (string(params[6]).length() == 2 && op == '/' && params[6][1] == '/') op = '|';

	Integer n1(params[2]), n2(params[4]);
	Natural d1(params[3]), d2(params[5]), one(1);
	Fraction num1(n1, d1), num2(n2, d2);

	if (op == '+') return ADD_QQ_Q(num1, num2);
	else if (op == '-') return SUB_QQ_Q(num1, num2);
	else if (op == '/') return DIV_QQ_Q(num1, num2);
	else if (op == '*') return MUL_QQ_Q(num1, num2);
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


Polynomial get_P_val(int params_count, char* params[]) {
	long coeff_count = 0, main_deg = (stoi(params[4]));
	Fraction* coeffs = (Fraction*)malloc((main_deg + 1) * sizeof(Fraction));
	
	for (int i = 0; i <= main_deg; i++) coeffs[i] = Fraction();


	for (int i = 0; i < params_count - 2; i+=3) {
		long deg = stoi(params[4 + i]);
		Integer n(params[2 + i]);
		Natural d(params[3 + i]), one(1);
		Fraction num(n, d);
		coeffs[deg] = num;
	}
	return Polynomial(main_deg, coeffs);
}