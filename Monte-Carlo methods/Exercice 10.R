rm(list=ls())

#Question 1-a
h1 <- function(N){
  x<-runif(N,0,5)
  y<-rnorm(N, 0, sqrt(2))
  H1<-sqrt((x+y)*(y>=2))*sin(y**4)*exp((-3*x)/2)*10*sqrt(pi)
  return(mean(H1))
}

#Question 1-b
h2 <- function(N){
  x<-rexp(N,3/2)                             
  y<-rnorm(N, 0, sqrt(2))
  H2<-sqrt((x+y)*(y>=2)*(x>=0 & x<=5))*sin(y**4)*(4/3)*sqrt(pi)
  return(mean(H2))
}  

#Question 1-c
tr_norm <- function(n, b, mean, sd){ #Permet de générer la loi normale tronquée
  x <- numeric(n)
  for (i in 1:n){
    x[i] <-rnorm(1, mean, sd)
    while((x[i] < b) > 0){
      x[i] <- rnorm(1, mean, sd)
    }
  }
  return(x)
}

h3 <- function(N){
  x<-rexp(N,3/2)                             
  y<-tr_norm(N, 2, 0, sqrt(2))
  H3<-sqrt((x+y)*(x>=0 & x<=5))*sin(y**4)*(2/3)*sqrt(4*pi)*pnorm(-2/sqrt(2))
  return(mean(H3))
}


#Question 2 - cout de calcul
library(microbenchmark)
N<-10000
microbenchmark(h1(N),h2(N),h3(N))
#Conclusion : l'algorithme h1 est le plus performant; puis h2 puis de loin h3

