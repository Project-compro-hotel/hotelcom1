#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cctype>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

vector<string> unaviroom;
string data[100][10];

struct roomtype{ //structure เก็บตัวแปรทุกอย่างเกี่ยวกับห้อง
    string type[3];
    int roomnumber[24];
    int price[3];
    char status[24];
    bool cleaning[24];
};

struct roomdata{
    string type;
    int roomnumber;
    int price;
};

struct guestinfo{ //structure เก็บตัวแปรทุกอย่างเกี่ยวกับลูกค้า
    string name;
    string email;
    int phonenumber;
    string checkindate;
    string checkoutdate;
    int bookingNO;
    roomdata *reservedroom;
};

void getdata(int &line) {
    string textline;
    line = 0;
    ifstream source;
    source.open("data.txt");
    while (getline(source, textline)) {
        int start = 0, para = 0;
        int end = textline.find_first_of(",");
        while (end != -1) {
            data[line][para] = textline.substr(start, end - start);
            start = end + 1;
            end = textline.find_first_of(",", start);
            para++;
        }
        data[line][para] = textline.substr(start, para - start);
        line++;
    }
    source.close();
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
//#########################################################################################################

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
//#########################################################################################################

void resetroomstatus(roomtype &room){
    for(int i=0;i<24;i++){
        room.status[i]='A';
    }
}
//#########################################################################################################

void setcleaning(roomtype &room)
{
    for(int i=0;i<24;i++)
    {
        room.cleaning[i] = false;
    }
}
//#########################################################################################################

void Showinfo(int loc,const roomtype room){
    int k = 0;
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

    cout<<      "\n+------------------------------------------------------------------------------------------+\n";
    cout<<      "|                                      GUEST INFORMATION                                   |\n";
    cout<<      "+------------------------------------------------------------------------------------------+\n";

    cout<<"|      Room Type       : "<<setw(30) << left  << data[loc][7];

    cout<<"Room Number    : "<<setw(19) << left  << data[loc][6]<<"|";

    cout<<"\n|      Name            : "<<setw(30) << left  << data[loc][0];

    cout<<"Booking Number : "<<setw(19) << left  << data[loc][5]<<"|";

    cout<<"\n|      Email           : "<<setw(30) << left  << data[loc][1];

    cout<<"Tel            : "<<setw(19) << left  << data[loc][2]<<"|";

    cout<<"\n|      Check in        : "<<setw(30) << left  << data[loc][3];

    cout<<"Check out      : "<<setw(19) << left  << data[loc][4]<<"|";

    cout<<     "\n|      Cleaning status : ";
    for(int i =0;i<24;i++)
    {
        if(room.roomnumber[i] == atoi(data[loc][6].c_str()))
        {
            k = i;
        }

    }
    if(room.cleaning[k]==true) cout<< setw(66) << left<<"Cleaned                                                           |\n";
    else{cout<< setw(66) << left<<"Wait to clean                                                     |\n";}
    cout<<"+------------------------------------------------------------------------------------------+\n";
}
//#########################################################################################################

int checkuser(){ //ฟังก์ชันแรกรับอินพุตเพื่อแยกลูกค้ากับหนักงาน
    int menu;
    cout << "\n\n\n";
    cout <<   "###########################################################################################";
    cout << "\n# +-------------------------------------------------------------------------------------+ #";
    cout << "\n# |                                Hotel Management System                              | #";
    cout << "\n# +-------------------------------------------------------------------------------------+ #";
    cout << "\n###########################################################################################\n";
    cout << "  \n\t\t\t              [1] Guest";
    cout << "  \n\t\t\t              [2] Receptionist";
    cout << "  \n\t\t\t              [3] Exit";
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nPlease select the MENU : ";cin >> menu;
    cout << "---------------------------------------------------------------------------------------";
    for(int i=0;i<20;i++)
    { if(menu!=1&&menu!=2&&menu!=3)
        {cout<<"\nPlease select again : "; cin>>menu;
            cout << "---------------------------------------------------------------------------------------";
            continue;}
    }
    return menu;
}
//#########################################################################################################

int guestpart() { //ฟังก์ชันต่อจาก checkuser เป็นพาร์ทของลูกค้า
    char menu;
    cout << "\n\n\t\t\t+--------------------------------------+";
    cout << "  \n\t\t\t|             GUEST MENU               |";
    cout << "  \n\t\t\t+--------------------------------------+";

    cout << "  \n\t\t\t      [1] Manage your booking";
    cout << "  \n\t\t\t      [2] Make a booking";
    cout << "  \n\t\t\t      [3] Back";
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nPlease select : ";
    cin >> menu;
    cout << "---------------------------------------------------------------------------------------";
    if (menu == '1') return 1;
    else if (menu == '2') return 2;
    else if (menu == '3') return 3;
    else {
        for (int i=0; i < 20; i++) {
            cout << "\nPlease select again : ";
            cin >> menu;
            cout << "---------------------------------------------------------------------------------------";
            continue;    
        }
        return 3;
    }
}
//#########################################################################################################

int receplogin(){ //ฟังก์ชันต่อจาก checkuser เป็นพาร์ทของพนักงาน
    string username,password;
    cout << "\n\n\t\t\t+--------------------------------------+";
    cout << "  \n\t\t\t|          Receptionist MENU           |";
    cout << "  \n\t\t\t+--------------------------------------+";
    cout << "\n                             ==> Username : ";
    cin >> username;
    cout <<   "                             ==> Password : ";
    cin >> password;
    if(username=="admin"&&password=="admin"){ //set username,password = admin
        cout << "\n---------------------------------------------------------------------------------------";
        return 1;
    }else{
        cout << "\n---------------------------------------------------------------------------------------";
        return 0;
    }
}
//#########################################################################################################

void update_income()
{
    string textline;
    int line,income = 0;
    ifstream source;
    getdata(line);
    for(int i=0;i<line;i++){
            if(data[i][5]!=data[i-1][5]){
                income = income+atoi(data[i][8].c_str());
            }
    }
    ofstream dest;
    dest.open("income.txt",ios::app);
    dest << to_string(income) <<"\n";
    dest.close();
}

void delete_income(const int loc[100])
{
    string textline;
    int line,income = 0;
    ifstream source;
    source.open("income.txt");
    while (getline(source,textline))
    {
        if(income<atoi(textline.c_str())){
            income = atoi(textline.c_str());
        }
    }
    
    income = income-atoi(data[loc[0]][8].c_str());
    ofstream dest;
    dest.open("income.txt");
    dest << to_string(income) <<"\n";
    dest.close();
}
//#########################################################################################################

void booking(roomtype &room,guestinfo &info,roomdata &reservedroom) { //ฟังก์ชันการจอง
    int date[2], month[2], year[2], slroom[24], roomNO, totalprice = 0, bookingNum, Numofday = 0;
    int rsdate[2], rsmonth[2], rsyear[2], rsroomNO, line;
    string name, email, checkin, checkout, rsroom[24], phonenumber,sltype[24];
    char type, confirm;
    getdata(line);
    resetroomstatus(room);
    cout << "\n\n\t\t\t+--------------------------------------+";
    cout << "\n  \t\t\t|         Booking your rooms           |";
    cout << "\n  \t\t\t+--------------------------------------+";
    do {
        cout << "\nPlease in put your information of Booking...\n";
        cout << "---------------------------------------------------------------------------------------";
        cout << "\n==> check-in  date (dd/mm/yyyy) : "; //รับวันเช็คอิน
        cin >> checkin;
        sscanf(checkin.c_str(), "%d/%d/%d", &date[0], &month[0], &year[0]);
        cout << "==> check-out date (dd/mm/yyyy) : "; //รับวันเช็คเอาท์
        cin >> checkout;
        sscanf(checkout.c_str(), "%d/%d/%d", &date[1], &month[1], &year[1]);
        cout << "---------------------------------------------------------------------------------------";
        if (year[0] == year[1]) {
            if ((date[0] < date[1] && month[1] == month[0] ) || ( month[1] > month[0])) break;
        } else if (year[0] < year[1]) {
            break;
        }
    } while (1);
    //อัปเดตการคิดจำนวนวัน
    //debug การคิดจำนวนวัน
    int para = 0, nom = 0;
    if (year[0] == year[1]) {
        nom = month[1] - month[0];
        para = month[1] - 1;
    } else {
        nom = 12 - month[0] + month[1];
        para = (12 * (year[1] - year[0])) - month[0] + month[1] - 1;
    }
    if (nom == 0) {
        Numofday = Numofday + date[1] - date[0];
    } else {
        while (nom != 0) {
            switch (para) {
                case 0:
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    if (nom == 1) {
                        Numofday = Numofday + 31 - date[0] + date[1];
                        break;
                    } else {
                        Numofday += 31;
                        break;
                    }

                case 4:
                case 6:
                case 9:
                case 11:
                    if (nom == 1) {
                        Numofday = Numofday + 30 - date[0] + date[1];
                        break;
                    } else {
                        Numofday += 30;
                        break;
                    }

                case 2:
                    if (year[0] % 4 == 0 || year[1] % 4 == 0) {
                        if (nom == 1) {
                            Numofday = Numofday + 29 - date[0] + date[1];
                            break;
                        } else {
                            Numofday += 29;
                            break;
                        }
                    } else {
                        if (nom == 1) {
                            Numofday = Numofday + 28 - date[0] + date[1];
                            break;
                        } else {
                            Numofday += 28;
                            break;
                        }
                    }
            }
            nom--;
            para--;
        }
    }

    cout << "\n                              ==> Number of room : "; //เช็คจำนวนห้องที่จะจอง
    cin >> roomNO;
    for (int s = 0; s < line; s++) {
        int temp = 0;
        sscanf(data[s][3].c_str(), "%d/%d/%d", &rsdate[0], &rsmonth[0], &rsyear[0]);
        sscanf(data[s][4].c_str(), "%d/%d/%d", &rsdate[1],&rsmonth[1], &rsyear[1]);
        sscanf(data[s][6].c_str(), "%d", &rsroomNO);
        for (int a = 0; a < 24; a++) {
            if (rsroomNO == room.roomnumber[a]) temp = a;
        }
        if (rsyear[0] != rsyear[1] && rsmonth[0] == rsmonth[1]) { //เช็คปีไม่เท่าแต่เดือนเท่า
            if (rsyear[0] <= year[0] && year[0] < rsyear[1]) { // ถ้าปีที่เช็คอินอยู่ระหว่างปีเดียวกันของข้อมูล
                if (rsmonth[0] < month[0] && month[0] < rsmonth[1]) { //ถ้าเดือนที่เช็คอินไม่ใช่เดือนเดียวกันกับข้อมูล -> อยู่ระหว่างเดือนที่ถูกจองไปแล้ว
                    room.status[temp] = 'U';
                } else if (rsmonth[0] == month[0] && month[0] == rsmonth[1]) { //ถ้าเดือนที่เช็คอินเป็นเดือนเดียวกันกับข้อมูล
                    if (rsdate[0] <= date[0] || date[0] < rsdate[1]) { //เช็ควันที่ต่อ ถ้าวันที่อยู่ในช่วงเดียวกันกับข้อมูล
                        room.status[temp] = 'U';
                    }
                }
            } else if (rsyear[0] < year[1] && year[1] <= rsyear[1]) {  // ถ้าปีที่เช็คเอาท์อยู่ระหว่างปีเดียวกันของข้อมูล
                if (rsmonth[0] < month[1] && month[1] < rsmonth[1]) { //ถ้าเดือนที่เช็คเอาท์ไม่ใช่เดือนเดียวกันกับข้อมูล -> อยู่ระหว่างเดือนที่ถูกจองไปแล้ว
                    room.status[temp] = 'U';
                } else if (rsmonth[0] == month[1] &&
                           month[1] == rsmonth[1]) { //ถ้าเดือนที่เช็คเอาท์เป็นเดือนเดียวกันกับข้อมูล
                    if (rsdate[0] < date[1] ||
                        date[1] <= rsdate[1]) { //เช็ควันที่ต่อ ถ้าวันที่อยู่ในช่วงเดียวกันกับข้อมูล
                        room.status[temp] = 'U';
                    }
                }
            }
        } else { //กรณีอื่นๆ
            if(year[0]==year[1]&&rsyear[0]==rsyear[1]&&year[0]==rsyear[1]){//กรณีปีเท่ากันทั้งหมด
                if (month[0] == month[1] && rsmonth[0] == rsmonth[1] && month[0] == rsmonth[0] ) { // ถ้าเดือนเดียวกันทั้งหมด
                    if ((rsdate[0] <= date[0] && date[0] < rsdate[1]) || (rsdate[0] < date[1] && date[1] <= rsdate[1])) { //กรณีวันที่เช็คอินหรือเช็คเอาท์อยู่ระหว่างข้อมูล
                        room.status[temp] = 'U';
                    } else if (date[0] < rsdate[0] && date[1] > rsdate[1]) { //กรณีวันที่เช็คอินและเช็คเอาท์อยู่ครอบข้อมูล
                        room.status[temp] = 'U';
                    }
                }
            }else{
                if (month[0] < month[1] && rsmonth[0] < rsmonth[1] && rsmonth[0] <= month[0] &&month[0] <= rsmonth[1]) { //กรณีเดือนไม่เท่า รวมถึงปีไม่เท่าด้วยเพราะถ้าเปลี่ยนปี=เปลี่ยนเดือน
                    if (date[0] >= rsdate[0] || date[0] < rsdate[1]) { //กรณีวันที่เช็คอินอยู่ระหว่างข้อมูล
                        room.status[temp] = 'U';
                    } else if (date[1] > rsdate[1] || date[1] <= rsdate[1]) { //กรณีวันที่เช็คเอาท์อยู่ระหว่างข้อมูล
                        room.status[temp] = 'U';
                    } else if (date[0] < rsdate[0] &&date[1] > rsdate[1]) { //กรณีที่วันที่เช็คอินและเช็คเอาท์อยู่ครอบข้อมูล
                        room.status[temp] = 'U';
                    }
                }
            }

        }
    }
    int M = 0;
    for (int i = 0; i < 24; i++) {
        if (room.status[i] != 'U') {
            M++;
        }
    }
    if (M >= 12) {
        room.price[0] = 1000;
        room.price[1] = 1500;
        room.price[2] = 2000;
    } else if (M >= 6) {
        room.price[0] = 1200;
        room.price[1] = 1700;
        room.price[2] = 2200;
    } else if (M >= 3) {
        room.price[0] = 1400;
        room.price[1] = 1900;
        room.price[2] = 2400;
    }
    else{
        room.price[0] = 1600;
        room.price[1] = 2100;
        room.price[2] = 2600;
    }
    for (int i = 0; i < roomNO; i++) {
        int para3=0;
        cout << "---------------------------------------------------------------------------------------";
        cout << "\n                                     Room Type         ";
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\n                        [1] Standard  price : " << room.price[0] <<" Baht";
        cout << "\n                        [2] Twin bed  price : " << room.price[1] <<" Baht";
        cout << "\n                        [3] Deluxe    price : " << room.price[2] <<" Baht"; //เลือกชนิดของห้อง 3 ชนิด
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\nPlease select : ";
        cin >> type;
        cout << "---------------------------------------------------------------------------------------";
        //เงื่อนไขในการเช็คห้องว่าง

        while(1){ //debug ไม่ให้แสดงห้องที่ถูกเลือกไปแล้ว
            if (type == '1') {
                cout << "\nAvailable room : ";
                for (int k = 0; k < 24; k++) {
                    if (((room.roomnumber[k] % 1000) / 100) == 1 && room.status[k] != 'U') {
                        int para4=0;
                        for(int j=0;j<=i;j++){
                            if(room.roomnumber[k]==slroom[i-j]){
                                para4++;
                            }
                        }
                        if(para4==0){
                            cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดstandardที่ว่างอยู่ทั้งหมด
                            para3++;
                        }
                    }
                }
                if(para3==0){
                    cout << "Sorry, All standard rooms aren't available" << "\n";
                }
                break;
            } else if (type == '2') {
                cout << "\nAvailable room : ";
                for (int k = 0; k < 24; k++) {
                    if (((room.roomnumber[k] % 1000) / 100) == 2 && room.status[k] != 'U' ) {
                        int para4=0;
                        for(int j=0;j<=i;j++){
                            if(room.roomnumber[k]==slroom[i-j]){
                                para4++;
                            }
                        }
                        if(para4==0){
                            cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดstandardที่ว่างอยู่ทั้งหมด
                            para3++;
                        }
                    }
                }
                if(para3==0){
                    cout << "Sorry, All twin bed rooms aren't available" << "\n";
                }
                break;
            } else if (type == '3') {
                cout << "\nAvailable room : ";
                for (int k = 0; k < 24; k++) {
                    if (((room.roomnumber[k] % 1000) / 100) == 3 && room.status[k] != 'U') {
                        int para4=0;
                        for(int j=0;j<=i;j++){
                            if(room.roomnumber[k]==slroom[i-j]){
                                para4++;
                            }
                        }
                        if(para4==0){
                            cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดstandardที่ว่างอยู่ทั้งหมด
                            para3++;
                        }
                    }
                }
                if(para3==0){
                    cout << "Sorry, All deluxe rooms aren't available" << "\n";
                }
                break;
            }else{ //ถ้าเลือกtypeผิดให้เปลี่ยนใหม่
                cout << "\nPlease select again : ";
                cin >> type;
                cout << "\n---------------------------------------------------------------------------------------";

            }
        }
        if(para3==0){
            i--;
            continue;
        }
        cout << "\nPlease select a room : "; //เลือกห้องที่จะจอง
        cin >> slroom[i];
        for(int j=0;j<=i;j++){ //แก้errorแล้วจ้า
            if(j==i&&j!=0) break;
            if (slroom[i - (j+1)] == slroom[i]) { //ถ้าเลือกห้องซ้ำให้เปลี่ยนเลขห้องใหม่
                cout << "Please select again : ";
                cin >> slroom[i];
            }else{
                for (int s = 0; s < roomNO; s++) {
                    if (type == '1') {
                        if (((slroom[i] % 1000) / 100) != 1) {
                            cout << "Please select again : ";
                            cin >> slroom[i];
                        }else{
                            int temp2=100;
                            for(int k=0;k<24;k++){
                                if(slroom[i]==room.roomnumber[k]) temp2=k;
                            }
                            if(room.status[temp2]=='U'||temp2==100){

                                cout << "Please select again : ";
                                cin >> slroom[i];
                            }
                        }
                    }else if (type == '2') {
                        if (((slroom[i] % 1000) / 100) != 2) {
                            cout << "Please select again : ";
                            cin >> slroom[i];
                        }else{
                            int temp2=100;
                            for(int k=0;k<24;k++){
                                if(slroom[i]==room.roomnumber[k]) temp2=k;
                            }
                            if(room.status[temp2]=='U'||temp2==100){
                                cout << "Please select again : ";
                                cin >> slroom[i];
                            }
                        }
                    }else{
                        if (((slroom[i] % 1000) / 100) != 3) {
                            cout << "Please select again : ";
                            cin >> slroom[i];
                        }else{
                            int temp2=100;
                            for(int k=0;k<24;k++){
                                if(slroom[i]==room.roomnumber[k]) temp2=k;
                            }
                            if(room.status[temp2]=='U'||temp2==100){
                                cout << "Please select again : ";
                                cin >> slroom[i];
                            }
                        }
                    }
                }
            }
        }
        switch (type){
            case '1': sltype[i]="Standard";
                break;
            case '2': sltype[i]="Twin bed";
                break;
            case '3': sltype[i]="Deluxe";
                break;
        }
        rsroom[i]= checkin+"/"+checkout+"/"+to_string(slroom[i]);
    }
    //คอนเฟิร์มห้อง
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\n                                Booking information";
    cout << "\n---------------------------------------------------------------------------------------";
    //แสดงสถานะห้องที่เลือก
    for (int i = 0; i < roomNO; i++) {
        cout << "\n          Room " << i + 1 << " Information";
        cout <<     "\n---------------------------------------------------------------------------------------";
        if ((slroom[i] % 1000) / 100 == 1) {
            cout << "\n                              Room type   : " << room.type[0];
            cout << "\n                              Room number : " << slroom[i];
            cout << "\n                              Room price  : " << room.price[0] << " Baht";
            totalprice += room.price[0];
        } else if ((slroom[i] % 1000) / 100 == 2) {
            cout << "\n                              Room type   : " << room.type[1];
            cout << "\n                              Room number : " << slroom[i];
            cout << "\n                              Room price  : " << room.price[1] << " Baht";
            totalprice += room.price[1];
        } else {
            cout << "\n                              Room type   : " << room.type[2];
            cout << "\n                              Room number : " << slroom[i];
            cout << "\n                              Room price  : " << room.price[2] << " Baht";
            totalprice += room.price[2];
        }
        cout << "\n---------------------------------------------------------------------------------------";
    }
    totalprice = totalprice * Numofday; //รวมค่าใช้จ่าย
    string voucher,vckey="giveusAfordiscount";
    char vcsts;
    cout << "\n\t\t\t\t       Have a voucher ? [Y/N] : " ;
    cin >> vcsts;
    if(vcsts=='y'||vcsts=='Y'){
        cout << "\n\t\t\t\t       Voucher code : " ;
        cin >> voucher;
        if(voucher!=vckey) {
            for(int i=0;i<3;i++){
                if(i==2){
                    cout << "\n\t\t\t       Invalid code. You have "<<3-i<<" chance to try again." ;
                }else{
                    cout << "\n\t\t\t       Invalid code. You have "<<3-i<<" chances to try again." ;
                }
                cout << "\n\t\t\t       Please input a voucher code again : " ;
                cin >> voucher;
                if(voucher==vckey) {
                    break;
                }
            }
        }
        if(voucher==vckey){
            cout << "\n---------------------------------------------------------------------------------------";

            int C = (rand()%4)+1;
            cout << "\n\n\t\t\t\t+----------------------------+";
            cout << "\n  \t\t\t\t|     Random Lucky Number    |";
            cout << "\n  \t\t\t\t|             " << C << "              |";
            cout << "\n  \t\t\t\t+----------------------------+";
            if (C == 1) {
                totalprice = totalprice * 85 / 100;

                cout << "\n\n\t\t\t\t+----------------------------+";
                cout << "\n  \t\t\t\t|   You just got a discount  |";
                cout << "\n  \t\t\t\t|       :  15%  off          |";
                cout << "\n  \t\t\t\t+----------------------------+";

            } else if (C == 2) {
                totalprice = totalprice * 70 / 100;

                cout << "\n\n\t\t\t\t+----------------------------+";
                cout << "\n  \t\t\t\t|   You just got a discount  |";
                cout << "\n  \t\t\t\t|       :  30%  off          |";
                cout << "\n  \t\t\t\t+----------------------------+";

            } else if (C == 3) {

                totalprice = totalprice - 250;
                cout << "\n\n\t\t\t\t+----------------------------+";
                cout << "\n  \t\t\t\t|   You just got a discount  |";
                cout << "\n  \t\t\t\t|       :  250฿  off         |";
                cout << "\n  \t\t\t\t+----------------------------+";

            } else if (C == 4) {

                totalprice = totalprice - 50;
                cout << "\n\n\t\t\t\t+----------------------------+";
                cout << "\n  \t\t\t\t|   You just got a discount  |";
                cout << "\n  \t\t\t\t|       :  50฿  off          |";
                cout << "\n  \t\t\t\t+----------------------------+";
            }

        }

    }

    cout << "\n---------------------------------------------------------------------------------------";

    cin.ignore();
    cout << "\n                         $$$$$$$$$$  Total : " << totalprice << " Baht $$$$$$$$$$$";
    reservedroom.price=totalprice;
    //รับข้อมูลลูกค้า
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\n                                    Guest information";
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\n                             ==> Name  : ";
    getline(cin, name);
    cout <<   "                             ==> Email : ";
    cin >> email;
    cout <<   "                             ==> Tel   : ";
    cin >> phonenumber;
    //คอนเฟิร์มการจอง
    cout << "---------------------------------------------------------------------------------------";
    cout << "\n                               Confirm booking information";
    cout << "\n                                    YES[Y] or NO[N] : ";
    cin >> confirm;
    confirm = toupper(confirm);
    if (confirm == 'Y') {
        string textline;
        bookingNum = rand() % 89999 + 10000;
        for (int i = 0; i < roomNO; i++) {
            info.name = name;
            info.email = email;
            info.checkindate = checkin;
            info.checkoutdate = checkout;
            info.bookingNO = bookingNum;
            info.reservedroom = &reservedroom;
            textline = name+","+email+","+phonenumber+","+checkin+","+checkout+","+to_string(bookingNum)+","+to_string(slroom[i])+","+sltype[i]+","+to_string(totalprice);
            unaviroom.push_back(rsroom[i]);
            ofstream dest("data.txt",ios::app);
            dest  << textline <<"\n";
            dest.close();
            
        }
        update_income();
        cout << "\n----------------------------------------------------------------------------------------";
        cout << "\nChecking room status by using this booking number.";
        cout << "\n\n\t\t\t\t+----------------------------+";
        cout << "\n  \t\t\t\t|       Booking Number       |";
        cout << "\n  \t\t\t\t|            " << bookingNum << "           |";
        cout << "\n  \t\t\t\t+----------------------------+";

        cout << "\n\n\t\t\t+----------------------------------------------+";
        cout << "\n  \t\t\t|       Thank you for choosing our hotel.      |";
        cout << "\n  \t\t\t|         *** Have a nice vacation ***         |";
        cout << "\n  \t\t\t+----------------------------------------------+";
        cout << "\n----------------------------------------------------------------------------------------";

    } else {
        cout << "\n\n\t\t\t+----------------------------------------------+";
        cout << "\n  \t\t\t|         *** Booking is canceled ***         |";
        cout << "\n  \t\t\t+----------------------------------------------+";
        cout << "\n----------------------------------------------------------------------------------------";

    }
}
//#########################################################################################################

void change_Cstatus(roomtype &room)
{
    int rnum;
    while(rnum != 0)
    {
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\n                           input 0 to back to menu";
        cout << "\nPlease input room number has been cleaned : ";
        cin >> rnum;
        for (int i =0;i<24;i++)
        {
            if(rnum == room.roomnumber[i])
            {
                room.cleaning[i] = true;
            }
        }
    }
}
//#########################################################################################################

void delete_booking(const int line,const int loc[100], const int para) {
    string textline,s,nl="\n";
    ifstream source;
    source.open("data.txt");
    for (int i = 0; i < line; i++) {
        int flag=0;
        getline(source,textline);
        for(int j=0;j<para;j++){
            if(i==loc[j]){
                flag++;
            }
        }
        if(flag==0){
            s=s+textline+nl;
        }else{
            s=s;
        }
    }
    source.close();
    ofstream dest;
    dest.open("data.txt");
    dest << s;
    dest.close();
}
//#########################################################################################################

void change_Booking(roomtype &room){
    int bookingNO,para=0,line,loc[100];
    getdata(line);
    cout << "\n\n\t\t\t+--------------------------------------+";
    cout << "  \n\t\t\t|            Delete booking            |";
    cout << "  \n\t\t\t+--------------------------------------+";
    cout << "\n\n---------------------------------------------------------------------------------------";
    cout << "\n Please input booking number : ";
    cin >> bookingNO;
    cout << "---------------------------------------------------------------------------------------";
    for(int i=0;i<line;i++){
        if(bookingNO==atoi(data[i][5].c_str())){
            loc[para]=i;
            for(int j = 0;j<24;j++)
            {
                if(room.roomnumber[j] == atoi(data[i][6].c_str()))
                    room.cleaning[j] = false;
            }
            para++;
        }
    }
    if(para==0){
        cout << "\n\n\t\t\t***Sorry, We can't find this room number.***";
        cout << "\n\n---------------------------------------------------------------------------------------";
    }else{
        delete_booking(line,loc,para);
        cout << "\n\n\t\t\t***Data of booking number : " << bookingNO << " was deleted.***";
        cout << "\n\n---------------------------------------------------------------------------------------";
    }

}
//#########################################################################################################

void searchforRecep(const guestinfo info, const roomtype room) {//ฟังก์ชันการค้นหาของพนักงาน
    char cmd;
    string name, checkin;
    int roomNO;
    int line;
    getdata(line);
    cout << "\n\n\t\t\t+--------------------------------------+";
    cout << "\n  \t\t\t|            Manage a room             |";
    cout << "\n  \t\t\t+--------------------------------------+";
    cout <<   "\n\t\t\t       [1] Searching by name";
    cout <<   "\n\t\t\t       [2] room number";
    cout <<   "\n\t\t\t       [3] check-in date";
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nPlease select and option : ";
    cin >> cmd;
    cout << "---------------------------------------------------------------------------------------";
    if (cmd == '1') {
        cin.ignore();
        cout << "\nPlease input a name : ";
        getline(cin, name);
        cout << "---------------------------------------------------------------------------------------";
        for (int i = 0; i < line; i++) {
            if (name == data[i][0]) {
                Showinfo(i,room);
            }
        }
    } else if (cmd == '2') {
        cout << "\nPlease input a room number : ";
        cin >> roomNO;
        cout << "\n---------------------------------------------------------------------------------------";
        for (int i = 0; i < line; i++) {
            if (roomNO == atoi(data[i][6].c_str())) {
                Showinfo(i,room);
            }
        }
    } else if (cmd == '3'){
        cout << "\nPlease input a check-in date : ";
        cin >> checkin;
        cout << "\n---------------------------------------------------------------------------------------";
        for (int i = 0; i < line; i++) {
            if (checkin == data[i][3]) {
                Showinfo(i,room);
            }
        }
    }

}
//#########################################################################################################

void searchforGuest(const guestinfo info, const roomtype room){ //ฟังก์ชันการค้นหาของลูกค้า
    string bookingNO;
    int line,cmd,para=0,para1=0,loc[100];
    getdata(line);
    cout << "\n\n\t\t\t+--------------------------------------+";
    cout << "\n  \t\t\t|            Manage a room             |";
    cout << "\n  \t\t\t+--------------------------------------+";
    cout << "\nSearching by booking number";
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nPlease input your booking number : ";
    cin >> bookingNO;
    for(int i = 0; i < line; i++){
        if(bookingNO==data[i][5]){
            Showinfo(i,room);
            para1++;
        }
    }
    if(para1==0){
        cout << "---------------------------------------------------------------------------------------";
        cout << "\n\t\t\t              - NOT FOUND THIS BOOKING NUMBER-";
        cout << "\n---------------------------------------------------------------------------------------";
    }else{
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\n\t\t\t\t[1]Cancel your booking    [2] Exit ";
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\n\t\t\t\t\tplease select the menu : ";
        cin >> cmd;
        if(cmd==1){
            char cmd1;
            cout << "\n---------------------------------------------------------------------------------------";
            cout << "\n\t\t\t\tAre you sure to cancel this booking";
            cout << "\n\t\t\t\tYes[Y] or No[N] : ";
            cin >> cmd1;
            cout << "---------------------------------------------------------------------------------------";
            if(cmd1=='Y'||cmd1=='y'){
                for(int i=0;i<line;i++){
                    if(bookingNO==data[i][5]){
                        loc[para]=i;
                        para++;
                    }
                }
                delete_income(loc);
                delete_booking(line,loc,para);
                cout << "\n\n\t\t\t***Your booking is canceled.***";
                cout << "\n\n---------------------------------------------------------------------------------------";
            }

        }else{
            cout << "\n---------------------------------------------------------------------------------------";
            //checkuser();
        }
    }

}
//#########################################################################################################

void check_Aroom(const roomtype room)//ฟังก์ชันเช็คห้องว่าง
{
    char checkA,checkAt;

    int checkAf,roomnum[100],date,month,year,dateU[2],monthU[2],yearU[2];
    string checkin;
    bool Aroom = true ;
    int line;
    getdata(line);
    cout << "\n\n\t\t\t+--------------------------------------+";
    cout <<   "\n\t\t\t|         Check available room         |";
    cout <<   "\n\t\t\t+--------------------------------------+";

    cout << "\nPlease input month and year you would like to check (mm/yyyy): ";
    cin >> checkin;
    sscanf(checkin.c_str(), "%d/%d", &month, &year);
    cout << "\n---------------------------------------------------------------------------------------";

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
                for(int i =0;i < line;i++)
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
                            if((month == monthU[0] && year == yearU[0]) || (month == monthU[1] && year == yearU[1] && dateU[1] != 01))
                                Aroom = false;
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
                for(int i =0;i < line;i++)
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
                            if((month == monthU[0] && year == yearU[0]) || (month == monthU[1] && year == yearU[1] && dateU[1] != 01))
                                Aroom = false;
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
                for(int i =0;i < line;i++)
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
                            if((month == monthU[0] && year == yearU[0]) || (month == monthU[1] && year == yearU[1] && dateU[1] != 01))
                                Aroom = false;
                        }
                    }
                }
                if(((room.roomnumber[k] % 1000) / 100) == 3 && Aroom == true )
                {
                    cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดdeluxeที่ว่างอยู่ทั้งหมด
                }
                Aroom = true;
            }
            cout << "\n---------------------------------------------------------------------------------------\n";}
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
            for(int i =0;i < line;i++)
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
                        if((month == monthU[0] && year == yearU[0]) || (month == monthU[1] && year == yearU[1] && dateU[1] != 01))
                            Aroom = false;
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
//#########################################################################################################

