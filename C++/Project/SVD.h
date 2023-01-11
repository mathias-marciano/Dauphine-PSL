//Fichier utilisé uniquement pour TenseurSVD pour eviter les problemes de surdefinition au niveau de la classe Matrice

#define SVDD2
#include <iostream>
#include <cmath>
using namespace std;

void givens(float x, float z, float &c, float &s){
    if(z == 0){
        c = 1;
        s = 0;
    } else {
        if(abs(z) > abs(x)){
            float tau = -x/z;
            s = 1/sqrt(1+pow(tau,2));
            c = s * tau;
        } else {
            float tau = -z/x;
            c = 1/sqrt(1+pow(tau,2));
            s = c * tau;
        }
    }
}

Vecteur householder(Vecteur x, float &B){
    float sigma = dot(x.subvec(1, x.getDimension()-1), x.subvec(1, x.getDimension()-1));
    Vecteur v = x;
    v[0] = 1;
    if(sigma == 0 and x[0]>=0){
        B = 0;
    } else if(sigma == 0 and x[0] < 0){
        B = 2;
    } else {
        float mu = sqrt(pow(x[0],2) + sigma);
        if(x[0] <= 0){
            v[0] = x[0] - mu;
        } else {
            v[0] = -sigma/(x[0]+mu);
        }
        B = 2*pow(v[0],2)/(sigma + pow(v[0], 2));
        float k = 1/v[0];
        v = k * v;
    }
    return v;
}

int signe(int a){
    if(a >=0){
        return 1;
    } else {
        return -1;
    }
}
Matrice reductridiag(Matrice &D){
    int l = D.getLines();
    float d = (D[l-2][l-2] - D[l-1][l-1])/2;
    float mu = D[l-1][l-1] - pow(D[l-1][l-2],2)/(d + signe(d) * sqrt(pow(d,2) + pow(D[l-1][l-2],2)));
    float x = D[0][0] - mu;
    float z = D[1][0];
    float tab_z[l];
    for(int i=0;i<l;i++){
        tab_z[i] = 1;
    }
    Vecteur z_vec(tab_z, l);
    Matrice Z(z_vec);
    for(int k=0;k<l-1;k++){
        float c = 0;
        float s = 0;
        givens(x, z, c, s);
        //Application de la rotation de Givens à droite
        for(int j=0;j<l;j++){
            float tau_1 = D[k][j];
            float tau_2 = D[k+1][j];
            D[k][j] = c*tau_1 - s*tau_2;
            D[k+1][j] = s*tau_1 + c*tau_2;
            tau_1 = Z[k][j];
            tau_2 = Z[k+1][j];
            Z[k][j] = c*tau_1 - s*tau_2;
            Z[k+1][j] = s*tau_1 + c*tau_2;
        }
        //Application de la rotation de Givens à gauche
        for(int j=0;j<l;j++){
            float tau_1 = D[j][k];
            float tau_2 = D[j][k+1];
            D[j][k] = c*tau_1 - s*tau_2;
            D[j][k+1] = s*tau_1 + c*tau_2;
        }
        if(k < l-2){
            x = D[k][k+1];
            z = D[k][k+2];
        }
    }
    return Z;
}

//Tester si une matrice est diagonale
bool isDiag(Matrice A){
    if(A.getLines() == A.getCols()){
        int n = A.getLines();
        for(int i=0;i<n;i++){
            for(int j = 0;j<n;j++){
                if(i != j){ //Si on se trouve hors de la diagonale
                    if(A[j][i] != 0){
                        return 0;
                    }
                }
            }
        }
        return 1;
    } else {
        cout <<"La matrice doit etre carre"<<endl;
        return 0;
    }
}

//Tester si une matrice est tridiagonale
bool isTriDiag(Matrice A){
    if(A.getLines() == A.getCols()){
        if(isDiag(A) == 0){ //Si la matrice n'est pas diagonale
            int n = A.getLines();
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(abs(j-i) > 1){ //Si on se situe hors de la tridiagonale
                        if(A[j][i] != 0){
                            return 0;
                        }
                    }
                }
            }
        }
        return 1;
    } else {
        cout <<"La matrice doit etre carre"<<endl;
        return 0;
    }
}

