//object oriented programming class final project, physical engineering
//In this project, both own libraries and those already incorporated into the Arduino IDE, defined classes and use of pointers were used
//I tried to explain most of the code in detail
//remember that the connections of the module with the arduino are in digital ports
#include "clases.h"
#include <SoftwareSerial.h>
const int pt=4;
const int pr=3;
//we declared a SoftwareSerial variable to be able to work with pins 3 and 4, pins 0 and 1 gave me problems when recompiling
SoftwareSerial gps(pt,pr);

void setup() {
    //definition of setups, the number inside the parentheses are bauds
    Serial.begin(115200);
    gps.begin(9600);
}

void loop() {
    //this here takes the data that the gps gives us and sends only the string with the GPGGA code, as I used SoftwareSerial.h I could not put it in a class
    decodificador s;
    String t,j,x;
    for (int i = 0; i < 10000; i++)
    {
    if (gps.available())
    //this here makes it take the first 1000 digits of the string that the gps gives us, as long as it receives data
    {
        char np;
        np=gps.read();
        t+=np;
        //digits are stored in this string 
    }
    }
    j=s.sep_strng(t,'$',3);
    x=s.sep_strng(j,',',0);
    if (x=="GPGGA")
    //we use a function of class separate to be able to separate the GPGGA frame from the rest of the others
    //the if allows us to see if it is actually the needed frame
    {
        interprete g(j);
        g.inter();
        //We declare a variable of the interpreter class, and we send it to the function inter
    }
    
}
