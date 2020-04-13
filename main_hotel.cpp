#include "hotel.h"
int main() {
    srand(time(0));
    roomtype room;
    guestinfo info;
    roomdata reservedroom;
    //เพิ่มตั้งค่าห้องของอิ๋ว
    roomsetup(room);
    setcleaning(room);
    //ตัวเริ่มโปรแกรม
    for(int i=1;i<1000000;i++){
        int x=checkuser();
        if(x==1){ //ถ้าcheckuser == 1 จะเข้าสู่เมนูของลูกค้า
            if(guestpart()==1){
                //เพิ่มฟังก์ชันหาของอัพ
                searchforGuest(info,room);
            }else{
                booking(room,info,reservedroom);
            }
        }else if(x==2){  //checkuser==0 จะเข้าสู่เมนูของพนักงาน
            for(int i=0;i<4;i++){ //ลูปให้ใส่ username,password ได้ไม่เกิน 3 ครั้ง
                if(receplogin()==1){
                    recepFunc(room,info);
                    break;
                }
                else{
                    if(i==3){
                        cout << "\n                                    Access deny!"; //ถ้าใส่ username,password ผิดเกิน3ครั้งจะจบโปรแกรม
                        cout << "\n---------------------------------------------------------------------------------------";
                        break;
                    }else{
                        cout << "\n                             Invalid username or password";
                        cout << "\n                             You have " << 3-i << " chance to login";
                        cout << "\n---------------------------------------------------------------------------------------";

                    }
                }
            }
        }else return 0;
    }
}