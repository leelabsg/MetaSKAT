/***************************************************

	Handle Mat file 
		Author: Seunggeun Lee
		Date: 04/16/2012


******************************************************/

#ifndef _MAT_FILE_H        
#define _MAT_FILE_H  

#include <fstream>  
#include <iostream> 
#include <cstring>
#include <vector>
#define MAGIC_NUM_MAT	0x11
#define MAX_SIZE_MAT	25000000 /* 5000 x 5000 */

class MatFile
{
public:
	MatFile();	
	~MatFile();

    int Init();
	int OpenToSave(const char * FileName);
	int OpenToRead(const char * FileName);
	int 	Check();
	int	Close();

	int	PutData(double * mat, int size);
	int	GetData(double * mat, long start, int nmarker);

	int GetNum_Sets();
	int	GetStart_Pos(long * pos, int * size);
    int GetStart_Pos_IDX(int idx, long * pos, int * size);
	int	CheckSavedData();
    int CheckCRC(long start, int size);
    int SeekG(long start);
	
private:
	

	std::ifstream 	m_file_read;
	std::ofstream 	m_file_save;
	std::string	m_filename_read;
	std::string	m_filename_save;

	std::vector<long>	m_save_startpos;

	char	m_decode_out[4];
	char 	m_magic_number[2];	
	char  	m_buffer_crc[MAX_SIZE_MAT*4];
    float  	m_buffer_float[MAX_SIZE_MAT];
    
    long m_debugPos;

};



#endif


