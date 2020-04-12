#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;

int income = 0;
vector<string> unaviroom;
vector<string> guestdata;

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
   
    int checkAf,roomnum[100],date,month,year,dateU[2],monthU[2],yearU[2];
    string checkin,data[100][10];
    bool Aroom = true ;

    for(int i=0;i<guestdata.size();i++){
        int start=0,para=0;
        int end=guestdata[i].find_first_of(",");
        while(end!=-1){
            data[i][para]=guestdata[i].substr(start,end-start);
            start=end+1;
            end=guestdata[i].find_first_of(",",start);
            para++;
        }
        data[i][para]=guestdata[i].substr(start,guestdata[i].size()-start);
        /*ข้อมูลถูกเก็บไว้ดังนี้
         data[ลำดับของลูกค้า][]
         data[][0] = ชื่อลูกค้า
         data[][1] = อีเมล
         data[][2] = หมายเลขโทรศัพท์
         data[][3] = วันเช็คอิน
         data[][4] = วันเช็คเอาท์
         data[][5] = หมายเลขการจอง
         data[][6] = ห้องที่จอง
         data[][7] = ชนิดของห้อง
         data[][8] = จำนวนเงินทั้งหมดที่จ่าย
         */
    }
   
    cout << "\n\n\t\t\t+--------------------------------------+";
    cout <<   "\n\t\t\t|         Check available room         |";
    cout <<   "\n\t\t\t+--------------------------------------+";

    cout << "\nPlease input month snd yearr you would like to check (mm/yyyy): ";
    cin >> checkin;
    sscanf(checkin.c_str(), "%d/%d", &month, &year);

    cout <<  "\n\t\t\t             [1] Room type";
    cout <<  "\n\t\t\t             [2] Floor";
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nPlease select : ";
    cin >> checkA;
    cout << "---------------------------------------------------------------------------------------";


    while(checkA != '1' && checkA != '2' )//ใส่ค่าไม่ถูกต้อง
    {
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\nPlease select again!! : ";
        cin >> checkA;
    }
 
     if(checkA == '1')//หาจากประเภทห้อง
    {
    
    cout <<"\n\n\t\t\t+--------------------------------------+";
    cout <<  "\n\t\t\t|           Check Room Type            |";
    cout <<  "\n\t\t\t+--------------------------------------+";
    cout <<  "\n\t\t\t             [1] Standard";
    cout <<  "\n\t\t\t             [2] Twin bed ";
    cout <<  "\n\t\t\t             [3] Deluxe ";
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nPlease select : ";
        cin >> checkAt;
        cout << "---------------------------------------------------------------------------------------";

        while(checkAt != '1' && checkAt != '2' && checkAt != '3')//ใส่ค่าไม่ถูกต้อง
    {
        cout << "\nPlease select again!! : ";
        cin >> checkAt;
    }
      
        cout << "\nAvailable  room : ";

        if (checkAt == '1')
        {
            for (int k = 0; k < 24; k++)
            {
                for(int i =0;i < guestdata.size();i++)
                {
                    if (((room.roomnumber[k] % 1000) / 100) == 1 && room.status[k] != 'U' && room.roomnumber[k] == atoi(data[i][6].c_str()))
                    {
                        Aroom = false;
                        if(Aroom == false)
                        {
                            sscanf(data[i][3].c_str(), "%d/%d/%d", &dateU[0], &monthU[0], &yearU[0]); 
                            sscanf(data[i][4].c_str(), "%d/%d/%d", &dateU[1], &monthU[1], &yearU[1]);
                            if(month != monthU[0] || (month != monthU[1] && dateU[1] != 01) || (month == monthU[0] && year != yearU[0]) || (month == monthU[1] && year != yearU[1]))
                            Aroom = true;
                        }
                    }
                }
                if(((room.roomnumber[k] % 1000) / 100) == 1 && Aroom == true )
                {
                    cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดstandardที่ว่างอยู่ทั้งหมด   
                }
                Aroom = true;
            }
                    cout << "\n---------------------------------------------------------------------------------------\n";

        } else if (checkAt == '2') {
            for (int k = 0; k < 24; k++)
            {
                for(int i =0;i < guestdata.size();i++)
                {
                    if (((room.roomnumber[k] % 1000) / 100) == 2 && room.status[k] != 'U' && room.roomnumber[k] == atoi(data[i][6].c_str()))
                    {
                        Aroom = false;
                        if(Aroom == false)
                        {
                            sscanf(data[i][3].c_str(), "%d/%d/%d", &dateU[0], &monthU[0], &yearU[0]); 
                            sscanf(data[i][4].c_str(), "%d/%d/%d", &dateU[1], &monthU[1], &yearU[1]);
                            if(month != monthU[0] || (month != monthU[1] && dateU[1] != 01) || (month == monthU[0] && year != yearU[0]) || (month == monthU[1] && year != yearU[1]))
                            Aroom = true;
                        }
                    } 
                }
                if(((room.roomnumber[k] % 1000) / 100) == 2 && Aroom == true )
                {
                    cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดtwinที่ว่างอยู่ทั้งหมด   
                }
                Aroom = true;
            }
                    cout << "\n---------------------------------------------------------------------------------------\n";

        } else if(checkAt == '3'){
            for (int k = 0; k < 24; k++)
            {
                for(int i =0;i < guestdata.size();i++)
                {
                    if (((room.roomnumber[k] % 1000) / 100) == 3 && room.status[k] != 'U' && room.roomnumber[k] == atoi(data[i][6].c_str()))
                    {
                        Aroom = false;
                        if(Aroom == false)
                        {
                            sscanf(data[i][3].c_str(), "%d/%d/%d", &dateU[0], &monthU[0], &yearU[0]); 
                            sscanf(data[i][4].c_str(), "%d/%d/%d", &dateU[1], &monthU[1], &yearU[1]);
                            if(month != monthU[0] || (month != monthU[1] && dateU[1] != 01) || (month == monthU[0] && year != yearU[0]) || (month == monthU[1] && year != yearU[1]))
                            Aroom = true;
                        }
                    } 
                }
                if(((room.roomnumber[k] % 1000) / 100) == 3 && Aroom == true )
                {
                    cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดdeluxeที่ว่างอยู่ทั้งหมด   
                }
                Aroom = true;
            }
        cout << "\n---------------------------------------------------------------------------------------\n";
    }
    }
    if(checkA == '2')//หาจากชั้น
    {
        cout <<"\n\n\t\t\t+--------------------------------------+";
        cout <<  "\n\t\t\t|         Check Room from Floor        |";
        cout <<  "\n\t\t\t+--------------------------------------+";
        cout <<  "\n\t\t\t              [1] Floor 1";
        cout <<  "\n\t\t\t              [2] Floor 2";
        cout <<  "\n\t\t\t              [3] Floor 3";
        cout <<  "\n\t\t\t              [4] Floor 4";
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\nPlease select : ";
        cin >> checkAf;
        cout << "---------------------------------------------------------------------------------------";
        cout << "\nAvailable room : ";
        
        for (int k = 0; k < 24; k++)
        {
            for(int i =0;i < guestdata.size();i++)
            {
                if (((room.roomnumber[k]/1000)) == checkAf && room.status[k] != 'U' && room.roomnumber[k] == atoi(data[i][6].c_str()))
                {
                    Aroom = false;
                    if(Aroom == false)
                        {
                            sscanf(data[i][3].c_str(), "%d/%d/%d", &dateU[0], &monthU[0], &yearU[0]); 
                            sscanf(data[i][4].c_str(), "%d/%d/%d", &dateU[1], &monthU[1], &yearU[1]);
                            if(month != monthU[0] || (month != monthU[1] && dateU[1] != 01) || (month == monthU[0] && year != yearU[0]) || (month == monthU[1] && year != yearU[1]))
                            Aroom = true;
                        }
                }
            }
            if(((room.roomnumber[k]/1000)) == checkAf && Aroom == true )
            {
                cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดstandardที่ว่างอยู่ทั้งหมด
            }
            Aroom = true;
        }
        cout << "\n---------------------------------------------------------------------------------------\n";
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