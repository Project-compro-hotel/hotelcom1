#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cctype>
using namespace std;

struct roomtype{ //structure เก็บตัวแปรทุกอย่างเกี่ยวกับห้อง
    string type[3];
    int roomnumber[24];
    int price[3];
    char status[24];
    int bookingNO[24];
};

struct guestinfo{ //structure เก็บตัวแปรทุกอย่างเกี่ยวกับลูกค้า
    string name[24];
    string email[24];
    int phonenumber[24];
    string checkindate[24];
    string checkoutdate[24];
    roomtype *roomdata;
};


void roomsetup(roomtype &room){
    int para1=1,para2=1;
    //ตั้งค่าชนิดของห้องและราคาห้องทั้งสามชนิด
    room.type[0]="Standard"; room.price[0]=1000;
    room.type[1]="Twin bed"; room.price[1]=1500;
    room.type[2]="Deluxe";   room.price[2]=2000;
    //ตั้งค่าเลขห้อง โดยมีเงื่อนไขดังนี้ เลขห้องมี4ตัว 1101 เรียงจากซ้ายไปขวา
    //1 ตัวแรกคือชั้นของห้อง
    //1 ตัวที่สองคือชนิดของห้องโดย (1=standard,2=twinbed,3=deluxe)
    //01 คือเลขของห้อง
    //เช่น ห้อง deluxe ชั้น3 -> 3301 | ห้อง twinbed ชั้น4 ห้องที่2 -> 4202
    for(int i=0;i<4;i++){ //ลูปบันทึกเลขห้องทั้งหมดใส่ใน room.roomnumber
        for(int j=0;j<6;j++) {
            if(j==3){
                para1++;
                para2=1;
            }
            if(j==5){
                para1++;
                para2=1;
            }
            room.roomnumber[j+(i*6)]=((i+1)*1000)+(para1*100)+para2;
            para2++;
        }
        para1=1;
        para2=1;
    }
}


void Showinfo(const guestinfo info,const roomtype room,int loc){
    cout<<"\n\n+------------------------------------------------------------------------------------------+\n";
    cout<<       "|                                      GUEST INFORMATION                                   |\n";
    cout<<        "+------------------------------------------------------------------------------------------+\n";
    
    cout<<     "|      Room number     : "<< room.roomnumber[loc]<<"                                                              |";

    cout<<     "\n|      Name            : "<<info.name[loc] <<"\t\tBooking Number : "<<room.bookingNO[loc]<<"                     |";

    cout<<     "\n|      Email           : "<<info.email[loc] <<"\tTel            : 0"<<info.phonenumber[loc]<<"                |";

    cout<<     "\n|      Cleaning status : ";
    int Clean= rand()%2;
    if(Clean<=0) cout<<"YES                                                               |\n";
    else{cout<<"NO                                                                |\n";}
    cout<<"+------------------------------------------------------------------------------------------+\n";
}



int checkuser(){ //ฟังก์ชันแรกรับอินพุตเพื่อแยกลูกค้ากับหนักงาน
    char menu;
    cout << "\n\n\n\n\n\n                               Hotel Management System "; 
    cout << "\n---------------------------------------------------------------------------------------";
   
   
  
    cout << "\n[1] Guest \n[2] Receptionist ";
    cout << "\n\nPlease select the menu : ";
    cin >> menu;
    
    if(menu=='1') return 1;
    else if(menu=='2') return 0;
}
int guestpart(){ //ฟังก์ชันต่อจาก checkuser เป็นพาร์ทของลูกค้า
    char menu;
    cout << "\n\n\t\t\t  +--------------------------------------+";
    cout << "  \n\t\t\t  |        Welcome to ..... hotel        |";
    cout << "  \n\t\t\t  +--------------------------------------+";
    
 
    cout << "\n[1] Manage your booking\n[2] Make a booking\n "; //ให้เลือกระหว่างเช็คสถานะการจอง,ห้อง กับ จองห้อง
    cout << "\nPlease select the menu : "; 
    cin >> menu;
    cout << "\n---------------------------------------------------------------------------------------";

    if(menu=='1'){ return 1;
    }else if(menu=='2'){ return 0;}
    }

int receplogin(){ //ฟังก์ชันต่อจาก checkuser เป็นพาร์ทของพนักงาน
    string username,password;
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nusername : ";
    cin >> username;
    cout << "password : ";
    cin >> password;
    if(username=="admin"&&password=="admin"){ //set username,password = admin
    cout << "\n---------------------------------------------------------------------------------------";
        return 1;
    }else{
    cout << "\n---------------------------------------------------------------------------------------";
        return 0;
    }
}

