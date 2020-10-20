#include "RFunc.h"
#include "Meta.h"

/************************************************
 
 
 ************************************************/

extern "C" {

/*  1: little endian, 0: big endian (only little endian is valid)*/
void IsLittleEndian(int * re){
        
    *re = endian(); 
        
}

/*************************************************************
	MAT file for read
    "MAT" and "MSSD" are the same
*************************************************************/
void	META_MSSD_Read_Open_Init(int * pNumPop, int * err){
	
	*err = Init_MatFile_Read(pNumPop[0]);
}

void	META_MSSD_Read_Open(int * pidx, char ** pFileName, int * err){

	*err = Open_NewMatFile_Read(pidx[0], pFileName[0]);
}

void	META_MSSD_GetData(int * pidx, double * mat, double * pstart, int * pnmarker, int *err){

    long start = (long)pstart[0];
	*err =Mat_GetData(pidx[0], mat, start, pnmarker[0]);
    
}

void	META_MSSD_Read_Close(int * pidx, int * err){
	*err = Close_MatFile(pidx[0]);

}

/*************************************************************
	MAT file for save

*************************************************************/

    
void META_MSSD_Write_Init(int * err){
        
        *err = Mat_Init_Save();
}
    
void	META_MSSD_Write_Open(char ** pFileName, int *err){

	*err =Open_NewMatFile_Save(pFileName[0]);
}

void	META_MSSD_Write(double * mat, int * psize,  int *err){

	*err = Mat_PutData(mat, psize[0]);
}


void	META_MSSD_Check_Saved(int *err){

	*err = Mat_Check_Saved();
}

void	META_MSSD_Num_Sets(int * nsets, int *err){

	*nsets = Mat_Num_Sets();
}

void	META_MSSD_GetStart_Pos(double * pos, int * size, int *err){

	*err = Mat_GetStart_Pos(pos, size);

}
    
void    META_MSSD_Write_Close(int * err){
    *err = Close_Write_MatFile();
}
    

/*************************************************************
	Bed file for read

*************************************************************/
void	META_BED_Init(char** pfilename, int* pNSample, int* pNSnp, int *err){

	*err = Bed_Init(pfilename[0], pNSample[0], pNSnp[0]);
	
}
void	META_BED_Read(int * pIdxs, unsigned char * Genotype, int * pnum, int *err){

	*err = Bed_ReadData(pIdxs, pnum[0], Genotype);
	
}
    
void META_BED_Close(int *err){
    
    *err = Bed_Close();
        
}

    
/*************************************************************
     Dosage file for read
*************************************************************/
void	META_Dosage_Init(char** pfilename, int* pNSample, int* pNSnp, int *err){
        
    *err = Dosage_Init(pfilename[0], pNSample[0], pNSnp);
        
}
void	META_Dosage_Read(int * pIdxs, float * Dosage, int * pnum, int *err){
        
    *err = Dosage_ReadData(pIdxs, pnum[0], Dosage);
        
}
    
void META_Dosage_Close(int *err){
        
    *err = Dosage_Close();
        
}
    
void META_Dosage_Info(char * pSNPID, char *pa1, char *pa2 , int *err){
        
    *err = Dosage_Info(pSNPID, pa1, pa2);
}
    

} // extern "C"

/*
# One int *
void 	IsLittleEndian(int * re);
void 	META_MSSD_Write_Init(int * err);
void	META_MSSD_Check_Saved(int *err);
void    META_MSSD_Write_Close(int * err);
void 	META_BED_Close(int *err);
void 	META_Dosage_Close(int *err);

# Two int
void	META_MSSD_Read_Open_Init(int * pNumPop, int * err);
void	META_MSSD_Read_Close(int * pidx, int * err);
void	META_MSSD_Num_Sets(int * nsets, int *err);

# One double two int
void	META_MSSD_Write(double * mat, int * psize,  int *err);
void	META_MSSD_GetStart_Pos(double * pos, int * size, int *err);



void	META_MSSD_Read_Open(int * pidx, char ** pFileName, int * err);
void	META_MSSD_GetData(int * pidx, double * mat, double * pstart, int * pnmarker, int *err);
void	META_MSSD_Write_Open(char ** pFileName, int *err);
void	META_BED_Init(char** pfilename, int* pNSample, int* pNSnp, int *err);
void	META_BED_Read(int * pIdxs, unsigned char * Genotype, int * pnum, int *err);
void	META_Dosage_Init(char** pfilename, int* pNSample, int* pNSnp, int *err);
void	META_Dosage_Read(int * pIdxs, float * Dosage, int * pnum, int *err);
void 	META_Dosage_Info(char * pSNPID, char *pa1, char *pa2 , int *err);
*/