Matrice qrsym(Matrice &A){
    int n = A.getLines();
    float tab_q[n];
    for(int i=0;i<n;i++){
        tab_q[i] = 1;
    } 
    Vecteur q(tab_q, n);
    Matrice Q(q);
    // Phase 1 : Tridiagonalisation de la matrice A

    for(int k=1;k<n-1;k++){
        float B = 0;
        Vecteur A_tilde = A[k-1];
        A_tilde = A_tilde.subvec(k,n-1);
        Vecteur v = householder(A_tilde, B);
        Matrice A_p = A.submat(k,n-1,k,n-1);
        Vecteur p = B * A_p.mvprod(v);
        Vecteur w = p - (B/2) * dot(p, v) * v;
        A[k-1][k] = norm(A_tilde);
        A[k][k-1] = A[k-1][k];
        
        //Modification Matrice A((k+1):n,(k+1):n) et Q((k+1):n,(k+1):n)
        Matrice v_w = outer(v, w);
        Matrice w_v = outer(w, v);
        Matrice v_v = outer(v, v);
        
        for(int i=0;i<n-k;i++){
            for(int j=0;j<n-k;j++){
                A[k + j][k + i] = A[k + j][k + i] - v_w[j][i] - w_v[j][i];
                Q[k + j][k + i] = Q[k + j][k + i] - B * v_v[j][i] * Q[k + j][k + i];
            }
        }
    }
    Matrice T(n, n);
    for(int j=n;j>0;j--){
        T[j-1][j-1] = A[j-1][j-1];
        if(j>1){
            T[j-1][j-2] = A[j-2][j-1];
            T[j-2][j-1] = T[j-1][j-2];
        }
    }
    // Phase 2 : Diagonalisation de T et mise a jour de Q
    while(isDiag(T) == 0){
        for(int i=1;i<n;i++){
            //Gestion des erreurs numeriques
            if(abs(T[i][i-1]) + abs(T[i-1][i]) <= pow(10, -9) * (abs(T[i-1][i-1]) + abs(T[i][i]))){                    T[i][i-1] = 0;
                T[i-1][i] = 0;
            }
        }
        
        int P=0;
        int Q_coef=0;
        float tab_T2[] = {0};
        Vecteur c1(tab_T2,1);
        Matrice T1(c1);
        Matrice T2(c1);
        Matrice T3(c1);
        if(n ==2){ //Cas particulier n=2
            T2 = T;
        } else if(n==3) { //Cas particulier n=3
            T2 = T.submat(0,1,0,1); //On prend comme candidat pour T2 la premiere matrice 2x2 de T
            if(isTriDiag(T2)==0){ //Si elle n'est pas tridiagonale, on prend celle des deux dernieres lignes
                T2=T.submat(1,2,1,2);
                T1 = T.submat(0,0,0,0);
                P = 1;
            } else {
                T3 = T.submat(2,2,2,2);
                Q_coef = 1;
            }
        } else {
            for(int p=1;p<n;p++){
                for(int q=1;q<n-p;q++){
                    T1 = T.submat(0,p-1,0,p-1);
                    if(n-p-q != 0){
                        T2 = T.submat(p, n-q-1, p, n-q-1);
                        T3 = T.submat(n-q, n-1, n-q, n-1);
                        if(isDiag(T1)==1 and isDiag(T3)==1 and isTriDiag(T3)==1){
                            P = p;
                            Q_coef = q;
                        }
                    } else {
                        T3 = T.submat(n-q, n-1, n-q, n-1);
                        if(isDiag(T1)==1 and isDiag(T3)==1){
                            P = p;
                            Q_coef = q;
                        }
                    }
                }
            }
        }
        if(P+Q_coef<n){
            Matrice Z = reductridiag(T2);
            Matrice QQ(n,n);
            for(int i=0;i<P;i++){ //Partie I(p) 
                for(int j=0;j<P;j++){
                    if(i==j){
                        QQ[j][i] = 1;
                    }
                }
            }
            for(int i=n-Q_coef;i<n;i++){ //Partie I(q) 
                for(int j=n-Q_coef;j<n;j++){
                    if(i==j){
                        QQ[j][i] = 1;
                    }
                }
            }
            for(int i=P;i<n-Q_coef;i++){
                for(int j=P;j<n-Q_coef;j++){
                    T[j][i] = T2[j-P][i-P];
                    QQ[j][i] = Z[j-P][i-P];
                }
            }
            float k = 1/2;
            T = k * (T + T.transpose());
            Q = Q * QQ;
        }
    }
    return Q;
}
/*
int tab_max(float tab, int taille){
    int indice_max = 0;
    for(int i=1;i<taille;i++){
        if(tab[i] > tab[indice_max]){
            indice_max = i;
        }
    }
    return indice_max;
}*/

int plusPetit(float tab[], float tau, int debut, int fin){
    for(int i=debut;i<fin;i++){
        if(tab[i]==tau){
            return i;
        }
    }
    return 0;
}

