/*H*****************************************************************************
* FILENAME : main.c
*
* DESCRIPTION : Includes main() function with while(1) loop where your code 
*               should go.
*
* PUBLIC FUNCTIONS :
*
* NOTES :
*
* COPYRIGHT : Copyright 2018 Hardi Selg
*

* AUTHOR : Hardi Selg     CONTACT : hardi.selg@ati.ttu.ee
*
* START DATE : 06.11.2018
*
* CHANGES :
*
*
*H*/

//Libraries
#include <xc.h>
#include <sys/attribs.h>
#include "config.h"

#define DELAY_IN_MSEC_50 	 50
#define DELAY_IN_MSEC_100	100
#define DELAY_IN_MSEC_500	500

//Main program
int main(void) {
    //Has to be the first function call after main()
    init(); //Includes PIC16F690 basic configuration
    int value;
    //Loop forever
    while(1)
    {
        //Write your code here

        DelayForAproxmSeconds(DELAY_IN_MSEC_100);
    }
    return 0;
}
