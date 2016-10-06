/*Carlos Alfredo Morales(Sn0rlax)
    Sep  24-2016
	Chapter  5.Exercise 7:  Solving quadratic equations
	Book: Programming ~ Principles and Practice using C++
*/	
#include <std_lib_facilities.h>

//Quadratic equations are of the form:
//   a*x^2+b*x+c=0
//To solve these, one uses the quadratic formula
// x=  (-b +or- sqrt(b^2-4ac))/2a

int main()
{
	cout<<"This program solves quadratic equations."<<endl;
	cout<<"Quadratic equations are of the form: a*x^2+b*x+c=0"<<endl;
	cout<<"Please insert the values of a, b and c separated by spaces: ";
	int a;
	int b;
	int c;
	cin>>a>>b>>c;
	if (a==0) error("a is equal to zero, your equation is linear, not quadratic");
	if((pow(b,2)-4*a*c)<0)error("b^2-4ac is less than zero, the program would fail.\nReason:Square root would have a negative number in it.");
	int inside_sqrt=pow(b,2)-4*a*c;
	double square_root=sqrt(pow(b,2)-4*a*c);
	int int_square_root=square_root;
	if (!(int_square_root==square_root)){
		cout<<"Negative root is: "<<-b<<"-sqrt("<<inside_sqrt<<")"<<endl;
		cout<<"                 -------------"<<endl;  
		cout<<"                       "<<2*a<<endl;
		cout<<"\n";
		cout<<"Positive root is: "<<-b<<"+sqrt("<<inside_sqrt<<")"<<endl;
		cout<<"                 -------------"<<endl;  
		cout<<"                       "<<2*a<<endl;
		
	}
	else {
	double sol_neg_root=(-b-(square_root))/2*a;
	cout<<"Negative root is: "<<sol_neg_root<<endl;
	double sol_pos_root=(-b+(square_root))/2*a;
	cout<<"Positive root is: "<<sol_pos_root<<endl;
	}
	
}



