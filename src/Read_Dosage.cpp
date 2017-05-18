#include <stdio.h>
#include <stdlib.h>
#include "RFunc.h"
#include "Read_Dosage.h"
#include "error_messages.h"


DosageFile::DosageFile(){

	m_pbuffer= NULL;
    m_pDosage= NULL;

    m_SNPID=NULL;	
    m_Allele1=NULL;	
    m_Allele2=NULL;	
    m_POS=NULL;
    
	m_nSample = 0;
	m_nSNP = 0;
	m_BlockSize = 0;

}
DosageFile::~DosageFile(){

	Close();    

}

int DosageFile::GetLineNum(){
    
    int NSnp = 0;
    std::string str;
    
    m_dosage.open(m_filename.c_str());
	if (!this->m_dosage)
	{
		return -1;
	}
    while(!m_dosage.eof()){
        
        std::getline(m_dosage, str);
        if(str.size() > 1){
            NSnp++;
        }
    }
    m_dosage.close();
    
    return NSnp;
    
}

int DosageFile::GetDosage_Info(char *pSNPID, char *pa1, char *pa2){
    

    memcpy(pSNPID, m_SNPID, m_nSNP * sizeof(char) * (SNP_ID_SIZE+1));
    memcpy(pa1, m_Allele1, m_nSNP * sizeof(char) );
    memcpy(pa2, m_Allele2, m_nSNP * sizeof(char) );
    
    
    return NO_ERRORS;

    
}

int DosageFile::ReadDosageFile(){
    
    std::string str;
    int row=0;
    while(!m_dosage.eof()){
        
        std::getline(m_dosage, str);
        if(str.size() > 1){
            memset(m_pDosage, 0, sizeof(float)*m_nSample);
            ReadLine(str, "\t ", row );
            row++;
        }
    }
    
    return NO_ERRORS;
    
}

int DosageFile::ReadLine(const std::string& str, const std::string& delimiters, int i )
{
    
    int j=0;
    char buff[21];
    int size;
    unsigned int size_str = str.size();
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);
    

    
    
    while (std::string::npos != pos){
        // Found a token, add it to the vector.
        size = (int)(pos - lastPos);
        //printf("size[%d][%d][%d][%d][%d][%d][%d]\n", i, j,size,(int) std::string::npos, (int)pos, (int)lastPos, size_str);
        if(j==0){
            if(size > SNP_ID_SIZE){
                error("Length of SNPID > 50 [%s]\n", str.substr(lastPos, size).c_str());
            }
            strncpy ( &(m_SNPID[i  * (SNP_ID_SIZE+1)]) , &(str.c_str()[lastPos]), size);
        } else if(j==1 || j==2){
            
            if(size > 1){
                    error("Second column of the Dosage file should be a char [%s]\n", str.substr(lastPos, pos - lastPos).c_str());
            }
            
            if(j==1){
                m_Allele1[i] = str[lastPos];
            } else {
                m_Allele2[i] = str[lastPos];
            }
        } else {
            
            if(size >20){
                
                error("Dosage value size > 20 [%d]\n", size);
            }
            memset(buff, 0, 21* sizeof(char));
            strncpy ( buff, &(str.c_str()[lastPos]), size );
            m_pDosage[j -3] = atof(buff);
            
            
        }
        
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
        j++;
    }
    
    // last element 
    if(lastPos < size_str){
        
        size = (int)(size_str - lastPos);
        if(size >20){
            
            error("Dosage value size > 20 [%d]\n", size);
        }
        memset(buff, 0, 21* sizeof(char));
        strncpy ( buff, &(str.c_str()[lastPos]), size );
        m_pDosage[j -3] = atof(buff);
        j++;
        
    }
    
    
    if(j != m_nSample + 3){
        
        error("The number of elements in line[%d] is not [%d] (%d)\n", i+1,m_nSample+3, j  ); 
    }
    m_POS[i] = m_tempfile.tellp();
    m_tempfile.write ( (char *) m_pDosage, sizeof(float) * m_nSample );
    if(!m_tempfile){
        
        error("Dosage temp file write!\n");
    }
    
    return NO_ERRORS;
    
}