void check_checkin(const roomtype room,const guestinfo info)//เช็คหาวันที่เข้าพักจากเลขห้อง
{
    int num_check;
    int line;
    getdata(line);

    cout << "\nPlease select room : ";
    cin >> num_check;
    cout << "---------------------------------------------------------------------------------------";

    for(int i =0;i < line;i++)
    {
        if(atoi((data[i][6].c_str())) == num_check)
        {
            cout <<"  \n\t\t\t+--------------------------------------+";
            cout <<  "\n\t\t\t|         Checkin   : " << data[i][3]<<"       |";
            cout <<  "\n\t\t\t|         Checkout  : " << data[i][4]<<"       |";
            cout <<  "\n\t\t\t+--------------------------------------+";
        }
    }
    cout << "\n---------------------------------------------------------------------------------------\n";

}

//#########################################################################################################
void check_income()
{
    string textline;
    int income=0;
    ifstream source;
    source.open("income.txt");
    while (getline(source,textline))
    {
        if(atoi(textline.c_str())>income){
            income = atoi(textline.c_str());
        }
    }
    source.close();
    cout << "\n                          $$$$$  Total income = " << income << " baht  $$$$$";
    cout << "\n---------------------------------------------------------------------------------------";
}
//#########################################################################################################

void reset_info()
{
    int passW = 1111,input;
    cout << "\nPlease input password to delete information : ";
    cin >> input;
    if(input == passW)
    {
        string s;
        ofstream resource;
        resource.open("data.txt");
        resource << s;
        resource.close();
        ofstream dest;
        dest.open("income.txt");
        dest << s;
        dest.close();
        memset(data, 0,sizeof(data));
        cout << "---------------------------------Information was deleted.------------------------------";
    }
    cout << "\n---------------------------------------------------------------------------------------";
    
}
//#########################################################################################################

