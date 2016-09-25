#include "stdafx.h"
#include <cv.h>
#include <highgui.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "C_Vision.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>


using namespace System;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Data;
using namespace cv;

namespace c_vis
{
   // Definice konstruktoru bez parametrù:
   c_vision::c_vision(){
		kal_bod = gcnew array<double>(5); // initializace pole pro souøadnice kalibraèních bodù
		souradnice = gcnew array<double>(1000); //initializace pole pro souøadnice zamìøených objektù


	    this->capture = cvCreateCameraCapture( CV_CAP_ANY );
		cvSetCaptureProperty(this->capture,CV_CAP_PROP_FRAME_WIDTH, 1280);
		cvSetCaptureProperty(this->capture,CV_CAP_PROP_FRAME_HEIGHT, 720);
		cvSetCaptureProperty(this->capture,CV_CAP_PROP_FPS, 1);
		
		if ( !this->capture ) {
		//fprintf( stderr, "ERROR: capture is NULL \n" );
		//getchar();
        } 

		// pomocný frame pro zjištìní parametrù
		IplImage* frame_pomocne = cvQueryFrame( this->capture );
		
		//frame destination pro zmìnu velikosti
		this->destination = cvCreateImage( cvSize((int)((frame_pomocne->width*40)/100) , (int)((frame_pomocne->height*40)/100) ), frame_pomocne->depth, frame_pomocne->nChannels );
		this->destination2 = cvCreateImage( cvSize((int)((frame_pomocne->width*40)/100) , (int)((frame_pomocne->height*40)/100) ), frame_pomocne->depth, frame_pomocne->nChannels );
		
		// naètení poslední uložené výšky ptaèího pohledu ze souboru
		StreamReader^ MyStreamReader = nullptr;
		System::String^ FileName1 = "hodnota_Z.txt";
		MyStreamReader = gcnew StreamReader(FileName1);
		System::String^ hodnota_Z = nullptr;
		hodnota_Z = MyStreamReader->ReadLine();
		this->vyska_Z=(float)Convert::ToDouble(hodnota_Z);
		MyStreamReader->Close();
		
		// naètení posledních uložených kalibraèních bodù ze souboru
		StreamReader^ MyStreamReader2 = nullptr;
		System::String^ FileName2 = "kalibracni_body.txt";
		MyStreamReader2 = gcnew StreamReader(FileName2);
		System::String^ hodnota = nullptr;
		hodnota = MyStreamReader2->ReadLine();
		this->odsazeni_kal_soustavy=Convert::ToDouble(hodnota);
		hodnota = MyStreamReader2->ReadLine();
		this->meritko_px_na_cm=Convert::ToDouble(hodnota);
		hodnota = MyStreamReader2->ReadLine();
		this->posun_osy_x_px=Convert::ToDouble(hodnota);
		MyStreamReader2->Close();

	}
   c_vision::~c_vision(){

		pin_ptr<CvCapture*> p;
		p = &this->capture;
		cvReleaseCapture( p );  

   }

   Drawing::Bitmap^ c_vision::IplImage2Bitmap( IplImage* iplimage )
{
	if (iplimage->roi)
	{
		IplImage* out;
		out = cvCreateImage(cvGetSize(iplimage), iplimage->depth,
		iplimage->roi->coi == 0 ? iplimage->nChannels : 1);
		cvCopyImage(iplimage, out);
		iplimage = out;
	}

		System::Drawing::Imaging::PixelFormat formato =
		(iplimage->nChannels == 3) ?
		System::Drawing::Imaging::PixelFormat::Format24bppRgb :
		System::Drawing::Imaging::PixelFormat::Format8bppIndexed;

		Drawing::Bitmap^ bmp = gcnew Drawing::Bitmap(iplimage->width,
		iplimage->height,
		iplimage->widthStep,
		formato,
		System::IntPtr(iplimage->imageData));

		if (formato == System::Drawing::Imaging::PixelFormat::Format8bppIndexed)
		{
			System::Drawing::Imaging::ColorPalette^ pal = bmp->Palette;
			for (int i = 0; i < pal->Entries->Length; i++)
				pal->Entries[i] = Color::FromArgb(255, i, i, i);
				bmp->Palette = pal;
		}	

		return bmp;
}

   
   Drawing::Bitmap^ c_vision::frame_output(){
		
	   	
		// Get one frame
		this->frame = cvQueryFrame( this->capture );
		
		//use cvResize to resize source to a destination image
	    cvResize(this->frame, this->destination);
		
		// pøevod IplImage na bmp
		Drawing::Bitmap^ bmp1 = this->IplImage2Bitmap(this->destination);
		
		return bmp1;
    }

