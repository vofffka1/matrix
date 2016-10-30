#include<stdio.h>
#include<math.h>

void Input(int n,int A[][100]) {
int i,j;
printf("Enter matrix:");
    for (i=0;i<n;i++)
        for (j=0;j<n;j++)
            scanf("%d",&A[i][j]);
}

void Solver(int A[][100],int n) {
float w0[100],w[100],summ=0,w0norm[100],e,e1,d,d0;
int i,j,k;
printf("Enter E:\n");
scanf("%f", &e1);
for (i=0;i<n;i++) w0[i]=0;
w0[0]=1;

    do {
        for (i=0;i<n;i++) summ=summ+w0[i]*w0[i];
        d0=sqrt(summ);
        for (i=0;i<n;i++) w0norm[i]=w0[i]/d0;
            for (i=0;i<n;i++) {
                w[i]=0;
                for (j=0;j<n;j++) w[i]=w[i]+A[i][j]*w0norm[j];
            }
        summ=0;
        for (i=0;i<n;i++) summ=summ+w[i]*w[i];
        d=sqrt(summ);
        e=fabs(d-d0);
        for (i=0;i<n;i++) w0[i]=w[i];
        summ=0;
    }
    while(e>e1);

printf("%f\n",d);
for (i=0;i<n;i++) printf("%f\n",w0norm[i]);
}

void main() {
int n,A[100][100];
printf ("Enter N:\n");
scanf("%d",&n);
Input(n,A);
Solver(A,n);
}