void booking(roomtype &room,guestinfo &info,vector<guestinfo> &roomstatus){ //ฟังก์ชันการจอง
    int date[2],month[2],year,slroom[10],phonenumber,roomNO,totalprice=0,bookingNum,Numofday=0;
    string name,email,checkin,checkout;
    char type,confirm;

    cout << "\n\n\t\t\t+--------------------------------------+";
    cout << "\n  \t\t\t|         Booking your rooms           |";
    cout << "\n  \t\t\t+--------------------------------------+";
    do{
        cout << "\nPlease in put a check-in  date (dd/mm/yyyy) : "; //รับวันเช็คอิน
        cin >> checkin;
        sscanf(checkin.c_str(),"%d/%d/%d",&date[0],&month[0],&year);
        cout << "Please in put a check-out date (dd/mm/yyyy) : "; //รับวันเช็คเอาท์
        cin >> checkout;
        sscanf(checkout.c_str(),"%d/%d/%d",&date[1],&month[1],&year);
    cout << "\n---------------------------------------------------------------------------------------";
    }while(date[1]<date[0]&&month[1]<=month[0]);
    //อัปเดตการคิดจำนวนวัน
    switch(month[0]){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            Numofday = ((month[1]-month[0])*31)-date[0]+date[1];
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            Numofday = ((month[1]-month[0])*30)-date[0]+date[1];
            break;
        case 2:
            if(year%4==0){
                Numofday = ((month[1]-month[0])*29)-date[0]+date[1];
                break;
            } else{
                Numofday = ((month[1]-month[0])*28)-date[0]+date[1];
                break;
            }
    }
    cout << "\nNumber of room : "; //เช็คจำนวนห้องที่จะจอง
    cin >> roomNO;
    for(int i=0;i<roomNO;i++) {
    cout << "\n---------------------------------------------------------------------------------------";
        
        cout << "\n[1] Standard  price : 1000 Baht";
        cout << "\n[2] Twin bed  price : 1500 Baht";       
        cout << "\n[3] Deluxe    price : 2000 Baht"; //เลือกชนิดของห้อง 3 ชนิด
        cout << "\nPlease choose a room type : ";
        cin >> type;
    cout << "\n---------------------------------------------------------------------------------------";
        cout << "\nAvailable room : ";
        //เงื่อนไขในการเช็คห้องว่าง
        if (type == '1') {
            for (int k = 0; k < 24; k++) {
                if (((room.roomnumber[k] % 1000) / 100) == 1 && room.status[k] != 'U') {
                    cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดstandardที่ว่างอยู่ทั้งหมด
                }
            }
        } else if (type == '2') {
            for (int k = 0; k < 24; k++) {
                if (((room.roomnumber[k] % 1000) / 100) == 2 && room.status[k] != 'U') {
                    cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดtwinbedที่ว่างอยู่ทั้งหมด
                }
            }
        } else {
            for (int k = 0; k < 24; k++) {
                if (((room.roomnumber[k] % 1000) / 100) == 3 && room.status[k] != 'U') {
                    cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดdeluxeที่ว่างอยู่ทั้งหมด
                }
            }
        }
        cout << "\nPlease select a room : "; //เลือกห้องที่จะจอง
        cin >> slroom[i];
        for(int j=0;j<i;j++){ //แก้errorแล้วจ้า
            if (slroom[i - (j+1)] == slroom[i] && i != 0) { //ถ้าเลือกห้องซ้ำให้เปลี่ยนเลขห้องใหม่
                cout << "Please select again : ";
                cin >> slroom[i];
            }
        }
    }
    //คอนเฟิร์มห้อง
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\n                  Booking information";
    cout << "\n---------------------------------------------------------------------------------------";
    //แสดงสถานะห้องที่เลือก
    for(int i=0;i<roomNO;i++){
        cout << "\nRoom " << i+1 << " Information";
    cout << "\n---------------------------------------------------------------------------------------";
        if((slroom[i]%1000)/100==1){
            cout << "\nRoom type : " << room.type[0];
            cout << "\nRoom number : " << slroom[i];
            cout << "\nRoom price : " << room.price[0] << " Baht";
            totalprice+=room.price[0];
        } else if((slroom[i]%1000)/100==2){
            cout << "\nRoom type : " << room.type[1];
            cout << "\nRoom number : " << slroom[i];
            cout << "\nRoom price : " << room.price[1] << " Baht";
            totalprice+=room.price[1];
        } else{
            cout << "\nRoom type : " << room.type[2];
            cout << "\nRoom number : " << slroom[i];
            cout << "\nRoom price : " << room.price[2] << " Baht";
            totalprice+=room.price[2];
        }
    cout << "\n---------------------------------------------------------------------------------------";
    }
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
	int C = rand()%10;
	    cout << "\n\n\t\t\t\t+----------------------------+";
    cout << "\n  \t\t\t\t|     Random Lucky Number    |";
    cout << "\n  \t\t\t\t|             "<<C<<"              |";
    cout << "\n  \t\t\t\t+----------------------------+";
	if(C==3){
		totalprice=totalprice*85/100;	

     
    cout << "\n\n\t\t\t+----------------------------+";
    cout << "\n  \t\t\t|        Super Lucky         |";
    cout << "\n  \t\t\t|       discount  15%        |";
    cout << "\n  \t\t\t+----------------------------+";

			
	}
	else if(C==5){
		totalprice=totalprice*70/100;
       
            cout << "\n\n\t\t\t\t+----------------------------+";
            cout << "\n  \t\t\t\t|         More Lucky         |";
            cout << "\n  \t\t\t\t|        discount  30%       |";
            cout << "\n  \t\t\t\t+----------------------------+";
		
	}
	else if(C==7){
		
		totalprice=totalprice-250;
            cout << "\n\n\t\t\t\t+----------------------------+";
            cout << "\n  \t\t\t\t|            Lucky           |";
            cout << "\n  \t\t\t\t|       discount 250 Baht    |";
            cout << "\n  \t\t\t\t+----------------------------+";
		
	}
	else if(C==9){
		
		totalprice=totalprice-50;
            cout << "\n\n\t\t\t\t+----------------------------+";
            cout << "\n  \t\t\t\t|        Some Lucky          |";
            cout << "\n  \t\t\t\t|     discount 50 Baht       |";
            cout << "\n  \t\t\t\t+----------------------------+";
			}
	else{
		 totalprice=totalprice;
        
            cout << "\n\n\t\t\t\t+----------------------------+";
            cout << "\n  \t\t\t\t|          Unlucky           |";
            cout << "\n  \t\t\t\t+----------------------------+";
       
	}
    cout << "\n---------------------------------------------------------------------------------------";

    totalprice=totalprice*Numofday; //รวมค่าใช้จ่าย
    cin.ignore();
    cout << "\nTotal : " << totalprice << " Baht";
    //รับข้อมูลลูกค้า
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\n                                 Guest information";
    cout << "\n---------------------------------------------------------------------------------------";
    cout <<"\nName : ";
    getline(cin,name);
    cout <<  "Email: ";
    cin >> email;
    cout <<  "Tel  : ";
    cin >> phonenumber;
    //คอนเฟิร์มการจอง
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nConfirm booking information";
    cout << "\n    YES[Y] or NO[N] : ";
    cin >> confirm;
    confirm=toupper(confirm);
    if(confirm=='Y'){
        bookingNum=rand()%89999+10000;
        for(int j=0;j<roomNO;j++){
            for(int i=0;i<24;i++){ //เงื่อนไขเปลี่ยนสถานะของห้องที่ถูกจองให้เป็น U (unavialable)
                if(room.roomnumber[i]==slroom[j]){
                    info.name[i]=name;
                    info.email[i]=email;
                    info.phonenumber[i]=phonenumber;
                    info.checkindate[i]=checkin;
                    info.checkoutdate[i]=checkout;
                    room.status[i]='U';
                    room.bookingNO[i]=bookingNum;
                    info.roomdata=&room;
                    roomstatus.push_back(info); // พุชข้อมูลลูกค้าเข้า vector
                }
            }
        }
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nChecking room status by using this booking number.";
    cout << "\n\n\t\t\t\t+----------------------------+";
    cout << "\n  \t\t\t\t|       Booking Number       |";
    cout << "\n  \t\t\t\t|            "<<bookingNum<<"           |";
    cout << "\n  \t\t\t\t+----------------------------+";
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\n                           Thank you for choosing our hotel.";
    cout << "\n                            *** Have a nice vacation ***";
    cout << "\n---------------------------------------------------------------------------------------";

    }else{
    cout << "\n---------------------------------------------------------------------------------------";
        cout <<                           "*** Booking was canceled ***";
    cout << "\n---------------------------------------------------------------------------------------";
    }
}

