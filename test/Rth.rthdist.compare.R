

library("Rth", lib.loc="~/R/x86_64-pc-linux-gnu-library/3.2")

rthdisttest <- function( base=1, power=c(1))
{
  #create an initial set of vectors - The first element will be removed later
  srun <- c(0)
  rthrun <- c(0)
  
  for( i in power )
  {
    dat <- matrix( rnorm(i*i) , i, i );
    elaps <- system.time( std_dist <- dist( dat ) )
    srun <- c( srun, elaps[3] ) 
    elaps <- system.time( rth_dist <- rthdist( dat ) )
    rthrun <- c( rthrun, elaps[3] ) 
  }
  
  df <- matrix( c( srun, rthrun), 2, byrow = TRUE )
  df <- df[,-1]
  
  barplot( df, 
           main="R (dist) vs Rth CUDA (rthdist)", 
           horiz=TRUE, 
           col=c("black","green"), 
           beside=TRUE, 
           names.arg = c( power ), 
           xlab = "Time in seconds", 
           ylab = paste( base, "to the nth power "  ), 
           legend.text = c( "R", "Rth" ) 
  )
}

rthdisttest( 2, seq( 100, 1000,by=100  ) )


