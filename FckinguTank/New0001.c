#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  FOOL     int
#define  TRUE      1
#define  FALSE     0
#define  MAXWORD   256
#define  hashnum  1024

/*���ù�ϣ����ṹ*/
typedef struct Hash{ 
    int count; 
 char str[1];     /*��һ��Ϊ1�����Ƕ�̬����*/
}Hash_table;

Hash_table hash_table[hashnum];

char buffer[256];     /*��������С��������ʱ�洢����*/
int tail_prob;              /*����������λָ�� */
int Hcount = 0;                   /*���������ж��ٵ���*/

/******************************************************************/
/**                      ��ʼ������                              **/
/**                                                              **/
void initial_buffer ()
{
 for (tail_prob = 0; tail_prob < MAXWORD ;tail_prob++)
 {
  buffer[tail_prob++] = 0;
 }
 tail_prob = 0;
}

void initial_hashtable ()
{
 unsigned int i;
 i = 0; 
 while (i < hashnum)
 {
  hash_table[i].count = 0;
  i++;
 }
}
/******************************************************************/  
/**    ���ڻ������Ĳ���                                          **/ 
/**                                                              **/

/*��һ���ַ���������������*/
void copytobuffer (char character)
{    
 if (tail_prob >= MAXWORD)
 {
  printf("Usag:this word is too long!");
  exit (-1);
 }
 buffer[tail_prob++] = character;
}

/*���������*/
void clear_buffer ()
{
 while (tail_prob != 0)
 {
  buffer[--tail_prob] = 0;
 }
}

/**************************************************************/
/** �ҹ�ϣ��Ĺؼ���,����ʹ�õ��ǰ��ַ�����ֵ����������ϣ��**/
/**���ȵ���                                                  **/  
unsigned int get_key (char *str)
{
 unsigned result = 0;
 do
 {
  result = result + (*str);
  str++;
 }while (*str != NULL);
 result = result % hashnum;
 return result;
}

/***************************************************************/
/**����ϣ�����Ƿ��ж�Ӧ�ĵ��ʣ��з�����                       **/
/**                                                           **/
int find_match ()
{
 int i;
 char *str;
 char *temp;
 int len1;          /*�������е��ʵĳ���*/
 int len2;          /*��ϣ���е��ʵĳ���*/
 int index;
 
 str = buffer;
 index = get_key (buffer);
 temp = hash_table[index].str;
 len1 = strlen (buffer);
 len2 = strlen (temp);

 while (hash_table[index].count)
 {
  if (len1 == len2)     /*Щ�Ƚ�len1��len2�Ƿ���ȣ���������ٱȽ�*/
  {
   for (i = 0;i<len1 && *str == *temp;i++)
    {
     str++;
     temp++;
    }   
   if (i != len2)
   {
    index = (index + 1) % hashnum;
    temp = hash_table[index].str;
    str = buffer;
   }
   else   //���ҵ�
   {
    hash_table[index].count++;
    return TRUE;
   }
  }
  else
  {
   index = (index + 1) % hashnum;
   temp = hash_table[index].str;
   str = buffer;
  }
 }  
}

/***************************************************************/
/** ���ݻ�����������ַ����ɹ�ϣ��                            **/
/**                                                           **/
void addtoHash()
{
 char str_temp[256];
 char *str;
 char *temp;
 int len;
 unsigned int index;
 int i;

 i=0;
 str = str_temp;
 strcpy (str,buffer);
 index = get_key (str);
 len = strlen(str);
 temp = hash_table[index].str;

 while (hash_table[index].count)  /*�ҵ�û�б�����Ľ��*/
 {
  index = (index + 1) % hashnum;
 }
 hash_table[index].count++;
 while (i < len)  /*�����ַ���*/
 {
  *temp++ = *str++;
  i++;
 }
}

