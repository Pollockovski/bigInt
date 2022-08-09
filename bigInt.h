/*
只适用于少量巨型整数计算。
Copyright 2022 Yang Y., All rights reserved.
*/
#pragma once
#include<iostream>
#include<vector>
#include<stdio.h>
using namespace std;

int whichNum(char ch)
{
	int a = ch - 48;
	return a;
}

char whichChar(int n)
{
	char a = n + 48;
	return a;
}

class bigInt {
public:
	vector<bool>value;
	void fromBinary(string a);
	void outputBinary();
	void carry(int n);
	void borrow(int n);
	void muiltitwo(int n);
	void devidetwo();
	friend ostream operator<<(ostream& output, bigInt bi)
	{

	}
	friend ostream operator>>(istream& input, bigInt bi)
	{
		string str;
		bigInt temp1, temp2;
		bi.value.resize(0);
		input >> str;
		if (str[0] = '-')
		{
			bi.value.push_back(false);
		}
		reverse(str.begin(), str.end());
		str.resize(str.size() - 1);
	}
	bool operator==(bigInt bi)
	{
		return (value == bi.value);
	}
	bool operator!=(bigInt bi)
	{
		return !(value == bi.value);
	}
	bool operator>(bigInt bi)
	{
		if (bi.value[0] != value[0])
		{
			return value[0];
		}
		if (bi.value.size() != value.size())
		{
			if (value[0])
			{
				return (value.size() > bi.value.size());
			}
			else {
				return !(value.size() > bi.value.size());
			}
		}
		for (int i = value.size() - 1; i > 0; i--)
		{
			if (value[i] != bi.value[i])
			{
				if (value[0])
				{
					return value[i];
				}
				else {
					return !value[i];
				}
			}
		}
		return false;
	}
	bool operator<(bigInt bi)
	{
		bigInt a;
		a.value = this->value;
		return (!(a > bi)) && a != bi;
	}
	bool operator>=(bigInt bi)
	{
		bigInt a;
		a.value = this->value;
		return (a > bi || a == bi);
	}
	bool operator<=(bigInt bi)
	{
		bigInt a;
		a.value = this->value;
		return (a < bi || a == bi);
	}
	bigInt operator!()
	{
		bigInt a;
		a.value = this->value;
		for (int i = 0; i < value.size(); i++)
		{
			a.value[i] = !a.value[i];
		}
		return a;
	}
	bigInt operator+(bigInt bi)
	{
		bigInt temp;
		bool bl;
		int n = 0;
		if (value.size() > bi.value.size())
		{
			temp.value.resize(value.size());
			bl = true;
		}
		else {
			temp.value.resize(bi.value.size());
			bl = false;
		}
		if (value[0] && bi.value[0])
		{
			temp.value[0] = true;
			for (int i = 1; i < value.size() && i < bi.value.size(); i++)
			{
				if (value[i] && bi.value[i])
				{
					if (temp.value[i])
					{
						temp.value[i] = true;
						temp.carry(i);
					}
					else {
						temp.value[i] = false;
						temp.carry(i);
					}
				}
				else if (value[i] || bi.value[i])
				{
					if (temp.value[i])
					{
						temp.value[i] = false;
						temp.carry(i);
					}
					else {
						temp.value[i] = true;
					}
				}
				n = i;
			}
			if (bl)
			{
				for (int i = n + 1; i < value.size(); i++)
				{
					if (temp.value[i] && value[i])
					{
						temp.value[i] = false;
						temp.carry(i);
					}
					else if(temp.value[i]||value[i])
					{
						temp.value[i] = true;
					}
				}
			}
			else {
				for (int i = n + 1; i < bi.value.size(); i++)
				{
					if (temp.value[i] && bi.value[i])
					{
						temp.value[i] = false;
						temp.carry(i);
					}
					else if (temp.value[i] || bi.value[i])
					{
						temp.value[i] = true;
					}
				}
			}
		}
		else if (value[0] || bi.value[0])
		{
			bigInt temp1, temp2;
			temp1.value = this->value;
			temp2.value = bi.value;
			if (value[0])
			{
				temp2.value[0] = true;
				return temp1 - temp2;
			}
			else {
				temp1.value[0] = true;
				return temp2 - temp1;
			}
		}
		else {
			temp.value[0] = false;
			for (int i = 1; i < value.size() && i < bi.value.size(); i++)
			{
				if (value[i] && bi.value[i])
				{
					if (temp.value[i])
					{
						temp.value[i] = true;
						temp.carry(i);
					}
					else {
						temp.value[i] = false;
						temp.carry(i);
					}
				}
				else if (value[i] || bi.value[i])
				{
					if (temp.value[i])
					{
						temp.value[i] = false;
						temp.carry(i);
					}
					else {
						temp.value[i] = true;
					}
				}
				n = i;
			}
			if (bl)
			{
				for (int i = n + 1; i < value.size(); i++)
				{
					if (temp.value[i] && value[i])
					{
						temp.value[i] = false;
						temp.carry(i);
					}
					else if (temp.value[i] || value[i])
					{
						temp.value[i] = true;
					}
				}
			}
			else {
				for (int i = n + 1; i < bi.value.size(); i++)
				{
					if (temp.value[i] && bi.value[i])
					{
						temp.value[i] = false;
						temp.carry(i);
					}
					else if (temp.value[i] || bi.value[i])
					{
						temp.value[i] = true;
					}
				}
			}
		}
		return temp;
	}
	bigInt operator-(bigInt bi)
	{
		bigInt temp, temp1, temp2;
		bool bl;
		int n = 0;
		if (value.size() > bi.value.size())
		{
			temp.value.resize(value.size());
			bl = true;
		}
		else {
			temp.value.resize(bi.value.size());
			bl = false;
		}
		temp1.value = this->value;
		temp2.value = bi.value;
		if (temp1 == temp2)
		{
			temp.value.resize(0);
			temp.value.push_back(true);
			temp.value.push_back(false);
			return temp;
		}
		if (value[0] && bi.value[0])
		{
			if (temp1 >= bi)
			{
				temp.value[0] = true;
				for (int i = 1; i < bi.value.size(); i++) 
				{
					if (temp1.value[i])
					{
						temp.value[i] = !bi.value[i];
					}
					else {
						if (bi.value[i])
						{
							temp.value[i] = true;
							temp1.borrow(i);
						}
						else {
							temp.value[i] = false;
						}
					}
				}
				for (int i = bi.value.size(); i < temp1.value.size(); i++)
				{
					temp.value[i] = temp1.value[i];
				}
			}
			else {
				temp.value[0] = false;
				for (int i = 1; i < value.size(); i++)
				{
					if (temp2.value[i])
					{
						temp.value[i] = !value[i];
					}
					else {
						if (value[i])
						{
							temp.value[i] = true;
							temp2.borrow(i);
						}
						else {
							temp.value[i] = false;
						}
					}
				}
				for (int i = value.size(); i < temp2.value.size(); i++)
				{
					temp.value[i] = temp2.value[i];
				}
			}
		}
		else if (value[0] || bi.value[0])
		{
			if (value[0])
			{
				temp2.value[0] = true;
				return temp1 + temp2;
			}
			else {
				temp1.value[0] = true;
				temp = temp1 + temp2;
				temp.value[0] = false;
				return temp;
			}
		}
		else {
			temp1.value[0] = true;
			temp2.value[0] = true;
			temp = temp1 - temp2;
			temp.value[0] = false;
		}
		for (int i = temp.value.size() - 1; i > 0 && temp.value[i] == false; i--)
		{
			temp.value.resize(temp.value.size() - 1);
		}
		return temp;
	}
	bigInt operator*(bigInt bi)
	{
		bigInt temp, temp1, temp_t, temp_a, temp_bi, temp_1;
		temp_1.value.push_back(true);
		temp_1.value.push_back(true);
		temp_a.value = value;
		temp_bi = bi;
		temp_bi.value[0] = true;
		temp_a.value[0] = true;
		bool sign;
		temp.value.push_back(true);
		if (value.size() == 2 || bi.value.size() == 2)
		{
			if (!value[1] || !bi.value[1])
			{
				temp.value.push_back(false);
				return temp;
			}
		}
		temp.value.resize(bi.value.size() + value.size());
		temp1 = temp;
		if (value[0] && bi.value[0])
		{
			sign = true;
		}
		else if (value[0] || bi.value[0])
		{
			sign = false;
		}
		else {
			sign = true;
		}
		temp1.value.resize(value.size());
		temp_t = temp1;
		for (int i = 1; i < bi.value.size(); i++)
		{
			temp1 = temp_t;
			if (bi.value[i] == true)
			{
				temp1 = temp_a;
			}/*
			for (int j = 1; j < value.size(); j++)
			{
				if (value[j] && bi.value[i])
				{
					temp1.value[j] = true;
				}
				else {
					temp1.value[j] = false;
				}
			}*/
			if (i != 1)
			{
				temp1.muiltitwo(i - 1);
			}
			temp = temp + temp1;
		}
		temp.value[0] = sign;
		for (int i = temp.value.size() - 1; i > 0 && temp.value[i] == false; i--)
		{
			temp.value.resize(temp.value.size() - 1);
		}
		return temp;
	}
	bigInt operator/(bigInt bi)
	{
		bigInt temp, temp1, temp_t, temp_a, temp_b, temp_1, temp2, temp3, temp_remainder;
		temp_1.value.push_back(true);
		temp_1.value.push_back(true);
		temp_a.value = this->value;
		temp_b = bi;
		temp_a.value[0] = true;
		temp_b.value[0] = true;
		bool sign;
		temp.value.push_back(true);
		temp.value.resize(temp_a.value.size());
		temp1.value.resize(value.size());
		if (value[0] && bi.value[0])
		{
			sign = true;
		}
		else if (value[0] || bi.value[0])
		{
			sign = false;
		}
		else {
			sign = true;
		}
		if (temp_a < temp_b)
		{
			return temp;
		}
		else if (temp_a == temp_b)
		{
			temp.value[1] = true;
			return temp;
		}
		else if (temp_b == temp_1)
		{
			temp_a.value[0] = sign;
			return temp_a;
		}
		if (value.size() == 2 || bi.value.size() == 2)
		{
			if (!value[1] || !bi.value[1])
			{
				temp.value.push_back(false);
				return temp;
			}
		}
		bigInt temp_a_temp = temp_a;
		bigInt temp_b_temp = temp_b;
		temp_remainder = temp_a;
		temp.value.resize(temp_a_temp.value.size());
		for (int i = temp_a.value.size() - temp_b.value.size() + 1; temp_b <= temp_remainder && i > 0; i--)
		{
			temp_b_temp = temp_b;
			if (i - 1 > 0)
			{
				temp_b_temp.muiltitwo(i - 1);
			}
			if (temp_b_temp <= temp_remainder)
			{
				temp_remainder = temp_remainder - temp_b_temp;
				temp.value[i] = true;
			}
		}
		temp.value[0] = sign;
		for (int i = temp.value.size() - 1; i > 0 && temp.value[i] == false; i--)
		{
			temp.value.resize(temp.value.size() - 1);
		}
		return temp;
	}
	bigInt operator%(bigInt bi)
	{
		bigInt temp, temp1, temp_t, temp_a, temp_b, temp_1, temp2, temp3, temp_remainder;
		temp_1.value.push_back(true);
		temp_1.value.push_back(true);
		temp_a.value = this->value;
		temp_b = bi;
		temp_a.value[0] = true;
		temp_b.value[0] = true;
		bool sign;
		temp.value.push_back(true);
		temp.value.resize(temp_a.value.size());
		temp1.value.resize(value.size());
		if (value[0] && bi.value[0])
		{
			sign = true;
		}
		else if (value[0] || bi.value[0])
		{
			sign = false;
		}
		else {
			sign = true;
		}
		if (temp_a < temp_b)
		{
			return temp;
		}
		else if (temp_a == temp_b)
		{
			return temp;
		}
		else if (temp_b == temp_1)
		{
			return temp;
		}
		if (value.size() == 2 || bi.value.size() == 2)
		{
			if (!value[1] || !bi.value[1])
			{
				return temp;
			}
		}
		bigInt temp_a_temp = temp_a;
		bigInt temp_b_temp = temp_b;
		temp_remainder = temp_a;
		temp.value.resize(temp_a_temp.value.size());
		for (int i = temp_a.value.size() - temp_b.value.size() + 1; temp_b <= temp_remainder && i > 0; i--)
		{
			temp_b_temp = temp_b;
			if (i - 1 > 0)
			{
				temp_b_temp.muiltitwo(i - 1);
			}
			if (temp_b_temp <= temp_remainder)
			{
				temp_remainder = temp_remainder - temp_b_temp;
				temp.value[i] = true;
			}
		}
		return temp_remainder;
	}
};

