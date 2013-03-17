#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  FOOL     int
#define  TRUE      1
#define  FALSE     0
#define  MAXWORD   256
#define  hashnum  1024

/*采用哈希表结点结构*/
typedef struct Hash{ 
    int count; 
 char str[1];     /*不一定为1，而是动态分配*/
}Hash_table;

Hash_table hash_table[hashnum];

char buffer[256];     /*缓冲区大小，用来暂时存储单词*/
int tail_prob;              /*缓冲区结束位指针 */
int Hcount = 0;                   /*用来计算有多少单词*/

/******************************************************************/
/**                      初始化操作                              **/
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
/**    关于缓冲区的操作                                          **/ 
/**                                                              **/

/*把一个字符拷贝到缓存区中*/
void copytobuffer (char character)
{    
 if (tail_prob >= MAXWORD)
 {
  printf("Usag:this word is too long!");
  exit (-1);
 }
 buffer[tail_prob++] = character;
}

/*清除缓冲区*/
void clear_buffer ()
{
 while (tail_prob != 0)
 {
  buffer[--tail_prob] = 0;
 }
}

/**************************************************************/
/** 找哈希表的关键字,这里使用的是把字符串的值相加再求与哈希表**/
/**长度的余                                                  **/  
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
/**看哈希表中是否有对应的单词，有返回真                       **/
/**                                                           **/
int find_match ()
{
 int i;
 char *str;
 char *temp;
 int len1;          /*缓冲区中单词的长度*/
 int len2;          /*哈希表中单词的长度*/
 int index;
 
 str = buffer;
 index = get_key (buffer);
 temp = hash_table[index].str;
 len1 = strlen (buffer);
 len2 = strlen (temp);

 while (hash_table[index].count)
 {
  if (len1 == len2)     /*些比较len1和len2是否相等，如果不等再比较*/
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
   else   //能找到
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
/** 根据缓冲区里面的字符生成哈希表                            **/
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

 while (hash_table[index].count)  /*找到没有被储存的结点*/
 {
  index = (index + 1) % hashnum;
 }
 hash_table[index].count++;
 while (i < len)  /*复制字符串*/
 {
  *temp++ = *str++;
  i++;
 }
}

/***************************************************************/
/**                 排序后输出到out文件中                     **/
/**                                                           **/
void Hash_sort(FILE *out)
{
 int index;
 unsigned int symbol; /*最小值*/
 int num;
 int len;
 int i = 0;
 index = 0;
 
 /*排序输出到out文件中,共有Hcount个单词*/ 
 while (i < Hcount)  
 {
  /*找到第一个遇见的频率非零的结点*/
  while (hash_table[index].count == 0)
  {
   index ++;
  }
  symbol = hash_table[index].count;  /*充当最小值*/
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
  /*找到了最小值*/
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
/*找文件in中单词出现的频率，存储其单词以及其频率，调用find_match*/
/*输入的字符小于等于Ox20或者大于0x80时说明不是数字或者字母。但是*/
/*也能组成一个单词                                              */
void find_frquence(FILE *in,FILE *out)
{
 char character;
 FOOL flag;
 flag = 1; /*开关语句*/

 initial_buffer();
 initial_hashtable ();

 /*当没有到文件结束时*/
 character = fgetc (in);
 do
 {
  if (character >0x20 && character < 0x80)
  {
   if (flag)
   {
    copytobuffer (character);
   }
   else /*新单词，且是字母和数字的组合*/ 
   {
    buffer[tail_prob] = '/0';/*表示结束*/
    if(find_match ())  /*如果能够找到，相对应的频率加1*/
    {
//     Tprob->count++;
    }
    else             /*不能找到，则生成一个新的结点加入孩子兄弟链表中*/
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
     if (find_match ())   /*如果能够找到，则对应的频率加1,find_match实现频率加1*/
     {
//      Tprob->count++;
     }
     else                 /*不能找到，则到哈希表中*/
     {
      addtoHash ();
      Hcount++;
     }
     clear_buffer ();   /*清除缓冲区*/
     copytobuffer (character);
     flag = !flag;
    }
    else
    {
     copytobuffer (character);
    }
   }
  }// if - else 结束 
 }while ((character = fgetc (in)) != EOF);

 /*处理最后缓冲区所存储的单词*/
 if(find_match())
 {
//  Tprob->count++;
 }
 else
 {
  addtoHash();
  Hcount++;
 }
 
 /*排序并按从小到大输出到out文件中*/
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
    /*找到各个单词，并且存储其频率,按频率顺序排列后输出到out中*/
 find_frquence (in,out);

 fclose (in);
 fclose (out);
}


