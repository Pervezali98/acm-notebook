#include <bits/stdc++.h> 
#define MOD 1000000007

using namespace std;
typedef long long ll;

//Square Matix Only
struct Matrix{
    int len; //dimension of square matrix
    vector<vector<ll> >mat;
    Matrix(int l=2)
    {
        len=l;
        mat=vector<vector<ll> >(l,vector<ll>(l,0));
    }
    void setToUnitMatrix()
    {
        for(int i=0;i<len;i++)    {
            mat[i][i]=1;
        }
    }
};

//A and B are both square matrices and both have equal dimension
//It multiplies A and B and stores into A
void MatMult(Matrix& A, Matrix& B)
{
    int dim=A.len;
    Matrix tmp(dim);
    for(int i=0;i<dim;i++)    {
        for(int j=0;j<dim;j++)    {
            for(int k=0;k<dim;k++)    {
                tmp.mat[i][j]+=A.mat[i][k]*B.mat[k][j];
                tmp.mat[i][j]%=MOD;
            }
        }
    }
    for(int i=0;i<dim;i++)    {
        for(int j=0;j<dim;j++)    {
            A.mat[i][j]=tmp.mat[i][j];
        }
    }
}

//Calculates A^r and returns. 
Matrix MatExp(Matrix& A,ll r)
{
    int dim=A.len;
    Matrix ret(dim);
    ret.setToUnitMatrix();
    while(r)    {
        if(r&1)    {
            MatMult(ret,A);
        }
        MatMult(A,A);
        r=r/2;
    }
    return ret;
}