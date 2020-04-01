int M=0;
    for(int i=0;i<24;i++){
        if( room.status[i]!='U'){
            M++;
        }
    }
    string A;
    if(M>=12){
		totalprice=totalprice;
		}
	else if(M>=6){
		totalprice=totalprice+200;
	}
	else if(M>=3){
		totalprice=totalprice+200;
	}
	srand(time(0));
	int C = rand()%10;
	cout<<"\nRandom Lucky Number : " << C;
	if(C==3){
		cout<<"\nSuper Lucky";
		totalprice=totalprice*85/100;		
	}
	else if(C==5){
		cout<<"\nMore Lucky";
		totalprice=totalprice*70/100;
	}
	else if(C==7){
		cout<<"\nLucky";
		totalprice=totalprice-250;
	}
	else if(C==9){
		cout<<"\nSome Lucky";
		totalprice=totalprice-50;
			}
	else{
		cout<<"\nUnlucky";
        totalprice=totalprice;
	}