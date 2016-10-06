/*Carlos Alfredo Morales(Sn0rlax)
    Sep  24-2016
	Chapter  5.Exercise: 2-5. Error Handling & Converting a temperature from Celsius to Kelvin and  Kelvin to Celsius
	Book: Programming ~ Principles and Practice using C++
*/	
#include <std_lib_facilities.h>
double ctok(double c) // converts Celsius to Kelvin
{
	if(c<-273.15)
		error("\n**The lowest temperature permitted is absolute zero (-273.15ºC)      \nPlease insert a greater temperature**\n");
	int k = c + 273.15;
	return k;
}
double ktoc(double c) // converts Kelvin to Celsius
{
	if(c<0)
		error("\n**The lowest temperature permitted is absolute zero (0ºK)      \nPlease insert a greater temperature**\n");
	int k = c - 273.15;
	return k;
}
int main()
{
	cout<<"Please insert a temperature: ";
	double c = 0; // declare input variable
	cin >> c; // retrieve temperature to input variable
	cout<<"Your temperature is in Celsius or Kelvin?. Answer (C) for Celsius and (K) for Kelvin: ";
    char answer='a';
	cin>>answer;
	if (answer=='K'){
		double k = ktoc(c); // convert temperature
		cout <<c<<"ºK is " <<k <<"ºC"<<endl; // print out temperature
	}
	else if (answer=='C'){
		double k = ctok(c); // convert temperature
		cout <<c<<"ºC is " <<k <<"ºK"<<endl; // print out temperature
	}
	else error("Answer C for Celsius or K for Kelvin please...");
	keep_window_open();
	return 0;
}


