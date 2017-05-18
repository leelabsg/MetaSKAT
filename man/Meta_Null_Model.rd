 \name{Meta_Null_Model}
 \alias{Meta_Null_Model}
 \alias{Meta_Null_Model_EmmaX}
 \title{Get parameters and residuals from H0}
 \description{
     Compute model parameters and residuals under the null model (H0) of no associations. 
     It can be used only when individual level data are available.
 }
 \usage{

Meta_Null_Model(y.list, x.list, n.cohort, out_type="C",  n.Resampling=0)
Meta_Null_Model_EmmaX(y.list, x.list, n.cohort, K.list=NULL, Kin.File.list=NULL)

 }
\arguments{
      \item{y.list}{a list object for phenotypes. Each element should be a vector of phenotypes. If you have 3 cohorts, it should have 3 elements.}
      \item{x.list}{a list object for covariates. Each element should be a vector or a  matrix of covariates. If there are 3 cohorts, it should have 3 elements. 
      If there are no covariates to adjust for, the element should be "intercept". See the examples.}
      \item{n.cohort}{a numeric value of the number of cohort.}
      \item{out_type}{an indicator for the outcome type. "C" for continuous outcomes and "D" for dichotomous outcomes.} 
      \item{n.Resampling}{internal use only.}    
      
      \item{K.list}{a list object of the kinship matrices. If K.list=NULL, the function reads files in Kin.File.list to obtain kinship matrices.}
      \item{Kin.File.list}{a list object of emmax-kin output file names. } 
}
\value{
	It returns an object that has model parameters and residuals. The returned object will be used to run MetaSKAT_wZ. 
}


\author{Seunggeun Lee}

\examples{


data(Example)
attach(Example)

#############################################################
#	Compute a p-value of the first gene

obj<-Meta_Null_Model(y.list, x.list, n.cohort=3, out_type="D")
MetaSKAT_wZ(Z.list[[1]], obj)$p.value

#############################################################
#	If you want to use the intercept-only model for the 2nd cohort

x.list[[2]]<-"intercept"
obj<-Meta_Null_Model(y.list, x.list, n.cohort=3, out_type="D")
MetaSKAT_wZ(Z.list[[1]], obj)$p.value


}


