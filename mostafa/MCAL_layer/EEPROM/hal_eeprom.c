/* 
 * File:   hal_eeprom.c
 * Author: user
 *
 * Created on September 12, 2023, 8:44 PM
 */

#include "hal_eeprom.h"


Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd , uint8 bData)
{
     Std_ReturnType ret =  E_OK ;
     /* check the interrupt status "Enable / Disenable" */
     uint8 Global_Interrupt_Status = INTCONbits.GIE;
     /*   Add address to EEADRH and EEADR*/
     EEADRH = (uint8)((bAdd >> 8)& 0x03);
     EEADR = (uint8)(bAdd & 0xFF);
     /* Update The Data */
     EEDATA = bData ;
     /*select access data */
     EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY ;
     EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
     /*Allow Write Cycle*/
     EECON1bits.WREN =ALLOW_WRITE_CYCLE ;
     /* Disable All Interrupts */ 
#if INTERRUPT_Priority_Levels_Enable == FeatureEnable
   
     INTERRUPT_GlobalInterruptHighDisable();
#endif
     /*Write the required sequence */
     EECON2 = 0x55 ;
     EECON2 = 0xAA ;
     /*Initiate A data EEPROM Erase /write cycle  */
     EECON1bits.WR = INIATE_DATA_EEPROM_WRITE ;
     /* Wait for Write complete */
     while( EECON1bits.WR);
     /*initiate Write Cycle*/
     EECON1bits.WREN =INHIBITS_WRITE_CYCLE ;
     /*return interrupt status "Enable / Disenable" */
     INTCONbits.GIE = Global_Interrupt_Status ;
     return ret ;
    
}
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd , uint8 *bData){
    Std_ReturnType ret =  E_OK ;
    if(NULL == bData)
    {
        ret =  E_NOT_OK ;
    }
    else
    {
       /*   Add address to EEADRH and EEADR*/
         EEADRH = (uint8)((bAdd >> 8)& 0x03);
         EEADR = (uint8)(bAdd & 0xFF);
       /*select access data */
          EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY ;
          EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        /*Initiate a data EEPROM Read */  
          EECON1bits.RD = INIATE_DATA_EEPROM_Read;
          NOP();
          NOP();
        /*Return Data*/ 
          *bData = EEDATA ;
    }
      return ret ;
    
}