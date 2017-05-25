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


Print_Error_CODE<-function(code){
  
  if(code == 0 ){
    return(0);
  } else if(code == 2){
    stop("Error Can't open BED file")
  } else if(code == 3){
    stop("Error BED file magic number is not correct")
  } else if(code == 4){
    stop("Error BED file is not SNP save mode")
  } else if(code == 5){
    stop("Error Can't open MSSD file")
  } else if(code == 6){
    stop("Error Can't open MSSD file")
  } else if(code == 7){
    stop("Error MSSD file magic number is not correct")
  } else if(code == 8){
    stop("Error CRC check is not correct")
  } else if(code == 9){
    stop("Error Size of the set is too large! Number of SNPs in a set cannot be larger than 20000")
  } else if(code == 10){
    stop("Error Init to MatFile object!")
  } else if(code == 11){
    stop("Error MatFile object hasn't been created")
  } else {
    MSG<-sprintf("Error [%d]\n",code)
    stop(MSG)
  }
  
  return(1)
  
}


Print_Error_SSD<-function(code){

	if(code == 0 ){
		return(0);
	} else if(code == 1){
		stop("Error Can't open BIM file")
	} else if(code == 2){
		stop("Error Can't open FAM file")
	} else if(code == 3){
		stop("Error Can't open BED file")
	} else if(code == 4){
		stop("Error Can't open SETID file")
	} else if(code == 5){
		stop("Error Can't write MSSD file")
	} else if(code == 6){
		stop("Error Can't read MSSD file")
	} else if(code == 7){
		stop("Error Can't write INFO file")
	} else if(code == 8){
		stop("Error Can't read INFO file")
	} else if(code == 9){
		stop("Error Can't write INFO file")
	} else if(code == 13){
		stop("Error Wrong SNP or Individual sizes")
	} else if(code == 14){
		stop("Error SetID not found")
	} else {
		MSG<-sprintf("Error [%d]\n",code)
		stop(MSG)
	}
	
	return(1)
}


Check_File_Exists<-function(FileName){
	
	if(!file.exists(FileName)){
		Msg<-sprintf("File %s does not exist\n",FileName)
		stop(Msg)
	}

}

MetaSKAT_Is_IsLittleEndian<-function(){

	re<-0
	temp<-.C("IsLittleEndian", as.integer(re))
	re1<-temp[[1]]
	
	if(re1 == 0){
		stop("MSSD files can only be used on a little endian machine")
	}
}



