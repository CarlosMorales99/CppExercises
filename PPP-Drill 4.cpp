/*Carlos Alfredo Morales(Sn0rlax)
    Sep 14-2016
	Solution to Drill on Chapter 4
	Book: Programming ~ Principles and Practice using C++
*/	

#include "std_lib_facilities.h"

int main(){
	double largestMeasure=2.2E-308;
	double largestNumber=2.2E-308;
	string largestUnit;
	double smallestMeasure=1.8E+307;
	double smallestNumber=1.8E+307;
	string smallestUnit;
	double newNumber;
	double tempNumber;
	string unit;
	double sum=0;
	vector<double>values;
	cout<<"To close the program insert a ( | ).\nPlease insert a distance measure with its unit (unit can ONLY be cm,m,in ot ft): ";
	while (cin>>newNumber>>unit){
		if (unit=="cm")
			tempNumber=newNumber /100;
		
		else if (unit=="m")
				tempNumber=newNumber;
		
		else if (unit =="in")
				tempNumber=newNumber * 2.54/100;
		
		else if (unit =="ft")	
				tempNumber=newNumber *12*2.54/100;
		
		else	{
				cout<<"Invalid unit";
				return 0;
		}
		values.push_back(tempNumber);
		sum+=tempNumber;
		if (tempNumber<smallestMeasure){
		smallestNumber=newNumber;
		smallestUnit=unit;
		smallestMeasure=tempNumber;
		
		}
		if (tempNumber>largestMeasure){
		largestNumber=newNumber;
		largestUnit=unit;
		largestMeasure=tempNumber;
		}
		cout<<"\n\nThe largest value so far is: "<<largestNumber<<largestUnit<<"\n";	
		cout<<"The smallest value so far is: "<<smallestNumber<<smallestUnit<<"\n";
		cout<<"The sum of entered measures is: "<<sum<<"meters.\n";
		sort(values);
		for (double x : values)
			cout<<x<<"meters \n";
		cout<<"\n\nTo run the program insert any number.\nTo close the program insert a ( | ) : ";
	
	}
	
	
}		

		


  