   Drawing::Bitmap^ c_vision::obr_zamereni_output(){
		
		//use cvResize to resize source to a destination image
	    cvResize(this->obr_zamereni, this->destination2);
		
		// pøevod IplImage na bmp
		Drawing::Bitmap^ bmp1 = this->IplImage2Bitmap(this->destination2);
		
		return bmp1;
    }

	
    /*---- udìlá snímek z frame ------------------------------------------------------------------------------------------------*/
    void c_vision::take_photo( char *name){

	   this->frame = cvQueryFrame( this->capture );	
	   cvSaveImage(name ,this->frame);
   
    }

    
	
	/*---- z pohledu na šachovnici vytvoøí ptaèí pohled a uloží homografní matici ----------------------------------------------*/
    void c_vision::birds_eye( float Z) // Z je jakoby výška pohledu
{
	//INPUT PARAMETERS:
	int board_w = 6;
	int board_h = 9;
	int board_n  = board_w * board_h;
	CvSize board_sz = cvSize( board_w, board_h );
	CvMat *intrinsic = (CvMat*)cvLoad("intrinsics.xml");
    CvMat *distortion = (CvMat*)cvLoad("distortion.xml");
	IplImage *image = 0, *gray_image = 0, *birds_image2 =0;
	if((image = cvLoadImage("1.jpg"))== 0) //naètení fotky pro zamìøení perspektivního pohledu
	{
		//printf("Error: Couldn't load %s\n","1.jpeg");
		//return -1;
	}
	birds_image2 = cvCloneImage(image); // naètení pro zobrazení ptaèího pohledu
		
	gray_image = cvCreateImage(cvGetSize(image),8,1);
    cvCvtColor(image, gray_image, CV_BGR2GRAY);

	//UNDISTORT OUR IMAGE
    IplImage* mapx = cvCreateImage( cvGetSize(image), IPL_DEPTH_32F, 1 );
    IplImage* mapy = cvCreateImage( cvGetSize(image), IPL_DEPTH_32F, 1 );
    cvInitUndistortMap(
      intrinsic,
      distortion,
      mapx,
      mapy
    );
	IplImage *t = cvCloneImage(image);
    cvRemap( t, image, mapx, mapy );

	//GET THE CHECKERBOARD ON THE PLANE
	//cvNamedWindow("Checkers");
	CvPoint2D32f* corners = new CvPoint2D32f[ board_n ];
    int corner_count = 0;
    int found = cvFindChessboardCorners(
        image,
        board_sz,
        corners,
        &corner_count, 
        CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
      );
	if(!found){
		//printf("Na snimku nenalezena kalibracni sachovnice, nalezeno pouze %d z %d rohu\n",corner_count,board_n);
		//return -1;
	}
	//Get Subpixel accuracy on those corners
	cvFindCornerSubPix(gray_image, corners, corner_count, 
    cvSize(11,11),cvSize(-1,-1), 
	cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));

	//GET THE IMAGE AND OBJECT POINTS:
	//Object points are at (r,c): (0,0), (board_w-1,0), (0,board_h-1), (board_w-1,board_h-1)
	//That means corners are at: corners[r*board_w + c]
	CvPoint2D32f objPts[4], imgPts[4];
	objPts[0].x = 0;         objPts[0].y = 0; 
	objPts[1].x = board_w-1; objPts[1].y = 0; 
	objPts[2].x = 0;         objPts[2].y = board_h-1;
	objPts[3].x = board_w-1; objPts[3].y = board_h-1; 
	imgPts[0] = corners[0];
	imgPts[1] = corners[board_w-1];
	imgPts[2] = corners[(board_h-1)*board_w];
	imgPts[3] = corners[(board_h-1)*board_w + board_w-1];

	//DRAW THE POINTS in order: B,G,R,YELLOW
	cvCircle(image,cvPointFrom32f(imgPts[0]),9,CV_RGB(0,0,255),3);
	cvCircle(image,cvPointFrom32f(imgPts[1]),9,CV_RGB(0,255,0),3);
	cvCircle(image,cvPointFrom32f(imgPts[2]),9,CV_RGB(255,0,0),3);
	cvCircle(image,cvPointFrom32f(imgPts[3]),9,CV_RGB(255,255,0),3);

	//DRAW THE FOUND CHECKERBOARD
	cvDrawChessboardCorners(image, board_sz, corners, corner_count, found);
    //cvShowImage( "Checkers", image );

