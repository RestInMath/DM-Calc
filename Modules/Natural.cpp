#include "stdafx.h"
#include "Natural.h"
#include<iostream>
#include <string>

Natural::Natural() {
	n = 0;
	nums = (short*)malloc(sizeof(short));
	nums[0] = 0;
}

Natural::Natural(long int t_n, int* t_nums) {
	n = t_n;
	nums = (short*)malloc((n + 1) * sizeof(short));
	for (int i = 0; i < (n + 1); i++) {
		nums[i] = t_nums[i];
	}
}

Natural::Natural(long int t_n, short* t_nums) {
	n = t_n;
	nums = (short*)malloc((n + 1) * sizeof(short));
	for (int i = 0; i < (n + 1); i++) {
		nums[i] = t_nums[i];
	}
}

Natural::Natural(std::string t_nums) {
	n = t_nums.length() - 1;
	nums = (short*)malloc((n + 1) * sizeof(short));
	for (int i = 0; i <= n; i++) {
		nums[i] = t_nums[i] - '0';
	}
}

Natural::Natural(int num)
{
	n = 0;
	nums = (short*)malloc(sizeof(short));
	nums[0] = num;
}

Natural Natural::operator = (const Natural a)
{
	short* temp = (short*)malloc((a.n + 1) * sizeof(short));
	for (int i = 0; i <= a.n; i++) {
		temp[i] = a.nums[i];
	}

	return Natural(this->n = a.n, this->nums = temp);
}

void Natural::printNum()
{
	for (int i = n; i >= 0; i--) std::cout << nums[i];
	std::cout << std::endl;
}

void Natural::printForPo()
{
	for (int i = n; i >= 0; i--) std::cout << nums[i];
}

Natural Natural::MUL_Nk_N(int k)
{
	short* temp = (short*)malloc((n + k + 1) * sizeof(short));
	for (int i = 0; i <= n; i++) temp[i + k] = nums[i];
	for (int i = 0; i < k; i++) temp[i] = 0;
	long int t_n = n + k;
	return Natural(t_n, temp);
}

int COM_NN_D(Natural x, Natural y) {
	if (x.n == y.n) {
		for (long int i = x.n; i >= 0; i--) {
			if (x.nums[i] > y.nums[i])
				return 2;
			if (x.nums[i] < y.nums[i])
				return 1;
		}
		return 0;
	}
	else if (x.n > y.n)
		return 2;
	else
		return 1;
}

bool Natural::NZER_N_B() {
	if (nums[n] == 0)
		return true;
	else
		return false;
}

void Natural::ADD_1N_N() {
	for (int i = 0; i <= n; i++) {
		if (nums[i] == 9)
			nums[i] = 0;
		else {
			nums[i] += 1;
			return;
		}
	}
	if (nums[n] == 0) {
		nums = (short*)realloc(nums, (++n + 1) * sizeof(short));
		nums[n] = 1;
	}
}

Natural Natural::MUL_ND_N(long int d) {
	int temp_mul, *temp_nums, next = 0;
	long int temp_n = n + 1; //1
	temp_nums = (int*)malloc((temp_n + 1) * sizeof(int));
	
	for (int i = 0; i <= temp_n; i++)
		temp_nums[i] = 0;
	for (int i = 0; i <= n; i++) {
		temp_mul = nums[i] * d;
		temp_nums[i] = (temp_mul + next) % 10 ;
		if (temp_mul+next >= 10) {
			next = (temp_mul + next) / 10;
			if (i == n)
				temp_nums[i + 1] = next;
		}
		else next = 0;
	}

	for (int i = temp_n; i >= 0; i--) {
		if (temp_nums[i] == 0 && i != 0)
			--temp_n;
		else
			break;
	}
	
	return Natural(temp_n, temp_nums);
}

void nat_reall(Natural &a, long int n) {
	short* t = (short*)malloc((a.n + 1) * sizeof(short));
	for (int i = 0; i <= a.n; i++) {
		t[i] = a.nums[i];
	}

	a.nums = (short*)realloc(a.nums, (a.n + n + 1) * sizeof(short*));
	for (int i = 0; i <= a.n; i++) {
		a.nums[i] = t[i];
	}
	a.n += n;
}

void nat_reall(int* &a, long int len,  long int n) {
	short* t = (short*)malloc((len + 1) * sizeof(short));
	for (int i = 0; i <= len; i++) {
		t[i] = a[i];
	}

	len += n;
	a = (int*)realloc(a, (len + 1) * sizeof(int));
	for (int i = 0; i <= len; i++) {
		a[i] = t[i];
	}
}

void nat_reall(short* &a, long int len, long int n) {
	short* t = (short*)malloc((len + 1) * sizeof(short));
	for (int i = 0; i <= len; i++) {
		t[i] = a[i];
	}
	//std::cout << std::endl;
	len += n;
	a = (short*)realloc(a, (len + 1) * sizeof(short));
	for (int i = 0; i <= len; i++) {
		a[i] = t[i];
		//std::cout << a[i] << ' ';
	}
}

