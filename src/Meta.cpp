

#include "Read_BED.h"
#include "Read_Dosage.h"
#include "MatFile.h"
#include "error_messages.h"

MatFile * 	g_pMatFile_Read;
MatFile 	g_MatFile_Save;
int		g_nPop;		/* Number of Population */
BedFile         g_BedFile;
DosageFile		g_DosageFile;
/****************************************************
 endian is important. The program is only valid
 under little endian.
 *****************************************************/
#define LITTLE_ENDIAN_DEF 1
#define BIG_ENDIAN_DEF    0


int endian() {
    int i = 1;
    char *p = (char *)&i;
    
    if (p[0] == 1)
        return LITTLE_ENDIAN_DEF;
    else
        return BIG_ENDIAN_DEF;
}



/*************************************************************
	MAT file for read

*************************************************************/
int	Init_MatFile_Read(int NumPop){

	g_nPop = NumPop;
	g_pMatFile_Read = new MatFile[NumPop];
	if(!g_pMatFile_Read){
		return ERORR_MAT_INIT;
	}

	return NO_ERRORS;

}

int	Open_NewMatFile_Read(int idx, const char * FileName){

	int re;
	if(idx >= g_nPop){
		return ERORR_MAT_IDX_OUTOFBOUND;
	}
	re = g_pMatFile_Read[idx].OpenToRead(FileName);
	return re;

}

int	Mat_GetData(int idx, double * mat, long start, int nmarker){

	int re;
	if(idx >= g_nPop){
		return ERORR_MAT_IDX_OUTOFBOUND;
	}
	re = g_pMatFile_Read[idx].GetData(mat, start, nmarker);
	return re;

}

int Close_MatFile(int idx){
    
	int re;
	if(idx >= g_nPop){
		return ERORR_MAT_IDX_OUTOFBOUND;
	}
	re = g_pMatFile_Read[idx].Close();
	return re;
    
}


/*************************************************************
	MAT file for Save

*************************************************************/

int Mat_Init_Save(){
    
    int re = g_MatFile_Save.Init(); 
    return re;
}

int	Open_NewMatFile_Save(const char * FileName){

	int re = g_MatFile_Save.OpenToSave(FileName);
	return re;
}

int	Mat_PutData(double * mat, int size){

	int re = g_MatFile_Save.PutData(mat, size);
	return re;
}


int	Mat_Check_Saved(){

	int re = g_MatFile_Save.CheckSavedData();
	return re;
}

int	Mat_Num_Sets(){

	int re = g_MatFile_Save.GetNum_Sets();
	return re;
}

int	Mat_GetStart_Pos(double * pos, int * size){

    int i, size1, re;
    long pos1;
    int len = g_MatFile_Save.GetNum_Sets();
    for(i=0;i<len;i++){
        re = g_MatFile_Save.GetStart_Pos_IDX(i, &pos1, &size1);
        pos[i] = (double) pos1;
        size[i] = size1;
    }
	
	return re;
}

int	Close_Write_MatFile(){
    
	int re = g_MatFile_Save.Close();
	return re;
}

/*************************************************************
	Bed file for read

*************************************************************/
int	Bed_Init(char* filename, int NSample, int NSnp){

	int re = g_BedFile.Init(filename, NSample, NSnp);
	return re;
}
int	Bed_ReadData(int * pIdxs, int num, unsigned char * Genotype){

	int re =g_BedFile.ReadData(pIdxs, num, Genotype);
	return re;
}

int	Bed_Close(){
    
	int re =g_BedFile.Close();
	return re;
}



/*************************************************************
 Dosage file for read
 
 *************************************************************/
int	Dosage_Init(char* filename, int NSample, int * pNSnp){
    
	int re = g_DosageFile.Init(filename, NSample, pNSnp);
	return re;
}
int	Dosage_ReadData(int * pIdxs, int num, float * Dosage){
    
	int re =g_DosageFile.ReadData(pIdxs, num, Dosage);
	return re;
}

int	Dosage_Close(){
    
	int re =g_DosageFile.Close();
	return re;
}

int Dosage_Info(char * pSNPID, char *pa1, char *pa2){
    
	int re =g_DosageFile.GetDosage_Info(pSNPID, pa1, pa2);
	return re;    
    
}



