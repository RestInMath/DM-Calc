#pragma once
#include <string>
class Integer;
class Fraction;
class Natural {
friend int COM_NN_D(Natural x, Natural y);
friend Natural ADD_NN_N(Natural a, Natural b);
friend Natural SUB_NN_N(Natural a, Natural b);
friend Natural MUL_NN_N(Natural a, Natural b);
friend int DIV_NN_Dk(Natural a, Natural b, long int k);
friend Natural SUB_NDN_N(Natural a, Natural b, long int k);
friend Natural DIV_NN_N(Natural a, Natural b);
friend void nat_reall(Natural &a, long int n);
friend void nat_reall(int* &a, long int len, long int n);
friend void nat_reall(short* &a, long int len, long int n);

private:
	long int n;		//n - на единицу меньше количества цифр, т.к. представляет разряд
	short* nums;	//nums - массив цифр "перевернутого" числа
public:
	friend Integer;
	friend Fraction;
	Natural();
	Natural(long int n, int* arr);
	Natural(long int n, short* arr);
	Natural(std::string arr);
	Natural(int num);
	Natural operator = (const Natural a);
	
	
	void printNum();
	void printForPo();

	bool NZER_N_B();
	void ADD_1N_N();
	Natural MUL_ND_N(long int d);
	Natural MUL_Nk_N(int k);
	
};

Natural MOD_NN_N(Natural a, Natural b);
Natural GCF_NN_N(Natural a, Natural b);
Natural LCM_NN_N(Natural a, Natural b);