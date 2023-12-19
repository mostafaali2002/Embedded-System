/* 
 * File:   mcal_std_types.h
 * Author: user
 *
 * Created on August 15, 2023, 4:31 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

#include "compile.h"
#include "std_libraries.h"


/* Section : Data Type Declaration */
typedef unsigned char uint8 ;
typedef unsigned short uint16 ;
typedef unsigned int uint32 ;
typedef signed char sint8 ;
typedef signed short sint16 ;
typedef signed int sint32 ;

typedef uint8 Std_ReturnType ;
/* Section : Macro Declaration*/
#define STD_HIGH      0x01
#define STD_LOW       0x00

#define STD_ON        0x01
#define STD_OFF       0x00

#define STD_ACTIVE    0x01
#define STD_IDEL      0x00

#define E_OK         (Std_ReturnType)0x01
#define E_NOT_OK     (Std_ReturnType)0x00

#define ZERO_INIT  0
 
/* Section : Macro Function Declaration*/

/* Section : Function Declaration*/

#endif	/* MCAL_STD_TYPES_H */

