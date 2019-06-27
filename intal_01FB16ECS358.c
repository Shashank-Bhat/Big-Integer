#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include<assert.h>
#include<ctype.h>
void* intal_create(const char* str)
{
   
   int k=0;
   char *filter = (char*)malloc(sizeof(char)*strlen(str));//filter array to stop processing if it encounters a Letter in the beginning or to process integers until it encounters a character
   if(!isdigit(str[0]) || strcmp(str,"0")==0)
   {
     strcpy(filter,"0");
     return filter;
   }
   else
   {
     for(int i=0;i<strlen(str);i++)
     {
       if(!isdigit(str[i]))
         break;
       else
       {
         filter[k] = str[i];
         k++;
       }
     }
   }
   int i=0,j;
   if(strcmp(filter,"0") == 0)//logic to remove all the leading zeroes
   {
     char st = '\0';
     return st;
   }
   while(filter[i] == '0')
     i++;
   int size = strlen(filter)-i;
   char* s = (char*)malloc(sizeof(char)*size);
   for(j=0;j<size;j++)
     s[j] = filter[i+j];
   return s;
}
void intal_destroy(void* intal)
{
   free((char*)intal);//frees the memory allocated to intal
}
char* intal2str(void* intal)
{

   if(intal == NULL)
   {
     char* null = (char*)malloc(sizeof(char)*4);
     strcpy(null,"NaN");
     return null;
   }
   //converts the given intal to a string
   char* intal1 = (char*)intal;
   char* intal2 = (char*)malloc(sizeof(char)*strlen(intal1));
   strcpy(intal2,intal1);
   return intal2;
}
void* intal_increment(void* intal)
{
   //increments the intal by 1
   char* intal1 = (char*)intal;
   int n = strlen(intal1);
   char* intal2 = (char*)malloc(sizeof(char)*(n+1));
   int carry = 1;
   int sum =0;
   for(int i=n-1;i>=0;i--)
   {
     sum = (intal1[i]-'0')+carry;
     intal2[i+1] = sum%10+'0';
     carry = sum/10;
   }
   if(carry+'0')//overflow condition
     intal2[0] = carry+'0';
   intal2 = intal_create(intal2);//remove all leading zeroes
   return (void*)intal2;
}
void* intal_decrement(void* intal)
{
   char* intal1 = (char*)intal;
   if((intal1[0]-'0') == 0)//test case where if the intal has only one character i.e, zero then dont perform any action
     return intal;
   int n = strlen(intal1);
   char* intal2 = (char*)malloc(sizeof(char)*(n));
   int carry=1;
   int diff;
   for(int i=n-1;i>=0;i--)
   {
     diff = (intal1[i]-'0')-carry;
     if(diff<0)//if diff < 0 then we add 10 to diff and append it to the intal2
     {
       carry=1;
       diff = diff+10;
       intal2[i] = diff+'0';
       continue;
     }
     else
     {
       intal2[i] = diff+'0';//other wise normally append it to intal2
       carry=0;
       continue;
     }
   }
   return intal_create(intal2);
}
void* intal_add(void* intal1,void* intal2)
{
   char* intal3 = (char*)intal1;
   char* intal4 = (char*)intal2;
   int n1 = strlen(intal3);
   int n2 = strlen(intal4);
   int max = (n1>=n2)?n1:n2;
   char* intal6 = (char*)malloc(sizeof(char)*(max+1));
   char*op1,*op2,*tmp;
   op2 = (char*)malloc(sizeof(char)*max);
   int tmpsize,sum;
   if(max == n1)
   {
     op1 = intal3;
     tmp = intal4;
     tmpsize = n2;
   }
   else
   {
     op1 = intal4;
     tmp = intal3;
     tmpsize = n1;
   }
   tmpsize--;
   for(int i=max-1;i>=0;i--) 
   {
     if(tmpsize>=0)
     {
       op2[i] = tmp[tmpsize];
       tmpsize--;
     }
     else
       op2[i] = '0';
   }
   int carry =0;
   for(int i=max;i>0;i--)
   {
     sum = (op1[i-1]-'0')+(op2[i-1]-'0')+carry;
     intal6[i] = sum%10+'0';
     carry=(sum/10);
   }
   if(carry+'0')
     intal6[0] = carry+'0';
   else
    intal6[0] = '0';
   intal6 = intal_create(intal6);
   return (void*)intal6;
}
void* intal_diff(void* intal1,void* intal2)
{
   char* intal3 = (char*)intal1;
   char* intal4 = (char*)intal2;
   int n1 = strlen(intal3);
   int n2 = strlen(intal4);
   int max = (n1>=n2)?n1:n2;//find max length
   char*op1,*op2,*tmp;
   op1 = (char*)malloc(sizeof(char)*max);
   op2 = (char*)malloc(sizeof(char)*max);
   tmp = (char*)malloc(sizeof(char)*max);
   int tmpsize,diff;
   if(max == n1)
   {
     op1 = intal3;
     tmp = intal4;
     tmpsize = n2;
   }
   else
   {
     op1 = intal4;
     tmp = intal3;
     tmpsize = n1;
   }
   tmpsize--;
   for(int i=max-1;i>=0;i--) 
   {
     if(tmpsize>=0)
     {
       op2[i] = tmp[tmpsize];
       tmpsize--;
     }
     else
       op2[i] = '0';
   }//finally stores the first operand in op1 and second one in op2
   int carry = 0;
   char *result = (char*)malloc(sizeof(char)*max);
   for(int i=max-1;i>=0;i--)
   {
     diff = (op1[i]-'0')-(op2[i]-'0')-carry;//subtraction logic
     if(diff < 0)//diff < 0 then we add 10 to diff and append it to result
     {
       diff = diff+10;
       carry = 1;
       result[i] = diff+'0';
     }
     else
     {
       carry = 0;
       result[i] = diff+'0';
     }
   }
   return intal_create(result);//remove leading zeroes if any
}
void* Karatsuba(void* op1,void* op2,int n);
void* intal_multiply(void* intal1, void* intal2)//Brute force
{
	if(intal1 == NULL || intal2 == NULL) return NULL;
	char *op1, *op2, *product;
	if(intal_compare(intal1, intal2) > 0) {
		op1 = (char *)intal1;
		op2 = (char *)intal2;
	}
	else {
		op1 = (char *)intal2;
		op2 = (char *)intal1;
	}
	long int len = strlen(op1), len2 = strlen(op2);
	if(len2 == 1 || len == 1) {
		if(op2[0] == '0' || op1[0] == '0') {
			product = (char *)malloc(sizeof(char) * 2);
			product[0] = '0';
			product[1] = '\0';
			return product;
		}
		if(op2[0] == '1' && len2 == 1) 
                {
			product = (char *)malloc(sizeof(char) * (strlen(op1) + 1));
			strcpy(product, op1);
			product[strlen(op1)] = '\0';
			return product;
		}
		if(op1[0] == '1' && len == 1) {
			product = (char *)malloc(sizeof(char) * (strlen(op2) + 1));
			strcpy(product, op2);
			product[strlen(op2)] = '\0';
			return product;
		}
	}
	long int i, j = len2 - 1;
	long int f_len = len + len2;
	long int op2_len = j;
	product = (char *)malloc(sizeof(char) * (f_len + 1));//+1 for NULL character
	for(int w = 0; w < f_len; w++) product[w] = '0';
	product[f_len] = '\0';
	long int k = f_len - 1;
	int carry = 0, prod = 0, sum = 0, s_carry = 0;
	while(j >= 0)
       {
		i = len - 1;
		while(i >= 0) 
                {
			prod = ((op2[j] - '0') * (op1[i] - '0')) + carry;
			if(prod >= 10) 
                        {
				carry = prod / 10;
				sum = (product[k] - '0') + (prod % 10) + s_carry;
				if(sum > 9)
                                {
					s_carry = sum / 10;
					product[k] = (sum % 10) + '0';
				}
				else 
                                {
					s_carry = 0;
					product[k] = sum + '0';
				}
			}
			else
                        {
				carry = 0;
				sum = (product[k] - '0') + prod + s_carry;
				if(sum > 9)
                                {
					s_carry = sum / 10;
					product[k] = (sum % 10) + '0';
				}
				else {
					s_carry = 0;
					product[k] = sum + '0';
				}	
			}
			k -= 1;
			i -= 1;
		}
		if(carry != 0) {
			sum = (product[k] - '0') + carry + s_carry;
			if(sum > 9) {
					s_carry = sum / 10;
					product[k] = (sum % 10) + '0';
			}
			else {
				s_carry = 0;
				product[k] = sum + '0';
			}
			carry = 0;
			k -= 1;
		}
		j -= 1;
		k = (f_len - 1) - (op2_len - j);
               //One vacant space after multiplication of one digit j with op1
	}
	if(product[0] == '0') {
		char *new_itl = intal_create(product);
		free(product);
		return new_itl;
	}
	return product;
        /*
          char* intal3 = (char*)intal1;
   char* intal4 = (char*)intal2;
   int n1 = strlen(intal3);
   int n2 = strlen(intal4);
   int max = (n1>=n2)?n1:n2;//find max length
   char*op1,*op2,*tmp;
   op1 = (char*)malloc(sizeof(char)*max);
   op2 = (char*)malloc(sizeof(char)*max);
   tmp = (char*)malloc(sizeof(char)*max);
   int tmpsize,diff;
   if(max == n1)
   {
     op1 = intal3;
     tmp = intal4;
     tmpsize = n2;
   }
   else
   {
     op1 = intal4;
     tmp = intal3;
     tmpsize = n1;
   }
   tmpsize--;
   for(int i=max-1;i>=0;i--) 
   {
     if(tmpsize>=0)
     {
       op2[i] = tmp[tmpsize];
       tmpsize--;
     }
     else
       op2[i] = '0';
   }
       char *mul=(char*)malloc(sizeof(char)*(size1*size2+1));
       mul = Karatsuba(op1,op2,n);
       return intal_create(mul);
        */
}
   
