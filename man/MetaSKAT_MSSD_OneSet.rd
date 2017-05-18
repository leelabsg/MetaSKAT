 \name{MetaSKAT_MSSD_OneSet}
 \alias{MetaSKAT_MSSD_OneSet}
 \alias{MetaSKAT_MSSD_ALL}
 \title{Meta analysis SKAT with summary data from each study cohort.}
 \description{
    Meta analysis SKAT with Meta SSD (MSSD) and Info (MInfo) files. MetaSKAT_MSSD_OneSet computes a p-value for a given set,
    and MetaSKAT_MSSD_ALL computes p-values for all sets.
 }
 \usage{

MetaSKAT_MSSD_OneSet(Cohort.Info, SetID, combined.weight=TRUE, weights.beta=c(1,25),
method="davies", r.corr=0, is.separate = FALSE, Group_Idx=NULL, MAF.cutoff=1, 
missing_cutoff=0.15)

MetaSKAT_MSSD_ALL(Cohort.Info, ...)

 }
\arguments{
    \item{Cohort.Info}{output object from Open_MSSD_File_2Read. }
	\item{SetID}{a character value of set id to test.} 
    \item{combined.weight}{a logical value (default=TRUE) for a type of weighting. See MetaSKAT_wZ page for details.} 
     \item{weights.beta}{a numeric vector of parameters for the beta weights (default=c(1,25))}
     \item{method}{a method to compute a p-value (default= "davies"). See MetaSKAT_wZ page for details.}
      \item{r.corr}{the \eqn{\rho} parameter for the compound symmetric correlation structure kernels (default= 0). See MetaSKAT_wZ page for details.}
      \item{is.separate}{a logical value (default=FALSE) for homogeneous(=FALSE) or heterogeneous(=TRUE) genetic effects
      of a SNP set across studies. See MetaSKAT_wZ page for details.}  
      \item{Group_Idx}{a vector of group indicator (default=NULL). See MetaSKAT_wZ page for details.}
      \item{MAF.cutoff}{a cutoff of the MAFs of SNPs (default=1). Any SNPs with MAFs > MAF.cutoff will be excluded from the analysis.}
      \item{missing_cutoff}{a cutoff of the missing rates of SNPs (default=0.15). See MetaSKAT_wZ page for details.}
      \item{...}{the same parameters of MetaSKAT_MSSD_OneSet after SetID.}
}
\value{
	MetaSKAT_MSSD_OneSet and MetaSKAT_wZ return the same object. See MetaSKAT_wZ for details.
	MetaSKAT_MSSD_ALL returns a dataframe with SetIDs (first column) and p-values (second column). 
}

\details{
	Please see MetaSKAT_wZ for details.

}


\author{Seunggeun Lee}

\references{

Lee, S., Teslovich, T., Boehnke, M., Lin, X. (2013)
General framework for meta-analysis of rare variants in sequencing association studies.  \emph{American Journal of Human Genetics}, 93, 42-53. 

}

