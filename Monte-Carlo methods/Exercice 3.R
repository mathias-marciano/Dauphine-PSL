#Question 1
BM <- function(n){
  if(n%%2==0){
    U1<-runif(n/2)
    U2<-runif(n/2)
  } else {
    U1<-runif(n/2)
    U2<-runif(n/2)
  }
  X1<-sqrt(-2*log(U1))*cos(2*pi*U2)
  X2<-sqrt(-2*log(U1))*sin(2*pi*U2)  
  return(c(X1,X2))
}

X<-BM(1000)
#Question 2
hist(X, freq=FALSE)
lines(y<-seq(-4, 4, 0.1), dnorm(y))
