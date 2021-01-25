//*******************************************************************************
// ConnectFourCubeNeoP.ino
// Progressive Version of the Cube
// Connect Four RGB Cube Game
// by RCI
//
// Edits:
//      10-11-2016
//         Added Player color choice check and flash yellow when same color selected.
//      3-18-2017
//         Cleaned up variable types,  reversed encoder direction - RCI.
//      12-24-2019
//         Fixed counter loop issue while displaying random rain - RCI.
//      11-10-2020
//         Added RefreshCube() call to FlashRow Routine.  Not sure why flash stopped
//         working - RCI.
//      12-24-2020 Changed EncoderHalfStep.h to ErriezRotaryHalfStep.h
//      1-16-2021 Redesigned cube for WS2812 Neopixels  
//*******************************************************************************
#include "RainbowShapes.h"

unsigned char RED[64] = {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,238,221,204,188,
171,154,137,119,102,85,68,51,34,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,35,52};

unsigned char GREEN[64] = {0,0,0,17,34,51,68,85,102,119,136,153,170,187,204,221,238,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,238,
221,204,188,170,154,136,120,102,86,68,52,34,18,0,0};

unsigned char BLUE[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,34,52,68,86,
102,120,136,154,170,188,204,221,238,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255};
//Matrix to Cube mapping 
unsigned char ZX[5][4]= 
{ 
 {0,0,0,0},
 {4,4,4,4},
 {8,8,8,8},
 {12,12,12,12}
};
unsigned char plane[4][4] = {
                            {0, 1, 2, 3},
                            {1, 2, 3, 0},
                            {2, 3, 0, 1},
                            {3, 0, 1, 2},
                            };
unsigned char plasma[4][4][4];
unsigned char plasmar[32][32];
int speede;
unsigned char colorshift = 0;

//****************************************************                           
const unsigned char TempPos[65][4] = {
                            {0, 0, 0, 0},  // dummy
                            {0, 0, 0, 0},  // 1
                            {0, 1, 0, 0},  // 2
                            {0, 2, 0, 0},  // 3
                            {0, 3, 0, 0},  // 4
                            {0, 0, 1, 0},  // 5
                            {0, 1, 1, 0},  // 6
                            {0, 2, 1, 0},  // 7
                            {0, 3, 1, 0},  // 8
                            {0, 0, 2, 0},  // 9
                            {0, 1, 2, 0},  // 10
                            {0, 2, 2, 0},  // 11
                            {0, 3, 2, 0},  // 12
                            {0, 0, 3, 0},  // 13
                            {0, 1, 3, 0},  // 14
                            {0, 2, 3, 0},  // 15
                            {0, 3, 3, 0},  // 16 
                            {1, 0, 0, 0},  // 1
                            {1, 1, 0, 0},  // 2
                            {1, 2, 0, 0},  // 3
                            {1, 3, 0, 0},  // 4
                            {1, 0, 1, 0},  // 5
                            {1, 1, 1, 0},  // 6
                            {1, 2, 1, 0},  // 7
                            {1, 3, 1, 0},  // 8
                            {1, 0, 2, 0},  // 9
                            {1, 1, 2, 0},  // 10
                            {1, 2, 2, 0},  // 11
                            {1, 3, 2, 0},  // 12
                            {1, 0, 3, 0},  // 13
                            {1, 1, 3, 0},  // 14
                            {1, 2, 3, 0},  // 15
                            {1, 3, 3, 0},  // 16 
                            {2, 0, 0, 0},  // 1
                            {2, 1, 0, 0},  // 2
                            {2, 2, 0, 0},  // 3
                            {2, 3, 0, 0},  // 4
                            {2, 0, 1, 0},  // 5
                            {2, 1, 1, 0},  // 6
                            {2, 2, 1, 0},  // 7
                            {2, 3, 1, 0},  // 8
                            {2, 0, 2, 0},  // 9
                            {2, 1, 2, 0},  // 10
                            {2, 2, 2, 0},  // 11
                            {2, 3, 2, 0},  // 12
                            {2, 0, 3, 0},  // 13
                            {2, 1, 3, 0},  // 14
                            {2, 2, 3, 0},  // 15
                            {2, 3, 3, 0},  // 16 
                            {3, 0, 0, 0},  // 1
                            {3, 1, 0, 0},  // 2
                            {3, 2, 0, 0},  // 3
                            {3, 3, 0, 0},  // 4
                            {3, 0, 1, 0},  // 5
                            {3, 1, 1, 0},  // 6
                            {3, 2, 1, 0},  // 7
                            {3, 3, 1, 0},  // 8
                            {3, 0, 2, 0},  // 9
                            {3, 1, 2, 0},  // 10
                            {3, 2, 2, 0},  // 11
                            {3, 3, 2, 0},  // 12
                            {3, 0, 3, 0},  // 13
                            {3, 1, 3, 0},  // 14
                            {3, 2, 3, 0},  // 15
                            {3, 3, 3, 0},  // 16                                 
                            }; 


