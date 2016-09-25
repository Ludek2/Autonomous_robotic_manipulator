#pragma once

using namespace System;
using namespace System::Drawing;


namespace c_vis
{
   public ref class c_vision
   {
      
   private:
		CvCapture* capture; 
	    IplImage* frame; // snímek z kamery
	    IplImage* destination; // pro nastavení velikosti 
		IplImage* obr_zamereni;
		IplImage* destination2; // pro nastavení velikosti
		
		IplImage *birds_image; // pro uložení ptaèího pohledu
		IplImage *birds_image_clone; // ve fci pøi uložení ptaèího pohledu
		
		
		array<double> ^kal_bod;
		double meritko_px_na_cm;
		double odsazeni_kal_soustavy;
		double posun_osy_x_px;
		float vyska_Z;
		
	   
	    Drawing::Bitmap^ c_vision::IplImage2Bitmap( IplImage* iplimage );
		void c_vision::take_photo( char *name); // udìlá snímek z frame
		void c_vision::birds_eye( float Z);// z pohledu na šachovnici vytvoøí ptaèí pohled a uloží homografní matici
		void c_vision::kal_body(void);
		IplImage* c_vision::bird_eye_f_picture();

   protected:
     
   
   public:
        
	    array<double> ^souradnice;
	    
		// Deklarace konstruktoru
		 c_vision();
       
	    // Deklarace destruktoru
		 ~c_vision();
		
	    // Deklarace funkce frame_output()
	    Drawing::Bitmap^ c_vision::frame_output();
		Drawing::Bitmap^ c_vision::obr_zamereni_output();
	    void c_vision::kalibrace();
		void c_vision::zamereni();

	};
}