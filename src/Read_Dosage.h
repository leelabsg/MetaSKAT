/***************************************************

	Read Bed file 
		Author: Seunggeun Lee
		Date: 03/13/2014


******************************************************/

#ifndef _READ_DOSAGE_H        
#define _READ_DOSAGE_H 


#include <fstream>  
#include <iostream> 
#include <cstring>

using namespace std;

class DosageFile
{
public:
	DosageFile();	
	~DosageFile();

	int	Init(char* filename, int NSample, int * pNSnp);	
	int	Close();
	int	ReadData(int * pIdxs, int num, float * pDosage);
    int GetDosage_Info(char *pSNPID, char *pa1, char *pa2);

protected:
    int ReadDosageFile();
    int ReadLine(const std::string& str, const std::string& delimiters, int i );
    int SeekG(int start);
    int GetLineNum();
    
private:
	
	std::ifstream 	m_dosage;
    std::ofstream   m_tempfile;
    std::ifstream   m_tempfileRead;
	std::string     m_filename;
    std::string     m_tempfilename;
    
    float * m_pDosage;
    char	*m_SNPID;	
    char	*m_Allele1;	
    char	*m_Allele2;	
    char	*m_pbuffer;	
    unsigned int * m_POS;
    
	
	int		m_nSample;
	int		m_nSNP;
	int		m_FileSize;
    int     m_BlockSize;
    int     m_TotalSize;    
	
	
	int m_debugPos ;
	int m_debuglength ;


};



#endif


