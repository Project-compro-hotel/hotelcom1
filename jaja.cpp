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

void check_Aroom(const roomtype room)//ฟังก์ชันเช็คห้องว่าง
{
    char checkA,checkAt;
    int checkAf;
    cout << "\nCheck available room";
    cout << "\nRoom type[T] or Floor[F] : ";//ให้เลือกว่าจะหาจากอะไร มีประเภทห้อง กับ ชั้น
    cin >> checkA;

    if(checkA != 'T' && checkA != 'F')//ใส่ค่าไม่ถูกต้อง
    {
        cout << "\n---------------------------------";
        cout << "\nPlease input again!!";
        cout << "\nStandard[S] , Twin bed[T] , Deluxe[D] : ";
        cin >> checkAt;
    }

    if(checkA == 'T')//หาจากประเภทห้อง
    {
        cout << "\n---------------------------------";
        cout << "\nPlease select room type ";
        cout << "\nStandard[S] , Twin bed[T] , Deluxe[D] : ";
        cin >> checkAt;

        cout << "\n---------------------------------";
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
        cout << "\n---------------------------------";

    }

    if(checkA == 'F')//หาจากชั้น
    {
        cout << "\n---------------------------------";
        cout << "\nPlease select floor 1 2 3 4 : ";
        cin >> checkAf;

        cout << "\n---------------------------------";
        cout << "\nAvailable room : ";
        for(int i = 0;i < 24;i++)
        {
            if(room.roomnumber[i]/1000 == checkAf)
            cout << room.roomnumber[i] << " ";
        }
        cout << "\n---------------------------------";
    }

    
}

void check_checkin(const roomtype room,const guestinfo guest)//เช็คหาวันที่เข้าพักจากเลขห้อง
{
    int num_check;
    cout << "\n---------------------------------";   
    cout << "\nPlease select room : ";
    cin >> num_check;
    for(int i =0;i < 24;i++)
    {
        if(room.roomnumber[i] == num_check)
        {
            cout << "Checkin : " << guest.checkindate[i];
            cout << "\nCheckout : " << guest.checkoutdate[i];
        }
    }
    cout << "\n---------------------------------";   

}

int main()
{
    char menuR;
    roomtype room;
    guestinfo info;
    cout << "\nWelcome!";            
    cout << "\nWhat do you want to check?";
    cout << "\nCheck available room[A] or Check checkin and checkout date[D] or Search information[S] : ";
    cin >> menuR;

    while(menuR != 'A' && menuR != 'D' && menuR != 'R')
    {
        cout << "Please input again : ";
        cin >> menuR;
    }
    if(menuR == 'A')
    check_Aroom(room);
    if(menuR == 'D')
    check_checkin(room,info);

    return 0;
}