/*void* Karatsuba(void* op1,void* op2,int n)
{
   if(n==1)
	{
		char *p=(char*)malloc(sizeof(char));
		int no=(a[0]-'0')*(b[0]-'0'),i=0;
		if(no==0)
			strcpy(p,"0");
		else
			while(no!=0)
			{
				char temp;
				temp=(no%10)+'0';
				p[i]=temp;
				no=no/10;i++;
				p=(char*)realloc(p,sizeof(char)*1);
			}
		strrev(p);
		return p;
	}
	if(n%2!=0)
		n++;
	int m=n/2,i=0,j;
	char *a1=(char*)malloc(sizeof(char)*m),*a2=(char*)malloc(sizeof(char)*m);
	char *b1=(char*)malloc(sizeof(char)*m),*b2=(char*)malloc(sizeof(char)*n-m);
	for(j=0;j<m;j++)
	{
		a1[i]=a[j];
		b1[i]=b[j];
		i++;
	}
	i=0;
	for(j=m;j<n;j++)
	{
		a2[i]=a[j];
		b2[i]=b[j];
		i++;
	}
	
	char *p1,*p2,*p3;
	p1=Karatsuba(a1,b1,m);
	p2=Karatsuba(a2,b2,n-m);
	char *a_sum=intal_add((void*)a1,(void*)a2);
	char *b_sum=intal_add((void*)b1,(void*)b2);
	p3=Karatsuba(a_sum,b_sum,m);
	char *p4;
	p4=(char*)intal_diff(intal_diff((void*)p3,(void*)p1),(void*)p2);
	for(i=0;i<n;i++)
		strcat(p1,"0");
	for(i=0;i<m;i++)
		strcat(p4,"0");
	return intal_add((void*)intal_add((void*)p1,(void*)p4),(void*)(p2));
  //Karatsuba algorithm
}*/
void* intal_divide(void* intal1,void* intal2)
{
    /*int quotient=0;//time consuming way to find quotient
   int k = intal_compare(intal3,intal4);
   while(k > 0)
   {
     intal3 = intal_diff(intal3,intal4);
     quotient++;
     k = intal_compare(intal3,intal4);
   }
   return quotient;*/
   char* intal3 = (char*)intal1;
   char* intal4 = (char*)intal2;
   if((intal4[0]-'0') == 0)
     return 0;
   if((intal4[0]-'0') == 1)
     return intal3;
   long long int divisor =0;
   int k=0;
   int n=0;
   //divisor = atoi(intal4);
   for(int c=0;intal4[c]!='\0';c++)
      divisor = divisor*10 + intal4[c]-'0';
   int id = 0;
   int tmp = intal3[id]-'0';
    char* res = (char*)malloc(sizeof(char)*strlen(intal3));
   while(tmp<divisor)
     tmp = tmp *10 + (intal3[++id]-'0');
   while(strlen(intal3) > id)
   {
      res[k]=(tmp/divisor) + '0';
      tmp = ((tmp%divisor) * 10 + intal3[++id])-'0';
      k++;
   }
   if(strlen(res) == 0)
      return 0;
   return intal_create(res);

}
void* intal_pow(void* intal1,void* intal2)
{
   char*intal3 = (char*)intal1;
  char*intal4 = (char*)intal2;
  if((intal3[0]-'0')  == 0)
    return "0";
  if((intal4[0]-'0') == 0)
    return "1";
  char* result = (char*)malloc(sizeof(char)*INT_MAX);
  long long int p = 0;
   int k=0;
   //p = atoi(intal4);
   for(int c=0;intal4[c]!='\0';c++)
      p = p*10 + intal4[c]-'0';
  for(int i=1;i<p;i++)
  {
    if(i==1)
      result = intal_multiply(intal3,intal3);
    else
      result = intal_multiply(result,intal3);
  }
  return intal_create(result);
}
int intal_compare(void* intal1,void* intal2)
{
  char* intal3 = (char*)intal1;
   char* intal4 = (char*)intal2;
   int n1 = strlen(intal3);
   int n2 = strlen(intal4);
   int max = (n1>=n2)?n1:n2;//max length returned
   char*op1,*op2,*tmp;
   op2 = (char*)malloc(sizeof(char)*max);
   int tmpsize,diff;
   char *intal5,*intal6;
   if(max == n1)
   {
     op1 = intal3;
     tmp = intal4;
     tmpsize = n2;
   }
   else
   {
     op1 = intal4;
     tmp = intal3;
     tmpsize = n1;
   }
   tmpsize--;
   for(int i=max-1;i>=0;i--) 
   {
     if(tmpsize>=0)
     {
       op2[i] = tmp[tmpsize];
       tmpsize--;
     }
     else
       op2[i] = '0';
   }//Equalize the lengths of both the arrays and then compare and return the suitable value
  if(strcmp(op1,op2) == 0)
    return 0;
  else if(strcmp(op1,op2) > 0)
    return 1;
  else
    return -1;    
}
