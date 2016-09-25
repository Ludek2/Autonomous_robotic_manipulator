#include "stdafx.h"

#include "manipulator.h"
#include "math.h"

using namespace System;

namespace manip
{
   // Definice konstruktoru bez parametr�:
   manipulator::manipulator(){
   
   }
	
   //definice funkce DataForSend
   array<unsigned char>^ manipulator::DataForSend(String ^ akce, float data[] )
   {
	   int akce_int; // ��slo akce kter� se m� prov�st
	   
	   unsigned char B[40]; // Byty pro odesl�n�
	   
	   // p�evod z �et�zce na ��slo akce kter� se m� prov�st
	   if (akce=="pohyb_servo")akce_int=0; 
	   if (akce=="najet_na_bod")akce_int=1; 
	   if (akce=="nahrat_program")akce_int=2;
	   if (akce=="vykonat_program")akce_int=3;
	   if (akce=="pripojit")akce_int=4;	
	   if (akce=="odpojit")akce_int=5;	
	   if (akce=="dokonceno?")akce_int=6;	

	   // vygenerv�n� p��lu�n�ch dat pro odesl�n� do manipul�toru dle typu akce(po�adavku)
	   switch(akce_int){    
		  
			case 0:    //p��m� ovl�d�n�
				this->pocet_B=8;
				B[0]=0;
				B[1]=(unsigned char)data[0];
				B[2]=1;
				B[3]=(unsigned char)data[1];
				B[4]=2;
				B[5]=(unsigned char)data[2];
				B[6]=3;
				B[7]=(unsigned char)data[3];
				break;
	   
			case 1:		//najet� na ur�it� bod
				this->pocet_B=6;
				int* poloha;
				poloha=this->vypocet_poloh( data[0], data[1], data[2]);
			
				B[0]=0;
				B[1]=(unsigned char)poloha[0];
				B[2]=1;
				B[3]=(unsigned char)poloha[1];
				B[4]=2;
				B[5]=(unsigned char)poloha[2];
				break;
		

			case 2:    // naprogramov�n� pohybu
				this->pocet_B=40;
				int* polohy;

				B[0]=4;
				polohy=this->vypocet_poloh( data[0], data[1]+7, data[2]);
				B[1]=(unsigned char)polohy[0];
				B[2]=(unsigned char)polohy[1];
				B[3]=(unsigned char)polohy[2];

				B[4]=4;
				polohy=this->vypocet_poloh( data[0], data[1]+5, data[2]);
				B[5]=(unsigned char)polohy[0];
				B[6]=(unsigned char)polohy[1];
				B[7]=(unsigned char)polohy[2];

				B[8]=4;
				polohy=this->vypocet_poloh( data[0], data[1]+3, data[2]);
				B[9]=(unsigned char)polohy[0];
				B[10]=(unsigned char)polohy[1];
				B[11]=(unsigned char)polohy[2];

				B[12]=4;
				polohy=this->vypocet_poloh( data[0], data[1]+1, data[2]);
				B[13]=(unsigned char)polohy[0];
				B[14]=(unsigned char)polohy[1];
				B[15]=(unsigned char)polohy[2];

				B[16]=4;
				polohy=this->vypocet_poloh( data[0], data[1], data[2]);
				B[17]=(unsigned char)polohy[0];
				B[18]=(unsigned char)polohy[1];
				B[19]=(unsigned char)polohy[2];

				B[20]=5;
				polohy=this->vypocet_poloh( data[3], data[4]+7, data[5]);
				B[21]=(unsigned char)polohy[0];
				B[22]=(unsigned char)polohy[1];
				B[23]=(unsigned char)polohy[2];

				B[24]=5;
				polohy=this->vypocet_poloh( data[3], data[4]+5, data[5]);
				B[25]=(unsigned char)polohy[0];
				B[26]=(unsigned char)polohy[1];
				B[27]=(unsigned char)polohy[2];

				B[28]=5;
				polohy=this->vypocet_poloh( data[3], data[4]+3, data[5]);
				B[29]=(unsigned char)polohy[0];
				B[30]=(unsigned char)polohy[1];
				B[31]=(unsigned char)polohy[2];

				B[32]=5;
				polohy=this->vypocet_poloh( data[3], data[4]+1, data[5]);
				B[33]=(unsigned char)polohy[0];
				B[34]=(unsigned char)polohy[1];
				B[35]=(unsigned char)polohy[2];

				B[36]=5;
				polohy=this->vypocet_poloh( data[3], data[4], data[5]);
				B[37]=(unsigned char)polohy[0];
				B[38]=(unsigned char)polohy[1];
				B[39]=(unsigned char)polohy[2];
				
				break;
	   
			case 3:  // spu�t�n� programu
				this->pocet_B=1;
				B[0]=6;	
				break;
			
			case 4:  // otev�en� portu com a zah�jen� komunikace - odesl�n� signaliza�n�ho bytu
                this->pocet_B=1;
				B[0]=7;	
				break;

			case 5:  // zav�en� portu com a ukon�en� komunikace - odesl�n� signaliza�n�ho bytu
                this->pocet_B=1;
				B[0]=8;	
				break;

			case 6:  // kontroln� byte pro dokon�en� �konu
                this->pocet_B=1;
				B[0]=9;	
				break;
		}
	    
		array<unsigned char>^ texBufArray = gcnew array<unsigned char>(this->pocet_B); //pole Byt�
		for (int i=0; i<(this->pocet_B); i++)texBufArray[i] = B[i];	// napln�n� pole Byt� pro odesl�n�
	
		return texBufArray; 
	
	}
	
