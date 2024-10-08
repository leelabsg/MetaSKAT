/*************************************************************
 *
 * File: error_meassages.h	
 * Date: April 16, 2012
 * Author: Seunggeun Lee
 *
 **************************************************************/
#ifndef _ERROR_MESSAGES_H        
#define _ERROR_MESSAGES_H

#define SNP_ID_SIZE 50


#define NO_ERRORS			0		//no error
#define ERORR_BIM_OPEN_FILE4READ	2		//check if it's exists
#define ERORR_BIM_MAGIC_NUM		3		//check magic number of bim
#define ERORR_BIM_NOT_SNP_MOD		4		//check snp save mode
#define ERORR_MAT_OPEN_FILE4SAVE	5		//open mat file to save
#define ERORR_MAT_OPEN_FILE4READ	6		//open mat file to read
#define ERORR_MAT_MAGIC_NUM		7		//check magic number of mat
#define ERORR_MAT_CRC			8		//ckeck crc
#define ERORR_MAT_MAX_SIZE			9		//check the size of matrix
#define ERORR_MAT_INIT			10		//check the size of matrix
#define ERORR_MAT_NO_INIT			11		//check the size of matrix
#define ERORR_MAT_IDX_OUTOFBOUND			12		//check the size of matrix
#define ERORR_MAT_FILEOPEN	13	// file hasn't been opened.
#define ERORR_MEMORY	14	// file hasn't been opened.
#define ERORR_BED_SEEK	15	// seekg in bed file read error
#define ERROR_BED_READ	16	// read in bed file read error
#define ERORR_BED_FILESIZE 17
#define ERORR_MAT_SEEK 18

#endif //_ERROR_MESSAGES_H




