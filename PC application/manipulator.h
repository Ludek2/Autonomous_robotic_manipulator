#pragma once

using namespace System;

namespace manip
{
   public ref class manipulator
   {
      
   private:
		// Deklarace funkce pro výpoèet geometrie pohybu
		int* vypocet_poloh( float x1, float y1, float z1); 

   protected:
     
   
   public:
      
		int pocet_B; // poèet bytù k odeslání
	  
		// Deklarace konstruktoru
		manipulator();
      
		// Deklarace funkce pro úpravu dat pro odeslání do mikrokontroléru
		array<unsigned char>^ manipulator::DataForSend(String ^ akce, float data[] );
	};
}