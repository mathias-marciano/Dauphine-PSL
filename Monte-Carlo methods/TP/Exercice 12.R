rm(list=ls())

#Question 1
g<-function(x,y){
  lambda=(1+sqrt(3))/2
  return(lambda*exp(-lambda*(y-2))*(y>=2)*(3/2)*exp(-(3/2)*x))
}

h_tilde<-function(x,y){ #h_tilde = f(Z)h(Z)/g(Z)
  return((sqrt(x+y)*sin(y**4)*exp(-(3/2)*x-(y**2)/4))/g(x,y))
}


e_pref<-function(N){
  X<-rexp(N,3/2)
  Y<-rexp(N,(1+sqrt(3))/2)+2
  return(mean(h_tilde(X,Y)))
}

#Question 2
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


