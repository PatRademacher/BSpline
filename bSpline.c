/*
    FPToolkit.c : A simple set of graphical tools.
    FPToolkitDemo.c 
    Copyright (C) 2018  Ely

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License (version 3)
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/





/*

This code assumes an underlying X11 environment.

       Most freshly installed unbuntu environments do not have
       the X11 developr stuff they'll need to do graphics.
       To download X11 developer stuff, connect to the internet and 
       issue the following two commands.  Each will ask for your password
       and each will take a few minutes.  At some point it might even
       look like nothing is happening....be patient :
       
sudo  apt-get  install  libx11-dev     

sudo  apt-get  install  xorg-dev

*/




/*
If this file and the file, FPToolkit.c, are in the
same directory that you are trying to compile in,  
do the following :

cc  FPToolkitDemo.c   -lm  -lX11

*/


#include  "FPToolkit.c"


int main()
{
   int    swidth, sheight ;
   double p[2] ;
   double x[100],y[100] ;
   double X,Y ;
   int counter = 0;
   double numeratorx;
   double denominatorx;
   
   // must do this before you do 'almost' any other graphical tasks 
   swidth = 800 ;  sheight = 800 ;
   G_init_graphics (swidth,sheight) ;  // interactive graphics

   
   // clear the screen in a given color
   G_rgb (0.3, 0.3, 0.3) ; // dark gray
   G_clear ();

   G_rgb (0, 0, 0);
   G_fill_rectangle(700, 0, 100, 800);


   G_rgb(1,1,0);  
   for (int q = 0; q < 100; q++){
      G_wait_click(p);
      if (p[0] >= 700){break;}
      else{
         x[q] = p[0] ; y[q] = p[1];
         G_fill_circle(x[q],y[q],2);
         counter += 1;
      }
   }
 
   G_rgb(1,0,0);
   if (counter > 1){
   for (X = 0; X < 700; X++){
   for (int w = 0; w < counter; w++){
      for (int v = 0; v < counter; v++){
         if (v != w){
            if (w == 0 && v == 1){
               numeratorx = (X - x[1]);
               printf("\n numeratorx = %lf - %lf = %lf", X, x[1], numeratorx);
               denominatorx = (x[0] - x[1]);
               }
            else if (v == 0) {
                 numeratorx = (X - x[0]);
                 denominatorx = (x[w] - x[0]);}
            else{
               double multiplier = (X - x[v]);
               numeratorx = numeratorx * multiplier;
               multiplier = (x[w] - x[v]);
               denominatorx = denominatorx * multiplier;
            }    
         } 
              
        }
        Y += y[w] * numeratorx / denominatorx;
      }
      G_point(X,Y);
      Y = 0;
      }
   }

   else if (counter == 1){
      for (X = 0 ; X < 700 ; X++) {
      Y = y[0];
      G_point(X,Y);}
   }
  
   else if (counter <= 0){
      printf("\n\nYou didn't input any points silly!\n\n");
   }

   int key;   
   key =  G_wait_key(); // pause so user can see results

   G_save_image_to_file("three_point_quadratic.xwd") ;
}

