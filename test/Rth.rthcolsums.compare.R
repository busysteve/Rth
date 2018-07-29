
library("Rth", lib.loc="~/R/x86_64-pc-linux-gnu-library/3.2")


rthcolsumstest <- function( x=1, y=1, z=1 )
{

  dat <- matrix( rnorm(x*y) , x, y );
  time1 <- system.time( for( i in 1:z) { t1 <- colSums( dat ) } )[3];
  time2 <- system.time( for( i in 1:z) { t2 <- rthcolsums( dat ) } )[3];

  
  return( time1 - time2);
}

rthcolsumstest( 100, 100, 10 )

