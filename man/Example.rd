\name{Example}
\alias{Example}
\title{Example dataset}
\description{
Example dataset
}
\format{
  This example dataset has the following objects:
  \describe{
    \item{y.list}{a list object of binary phenotypes. 
    It has 3 elements for 3 study cohorts. Each element is a vector of binary phenotypes.}
    \item{x.list}{a list object of covariates. 
    It has 3 elements for 3 study cohorts. Each element is a matrix of covariates. 
    The first and last elements have two covariates (two columns), and the second element has one covariate (one column).}
    \item{n.g}{a numeric value of the number of cohorts (3).}
    \item{Z.list}{a list object of genotypes of all samples. It has 10 elements for 10 genes. 
    Each element is an nxp matrix with n being the total sample size (3000) and p being the number of SNPs.}
  }
}


