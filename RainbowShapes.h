

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <ErriezRotaryHalfStep.h> 


//***** Variables **************************
unsigned char flag;
unsigned char pos, next_slot, current_pos, last_pos;
unsigned char result;
unsigned char EncVal;
unsigned char EncValLast = 0;
int countLast = 0;
unsigned char ColorChoice;
unsigned char next_player;
unsigned int counter;
unsigned int buttoncount;
unsigned char player;
unsigned char win[5];
unsigned char PlayerColor[3][3];
unsigned char MemoryColors[66][4]; 



#define PIN 4            // D2
#define BUTTON 14        // D5
#define ROTARY_PIN1  13  // D7
#define ROTARY_PIN2  12  // D6

#define MATRIX_WIDTH 4
#define MATRIX_HEIGHT 4
#define STARTING_PIXEL 1
#define MIN_ENC_VAL 1
#define MAX_ENC_VAL 64

#define LED_COUNT 64
#define num_of_pixels 64  //(sacrificial LED)

#define red       255, 0, 0
#define green     0, 255, 0
#define blue      0, 0, 255
#define black     0 ,0, 0
#define grey      1, 1, 1
#define dimwhite  1, 1, 1
#define midwhite  127, 127, 127
#define white     255, 255, 255
#define coolwhite 255, 255, 255
#define yellow    255, 138, 0
#define cyan      0, 255, 255
#define magenta   255, 0, 255
#define gold      255, 90, 0
#define orange    220, 40, 0
#define olive     100, 220, 47
#define turq      35, 255, 30
#define lime      15, 70, 10
#define skyblue   65, 176, 255
#define purple    70, 0, 120

unsigned int a, c, r, g, b, center;
unsigned int xa, xb, xc, ya, yb, yc;
unsigned int z, x, y, i, times, tempcolor, tempcolor1, tempcolor2;
unsigned char count;
unsigned char zpos, xpos, ypos;

unsigned char corner1[4] = {0,0,3,3};
unsigned char corner2[4] = {0,3,0,3};
unsigned char center1[4] = {1,1,2,2};
unsigned char center2[4] = {1,2,1,2};
unsigned char circle1[4] = {1,0,0,1};
unsigned char circle2[4] = {0,1,2,3};
unsigned char circle3[4] = {2,3,3,2};
unsigned char circle4[4] = {0,1,2,3};

unsigned char zcol1[4] = {0,0,1,1};
unsigned char xbar1[4] = {0,1,0,1};
unsigned char ybar1[4] = {0,0,0,0};

unsigned char zcol2[4] = {0,0,1,1};
unsigned char xbar2[4] = {0,1,0,1};
unsigned char ybar2[4] = {0,1,0,1};

unsigned char zcol3[4] = {0,0,1,1};
unsigned char xbar3[4] = {0,0,0,0};
unsigned char ybar3[4] = {0,1,0,1};

unsigned char zcol4[4] = {0,0,1,1};
unsigned char xbar4[4] = {1,1,1,1};
unsigned char ybar4[4] = {0,1,0,1};

unsigned char zcol5[4] = {0,0,1,1};
unsigned char xbar5[4] = {0,1,0,1};
unsigned char ybar5[4] = {1,1,1,1};

unsigned char zcol6[4] = {0,0,1,1};
unsigned char xbar6[4] = {1,0,1,0};
unsigned char ybar6[4] = {0,1,0,1};

unsigned char spinover[12]   = {0,0,0,0,1,2,3,3,3,3,2,1};
unsigned char spinaround[12] = {0,1,2,3,3,3,3,2,1,0,0,0};
unsigned char rotateX[25]    = {0,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,1,1,2,2,2,2,1,1};
unsigned char rotateZ[25]    = {0,0,1,2,3,1,1,2,2,2,2,1,1,3,2,1,0,3,2,1,0,3,2,1,0};


unsigned char stepg[10]         = {0,     0, 4, 8, 12, 16, 20, 24, 28};
unsigned char planeX[30]        = {0,     0,1,2,3, 0,1,2,3, 0,1,2,3, 0,1,2,3, 0,1,1,2, 0,0,1,1, 0,0,0,0};
unsigned char planeZ[30]        = {0,     0,0,0,0, 0,0,1,1, 0,1,1,2, 0,1,2,3, 0,1,2,3, 0,1,2,3, 0,1,2,3};
unsigned char planebackX[30]    = {0,     0,0,0,0, 1,1,0,0, 2,1,1,0, 3,2,1,0, 3,2,1,0, 3,2,1,0, 3,2,1,0};
unsigned char planebackZ[30]    = {0,     0,1,2,3, 0,1,2,3, 0,1,2,3, 0,1,2,3, 1,2,2,3, 2,2,3,3, 3,3,3,3};
unsigned char planebackY[30]    = {0,     3,3,3,3, 2,2,3,3, 1,2,2,3, 0,1,2,3, 0,1,2,3, 0,1,2,3, 0,1,2,3};


