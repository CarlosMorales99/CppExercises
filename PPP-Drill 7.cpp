/*Carlos Alfredo Morales(Sn0rlax)
    Oct 06-2016
	Chapter  7.Drill: Improving the calculator
	Book: Programming ~ Principles and Practice using C++
////////////////////////////////////
Calculation:
	Statement
	Print
	Quit
	Calculation Statement
Statement:
	Declaration
	Expression
Declaration:
	"let" Name "=" Expression
////////////////////////////////////	
Expression:
	Term
	Expression + Term
	Expression – Term
Term:
	Primary
	Term * Primary
	Term / Primary
	Term % Primary
Primary:
	Number
	( Expression )
	– Primary
	+ Primary
	Name
	sqrt ( Expression )
	pow( Expression , integer)
Number:
	floating-point-literal
	
	
*/
#include "std_lib_facilities.h"
//Definition of Tokens and their funcions, Tokens are the main object with which the program works
struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch,string n) :kind(ch), name(n){}
	};
// Token stream is used to  store  Tokens and use them repeatedly
class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(false), buffer(0) { }

	Token get();
	void unget(Token t) { buffer=t; full=true; }

	void ignore(char);
};
//Constant characters to represent different objects in a Token
const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char my_sqrt= 's';
const char my_pow='p';

//Most used function, used to extract characters from stantard input (or token_stream) and to the right thing with them
Token Token_stream::get()
{
	if (full) { full=false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case ',':
	case '=':	
		return Token(ch);//These characters represent themselves, they are used for various operations
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	cin.unget();
		double val;
		cin >> val;
		 char sufix;
		 cin.get(sufix);
		 if(sufix=='k') val*=1000;
		 else if (sufix=='m')val*=1000000;
		 else cin.unget();
		 if (!cin){
			error("Invalid number");}
		return Token(number,val);//Right here it stores a Token of kind number('8') with its respective  double value
	}
	default:
		if (isalpha(ch)) { //This is used to create variable Tokens 
			string s;
			s += ch;
			while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+=ch;
			cin.unget();
			if (s == "let") return Token(let);	//Used to assign  values to variables
			if (s == "quit"||s=="exit") return Token(quit);//Used to exit the program
			if(s=="sqrt") return Token (my_sqrt);
			if (s=="pow") return Token(my_pow);
			return Token(name,s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c) //When an error comes up, this is used to ignore the rest of the error until  it finds the char c  entered
{
	if (full && c==buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin>>ch)
		if (ch==c) return;
}

struct Variable {  //Variable types that can be assigned by the user or pre-defined by the program itself
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;	 //All the variables are stored here

double get_value(string s) //This is used to extract the value of a variable inside the variables vector
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ",s);
}

void set_value(string s, double d) //I think it will be used later to reset values to a variable. ///Declared but not used
{
	for (int i = 0; i<=names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ",s);
}

bool is_declared(string s) //To be used before attempting to add a new variable
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts; 

double expression();//The grammar requires expression() to be declared first

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-':
		return - primary();
	case '+':
		return + primary();
	case my_sqrt:{
		t=ts.get();
		if (t.kind!='(')error("expected '(' after pow)");
		double d = expression();
		if (d<0) error("Cant calculate square root of a negative number");
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return sqrt(d);
	}
	case my_pow:{
		t=ts.get();
		if (t.kind!='(')error("expected '(' after pow)");
		double d=expression();
		t=ts.get();
		if (t.kind !=',' ) error("expected a ',' after exponent base");
		int r=narrow_cast<int>(expression());
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return pow(d,r);
	}
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	default:
		error("primary expected");
	}
}

double term()
{
	double left = primary();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		case '%':{
			double d=primary();
			if(d==0)error("divide by zero");
			int int1=narrow_cast<int>(left);
			int int2=narrow_cast<int>(d);
			left=int1%int2;
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration() //This handles declarations, its only used if the statement begins with "let"
{
	Token t = ts.get();
	if (t.kind != 'a') error ("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of " ,name);
	double d = expression();
	names.push_back(Variable(name,d));
	return d;
}

void define_name(string var, double val)
// add (var,val) to names vector
{
if (is_declared(var)) error(var," declared twice");
names.push_back(Variable(var,val));
return;
}
double statement() //This distinguishes between declarations and operations
{
	Token t = ts.get();
	switch(t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess() //This is used to handle correct operations in the same line with errors, it skips characters until a ';' is detected, then continues normally
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()  
{
while (cin)
	try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t=ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch(runtime_error& e) {
		cerr <<"ERROR: "<< e.what() << endl;
		clean_up_mess();
		cin.clear();
	}
}

int main(){
try {
		//Predefined names
		define_name("pi",3.1415926535);
		define_name("e",2.7182818284);
		define_name("k",1000);
		cout<<"Hello!. This calculator can perform the following operations:"<<endl;
		cout<<"*Basics: a+b,  a-b,  a/b,  a*b"<<endl;
		cout<<"*Advanced:"<<endl; 
		cout<<"-| a%b | Shows the remainder of a division. Example: 2%3=2"<<endl;
		cout<<"-| pow(a,b) | exponencial operation, where a is the base and b is the exponent."<<endl;
		cout<<"-| sqrt(x) | square root, where x is a positive value"<<endl;
		cout<<"-| let name = operation or value | This assigns the value after = to the entered name"<<endl;
		cout<<"*I can handle different operations in a single line,\ndoing them in the correct mathematical order"<<endl;
		cout<<"*To show the result you must enter a ';' at the end"<<endl;
		cout<<"*To terminate the program write exit or quit"<<endl;
		cout<<"*Please feel free to try different inputs and spot any bugs in the program"<<endl;
		calculate();
		return  0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		keep_window_open("q");
		return 1;
	}
	catch (...) {
		cerr << "exception\n";
		keep_window_open("q");
		return 2;
	}
}
