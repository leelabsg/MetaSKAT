 \name{MetaSKAT_wZ}
 \alias{MetaSKAT_wZ}
 \title{Meta analysis SKAT with individual level genotype data}
 \description{
    Meta analysis SKAT with individual level genotype data.
 }
 \usage{

MetaSKAT_wZ(Z, obj, combined.weight=TRUE, weights.beta=c(1,25), 
method="davies", r.corr=0, is.separate = FALSE, Group_Idx=NULL, 
impute.method="fixed",impute.estimate.maf=1, missing_cutoff=0.15)


 }
\arguments{
      \item{Z}{a numeric genotype matrix with each row as a different individual and each column as a separate snp. 
      Each genotype should be coded as 0, 1, 2, and 9 (or NA) for AA, Aa, aa, and missing, 
      where A is a major allele and a is a minor allele. Missing genotypes will be imputed using observed MAFs. }
      \item{obj}{an output object from the Meta_Null_Model function. }
    \item{combined.weight}{a logical value (default=TRUE) for the type of weighting. 
	If it is TRUE, a weight for each SNP is computed using MAFs that are common across studies. 
	If it is FALSE, group specific weights will be used based on group specific MAFs.} 
     \item{weights.beta}{a numeric vector of parameters of beta weights (default=c(1,25))}
     \item{method}{a method to compute a p-value (default= "davies"). 
      "davies" represents an exact method that computes a p-value by inverting the characteristic function of the mixture chisq dist.,
       and "optimal" represents the optimal test (SKAT-O) that is based on an optimal linear combination  of burden and SKAT statistics.
       "optimal" is equivalent to "optimal.adj" in the SKAT function.}      
      \item{r.corr}{the \eqn{\rho} parameter for the compound symmetric correlation structure kernel (default= 0). If r.corr=0, it does the SKAT test.  If r.corr=1, it does the burden test. 
      If r.corr=(a vector of grid values between 0 and 1), it does SKAT-O. r.corr will be ignored if method="optimal". See the manual of SKAT.}
      \item{is.separate}{a logical value (default=FALSE) for homogeneous(=FALSE) or heterogeneous(=TRUE) genetic effects
      of a SNP set across studies.
      When FALSE, it is assumed that all studies share the same causal variants with the same effect size. 
      When TRUE, it is assumed that studies/groups may have different causal variants. }  
      \item{Group_Idx}{a vector of group indicator (default=NULL). 
      If a vector of integers are specified, it assumes causal variants are the same for studies with the same group index, and different for studies  with different group indexes.
      When NULL, studies are assumed to be in different groups with different group indexes.
      When is.separate=FALSE, it will be ignored.}
      \item{impute.method}{a method to impute missing genotypes (default= "fixed"). "bestguess" imputes missing genotypes as the most likely values(0,1,2), 
      "random" imputes missing genotypes by generating binomial(2,p) random variables (p = MAF), and "fixed" imputes missing genotypes by assigning the mean genotype value (2p).}
      \item{impute.estimate.maf}{ a numeric value indicating how to estimate MAFs for the imputation. If
          impute.estimate.maf=1 (default), MetaSKAT uses study-specific MAFs, in which each study MAFs will be used for the imputation. 
          If impute.estimate.maf=2, all samples in the Z matrix will be used to calculate MAFs for
          the imputation. If impute.estimate.maf=3, MetaSKAT uses group-specific MAFs.
          Previous versions (< ver 0.6) used impute.estimate.maf=2 as a default.}
      \item{missing_cutoff}{a cutoff of the missing rates of SNPs (default=0.15). If the first study has SNPs with missing rates higher than the cutoff, 
       these SNPs in the study will be excluded from the analysis. However, the same SNPs in other studies will not be excluded, if their missing rates are lower than the cutoff. The missing
      rates are calculated study by study.}
}
\value{
	\item{p.value}{p-value. }
	\item{param}{estimated parameters of each method.}   
	\item{param$Is_Converged}{ (only with method="davies") an indicator for the convergence. 1 indicates convergence and 0 otherwise. 
	When 0 (not converged), "liu" method will used to compute a p-value. }  
}
\details{
	The rows of Z should be matched with phenotypes and covariates. 
	If there are 3 studies, and study 1,2, and 3 have n1, n2, and n3 samples, 
	the first n1, n2, and n3 rows of Z should be genotypes of the first, second, and third studies, respectively.

	Group_Idx is a vector of group index. Suppose the first two studies are European-based and the last study is African American-based.
	If you want to run MetaSKAT with assuming ancestry group specific heterogeneity, you can set Group_Idx=c(1,1,2), which indicates
	the first two studies belong to the same group. 
	
	The four methods in the MetaSKAT paper can be run with the following parameters: 
	\enumerate{
	\item Hom-Meta-SKAT:  combined.weight=TRUE, is.separate=FALSE 
	\item Hom-Meta-SKAT-O: combined.weight=TRUE, is.separate=FALSE, method="optimal" 
	\item Het-Meta-SKAT:  combined.weight=FALSE, is.separate=TRUE 
	\item Het-Meta-SKAT-O: combined.weight=FALSE, is.separate=TRUE, method="optimal" 
	}
}


\author{Seunggeun Lee}

\examples{


data(Example)
attach(Example)

#############################################################
#	Compute a p-value of the first gene

obj<-Meta_Null_Model(y.list, x.list, n.cohort=3, out_type="D")

# rho=0
MetaSKAT_wZ(Z.list[[1]], obj)$p.value

# rho=1 (burden test)
MetaSKAT_wZ(Z.list[[1]], obj, r.corr=1)$p.value


# optimal test
MetaSKAT_wZ(Z.list[[1]], obj, method="optimal")$p.value

# cohort specific weights
MetaSKAT_wZ(Z.list[[1]], obj, combined.weight=FALSE)$p.value


# Seperate = TRUE
# Assume heterogeneous genetic effect 
MetaSKAT_wZ(Z.list[[1]], obj, combined.weight=FALSE, is.separate = TRUE)$p.value


# Group

# the first two cohorts are in the same group.
Group_Idx=c(1,1,2)
MetaSKAT_wZ(Z.list[[1]], obj, combined.weight=FALSE, is.separate = TRUE,Group_Idx=Group_Idx)$p.value

# all three cohorts are in different group.
Group_Idx=c(1,2,3)
MetaSKAT_wZ(Z.list[[1]], obj, combined.weight=FALSE, is.separate = TRUE,Group_Idx=Group_Idx)$p.value



}


