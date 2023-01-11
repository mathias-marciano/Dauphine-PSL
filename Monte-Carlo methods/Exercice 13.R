rm(list=ls())
n<-10000
#Question 1
#Estimation avec une loi Uniforme([0;2])
h1<-function(x){
  return(2*exp(-x**2))
}
estimation1<-function(n){
  X1<-runif(n, 0,2)
  return(mean(2*exp(-X1**2)))
}

#Estimation avec une loi Normale(0,1/2)
h2<-function(x){
  return(sqrt(pi)*(x>=0 & x<=2))
}
estimation2<-function(n){
  X2<-rnorm(n,0,1/sqrt(2))
  return(mean(h2(X2)))
}

#Question2
#Variable antithétique pour la loi Uniforme([0;2])
A1<-function(x){
  return(2-x)
}
estimation1_bis<-function(n){
  X1<-runif(n,0,2)
  return(mean((h1(X1)+h1(A1(X1)))/2))
}
#Variable antithétique pour la loi Uniforme([0;2])
A2<-function(x){
  return(-x)
}
estimation2_bis<-function(n){
  X2<-rnorm(n,0,1/sqrt(2))
  return(mean((h2(X2)+h2(A2(X2)))/2))
}

#Question 3 
#a
#Le moment d'ordre k d'une uniforme([0;2]) est 2**k/k+1
#b
k_star<-function(N){
  H<-numeric(N)
  x<-runif(N,0,2)
  h0_x<-1
  for(k in 1:N){
    h0_x<-(h0_x+((-x**2)**k)/factorial(k))
    H[k]<-cor(h0_x,h1(x))
  }
  return(H)
}
plot(k_star(100))
#On voit que le k optimal est k=10 environ
#On peut alors definir la variable de controle h0(X) tronquée à k=10
h0<-function(x){
  S<-0
  for(i in 0:14){
    S<-S+(((-x**2)**i))/factorial(i)
  }
  return(S)
}
#Estimation de m
m<-0
for(k in 0:10){
  m<-m+((-1)**k)*(2**(2*k))/(factorial(k)*((2*k)+1))
}
#On cherche la valeur du l optimal
l_star<-function(N){
  b_star<-numeric(N)
  X<-runif(N,0,2)
  for(l in 1:N){
    X_bis<-X[1:l]
    S<-0
    S<-(sum((h0(X_bis)-m)*(h1(X_bis)-mean(h1(X_bis)))))/sum((h0(X_bis)-m)**2)
    b_star[l]<-S
  }
  return(b_star)
}
b<-l_star(50)
plot(b)
#On remarque que l est environ égale a 30

#Question 4
#On prend comme variable de strat Z = Unif[0;2]
