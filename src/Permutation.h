/***************************************************

	Read Bed file 
		Author: Seunggeun Lee
		Date: 03/13/2014


******************************************************/

#ifndef _PERMUTATION_H        
#define _PERMUTATION_H 


#include <fstream>  
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Permutation
{
public:
	Permutation();	
	~Permutation();

	int	Init(int nPop);
	int OpenPermu(char * filename, char * filenamePermu, int npermu, int idx, int nSample, int nSNP);
	int	Close();

protected:

private:
	
	std::ifstream 	m_File;
    
    int      m_nPop;
    vector<string>      m_filenameVec;
    vector<int>         m_nPermuVec;
    vector<int>         m_nSampleVec;
    vector<int>         m_nSNPVec;
    
    vector<float *> m_pScoreVec;
    float * m_pScoreOrg;
    
    unsigned char	*m_pbuffer;	
	

};



#endif


