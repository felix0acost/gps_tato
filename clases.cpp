//primary inspiration for the completion of this code https://www.youtube.com/watch?v=uMCSdgkdOJc
//also this https://www.youtube.com/watch?v=5qap5aO4i9A ╰(艹皿艹 )
#include <Arduino.h>
#include <stdlib.h>
//beautiful libraries that sometimes did not load

class decodificador{
    private:
        String Trama;
        char Separador;
        int Posi;
    public:
        decodificador(){
            //builder, nothing else....
        }
        String sep_strng(String Trama,char Separador,int Posi){
            //this thing separates the strings (¬‿¬)
            //I preferred to leave the class like this so as not to declare many variables of type decoder and reuse one if necessary
            int Cont = 0;
	        int strPosi[] = {0, -1};
	        int maxPosi = Trama.length() - 1;

	        for (int i = 0; i <= maxPosi && Cont <= Posi; i++) {
		        if (Trama.charAt(i) == Separador || i == maxPosi) {
			        Cont++;
			        strPosi[0] = strPosi[1] + 1;
			        strPosi[1] = (i == maxPosi) ? i + 1 : i;
		        }
	        }

	        return Cont > Posi ? Trama.substring(strPosi[0], strPosi[1]) : "";
        }
        double conv_lalo(String Trama,int Posi){
            //this thing was done to avoid writing twice the conversion from string to float latitude and longitude,
            //besides leaving it all in degrees (╬▔皿▔)╯
            char m[Posi];
            for (int i = 0; i < Posi; i++)
            {
                m[i]=Trama[i];
            }
            double me=atol(m);
            me=me/100;
            int em=me;
            me=me-em;
            me=me*100/60;
            me=me+em;
            return me;
        }
        void sep_tim(String Trama,int Posi){
            // This here helps us to convert from string to float all the utc and separate it into hours, minutes and seconds
            char m[Posi];
            for (int i = 0; i < Posi; i++)
            {
                m[i]=Trama[i];
            }
            float me=atof(m);
            me=me/10000;
            int h=me;
            me=me-h;
            me=me*100;
            int mi=me;
            me=me-mi;
            me=me*100;
            Serial.println("Horas: ");
            Serial.print(h);
            Serial.println("\nMinutos: ");
            Serial.print(mi);
            Serial.println("\nSegundos: ");
            Serial.print(me);       
        }
};

class interprete{
    private:
        String tram;
    public:
        interprete(String _tram){
            tram=_tram;
        }
        void inter(){
            Serial.println("\n"+tram);
            decodificador s;
            double la,lo;
            String proto,utc,lat,NS,lon,EW,PFSI,SU,HDOP,alt,MA,GS,MG,adc,dif,chcksm,cr;
            String *h[16];
            //we use this pointer since this serves as an array this helps us to avoid writing the function string by string
            //that separates the strings
            h[0]=&proto;
            h[1]=&utc;
            h[2]=&lat;
            h[3]=&NS;
            h[4]=&lon;
            h[5]=&EW;
            h[6]=&PFSI;
            h[7]=&SU;
            h[8]=&HDOP;
            h[9]=&alt;
            h[10]=&MA;
            h[11]=&GS;
            h[12]=&MG;
            h[13]=&adc;
            h[14]=&dif;
            h[15]=&chcksm;
            h[16]=&cr;
            for (int i = 0; i < 16 ; i++)
            {
                *h[i]=s.sep_strng(tram,',',i);
            }
            //and this part is the one that prints everything on the screen
            Serial.println("----------------------------------------------------------------------------------");
            s.sep_tim(utc,10);//esta funcion en especifico imprime solo el utc
            la=s.conv_lalo(lat,9);
            lo=s.conv_lalo(lon,9);
            Serial.println("\nLatitud: ");
            Serial.print(la);
            Serial.println(" Grados "+NS);
            Serial.println("Longitud: ");
            Serial.print(lo);
            Serial.println(" Grados "+EW);
            Serial.println("Satelites en Uso: "+SU);
            Serial.println("Dilucion Horizontal de la Precisión: "+HDOP);
            Serial.println("Metros Sobre el Nivel del Mar: "+alt+MA);
            Serial.println("Separación del Geoide: "+GS+MG);
            Serial.println(":D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D-:D");
        }
};








































































































































































/*luche como 3 dias tratando de que VS Code funcionara y poder escribir todo mas rapido ￣へ￣, pero el esfuerzo valio la pena,
no solo se ve mejor sino que el auto-completado ayudo mucho, tambien la pantalla es de un color oscuro asi que se cansa menos,
el codigo c++ corre muy bien y ya esta todo integrado, desde la terminal de comandos hasta el serial monitor*/