void recepFunc(roomtype &room,const guestinfo info)
{
    char menuR;

    while(menuR != '8')
    {
        cout << "\n\n\t\t\t+--------------------------------------+";
        cout << "  \n\t\t\t|          Receptionist MENU           |";
        cout << "  \n\t\t\t+--------------------------------------+";

        cout << "\n                     [1] Check available room";
        cout << "\n                     [2] Check checkin and checkout date";
        cout << "\n                     [3] Check total income";
        cout << "\n                     [4] Search information";
        cout << "\n                     [5] Change cleaning status";
        cout << "\n                     [6] Clear booking";
        cout << "\n                     [7] Delete all information";
        cout << "\n                     [8] Exit...";

        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\nPlease select : ";
        cin >> menuR;
        cout << "---------------------------------------------------------------------------------------";
        menuR=toupper(menuR);

        while(menuR != '1' && menuR != '2' && menuR != '3' && menuR != '4' && menuR != '5' && menuR != '6' && menuR != '7' && menuR != '8')
        {
            cout << "\nPlease select again!! : ";
            cin >> menuR;

        }

        if(menuR == '1')
            check_Aroom(room);

        if(menuR == '2')
            check_checkin(room,info);

        if(menuR == '3')
            check_income();

        if(menuR == '4')
            searchforRecep(info,room);

        if(menuR == '5')
            change_Cstatus(room);

        if(menuR == '6')
            change_Booking(room);

        if(menuR == '7')
            reset_info();

    }
}
//#########################################################################################################