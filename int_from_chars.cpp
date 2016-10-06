/*Carlos Alfredo Morales(Sn0rlax)
    Oct 1-2016
	Chapter  6.Exercise 9:  Compose integers out of characters: 123 is 1 hundered 2 tens and 3 ones 
	Book: Programming ~ Principles and Practice using C++
*/
#include <std_lib_facilities.h>
class Salida{};
int main()
try
{
	vector<int>digits;
	vector<string>units;
	units.push_back("ones");
	units.push_back("tens");
	units.push_back("hundreds");
	units.push_back("thousands");
	
	cout<<"Please write a positive integer number with no more than "<<units.size()<<" digits\nfollowed by a semicolon ';' \n=";
	char ch;
	while (cin>>ch){
		if (ch!=';'){
		if (ch<'0' || '9'<ch) throw Salida{};
		digits.push_back(ch-'0');
		}
		else break;
	}
	if (digits.size()==0) error("no digits");
	if (units.size()<digits.size()) error("Sorry, cannot handle that many digits");
	
	int number=0;
	int exponent=0;
	for(int i=digits.size()-1;i>=0;--i){
		if (exponent==0){
			number+=digits[digits.size()-1];
			++exponent;
		}
		else {
		int power=10;
		for (int i=1;i<exponent;++i){
			power*=10;
		}
		number+=digits[i]*power;
		++exponent;
		}
	}
	
	cout<<number<<" is";
	for (int i=digits.size()-1;i>=0;--i){
		cout<<" "<<digits[digits.size()-(i+1)]<<" "<<units[i];
	}
}		
catch (exception& e) {
    cerr << "error: " << e.what() << '\n'; 
	keep_window_open();
    return 1;
}
catch(Salida){
	cerr<<"A invalid number has been inserted"<<'\n';
	keep_window_open();
	return 2;
	}
catch (...) {
    cerr << "Oops: unknown exception!\n"; 
	keep_window_open();
    return 3;
}