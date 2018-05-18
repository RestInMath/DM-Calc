#pragma once
#include "Fraction.h"
#include "Polynomial.h"
#include <string>
void Handler(int params_count, char* params[]);
Fraction get_F_val(char* params[]);
Polynomial get_P(char* params[], std::string op, int &counter);
Polynomial get_P_val(Polynomial a, Polynomial b, std::string op);