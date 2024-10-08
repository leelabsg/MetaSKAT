/*************************************************************
 *
 * File: error_meassages.h	
 * Date: 03/13, 2014
 * Author: Seunggeun Lee
 *
 **************************************************************/
#ifndef _RFUNC_H        
#define _RFUNC_H

#ifdef _STAND_ALONE_
    #define Rprintf printf
    #define error printf
#else
    #include <R.h>
    #include <Rmath.h>
#endif

void * F_alloc(int n, int size);
int F_free(void * ptr);

#endif //_ERROR_MESSAGES_H




