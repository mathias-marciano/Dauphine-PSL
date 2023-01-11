rm(list=ls())

rejet_boucle<-function(n){
  x <- numeric(n)
  
  for (i in 1:n){
    x[i] <- runif(1, -1, 1)
    u <- runif(1)
    while(u > sqrt(1 - x[i]**2)){
      x[i] <- runif(1, -1, 1)
      u <- runif(1)
    }
  }
  return(x)
}

hist(rejet_boucle(1000000),freq=FALSE)