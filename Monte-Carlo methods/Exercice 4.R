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

mu<-c(1,2)
V<-matrix(c(4,3,3,9), nrow=2, ncol=2)
L<-t(chol(V))
X<-c()