//*********************************************************************************
#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
ICACHE_RAM_ATTR
#endif
//*********************************************************************************
ICACHE_RAM_ATTR void rotaryInterrupt()
{
    int rotaryState;

    // Read rotary state (Counter clockwise) -2, -1, 0, 1, 2 (Clockwise)
    rotaryState = rotary.read();

    // Count up or down by using rotary speed
    if (rotaryState == 0) 
        {
        // No change
        return;
        } 
    else if (abs(rotaryState) >= 2) 
        {
        EncVal += rotaryState * 2;
        } 
    else 
        {
        EncVal += rotaryState;
        }

    // Limit count to a minimum and maximum value
    if (EncVal > MAX_ENC_VAL) 
        {
        EncVal = MAX_ENC_VAL;
        }
    if (EncVal <= MIN_ENC_VAL) 
        {
        EncVal = MIN_ENC_VAL;
        }

    // Print count value when count value changed
    if (countLast != EncVal) 
        {
        countLast = EncVal;
        }
}
//************************************************************************************************
// delayms (loops) Milliseconds if using ESPAlexa
void delayms(int loops) 
{
unsigned long time_now = 0;
    time_now = millis();
    
    while(millis() < time_now + loops)
      {
      delay(1);   
      }  
}
//***********************************************************************************
void InitVariables() 
{
  EncVal = 0;
  counter = 0;
  next_player = 0;
  buttoncount = 0;
  win[0] = 0;
  win[1] = 0;
  win[2] = 0;
  win[3] = 0;
  win[4] = 0;
  next_slot = 0;
  pos = 1;
  flag = 0;
  matrix.fillScreen(0);

}
//***********************************************************************************
void ClearCube()
{
int a, b, c;

   for(a = 0; a < 5; a++)
     { 
     for(b = 0; b < 5; b++)
       {
       for(c = 0; c < 5; c++)
         {
         setPixelZXY(a, b, c, 0, 0, 0); //uses 24bit RGB color Code
         }    
       }      
     }      
   matrix.show();    
 
}
//***********************************************************************************
void ClearPixel(unsigned char x, unsigned char y, unsigned char z)
{
      setPixelZXY(z, x, y, 0, 0, 0);
}
//***********************************************************************************
void SelectColor(unsigned char r, unsigned char g, unsigned char b, unsigned pos)
{
      setPixelZXY(TempPos[pos][0], TempPos[pos][1], TempPos[pos][2], r, g, b); 
      matrix.show();       
}
//***********************************************************************************
void SelectPixel(unsigned char r, unsigned char g, unsigned char b, unsigned pos)
{
      setPixelZXY(TempPos[pos][0], TempPos[pos][1], TempPos[pos][2], 0, 0, 0);
      matrix.show();
      delayms(50);
      setPixelZXY(TempPos[pos][0], TempPos[pos][1], TempPos[pos][2], r, g, b); 
      matrix.show();
      delayms(50);      
}
//***********************************************************************************
//set the pixel (Z,X,Y) of RGB Cube with colours R,G,B 
void setPixelZXY(unsigned char zaxis, unsigned char x, unsigned char y, unsigned char r, unsigned char g, unsigned char b) 
{     
     matrix.drawPixel(ZX[zaxis][x] + x, y, matrix.Color(r, g, b));       
}
//**************************************************************************************
void setup()
{
  Serial.begin(115200);
  pinMode(BUTTON, INPUT_PULLUP);

  matrix.begin();
  matrix.setBrightness(100);
  matrix.clear();
  strip.setBrightness(25);  
  strip.begin();  
  strip.show();                 

  // Initialize pin change interrupt on both rotary encoder pins
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN1), rotaryInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN2), rotaryInterrupt, CHANGE);
  // Change sensitivity
  rotary.setSensitivity(1);
  InitVariables();
  
}
//***************************************************************************************
void loop()
{
int group, row;

  tempcolor = random(12);
  RotatePlanes(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 50);
  delay(2000);
// Fill Cube with Solid Color 
  Fill_Solid(red, 500);
  Fill_Solid(green, 500);
  Fill_Solid(blue, 500);

  ClearCube();
  
 // Cube Demo, Clockwise, Solid Colors and Cube Demo, Counter-Clockwise, Solid Colors
  CubeDemoCW(red, 100);
  CubeDemoCCW(blue, 100);
  CubeDemoCW(green, 100);
  CubeDemoCCW(purple, 100);
  CubeDemoCW(yellow, 100);
  CubeDemoCCW(cyan, 100);
  CubeDemoCW(red, 100);
  CubeDemoCCW(blue, 100);
  CubeDemoCW(green, 100);
  CubeDemoCCW(purple, 100);
  CubeDemoCW(yellow, 100);
  CubeDemoCCW(cyan, 100); 
  CubeDemoCW(white, 100); 
  
  delay(1000);
  ClearCube(); //Clear the LEDs (make all blank)
//*******************************************************************************************   
// Move Six Random Color Dots Around
for(times = 0; times < 8; times++)
   {
   for(a = 0; a < 4; a++)
      {
      tempcolor = random(12);
      tempcolor1 = random(12);
      tempcolor2 = random(12);       
      for(i = 4; i--;)
         {           
         for(y = 0; y < 4; y++)
            {   
            HorizXBar(1, y, i, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
            HorizXBar(y, i, a, colors[tempcolor2][0], colors[tempcolor2][1], colors[tempcolor2][2]);
            HorizXBar(i, i, y, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);
            HorizXBar(a, y, i, colors[tempcolor][0], colors[tempcolor2][1], colors[tempcolor1][2]);
            HorizXBar(y, a, i, colors[tempcolor1][0], colors[tempcolor2][1], colors[tempcolor2][2]);
            HorizXBar(i, a, y, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor][2]);          
            matrix.show();         
            delay(100);
            ClearCube();                    
            }// End For y    
         }// End For i
      }// End For a   
   }// End For times  
//**************************************************************************************************************
// Fill from bottom to top with solid plane and Center Square
for(times = 0; times < 5; times++)
   {
   tempcolor = random(12); 
   tempcolor1 = random(12);    
   FlatPlaneSqYDec(red, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2], 100, 1);
   FlatPlaneSqXDec(green, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 100, 1);
   FlatPlaneSqUP(orange, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 100, 1);  
   FlatPlaneSqYInc(colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 100, 0);
   FlatPlaneSqXInc(white, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 100, 1);
   FlatPlaneSqDN(purple, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 100, 1);
   
   FlatPlaneSqXInc(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], gold, 100, 1);
   FlatPlaneSqDN(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], cyan, 100, 0);
   FlatPlaneSqYInc(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], green, 100, 1);    
   FlatPlaneSqYDec(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2], 100, 0);
   FlatPlaneSqXDec(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], blue, 100, 1);  
   FlatPlaneSqUP(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], red, 100, 1); 
   }
