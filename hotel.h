#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cctype>
using namespace std;

int income = 0;
vector<string> unaviroom;
vector<string> guestdata;

struct roomtype{ //structure เก็บตัวแปรทุกอย่างเกี่ยวกับห้อง
    string type[3];
    int roomnumber[24];
    int price[3];
    char status[24];
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

void resetroomstatus(roomtype &room){
    for(int i=0;i<24;i++){
        room.status[i]='A';
    }
}

void Showinfo(const string data[100][10],int loc){
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
    cout<<"\n\n+------------------------------------------------------------------------------------------+\n";
    cout<<       "|                                      GUEST INFORMATION                                   |\n";
    cout<<        "+------------------------------------------------------------------------------------------+\n";

    cout<<     "|      Room number     : "<< data[loc][6]<<"                                                              |";

    cout<<     "\n|      Name            : "<<data[loc][0] <<"\t\tBooking Number : "<<data[loc][5]<<"                     |";

    cout<<     "\n|      Email           : "<<data[loc][1] <<"\tTel            : "<<data[loc][2]<<"                |";

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

void plus_income(int price,int &income)
{
    income = income + price;
}

void booking(roomtype &room,guestinfo &info,roomdata &reservedroom) { //ฟังก์ชันการจอง
    int date[2], month[2], year[2], slroom[24], roomNO, totalprice = 0, bookingNum, Numofday = 0;
    int rsdate[2], rsmonth[2], rsyear[2], rsroomNO;
    string name, email, checkin, checkout, rsroom[24], phonenumber,sltype[24];
    char type, confirm;
    resetroomstatus(room);
    cout << "\n\n\t\t\t+--------------------------------------+";
    cout << "\n  \t\t\t|         Booking your rooms           |";
    cout << "\n  \t\t\t+--------------------------------------+";
    do {
        cout << "\nPlease in put a check-in  date (dd/mm/yyyy) : "; //รับวันเช็คอิน
        cin >> checkin;
        sscanf(checkin.c_str(), "%d/%d/%d", &date[0], &month[0], &year[0]);
        cout << "Please in put a check-out date (dd/mm/yyyy) : "; //รับวันเช็คเอาท์
        cin >> checkout;
        sscanf(checkout.c_str(), "%d/%d/%d", &date[1], &month[1], &year[1]);
        cout << "\n---------------------------------------------------------------------------------------";
        if (year[0] == year[1]) {
            if (date[0] < date[1] && month[1] == month[0] || month[1] > month[0]) break;
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

    cout << "\nNumber of room : "; //เช็คจำนวนห้องที่จะจอง
    cin >> roomNO;
    for (int s = 0; s < unaviroom.size(); s++) {
        int temp = 0;
        sscanf(unaviroom[s].c_str(), "%d/%d/%d/%d/%d/%d/%d", &rsdate[0], &rsmonth[0], &rsyear[0], &rsdate[1],
               &rsmonth[1], &rsyear[1], &rsroomNO);
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
                    if (rsdate[0] <= date[0] && date[0] < rsdate[1] ||
                        rsdate[0] < date[1] && date[1] <= rsdate[1]) { //กรณีวันที่เช็คอินหรือเช็คเอาท์อยู่ระหว่างข้อมูล
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
    for (int i = 0; i < roomNO; i++) {
        cout << "\n---------------------------------------------------------------------------------------";

        cout << "\n[1] Standard  price : 1000 Baht";
        cout << "\n[2] Twin bed  price : 1500 Baht";
        cout << "\n[3] Deluxe    price : 2000 Baht"; //เลือกชนิดของห้อง 3 ชนิด
        cout << "\nPlease choose a room type : ";
        cin >> type;
        cout << "\n---------------------------------------------------------------------------------------";
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
                        }
                    }
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
                        }
                    }
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
                        }
                    }
                }
                break;
            }else{ //ถ้าเลือกtypeผิดให้เปลี่ยนใหม่
                cout << "\nPlease select again : ";
                cin >> type;
            }
        }

        cout << "\nPlease select a room : "; //เลือกห้องที่จะจอง
        cin >> slroom[i];
        for(int j=0;j<i;j++){ //แก้errorแล้วจ้า
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
                            int temp2=0;
                            for(int k=0;k<24;k++){
                                if(slroom[i]==room.roomnumber[k]) temp2=k;
                            }
                            if(room.status[temp2]=='U'||temp2==0){

                                cout << "Please select again : ";
                                cin >> slroom[i];
                            }
                        }
                    }else if (type == '2') {
                        if (((slroom[i] % 1000) / 100) != 2) {
                            cout << "Please select again : ";
                            cin >> slroom[i];
                        }else{
                            int temp2=0;
                            for(int k=0;k<24;k++){
                                if(slroom[i]==room.roomnumber[k]) temp2=k;
                            }
                            if(room.status[temp2]=='U'||temp2==0){
                                cout << "Please select again : ";
                                cin >> slroom[i];
                            }
                        }
                    }else{
                        if (((slroom[i] % 1000) / 100) != 3) {
                            cout << "Please select again : ";
                            cin >> slroom[i];
                        }else{
                            int temp2=0;
                            for(int k=0;k<24;k++){
                                if(slroom[i]==room.roomnumber[k]) temp2=k;
                            }
                            if(room.status[temp2]=='U'||temp2==0){
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
    cout << "\n                  Booking information";
    cout << "\n---------------------------------------------------------------------------------------";
    //แสดงสถานะห้องที่เลือก
    for (int i = 0; i < roomNO; i++) {
        cout << "\nRoom " << i + 1 << " Information";
        cout << "\n---------------------------------------------------------------------------------------";
        if ((slroom[i] % 1000) / 100 == 1) {
            cout << "\nRoom type : " << room.type[0];
            cout << "\nRoom number : " << slroom[i];
            cout << "\nRoom price : " << room.price[0] << " Baht";
            totalprice += room.price[0];
        } else if ((slroom[i] % 1000) / 100 == 2) {
            cout << "\nRoom type : " << room.type[1];
            cout << "\nRoom number : " << slroom[i];
            cout << "\nRoom price : " << room.price[1] << " Baht";
            totalprice += room.price[1];
        } else {
            cout << "\nRoom type : " << room.type[2];
            cout << "\nRoom number : " << slroom[i];
            cout << "\nRoom price : " << room.price[2] << " Baht";
            totalprice += room.price[2];
        }
        cout << "\n---------------------------------------------------------------------------------------";
    }
    totalprice = totalprice * Numofday; //รวมค่าใช้จ่าย
    int M = 0;
    for (int i = 0; i < 24; i++) {
        if (room.status[i] != 'U') {
            M++;
        }
    }
    string A;
    if (M >= 12) {
        totalprice = totalprice;
    } else if (M >= 6) {
        totalprice = totalprice + 200;
    } else if (M >= 3) {
        totalprice = totalprice + 200;
    }
    int C = rand() % 10;
    cout << "\n\n\t\t\t\t+----------------------------+";
    cout << "\n  \t\t\t\t|     Random Lucky Number    |";
    cout << "\n  \t\t\t\t|             " << C << "              |";
    cout << "\n  \t\t\t\t+----------------------------+";
    if (C == 3) {
        totalprice = totalprice * 85 / 100;


        cout << "\n\n\t\t\t+----------------------------+";
        cout << "\n  \t\t\t|        Super Lucky         |";
        cout << "\n  \t\t\t|       discount  15%        |";
        cout << "\n  \t\t\t+----------------------------+";


    } else if (C == 5) {
        totalprice = totalprice * 70 / 100;

        cout << "\n\n\t\t\t\t+----------------------------+";
        cout << "\n  \t\t\t\t|         More Lucky         |";
        cout << "\n  \t\t\t\t|        discount  30%       |";
        cout << "\n  \t\t\t\t+----------------------------+";

    } else if (C == 7) {

        totalprice = totalprice - 250;
        cout << "\n\n\t\t\t\t+----------------------------+";
        cout << "\n  \t\t\t\t|            Lucky           |";
        cout << "\n  \t\t\t\t|       discount 250 Baht    |";
        cout << "\n  \t\t\t\t+----------------------------+";

    } else if (C == 9) {

        totalprice = totalprice - 50;
        cout << "\n\n\t\t\t\t+----------------------------+";
        cout << "\n  \t\t\t\t|        Some Lucky          |";
        cout << "\n  \t\t\t\t|     discount 50 Baht       |";
        cout << "\n  \t\t\t\t+----------------------------+";
    } else {
        totalprice = totalprice;

        cout << "\n\n\t\t\t\t+----------------------------+";
        cout << "\n  \t\t\t\t|          Unlucky           |";
        cout << "\n  \t\t\t\t+----------------------------+";

    }
    cout << "\n---------------------------------------------------------------------------------------";

    cin.ignore();
    cout << "\nTotal : " << totalprice << " Baht";
    reservedroom.price=totalprice;
    plus_income(totalprice,income);
    //รับข้อมูลลูกค้า
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\n                                 Guest information";
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nName : ";
    getline(cin, name);
    cout << "Email: ";
    cin >> email;
    cout << "Tel  : ";
    cin >> phonenumber;
    //คอนเฟิร์มการจอง
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nConfirm booking information";
    cout << "\n    YES[Y] or NO[N] : ";
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
            guestdata.push_back(textline);
        }

        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\nChecking room status by using this booking number.";
        cout << "\n\n\t\t\t\t+----------------------------+";
        cout << "\n  \t\t\t\t|       Booking Number       |";
        cout << "\n  \t\t\t\t|            " << bookingNum << "           |";
        cout << "\n  \t\t\t\t+----------------------------+";
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\n                           Thank you for choosing our hotel.";
        cout << "\n                            *** Have a nice vacation ***";
        cout << "\n---------------------------------------------------------------------------------------";
        for(int i=0;i<guestdata.size();i++){
            cout << "\n" << guestdata[i] << "\n";
        }
    } else {
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "*** Booking was canceled ***";
        cout << "\n---------------------------------------------------------------------------------------";
    }
}

