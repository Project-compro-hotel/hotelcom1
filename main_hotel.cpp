#include "hotel.h"

int main() {
    srand(time(0));
    roomtype room;
    guestinfo info;
    roomdata reservedroom;
    //เพิ่มตั้งค่าห้องของอิ๋ว
    roomsetup(room);
    //ตัวเริ่มโปรแกรม
    for(int i=1;i<10;i++){
        if(checkuser()==1){ //ถ้าcheckuser == 1 จะเข้าสู่เมนูของลูกค้า
            if(guestpart()==1){
                //เพิ่มฟังก์ชันหาของอัพ
                searchforGuest(info,room);
            }else{
                booking(room,info,reservedroom);
            }
        }else{ //checkuser==0 จะเข้าสู่เมนูของพนักงาน
            for(int i=0;i<4;i++){ //ลูปให้ใส่ username,password ได้ไม่เกิน 3 ครั้ง
                if(receplogin()==1){
                    recepFunc(room,info);
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