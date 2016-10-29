/*Carlos Alfredo Morales(Sn0rlax)
    Oct 29-2016
	Chapter  7.Exercises 1,2,3,6 Improving the calculator
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
//-----------------------------------------------------------------------------------------------------------------------------//
//Definition of Tokens and their functions, Tokens are the main object with which the program works
struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch,string n) :kind(ch), name(n){}
	};
//-----------------------------------------------------------------------------------------------------------------------------//
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
//-----------------------------------------------------------------------------------------------------------------------------//
//Constant characters to represent different objects in a Token
const char help='h';
const char constant='c';
const char let = 'l';
const char mod = 'm';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char my_sqrt= 's';
const char my_pow='p';
//-----------------------------------------------------------------------------------------------------------------------------//
//Most used function, used to extract characters from standard input (or token_stream) and to the right thing with them
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
			while(cin.get(ch) && (isalpha(ch) || isdigit(ch)||(ch=='_'))) s+=ch;
			cin.unget();
			if(s=="help") return Token(help);
			if(s=="const")return Token(constant);//Notation to create constant variables
			if(s=="mod")return Token(mod);//This is used to modify the value of a previously assigned name
			if (s == "let") return Token(let);	//Used to assign  values to variables
			if (s == "quit"||s=="exit") return Token(quit);//Used to exit the program
			if(s=="sqrt") return Token (my_sqrt);
			if (s=="pow") return Token(my_pow);
			return Token(name,s);
		}
		error("Bad token");
	}
}
//-----------------------------------------------------------------------------------------------------------------------------//
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
//-----------------------------------------------------------------------------------------------------------------------------//
struct Variable {  //Variable types that can be assigned by the user or pre-defined by the program itself
    bool constant;
	string name;
	double value;
	Variable(string n, double v) :constant(false),name(n), value(v) { }
    Variable(bool b,string n, double v) :constant(b),name(n),value(v){ }
};
//-----------------------------------------------------------------------------------------------------------------------------//
vector<Variable> var_table;	 //All the variables are stored here
//-----------------------------------------------------------------------------------------------------------------------------//
double get_value(string s) //This is used to extract the value of a variable inside the variables vector
{
	for (int i = 0; i<var_table.size(); ++i)
		if (var_table[i].name == s) return var_table[i].value;
	error("get: undefined name ",s);
}
//-----------------------------------------------------------------------------------------------------------------------------//
void set_value(bool b,string s, double d) //Function to change to value of a previously declared name
{

	for (int i = 0; i<=var_table.size(); ++i)
		if (var_table[i].name == s) {
			if (var_table[i].constant)error("Cant change the value of a constant name");
			if (b) var_table[i].constant=true;
			var_table[i].value = d;
			return;
		}
	error("set: undefined name ",s);
}
//-----------------------------------------------------------------------------------------------------------------------------//
bool is_declared(string s) //To be used before attempting to add a new variable
{
	for (int i = 0; i<var_table.size(); ++i)
		if (var_table[i].name == s) return true;
	return false;
}

Token_stream ts;
//-----------------------------------------------------------------------------------------------------------------------------//
double expression();//The grammar requires expression() to be declared first
//-----------------------------------------------------------------------------------------------------------------------------//
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
//-----------------------------------------------------------------------------------------------------------------------------//
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
//-----------------------------------------------------------------------------------------------------------------------------//
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
//-----------------------------------------------------------------------------------------------------------------------------//
double declaration() //This handles declarations, its only used if the statement begins with "let"
{
	Token t1 = ts.get();
	Token t2 = 'a';
	bool const_declare=false;
	if (t1.kind==constant){const_declare=true;
    t2 = ts.get();}
    else t2=t1;
	if (t2.kind != 'a') error ("name expected in declaration");
	string name = t2.name;
	if (is_declared(name)) error(name, " declared twice, use \"mod\" to modify variables");
	Token t3 = ts.get();
	if (t3.kind != '=') error("= missing in declaration of " ,name);
	double d = expression();
	var_table.push_back(Variable(const_declare,name,d));
	return d;
}
//-----------------------------------------------------------------------------------------------------------------------------//
double modification()
{
    Token t1 = ts.get();
	Token t2 = 'a';
	bool const_declare=false;
	if (t1.kind==constant){const_declare=true;
    t2 = ts.get();}
    else t2=t1;
    if (t2.kind != 'a') error ("name expected in modification");
    string name = t2.name;
    Token t3 = ts.get();
	if (t3.kind != '=') error("= missing in modification of " ,name);
    double d = expression();
    set_value(const_declare,name,d);
    return d;
}
//-----------------------------------------------------------------------------------------------------------------------------//
void define_name(string var, double val)
// add (var,val) to var_table vector
{
if (is_declared(var)) error(var," declared twice");
var_table.push_back(Variable(var,val));
return;
}
//-----------------------------------------------------------------------------------------------------------------------------//
string help_message="\nHello!. This calculator can perform the following operations:\n*Basics: a+b,  a-b,  a/b,  a*b\n*Advanced:\n-| a%b | Shows the remainder of a division. Example: 2%3=2\n-| pow(a,b) | exponential operation, where a is the base and b is the exponent.\n-| sqrt(x) | square root, where x is a positive value\n-| let name = operation or value | This assigns the value after = to the entered name\n-| mod name = operation or value | Changes the value of \"name\" variable\n*Also, if you write \"const\" before the name(in either \"let\" or \"mod\",\nyou permanently turn that variable to a constant one\n*I can handle different operations in a single line,\ndoing them in the correct mathematical order\n*To show the result you must enter a ';' at the end of the statement\n*To terminate the program write \"exit\" or \"quit\"\n*Please feel free to try different inputs and spot any bugs in the program.Thanks.";
//-----------------------------------------------------------------------------------------------------------------------------//
double statement() //This distinguishes between declarations and operations
{
	Token t = ts.get();
	switch(t.kind) {
    case help:
        cout<<help_message<<endl;
        return 0;
    case mod:
        return modification();
    case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}
//-----------------------------------------------------------------------------------------------------------------------------//
void clean_up_mess() //This is used to handle correct operations in the same line with errors, it skips characters until a ';' is detected, then continues normally
{
	ts.ignore(print);
}
//-----------------------------------------------------------------------------------------------------------------------------//
const string prompt = "> ";
const string result = "= ";
//-----------------------------------------------------------------------------------------------------------------------------//
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
//-----------------------------------------------------------------------------------------------------------------------------//
int main(){
try {
		//Predefined variables
		define_name("pi",3.1415926535);
		define_name("e",2.7182818284);
		define_name("k",1000);
		cout<<"Hello!. Welcome to my calculator:"<<endl;
		cout<<"To see a complete list with the supported operations and utilities, type \"help\""<<endl;
		cout<<"*I can handle different operations in a single line,"<<endl;
		cout<<"doing them in the correct mathematical order"<<endl;
		cout<<"*To show the result you must enter a ';' at the end of the statement"<<endl;
		cout<<"*To terminate the program write exit or quit"<<endl;
		cout<<"*Please feel free to try different inputs and spot any bugs in the program.Thanks."<<endl;
		calculate();
		return  0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		//keep_window_open("q");
		return 1;
	}
	catch (...) {
		cerr << "exception\n";
		//keep_window_open("q");
		return 2;
	}
}

