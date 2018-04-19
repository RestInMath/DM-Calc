#include "stdafx.h"
#include "Fraction.h"
#include <iostream>
#include <malloc.h>

Fraction::Fraction(){
	den = Natural(1);
}

Fraction::Fraction(Integer a, Natural b){
	nom.operator= (a);
	den.operator= (b);
}

void Fraction::printNum()
{
	nom.printForFract();
	std::cout << "/";
	den.printForPo();
}

void Fraction::printForPo() { // ???
	nom.printForFract();
	std::cout << "/";
	den.printForPo();
}

void Fraction::print()
{
	nom.printForFract();
	std::cout << "/";
	den.printForPo();
}

Fraction Fraction::RED_Q_Q(){
	Natural nod;
	nod = GCF_NN_N(nom.ABS_Z_N(), den); //GCF_NN_N ���������� Natural
	return Fraction(DIV_ZZ_Z(nom, TRANS_N_Z(nod)), DIV_NN_N(den, nod));
}

bool Fraction::INT_Q_B(){

	if (MOD_NN_N(nom.ABS_Z_N(), den).NZER_N_B())
		return true;
	else
		return false;
}

Fraction TRANS_Z_Q (Integer sad){
	Natural den_N(1);
	Fraction *frac = new Fraction(sad, den_N);//��� �� ���������� �������������
	return *frac;
}

Integer Fraction::TRANS_Q_Z (){
	if(COM_NN_D(LCM_NN_N(den, nom.ABS_Z_N()), nom.ABS_Z_N()) == 0){
		return Integer(nom.sign, nom.n, nom.nums);
	}
	else; //��� �������?
}

Fraction ADD_QQ_Q(Fraction f1, Fraction f2) {//���������� � �������������� ���, lol
	Natural nok_N = LCM_NN_N(f1.den, f2.den);
	Integer nok_Z = TRANS_N_Z(nok_N);
	Integer mnozh1 = DIV_ZZ_Z(nok_Z, TRANS_N_Z(f1.den));
	Integer mnozh2 = DIV_ZZ_Z(nok_Z, TRANS_N_Z(f2.den));
	Integer newNom1_Z = MUL_ZZ_Z(mnozh1, f1.nom);
	Integer newNom2_Z = MUL_ZZ_Z(mnozh2, f2.nom);

	Integer newNom_Z = ADD_ZZ_Z(newNom1_Z, newNom2_Z);
	return Fraction(newNom_Z, nok_N);//��� �� ���������� �������������
}

Fraction MUL_QQ_Q (Fraction f1, Fraction f2){
	Integer newNom_Z = MUL_ZZ_Z(f1.nom, f2.nom);
	Integer den1_Z; den1_Z.operator=(f1.den);
	Integer den2_Z; den2_Z.operator=(f2.den);

	Integer newDen_Z = MUL_ZZ_Z(den1_Z, den2_Z);

	return Fraction(newNom_Z, newDen_Z.ABS_Z_N());
}

Fraction SUB_QQ_Q(Fraction f1, Fraction f2) {//���������� � �������������� ���, lol
	Natural nok_N = LCM_NN_N(f1.den, f2.den);
	Integer nok_Z = TRANS_N_Z(nok_N);
	Integer mnozh1 = DIV_ZZ_Z(nok_Z, TRANS_N_Z(f1.den));
	Integer mnozh2 = DIV_ZZ_Z(nok_Z, TRANS_N_Z(f2.den));
	Integer newNom1_Z = MUL_ZZ_Z(mnozh1, f1.nom);
	Integer newNom2_Z = MUL_ZZ_Z(mnozh2, f2.nom);

	Integer newNom_Z = SUB_ZZ_Z(newNom1_Z, newNom2_Z);
	return Fraction(newNom_Z, nok_N);
}

Fraction DIV_QQ_Q(Fraction f1, Fraction f2){
	Integer newNom = MUL_ZZ_Z(f1.nom, f2.den);
	Integer newDen = MUL_ZZ_Z(f1.den, f2.nom);
	if (newDen.POZ_Z_D() == 1) newNom = newNom.MUL_ZM_Z();
	//first argument in constructor newNom_Z means that if signs are opposite, then result will be minus
	return Fraction(newNom, newDen.ABS_Z_N());
}