# PIC16F1827 Melody Timer Project.
---
This is a simple kitchen/cooking timer by [PIC16F1827][1].
It can choose which of 3 minutes, 5 minutes and 10 minutes.

## Description

This is a simple kitchen/cooking timer by [PIC16F1827][1].
It can choose which of 3 minutes, 5 minutes and 10 minutes.
When it became end of time, it sounds a melody.

I use following peripherals for this Melody Timer project.
  *TMR1* (with interrupt. It makes 1mil second interval.)
  *TMR2*
  *ECCP2*(with TMR2. I use it for PWM output. It buzz a piezo sounder.)
  *GPIO*(input x2 for Switches, output x3 for LED1, LED2, LED3)

Other references.
  <https://docs.google.com/spreadsheets/d/1fajrvUh0QQHbjQNBCf9UKNRYu8I2-zE32fsanEHT9bc/edit?usp=sharing>



## Demo

![Alt text](/DEMO/circuit_DEMO.gif)

## Prerequisites

I created this project using the free versions of the following tools:
 * [Microchip MPLAB X][2] (v2.3)
 * [Microchip XC8 Compiler][3] (v1.32)
 * [MPLAB Code Configurator][4] (installed as plugin within MPLAB X)
 * [KICAD][6] (BZR4022)

You will need to download and install these tools appropriately before you
can open this project and build it.
I use the [Microchip MPLAB PICkit3 In-Circuit Debugger][5] to program
the chip and debug it.  


## Licence

[MIT](https://github.com/tcnksm/tool/blob/master/LICENCE)

## Author

Hiroshi Murakami  
<https://github.com/ClockWorks001>  


[1]: http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en538963 "PIC16F1827"
[2]: http://www.microchip.com/pagehandler/en-us/family/mplabx/ "MPLAB X"
[3]: http://www.microchip.com/pagehandler/en_us/devtools/mplabxc/ "MPLAB XC Compilers"
[4]: http://www.microchip.com/pagehandler/en-us/press-release/microchips-free-code-configura.html "MPLAB Code Configurator"
[5]: http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=PG164130 "MPLAB PICkit3 In-Circuit Debugger"
[6]: http://www.kicad-pcb.org/display/KICAD/KiCad+EDA+Software+Suite "KICAD"



