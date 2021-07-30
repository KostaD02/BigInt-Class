#include <iostream> 

using namespace std; 

void reverseString(string& String){ 
	int length = String.length(); 
	for(int i=0;i<length/2;i++){ 
		swap(String[i],String[length-i-1]); 
	}
}

class BigInt{ 
	private: 
		string number; 
	public:
		BigInt(string number="0"){ 
			this->number=number;
		}
		string getNumber(){
			return this->number;
		}
		int length(){ 
			return this->number.length();
		}
		void printNumber(){ 
			cout<<this->number;
		}
		friend istream &operator >>(istream &Input,BigInt &Temp); 
		friend ostream &operator <<(ostream &Output,const BigInt &Temp);
};

BigInt operator +(BigInt numberOne,BigInt numberTwo){ 
	string str = ""; 
    string first = numberOne.getNumber(); 
    string second = numberTwo.getNumber(); 
    if (first.length() > second.length()) swap(first, second); 
    int taking = 0; 
    int lengthOne = first.length(); 
	int lengthTwo = second.length(); 
    int length = lengthTwo - lengthOne; 
    for (int i=lengthOne-1; i>=0; i--){ 
        int sum = ((first[i]-'0')+(second[i+length]-'0')+taking); 
        str.push_back(sum%10 + '0');
        taking = sum/10;
    }
    for (int i=lengthTwo-lengthOne-1; i>=0; i--){ 
        int sum = ((second[i]-'0')+taking);
        str.push_back(sum%10 + '0');
        taking = sum/10;
    }
    if (taking) str.push_back(taking+'0');
    reverseString(str); 
    return BigInt(str); 
}

BigInt operator *(BigInt numberOne,BigInt numberTwo){ 
    string first = numberOne.getNumber(); 
    string second = numberTwo.getNumber(); 
	if(first[0]=='0'||second[0]=='0') return BigInt("0");
	int lengthOne = first.length(); 
	int lengthTwo = second.length();
	string str(lengthOne + lengthTwo, '0');
	for (int i = lengthTwo - 1; i >= 0;i--){
		int tempOne = 0; 
		int tempTwo = 0; 
		for (int j = lengthOne - 1; j >= 0;j--){ 
			int tempThree = (second[i] - '0') * (first[j] - '0') + tempOne;
			tempOne = tempThree / 10; 
			tempThree = tempThree % 10; 
			int tempForth = str[i + j + 1] - '0' + tempThree + tempTwo;
			str[i + j + 1] = tempForth % 10 + '0';
			tempTwo = tempForth / 10; 
		}
		str[i] += tempOne + tempTwo; 
	}
	if(str[0]=='0') 
		str = str.substr(1, str.length());
	return BigInt(str); 
}

BigInt operator /(BigInt numberOne,unsigned long long int numberTwo){ 
	string str = ""; 
    string first = numberOne.getNumber(); 
    int index = 0 ;
    int temp = first[index]-'0';
    while(temp<numberTwo) temp=temp*10+(first[index++]-'0');
    while(first.length()>index){
    	str +=(temp/numberTwo)+'0';
    	temp=(temp%numberTwo)*10+first[index++]-'0';
	}
	if(str.length()==0) return BigInt("0");
    return BigInt(str);
}

istream &operator >>(istream &Input,BigInt &Temp){
	cout<<"Input number: "; 
	Input>>Temp.number;
	return Input;
}

ostream &operator <<(ostream &Output,const BigInt &Temp){
	Output<<"Inputed number: "<<Temp.number<<endl;
	return Output;
}

int main(int argc, char** argv) { 
	return 0; 
} 