//**************************************************************************************************************
// Display Random Colors
i = 255;
  for (times = 0; times < 127; times++)
      {
      for(z = 0; z < 4; z++)
         { 
         for(x = 0; x < 4; x++)
            {
            for(y = 0; y < 4; y++)
               {   
               setPixelZXY(z, x, y, random(i), random(i), random(i));
               matrix.show(); 
               }
            }  
         }
      delay(10);   
      } 

  delay(100);
//**************************************************************************************************************
// Fill from bottom to top with solid plane
for(times = 0; times < 5; times++)
   {
   for(i = 0; i < 4; i++)
      {
      for(y = 0; y < 4; y++)
         {
         for(x = 0; x < 4; x++)
            {
            setPixelZXY(i,x,y,255, 0, 0); // uses Red         
            }
         }
      matrix.show(); 
      delay(100);
      ClearCube();
      } 
    for(i = 3; i--;)
       {
       for(y = 0; y < 4; y++)
          {
          for(x = 0; x < 4; x++)
             {
             setPixelZXY(i,x,y,255, 0, 0); // uses Red         
             }
          }
      matrix.show(); 
      delay(100);
      ClearCube();
      }     
   }         
ClearCube(); //Clear the LEDs (make all blank)    
//**************************************************************************************************************
// Fill from side to side with random colors
  for(z = 0; z < 4; z++)
     {
     for(y = 0; y < 4; y++)
        {
        for(x = 0; x < 4; x++)
           { 
           setPixelZXY(x,y,z,random(0xFF),random(0xFF),random(0xFF)); //uses R, G and B color bytes
           matrix.show(); 
           delay(50); //delay to illustrate the postion change. can be removed
           }
        }
     }
