#include "stdafx.h"
#include "Polynomial.h"
#include <iostream>

Polynomial::Polynomial()
{
	coeffs = (Fraction*)malloc(sizeof(Fraction));	
	coeffs[0] = Fraction();
	m = 0;
}

Polynomial::Polynomial(long t_m, Fraction* t_coeffs)
{
	m = t_m;
	coeffs = (Fraction*)malloc((m + 1) * sizeof(Fraction));	//насчёт sizeof не уверен, нужно проверить
	for (int i = 0; i <= m; i++)
		coeffs[i] = t_coeffs[i];
}

Polynomial Polynomial::operator = (const Polynomial p) { //changed
	coeffs = (Fraction*)malloc((p.m + 1) * sizeof(Fraction));
	for (int i = 0; i <= p.m; i++)
		coeffs[i] = p.coeffs[i];
	return Polynomial(m = p.m, coeffs);
}

void Polynomial::printPolynomial()
{
	for (int i = m; i >= 0; i--)
	{
		if (coeffs[i].nom.ABS_Z_N().NZER_N_B()) {
			continue;
		}
		else if (coeffs[i].nom.POZ_Z_D() == 2)
			std::cout << '+';

		coeffs[i] = coeffs[i].RED_Q_Q();
		if (coeffs[i].INT_Q_B()) coeffs[i].nom.printForFract();
		else coeffs[i].printForPo();
		std::cout << "x^" << i << ' ';
	}
}

Polynomial ADD_PP_P(Polynomial a, Polynomial b)	
{
	Polynomial result;
	if (sizeof(a) >= sizeof(b))
	{
		result = a;
		for (int i = 0; i < sizeof(b); i++)
			result.coeffs[i] = ADD_QQ_Q(result.coeffs[i], b.coeffs[i]);
	}
	else
	{
		result = b;
		for (int i = 0; i < sizeof(a); i++)
			result.coeffs[i] = ADD_QQ_Q(result.coeffs[i], a.coeffs[i]);
	}
	return result;
}

Polynomial SUB_PP_P(Polynomial a, Polynomial b)
{
	Polynomial result;
	if (sizeof(a) >= sizeof(b))
	{
		result.operator= (a);
		for (int i = 0; i < sizeof(b); i++)
			result.coeffs[i] = SUB_QQ_Q(result.coeffs[i], b.coeffs[i]);
	}
	else
	{
		result.operator = (b);
		for (int i = 0; i < sizeof(a); i++)
			result.coeffs[i] = SUB_QQ_Q(result.coeffs[i], a.coeffs[i]);
	}
	return result;
}

Polynomial MUL_PQ_P(Polynomial a, Fraction q)
{
	Polynomial result;
	result.operator= (a);
	for (int i = 0; i < sizeof(a); i++)
		result.coeffs[i] = MUL_QQ_Q(result.coeffs[i], q);
	return result;
}

Polynomial Polynomial::MUL_Pxk_P(long k) {
	long prime_m = m;
	Polynomial a; a.operator=(*this);
	a.m += k;
	a.coeffs = (Fraction*)realloc(a.coeffs, (a.m + 1) * sizeof(Fraction));
	long j = a.m;
	for (int i = prime_m; i >= 0; i--) {
		a.coeffs[j] = a.coeffs[i];
		j--;
	}
	for (int i = 0; i < k - 1; i++) {
		a.coeffs[i] = Fraction();
	}
	return a;
}

Fraction Polynomial::LED_P_Q()
{
	return coeffs[m];
}

int Polynomial::DEG_P_N()
{
	return m;
}

Polynomial Polynomial::FAC_P_Q()
{
	
	return Polynomial();
}

Polynomial MUL_PP_P(Polynomial a, Polynomial b)
{
	Fraction* newCoeffs = (Fraction*)malloc((a.m + b.m - 2) * sizeof(Fraction));
	for (int i = 0; i < a.m + b.m; i++)
		newCoeffs[i] = Fraction();
	Polynomial result = Polynomial(a.m + b.m, newCoeffs);
	if (a.m > b.m)
	{
		for (int i = 0; i <= a.m; i++)
			if (b.coeffs[i].nom.POZ_Z_D() != 0)
			{
				result = ADD_PP_P(result, MUL_PQ_P(a, b.coeffs[i]));
				result = ADD_PP_P(result, result.MUL_Pxk_P(i));
			}
	}
	else
	{
		for (int i = 0; i <= b.m; i++)
			if (a.coeffs[i].nom.POZ_Z_D() != 0)
			{
				result = ADD_PP_P(result, MUL_PQ_P(b, a.coeffs[i]));
				result = ADD_PP_P(result, result.MUL_Pxk_P(i));
			}
	}
	return result;
}

Polynomial DIV_PP_P(Polynomial a, Polynomial b) {
	Polynomial buff, result;
	//	if (a.DEG_P_N() < b.DEG_P_N()) {buff.operator=(a); a.operator=(b); b.operator=(buff);}
	while (a.DEG_P_N() >= b.DEG_P_N()) {
		buff = b.MUL_Pxk_P(a.DEG_P_N() - b.DEG_P_N());
		buff = MUL_PQ_P(buff, a.LED_P_Q());
		a = SUB_PP_P(a, buff);
		result = ADD_PP_P(result, buff);
	}
	return result;
}

Polynomial MOD_PP_P(Polynomial p1, Polynomial p2) {
	Polynomial div = DIV_PP_P(p1, p2);
	if (p1.DEG_P_N() >= p2.DEG_P_N()) {
		Polynomial q = MUL_PP_P(div, p1);
		return SUB_PP_P(p1, q);
	}
	else {
		Polynomial q = MUL_PP_P(div, p2);
		return SUB_PP_P(p2, q);
	}
}

Polynomial GCF_PP_P(Polynomial p1, Polynomial p2) {
	Polynomial buff, gcf;
	do {
		gcf = DIV_PP_P(p1, p2);
		buff.operator=(p1);
		p1.operator=(p2);
		p2 = MOD_PP_P(buff, p2);
	} while (MOD_PP_P(p1, p2).DEG_P_N() != 0);
	return gcf;
}

Polynomial Polynomial::DER_P_P() {
	Polynomial p; p.operator=(*this);
	Fraction *ret = new Fraction(ReformInt(0), ReformInt(1).ABS_Z_N());
	if (p.m == 0) return Polynomial(0, ret);

	for (int i = 0; i < p.m; i++) {
		p.coeffs[i].operator=(p.coeffs[i + 1]);
		p.coeffs[i].operator=(MUL_QQ_Q(p.coeffs[i], Fraction(ReformInt(i), ReformInt(1).ABS_Z_N())));
	}
	p.m--;
	return p;
}

Integer ReformInt(long int a) {
	short* nums = (short*)malloc(sizeof(short)); nums[0] = 0;
	long int n = 0, copy_a = a;
	while (copy_a != 0) {
		n++;
		nums = (short*)realloc(nums, n * sizeof(short));
		nums[n - 1] = copy_a % 10;
		copy_a /= 10;
	}
	if (a<0) return Integer(true, n, nums);
	else return Integer(false, n, nums);
}

Natural ReformNat(long int a) {
	short* nums = (short*)malloc(sizeof(short)); nums[0] = 0;
	long int n = 0;
	while (a != 0) {
		n++;
		nums = (short*)realloc(nums, n * sizeof(short));
		nums[n - 1] = a % 10;
		a /= 10;
	}
	return Natural(n, nums);
}