void searchforRecep(const guestinfo info, const roomtype room){//ฟังก์ชันการค้นหาของพนักงาน
    char cmd;
    string name,checkin;
    int roomNO;
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\n      Manage a room";
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\n[N] Searching by name";
    cout << "\n[R] room number";
    cout << "\n[C] check-in date";
    cout << "\nPlease select and option : ";
    cin >> cmd;
    cmd=toupper(cmd);
    cout << "\n---------------------------------------------------------------------------------------";
    if(cmd=='N'){
        cout << "\nPlease input a name : ";
        getline(cin,name);
        cout << "\n---------------------------------------------------------------------------------------";
        for(int i=0;i<24;i++){
            if(name==info.name[i]){
                Showinfo(info,room,i);
            }
        }
    }else if(cmd=='R'){
        cout << "\nPlease input a room number : ";
        cin >> roomNO;
        cout << "\n---------------------------------------------------------------------------------------";
        for(int i=0;i<24;i++){
            if(roomNO==info.roomdata->roomnumber[i]){
                Showinfo(info,room,i);
            }
        }
    }else {
        cout << "\nPlease input a check-in date : ";
        cin >> checkin;
        cout << "\n---------------------------------------------------------------------------------------";
        for(int i=0;i<24;i++){
            if(checkin==info.checkindate[i]){
                Showinfo(info,room,i);
            }
        }               
    }

}

