#include "stdafx.h"
#include "Integer.h"
#include "Natural.h"
#include <iostream>
#include <string>

Integer::Integer() {
	sign = false;
	n = 0;
	nums = (short*)malloc(sizeof(short));
	nums[0] = 0;
}

Integer::Integer(bool b, long int t_n, int* t_nums) {
	sign = b;
	n = t_n;
	nums = (short*)malloc((n + 1) * sizeof(short));
	for (int i = 0; i < n + 1; i++) {
		nums[i] = t_nums[i];
	}
}

Integer::Integer(bool b, long int t_n, short* t_nums) {
	sign = b;
	n = t_n;
	nums = (short*)malloc((n + 1) * sizeof(short));
	for (int i = 0; i < n + 1; i++) {
		nums[i] = t_nums[i];
	}
}

Integer::Integer(std::string t_nums) {
	n = t_nums.length() - 1;
	sign = t_nums[n] == '-';
	if (sign) n--;

	nums = (short*)malloc((n + 1) * sizeof(short));
	for (int i = 0; i < n + 1; i++) {
		nums[i] = short(t_nums[i] - '0');
	}
}

Integer::Integer(Natural a)
{
	short* temp = (short*)malloc((a.n + 1) * sizeof(short));
	for (int i = 0; i <= a.n; i++) {
		temp[i] = a.nums[i];
	}
	sign = false; n = a.n; nums = temp;
}

Integer Integer::operator=(const Integer & a)
{
	short* temp = (short*)malloc((a.n + 1) * sizeof(short));
	for (int i = 0; i <= a.n; i++) {
		temp[i] = a.nums[i];
	}
	return Integer(this->sign = a.sign, this->n = a.n, this->nums = temp);
}

void Integer::printNum()
{
	if (sign) std::cout << '-';
	for (int i = n; i >= 0; i--) std::cout << nums[i];
	std::cout << std::endl;
}

void Integer::printForFract()
{
	if (sign) std::cout << '-';
	for (int i = n; i >= 0; i--) std::cout << nums[i];
}

//ready
Natural Integer::ABS_Z_N() {
	return Natural(n, nums);
}

//ready
int Integer::POZ_Z_D() {
	if (nums[n] == 0) return 0;
	else if (sign) return 1;
	else return 2;
}

//ready
Integer Integer::MUL_ZM_Z() {
	sign = !sign;
	return Integer(sign, n, nums);
}

//ready
Natural Integer::TRANS_Z_N()
{
	return Natural(n, nums);
}

Integer TRANS_N_Z(Natural a) {
	return Integer(a);
}

//ready
Integer ADD_ZZ_Z(Integer i1, Integer i2) {
	bool first_pos = i1.POZ_Z_D() == 2,
		second_pos = i2.POZ_Z_D() == 2;
	if (first_pos && second_pos) {
		return TRANS_N_Z(ADD_NN_N(i1.TRANS_Z_N(), i2.TRANS_Z_N()));
	}
	else if (!first_pos && !second_pos) {
		return TRANS_N_Z(ADD_NN_N(i1.TRANS_Z_N(), i2.TRANS_Z_N())).MUL_ZM_Z();
	}
	else {
		int comp = COM_NN_D(i1.TRANS_Z_N(), i2.TRANS_Z_N());
		if (comp == 0) return Integer();
		else {
			if (comp == 2) {
				Integer to_return = TRANS_N_Z(SUB_NN_N(i1.TRANS_Z_N(), i2.TRANS_Z_N()));
				return (i1.POZ_Z_D() == 1 ? to_return.MUL_ZM_Z() : to_return);
			}
			else if (comp == 1) {
				Integer to_return = TRANS_N_Z(SUB_NN_N(i2.TRANS_Z_N(), i1.TRANS_Z_N()));
				return (i1.POZ_Z_D() == 1 ? to_return : to_return.MUL_ZM_Z());
			}
		}
	}
}

Integer SUB_ZZ_Z(Integer i1, Integer i2)
{
	return Integer(ADD_ZZ_Z(i1, i2.MUL_ZM_Z()));
}

Integer MUL_ZZ_Z(Integer i1, Integer i2)
{
	Integer to_return = TRANS_N_Z( MUL_NN_N(i1.TRANS_Z_N(), i2.TRANS_Z_N()) );
	if (i1.POZ_Z_D() == i2.POZ_Z_D()) return to_return;
	else return to_return.MUL_ZM_Z();
}

Integer DIV_ZZ_Z(Integer i1, Integer i2){
	int poz_i1 = i1.POZ_Z_D(), poz_i2 = i2.POZ_Z_D();
	if (poz_i2 == 0) return std::string(NULL);
	Integer to_return = TRANS_N_Z(DIV_NN_N(i1.ABS_Z_N(), i2.ABS_Z_N()));
	if (poz_i1 != poz_i2)
		to_return.MUL_ZM_Z();
	return to_return;
}

Integer MOD_ZZ_Z(Integer i1, Integer i2) {
	int poz_i1 = i1.POZ_Z_D(), poz_i2 = i2.POZ_Z_D();
	if (poz_i2 == 0) return std::string(NULL);
	Integer to_return = MOD_NN_N(i1.ABS_Z_N(), i2.ABS_Z_N());
	if (poz_i1 != poz_i2)
		to_return.MUL_ZM_Z();
	return to_return;
}