//ClearCube(); //Clear the LEDs (make all blank)
//**************************************************************************************************************
// Fill from bottom to top with solid plane
for(times = 0; times < 5; times++)
   {
   for(i = 0; i < 4; i++)
      {
      for(y = 0; y < 4; y++)
         {
         for(x = 0; x < 4; x++)
            {
            setPixelZXY(x,y,i,0, 0, 255); // uses Blue        
            }
         }
      matrix.show(); 
      delay(100);
      ClearCube();
      } 
    for(i = 3; i--;)
       {
       for(y = 0; y < 4; y++)
          {
          for(x = 0; x < 4; x++)
             {
             setPixelZXY(x,y,i, 0, 0, 255); // uses Blue        
             }
          }
      matrix.show(); 
      delay(100);
      ClearCube();
      }     
   }         
ClearCube(); //Clear the LEDs (make all blank) 
//**************************************************************************************************************
// Fill from side to side with random colors
  for(z = 0; z < 4; z++)
     {
     for(y = 0; y < 4; y++)
        {
        for(x = 0; x < 4; x++)
           { 
           setPixelZXY(y,z,x,random(0xFF),random(0xFF),random(0xFF)); //uses R, G and B color bytes
           matrix.show(); 
           delay(50); //delay to illustrate the postion change. can be removed
           }
        }
     }
//ClearCube(); //Clear the LEDs (make all blank)

//**************************************************************************************************************
// Fill from bottom to top with solid plane
for(times = 0; times < 5; times++)
   {
   for(i = 0; i < 4; i++)
      {
      for(y = 0; y < 4; y++)
         {
         for(x = 0; x < 4; x++)
            {
            setPixelZXY(x,i,y,0, 255, 0); // uses Green         
            }
         }
      matrix.show(); 
      delay(100);
      ClearCube();
      } 
    for(i = 3; i--;)
       {
       for(y = 0; y < 4; y++)
          {
          for(x = 0; x < 4; x++)
             {
             setPixelZXY(x,i,y,0, 255, 0); // uses Green         
             }
          }
      matrix.show(); 
      delay(100);
      ClearCube();
      }     
   }         
ClearCube(); //Clear the LEDs (make all blank)
//*******************************************************************************************  
// Quad Walker Walks Up Cube

speede = 100;
for(zpos = 0; zpos < 3; zpos++)
   {
   for(ypos = 0; ypos < 3; ypos++)
      {
     tempcolor1 = random(12);   
      for(xpos = 0; xpos < 3; xpos++)
         {               
         //QWPos1(zpos, xpos, ypos, r, g, b)
         QWPos3(zpos, xpos, ypos, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);
         matrix.show(); 
         delay(speede);
         ClearCube();
         QWPos2(zpos, xpos, ypos, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);
         matrix.show(); 
         delay(speede);
         ClearCube();         
         QWPos1(zpos, xpos, ypos, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);
         matrix.show(); 
         delay(speede);
         ClearCube(); 
         QWPos6(zpos, xpos, ypos, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);
         matrix.show(); 
         delay(speede);
         ClearCube();
         QWPos4(zpos, xpos, ypos, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);
         matrix.show(); 
         ClearCube();         
         }
      }
   }
