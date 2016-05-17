#include"lab5.h"

using namespace std;

void HugeInt::initialize(){
	sign=true;
	len=1;
	memset(num, 0, sizeof(num)); //fill num with 0
}

HugeInt::HugeInt(){
	initialize();
}

HugeInt::HugeInt(const char &n){
	initialize();
	int check=0;
	ptr=&n;
	if(ptr[0]=='-'){ //check if negative
		sign=false;
		check++;
	}
	else if(ptr[0]=='+'){ //eliminate + symbol
		check++;
	}
	len=strlen(ptr);
	
	for(int i=check;i<len;i++){
		if(ptr[i]=='0'){check++;}
		else{break;}
	}
	for(int i=len-1,j=0;i>=check;i--,j++){
		num[j]=ptr[i]-'0'; //turn to int
	}
	len-=check;
	if(len==0){ //if empty
		num[0]=0;
		len=1;
	}
}

HugeInt HugeInt::invert()const{ //return its invert sign num
	HugeInt tmp(*this);
	tmp.sign=!tmp.sign;
	return tmp;
}

ostream &operator<<(ostream &out, const HugeInt &num){
	char tmp[HugeInt::size];
	int len=0;
	if(num.sign==false){
		tmp[0]='-';
		len++;
	}
	for(int i=num.len-1;i>=0;i--){
		tmp[len]=num.num[i]+'0';
		len++;
	}
	tmp[len]='\0';
	out<<tmp;
	return out;
}

istream &operator>>(istream &in, HugeInt &num){
	char tmp[HugeInt::size];
	int len=0;
	if(num.sign==false){
		tmp[0]='-';
		len++;
	}
	for(int i=num.len-1;i>=0;i--){
		tmp[len]=num.num[i]+'0';
		len++;
	}
	tmp[len]='\0';
	in>>num;
	return in;
}

bool operator>(const HugeInt &num1, const HugeInt &num2){
	if(num1.sign==true&&num2.sign==true){
		if(num1.len>num2.len) return true;
		else if(num1.len<num2.len) return false;
		else{
			for(int i=num1.len-1;i>=0;i--){
				if(num1.num[i]>num2.num[i]) return true;
				else if(num1.num[i]<num2.num[i]) return false;
				else continue;
			}
			return false;
		}
	}
	else if(num1.sign==true&&num2.sign==false) return true;
	else if(num1.sign==false&&num2.sign==true) return false;
	else if(num1.sign==false&&num2.sign==false){
		return num2.invert()>num1.invert();
	}
}

bool operator<(const HugeInt &num1, const HugeInt &num2){
	return (num2>num1);
}

HugeInt operator+(const HugeInt &num1, const HugeInt &num2){
	HugeInt ans;
	if(num1.sign==false&&num2.sign==true){
		return num2-num1.invert();
	}
	else if(num1.sign==true&&num2.sign==false){
		return num1-num2.invert();
	}
	else if(num1.sign==false&&num2.sign==false){
		ans.sign=false;
	}
	ans.len=(num1.len>num2.len)?num1.len:num2.len;
	for(int i=0;i<ans.len;i++){
		ans.num[i]+=num1.num[i]+num2.num[i];
		if(ans.num[i]>=10){ //check carry
			ans.num[i+1]+=(ans.num[i]/10);
			ans.num[i]%=10;
		}
	}
	if(ans.num[ans.len]!=0){
		ans.len++;
	}
	return ans;
}

HugeInt operator+=(HugeInt &num1, const HugeInt &num2){
	num1=num1+num2;
	return num1;
}

HugeInt operator-(const HugeInt &num1, const HugeInt &num2){
	HugeInt ans;
	if(num1.sign==true&&num2.sign==false){
		return num1+num2.invert();
	}
	else if(num1.sign==false&&num2.sign==true){
		return num1+num2.invert();
	}
	else if(num1.sign==false&&num2.sign==false){
		return num2.invert()-num1.invert();
	}
	else{
		if(num1<num2){
			ans=num2-num1;
			ans.sign=false;
			return ans;
		}
		else{
			ans.len=num1.len;
			for(int i=0;i<ans.len;i++){
				if((ans.num[i]+num1.num[i])>=num2.num[i]){
					ans.num[i]+=(num1.num[i]-num2.num[i]);
				}
				else{
					ans.num[i+1]-=1;
					ans.num[i]+=10+(num1.num[i]-num2.num[i]);
				}
			}
			for(int i=num1.len-1;i>=0;i--,ans.len--){
				if(ans.num[i]!=0){break;}
			}
			if(ans.len==0){
				ans.len=1;
				ans.num[0]=0;
			}
			return ans;
		}
	}
}

