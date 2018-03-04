/****************************************************************************/
/**
 * @file		filename
 * @brief		
 * @details		
 * @author		Linh N.Van 
 * @version		1.00
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 *  Ver   	Who			Date			Changes
 *  ------	----------	--------------	--------------------------------------
 *  1.00	Linh N.Van	8/5/2017       	First release
 *
 *</pre>
 *
 * @date		8/5/2017
 * @pre			First initialize the system.
 * @bug			No known bug.
 * @warning		No warning.
 * @copyright	Copyright (c) 2017.
 *				All Rights Reserved. This program is the confidential and proprietary
 *				product of author. Any Unauthorized use, reproduction or transfer
 *				of this program is strictly prohibited.
 * @note		No Note at the moment.
 *
******************************************************************************/



/***************************** Include Files *********************************/
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
//#include <alloc.h>  
/**************************** Type Definitions *******************************/
typedef struct tagNODE
{
	int Key;
	struct tagNODE *pNext;

} NODE, *NODEPTR;  //danh sach ten bien cau truc 
				   // con tro cau truc 
				   //sizeof NODE =8 
				   //sizeof NODEPTR =4	
/************************** Constant Definitions *****************************/
#define M  100  // khai bao bang bam co 100 phan tu
/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/
NODEPTR Bucket[M]; // mang cau truc 


/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
 // tao node cho key
NODEPTR GetNode(void)
{
	NODEPTR p; // da sua 
	//printf("sizeof p = \n", sizeof(p));  // sizeof p= 4
	p->Key =0;
	p->pNext=NULL;
	return p;  // tra ve 1 mang cau truc 
}


/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
int Hashfunc(int key)
{
	return(key%M);
}


/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
// khhoi tao cac bucket
void initBucket()
{
	int b;
	for(b=0;b <M ;b++)
		Bucket[b]=NULL;
}

/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
//kiem tra 1 bucket b co rong hay khong
int EmptyBucket(int b)
{
	return(Bucket[b] == NULL ? 1: 0);
}


/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
// kiem tra bang bam xem co rong khong
int empty()
{
	int b;
	for (b = 0;b<M;b++)
	     if(Bucket[b] !=NULL)  return(-1);
	return(1);
}




/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
//Tac vu Push; them nut moi vao dau Bucket b
void Push(int b, int x)
{
      NODEPTR p;
      p = GetNode();
      p-> Key = x;
      p-> pNext =Bucket[b];
      Bucket[b] = p;
}


/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
// tac vu Pop lay node tu Bucket ra 
int Pop(int b)
{
	NODEPTR p;
	if (EmptyBucket(b))
	 {
	 	printf("\n Bucket %d  rong \n",b );
	 	return  0;
	 } 
	 p= Bucket[b];
	 int k=p->Key;
	 Bucket[b]=p->pNext;
	 free (p);
	 return k;

}


/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
//Tac vu InsAfter:them nut moi vao Bucket sau nut p
void InsAfter (NODEPTR q, int k)
{
	NODEPTR p;
	if (p == NULL)
		printf("Khong them node moi duoc \n");

	else
	{
		q=GetNode();
		q->Key=k;
		q->Key=p->pNext;
		p->pNext=q;
	}

}

/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
//Tac vu DelAfter:Xoa nut trong Bucket trong nut p
int DelAfter (NODEPTR q)
{
	NODEPTR p;
	if(p==NULL || p->pNext==NULL)
	{
		printf("khong xoa node duoc \n");
	}
	q=p->pNext;
	int k=q->Key;
	p->pNext =q->pNext;
	free(q);
	return k;
}

/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
////Tac vu place:tac vu nay chi su dung khi them nut vao Bucket da co thu tu 
void place(int b, int k)
{
	NODEPTR p,q=NULL; 
	
	for(p=Bucket[b]; p!=NULL && k>p->Key; p=p->pNext)
		q=p;
	if(q==NULL)
		Push(b,k);
	else
		InsAfter(q,k);
}

/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
// them phan tu co khoa k vao bang bam
void Insert(int k)
{
	int b;
	b=Hashfunc(k);
	place(b,k);
}

/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
void Remove (int k)
{
	  int b;
      NODEPTR p,q;
      b = Hashfunc(k);
      p = Bucket[b]; // da sua roi 
      while(p!=NULL && p->Key !=k)
      {
            q = p;
            p = p->pNext;
      }
      if (p == NULL)
            printf("\n Khong co nut co khoa %d", k);
      else if (p == Bucket[b])
            Pop(b);              
      else
            DelAfter(q); 
}

/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
//Tac vu ClearBucket;xoa tat ca cac nut trong Bucket b
void ClearBucket (int b)
{
      NODEPTR p = Bucket[b], q = NULL;// q la nut truoc , p la nut sau
      while(p !=NULL)
      {
            q = p;
            p = p->pNext;
            Bucket[b] = NULL;//khoi dong Bucket b
      }
}

/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
//Tac vu Clear: xoa tat ca cac nut trong bang bam
void Clear( )
{
	  int b;
      for (b=0; b<M; b++)
            ClearBucket(b);
}
  
/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
//Tac vu TraverseBucket:duyet Bucket b
void TraverseBucket(int b)
{
      NODEPTR p = Bucket[b];
      while (p !=NULL)
      {
            printf("%3d",p->Key);
            p = p->pNext;
      }
}

/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
//Tac vu Traverse:duyet bang ham
void Traverse()
{
	  int b;
      for (b=0;b<M;b++)
      {
            printf("\nBucket %d:",b);
            TraverseBucket(b);
      }
}

 
/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
int Search(int k)
{
      int b = Hashfunc(k);
      NODEPTR p = Bucket[b];
      while (k > p->Key && p !=NULL)  // tai sao lai la so lon hon 
            p = p->pNext;
      if (p == NULL || k!=p->Key) //khong tim thay
            return -1; 
      else // tim thay
            return 1;
}

/************************** Function Definitions *****************************/
/**
 * @brief		
 * @param [in]	
 * @return		
 * @note		None.
 */
void main()
{

	initBucket();  // khoi tao M bucket cua bang bam, cho bang NULL
	int key;
	scanf("%d",&key);
    Insert(key); 
	//Insert(10);
	//Search(10);// cho vao core dump
	//Clear();

}
