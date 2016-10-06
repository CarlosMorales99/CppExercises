/*Carlos Alfredo Morales(Sn0rlax)
    Sep  14-2016
	Number guesser bewteen 1-100. 4 Chapter, Exercise 4 .
	Book: Programming ~ Principles and Practice using C++
*/	

#include "std_lib_facilities.h"
char choice='a';
int max_number=100;
int min_number=1;
int guess=50;
int try_count=7;
int main(){
	cout<<"Please think in a number between 1-100.\nI will make a simple question: ¿Is it x?¿If not, is Greater or Lower than x?\nYou have to answer 'D' when i guessed the number,\nor 'G' for Greater, and 'L' for Lower\n";
	cout<<"Also, i have only 7 chances to guess your number, so please be fair.\n";
	while(try_count>0) {
	--try_count;
	guess=(max_number+min_number)/2;
	cout<<"¿Your number is "<<guess<<"? I have ("<<try_count<<") tries left: ";
	cin>>choice;
		if (choice=='G'){
			min_number=guess;
		}
		else if(choice=='L'){
			max_number=guess;
		}
		else if (choice=='D')
			try_count=0;
		else {
			cout<<"Sorry, wrong choice, type 'G' if your number is greater, 'L' if is lower, or 'D' if i have guessed your number\n";  
		++try_count;}
	if (min_number==99){
			guess=100;
	}
	if(max_number==2){
			guess=1;
	}
	}
cout<<"Great, so your number is: "<<guess<<". Thanks for playing!\n";
}		

		


  