int 	DosageFile::Init(char* filename, int NSample, int *pNSnp){

	int re, NSnp=0;

    Close();
    m_filename = filename;
    
    NSnp = GetLineNum();
    *pNSnp = NSnp;
    
	m_nSample = NSample;
	m_nSNP = NSnp;
	m_BlockSize = m_nSample * sizeof(float);
    m_TotalSize = NSample * NSnp;

    
	m_pbuffer = (char *) F_alloc(m_BlockSize, sizeof(char));
    m_pDosage = (float *) F_alloc(m_nSample, sizeof(float));
	m_SNPID = (char *) F_alloc(NSnp * (SNP_ID_SIZE+1), sizeof(unsigned char));
	m_Allele1 = (char *) F_alloc(NSnp, sizeof(char));
	m_Allele2 = (char *) F_alloc(NSnp, sizeof(char));
	m_POS = (unsigned int *) F_alloc(NSnp, sizeof(unsigned int));
    
    memset(m_SNPID, 0, sizeof(char) * m_nSNP * (SNP_ID_SIZE+1));
    
    
    //Rprintf("Sample [%d] SNP [%d] Block [%d]\n", m_nSample, m_nSNP, m_BlockSize);
    
	m_filename = filename;
    m_tempfilename = m_filename + ".MetaTemp";
 
    if(m_dosage.is_open()){
        m_dosage.close();
    }
	m_dosage.open(m_filename.c_str());
	if (!this->m_dosage)
	{
		re = 20;
        
		return re;
	}

    if(m_tempfile.is_open()){
        m_tempfile.close();
    }
    m_tempfile.open(m_tempfilename.c_str(), std::ios::out|std::ios::binary|std::ios::trunc);
	if (!this->m_tempfile)
	{
		re = 21;
       
		return re;
	}    
    

    re = ReadDosageFile();
    m_tempfile.close();
    
    
    if(m_tempfileRead.is_open()){
        m_tempfileRead.close();
    }
    m_tempfileRead.open(m_tempfilename.c_str(), std::ios::in|std::ios::binary);
	if (!this->m_tempfileRead)
	{
		re = 22;
        //printf("Open %s error!\n",  m_tempfilename.c_str());
		return re;
	} 
    
	return re;
}


int 	DosageFile::Close(){

	if(m_dosage.is_open()){
		m_dosage.close();
	}
	if(m_tempfile.is_open()){
		m_tempfile.close();
	}
	if(m_tempfileRead.is_open()){
		m_tempfileRead.close();
        remove(m_tempfilename.c_str());
	}
    
    F_free(m_pbuffer);
    F_free(m_pDosage);
    F_free(m_SNPID);
    F_free(m_Allele1);
    F_free(m_Allele2);
    F_free(m_POS);
    
    m_pbuffer=NULL;
    m_pDosage=NULL;
    m_SNPID=NULL;
    m_Allele1=NULL;
    m_Allele2=NULL;
    m_POS=NULL;
    

	return 0;
}

/*******************
 idx start from 1
 **********************/
int	DosageFile::ReadData(int * pIdxs, int num, float * pDosage){

	int i, Idx, start, re, total;
    
    total=0;
	for(i=0;i< num;i++){
		Idx = pIdxs[i] -1;
		start = m_POS[Idx];
        
        re = SeekG( start);
        if(re > 0){
            return re;
        }
        
        m_tempfileRead.read(m_pbuffer, m_nSample * sizeof(float));
        memcpy((pDosage + total), m_pbuffer, m_nSample * sizeof(float));
        if(!m_tempfileRead){
            return 23;
        }
        //printf("[%d][%d][%d][%d][%d][%f]\n", i,num, Idx,start, total,pDosage[total] );
        total +=m_nSample ;

        
	}

	return 0;

}


//#define ERORR_BED_SEEK	15	// seekg in bed file read error
//#define ERROR_BED_READ	16	// read in bed file read error


int DosageFile::SeekG(int start){
    
	int idx;
    int pos;
    
    if(start == m_tempfileRead.tellg()){
        return 0;
    }
	
	m_tempfileRead.seekg(start ,std::ios::beg); // +3 because of first 3 bytes in the file
	
    idx=0;
	while(!m_tempfileRead.good()){
		// try one more 
		m_tempfileRead.clear();
		m_tempfileRead.seekg(start ,std::ios::beg);
		
		idx++;
		if(idx >= 5){
			break;
		}
	}
	
	if(!m_tempfileRead.good()){
		return ERORR_BED_SEEK;
	} else{
		pos = m_tempfileRead.tellg();
		if(start != pos){
			return ERORR_BED_SEEK;
		}
	}
    
	return 0;
}

