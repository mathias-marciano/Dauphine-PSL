#Exercice2
#Question 1
n<-1000
U<-runif(n)
x<--1/2*(log(1-U))
hist(x, freq=FALSE)
lines(y <- seq(0, 4, 0.1),dexp(y,2))

#Question2
generer_exp <- function(n, lambda){
  U<-runif(n)
  x<--1/lambda*log(1-U)
  return(x)
}

Y<-c()
for(i in 1:1000){
  Y<-c(Y, sum(generer_exp(10, 1.5)))
}
hist(Y,freq = FALSE)
lines(y <- seq(0, 15, 0.1),dgamma(y,10,1.5))

#Question 3
generer_gamma <- function(nb, n, lambda){
  Z<-c()
  for(i in 1:nb){
    Z<-c(Z, sum(generer_exp(n, lambda)))
  }
  return(Z)
}

generer_poisson <- function(n, lambda){
  P<-numeric(n)
  for(i in 1:n){
    j<-1
    Gamma<-generer_gamma(1, 1, lambda)
    while(Gamma<=1){
      j<-j+1
      Gamma<-generer_gamma(1, j, lambda)
    }
    P[i]<-j-1
  }
  return(P)
}
P<-generer_poisson(1000, 4)
hist(P, freq=FALSE)
lines(y <- seq(0, 7, 0.2),dpois(y,4))