void bigInt::fromBinary(string a)
{
	value.resize(0);
	if (a[0] == '-')
	{
		value.push_back(false);
		reverse(a.begin(), a.end());
		for (int i = 0; i < a.size() - 1; i++)
		{
			value.push_back(a[i] == '1');
		}
	}
	else {
		value.push_back(true);
		reverse(a.begin(), a.end());
		for (int i = 0; i < a.size(); i++)
		{
			value.push_back(a[i] == '1');
		}
	}
}

void bigInt::outputBinary()
{
	bigInt temp;
	temp.value = value;
		if (!temp.value[0])
		{
			cout << "-";
		}
		reverse(temp.value.begin(), temp.value.end());
		for (int i = 0; i < temp.value.size() - 1; i++)
		{
			if (temp.value[i])
			{
				cout << "1";
			}
			else {
				cout << "0";
			}
		}
		cout << endl;
}

void bigInt::carry(int n)
{
	if (value.size() == n + 1)
	{
		value.resize(value.size() + 1);
	}
	if (value[n + 1])
	{
		value[n + 1] = false;
		carry(n + 1);
	}
	else {
		value[n + 1] = true;
	}
}

void bigInt::borrow(int n)
{
	if (n == value.size() - 1)
	{
		value.resize(value.size() - 1);
	}
	else {
		if (value[n + 1])
		{
			value[n + 1] = false;
		}
		else {
			borrow(n + 1);
			value[n + 1] = true;
		}
	}
}

void bigInt::muiltitwo(int n)
{
	value.resize(value.size() + n);
	for (int i = value.size() - 1; i > n; i--)
	{
		value[i] = value[i - n];
		value[i - n] = false;
	}
	value[1] = false;
}

void bigInt::devidetwo()
{
	if (value.size() > 3)
	{
		for (int i = 1; i < value.size() - 1; i++)
		{
			value[i] = value[i + 1];
		}
		value.resize(value.size() - 1);
	}
	else {
		value.resize(0);
		value.push_back(true);
		value.push_back(false);
	}
}