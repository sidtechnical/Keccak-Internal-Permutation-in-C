// I have implemented my code in c based on the psuedo code in keccak.noekeon.org/specs_summary.html and based on The Keccak reference 3.0
/* Also I have refered "GPU Implementation of the Keccak Hash Function Family" by Pierre-Louis Cayrel et.al International Journal of Security
and Its Applications Vol.5 No. 4, October,2011 */
/* For the implementation of bit rotation I have refered gist.github.com/clemensg/3833651( which is the Ruby Implementation */
/* For a better understanding of optimal code, I have refered "Implementation of cryptographic hash functions on the
Android opearing system — A Chalmers project" by Pierre Karpman, Thibault Verdon */

/* For the better understanding of code(for myself), I have written the psuedo code and comments alongside my code snippet where and when possible */



/* implementation of the internal permutation of Keccak with a 1600-bit state*/


#include "stdio.h"
#include "stdlib.h"
#include "KeccakF1600.h"

/*Function Definations */
unsigned long** rounds(unsigned long**,unsigned long);
unsigned long** theta_step(unsigned long**);
unsigned long** pi_step(unsigned long**);
unsigned long** x_step(unsigned long** ,unsigned long**);
unsigned long rot(unsigned long, unsigned int);
 

//The offset constants
const char r[5][5]={{0,36,3,41,18},{1,44,10,45,2},{62,6,43,15,61},{28,55,25,21,56},{27,20,39,8,14}};

//The round constants
const unsigned long RC[24]={0x0000000000000001, 0x0000000000008082,
			    0x800000000000808A, 0x8000000080008000,
			    0x000000000000808B, 0x0000000080000001,
			    0x8000000080008081, 0x8000000000008009,
			    0x000000000000008A, 0x0000000000000088,
			    0x0000000080008009, 0x000000008000000A,
			    0x000000008000808B, 0x800000000000008B,
			    0x8000000000008089, 0x8000000000008003,
			    0x8000000000008002, 0x8000000000000080,
			    0x000000000000800A, 0x800000008000000A,
			    0x8000000080008081, 0x8000000000008080,
			    0x0000000080000001, 0x8000000080008008 };


//Return the state after 24 rounds
//Do not modify the name of this fonction  
unsigned long** KeccakF(unsigned long** INPUT)
{
	/*For better understanding of the code, this functions calls all the steps seperately*/
	unsigned long** temp_arr=malloc(5*sizeof(unsigned long)); //using a temporary array,by copying the INPUT to 24 rounds, return the same 
	int i,j,k,l;						  //declaration of iteration variables
    for(i=0;i<5;i++)
   {
      temp_arr[i]=malloc(5*sizeof(unsigned long));                //Dynamically allocating 5 blocks of memory space
    }
    
    for(j=0;j<5;j++)
	{
	  for(k=0;k<5;k++)
	   {
	    temp_arr[j][k] = INPUT[j][k];			//copying INPUT to the temporary array
	   }
        }
  
	for(l=0;l<24;l++){
    		temp_arr=rounds(temp_arr, RC[l]);		//calling the rounds fucntion 24 times
  	}
	return temp_arr;
}


/* Rounds function defination -  this whole set of functions run 24 times*/
unsigned long** rounds(unsigned long** INPUT,unsigned long RC)
{
	unsigned long** A;
	A=theta_step(INPUT);					//calling the θ step
	unsigned long **B=pi_step(A);				//calling to  ρ and π steps
	A=x_step(A,B);						//calling the χ step
	A[0][0]=A[0][0]^RC;					//defination of ι step -- A[0,0] = A[0,0] xor RC
	return A;						//returning the output from all the above steps
}

// θ step Defination
unsigned long** theta_step(unsigned long** INPUT)
{
	unsigned long *c=malloc(5*sizeof(unsigned long));	//Dynamically allocating 5 blocks of memory space
	unsigned int i,j,k,l;					//declaration of iteration variables	
	for(i=0; i<5; i++) 					//forall x in 0…4
	{
		//C[x] = A[x,0] xor A[x,1] xor A[x,2] xor A[x,3] xor A[x,4]
		c[i] ^= INPUT[i][0]^INPUT[i][1]^INPUT[i][2]^INPUT[i][3]^INPUT[i][4];
	}
	unsigned long *d=malloc(5*sizeof(unsigned long));
	for(j=0;j<5;j++)					//forall x in 0…4
		{
		     //D[x] = C[x-1] xor rot(C[x+1],1) -- This has been modified as per the instructions in Noppa: Q4 as modulo 5
			d[j]=c[(j+4)%5]^rot(c[(j+1)%5],1);
		}
	for(k=0; k<5; k++)					//forall (x,y) in (0…4,0…4)
		{
		for(l=0; l<5; l++)
			{
				//A[x,y] = A[x,y] xor D[x]
				INPUT[k][l] ^= d[k];
			}
		}
	return INPUT;
}

// ρ and π steps Defination
unsigned long** pi_step(unsigned long **A)
{
	unsigned long **B=malloc(5*sizeof(unsigned long));
	unsigned int i,j,k;					//declaration of iteration variables
	for(i=0;i<5;i++){
		B[i]=malloc(5*sizeof(unsigned long));		//Dynamically allocating 5 blocks of memory space
	}
	for(j=0; j<5; j++){					//forall (x,y) in (0…4,0…4)
		for(k=0; k<5; k++)
		{
/*B[y,2*x+3*y] = rot(A[x,y], r[x,y])  -- Call to bit rotation function and Modulo 5 addition and multiplication as per guidelines in Noppa */
			B[k][(((2*j)%5)+((3*k)%5))%5] = rot(A[j][k],r[j][k]);
		}
	}
	return B;
}

// χ step Defination
unsigned long** x_step(unsigned long **A,unsigned long **B)
{
	unsigned int i,j;					//declaration of iteration variables
	for(i=0; i<5; i++) 
		{ 						//forall (x,y) in (0…4,0…4)
		  for(j=0; j<5; j++)
		   {
			/* A[x,y] = B[x,y] xor ((not B[x+1,y]) and B[x+2,y])-- modulo 5 arithmetic */
			A[i][j] = B[i][j] ^ ((~B[(i+1)%5][j]) & B[(i+2)%5][j]);
		   }	
	        }
	return A;
}

// 64 Bit rotation function defination -- implementation similar to rotl64 inbuilt function
unsigned long rot(unsigned long x,unsigned int y){
unsigned long m,n; 
m = 1 << 64;
n = ((x << y) | (x >> (64 - y))) & (m-1);
return n;
}