	//FIND THE HOMOGRAPHY
	CvMat *H = cvCreateMat( 3, 3, CV_32F);
	CvMat *H_invt = cvCreateMat(3,3,CV_32F);
	cvGetPerspectiveTransform(objPts,imgPts,H);

	int key = 0;
	IplImage *birds_image = cvCloneImage(image); //clone pouze proto, aby promìnná nebyla prázdná(jinak mi to nefungovalo)
	cvNamedWindow("Birds_Eye");
	
	//LET THE USER ADJUST THE Z HEIGHT OF THE VIEW
	while(key != 27) {	//escape key stops
		CV_MAT_ELEM(*H,float,2,2) = Z;
		//cvInvert(H,H_invt); //If you want to invert the homography directly
		//cvWarpPerspective(image,birds_image,H_invt,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS );
		//USE HOMOGRAPHY TO REMAP THE VIEW
		cvWarpPerspective(birds_image2,birds_image,H,CV_INTER_LINEAR+CV_WARP_INVERSE_MAP+CV_WARP_FILL_OUTLIERS );
		cvShowImage("Birds_Eye", birds_image);
	    key = cvWaitKey();
	    if(key == 'u') Z += 0.5;
	    if(key == 'd') Z -= 0.5;
	}
	this->vyska_Z = Z;

	// uložení hodnoty Z do souboru 
	StreamWriter^ MyStreamWriter = nullptr;
	System::String^ FileName = "hodnota_Z.txt";
	MyStreamWriter = gcnew StreamWriter(FileName);
	System::String^ hodnota_Z=Convert::ToString((double)Z);
	MyStreamWriter->WriteLine(hodnota_Z, FileName);
	MyStreamWriter->Close();

	// zde se uloží foto pro další zpracování
	cvSaveImage("bird_eye.jpg", birds_image);

	//cvShowImage("Birds_Eye", birds_image);
	
	//SHOW ROTATION AND TRANSLATION VECTORS
	CvMat* image_points  = cvCreateMat(4,1,CV_32FC2);
	CvMat* object_points = cvCreateMat(4,1,CV_32FC3);
	for(int i=0;i<4;++i){
		CV_MAT_ELEM(*image_points,CvPoint2D32f,i,0) = imgPts[i];
		CV_MAT_ELEM(*object_points,CvPoint3D32f,i,0) = cvPoint3D32f(objPts[i].x,objPts[i].y,0);
	}

	CvMat *RotRodrigues   = cvCreateMat(3,1,CV_32F);
	CvMat *Rot   = cvCreateMat(3,3,CV_32F);
	CvMat *Trans = cvCreateMat(3,1,CV_32F);
	cvFindExtrinsicCameraParams2(object_points,image_points,
			intrinsic,distortion,
			RotRodrigues,Trans);
	cvRodrigues2(RotRodrigues,Rot);

