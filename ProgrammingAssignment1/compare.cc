#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<sstream>
using namespace std;

void add(int *A,int *B,int *C,int size){
  for(int i=0;i<size;i++){
    *(C+i)= *(A+i)+ *(B+i);
  }
}
void sub(int *A,int *B,int *C,int size){
  for(int i=0;i<size;i++){
    *(C+i)= *(A+i)- *(B+i);
  }
}



void multiply(int *A,int *B,int *C,int n){
  //mod 101
  for(int i=0;i<n*n;i++){
    *(A+i)=*(A+i) %101;
    *(B+i)=*(B+i) %101;
  }


  if(n<=1){
    *C = (*A) * (*B);
    return;
  }else if(n>1){
    int *ptr_M1=new int[n*n/4];
    int *ptr_M2=new int[n*n/4];
    int *ptr_M3=new int[n*n/4];
    int *ptr_M4=new int[n*n/4];
    int *ptr_M5=new int[n*n/4];
    int *ptr_M6=new int[n*n/4];
    int *ptr_M7=new int[n*n/4];
    int *ptr_A11=new int[n*n/4];
    int *ptr_A12=new int[n*n/4];
    int *ptr_A21=new int[n*n/4];
    int *ptr_A22=new int[n*n/4];
    int *ptr_B11=new int[n*n/4];
    int *ptr_B12=new int[n*n/4];
    int *ptr_B21=new int[n*n/4];
    int *ptr_B22=new int[n*n/4];
    int *ptr_tmp1=new int[n*n/4];
    int *ptr_tmp2=new int[n*n/4];


    //divide A to A11 A12 A21 A22 & divide B to B11 B12 B21 B22
    for(int i=0;i<n/2;i++){
      int* temp_address_A11=A+(0*(n*n/2)+0*(n/2))+i*n;
      int* temp_address_A12=A+(0*(n*n/2)+1*(n/2))+i*n;
      int* temp_address_A21=A+(1*(n*n/2)+0*(n/2))+i*n;
      int* temp_address_A22=A+(1*(n*n/2)+1*(n/2))+i*n;
      int* temp_address_B11=B+(0*(n*n/2)+0*(n/2))+i*n;
      int* temp_address_B12=B+(0*(n*n/2)+1*(n/2))+i*n;
      int* temp_address_B21=B+(1*(n*n/2)+0*(n/2))+i*n;
      int* temp_address_B22=B+(1*(n*n/2)+1*(n/2))+i*n;
      for(int j=0;j<n/2;j++){
        *(ptr_A11+i*(n/2)+j)= *(temp_address_A11+j);
        *(ptr_A12+i*(n/2)+j)= *(temp_address_A12+j);
        *(ptr_A21+i*(n/2)+j)= *(temp_address_A21+j);
        *(ptr_A22+i*(n/2)+j)= *(temp_address_A22+j);
        *(ptr_B11+i*(n/2)+j)= *(temp_address_B11+j);
        *(ptr_B12+i*(n/2)+j)= *(temp_address_B12+j);
        *(ptr_B21+i*(n/2)+j)= *(temp_address_B21+j);
        *(ptr_B22+i*(n/2)+j)= *(temp_address_B22+j);
      }
    }



    //make M1~M7
    // cout<<"  M1=(A11+A22)(B11+B22)"<<endl;
    add(ptr_A11,ptr_A22,ptr_tmp1,n*n/4);
    add(ptr_B11,ptr_B22,ptr_tmp2,n*n/4);
    multiply(ptr_tmp1,ptr_tmp2,ptr_M1,n/2);
    // cout<<"  M2=(A21+A22)B11"<<endl;
    add(ptr_A21,ptr_A22,ptr_tmp1,n*n/4);
    multiply(ptr_tmp1,ptr_B11,ptr_M2,n/2);
    // cout<<"  M3=A11(B12-B22)"<<endl;
    sub(ptr_B12,ptr_B22,ptr_tmp1,n*n/4);
    multiply(ptr_A11,ptr_tmp1,ptr_M3,n/2);
    // cout<<"  M4=A22(B21-B11)"<<endl;
    sub(ptr_B21,ptr_B11,ptr_tmp1,n*n/4);
    multiply(ptr_A22,ptr_tmp1,ptr_M4,n/2);
    // cout<<"  M5=(A11+A12)B22"<<endl;
    add(ptr_A11,ptr_A12,ptr_tmp1,n*n/4);
    multiply(ptr_tmp1,ptr_B22,ptr_M5,n/2);
    // cout<<"  M6=(A21-A11)(B11+B12)"<<endl;
    sub(ptr_A21,ptr_A11,ptr_tmp1,n*n/4);
    add(ptr_B11,ptr_B12,ptr_tmp2,n*n/4);
    multiply(ptr_tmp1,ptr_tmp2,ptr_M6,n/2);
    // cout<<"  M7=(A12-A22)(B21+B22)"<<endl;
    sub(ptr_A12,ptr_A22,ptr_tmp1,n*n/4);
    add(ptr_B21,ptr_B22,ptr_tmp2,n*n/4);
    multiply(ptr_tmp1,ptr_tmp2,ptr_M7,n/2);

    delete [] ptr_A11;
    delete [] ptr_A12;
    delete [] ptr_A21;
    delete [] ptr_A22;
    delete [] ptr_B11;
    delete [] ptr_B12;
    delete [] ptr_B21;
    delete [] ptr_B22;

    int *ptr_C11=new int[n*n/4];
    int *ptr_C12=new int[n*n/4];
    int *ptr_C21=new int[n*n/4];
    int *ptr_C22=new int[n*n/4];

    //make C11 C12 C21 C22
    // cout<<"   C11=M1+M4-M5+M7"<<endl;
    add(ptr_M1,ptr_M4,ptr_tmp1,n*n/4);
    sub(ptr_tmp1,ptr_M5,ptr_tmp2,n*n/4);
    add(ptr_tmp2,ptr_M7,ptr_C11,n*n/4);
    // cout<<"   C12=M3+M5"<<endl;
    add(ptr_M3,ptr_M5,ptr_C12,n*n/4);
    // cout<<"   C21=M2+M4"<<endl;
    add(ptr_M2,ptr_M4,ptr_C21,n*n/4);
    // cout<<"   C22=M1-M2+M3+M6"<<endl;
    sub(ptr_M1,ptr_M2,ptr_tmp1,n*n/4);
    add(ptr_tmp1,ptr_M3,ptr_tmp2,n*n/4);
    add(ptr_tmp2,ptr_M6,ptr_C22,n*n/4);

    delete [] ptr_M1;
    delete [] ptr_M2;
    delete [] ptr_M3;
    delete [] ptr_M4;
    delete [] ptr_M5;
    delete [] ptr_M6;
    delete [] ptr_M7;
    delete [] ptr_tmp1;
    delete [] ptr_tmp2;

    //put C11~C22 into C
    for(int i=0;i<n/2;i++){
      int* temp_address_C11=C+(0*(n*n/2)+0*(n/2))+i*n;
      int* temp_address_C12=C+(0*(n*n/2)+1*(n/2))+i*n;
      int* temp_address_C21=C+(1*(n*n/2)+0*(n/2))+i*n;
      int* temp_address_C22=C+(1*(n*n/2)+1*(n/2))+i*n;
      for(int j=0;j<n/2;j++){
        *(temp_address_C11+j)=  *(ptr_C11+i*(n/2)+j);
        *(temp_address_C12+j)=  *(ptr_C12+i*(n/2)+j);
        *(temp_address_C21+j)=  *(ptr_C21+i*(n/2)+j);
        *(temp_address_C22+j)=  *(ptr_C22+i*(n/2)+j);
      }
    }


    delete [] ptr_C11;
    delete [] ptr_C12;
    delete [] ptr_C21;
    delete [] ptr_C22;

  }
}