void searchforGuest(const guestinfo info, const roomtype room){ //ฟังก์ชันการค้นหาของลูกค้า
    int bookingNO;
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nManage a room";
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nSearching by booking number";
    cout << "\nPlease input your booking number : ";
    cin >> bookingNO;
    cout << "\n---------------------------------------------------------------------------------------";
    for(int i=0;i<24;i++){
        if(bookingNO==info.roomdata->bookingNO[i]){
            Showinfo(info,room,i);
        }
    }

}

void check_Aroom(const roomtype room)//ฟังก์ชันเช็คห้องว่าง
{
    char checkA,checkAt;
    int checkAf;
    cout << "\nCheck available room";
    cout << "\nRoom type[T] or Floor[F] : ";//ให้เลือกว่าจะหาจากอะไร มีประเภทห้อง กับ ชั้น
    cin >> checkA;
    checkA=toupper(checkA);

    if(checkA != 'T' && checkA != 'F')//ใส่ค่าไม่ถูกต้อง
    {
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\n[S] Standard\n[T] Twin bed \n[D]  Deluxe";
        cout << "\nPlease input again!! : ";
        cin >> checkAt;
        checkAt=toupper(checkAt);
    }

    if(checkA == 'T')//หาจากประเภทห้อง
    {
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\n[S] Standard\n[T] Twin bed \n[D]  Deluxe";
        cout << "\nPlease input again!! : ";
        cin >> checkAt;
        checkAt=toupper(checkAt);
    cout << "\n---------------------------------------------------------------------------------------";
        cout << "\nAvailable room : ";
        if (checkAt == 'S') {
            for (int k = 0; k < 24; k++) {
                if (((room.roomnumber[k] % 1000) / 100) == 1 && room.status[k] != 'U') {
                    cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดstandardที่ว่างอยู่ทั้งหมด
                }
            }
        } else if (checkAt == 'T') {
            for (int k = 0; k < 24; k++) {
                if (((room.roomnumber[k] % 1000) / 100) == 2 && room.status[k] != 'U') {
                    cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดtwinbedที่ว่างอยู่ทั้งหมด
                }
            }
        } else {
            for (int k = 0; k < 24; k++) {
                if (((room.roomnumber[k] % 1000) / 100) == 3 && room.status[k] != 'U') {
                    cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดdeluxeที่ว่างอยู่ทั้งหมด
                }
            }
        }
    cout << "\n---------------------------------------------------------------------------------------";

    }

    if(checkA == 'F')//หาจากชั้น
    {
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\nPlease select floor 1 2 3 4 : ";
        cin >> checkAf;

        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\nAvailable room : ";
        for(int i = 0;i < 24;i++)
        {
            if(room.roomnumber[i]/1000 == checkAf)
            cout << room.roomnumber[i] << " ";
        }
        cout << "\n---------------------------------------------------------------------------------------";
    }

    
}

void check_checkin(const roomtype room,const guestinfo info)//เช็คหาวันที่เข้าพักจากเลขห้อง
{
    int num_check;
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nPlease select room : ";
    cin >> num_check;
    for(int i =0;i < 24;i++)
    {
        if(room.roomnumber[i] == num_check)
        {
            cout << "Checkin : " << info.checkindate[i];
            cout << "\nCheckout : " << info.checkoutdate[i];
        }
    }
    cout << "\n---------------------------------------------------------------------------------------";

}

void recepFunc(const roomtype room,const guestinfo info)
{
    char menuR;
    cout << "\nWelcome!";            
    cout << "\nWhat do you want to check?";
    cout << "\n[A] Check available room";
    cout << "\n[D] Check checkin and checkout date";
    cout << "\n[S] Search information";
     cout << "\nPlease select : ";
    cin >> menuR;
    cout << "\n---------------------------------------------------------------------------------------";
    menuR=toupper(menuR);
    
    while(menuR != 'A' && menuR != 'D' && menuR != 'R')
    {
        cout << "Please input again : ";
        cin >> menuR;
    }
    if(menuR == 'A')
    check_Aroom(room);

    if(menuR == 'D')
    check_checkin(room,info);
                
    if(menuR == 'R')
    searchforRecep(info,room);

    }