//**************************************************************************************************************
// Display different color in layers
for(times = 0; times < 5; times++)
   {
for(i = 0; i < 4; i++)
   {
for(y = 0; y < 4; y++)
   {
    for(x = 0; x < 4; x++)
       {
       setPixelZXY(plane[0][i],x,y, 255, 0, 0 ); //Paint layer 0 (z-0) Red completely 
       matrix.show(); 
       }
   }
   
for(y = 0; y < 4; y++)
   { 
    for(x = 0; x < 4; x++)
       {
       setPixelZXY(plane[1][i],x,y,0, 255, 0); //Paint layer 1 (z-1) Green completely 
       matrix.show(); 
       }
   }
   
for(y = 0; y < 4; y++)
   {
    for(x = 0; x < 4; x++)
       { 
       setPixelZXY(plane[2][i],x,y,0, 0, 255); //Paint layer 2 (z-2) Blue completely 
       matrix.show(); 
       }
   }

for(y = 0; y < 4; y++)
   { 
   for(x = 0; x < 4; x++)
      {
      setPixelZXY(plane[3][i],x,y,255, 0, 255); //Paint layer 3 (z-3) White completely 
      matrix.show(); 
      }
   }
   
   delay(500);
   }// end for i
   
   }// end for times
ClearCube(); //Clear the LEDs (make all blank)
//************************************************************************************************************************************* 
// Cube Demo, Mirror Image Effect, Random Colors Split
  for(x = 0; x < 10; x++)
     {
     tempcolor = random(12); 
     CubeDemoxbRan2(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 100);
     } 
//**************************************************************************************************************
// Display Pixel Demo, Random Colors
  for(x = 0; x < 12; x++)
     {
     tempcolor = random(12); 
     PixelDemoCW(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 100);
     }
  for(x = 0; x < 12; x++)
     {
     tempcolor = random(12); 
     PixelDemoCCW(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 100);
     }
//**************************************************************************************************************
// Display Random Pixel Demo, Random Colors
  for(x = 0; x < 12; x++)
     {
     tempcolor = random(12); 
     PixelDemoCWRan(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 100);

     tempcolor = random(12); 
     PixelDemoCCWRan(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 100);
     } 

//*******************************************************************************************  
// Random Fill,  Slowly Delete Colors
  for(times = 0; times < 25; times++)
     {
     tempcolor = random(12);  
     PixelDemoRandomHold(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 1, 30);
     }
     delay(2000);
  for(times = 0; times < 25; times++)
     {
     tempcolor = random(12);  
     PixelDemoRandomHold(0, 0, 0, 25, 30);
     }
     ClearCube();   
//*******************************************************************************************  
// Rain Random Colors Upward
   speede = 100;