void searchforRecep(const guestinfo info, const roomtype room) {//ฟังก์ชันการค้นหาของพนักงาน
    char cmd;
    string name, checkin;
    string data[100][10];
    int roomNO;
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
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\n      Manage a room";
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\n[N] Searching by name";
    cout << "\n[R] room number";
    cout << "\n[C] check-in date";
    cout << "\nPlease select and option : ";
    cin >> cmd;
    cmd = toupper(cmd);
    cout << "\n---------------------------------------------------------------------------------------";
    if (cmd == 'N') {
        cin.ignore();
        cout << "\nPlease input a name : ";
        getline(cin, name);
        cout << "\n---------------------------------------------------------------------------------------";
        for (int i = 0; i < guestdata.size(); i++) {
            if (name == data[i][0]) {
                Showinfo(data,i);
            }
        }
    } else if (cmd == 'R') {
        cout << "\nPlease input a room number : ";
        cin >> roomNO;
        cout << "\n---------------------------------------------------------------------------------------";
        for (int i = 0; i < guestdata.size(); i++) {
            if (roomNO == stoi(data[i][6])) {
                Showinfo(data,i);
            }
        }
    } else {
        cout << "\nPlease input a check-in date : ";
        cin >> checkin;
        cout << "\n---------------------------------------------------------------------------------------";
        for (int i = 0; i < guestdata.size(); i++) {
            if (checkin == data[i][3]) {
                Showinfo(data,i);
            }
        }
    }

}