	//SAVE
	cvSave("Rot.xml",Rot);
	cvSave("Trans.xml",Trans);
	cvSave("H.xml",H);
	cvInvert(H,H_invt);
    cvSave("H_invt.xml",H_invt); //Bottom row of H invert is horizon line
}
	
    /*---- pro získání kalibraèních bodù ze šachovnice v ptaèím pohledu --------------------------------------------------------*/
    /*---- pro pøevod souøadnicové soustavy z px na reálné(robota) ----*/
    void c_vision::kal_body(void)
{
	
	//INPUT PARAMETERS:
	int board_w = 6;
	int board_h = 9;
	int board_n  = board_w * board_h;
	CvSize board_sz = cvSize( board_w, board_h );
	CvPoint2D32f* corners = new CvPoint2D32f[ board_n ];
    int corner_count = 0;

	IplImage *birds_image =0;
	birds_image=cvLoadImage("bird_eye.jpg");


	//nalezení rohù šachovnice v ptaèím pohledu 
	IplImage *gray_by_image = 0;
	gray_by_image = cvCreateImage(cvGetSize(birds_image),8,1);
    cvCvtColor(birds_image, gray_by_image, CV_BGR2GRAY);
	//CvPoint2D32f* corners = new CvPoint2D32f[ board_n ];
    int corner_count2 = 0;
    int found2 = cvFindChessboardCorners(
        birds_image,
        board_sz,
        corners,
        &corner_count2, 
        CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
      );
	if(!found2){
		printf("Couldn't aquire checkerboard on %s, only found %d of %d corners\n",
				"argv[5]",corner_count2,board_n);
		//return -1;
	}
	else //pokud je v ptaèím pohledu nalezena šachovnice
	{
		//Get Subpixel accuracy on those corners
		cvFindCornerSubPix(gray_by_image, corners, corner_count2, 
		cvSize(11,11),cvSize(-1,-1), 
		cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
		//DRAW THE FOUND CHECKERBOARD
		cvDrawChessboardCorners(birds_image, board_sz, corners, corner_count, found2);
	
		CvPoint bod[2];
		bod[0].x=corners[5].x;
		bod[0].y=corners[5].y;
		bod[1].x=corners[53].x;
		bod[1].y=corners[53].y;

		CvPoint bod2[2];
		bod2[0].x=corners[5].x;
		bod2[0].y=corners[5].y;
		bod2[1].x=corners[0].x;
		bod2[1].y=corners[0].y;

		cvLine( birds_image, bod[0], bod[1], CV_RGB(255,0,0),4 );
		cvLine( birds_image, bod2[0], bod2[1], CV_RGB(0,255,0),4 );
		cvNamedWindow("Zamereni_rohu_sachovnice");
		cvShowImage( "Zamereni_rohu_sachovnice", birds_image );
	
		//osa y
		this->kal_bod[0]=(double)corners[5].x;
		this->kal_bod[1]=(double)corners[5].y;
		this->kal_bod[2]=(double)corners[53].x;
		this->kal_bod[3]=(double)corners[53].y;
	}
}

	

	/*----  ze snímku vytvoøí ptaèí pohled -------------------------------------------------------------------------------------*/
	IplImage* c_vision::bird_eye_f_picture()
{
	CvMat *H = (CvMat*)cvLoad("H.xml");
	
	//cvNamedWindow("Birds_Eye");
	
	//load 2.jpg -- snímek urèený pro zachycení souøadnic objektù
	//IplImage *birds_image2 =0;
	//this->birds_image=cvLoadImage("1.jpg");
	//IplImage *birds_image = cvCloneImage(birds_image2);
	
    this->birds_image_clone = cvCloneImage(this->birds_image);
	CV_MAT_ELEM(*H,float,2,2) = this->vyska_Z;
	//cvInvert(H,H_invt); //If you want to invert the homography directly
	//cvWarpPerspective(image,birds_image,H_invt,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS );
	//USE HOMOGRAPHY TO REMAP THE VIEW
	cvWarpPerspective(this->birds_image_clone,this->birds_image,H,CV_INTER_LINEAR+CV_WARP_INVERSE_MAP+CV_WARP_FILL_OUTLIERS );
	//cvShowImage("Birds_Eye", birds_image);

	//cvSaveImage("bird_eye.jpg", birds_image);
	return this->birds_image;

}


		
	/* ----------- proces kalibrace  ------------------------------------------------------------------------------------------ */
	void c_vision::kalibrace(){
		
		this->take_photo("1.jpg");
		this->birds_eye( -75 );// z pohledu na šachovnici vytvoøí ptaèí pohled a uloží homografní matici
		this->kal_body();  //najde v šachovnici kalibraèní body pro pøevod souøadnicové soustavy z px na reálné(robota)

		this->odsazeni_kal_soustavy = 15;
        double x[2];
        double y[2];
		
		//bod1
		x[0]=this->kal_bod[0];
        x[1]=this->kal_bod[1];
        //bod 2
        y[0]=this->kal_bod[2];
        y[1]=this->kal_bod[3];
		
		double real_vzdalenost = 15;
        
		//vypoèítá konstantu pro pøevod z px na cm
		//bod_a[0] je x èást bod_a[1] je y èást
		double vzdalenost;
		if(x[0]!=y[0]); //test správnosti -- úseèka z rohù šachovnice musí být rovnobìžnì s osou ošetøit !!!!!!!!!!!!!
		if(x[1]>y[1])vzdalenost=x[1]-y[1];
		else vzdalenost=y[1]-x[1];
		this->meritko_px_na_cm = real_vzdalenost/(double)vzdalenost; //vypoèet konstanty pro pøepoèet mìøítka

		
		if(x[1]<y[1])this->odsazeni_kal_soustavy = this->odsazeni_kal_soustavy - (x[1]*this->meritko_px_na_cm);  // okraj snímku v reál. souøadnicích
        else this->odsazeni_kal_soustavy=this->odsazeni_kal_soustavy-(y[1]*this->meritko_px_na_cm);          // okraj snímku v reál. souøadnicích
        this->posun_osy_x_px = x[0];

		// uložení hodnoty Z do souboru 
		StreamWriter^ MyStreamWriter = nullptr;
		System::String^ FileName = "kalibracni_body.txt";
		MyStreamWriter = gcnew StreamWriter(FileName);
		MyStreamWriter->WriteLine(Convert::ToString(this->odsazeni_kal_soustavy), FileName);
		MyStreamWriter->WriteLine(Convert::ToString(this->meritko_px_na_cm), FileName);
		MyStreamWriter->WriteLine(Convert::ToString(this->posun_osy_x_px), FileName);
		MyStreamWriter->Close();

	}

	
	/* ------ zamìøení objektù --------------------------------------------------------------------------------------------------------------------*/
	void c_vision::zamereni(){
		
		Mat src; Mat src_gray;
		int thresh = 70;
		int max_thresh = 255;

		//take_photo("1.jpg");
		
		this->frame = cvQueryFrame( this->capture );	
		this->birds_image = this->frame;
		src = this->bird_eye_f_picture();
	
		//zde zaèíná algoritmus pro zamìøení objektù
		/// Load source image and convert it to gray
		//src = imread( "bird_eye.jpg", 1 );
		/// Convert image to gray and blur it
		cvtColor( src, src_gray, CV_BGR2GRAY );
		blur( src_gray, src_gray, cv::Size(3,3) );
		/// Create Window
		char* source_window = "Source";
		//namedWindow( source_window, CV_WINDOW_AUTOSIZE );
		//imshow( source_window, src );
		//createTrackbar( " Threshold:", "Source", &thresh, max_thresh, this->vyhledani_kontur );
		

		
	
		RNG rng(12345);
		Mat threshold_output;
		vector<vector<cv::Point> > contours;
		vector<Vec4i> hierarchy;
		/// Detect edges using Threshold
		threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );
		/// Find contours
		findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
		/// Approximate contours to polygons + get bounding rects and circles
		vector<vector<cv::Point> > contours_poly( contours.size() );
		vector<Rect> boundRect( contours.size() );
		vector<Point2f>center( contours.size() );
		vector<float>radius( contours.size() );
		for( int i = 0; i < contours.size(); i++ )
		{ 
			approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
			boundRect[i] = boundingRect( Mat(contours_poly[i]) );
			minEnclosingCircle( contours_poly[i], center[i], radius[i] );
		}

		/// Draw polygonal contour + bonding rects + circles
		Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
	
	
		
		int pocitadlo=0;
		int max_radius=200;
		int min_radius=20;
		for( int i = 0; i< contours.size(); i++ )
		{
			if((int)radius[i]<max_radius && (int)radius[i]>min_radius)// pokud je polomìr menší než ...
			{
				//cout << center[i]<<endl;
				cv::Point pt =center[i];
				//cout << pt.x << ", " << pt.y << endl;
				this->souradnice[pocitadlo]=pt.x;
				pocitadlo++;
				this->souradnice[pocitadlo]=pt.y;
				pocitadlo++;
			}
			
			
		
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, cv::Point() );
		//rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
		if((int)radius[i]<max_radius && (int)radius[i]>min_radius) circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
		}
		this->souradnice[pocitadlo]=9999;
		
		//uložení do souboru
		//to_txt(cisla,"data.txt");

		/// Show in a window
		//namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
		//imshow( "Contours", drawing );
		
		Scalar color = Scalar( 255, 0, 0 );
		for( int i = 0; i< contours.size(); i++ )
		{
			if((int)radius[i]<max_radius && (int)radius[i]>min_radius) circle( src, center[i], (int)radius[i], color, 4, 8, 0 );
		}
		//namedWindow( "Test", CV_WINDOW_AUTOSIZE );
		//imshow( "Test", src );
		this->obr_zamereni = cvCloneImage(&(IplImage)src);
		
		// pøepoèet px na cm  
		for(int i=0;i<1000;i++)
        {
                if ( this->souradnice[i]==9999 ) break; // detekce posledního bodu v poli cisla[]
                if ( (i%2)==0 || i==0)
                {
                        this->souradnice[i]-=this->posun_osy_x_px;
                        this->souradnice[i]*=(-1);
                }
                this->souradnice[i]=this->souradnice[i]*this->meritko_px_na_cm;


                if ( (i%2)==1 )
                {
                        this->souradnice[i]+=this->odsazeni_kal_soustavy; // pøiètení vzdálenosti od hrany kalibraèní soustavy k poèátku reálné osy
                        
						//pohyb( souradnice_real[i], 0, souradnice_real[i-1], "vezmi");

                        //pohyb( 3, 10, 20, "poloz");// poloha pro pøesun
                }
        }

	    
		
	}

	
}