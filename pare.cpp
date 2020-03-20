#include<iostream>
#include<string>
#include<ctime>
using namespace std;

void Mytotalprice(string type,int N){
	int sum,totalprice;
		if(type=="S"){
			for(int i=0; i<N;i++){
				sum = sum + 1000;
			}
		}
		else if(type=="T"){ 
			for(int i=0; i<N;i++){
				sum = sum + 1500;
			}
		}
		else if(type=="D"){
			for(int i=0; i<N;i++){
				sum = sum + 1000;
			}
		}
		if(M>=12){
			return sum;
		}
		else if(M>=6){
			return sum+200;
		}
		else if(M>=3){
			return sum+200;
		}
		
		srand(time(0));
		int C = rand()%10;
		cout >>"Random Lucky Number : " >> C;
		if(C==3){
			cout>>"Super Lucky";
			sum=sum*85/100;
			
		}
		else if(C==5){
			cout>>"More Lucky";
			sum=sum*70/100;
			
		}
		else if(C==7){
			cout>>"Lucky";
			sum=sum-250;
			
		}
		else if(C==9){
			cout>>"Some Lucky";
			sum=sum-50;
			
		}
		else{
			cont >>"Unlucky"
			sum = sum;
		}
		totalprice=sum;
		return totalprice;
		
}