/*Carlos Alfredo Morales(Sn0rlax)
    Sep  16-2016
	Chapter 4, Exercise  8.
	Book: Programming ~ Principles and Practice using C++
*/	

#include "std_lib_facilities.h"
long int rice=1;
long int sum_of_rice=0;
int loop_count =0;
int square=0;
int result=1;
vector<int>Results;
int main(){
	while(loop_count<64){
		
		rice=pow(2,loop_count);
		cout<<"Rice: "<<rice<<"\t ";
		
		cout<<"Loop Count: "<<loop_count<<"\n";
		sum_of_rice+=rice;
		cout<<"Sum of rice: "<<sum_of_rice<<"\t";
		square=loop_count+1;
		cout<<"Squares: "<<square<<"\n";
		
		if ((rice>1000)&&(result==1)){
		result=2;	
		Results.push_back(square-1);}
		if((rice>1000000)&&(result==2)){
		result=3;
		Results.push_back(square-1);}
		if((rice>1000000000)&&(result==3)){
		Results.push_back(square-1);
		result=4;}
		++loop_count;
		}
for (int x:Results){
	cout<<x<<"\t";
}
cout<<"Total rice for the 64 squares "<<sum_of_rice<<" \n";
cout<<"Rice for the last square is "<<rice<<"\n";
cout<<"********************************************************\n";

}  




  


