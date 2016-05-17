#ifndef LAB5_H
#define LAB5_H
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cstring>
using namespace std;

class HugeInt{
	public:
		static const int size=100;
		bool sign; //check + or -
		HugeInt(); //default constructor
		HugeInt(const char &); //copy constructor
		HugeInt invert() const;
		friend ostream &operator<<(ostream &, const HugeInt &); //cout with cascade
		friend istream &operator>>(istream &, HugeInt &); //cin with cascade
		friend bool operator<(const HugeInt &, const HugeInt &); //check less than
		friend bool operator>(const HugeInt &, const HugeInt &); //check bigger than
		friend HugeInt operator+(const HugeInt &, const HugeInt &);	//HugeInt add
		friend HugeInt operator+=(HugeInt &, const HugeInt &); 
		friend HugeInt operator-(const HugeInt &, const HugeInt &); //HugeInt substract
	private:
		void initialize();
		int num[size];
		int len;
		const char *ptr;
};
#endif
