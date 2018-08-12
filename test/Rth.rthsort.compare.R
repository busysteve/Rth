

library("Rth", lib.loc="~/R/x86_64-pc-linux-gnu-library/3.2")

rthsorttest <- function( base=1, power=c(1))
{
  #create an initial set of vectors - The first element will be removed later
  srun <- c(0)
  rthrun <- c(0)
  
  for( i in power )
  {
    rdx <- runif( base^i )
    elaps <- system.time( stdsort <- sort( rdx ) )
    srun <- c( srun, elaps[3] ) 
    elaps <- system.time( rthsort <- rthsort( rdx ) )
    rthrun <- c( rthrun, elaps[3] ) 
  }
  
  df <- matrix( c( srun, rthrun), 2, byrow = TRUE )
  df <- df[,-1]

  barplot( df, 
           main="R vs Rth(CUDA) ", 
           horiz=TRUE, 
           col=c("black","green"), 
           beside=TRUE, 
           names.arg = c( power ), 
           xlab = "Time in seconds", 
           ylab = paste( base, "to the nth power "  ), 
           legend.text = c( "R", "Rth" ) 
        )
}

rthsorttest( 2, 18:24 )


