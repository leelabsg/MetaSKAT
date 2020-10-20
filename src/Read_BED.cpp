#include "RFunc.h"
#include "Read_BED.h"
#include "error_messages.h"


BedFile::BedFile(){

	m_pbuffer= NULL;

	m_nSample = 0;
	m_nSNP = 0;
	m_BlockSize = 0;

}
BedFile::~BedFile(){

    
	Close();
    

}


int 	BedFile::Init(char* filename, int NSample, int NSnp){

	int re;
    Close();
    
	m_nSample = NSample;
	m_nSNP = NSnp;
	m_BlockSize = (m_nSample+3)/4;
	m_pbuffer = (unsigned char *) F_alloc(m_BlockSize, sizeof(unsigned char));
	if(!m_pbuffer){
		re = ERORR_BIM_OPEN_FILE4READ;
		return re;
	}
    


    //Rprintf("Sample [%d] SNP [%d] Block [%d]\n", m_nSample, m_nSNP, m_BlockSize);
    
	m_filename = filename;
	m_bed.open(m_filename.c_str(), std::ios::binary);

	if (!this->m_bed)
	{
		re = ERORR_BIM_OPEN_FILE4READ;
		return re;
	}

	re = Check();
	return re;
}


int 	BedFile::Close(){

	if(m_bed.is_open()){
		m_bed.close();
	}

    if(m_pbuffer != NULL){
        //delete [] m_pbuffer;
        F_free(m_pbuffer);
        m_pbuffer=NULL;
	}
    
	return 0;
}

/************************************************
	Check magic number

*************************************************/
int 	BedFile::Check(){

	// 3 bit magic number and mode
	// magic number : 01101100 00011011
	// mode : 00000001 (SNP Major) 00000000 (IND major)
	int re = NO_ERRORS;
	m_bed.read((char *)m_magic_number,3 * sizeof(unsigned char)); // three first bytes - permanent in bed file

	if(m_magic_number[0] != 0x6C || m_magic_number[1] != 0x1B){
		re = ERORR_BIM_MAGIC_NUM;
	}
	if(m_magic_number[2] != 0x01){
		re = ERORR_BIM_NOT_SNP_MOD;
	}

	// read
	m_bed.seekg (0, std::ios::end);
    m_FileSize = m_bed.tellg();
    m_bed.seekg (0, std::ios::beg);
	//Rprintf("Length[%d]\n", length);
	return re;

}

int	BedFile::GetStartByte(int SNP_Idx){

	int re ;
	re = 3 + m_BlockSize * (SNP_Idx-1) ;
	return re;

}

/*******************
 idx start from 1
 **********************/
int	BedFile::ReadData(int * pIdxs, int num, unsigned char * Genotype){

	int i,Idx, start, re;
	for(i=0;i< num;i++){
		Idx = pIdxs[i];
		start = i * m_nSample;
		re = ReadDataOne(Idx, (Genotype + start));
		
		if(re > 0){
			return re;
		}
	}

	return 0;

}


//#define ERORR_BED_SEEK	15	// seekg in bed file read error
//#define ERROR_BED_READ	16	// read in bed file read error


int BedFile::SeekG(int start){

	int idx=0;
	if(m_FileSize < start){
		return ERORR_BED_FILESIZE;
	}
	
    if(start == m_bed.tellg()){
        return 0;
    }
    
	m_bed.seekg(start ,std::ios::beg); // +3 because of first 3 bytes in the file
	
	while(!m_bed.good()){
		// try one more 
		m_bed.clear();
		m_bed.seekg(start ,std::ios::beg);
		
		idx++;
		if(idx >= 5){
			break;
		}
	}
	
	if(!m_bed.good()){
		return ERORR_BED_SEEK;
	} else{
		m_debugPos = m_bed.tellg();
		if(start != m_debugPos){
			return ERORR_BED_SEEK;
		}
	}

	return 0;
}


int BedFile::ReadFile(int start){

	int re;
	m_bed.read((char *)m_pbuffer,m_BlockSize);
	m_debuglength = m_bed.gcount();
	//Rprintf("-[%d]",m_debuglength);
	if( m_debuglength  != m_BlockSize){
		m_bed.clear();
		re = BedFile::SeekG(start);
		if(re > 0){
			return re;
		}
	} else{
		return 0;
	}
	
	m_bed.read((char *)m_pbuffer,m_BlockSize);
	m_debuglength = m_bed.gcount();
	//Rprintf("-[%d]",m_debuglength);
	if( m_debuglength  != m_BlockSize){
		return ERROR_BED_READ;
		return 0;
	}
	//Rprintf("\n");
	return 0;
}


int	BedFile::ReadDataOne(int Idx, unsigned char * Genotype){

	int i,j,k, temp;
	int start = GetStartByte(Idx);
	int re;
	re = SeekG( start);
	if(re > 0){
		return re;
	}
	
	re = ReadFile( start);
	if(re > 0){
		//Rprintf("IDX[%d], start[%d][%d], Read[%d][%d], First k[%d], Sample-k [%d]\n",Idx, start,m_debugPos, m_BlockSize,m_debuglength, k, m_nSample-k);
		//return 0;
		return re;
	}
		
	k=0;
	for(i=0;i<m_BlockSize-1;i++){
		Decoding(m_pbuffer[i]);
		for(j=0;j<4;j++){
			Genotype[k] = 	m_decode_out[j];
            //Rprintf("%c",Genotype[k]);
			k++;
		}
	}
    
	/* last block */
	Decoding(m_pbuffer[i]);
    temp = m_nSample-k;
	for(j=0;j< temp ;j++){
		Genotype[k] = 	m_decode_out[j];
        //Rprintf("%d",(int)Genotype[k]);
		k++;
	}
    //Rprintf("\n");
	return 0;

}

int	BedFile::Decoding(unsigned char bitval){

	int i,j,k;
	unsigned char temp[2];
	k=0;
	for(i=0;i<4;i++){
		for(j=0;j<2;j++){
			temp[j] = (bitval >> k) & 1;
			k++;
		}

		if(temp[0] ==0 && temp[1] ==0){
			m_decode_out[i] = 0;
		} else if(temp[0] ==1 && temp[1] ==1){
			m_decode_out[i] = 2;
		} else if(temp[0] ==0 && temp[1] ==1){
			m_decode_out[i] = 1;
		} else {
			m_decode_out[i] = 9;
		}
	}

	return 0;

}


