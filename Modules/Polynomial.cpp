#include "stdafx.h"
#include "Polynomial.h"
#include <iostream>

Polynomial::Polynomial()
{
	coeffs = (Fraction*)malloc(sizeof(Fraction));	
	coeffs[0] = Fraction();
	m = 0;
}

Polynomial::Polynomial(long t_n, Fraction f)
{
	m = t_n;
	Fraction* c = (Fraction*)malloc((t_n + 1) * sizeof(Fraction));
	c[m] = f;
	for (long i = 0; i < m; i++)
		c[i] = Fraction();
	coeffs = c;
}

Polynomial::Polynomial(long t_m, Fraction* t_coeffs)
{
	m = t_m;
	coeffs = (Fraction*)malloc((m + 1) * sizeof(Fraction));
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
	if (m == 0) {
		coeffs[0].printNum();
		return;
	}
	for (int i = m; i >= 0; i--)
	{
		if (coeffs[i].nom.ABS_Z_N().NZER_N_B()) {
			continue;
		}
		else if (coeffs[i].nom.POZ_Z_D() == 2)
			std::cout << '+';

		coeffs[i] = coeffs[i].RED_Q_Q();
		if (coeffs[i].INT_Q_B()) coeffs[i].nom.printForFract();
		else coeffs[i].printNum();
		if (i == 1)
			std::cout << 'x' << ' ';
		else if(i != 0)
			std::cout << "x^" << i << ' ';
	}
	std::cout << '\n';
}

Polynomial ADD_PP_P(Polynomial a, Polynomial b)	
{
	Polynomial result;
	if (a.m > b.m)
	{
		result = a;
		for (int i = 0; i <= b.m; i++) {
			result.coeffs[i] = ADD_QQ_Q(result.coeffs[i], b.coeffs[i]);
		}
	}
	else
	{
		result = b;
		for (int i = 0; i <= a.m; i++) {
			result.coeffs[i] = ADD_QQ_Q(result.coeffs[i], a.coeffs[i]);
		}
	}
	for (long i = result.m; i > 0; i--) {
		if (result.coeffs[i].nom.POZ_Z_D() == 0)
			result.m--;
		else break;
	}
	return result;
}

Polynomial SUB_PP_P(Polynomial a, Polynomial b)
{
	Polynomial result;
	if (a.m >= b.m)
	{
		result.operator= (a);
		for (long i = 0; i <= b.m; i++)
			result.coeffs[i] = SUB_QQ_Q(result.coeffs[i], b.coeffs[i]);
	}
	else
	{
		result.operator = (b);
		for (long i = 0; i <= a.m; i++)
			result.coeffs[i] = SUB_QQ_Q(a.coeffs[i], result.coeffs[i]);
		for (long i = a.m + 1; i <= result.m; i++)
			result.coeffs[i].nom.MUL_ZM_Z();
	}
	for(long i = result.m; i >= 0; i--)
		if (result.coeffs[i].nom.POZ_Z_D() == 0)
			result.m--;
		else break;

	return result;
}

Polynomial MUL_PQ_P(Polynomial a, Fraction q)
{
	Polynomial result;
	result.operator= (a);
	for (int i = 0; i <= a.m; i++) {
		result.coeffs[i] = MUL_QQ_Q(result.coeffs[i], q);
	}
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
	for (int i = 0; i <= k - 1; i++) {
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

Polynomial Polynomial::FAC_P_Q(bool show)
{
	Natural NOD(coeffs[m].nom.ABS_Z_N());
	Natural NOK(coeffs[m].den);
	for (int i = m - 1; i >= 0; i--) {
		if (!coeffs[i].nom.ABS_Z_N().NZER_N_B()) {
			NOD = GCF_NN_N(NOD, coeffs[i].nom.ABS_Z_N());
			NOK = LCM_NN_N(NOK, coeffs[i].den);
		}
	}
	Fraction mult(NOD, NOK);
	Fraction* new_coeffs;
	new_coeffs = (Fraction*)malloc((m + 1) * sizeof(Fraction));
	for (int i = m; i >= 0; i--) {
		new_coeffs[i] = DIV_QQ_Q(coeffs[i], mult);
	}
	if (show) std::cout << '('; mult.RED_Q_Q().printNum(); std::cout << ") ";
	return Polynomial(m, new_coeffs);
}

Polynomial MUL_PP_P(Polynomial a, Polynomial b)
{
	Fraction* newCoeffs = (Fraction*)malloc((a.m + b.m + 1) * sizeof(Fraction));
	for (long i = 0; i <= a.m + b.m; i++)
		newCoeffs[i] = Fraction();
	Polynomial result = Polynomial(a.m + b.m, newCoeffs);
	Polynomial temp;

	for (long i = 0; i <= b.m; i++)
		if (b.coeffs[i].nom.POZ_Z_D() != 0)
		{
			temp = MUL_PQ_P(a, b.coeffs[i]);
			temp = temp.MUL_Pxk_P(i);
			//result.printPolynomial(); std::cout << '\n';
			//temp.printPolynomial(); std::cout << '\n';
			result = ADD_PP_P(result, temp);
		}
	return result;
}

Polynomial DIV_PP_P(Polynomial a, Polynomial b) {
	Polynomial div, buff, result;
	Fraction to_answer;
	div.operator=(a);
	long res_deg;
	while (div.DEG_P_N() >= b.DEG_P_N()) {
		to_answer = DIV_QQ_Q(div.LED_P_Q(), b.LED_P_Q());
		buff = b.MUL_Pxk_P(div.DEG_P_N() - b.DEG_P_N());
		buff = MUL_PQ_P(buff, to_answer);
		res_deg = div.DEG_P_N() - b.DEG_P_N();
		div = SUB_PP_P(div, buff);
		result = ADD_PP_P(result, Polynomial(res_deg, to_answer));
	}
	return result;
}

Polynomial MOD_PP_P(Polynomial p1, Polynomial p2) {
	Polynomial div = DIV_PP_P(p1, p2);

	return SUB_PP_P(p1, MUL_PP_P(p2, div));
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
	Fraction *ret = new Fraction(Integer(), Natural(1));
	if (p.m == 0) return Polynomial(0, ret);

	for (int i = 0; i < p.m; i++) {
		p.coeffs[i].operator=(p.coeffs[i + 1]);
		p.coeffs[i].operator=(MUL_QQ_Q(p.coeffs[i], Fraction(ReformInt(i+1), ReformInt(1).ABS_Z_N())));
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