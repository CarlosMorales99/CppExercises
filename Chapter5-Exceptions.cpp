/*Carlos Alfredo Morales(Sn0rlax)
    Sep  20-2016
	Chapter  5: Error Handling.
	Book: Programming ~ Principles and Practice using C++
*/	

#include "std_lib_facilities.h"
//Classes and variables definition
constexpr int frame_width=2;
class bad_area{};
class bad_f_area{};
int a=2;//PLAY WITH THESE VARIABLES TO GET OR  DONT GET ERRORS
int b=-1;
int c=3;
int d=5;
//Custom functions
int area(int length, int width) // calculate area of a rectangle
{
if (length<=0||width<=0)throw bad_area{};
return length*width;
}

int framed_area(int x, int y) // calculate area within frame
{
int x1=x-frame_width;
int y1=y-frame_width;
if (x1<=0||y1<=0) throw bad_f_area{};
int result=area(x1,y1);
return result;
}
//Running code
int main()
try{

	int area1= area(a,b);
	int area2=framed_area(b,c);
	int area3=area(a,d);
	cout<<area1<<"\n";
	cout<<area2<<"\n";
	cout<<area3<<"\n";
	}

catch (exception& e) {
cerr << "error: " << e.what() << '\n';
keep_window_open();
return 1; // 1 indicates failure
}
catch (bad_area) {
cerr << "Oops: bad input for area(), it must be positive integers\n";
keep_window_open();
return 2; // 2 indicates failure
}
catch (bad_f_area) {
cerr << "Oops: bad input for area(), it must be positive integers\n";
keep_window_open();
return 3; // 2 indicates failure
}
catch (...) {
cerr << "Oops: unknown exception!\n";
keep_window_open();
return 4; // 2 indicates failure
}

  


