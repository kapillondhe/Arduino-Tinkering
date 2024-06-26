
// Include Libraries
#include "Arduino.h"
#include "ACS712.h"


// Pin Definitions
#define ACS712_1_PIN_VO	A0
#define ACS712_2_PIN_VO	A1
#define NRF24L01_PIN_CS	10
#define NRF24L01_PIN_CE	2



// Global variables and defines
const int acs712_1calFactor = 513;
const int acs712_2calFactor = 513;
// object initialization
ACS712 acs712_1(ACS712_1_PIN_VO);
ACS712 acs712_2(ACS712_2_PIN_VO);



// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    //Manually calibarte the ACS712 current sensor.
    //Connet the ACS to your board, but do not connect the current sensing side.
    //Follow serial monitor instructions. This needs be done one time only.
    acs712_1.calibrate(acs712_1calFactor);
    //Manually calibarte the ACS712 current sensor.
    //Connet the ACS to your board, but do not connect the current sensing side.
    //Follow serial monitor instructions. This needs be done one time only.
    acs712_2.calibrate(acs712_2calFactor);
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // Current Sensor Module ACS712 #1 - Test Code
    //Get averaged current measurment.
    float acs712_1Currrent  = acs712_1.getCurrent();
    Serial.print(acs712_1Currrent); Serial.println(F(" [mA]"));

    }
    else if(menuOption == '2') {
    // Current Sensor Module ACS712 #2 - Test Code
    //Get averaged current measurment.
    float acs712_2Currrent  = acs712_2.getCurrent();
    Serial.print(acs712_2Currrent); Serial.println(F(" [mA]"));

    }
    else if(menuOption == '3') {}
    // Disclaimer: The NRF24L01 - 2.4G Wireless Transceiver Module is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    
    
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Current Sensor Module ACS712 #1"));
    Serial.println(F("(2) Current Sensor Module ACS712 #2"));
    Serial.println(F("(3) NRF24L01 - 2.4G Wireless Transceiver Module"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {
            if(c == '1') 
    			Serial.println(F("Now Testing Current Sensor Module ACS712 #1"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Current Sensor Module ACS712 #2"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing NRF24L01 - 2.4G Wireless Transceiver Module - note that this component doesn't have a test code"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/