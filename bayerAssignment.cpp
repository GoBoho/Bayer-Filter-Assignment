//g++ -o bayerAssignment.exe bayerAssignment.cpp -O2 -lgdi32

#include <iostream>
#include "CImg_latest\Cimg-2.8.2\CImg.h"

using namespace cimg_library;
using namespace std;

int main() {
  CImg<unsigned char> orig("cherryBlossoms.bmp");
  //Create empty image to fill in with colored Bayer Filter
  CImg<unsigned char> bayerFilter(orig.width(), orig.height(), 1, 3, 0);
  
  //Copy over red intensities (every other pixel of every other row)
  //Fill in here//  
  for (int i = 1; i < orig.width(); i+=2){
	  for(int j = (i%1); j < orig.height(); j+=2){
		 //Copy over green channel to 0
		 bayerFilter(i,j,0,1) = 0.0; 
		 //red not zero
		 bayerFilter(i,j,0,0) = orig(i,j,0,0);
		 bayerFilter(i,j,0,2) = 0.0;
	  }
  }
  
  //Copy over blue intensities (every other pixel of every other row)
  //Fill in here//  
  for (int i = 0; i < orig.width(); i+=2){
	  for(int j = (i%1)+1; j < orig.height(); j+=2){
		 //Copy over green channel to 0
		 bayerFilter(i,j,0,1) = 0.0; 
		 //blue not zero
		 bayerFilter(i,j,0,0) =0.0;
		 bayerFilter(i,j,0,2) = orig(i,j,0,2);
	  }
  }
  
  //Copy over green intensities (every other pixel)
  for (int i = 0; i < orig.width(); i++){
	  for(int j = (i%2); j < orig.height(); j+=2){
		 //Copy over green channel intensity for this pixel 
		 bayerFilter(i,j,0,1) = orig(i,j,0,1); 
		 //red and blue are zero
		 bayerFilter(i,j,0,0) = 0.0;
		 bayerFilter(i,j,0,2) = 0.0;
	  }
  }
  
  //Display and save filtered image
  CImgDisplay disp(bayerFilter); 
  while (!disp.is_closed()){
      disp.wait(); 
  }
  bayerFilter.save("bayerFilter.bmp");
  
////Reconstruct image from filter/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Fill in here//
  
  CImg<unsigned char> bFilter("bayerFilter.bmp");
  CImg<unsigned char> reconImage(bFilter.width(), bFilter.height(), 1, 3, 0);
  
  //Red
  for (int i = 1; i < bFilter.width(); i+=2){
	  for(int j = (i%1); j < bFilter.height(); j+=2){
		 reconImage(i, j, 0, 0) = bFilter(i,j,0,0); //Red
		 reconImage(i, j, 0, 2) =(bFilter(i-1,j-1,0,2)+bFilter(i+1,j-1,0,2)+bFilter(i-1,j+1,0,2)+bFilter(i+1,j+1,0,2))/4.0; //Blue
		 reconImage(i, j, 0, 1) = (bFilter(i-1,j,0,1)+bFilter(i+1,j,0,1)+bFilter(i,j-1,0,1)+bFilter(i,j+1,0,1))/4.0; //Green
	  }
  }
  
  //Blue
  for (int i = 0; i < bFilter.width(); i+=2){
	  for(int j = (i%1)+1; j < bFilter.height(); j+=2){
		 reconImage(i, j, 0, 2) = bFilter(i,j,0,2); //Blue
		 reconImage(i, j, 0, 1) = (bFilter(i-1,j,0,1)+bFilter(i+1,j,0,1)+bFilter(i,j-1,0,1)+bFilter(i,j+1,0,1))/4.0; //Green
		 reconImage(i, j, 0, 0) = (bFilter(i-1,j-1,0,0)+bFilter(i+1,j-1,0,0)+bFilter(i-1,j+1,0,0)+bFilter(i+1,j+1,0,0))/4.0; //Red
	  }
  }
  
  //Green
  for (int i = 0; i < bFilter.width(); i++){
	  for(int j = (i%2); j < bFilter.height(); j+=2){
		  reconImage(i, j, 0, 1) = (bFilter(i-1,j-1,0,1)+bFilter(i+1,j-1,0,1)+bFilter(i-1,j+1,0,1)+bFilter(i+1,j+1,0,1)+bFilter(i,j,0,1))/5.0; //Green 
		  //cout << i%2;
		  if ((i%2)==0){
			 reconImage(i, j, 0, 0) = (bFilter(i-1,j,0,0)+bFilter(i+1,j,0,0))/2.0; //Red 
			 reconImage(i, j, 0, 2) = (bFilter(i,j-1,0,2)+bFilter(i,j+1,0,2))/2.0; //Blue 
		  }
		 
		  if ((i%2)==1){
			 reconImage(i, j, 0, 0) = (bFilter(i,j+1,0,0)+bFilter(i,j+1,0,0))/2.0; //Red 
			 reconImage(i, j, 0, 2) = (bFilter(i-1,j,0,2)+bFilter(i+1,j,0,2))/2.0; //Blue 
		  }
	  }
  }

  //Display and save reconstructed image  
  //Fill in here//
  CImgDisplay reDisp(reconImage); 
  while (!reDisp.is_closed()){
      reDisp.wait(); 
  }
  reconImage.save("reconstructedImage.bmp");
  
return 0;
}
