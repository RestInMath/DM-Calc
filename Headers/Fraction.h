#pragma once
#include "Integer.h"
#include "Natural.h"

class Fraction{
friend Fraction DIV_QQ_Q(Fraction f1, Fraction f2);
public:
	Integer nom;
	Natural den;
	Fraction ();
	Fraction(Integer a, Natural b);

	void printNum();
	void printForPo();
	void print();

	Fraction RED_Q_Q ();
	bool INT_Q_B();
	Integer TRANS_Q_Z ();
};

Fraction TRANS_Z_Q (Integer sad);
Fraction ADD_QQ_Q (Fraction f1, Fraction f2);
Fraction MUL_QQ_Q (Fraction f1, Fraction f2);
Fraction SUB_QQ_Q(Fraction f1, Fraction f2);
