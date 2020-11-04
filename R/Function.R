Check_Class<-function(obj, class_type){
  re<-TRUE
  if(!any(class(obj) %in% class_type)){
    re<-FALSE
  }
  return(re)
}

Is_TryError<-function(obj){
  
  re<-Check_Class(obj, "try-error")
  return(re)
}

Check_File_Exists<-function(FileName){
  
  if(!file.exists(FileName)){
    Msg<-sprintf("File %s does not exist\n",FileName)
    stop(Msg)
  }
  
}

# Simple Imputation
# Z : an n x p genotype matrix with n samples and p SNPs
# Missing : a missing genotype value. Default is 9

Impute<-function(Z, impute.method){
  
  p<-dim(Z)[2]
  
  if(impute.method =="random"){
    for(i in 1:p){
      IDX<-which(is.na(Z[,i]))
      if(length(IDX) > 0){
        maf1<-mean(Z[-IDX,i])/2
        Z[IDX,i]<-rbinom(length(IDX),2,maf1)
      }
    }
  } else if(impute.method =="fixed"){
    for(i in 1:p){
      IDX<-which(is.na(Z[,i]))
      if(length(IDX) > 0){
        maf1<-mean(Z[-IDX,i])/2
        Z[IDX,i]<-2 * maf1
      }
    }
  } else if(impute.method =="bestguess") {
    
    for(i in 1:p){
      IDX<-which(is.na(Z[,i]))
      if(length(IDX) > 0){
        maf1<-mean(Z[-IDX,i])/2
        Z[IDX,i]<-round(2 * maf1)
      }
    }
    
  } else {
    stop("Error: Imputation method shoud be \"fixed\", \"random\" or \"bestguess\" ")
  }
  
  return(Z)
}


Beta.Weights<-function(MAF,weights.beta, Cutoff=1, Is.MAF=TRUE){

	n<-length(MAF)
	weights<-rep(0,n)
	Sign<-rep(1,n)
	
	IDX1<-which(MAF > 0.5)
	if(length(IDX1) > 0){
		Sign[IDX1]<--1
		MAF[IDX1]<-1-MAF[IDX1]
	}
	 

	
	IDX_0<-union(which(MAF == 0), which(MAF > Cutoff))
	if(length(IDX_0) == n){
		#stop("No polymorphic SNPs")
		weights<-rep(0,n)
	} else if( length(IDX_0) == 0){
		weights<-dbeta(MAF,weights.beta[1],weights.beta[2])
	} else {
		weights[-IDX_0]<-dbeta(MAF[-IDX_0],weights.beta[1],weights.beta[2])
	}

	weights = weights * Sign	
	#if(!Is.MAF){
	#	weights1<<-weights
	#	MAF1<<-MAF
	#} else {
	#	weights2<<-weights
	#	MAF2<<-MAF
	#}
	

	return(weights)
	
}

