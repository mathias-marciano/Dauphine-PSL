rm(list=ls())

#Question 1
methode_classique <-function(N){
  return(mean(rcauchy(N)>=50))
}

#Question 2 (installer au prélable la library Pareto)
#a
#a=50 car le support de hf doit etre inclus dans celui de g
#k=1 car le terme h(X)f(X)/g(X) doit être bornee en +infini
#b
h<-function(X){
  return(X>=50)
}

f<-function(X){
  return(1/((1+X**2)*pi))
}

g<-function(X){ #pour k=1 et a=50
  return(50/X**(2))
}

e_pref <- function(N, a, k){
  Z<-rPareto(N, a, k)
  return(mean(f(Z)*h(Z)*(1/g(Z))))
}

#Question 3
library(microbenchmark)
N<-10000
a<-50
k<-1
microbenchmark(methode_classique(N),e_pref(N,a,k))
#Conclusion : la methode d'échantillonage préférentiel est plus efficace
