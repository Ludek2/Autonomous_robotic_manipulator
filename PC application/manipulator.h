#pragma once

using namespace System;

namespace manip
{
   public ref class manipulator
   {
      
   private:
		// Deklarace funkce pro v�po�et geometrie pohybu
		int* vypocet_poloh( float x1, float y1, float z1); 

   protected:
     
   
   public:
      
		int pocet_B; // po�et byt� k odesl�n�
	  
		// Deklarace konstruktoru
		manipulator();
      
		// Deklarace funkce pro �pravu dat pro odesl�n� do mikrokontrol�ru
		array<unsigned char>^ manipulator::DataForSend(String ^ akce, float data[] );
	};
}