/*
 *  Copyright (C) Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see http://www.gnu.org/licenses/.
 *
 *  Version:           1.0
 *  Design:            David Gascón
 *  Implementation:    Yuri Carmona & Ruben Martin
 */ 

#include "cookingClasses.h"
#include "cookingSigfox.h"
#include "cookingUART.h"
#include "cookingUtils.h"

//////////////////////////////////////////////
uint8_t sock = SOCKET0;     //Asign to UART0
//////////////////////////////////////////////

uint8_t error;

void setup() 
{
  //////////////////////////////////////////////
  // 1. switch on
  //////////////////////////////////////////////
  error = Sigfox.ON(sock);
  
  // Check status
  if( error == 0 ) 
  {
    printf("Switch ON OK\n");
  }
  else 
  {
    printf("Switch ON ERROR\n");
  } 

  //////////////////////////////////////////////
  // 2. send data
  //////////////////////////////////////////////
  
  // Send 12 bytes at most
  error = Sigfox.send((char*)"0123456789ABCDEF01234567");
  
  // Check sending status
  if( error == 0 ) 
  {
    printf("Sigfox packet sent OK\n");
  }
  else 
  {
    printf("Sigfox packet sent ERROR\n"); 
  } 
}


//////////////////////////////////////////////
// Main loop setup() and loop() declarations
//////////////////////////////////////////////

int main (){
	setup();
	return (0);
}                 

//////////////////////////////////////////////


				