Matrice qrpivot(Matrice A, Matrice &Q){
    int m = A.getLines();
    int n = A.getCols();
    float B;  
    //Initialisation matrice Pi
    Matrice Pi(n,n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j){ //Si on se situe sur la diagonale
                Pi[j][i] = 1;
            }
        }
    }
    float c[n];
    for(int j=0;j<n;j++){
        c[j] = dot(A[j].subvec(0,m-1), A[j].subvec(0,m-1));
    }
    
    int r = 0;
    float c_max = c[0];
    for(int j=1;j<n;j++){
        if(c[j] > c_max){
            c_max = c[j];
        }
    }
    float tau = c_max;
    while(tau > 0 and r < n){
        r = r + 1;
        int k = plusPetit(c, tau, r-1, n);

        //Permutation de A(1:m,r) et de A(1:m,k)
        Vecteur Permute_1 = A[r-1].subvec(0, m-1);
        Vecteur Permute_2 = A[k].subvec(0, m-1);
        for(int i=0;i<m;i++){
            A[r-1][i] = Permute_2[i];
            A[k][i] = Permute_1[i];
        }
        //Permutation de ck et cr
        float c_r = c[r-1];
        float c_k = c[k];
        c[r-1] = c_k;
        c[k] = c_r;
        //Permutation de Pi(1:m,r) et de Pi(1:m,k)
        Vecteur Permute_Pi_1 = Pi[r-1].subvec(0, n-1);
        Vecteur Permute_Pi_2 = Pi[k].subvec(0, n-1);

        for(int i=0;i<n;i++){
            Pi[r-1][i] = Permute_Pi_2[i];
            Pi[k][i] = Permute_Pi_1[i];
        }
        
        Vecteur v = householder(A[r-1].subvec(r-1, m-1), B);
        Matrice v_v = outer(v, v);
        Matrice A_aux = A.submat(r-1, m-1, r-1, n-1);
        Matrice v_A = v_v * A_aux;
        for(int i=r-1;i<m;i++){
            for(int j=r-1;j<n;j++){
                A[j][i] = A[j][i] - B * v_A[j - r + 1][i - r + 1];
            }
        }
        
        for(int i=r;i<m;i++){
            A[r-1][i] = v[i - r + 1];
        }
        
        for(int i=r;i<n;i++){
            c[i] = c[i] - pow(A[i][r-1],2);
        }
        
        if(r < n){
            tau = c[r];
            for(int i=r+1;i<n;i++){
                if(c[i] > tau){
                    tau = c[i];
                }
            }
        } else {
            tau = 0;
        }
    }
    //Calcul de Q
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            if(i==j){
                Q[j][i] = 1;
            } else {
                Q[j][i] = 0;
            }
        }
    } 
    Vecteur v(m);
    for(int j=n-1;j>-1;j--){
        v[j] = 1; 
        if(j+1 <= m-1){
            for(int i=j+1;i<m;i++){
                v[i] = A[j][i];
            }
            B = 2.0/(1.0 + pow(norm(A[j].subvec(j+1,m-1)),2));
        }
        else {
            B = 2.0;
        }
        Matrice v_v_2 = outer(v.subvec(j,m-1), v.subvec(j,m-1));
        Matrice Q_aux = Q.submat(j, m-1, j, m-1);
        Matrice v_Q = v_v_2 * Q_aux;
        for(int l=j;l<m;l++){
            for(int i=j;i<m;i++){
                    Q[i][l] = Q[i][l] - B * v_Q[i-j][l-j];
            }
        }
    }
    return Pi;
}

Matrice* svd(Matrice A, Matrice *tab){
    int m = A.getLines();
    int n = A.getCols();
    if(m >= n){
        Matrice A_t_A = A.transpose() * A;
        Matrice Q1 = qrsym(A_t_A);
        
        Matrice A_Q1 = A * Q1;
        Matrice Q2(m,m);
        Matrice Pi = qrpivot(A_Q1, Q2);
        
        Matrice R = Q2.transpose() * A_Q1 * Pi;
        
        for(int j =0;j<n;j++){
            if(R[j][j] < 0){
                for(int i=0;i<m;i++){
                    Q2[j][i] = -Q2[j][i];
                }
            }
        }
        R = Q2.transpose() * A_Q1 * Pi;
        *tab = Q2;
        *(tab+1) = R;
        *(tab+2) = Q1 * Pi;
    } else {
        Matrice A_t_A2 = A * A.transpose();
        Matrice Q1 = qrsym(A_t_A2);
        Matrice A_Q1 = A.transpose() * Q1;
        Matrice Q2(n,n);
        Matrice Pi_2 = qrpivot(A_Q1, Q2);
        Matrice R = Q2.transpose() * A_Q1 * Pi_2;
        for(int i=0;i<m;i++){
            if(R[i][i] < 0){
                for(int j=0;j<n;j++){
                    Q2[i][j] = -Q2[i][j];
                }
            }
        }
        
        R = Q2.transpose() * A_Q1 * Pi_2;
        *tab = Q1 * Pi_2;
        *(tab+1) = R.transpose();
        *(tab+2) = Q2;
    }
    return tab;
}