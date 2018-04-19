#pragma once
#include "Fraction.h"

class Polynomial
{
	friend Polynomial ADD_PP_P(Polynomial a, Polynomial b);
	friend Polynomial SUB_PP_P(Polynomial a, Polynomial b);
	friend Polynomial MUL_PQ_P(Polynomial a, Fraction q);
	friend Polynomial MUL_PP_P(Polynomial a, Polynomial b);
private:
	Fraction* coeffs;	
	long m;
public:
	Polynomial();
	Polynomial(long t_m, Fraction* t_coeffs);
	Polynomial operator = (const Polynomial p);

	void printPolynomial();
	Polynomial FAC_P_Q();
	Fraction LED_P_Q();
	int DEG_P_N();
	Polynomial MUL_Pxk_P(long k);
	Polynomial DER_P_P();
};

Polynomial DIV_PP_P(Polynomial a, Polynomial b);
Polynomial MOD_PP_P(Polynomial p1, Polynomial p2);
Polynomial GCF_PP_P(Polynomial p1, Polynomial p2);
Integer ReformInt(long int a);
Natural ReformNat(long int a);