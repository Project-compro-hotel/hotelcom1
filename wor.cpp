#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
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

int checkuser(){ //ฟังก์ชันแรกรับอินพุตเพื่อแยกลูกค้ากับหนักงาน
    char menu;
    cout << "Welcome to ..... hotel";
    cout << "\nPlease select the menu";
    cout << "\n---------------------------------";
    cout << "\nGuest[G] or Receptionist[R] : ";
    cin >> menu;
    if(menu=='G') return 1;
    else return 0;
}
int guestpart(){ //ฟังก์ชันต่อจาก checkuser เป็นพาร์ทของลูกค้า
    char menu;
    cout << "---------------------------------";
    cout << "\nWelcome to ..... hotel";
    cout << "\nPlease select the menu";
    cout << "\n---------------------------------";
    cout << "\nManage your booking[M] or Make a booking[B] : "; //ให้เลือกระหว่างเช็คสถานะการจอง,ห้อง กับ จองห้อง
    cin >> menu;
    if(menu=='M') return 1;
    else return 0;
}

int receplogin(){ //ฟังก์ชันต่อจาก checkuser เป็นพาร์ทของพนักงาน
    string username,password;
    cout << "---------------------------------";
    cout << "\nusername : ";
    cin >> username;
    cout << "password : ";
    cin >> password;
    if(username=="admin"&&password=="admin"){ //set username,password = admin
        cout << "---------------------------------";
        return 1;
    }else{
        cout << "---------------------------------";
        return 0;
    }
}

void booking(roomtype &room,guestinfo &info,vector<guestinfo> &roomstatus){ //ฟังก์ชันการจอง
    int date[2],month[2],year,slroom[10],phonenumber,roomNO,totalprice=0,bookingNum,Numofday=0;
    string name,email,checkin,checkout;
    char type,confirm;
    cout << "---------------------------------";
    cout << "\nBooking your rooms";
    cout << "\n---------------------------------";
    do{
        cout << "\nPlease in put a check-in  date (dd/mm/yyyy) : "; //รับวันเช็คอิน
        cin >> checkin;
        sscanf(checkin.c_str(),"%d/%d/%d",&date[0],&month[0],&year);
        cout << "Please in put a check-out date (dd/mm/yyyy) : "; //รับวันเช็คเอาท์
        cin >> checkout;
        sscanf(checkout.c_str(),"%d/%d/%d",&date[1],&month[1],&year);
        cout << "---------------------------------";
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
            Numofday = ((month[1]-month[0])*31)-date[0]+date[1]+1;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            Numofday = ((month[1]-month[0])*30)-date[0]+date[1]+1;
            break;
        case 2:
            if(year%4==0){
                Numofday = ((month[1]-month[0])*29)-date[0]+date[1]+1;
                break;
            } else{
                Numofday = ((month[1]-month[0])*28)-date[0]+date[1]+1;
                break;
            }
    }
    cout << "\nNumber of room : "; //เช็คจำนวนห้องที่จะจอง
    cin >> roomNO;
    for(int i=0;i<roomNO;i++) {
        cout << "---------------------------------";
        cout << "\nPlease choose a room type";
        cout << "\nStandard[S] , Twin bed[T] , Deluxe[D] : "; //เลือกชนิดของห้อง 3 ชนิด
        cin >> type;
        cout << "---------------------------------";
        cout << "\nAvailable room : ";
        //เงื่อนไขในการเช็คห้องว่าง
        if (type == 'S') {
            for (int k = 0; k < 24; k++) {
                if (((room.roomnumber[k] % 1000) / 100) == 1 && room.status[k] != 'U') {
                    cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดstandardที่ว่างอยู่ทั้งหมด
                }
            }
        } else if (type == 'T') {
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
    cout << "---------------------------------";
    cout << "\nBooking information";
    cout << "\n---------------------------------";
    //แสดงสถานะห้องที่เลือก
    for(int i=0;i<roomNO;i++){
        cout << "\nRoom " << i+1 << " Information";
        cout << "\n---------------------------------";
        if((slroom[i]%1000)/100==1){
            cout << "\nRoom type : " << room.type[0];
            cout << "\nRoom number : " << slroom[i];
            cout << "\nRoom price : " << room.price[0] << " ฿.";
            totalprice+=room.price[0];
        } else if((slroom[i]%1000)/100==2){
            cout << "\nRoom type : " << room.type[1];
            cout << "\nRoom number : " << slroom[i];
            cout << "\nRoom price : " << room.price[1] << " ฿.";
            totalprice+=room.price[1];
        } else{
            cout << "\nRoom type : " << room.type[2];
            cout << "\nRoom number : " << slroom[i];
            cout << "\nRoom price : " << room.price[2] << " ฿.";
            totalprice+=room.price[2];
        }
        cout << "\n---------------------------------";
    }
    totalprice=totalprice*Numofday; //รวมค่าใช้จ่าย
    cin.ignore();
    cout << "\nTotal : " << totalprice << " ฿.";
    //รับข้อมูลลูกค้า
    cout << "\n---------------------------------";
    cout << "\nGuest information";
    cout << "\n---------------------------------";
    cout << "\nName : ";
    getline(cin,name);
    cout << "Email : ";
    cin >> email;
    cout << "Tel : ";
    cin >> phonenumber;
    //คอนเฟิร์มการจอง
    cout << "---------------------------------";
    cout << "\nConfirm booking information";
    cout << "\nYES[Y] or NO[N] : ";
    cin >> confirm;
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
        //สร้าง booking number ไว้ดูสถานะห้องสำหรับลูกค้า
        cout << "---------------------------------";
        cout << "\nChecking room status by using this booking number.";
        cout << "\nBooking Number : " << bookingNum;
        cout << "\n---------------------------------";
        cout << "\nThank you for choosing our hotel.";
        cout << "\n*** Have a nice vacation ***";
        cout << "\n---------------------------------";

    }else{
        cout << "---------------------------------";
        cout << "*** Booking was canceled ***";
        cout << "\n---------------------------------";
    }
}

int main() {
    srand(time(0));
    roomtype room;
    guestinfo info;
    vector<guestinfo> roomstatus;
    //เพิ่มตั้งค่าห้องของอิ๋ว
    //ตัวเริ่มโปรแกรม
    for(int i=1;i<10;i++){
        if(checkuser()==1){ //ถ้าcheckuser == 1 จะเข้าสู่เมนูของลูกค้า
            if(guestpart()==1){
                //เพิ่มฟังก์ชันหาของอัพ
            }else{
                booking(room,info,roomstatus);
            }
        }else{ //checkuser==0 จะเข้าสู่เมนูของพนักงาน
            for(int i=0;i<4;i++){ //ลูปให้ใส่ username,password ได้ไม่เกิน 3 ครั้ง
                if(receplogin()==1){
                    cout << "Welcome!";
                    //เพิ่มฟังก์ชันหาของอัพ
                    break;
                }
                else{
                    if(i==3){
                        cout << "\nAccess deny!"; //ถ้าใส่ username,password ผิดเกิน3ครั้งจะจบโปรแกรม
                        break;
                    }else{
                        cout << "\nInvalid username or password";
                        cout << "\nYou have " << 3-i << " chance to login\n";
                    }
                }
            }
        }
    }


}
