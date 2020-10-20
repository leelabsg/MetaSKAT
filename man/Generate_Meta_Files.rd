 \name{Generate_Meta_Files}
 \alias{Generate_Meta_Files}
 \alias{Generate_Meta_Files_FromDosage}
 \title{Generate summary statistics files}
 \description{
    Generate Meta SSD (MSSD) and Meta Info (MInfo) files. 
    Both files are needed to run MetaSKAT with summary statistics.
 }
 \usage{

	Generate_Meta_Files(obj, File.Bed, File.Bim
	, File.SetID, File.MSSD, File.MInfo, N.Sample
	, File.Permu = NULL, data=NULL, impute.method="fixed")
	
	Generate_Meta_Files_FromDosage(obj, File.Dosage
	, File.SetID, File.MSSD, File.MInfo, N.Sample
	, File.Permu=NULL, data=NULL, impute.method="fixed")


 }
 \arguments{
    \item{obj}{returned object from SKAT_Null_Model. }
    \item{File.Bed}{name of the binary ped file (BED).}
    \item{File.Bim}{name of the binary bim file (BIM).}
    \item{File.SetID}{name of the SNP set ID file. The first column must be Set ID, and the second column must be SNP ID. There should be no header!!}
    \item{File.MSSD}{name of the MSSD file that will be generated.}
    \item{File.MInfo}{name of the MInfo file that will be generated.}
    \item{N.Sample}{number of samples.}
    \item{File.Permu}{name of a file that will have score statistics from permuted phenotypes (currently internal use only).}
    \item{data}{an optional data frame containing the variables in the model (default=NULL). If it is NULL, the variables are taken from environment(formula).}
    \item{impute.method}{a method to impute missing genotypes (default= "fixed"). "bestguess" imputes missing genotypes as the most likely values(0,1,2), 
    "random" imputes missing genotypes by generating binomial(2,p) random variables (p = MAF), and "fixed" imputes missing genotypes by assigning the mean genotype values (2p).}
    \item{File.Dosage}{name of the dosage file. The dosage file must not have a header.}
}
\details{
	These functions generate summary statistic files (MSSD and MInfo files) from plink binary files. 
	To run meta analysis, each study should provide both MSSD and MInfo files. 
	The MSSD is a binary file with between-SNP information matrices, 
	and MInfo is a text file with information on study cohorts and SNPsets. 
	
	If users want to use dosages instead of hard call genotypes, 
	Generate_Meta_Files_FromDosage should be used instead of Generate_Meta_Files. 
	The dosage file should follow the plink dosage file format with a single dosage value per each 
	SNP (Format=1 in plink). The first three columns should be SNP ID, allele type1 (a1) and allele type2 (a2). 
	After the first three columns, there should be N.Sample columns of dosage data. 
	Each column represents each sample, and the order of samples should be matched with the order in
	phenotypes and covariates used in SKAT_Null_Model.  
	
		ex) 
		
		rs0001	A	T 	0.1	0.2 
		
		rs0002	C	G	1.2	0 	
	
	Dosage value is the expected number of a2 copies, and 0 .. 2 scale. So the value 
	0.1 indicates that the expected number of copy of a2 is 0.1. 
		
}


\author{Seunggeun Lee}