void searchforGuest(const guestinfo info, const roomtype room){ //ฟังก์ชันการค้นหาของลูกค้า
    string bookingNO;
    string data[100][10];
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
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nManage a room";
    cout << "\n---------------------------------------------------------------------------------------";
    cout << "\nSearching by booking number";
    cout << "\nPlease input your booking number : ";
    cin >> bookingNO;
    cout << "\n---------------------------------------------------------------------------------------";
    for(int i = 0; i < guestdata.size(); i++){
        if(bookingNO==data[i][5]){
            Showinfo(data,i);
        }
    }

}

void check_Aroom(const roomtype room)//ฟังก์ชันเช็คห้องว่าง
{
    char checkA,checkAt;
    int checkAf,roomnum[100],date[2],month[2],year[2],datein[2],monthin[2],yearin[2],dateout[2],monthout[2],yearout[2];
    string checkin,data[100][10];
    bool Aroom = true;

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

    cout << "\nCheck available room";
    /*cout << "\nPlease input day you would like to check : ";
    cin >> checkin;
    sscanf(checkin.c_str(), "%d/%d/%d", &date[0], &month[0], &year[0]);*/
    cout << "\nRoom type[T] or Floor[F] : ";//ให้เลือกว่าจะหาจากอะไร มีประเภทห้อง กับ ชั้น
    cin >> checkA;
    checkA=toupper(checkA);

    while(checkA != 'T' && checkA != 'F')//ใส่ค่าไม่ถูกต้อง
    {
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\nRoom type[T] or Floor[F] ";
        cout << "\nPlease input again!! : ";
        cin >> checkA;
        checkAt=toupper(checkA);
    }

    /*for(int i = 0;i < guestdata.size();i++)
    {
        sscanf(data[i][3].c_str(), "%d/%d/%d", &datein[0], &monthin[0], &yearin[0]);
        sscanf(data[i][4].c_str(), "%d/%d/%d", &dateout[0], &monthout[0], &yearout[0]);
        if(date[0])
    }*/

    if(checkA == 'T')//หาจากประเภทห้อง
    {
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\n[S] Standard\n[T] Twin bed \n[D]  Deluxe";
        cout << "\nPlease select room type : ";
        cin >> checkAt;
        checkAt=toupper(checkAt);
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\nAvailable room : ";
        if (checkAt == 'S')
        {
            for (int k = 0; k < 24; k++)
            {
                for(int i =0;i < guestdata.size();i++)
                {
                    if (((room.roomnumber[k] % 1000) / 100) == 1 && room.status[k] != 'U' && room.roomnumber[k] == atoi(data[i][6].c_str()))
                    {
                        Aroom = false;
                    }
                }
                if(((room.roomnumber[k] % 1000) / 100) == 1 && Aroom == true)
                {
                    cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดstandardที่ว่างอยู่ทั้งหมด
                }
                Aroom = true;
            }
        } else if (checkAt == 'T') {
            for (int k = 0; k < 24; k++)
            {
                for(int i =0;i < guestdata.size();i++)
                {
                    if (((room.roomnumber[k] % 1000) / 100) == 2 && room.status[k] != 'U' && room.roomnumber[k] == atoi(data[i][6].c_str()))
                    {
                        Aroom = false;
                    }
                }
                if(((room.roomnumber[k] % 1000) / 100) == 2 && Aroom == true)
                {
                    cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดtwinที่ว่างอยู่ทั้งหมด
                }
                Aroom = true;
            }
        } else {
            for (int k = 0; k < 24; k++)
            {
                for(int i =0;i < guestdata.size();i++)
                {
                    if (((room.roomnumber[k] % 1000) / 100) == 3 && room.status[k] != 'U' && room.roomnumber[k] == atoi(data[i][6].c_str()))
                    {
                        Aroom = false;
                    }
                }
                if(((room.roomnumber[k] % 1000) / 100) == 3 && Aroom == true)
                {
                    cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดdeluxeที่ว่างอยู่ทั้งหมด
                }
                Aroom = true;
            }
        }
        cout << "\n---------------------------------------------------------------------------------------\n";

    }

    if(checkA == 'F')//หาจากชั้น
    {
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\nPlease select floor 1 2 3 4 : ";
        cin >> checkAf;
        cout << "\n---------------------------------------------------------------------------------------";
        cout << "\nAvailable room : ";
        for (int k = 0; k < 24; k++)
        {
            for(int i =0;i < guestdata.size();i++)
            {
                if (((room.roomnumber[k]/1000)) == checkAf && room.status[k] != 'U' && room.roomnumber[k] == atoi(data[i][6].c_str()))
                {
                    Aroom = false;
                }
            }
            if(((room.roomnumber[k]/1000)) == checkAf && Aroom == true)
            {
                cout << room.roomnumber[k] << " "; //ให้ปริ้นท์ห้องชนิดstandardที่ว่างอยู่ทั้งหมด
            }
            Aroom = true;
        }
        cout << "\n---------------------------------------------------------------------------------------\n";
    }


}

