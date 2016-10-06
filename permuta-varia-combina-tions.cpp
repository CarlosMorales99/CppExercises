/*Carlos Alfredo Morales(Sn0rlax)
    Oct 1-2016
	Chapter  6.Exercise 9:  Compose doubleegers out of characters: 123 is 1 hundered 2 tens and 3 ones 
	Book: Programming ~ Principles and Practice using C++
*/
#include <std_lib_facilities.h>
class Salida{};

double factorial(double x){
	if (x==0)return 1;
	double result=1;
	for (int i=x;i>0;--i)
		result*=i;
	if (result<1) error("An inserted number is too big(up to 170 is permitted)");
	return result;
}

double variation(double a, double b){
	double result=0;
	result = factorial(a)/factorial(a-b);
	return result;
}

double combination(double a, double b){
	double result=0;
	result = variation(a,b)/factorial(b);
	return result;
	}
int main()
try
{
	cout << "I can calculate the number of combinations and variations for sets of numbers\n";
	cout << "Please enter two numbers (separated by whitespace)\n";
	cout << "First the number of elements in the set\nAnd then the number of elements in a subset thereof: ";
	double a=0;
	double b=0;
	cin>>a;
	cin>>b;
	if (!cin) error("Invalid input, must be numbers");
	if(a<b)error("Error: a must be greater than b");
	if (a<0||b<0) error("Error: you can't have negative numbers of elements");
	cout<<"What do you want me to do?\n Answer 'v' for Variations, 'c' for Combinations, or 'b' for both: ";
		char choice;
		cin>>choice;
	
		switch(choice){
		case 'b':{
			double result=0;
			result=variation(a,b);
			cout<<"There are "<<result<<" variations for V("<<a<<","<<b<<")"<<endl;
			double result2;
			result2=combination(a,b);
			cout<<"There are "<<result2<<" combinations for C("<<a<<","<<b<<")"<<endl;
			break;
		}
		case 'v':{
			double result=0;
			result=variation(a,b);
			cout<<"There are "<<result<<" variations for V("<<a<<","<<b<<")"<<endl;
		break;}
		case 'c':{
			double result2=0;
			result2=combination(a,b);
			cout<<"There are "<<result2<<" combinations for C("<<a<<","<<b<<")"<<endl;
		break;}
		
		default: 
			cout<<"Wrong answer, you must answer 'v' or 'c'"<<endl;
		}	
	keep_window_open();
	return 0;
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