  // Definice funkce pro v�po�et geometrie pohybu
  int* manipulator::vypocet_poloh( float x1, float y1, float z1){
	
	double PI=3.14;		
	double x0, y0, r0, r1;
	double a, dx, dy, d, h, rx, ry;
	double x2, y2;
	double x3, y3, x3_a, y3_a, x3_b, y3_b;
	double alfa, beta, gama, theta; //alfa - servo1; beta pomocn� servo2; theta servo0

	x0=0;
	y0=7.5;
	r0=14.2;
	r1=22.9;

	theta= atan( z1/x1 )* 180 / PI+90; //nato�en� serva 0
	//if(z1<0) theta+=90;

	if(z1!=0)x1= sqrt((z1*z1)+(x1*x1));  // p�epo�et hodnoty na ose x v p��pad� pooto�en� podstavy
	
	// ------- v�po�et pr�se��ku 2 kru�nic-----------------------------------------------//
    // tato ��st je p�evzata z C source code example of 2 circles intersections od Tim Voght
	// nalezeno na http://paulbourke.net/geometry/circlesphere/   
	
	dx = x1 - x0;
	dy = y1 - y0;
	d = hypot(dx,dy); // Suggested by Keith Briggs

	if ((d > (r0 + r1)) || (d < fabs(r0 - r1)))
	{
	/* no solution. circles do not intersect. 
	*/
	}
	else {
		/* Determine the distance from point 0 to point 2. */
        a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d) ;
        /* Determine the coordinates of point 2. */
		x2 = x0 + (dx * a/d);
        y2 = y0 + (dy * a/d);
        
		 /* Determine the distance from point 2 to either of the
		* intersection points.
		*/
		h = sqrt((r0*r0) - (a*a));
        
		/* Now determine the offsets of the intersection points from
		* point 2.
		*/
		rx = -dy * (h/d);
        ry = dx * (h/d);
        
		/* Determine the absolute intersection points. */
        x3_a = x2 + rx;
        y3_a = y2 + ry;
        x3_b = x2 - rx;
        y3_b = y2 - ry;
		
		/* Zde kon�� p�evzat� ��st */
		/* v x3_a,y3_a,x3_b,y3_b jsou ulo�eny sou�adnice dvou pr�se��k� kru�nic*/ 
        
		// v�b�r pouze jednoho pr�se��ku a to toho, kter� m� v�t�� sou�adnici y 
		if(y3_a > y3_b){  
                x3= x3_a;
                y3= y3_a;
        }else{
                x3= x3_b;
                y3= y3_b;
        }
		// v x3 a y3 je ulo�ena v�sledn� sou�adnice pr�se��ku


        //nato�en� serva 1
        if(x3!=0)alfa= atan ((y3-y0)/x3) * 180 / PI;
        else alfa= 90; // pr�se��k v ose y gama=beta
        if(alfa<0)alfa+=180;

        // nato�en� serva 2
        if(alfa<=90){

                if((y3)-y1!=0)beta= atan((x1-x3)/abs(((y3)-y1))) * 180 / PI;
                else beta=90; //rovnob�nost s osou x

                if(((y3)-y1)>0){
                        if(alfa<90) gama= (90-alfa)+beta;
                        if(alfa==90) gama= beta;
                }
                else {
                        if(alfa<90)  gama= (90-alfa)+(90+beta);
                        if(alfa==90) gama= (90+beta);
                }
        }

        if(alfa>90){

                beta= atan(abs(((y3)-y1))/(x1-x3)) * 180 / PI;
                if(((y3)-y1)>0) gama= (180-alfa) - beta;
                else gama= (180-alfa) + beta;
        }
		
		// sou�initel� pro jednotliv� servomotory - zji�t�ny m��en�m 
        
		//pro star�� zapojen�
		//float prevod_konst_0=1.266666666;  
        //float prevod_konst_1=1.235;
        //float prevod_konst_2=1.288;
		
		double prevod_konst_0=1.177777;
		double prevod_konst_0_do75st=1.25;//1.177777; 
		double prevod_konst_0_nad105st=1.16;
        double prevod_konst_1=1.20149;
        double prevod_konst_2=1.211111;


        int k_0,k_1,k_2; // odstup pro 0 stup��
        int uh_0,uh_1,uh_2; // zde budou ulo�eny hodnoty pro OCR1A v mikrokontrol�ru

        //pro star�� zapojen�
		//k_0=14;
        //k_1=25;
        //k_2=30;

		k_0=18;
        k_1=47;
        k_2=36;
		
		uh_0=(int)((theta*prevod_konst_0)+k_0);
		if(theta<75)uh_0= (int)((theta*prevod_konst_0_do75st)+k_0);
		if(theta>105)uh_0= (int)((theta*prevod_konst_0_nad105st)+k_0);
		uh_1= (int)(((180-alfa)*prevod_konst_1)+k_1);
        uh_2= (int)((gama*prevod_konst_2)+k_2);
		
		
        int polohy[3];
        int* ukaz_polohy;
        ukaz_polohy=polohy;
        polohy[0]= uh_0;
        polohy[1]= uh_1;
        polohy[2]= uh_2;

        return ukaz_polohy;
     }
  }


}