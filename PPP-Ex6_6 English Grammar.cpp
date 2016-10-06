/*Carlos Alfredo Morales(Sn0rlax)
    Oct 1-2016
	Chapter  6.Exercise 6:  English grammar checker
	Book: Programming ~ Principles and Practice using C++
*/
#include <std_lib_facilities.h>

class Salida{};

bool noun(string word){
	if (word=="the"){
		string article="";
		cin>>article;
		return noun(article);
	}
	if (word=="birds" || word=="fish"||word=="c++")return true; //This checking (in noun,verb,and conjuction) can also be implemented with vectors
	else return false;
}

bool verb(string word){
	if (word=="rules"||word=="fly"||word=="swim")return true;
	else return false;
}

bool conjunction(string word){
	if(word=="and"||word=="or"||word=="but") return true;
	else return false;
}

bool sentence(){
	string w1;
	cin >>w1;
	if (w1=="q"){
	throw Salida{};
	}
	
	if (!noun(w1)) return false;
	string w2;
	cin>>w2;
	if (!verb(w2)) return false;
	string w3;
	cin>>w3;
	if(w3==".") return true;
	if (!conjunction(w3)) return false;
	return sentence();
}


int main()
try
{
	cout<<"Please write a sentence and i'll check if the grammar is correct or not.\nThe sentence must end with a space followed by a dot '.'\nWrite 'q' to cancel\n-";
	while(cin){
	if (sentence()){
			cout<<"OK\n";
	}
	else {
		cout<<"NOT OK\n";
	}
	cout<<"Please try again.\n-";
	}

	}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n'; 
	keep_window_open();
    return 1;
}
catch(Salida){
	cerr<<"Program aborted"<<'\n';
	keep_window_open();
	return 2;
	}
catch (...) {
    cerr << "Oops: unknown exception!\n"; 
	keep_window_open();
    return 3;
}



//------------------------------------------------------------------------------



