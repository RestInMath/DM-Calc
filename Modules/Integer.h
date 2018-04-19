#pragma once
#include "Natural.h"
#include <string>
class Fraction;
class Integer {
private:
	bool sign;
	long int n;
	short *nums;
public:
	friend Fraction;
	Integer();
	Integer(bool b, long int t_n, int* t_nums);
	Integer(bool b, long int t_n, short* t_nums);
	Integer(std::string t_nums);
	Integer(Natural a);
	Integer operator = (const Integer &a);


	void printNum();
	void printForFract();

	Natural ABS_Z_N();
	int POZ_Z_D();
	Integer MUL_ZM_Z();
	Natural TRANS_Z_N();
};
Integer TRANS_N_Z(Natural a);
Integer ADD_ZZ_Z(Integer i1, Integer i2);
Integer SUB_ZZ_Z(Integer i1, Integer i2);
Integer MUL_ZZ_Z(Integer i1, Integer i2);
Integer DIV_ZZ_Z(Integer i1, Integer i2);
Integer MOD_ZZ_Z(Integer i1, Integer i2);