unsigned char xsquarechase[16] = {0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,1};
unsigned char ysquarechase[16] = {0,0,0,1,2,2,2,2,2,2,2,1,0,0,0,0};
unsigned char zsquarechase[16] = {0,1,2,2,2,1,0,0,0,1,2,2,2,1,0,0};

unsigned char zpixelchase[25] = {0,1,2,3,3,3,3,2,1,0,0,0,0,1,2,3,3,3,3,2,1,0,0,0};
unsigned char xpixelchase[25] = {0,0,0,0,0,0,0,0,0,0,1,2,3,3,3,3,3,3,3,3,3,3,2,1};
unsigned char ypixelchase[25] = {0,0,0,0,1,2,3,3,3,3,3,3,3,3,3,3,2,1,0,0,0,0,0,0};

unsigned char colors[12][3] = {
                            {255, 0, 0},      // red
                            {0, 255, 0},      // green
                            {0, 0, 255},      // blue
                            {255, 255, 255},  // white
                            {255, 255, 0},    // yellow
                            {255, 0, 255},    // magenta
                            {0, 255, 255},    // cyan
                            {150, 0, 170},    // purple                           
                            {255, 30, 0},     // orange 
                            {255, 100, 0},    // gold
                            {14, 255, 10},    // lime                           
                            {255, 141, 157},  // pink                            
                            };

#define red     255, 0, 0
#define	green	  0, 255, 0
#define	blue	  0, 0, 255
#define	black	  0 ,0, 0
#define	grey	  40, 40, 40
#define	white	  255, 255, 255
#define	yellow	255, 255, 0
#define	cyan	  0, 255, 255
#define	magenta	  255, 0, 255
#define	gold	  255, 110, 0
#define	orange	255, 40, 0
#define	olive	  100, 220, 47
#define	turq	  35, 255, 30
#define	lime	  14, 255, 10
#define	skyblue	  65, 176, 255
#define	purple	  70, 0, 120
#define	pink	  255, 141, 157
#define	crimson	  220, 3, 3
#define darkred   30, 0, 0 

void setPixelZXY(unsigned char zaxis, unsigned char x, unsigned char y, unsigned char r, unsigned char g, unsigned char b); 
void SelectPixel(unsigned char r, unsigned char g, unsigned char b, unsigned pos);
void ClearPixel(unsigned char x, unsigned char y, unsigned char z);
void ClearCube();

