rm(list=ls())

#Question 1
tr_norm <- function(n, b, mean, sd){
  x <- numeric(n)
  for (i in 1:n){
    x[i] <-rnorm(1, mean, sd)
    while((x[i] < b) > 0){
      x[i] <- rnorm(1, mean, sd)
    }
  }
  return(x)
}
b<-tr_norm(10000, 2, 0, sqrt(2))

densite<-function(x, b, mean, sd){
  if(x < b){
    return(0)
  } else{
    phi <- pnorm((mean-b)/sd)
    return((1/(phi*sd*sqrt(2*pi)))*exp(-((x-mean)**2)/(2*(sd**2))))
  }
}

hist(b, freq=FALSE)
curve(densite(x,2,0,sqrt(2)),add=TRUE)