void Strassen(int *A,int *B,int *C,int M,int N,int K){
  int Z=1;//2^0
  while (Z<max(max(M,N),K)) {
    Z*=2;
  }

  int *AA=new int[Z*Z];
  int *BB=new int[Z*Z];
  int *CC=new int[Z*Z];

  //fill A & B with 0
  for(int i=0;i<Z;i++){
    for(int j=0;j<Z;j++){
      if(i<N && j<M){
        *(AA+i*Z+j)=*(A+M*i+j);
      }else{
        *(AA+i*Z+j)=0;
      }
      if(i<M && j<K){
        *(BB+i*Z+j)=*(B+K*i+j);
      }else{
        *(BB+i*Z+j)=0;
      }
    }
  }

  multiply(AA,BB,CC,Z);


  //put ans into C
  for(int i=0;i<N;i++){
    for(int j=0;j<K;j++){
      *(C+i*K+j)= *(CC+i*N+j);
    }
  }
}


void tradition(int *A,int *B,int *C,int n){

  //mod 101
  for(int i=0;i<n*n;i++){
    *(A+i)=*(A+i) %101;
    *(B+i)=*(B+i) %101;
  }


  //clean C
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      *(C+i*n+j)=0;
    }
  }


  //calculating~~~
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      for(int k=0;k<n;k++){
          *(C+n*i+j) += *((A+n*i+k))* (*(B+k*i+j));
      }
    }
  }

}

int main(){
  ofstream outfile;
  outfile.open("test_result.txt");


  //Start testing~~~
  for(int n=1;n<=1024;n++){
    int A[n][n];
    int B[n][n];
    int C[n][n];

    //make data by rand()
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        A[i][j]=rand()%101;
        B[i][j]=rand()%101;
      }
    }

    int t_Strassen_start=clock();
    multiply(&A[0][0],&B[0][0],&C[0][0], n);
    int t_Strassen_end=clock();



    //traditional method~~~
    int t_tradition_start=clock();
    tradition(&A[0][0],&B[0][0],&C[0][0], n);
    int t_tradition_end=clock();


    outfile<<n<<" "<<t_Strassen_end-t_Strassen_start;
    outfile<<" "<<t_tradition_end-t_tradition_start<<endl;
    cout<<"n="<<setw(4)<<n<<" t_Strassen="<<setw(4)<<t_Strassen_end-t_Strassen_start;
    cout<<" t_tradition="<<setw(4)<<t_tradition_end-t_tradition_start<<endl;

  }

  outfile.close();


  return 0;
}