Natural ADD_NN_N(Natural a, Natural b) {
	Natural temp,x,y;
	int next = 0;
	long int i, len;
	if (COM_NN_D(a, b) == 1) {
		temp.operator= (b);
		y.operator= (a);
		x.operator= (temp);
	}
	else {
		temp.operator= (a);
		x.operator=(a); 
		y.operator=(b);
	}
	len = y.n;

	for (i = 0; i <= len; i++) {
		temp.nums[i] = (x.nums[i] + y.nums[i] + next) % 10;
		if ((x.nums[i] + y.nums[i] + next) >= 10) {
			if (i == temp.n) {
				nat_reall(temp, 1);
				temp.nums[i + 1] = 1;
				next = 0;
			}
			else
				next = 1;
		}
		else next = 0;
	}

	for (i = len + 1; i <= temp.n && next; i++) {
		if (i == temp.n) {
			temp.nums[i]++;
			next = 0;
		}
		else if (temp.nums[i] + next < 10) {
			temp.nums[i] += 1;
			next = 0;
		}
		else
			temp.nums[i] = 0;
	}

	return temp;
}

Natural SUB_NN_N(Natural a, Natural b) {
	Natural temp, x, y;
	x.operator=(a);
	y.operator=(b);
	int i;

	for (i = 0; i <= y.n; i++) {
		if (x.nums[i] < y.nums[i] || x.nums[i] < 0) {
			x.nums[i + 1] -= 1;
			x.nums[i] = 10 + x.nums[i];
			x.nums[i] -= y.nums[i];
		}
		else
			x.nums[i] -= y.nums[i];
	}
	
	for (i = y.n+1; i <= x.n; i++) {
		if (x.nums[i] < 0) {
			x.nums[i] += 10;
			x.nums[i + 1] -= 1;
		}
		else break;
	}

	for (i = x.n; i >= 0; i--)
		if (x.nums[i] == 0 && x.n !=0) x.n--;
		else break;

	return x;
}

Natural MUL_NN_N(Natural a, Natural b) {
	Natural temp, to_return, x, y;
	if (COM_NN_D(a, b) == 2) {
		x.operator=(a); y.operator=(b);
	}
	else {
		x.operator=(b); y.operator=(a);
	}
	for (int i = y.n; i >= 0; i--) {
		temp.operator= (x);
		temp = temp.MUL_Nk_N(i);
		temp = temp.MUL_ND_N(y.nums[i]);
		to_return = ADD_NN_N(to_return, temp);
	}
	return to_return;
}

int DIV_NN_Dk(Natural a, Natural b, long int k) {
	int i = 0;
	int comp = COM_NN_D(a, b.MUL_Nk_N(k));
	if (comp == 1) return 0;
	else if (comp == 0) return 1;
	
	Natural temp, temp2;
	temp2.operator = (b); //2
	temp2 = temp2.MUL_Nk_N(k); //20
	temp.operator=(b); 
	while (i < 10 && COM_NN_D(a, temp) != 1) {
		temp.operator= (temp2);
		temp = temp.MUL_ND_N(++i);
	}
	return i - 1;
}

Natural SUB_NDN_N(Natural a, Natural b, long int num)
{
	Natural temp; temp.operator= (b);
	return SUB_NN_N(a, temp.MUL_ND_N(num));
}

Natural DIV_NN_N(Natural a, Natural b)
{
	long int k;
	Natural temp, sum, temp_a; 
	temp_a.operator = (a);
	temp.operator= (b);
	while (COM_NN_D(temp_a, temp) != 1) {

		if (COM_NN_D(temp_a, temp.MUL_Nk_N(temp_a.n - temp.n)) != 1) {
			k = temp_a.n - temp.n;
		}
		else
			k = temp_a.n - temp.n - 1;

		int f_num = DIV_NN_Dk(temp_a, temp, k);
		temp_a = SUB_NDN_N(temp_a, temp.MUL_Nk_N(k), f_num);
		Natural temp(f_num);
		sum = ADD_NN_N(sum, temp.MUL_Nk_N(k));
	}
	return sum;
}

Natural MOD_NN_N(Natural a, Natural b)
{
	return SUB_NN_N(a, MUL_NN_N(b, DIV_NN_N(a, b)));
}

Natural GCF_NN_N(Natural a, Natural b) {
	Natural x, y, temp, d;
	x.operator=(a);
	y.operator=(b);
	if (MOD_NN_N(x, y).NZER_N_B())
		return y;
	else if (MOD_NN_N(y, x).NZER_N_B())
		return x;
	
	while (true) {
		if (COM_NN_D(x, y) == 1) {
			temp.operator=(x);
			x.operator=(y);
			y.operator=(temp);
		}
		temp = MOD_NN_N(x, y);
		if (temp.NZER_N_B()) {
			return d;
		}
		else {
			d.operator=(temp);
			x.operator=(y);
			y.operator=(temp);
		}
	}
}

Natural LCM_NN_N(Natural a, Natural b)
{
	return DIV_NN_N(MUL_NN_N(a,b), GCF_NN_N(a,b));
}