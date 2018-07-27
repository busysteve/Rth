
library("Rth", lib.loc="~/R/x86_64-pc-linux-gnu-library/3.2")

rthsorttest <- function( base=1, power=1)
{
  srun <- c(0)
  rthrun <- c(0)
  
  for( i in 1:power )
  {
    rdx <- runif( base^i )
    elaps <- system.time( stdsort <- sort( rdx ) )
    srun <- c( srun, elaps[3] ) 
  
    elaps <- system.time( rthsort <- rthsort( rdx ) )
    rthrun <- c( rthrun, elaps[3] ) 
  }
  
  df <- matrix( c( srun, rthrun), 2, byrow = TRUE )
  #df = data.frame( srun, rthrun)
  
  barplot( df, col=c("blue","red"), beside=TRUE, names.arg = c( 0:power ), xlab = c( base, " to the nth power "  ) )
  #ts.plot( df, col=c(rep("blue",1),rep("red",1)) )
}