for(times = 0; times < 50; times++)
   {
    
    x = random(4);
    y = random(4);
    xa = random(4);
    ya = random(4);
    xb = random(4);
    yc = random(4);
    tempcolor = random(12);
    tempcolor1 = random(12);
    tempcolor2 = random(12);
      for(zpos = 0; zpos < 4; zpos++)
         {
         setPixelZXY(zpos, x, y, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
         setPixelZXY(zpos + 1, xa, ya, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);
         setPixelZXY(zpos + 2, xb, yb, colors[tempcolor2][0], colors[tempcolor2][1], colors[tempcolor2][2]);
         setPixelZXY(zpos + 3, x, yc, colors[tempcolor2][0], colors[tempcolor2][1], colors[tempcolor2][2]);
         matrix.show(); 
         delay(speede);
         ClearCube();
         }
   }         

//*******************************************************************************************  
// Random Pixel Demo, Random Colors
  for(times = 0; times < 25; times++)
   {
   tempcolor = random(12);  
   PixelDemoRandom(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 50, 100);
   delay(500);
   }
//************************************************************************************************************************************* 
matrix.setBrightness(255);
// Gradient fade
for(times = 0; times < 3; times++)
   { 
   a = 64;
         for(z = 0; z < 4; z++)  
            {
            for(y = 0; y < 4; y++)  
               {
               for(x = 0; x < 4; x++)
                  {
                  //setPixelZXY(z,x,y,(RED[plasma[x][y][z] + colorshift]) % 256,(GREEN[plasma[x][y][z] + colorshift]) % 256,(BLUE[plasma[x][y][z] + colorshift]) % 256);
                  setPixelZXY(z,x,y, (a * x), (a * y), (a * z));
                  setPixelZXY(0,0,0,30, 0, 0);
                  matrix.show(); 
                  }
               }
            }
            delay(2000);
    a = 32;
         for(z = 0; z < 4; z++)  
            {
            for(y = 0; y < 4; y++)  
               {
               for(x = 0; x < 4; x++)
                  {
                  //setPixelZXY(z,x,y,(RED[plasma[x][y][z] + colorshift]) % 256,(GREEN[plasma[x][y][z] + colorshift]) % 256,(BLUE[plasma[x][y][z] + colorshift]) % 256);
                  setPixelZXY(y,z,x, (a * x), (a * y), (a * z));
                  setPixelZXY(0,0,0,0, 0, 30);
                  matrix.show(); 
                  }
               }
            }
            delay(2000);
    a = 48;
         for(z = 0; z < 4; z++)  
            {
            for(y = 0; y < 4; y++)  
               {
               for(x = 0; x < 4; x++)
                  {
                  //setPixelZXY(z,x,y,(RED[plasma[x][y][z] + colorshift]) % 256,(GREEN[plasma[x][y][z] + colorshift]) % 256,(BLUE[plasma[x][y][z] + colorshift]) % 256);
                  setPixelZXY(x,y,z, (a * x), (a * y), (a * z));
                  setPixelZXY(0,0,0,0, 30, 0);
                  matrix.show(); 
                  }
               }
            }
            delay(2000);
   }

   ClearCube(); //Clear the LEDs (make all blank)  
   delay(1000);
matrix.setBrightness(100);   
//*******************************************************************************************   

// Move Three Random Color Bars Across
for(times = 0; times < 5; times++)
   {
    tempcolor = random(12);
    tempcolor1 = random(12);
    tempcolor2 = random(12); 

for(a = 0; a < 4; a++)
    {   
    for(i = 4; i--;)
       {           
       for(y = 0; y < 4; y++)
          {   
          HorizXBar(1, y, i, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
          HorizXBar(y, i, a, colors[tempcolor2][0], colors[tempcolor2][1], colors[tempcolor2][2]);
          HorizXBar(i, i, y, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);          
          }
       matrix.show(); 
       delay(140);
       ClearCube(); 
       }
    }
   }
   
 //************************************************************************************************************************************* 
// Cube Demo
  for(x = 0; x < 10; x++)
     {
     tempcolor = random(12); 
     CubeDemoRanCW(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 50);
     CubeDemoRanCCW(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 50);
     }
  for(x = 0; x < 10; x++)
     {
     tempcolor = random(12); 
     CubeDemoCW(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 50);
     CubeDemoCCW(colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2], 50);
     }   
  delay(1000);
  ClearCube(); //Clear the LEDs (make all blank)   
//*******************************************************************************************   
// Move Three Random Color Dots Around
for(times = 0; times < 3; times++)
   {
for(a = 0; a < 4; a++)
    {
    tempcolor = random(12);
    tempcolor1 = random(12);
    tempcolor2 = random(12);       
    for(i = 4; i--;)
       {           
       for(y = 0; y < 4; y++)
          {   
          HorizXBar(1, y, i, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
          HorizXBar(y, i, a, colors[tempcolor2][0], colors[tempcolor2][1], colors[tempcolor2][2]);
          HorizXBar(i, i, y, colors[tempcolor1][0], colors[tempcolor1][1], colors[tempcolor1][2]);
       matrix.show(); 
       delay(180);
       ClearCube();                    
          }
       }
    }
   }    
//**********************************************************************************************
// Random Circle, Center, and Corner    
for(times = 0; times < 20; times++)
   {    
    speede = 100;
    tempcolor = random(12);

    for(zpos = 0; zpos < 4; zpos++)
       {         
       for(i = 0; i < 4; i++)
          {
          setPixelZXY(zpos, corner1[i], corner2[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
          }
       matrix.show(); 
       delay(speede);
       }
        tempcolor = random(12);
    for(zpos = 0; zpos < 4; zpos++)
       {         
       for(i = 0; i < 4; i++)
          {
          setPixelZXY(zpos, circle1[i], circle2[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
          setPixelZXY(zpos, circle3[i], circle4[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
          }
       matrix.show(); 
       delay(speede);
       }
    tempcolor = random(12);
    for(zpos = 4; zpos--;)
       {         
       for(i = 0; i < 4; i++)
          {
          setPixelZXY(zpos, center1[i], center2[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
          }
       matrix.show(); 
       delay(speede);
       }
   }    
//*******************************************************************************************  
// Spiral Wrap Counter Clockwise
tempcolor = random(12);  
for(times = 0; times < 4; times++)
   {
   for (i = 0; i < 12; i++)                 
       {
       HorizXBar(spinover[i], times, spinaround[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       matrix.show(); 
       delay(55);       
       }
   }
tempcolor = random(12);     
for(times = 0; times < 4; times++)
   {   
   for (i = 0; i < 12; i += 2)                 
       {
       HorizXBar(spinover[i], times, spinaround[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       matrix.show(); 
       delay(155);       
       }
   }
   delay(1000);
//******************************************************************************************* 
// Vert Bar Counter Clockwise, Hold Color
   tempcolor = random(12);  
   for (i = 0; i < 12; i++)                
       {
       VertZBar(0, spinover[i], spinaround[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       VertZBar(1, spinover[i], spinaround[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       VertZBar(2, spinover[i], spinaround[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       VertZBar(3, spinover[i], spinaround[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       matrix.show(); 
       delay(100);     
       }         

   delay(1000);
   ClearCube();    
//******************************************************************************************* 
// Clockwise Bar in Circle
tempcolor = random(12); 
for(times = 0; times < 5; times++)
   {
   for (i = 0; i < 12; i++)                
       {
       HorizYBar(spinover[i], spinaround[i], 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(spinover[i], spinaround[i], 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(spinover[i], spinaround[i], 2, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(spinover[i], spinaround[i], 3, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       matrix.show(); 
       delay(50);       
       ClearCube();
       }
   }
tempcolor = random(12);    
for(times = 0; times < 5; times++)
   {   
   for (i = 12; i--;)                
       {
       HorizYBar(spinover[i], spinaround[i], 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(spinover[i], spinaround[i], 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(spinover[i], spinaround[i], 2, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(spinover[i], spinaround[i], 3, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       matrix.show(); 
       delay(50);       
       ClearCube();
       }       
   } 
   delay(1000);
//******************************************************************************************* 
// Spiral Wrap Counter Clockwise Z Rise,  One Color per Layer
for(times = 0; times < 4; times++)
   {
   for (i = 0; i < 12; i++)                
       {
       VertZBar(times, spinover[i], spinaround[i], colors[times][0], colors[times][1], colors[times][2]);
       matrix.show(); 
       delay(50);       
       }
   }
   delay(1000);   
//*******************************************************************************************           

// Rotate Bars in X direction CCW

for(times = 0; times < 10; times++)
   {
   tempcolor = random(12);   
   for (i = 1; i < 25; i++)                 // Rotate Bar Counter Clockwise
       {        
       count++;
       HorizYBar(rotateZ[i], rotateX[i], 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(rotateZ[i], rotateX[i], 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);       
       HorizYBar(rotateZ[i], rotateX[i], 2, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);       
       HorizYBar(rotateZ[i], rotateX[i], 3, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);  
       if (count == 4)
          {
          count = 0;       
          matrix.show(); 
          delay(50);
          ClearCube();    
          }
       delay(1);  
       }  
   }
//*******************************************************************************************  
// Rotate Bars in Y direction CCW
for(times = 0; times < 10; times++)
   {
   tempcolor = random(12);   
   for (i = 1; i < 25; i++)                 // Rotate Bar Counter Clockwise
       {        
       count++;
       HorizYBar(rotateX[i], 0, rotateZ[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(rotateX[i], 1, rotateZ[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);       
       HorizYBar(rotateX[i], 2, rotateZ[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);       
       HorizYBar(rotateX[i], 3, rotateZ[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);  
       if (count == 4)
          {
          count = 0;       
          matrix.show(); 
          delay(50);
          ClearCube();    
          }
       delay(1);  
       }  
   } 
//*******************************************************************************************   
// Rotate Bars in X direction CW 
 for(times = 0; times < 10 ; times++)
   {
   tempcolor = random(12);   
   for (i = 1; i < 25; i++)                 // Rotate Bar Counter Clockwise
       {        
       count++;
       HorizYBar(rotateX[i], rotateZ[i], 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(rotateX[i], rotateZ[i], 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);       
       HorizYBar(rotateX[i], rotateZ[i], 2, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);       
       HorizYBar(rotateX[i], rotateZ[i], 3, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);  
       if (count == 4)
          {
          count = 0;       
          matrix.show(); 
          delay(50);
          ClearCube();    
          }
       delay(1);  
       }  
   }   
//*******************************************************************************************   
// Rotate Bars in Z direction CCW 

 for(times = 0; times < 10; times++)
   {
   tempcolor = random(12); 
   for (i = 1; i < 25; i++)                 // Rotate Bar Counter Clockwise
       {        
       count++;
       HorizYBar(0, rotateX[i], rotateZ[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(1, rotateX[i], rotateZ[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);       
       HorizYBar(2, rotateX[i], rotateZ[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);       
       HorizYBar(3, rotateX[i], rotateZ[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);       
       if (count == 4)
          {
          count = 0;       
          matrix.show(); 
          delay(50);
          ClearCube();         
          }          
       delay(1);  
       }
   }
//*******************************************************************************************   

// Rotate Bars in Z direction CW 

 for(times = 0; times < 10; times++)
   {
   tempcolor = random(12); 
   for (i = 1; i < 25; i++)                 // Rotate Bar Counter Clockwise
       {        
       count++;
       HorizYBar(0, rotateZ[i], rotateX[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(1, rotateZ[i], rotateX[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);       
       HorizYBar(2, rotateZ[i], rotateX[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);       
       HorizYBar(3, rotateZ[i], rotateX[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);       
       if (count == 4)
          {
          count = 0;       
          matrix.show(); 
          delay(50);
          ClearCube();         
          }          
       delay(1);  
       }
   }
//*******************************************************************************************  
//Rotate Bars Counter Clockwise, Random Colors
for(times = 0; times < 10; times++)
   {
   for (i = 1; i < 25; i++)                 // Rotate Bar Counter Clockwise
       {        
       count++;
       tempcolor = random(12);
       HorizYBar(spinover[i], spinaround[i], 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(spinover[i], spinaround[i], 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(spinover[i], spinaround[i], 2, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(spinover[i], spinaround[i], 3, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       tempcolor = random(12);
       VertZBar(0, spinover[i], spinaround[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]); 
       VertZBar(1, spinover[i], spinaround[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]); 
       VertZBar(2, spinover[i], spinaround[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]); 
       VertZBar(3, spinover[i], spinaround[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       tempcolor = random(12);
       HorizXBar(rotateZ[i], 3, rotateX[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]); 
       HorizXBar(rotateZ[i], 2, rotateX[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]); 
       HorizXBar(rotateZ[i], 1, rotateX[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);        
       HorizXBar(rotateZ[i], 0, rotateX[i], colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);        
       if (count == 4)
          {
          count = 0;       
          matrix.show(); 
          delay(10);
          ClearCube();    
          }
       delay(100);  
       }  
       tempcolor = random(12);
   }   
//*******************************************************************************************    
// Counter Clockwise Rotate in outer columns
for(times = 0; times < 20; times++)
   {
   for (i = 1; i < 25; i++)                
       {
        
       count++;
       HorizXBar(rotateZ[i], rotateX[i], 0, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizXBar(rotateZ[i], rotateX[i], 3, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);  
       if (count == 4)
          {
          count = 0;       
          matrix.show(); 
          delay(50);
          ClearCube();    
          }
       delay(1);  
       }  
       tempcolor = random(12);
   } 
 
//*******************************************************************************************

// Clockwise Rotate in Center two columns
for(times = 0; times < 10; times++)
   {
   tempcolor = random(12);     
   for(i = 25; i--;)                
       {        
       count++;
       HorizYBar(rotateZ[i], rotateX[i], 1, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]);
       HorizYBar(rotateZ[i], rotateX[i], 2, colors[tempcolor][0], colors[tempcolor][1], colors[tempcolor][2]); 
       if (count == 4)
          {
          count = 0;       
          matrix.show(); 
          delay(50);
          ClearCube();    
          }
       delay(1);  
       }  
   }
   ClearCube();   
   
}// End Loop

//**************************************************************************************************************