/***************************************************************/
/**                 ����������out�ļ���                     **/
/**                                                           **/
void Hash_sort(FILE *out)
{
 int index;
 unsigned int symbol; /*��Сֵ*/
 int num;
 int len;
 int i = 0;
 index = 0;
 
 /*���������out�ļ���,����Hcount������*/ 
 while (i < Hcount)  
 {
  /*�ҵ���һ��������Ƶ�ʷ���Ľ��*/
  while (hash_table[index].count == 0)
  {
   index ++;
  }
  symbol = hash_table[index].count;  /*�䵱��Сֵ*/
  num = index;
  index++;
  while (index < hashnum)
  {
   if (hash_table[index].count < symbol && hash_table[index].count)
   {
    symbol = hash_table[index].count;
    num = index;
   }
   index ++;
  }
  /*�ҵ�����Сֵ*/
  len = strlen (hash_table[num].str);
  printf("%d ",hash_table[num].count);
  printf("%s/n",hash_table[num].str);
  fprintf(out,"%s,%d/n",hash_table[num].str,hash_table[num].count);
  
  hash_table[num].count = 0;
  i++;
  index = 0;
 }  
}


/*****************************************************************
/*���ļ�in�е��ʳ��ֵ�Ƶ�ʣ��洢�䵥���Լ���Ƶ�ʣ�����find_match*/
/*������ַ�С�ڵ���Ox20���ߴ���0x80ʱ˵���������ֻ�����ĸ������*/
/*Ҳ�����һ������                                              */
void find_frquence(FILE *in,FILE *out)
{
 char character;
 FOOL flag;
 flag = 1; /*�������*/

 initial_buffer();
 initial_hashtable ();

 /*��û�е��ļ�����ʱ*/
 character = fgetc (in);
 do
 {
  if (character >0x20 && character < 0x80)
  {
   if (flag)
   {
    copytobuffer (character);
   }
   else /*�µ��ʣ�������ĸ�����ֵ����*/ 
   {
    buffer[tail_prob] = '/0';/*��ʾ����*/
    if(find_match ())  /*����ܹ��ҵ������Ӧ��Ƶ�ʼ�1*/
    {
//     Tprob->count++;
    }
    else             /*�����ҵ���������һ���µĽ����뺢���ֵ�������*/
    {
     addtoHash ();
     Hcount++;
    }
    clear_buffer ();   
    copytobuffer (character);
    flag = !flag;
   }
  }
  else
  {
   if (character <= 0x20 || character >= 0x80)
   {
    if (flag)
    {
     buffer[tail_prob] = '/0';
     if (find_match ())   /*����ܹ��ҵ������Ӧ��Ƶ�ʼ�1,find_matchʵ��Ƶ�ʼ�1*/
     {
//      Tprob->count++;
     }
     else                 /*�����ҵ����򵽹�ϣ����*/
     {
      addtoHash ();
      Hcount++;
     }
     clear_buffer ();   /*���������*/
     copytobuffer (character);
     flag = !flag;
    }
    else
    {
     copytobuffer (character);
    }
   }
  }// if - else ���� 
 }while ((character = fgetc (in)) != EOF);

 /*������󻺳������洢�ĵ���*/
 if(find_match())
 {
//  Tprob->count++;
 }
 else
 {
  addtoHash();
  Hcount++;
 }
 
 /*���򲢰���С���������out�ļ���*/
 Hash_sort(out);
}


/**************************************************************/

void main(int argc,char *argv[])
{
 FILE *in;
 FILE *out;
 char temp_string1[256];
 char temp_string2[256];
 if(argc < 2)
 {
  printf ("Usag:please input the correct filename");
  exit (-1);
 }
 if (strlen (argv[1]) >256 || strlen (argv[2]) > 256)
 {
  printf (" Usag:the filename is too long!");
  exit (-1);
 }

 strcpy (temp_string1,argv[1]);
 strcpy (temp_string2,argv[2]);
 in = fopen (temp_string1,"rb");
 out = fopen (temp_string2,"w");
 printf("in = %p\n", in);
 printf("out = %p\n", out);
    /*�ҵ��������ʣ����Ҵ洢��Ƶ��,��Ƶ��˳�����к������out��*/
 find_frquence (in,out);

 fclose (in);
 fclose (out);
}


