 \name{Open_MSSD_File_2Read}
 \alias{Open_MSSD_File_2Read}
 \title{Read Meta SSD and Info files}
 \description{
    Read Meta SSD (MSSD) and Meta Info (MInfo) files.
 }
 \usage{

	Open_MSSD_File_2Read(File.MSSD.vec, File.MInfo.vec)

 }
 \arguments{
    \item{File.MSSD.vec}{a vector of MSSD files. Each element represents a MSSD file of each study.}
    \item{File.MInfo.vec}{a vector of MInfo files. Each element represents a MInfo file of each study.}
}
\value{
	This function returns an data object. The returned object will be used to run MetaSKAT_MSSD_OneSet or MetaSKAT_MSSD_ALL.
}
\details{
 	Users should open MSSD and MInfo files to run MetaSKAT_MSSD_OneSet or MetaSKAT_MSSD_ALL.
 	If all individual level data are available, use MetaSKAT_wZ instead. 
}


\author{Seunggeun Lee}