RotaryHalfStep rotary(ROTARY_PIN1, ROTARY_PIN2);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(MATRIX_WIDTH, MATRIX_HEIGHT, 4, 1, PIN,
                            NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_ROWS + NEO_TILE_PROGRESSIVE +
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            NEO_RGB + NEO_KHZ800);
/*
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(MATRIX_WIDTH, MATRIX_HEIGHT, 4, 1, PIN,
                            NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_ROWS + NEO_TILE_ZIGZAG +
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                            NEO_RGB + NEO_KHZ800);                            
*/
Adafruit_NeoPixel strip = Adafruit_NeoPixel(num_of_pixels, PIN, NEO_RGB + NEO_KHZ800);
//************************************************************************************************************************************* 
// Quad Walker
void QWPos1(unsigned char zpos, unsigned char xpos, unsigned char ypos, unsigned char r, unsigned char g, unsigned char b)
{
     for(i = 0; i < 4; i++)
        {
        setPixelZXY(zcol1[i] + zpos, xbar1[i] + xpos, ybar1[i] + ypos, r, g, b);  
        }    
}
//************************************************************************************************************************************* 
void QWPos2(unsigned char zpos, unsigned char xpos, unsigned char ypos, unsigned char r, unsigned char g, unsigned char b)
{
     for(i = 0; i < 4; i++)
        {
        setPixelZXY(zcol2[i] + zpos, xbar2[i] + xpos, ybar2[i] + ypos, r, g, b);  
        }  
}
//************************************************************************************************************************************* 
void QWPos3(unsigned char zpos, unsigned char xpos, unsigned char ypos, unsigned char r, unsigned char g, unsigned char b)
{
     for(i = 0; i < 4; i++)
        {
        setPixelZXY(zcol3[i] + zpos, xbar3[i] + xpos, ybar3[i] + ypos, r, g, b);  
        }  
}
//************************************************************************************************************************************* 
void QWPos4(unsigned char zpos, unsigned char xpos, unsigned char ypos, unsigned char r, unsigned char g, unsigned char b)
{
     for(i = 0; i < 4; i++)
        {
        setPixelZXY(zcol4[i] + zpos, xbar4[i] + xpos, ybar4[i] + ypos, r, g, b);  
        }  
}
//************************************************************************************************************************************* 
void QWPos5(unsigned char zpos, unsigned char xpos, unsigned char ypos, unsigned char r, unsigned char g, unsigned char b)
{
     for(i = 0; i < 4; i++)
        {
        setPixelZXY(zcol5[i] + zpos, xbar5[i] + xpos, ybar5[i] + ypos, r, g, b);  
        }  
}
//************************************************************************************************************************************* 
void QWPos6(unsigned char zpos, unsigned char xpos, unsigned char ypos, unsigned char r, unsigned char g, unsigned char b)
{
     for(i = 0; i < 4; i++)
        {
        setPixelZXY(zcol6[i] + zpos, xbar6[i] + xpos, ybar6[i] + ypos, r, g, b);  
        }  
}
//************************************************************************************************************************************* 
void HorizXBar(unsigned char z, unsigned char xwidth, unsigned char y, unsigned char r, unsigned char g, unsigned char b)
{ 
//   for(x = 0; x < xwidth; x++)
//       {  
       setPixelZXY(z, xwidth, y, r, g, b); //uses 24bit RGB color Code
//       } 
}       
//************************************************************************************************************************************* 
void HorizYBar(unsigned char z, unsigned char x, unsigned char ywidth, unsigned char r, unsigned char g, unsigned char b)
{
//   for(y = 0; y < ywidth; y++)
//       {  
       setPixelZXY(z, x, ywidth, r, g, b); //uses 24bit RGB color Code
//       }  
}        
//************************************************************************************************************************************* 
void VertZBar(unsigned char zwidth, unsigned char x, unsigned char y, unsigned char r, unsigned char g, unsigned char b)
{
//   for(z = 0; z < zwidth; z++)
//       {  
       setPixelZXY(zwidth, x, y, r, g, b); //uses 24bit RGB color Code
//       }   
} 
//***********************************************************************************
void RotatePlanes(unsigned char r, unsigned char g, unsigned char b, int spd)
{
int group, row, i;
//***********************************************  
// From Right Up to the Top 
for(group = 1; group < 8; group++)
   {
   row = stepg[group];
   ClearCube();  
   for (i = 1; i < 5; i++)              
       {       
       HorizXBar(planebackZ[i + row], planebackX[i + row], 0, r, g, b);
       HorizXBar(planebackZ[i + row], planebackX[i + row], 1, r, g, b); 
       HorizXBar(planebackZ[i + row], planebackX[i + row], 2, r, g, b);              
       HorizXBar(planebackZ[i + row], planebackX[i + row], 3, r, g, b);        
       matrix.show();
       }     
       delay(spd);
        
   }

//***********************************************  
//  From Top Dn to the Front
for(group = 7; group >= 1; group--)
   {
   row = stepg[group];
   ClearCube();  
   for (i = 1; i < 5; i++)              
       {       
       HorizXBar(planebackZ[i + row], 0, planebackX[i + row], r, g, b);
       HorizXBar(planebackZ[i + row], 1, planebackX[i + row], r, g, b); 
       HorizXBar(planebackZ[i + row], 2, planebackX[i + row], r, g, b);              
       HorizXBar(planebackZ[i + row], 3, planebackX[i + row], r, g, b);        
       matrix.show();
       }      
       delay(spd);
       
   }

//***********************************************  
//  Turn From Front to the Left
for(group = 1; group < 8; group++)
   {
   ClearCube();  
   row = stepg[group];
   
   for (i = 1; i < 5; i++)                
       {       
       HorizXBar(0, planebackZ[i + row], planebackX[i + row], r, g, b);
       HorizXBar(1, planebackZ[i + row], planebackX[i + row], r, g, b); 
       HorizXBar(2, planebackZ[i + row], planebackX[i + row], r, g, b);              
       HorizXBar(3, planebackZ[i + row], planebackX[i + row], r, g, b);        
       matrix.show();
       }     
       delay(spd);
       
   }

//***********************************************  
//  Turn From Left Up to Back
for(group = 7; group >= 1; group--)
   {
   ClearCube();  
   row = stepg[group];
   
   for (i = 1; i < 5; i++)                
       {       
       HorizXBar(0, planebackZ[i + row], planebackY[i + row], r, g, b);
       HorizXBar(1, planebackZ[i + row], planebackY[i + row], r, g, b); 
       HorizXBar(2, planebackZ[i + row], planebackY[i + row], r, g, b);              
       HorizXBar(3, planebackZ[i + row], planebackY[i + row], r, g, b);        
       matrix.show();
       }     
       delay(spd);
       
   }

//***********************************************  
//  Turn From Back Dn to the Bottom
for(group = 7; group >= 1; group--)
//for(group = 1; group < 8; group++)
   {
   ClearCube();  
   row = stepg[group];
   
   for (i = 1; i < 5; i++)                
       {       
       HorizXBar(planeZ[i + row], 0, planebackZ[i + row], r, g, b);
       HorizXBar(planeZ[i + row], 1, planebackZ[i + row], r, g, b); 
       HorizXBar(planeZ[i + row], 2, planebackZ[i + row], r, g, b);              
       HorizXBar(planeZ[i + row], 3, planebackZ[i + row], r, g, b);        
       matrix.show();
       }     
       delay(spd);
       
   }

//***********************************************  
//  Turn From Bottom Up to the Right
for(group = 1; group < 8; group++)
   {
   row = stepg[group];
   ClearCube();  
   for (i = 1; i < 5; i++)              
       {       
       HorizXBar(planeZ[i + row], planeX[i + row], 0, r, g, b);
       HorizXBar(planeZ[i + row], planeX[i + row], 1, r, g, b); 
       HorizXBar(planeZ[i + row], planeX[i + row], 2, r, g, b);              
       HorizXBar(planeZ[i + row], planeX[i + row], 3, r, g, b);        
       matrix.show();
       }      
       delay(spd);
       
   } 
     
} 
//***************************************************************************************
void demoMoves()
{
  int group, row;

// Counter Clockwise Bar Rotate 
tempcolor = 1;

//***********************************************  
//  Turn From Back Up to the Top
for(group = 1; group < 8; group++)
   {
   ClearCube();  
   row = stepg[group];
   
   for (i = 1; i < 5; i++)                
       {       
       HorizXBar(planebackZ[i + row], 0, planebackY[i + row], r, g, b);
       HorizXBar(planebackZ[i + row], 1, planebackY[i + row], r, g, b); 
       HorizXBar(planebackZ[i + row], 2, planebackY[i + row], r, g, b);              
       HorizXBar(planebackZ[i + row], 3, planebackY[i + row], r, g, b);        
       matrix.show();
       }     
       delay(50);
       
   }
//***********************************************  
//  Turn From Left Up to Back
for(group = 7; group >= 1; group--)
   {
   ClearCube();  
   row = stepg[group];
   
   for (i = 1; i < 5; i++)                
       {       
       HorizXBar(0, planebackZ[i + row], planebackY[i + row], r, g, b);
       HorizXBar(1, planebackZ[i + row], planebackY[i + row], r, g, b); 
       HorizXBar(2, planebackZ[i + row], planebackY[i + row], r, g, b);              
       HorizXBar(3, planebackZ[i + row], planebackY[i + row], r, g, b);        
       matrix.show();
       }     
       delay(50);
       
   }
//***********************************************  
//  Turn From Front Up to the Top
for(group = 1; group < 8; group++)
   {
   ClearCube();  
   row = stepg[group];
   
   for (i = 1; i < 5; i++)                
       {       
       HorizXBar(planebackZ[i + row], 0, planebackX[i + row], r, g, b);
       HorizXBar(planebackZ[i + row], 1, planebackX[i + row], r, g, b); 
       HorizXBar(planebackZ[i + row], 2, planebackX[i + row], r, g, b);              
       HorizXBar(planebackZ[i + row], 3, planebackX[i + row], r, g, b);        
       matrix.show();
       }     
       delay(50);
       
   }   
//***********************************************  
//  Turn From Top Dn to Front
//for(group = 7; group >= 1; group--)
for(group = 1; group < 8; group++)
   {
   ClearCube();  
   row = stepg[group];
   
   for (i = 1; i < 5; i++)                
       {
       // z, x, y       
       HorizXBar(planebackZ[i + row], 0, planebackX[i + row], r, g, b);
       HorizXBar(planebackZ[i + row], 1, planebackX[i + row], r, g, b); 
       HorizXBar(planebackZ[i + row], 2, planebackX[i + row], r, g, b);              
       HorizXBar(planebackZ[i + row], 3, planebackX[i + row], r, g, b);        
       matrix.show();
       }     
       delay(50);
       
   }
//***********************************************  
// From Right Up to the Left 
for(group = 1; group < 8; group++)
   {
   row = stepg[group];
   ClearCube();  
   for (i = 1; i < 5; i++)              
       {       
       HorizXBar(planebackZ[i + row], planebackX[i + row], 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizXBar(planebackZ[i + row], planebackX[i + row], 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]); 
       HorizXBar(planebackZ[i + row], planebackX[i + row], 2, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);              
       HorizXBar(planebackZ[i + row], planebackX[i + row], 3, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);        
       matrix.show();
       }     
       delay(50);
        
   } 

//***********************************************  
// From Top Dn to the Right
for(group = 7; group >= 1; group--)
   {
   row = stepg[group];
   ClearCube();  
   for (i = 1; i < 5; i++)              
       {       
       HorizXBar(planebackZ[i + row], planebackX[i + row], 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizXBar(planebackZ[i + row], planebackX[i + row], 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]); 
       HorizXBar(planebackZ[i + row], planebackX[i + row], 2, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);              
       HorizXBar(planebackZ[i + row], planebackX[i + row], 3, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);        
       matrix.show();
       }      
       delay(50);
       
   }

//***********************************************   
// From Right Dn to the Left
for(group = 7; group >= 1; group--)
   {
   row = stepg[group];
   ClearCube();  
   for (i = 1; i < 5; i++)              
       {       
       HorizXBar(planeZ[i + row], planeX[i + row], 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizXBar(planeZ[i + row], planeX[i + row], 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]); 
       HorizXBar(planeZ[i + row], planeX[i + row], 2, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);              
       HorizXBar(planeZ[i + row], planeX[i + row], 3, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);        
       matrix.show();
       }     
       delay(50);
        
   } 

//***********************************************   
// From Bottom Up to the Right
for(group = 1; group < 8; group++)
   {
   row = stepg[group];
   ClearCube();  
   for (i = 1; i < 5; i++)              
       {       
       HorizXBar(planeZ[i + row], planeX[i + row], 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizXBar(planeZ[i + row], planeX[i + row], 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]); 
       HorizXBar(planeZ[i + row], planeX[i + row], 2, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);              
       HorizXBar(planeZ[i + row], planeX[i + row], 3, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);        
       matrix.show();
       }      
       delay(50);
       
   }   

//***********************************************  
//  Turn From Right Up to Top
for(group = 1; group < 8; group++)
   {
   ClearCube();  
   row = stepg[group];
   
   for (i = 1; i < 5; i++)                
       {       
       HorizXBar(planebackZ[i + row], planebackX[i + row], 0, r, g, b);
       HorizXBar(planebackZ[i + row], planebackX[i + row], 1, r, g, b); 
       HorizXBar(planebackZ[i + row], planebackX[i + row], 2, r, g, b);              
       HorizXBar(planebackZ[i + row], planebackX[i + row], 3, r, g, b);        
       matrix.show();
       }     
       delay(50);
       
   }   

}// End demo       
//************************************************************************************************************************************* 
void Fill_Solid(unsigned char r, unsigned char g, unsigned char b, int tdelay )
{
 for(i = 0; i < 4; i++)
   {
   for(z = 0; z < 4; z++)
     { 
     for(x = 0; x < 4; x++)
       {
       for(y = 0; y < 4; y++)
         {  
         //Set (Z,X,Y):(0,0,0) 
         setPixelZXY(z, x, y, r, g, b); //uses 24bit RGB color Code
         }    
       }      
     }      
   }
 matrix.show();     
 delay(tdelay); 
} 
//*******************************************************************************************  
// Cube Demo, Clockwise, Solid Colors
void CubeDemoCW(unsigned char r, unsigned char g, unsigned char b, unsigned char speeds)
{
   
   for(i = 0; i < 16; i++)
      { 
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 0, ysquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 0, ysquarechase[i] + 1, r, g, b);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 1, ysquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 1, ysquarechase[i] + 1, r, g, b);  
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 0, ysquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 0, ysquarechase[i] + 1, r, g, b);  
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 1, ysquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 1, ysquarechase[i] + 1, r, g, b);
      matrix.show();          
      delay(speeds);
      ClearCube();
     }
  
}
//*******************************************************************************************  
// Cube Demo, Counter-Clockwise, Solid Colors
void CubeDemoCCW(unsigned char r, unsigned char g, unsigned char b, unsigned char speeds)
{
   
   for(i = 0; i < 16; i++)
      { 
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 0, xsquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 0, xsquarechase[i] + 1, r, g, b);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 1, xsquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 1, xsquarechase[i] + 1, r, g, b);  
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 0, xsquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 0, xsquarechase[i] + 1, r, g, b);  
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 1, xsquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 1, xsquarechase[i] + 1, r, g, b);  
      matrix.show();        
      delay(speeds);
      ClearCube();
     }
  
}
//*******************************************************************************************  
// Cube Demo, Mirror Image Effect
void CubeDemoxb(unsigned char r, unsigned char g, unsigned char b, unsigned char speeds)
{   
   for(i = 0; i < 16; i++)
      { 
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 0, ysquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 0, xsquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 0, ysquarechase[i] + 1, r, g, b);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 0, xsquarechase[i] + 1, r, g, b);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 1, ysquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 1, xsquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 1, ysquarechase[i] + 1, r, g, b); 
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 1, xsquarechase[i] + 1, r, g, b); 
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 0, ysquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 0, xsquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 0, ysquarechase[i] + 1, r, g, b);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 0, xsquarechase[i] + 1, r, g, b);
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 1, ysquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 1, xsquarechase[i] + 0, r, g, b);
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 1, ysquarechase[i] + 1, r, g, b);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 1, xsquarechase[i] + 1, r, g, b);
      matrix.show(); 
      delay(speeds);
      ClearCube();
     }  
}
//*******************************************************************************************  
// Cube Demo, Mirror Image Effect, Random Colors
void CubeDemoxbRan(unsigned char r, unsigned char g, unsigned char b, unsigned char speeds)
{   
   for(i = 0; i < 16; i++)
      {
      tempcolor = random(12);   
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 0, ysquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 0, xsquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 0, ysquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 0, xsquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 1, ysquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 1, xsquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 1, ysquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]); 
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 1, xsquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]); 
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 0, ysquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 0, xsquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 0, ysquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 0, xsquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 1, ysquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 1, xsquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 1, ysquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 1, xsquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      matrix.show(); 
      delay(speeds);
      ClearCube();
     }  
}
//*******************************************************************************************  
// Cube Demo, Mirror Image Effect, Random Colors
void CubeDemoxbRan2(unsigned char r, unsigned char g, unsigned char b, unsigned char speeds)
{   
   for(i = 0; i < 16; i++)
      {
      tempcolor = random(12);
      tempcolor1 = random(12);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 0, ysquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 0, xsquarechase[i] + 0, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 0, ysquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 0, xsquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 1, ysquarechase[i] + 0, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 1, xsquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 1, ysquarechase[i] + 1, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]); 
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 1, xsquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]); 
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 0, ysquarechase[i] + 0, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 0, xsquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 0, ysquarechase[i] + 1, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 0, xsquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 1, ysquarechase[i] + 0, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 1, xsquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 1, ysquarechase[i] + 1, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 1, xsquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      matrix.show(); 
      delay(speeds);
      ClearCube();
     }  
}
//*******************************************************************************************  
// Cube Demo, Counter-Clockwise, Random Colors
void CubeDemoRanCCW(unsigned char r, unsigned char g, unsigned char b, unsigned char speeds)
{
   
   for(i = 0; i < 16; i++)
     { 
      tempcolor = random(12); 
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 0, ysquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 0, ysquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 1, ysquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, xsquarechase[i] + 1, ysquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);  
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 0, ysquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 0, ysquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);  
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 1, ysquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 1, xsquarechase[i] + 1, ysquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);         
      matrix.show(); 
      delay(speeds);
      ClearCube();
     }
  
}
//*******************************************************************************************  
// Cube Demo, Clockwise, Solid Colors
void CubeDemoRanCW(unsigned char r, unsigned char g, unsigned char b, unsigned char speeds)
{
   
   for(i = 0; i < 16; i++)
      { 
      tempcolor = random(12);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 0, xsquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 0, xsquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 1, xsquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 0, ysquarechase[i] + 1, xsquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);  
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 0, xsquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 0, xsquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);  
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 1, xsquarechase[i] + 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
      setPixelZXY(zsquarechase[i] + 1, ysquarechase[i] + 1, xsquarechase[i] + 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);         
      matrix.show(); 
      delay(speeds);
      ClearCube();
     }
  
}
//*******************************************************************************************  
// Random Pixel Demo, Solid Colors
void PixelDemoRan(unsigned char r, unsigned char g, unsigned char b, unsigned char speeds)
{  
   for(i = 0; i < 25; i++)
     { 
         setPixelZXY(random (zpixelchase[i] + 3), random (xpixelchase[i] + 3), random(ypixelchase[i] + 3), r, g, b);        
         matrix.show(); 
         delay(speeds);
         ClearCube();
     }  
}
//*******************************************************************************************  
// Random Pixel Demo, Random Colors
void PixelDemoRandom(unsigned char r, unsigned char g, unsigned char b, unsigned char speeds, unsigned char repeats)
{  
   for(i = 0; i < repeats; i++)
     { 
         setPixelZXY(random (zpixelchase[i] + 3), random (xpixelchase[i] + 3), random(ypixelchase[i] + 3), random(r), random(g), random(b));        
         matrix.show(); 
         delay(speeds);
         ClearCube();
     }  
}
//*******************************************************************************************  
// Random Pixel Demo, Random Colors
void PixelDemoRandomHold(unsigned char r, unsigned char g, unsigned char b, unsigned char speeds, unsigned char repeats)
{  
   for(i = 0; i < repeats; i++)
     { 
         setPixelZXY(random (zpixelchase[i] + 3), random (xpixelchase[i] + 3), random(ypixelchase[i] + 3), random(r), random(g), random(b));        
         matrix.show(); 
         delay(speeds);
         //ClearCube();
     }  
}
//*******************************************************************************************  
// Pixel Demo, Clockwise Rotation, Random Colors
void PixelDemoCWRan(unsigned char r, unsigned char g, unsigned char b, unsigned char speeds)
{    
   for(i = 0; i < 25; i++)
     { 
         setPixelZXY(zpixelchase[i] + center, ypixelchase[i] + center, xpixelchase[i] + center, random(r), random(g), random(b));        
         matrix.show(); 
         delay(speeds);
         ClearCube();
     }      
} 
//*******************************************************************************************  
// Pixel Demo, Counter-Clockwise Rotation, Random Colors
void PixelDemoCCWRan(unsigned char r, unsigned char g, unsigned char b, unsigned char speeds)
{    
   for(i = 0; i < 25; i++)
     { 
         setPixelZXY(zpixelchase[i] + center, xpixelchase[i] + center, ypixelchase[i] + center, random(r), random(g), random(b));        
         matrix.show(); 
         delay(speeds);
         ClearCube();
     }      
}

