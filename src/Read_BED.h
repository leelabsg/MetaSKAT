/***************************************************

	Read Bed file 
		Author: Seunggeun Lee
		Date: 04/16/2012


******************************************************/

#ifndef _READ_BED_H        
#define _READ_BED_H 


#include <fstream>  
#include <iostream> 
#include <cstring>

using namespace std;

class BedFile
{
public:
	BedFile();	
	~BedFile();

	int	Init(char* filename, int NSample, int NSnp);	
	int 	Check();
	int	Close();
	int	ReadData(int * pIdxs, int num, unsigned char * Genotype);

protected:
	int	Decoding(unsigned char bitval);
	int	ReadDataOne(int Idx, unsigned char * Genotype);
	int	GetStartByte(int SNP_Idx);
	int ReadFile(int start);
	int SeekG(int start);
	
private:
	
	std::ifstream 	m_bed;
	std::string	m_filename;
	
	int		m_nSample;
	int		m_nSNP;
	int		m_BlockSize;
	int		m_FileSize;

	unsigned char	m_decode_out[4];
	unsigned char 	m_magic_number[3];
	unsigned char	*m_pbuffer;	
	
	int m_debugPos ;
	int m_debuglength ;


};



#endif