void check_checkin(const roomtype room,const guestinfo info)//เช็คหาวันที่เข้าพักจากเลขห้อง
{
    int num_check;
    string data[100][10];
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
    cout << "\nPlease select room : ";
    cin >> num_check;
    for(int i =0;i < guestdata.size();i++)
    {
        if(stoi(data[i][6]) == num_check)
        {
            cout << "Checkin : " << data[i][3];
            cout << "\nCheckout : " << data[i][4]<<endl;
        }
    }
    cout << "\n---------------------------------------------------------------------------------------\n";

}

void check_income(const int income)
{
    cout << "\nTotal income = " << income << " baht";
    cout << "\n---------------------------------------------------------------------------------------\n";
}

void recepFunc(const roomtype room,const guestinfo info)
{
    char menuR;
    cout << "\nWelcome!";
    while(menuR != 'E')
    {
        cout << "\nWhat do you want to check?";
        cout << "\n[A] Check available room";
        cout << "\n[D] Check checkin and checkout date";
        cout << "\n[C] Check total income";
        cout << "\n[S] Search information";
        cout << "\n[E] Exit";
        cout << "\nPlease select : ";
        cin >> menuR;
        cout << "\n---------------------------------------------------------------------------------------";
        menuR=toupper(menuR);

        while(menuR != 'A' && menuR != 'D' && menuR != 'S' && menuR != 'E' && menuR != 'C')
        {
            cout << "\nPlease input again : ";
            cin >> menuR;
            menuR=toupper(menuR);
        }

        if(menuR == 'A')
            check_Aroom(room);

        if(menuR == 'D')
            check_checkin(room,info);

        if(menuR == 'S')
            searchforRecep(info,room);

        if(menuR == 'C')
            check_income(income);

    }

}