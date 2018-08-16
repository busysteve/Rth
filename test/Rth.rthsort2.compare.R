

library("Rth", lib.loc="~/R/x86_64-pc-linux-gnu-library/3.2")

rthsorttest2 <- function( base=1, power=c(1))
{
  #create an initial set of vectors - The first element will be removed later
  srun <- c(0)
  rthrun <- c(0)
  rthrun2 <- c(0)
  
  for( i in power )
  {
    rdx <- runif( base^i )
    elaps <- system.time( stdsort <- sort( rdx ) )
    srun <- c( srun, elaps[3] ) 
    elaps <- system.time( rthsrt <- rthsort( rdx ) )
    rthrun <- c( rthrun, elaps[3] ) 
    
    #elaps <- system.time( rthsrt2 <- sort( rdx ) )
    elaps <- system.time( rthsrt2 <- rthsort2( rdx ) )
    rthrun2 <- c( rthrun2, elaps[3] ) 
    
    #print ( all.equal( stdsort, rthsrt2 ) )
    
    #print ( summary( stdsort ) )
    #print ( summary( rthsrt2 ) )
    
    #print ( head( stdsort, 10 ) )
    #print ( head( rthsrt2, 10 ) )
    
    #print ( tail( stdsort, 10 ) )
    #print ( tail( rthsrt2, 10 ) )

    #dat <- matrix( c( stdsort, rthsrt2), 3, byrow = TRUE )
    
    
    #barplot( dat, 
    #         main="Sort Compare", 
    #         horiz=FALSE, 
    #         #col=c( "black", "green", "lightblue" ), 
    #         col=c( "black", "lightblue" ), 
    #         beside=TRUE, 
    #         names.arg = c( 1:2 ), 
    #         xlab = "Time in seconds", 
    #         ylab = paste( base, "to the nth power "  ), 
    #         #legend.text = c( "R", "Rth", "Rth2" ) 
    #         legend.text = c( "R", "Rth2" ) 
    #)
    
        
  }
  
  df <- matrix( c( srun, rthrun, rthrun2), 3, byrow = TRUE )
  #df <- matrix( c( srun, rthrun2), 2, byrow = TRUE )
  df <- df[,-1]

  barplot( df, 
           main="R vs Rth(CUDA) ", 
           horiz=TRUE, 
           col=c( "black", "green", "lightblue" ), 
           #col=c( "black", "red" ), 
           beside=TRUE, 
           names.arg = c( power ), 
           xlab = "Time in seconds", 
           ylab = paste( base, "to the nth power "  ), 
           legend.text = c( "R", "Rth", "Rth2" ) 
           #legend.text = c( "R", "Rth2" ) 
  )
}

#rthsorttest2( 2, 24 )
rthsorttest2( 2, 25:27 )