//*******************************************************************************************  
// Pixel Demo, Clockwise Rotation, Solid Colors
void PixelDemoCW(unsigned char r, unsigned char g, unsigned char b, unsigned char speeds)
{
   for(i = 0; i < 25; i++)
     { 
         setPixelZXY(zpixelchase[i] + center, ypixelchase[i] + center, xpixelchase[i] + center, r, g, b);        
         matrix.show(); 
         delay(speeds);
         ClearCube();
     }      
}

//*******************************************************************************************  
// Pixel Demo, Counter-Clockwise Rotation, Solid Colors
void PixelDemoCCW(unsigned char r, unsigned char g, unsigned char b, unsigned char speeds)
{
   for(i = 0; i < 25; i++)
     { 
         setPixelZXY(zpixelchase[i] + center, xpixelchase[i] + center, ypixelchase[i] + center, r, g, b);        
         matrix.show(); 
         delay(speeds);
         ClearCube();
     }      
}
//*******************************************************************************************  
// Flat Plane with Center Square Move Up
void FlatPlaneSqUP(unsigned char r, unsigned char g, unsigned char b, unsigned char rr, unsigned char gg, unsigned char bb, int delayed, char blank)
{
   for(i = 0; i < 4; i++)
      {
      for(y = 0; y < 4; y++)
         {
         for(x = 0; x < 4; x++)
            {
            setPixelZXY(i,x,y,r, g, b); 
            setPixelZXY(i,2,2,rr,gg,bb);
            setPixelZXY(i,1,2,rr,gg,bb); 
            setPixelZXY(i,2,1,rr,gg,bb); 
            setPixelZXY(i,1,1,rr,gg,bb); 
            }
         }
       matrix.show(); 
       delay(delayed);
       if (blank == 1) ClearCube();       
       }
}      
//*******************************************************************************************  
// Flat Plane with Center Square Move Down
void FlatPlaneSqDN(unsigned char r, unsigned char g, unsigned char b, unsigned char rr, unsigned char gg, unsigned char bb, int delayed, char blank)
{     
    for(i = 4; i--;)
       {
       for(y = 0; y < 4; y++)
          {
          for(x = 0; x < 4; x++)
             {
             setPixelZXY(i,x,y,r,g,b); 
             setPixelZXY(i,2,2,rr,gg,bb); 
             setPixelZXY(i,1,2,rr,gg,bb); 
             setPixelZXY(i,2,1,rr,gg,bb); 
             setPixelZXY(i,1,1,rr,gg,bb);          
             }
          }
       matrix.show(); 
       delay(delayed); 
       if (blank == 1) ClearCube();
       }     
}
//*******************************************************************************************  
// Flat Plane with Center Square Move Right
void FlatPlaneSqXDec(unsigned char r, unsigned char g, unsigned char b, unsigned char rr, unsigned char gg, unsigned char bb, int delayed, char blank)
{     
    for(i = 4; i--;)
       {
       for(y = 0; y < 4; y++)
          {
          for(x = 0; x < 4; x++)
             {
             setPixelZXY(x,i,y,r,g,b); 
             setPixelZXY(2,i,2,rr,gg,bb); 
             setPixelZXY(1,i,2,rr,gg,bb); 
             setPixelZXY(2,i,1,rr,gg,bb); 
             setPixelZXY(1,i,1,rr,gg,bb);           
             }
          }
       matrix.show(); 
       delay(delayed); 
       if (blank == 1) ClearCube();
       }     
} 
//*******************************************************************************************  
// Flat Plane with Center Square Move Right
void FlatPlaneSqXInc(unsigned char r, unsigned char g, unsigned char b, unsigned char rr, unsigned char gg, unsigned char bb, int delayed, char blank)
{     
    for(i = 0; i < 4; i++)
       {
       for(y = 0; y < 4; y++)
          {
          for(x = 0; x < 4; x++)
             {
             setPixelZXY(x,i,y,r,g,b); 
             setPixelZXY(2,i,2,rr,gg,bb); 
             setPixelZXY(1,i,2,rr,gg,bb); 
             setPixelZXY(2,i,1,rr,gg,bb); 
             setPixelZXY(1,i,1,rr,gg,bb);          
             }
          }
       matrix.show(); 
       delay(delayed); 
       if (blank == 1) ClearCube();
       }     
}
//*******************************************************************************************  
// Flat Plane with Center Square Move Right
void FlatPlaneSqYDec(unsigned char r, unsigned char g, unsigned char b, unsigned char rr, unsigned char gg, unsigned char bb, int delayed, char blank)
{     
    for(i = 4; i--;)
       {
       for(y = 0; y < 4; y++)
          {
          for(x = 0; x < 4; x++)
             {
             setPixelZXY(x,y,i,r,g,b); 
             setPixelZXY(2,2,i,rr,gg,bb); 
             setPixelZXY(1,2,i,rr,gg,bb); 
             setPixelZXY(2,1,i,rr,gg,bb); 
             setPixelZXY(1,1,i,rr,gg,bb);           
             }
          }
       matrix.show(); 
       delay(delayed); 
       if (blank == 1) ClearCube();
       }     
} 
//*******************************************************************************************  
// Flat Plane with Center Square Move Right
void FlatPlaneSqYInc(unsigned char r, unsigned char g, unsigned char b, unsigned char rr, unsigned char gg, unsigned char bb, int delayed, char blank)
{     
    for(i = 0; i < 4; i++)
       {
       for(y = 0; y < 4; y++)
          {
          for(x = 0; x < 4; x++)
             {    
             setPixelZXY(x,y,i,r,g,b); 
             setPixelZXY(2,2,i,rr,gg,bb); 
             setPixelZXY(1,2,i,rr,gg,bb); 
             setPixelZXY(2,1,i,rr,gg,bb); 
             setPixelZXY(1,1,i,rr,gg,bb);               
             }
          }
       matrix.show();    
       delay(delayed); 
       if (blank == 1) ClearCube();
       }     
}