/* register native routines */
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

static R_NativePrimitiveArgType type2[] = {INTSXP};
static R_NativePrimitiveArgType type3[] = {INTSXP, INTSXP};
static R_NativePrimitiveArgType type4[] = {REALSXP, INTSXP, INTSXP};

static R_NativePrimitiveArgType type5[] = {INTSXP, STRSXP, INTSXP}; //META_MSSD_Read_Open
static R_NativePrimitiveArgType type6[] = {INTSXP, REALSXP,REALSXP, INTSXP,INTSXP}; // META_MSSD_GetData
static R_NativePrimitiveArgType type7[] = {STRSXP, INTSXP}; // META_MSSD_Write_Open
static R_NativePrimitiveArgType type8[] = {STRSXP, INTSXP,INTSXP,INTSXP}; // META_BED_Init
static R_NativePrimitiveArgType type9[] = {INTSXP, STRSXP,INTSXP,INTSXP}; //META_BED_Read

static R_NativePrimitiveArgType type10[] = {STRSXP, INTSXP,INTSXP,INTSXP}; //META_Dosage_Init
static R_NativePrimitiveArgType type11[] = {INTSXP, REALSXP,INTSXP,INTSXP}; //META_Dosage_Read
static R_NativePrimitiveArgType type12[] = {STRSXP, STRSXP,STRSXP,INTSXP}; //META_Dosage_Info



R_CMethodDef cMethods[] = {
 	{"IsLittleEndian", (DL_FUNC) &IsLittleEndian, 1, type2},
  	{"META_MSSD_Write_Init", (DL_FUNC) &META_MSSD_Write_Init, 1, type2},
 	{"META_MSSD_Check_Saved", (DL_FUNC) &META_MSSD_Check_Saved, 1, type2},
 	{"META_MSSD_Write_Close", (DL_FUNC) &META_MSSD_Write_Close, 1, type2},
  	{"META_BED_Close", (DL_FUNC) &META_BED_Close, 1, type2},
   	{"META_Dosage_Close", (DL_FUNC) &META_Dosage_Close, 1, type2},
//   	
   	{"META_MSSD_Read_Open_Init", (DL_FUNC) &META_MSSD_Read_Open_Init, 2, type3},
   	{"META_MSSD_Read_Close", (DL_FUNC) &META_MSSD_Read_Close, 2, type3},
   	{"META_MSSD_Num_Sets", (DL_FUNC) &META_MSSD_Num_Sets, 2, type3},
//   	
   	{"META_MSSD_Write", (DL_FUNC) &META_MSSD_Write, 3, type4},
   	{"META_MSSD_GetStart_Pos", (DL_FUNC) &META_MSSD_GetStart_Pos, 3, type4},
//
   	{"META_MSSD_Read_Open", (DL_FUNC) &META_MSSD_Read_Open, 3, type5},
   	{"META_MSSD_GetData", (DL_FUNC) &META_MSSD_GetData, 5, type6},
   	{"META_MSSD_Write_Open", (DL_FUNC) &META_MSSD_Write_Open, 2, type7},
    {"META_BED_Init", (DL_FUNC) &META_BED_Init, 4, type8},
    {"META_BED_Read", (DL_FUNC) &META_BED_Read, 4, type9},
//
    {"META_Dosage_Init", (DL_FUNC) &META_Dosage_Init, 4, type10},
    {"META_Dosage_Read", (DL_FUNC) &META_Dosage_Read, 4, type11},
    {"META_Dosage_Info", (DL_FUNC) &META_Dosage_Info, 4, type12},
   	{NULL, NULL, 0}
};


extern "C" {

void R_init_SKAT(DllInfo *dll)
{
    R_registerRoutines(dll, cMethods, NULL, NULL, NULL);
    R_useDynamicSymbols(dll, (Rboolean)FALSE);
}

}

