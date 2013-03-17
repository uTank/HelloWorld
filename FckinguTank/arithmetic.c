#include <string.h>
#include "base.h"

byte DatHigh4Bit(byte inchar);
byte DatLow4Bit(byte inchar);
byte DatByteToBcd(byte inchar);

byte *DatMemUchr(byte *ptr, byte value, word len)
{
	while(len-- > 0)
	{
		if(*ptr != value)
		{
			return ptr;
		}
		ptr++;
	}
	return NULL;
}

byte *DatMemChr(byte *ptr, byte value, word len)
{
	while(len-- > 0)
	{
		if(*ptr == value) 
		{
			return ptr;
		}
		ptr++;
	}

	return NULL;
}

void DatStrXor(byte *ptr1, byte *ptr2, word len)
{
	while(len-- > 0)
	{
		*ptr1++ ^= *ptr2++;
	}
}


byte DatCalLrc(byte *ptr, word len)
{
	/*~~~~~~~~*/
	byte	lrc;
	/*~~~~~~~~*/

	lrc = 0;
	while(len-- > 0)
	{
		lrc ^= *ptr++;
	}

	return lrc;
}


byte DatAscDec(byte *Asc, word len)
{
	Asc += len - 1;
	while(--(*Asc) < '0')
	{
		*Asc-- = '9';
		if(--len == 0)
		{
			return 1;
		}
	}

	return 0;
}


byte DatAscInc(byte *Asc, word len)
{
	Asc += len - 1;
	while(++(*Asc) > '9')
	{
		*Asc-- = '0';
		if(--len == 0) return 1;
	}

	return 0;
}

byte DatAscSub(byte *ptr1, byte *ptr2, word len)
{
   byte carry,tmp;

   	carry=0;
   	while(len--!=0) 
	{
   	  	tmp=ptr1[len]-ptr2[len]-carry;

   	  	if (tmp>ptr1[len]) 
		{
   	  		tmp-=0xf6;
   	  		carry=1;
   		}
		else 
		{ 
			carry=0;
		}
		
   	  	ptr1[len]=tmp|'0';
   	}	  
   return carry;
}

/*
 =======================================================================================================================
    功能：把AscII码转换成压缩Bcd码，如把“12AB89”转换成“\x12\xab\x89” 如果长度为奇数，高4位为零；
    入口参数：指向Asc码的指针，存放Bcd码的地址，Asc码长度， 出口：
 =======================================================================================================================
 */
void DatAscToBcd(byte *Bcd, byte *Asc, word Asc_len)
{
	/*~~~~~~~~~~~~~~~~*/
	byte	is_high, by;
	/*~~~~~~~~~~~~~~~~*/

	is_high = !(Asc_len % 2);
	*Bcd = 0x00;
	while(Asc_len-- > 0)
	{
		by = *Asc++;

		if(!(by & 0x10) && (by > 0x30))
		{
			by += 9;
		}
		/* 对字母和空格的处理,小写变大写,空格变0 */
		if(is_high)
		{
			*Bcd = by << 4;
		}
		else
		{
			by &= 0x0f;
			*Bcd++ |= by;
		}

		is_high = !is_high;
	}
}

ulong DatAscToBin(byte *ptr, byte len)
{
	/*~~~~~~~~~~~~~~~~*/
	ulong	result4byte;
	/*~~~~~~~~~~~~~~~~*/

	result4byte = 0;

	while(len-- > 0)
	{
		result4byte = result4byte * 10 + DatLow4Bit(*ptr++);
	}

	return result4byte;
}

byte DatBcdAdd(byte *ptr1, byte *ptr2, word len)
{
	/*~~~~~~~~~~~~~~~~~~~~~~*/
	byte	carry, tmp_result;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	ptr1 += len - 1;
	ptr2 += len - 1;
	carry = 0x66;

	while(len-- > 0)
	{
		tmp_result = *ptr1 +*ptr2-- +carry;
		carry = 0x67;
		if(DatLow4Bit(tmp_result) > DatLow4Bit(*ptr1))
		{
			tmp_result -= 0x06;
		}
		if(DatHigh4Bit(tmp_result) > DatHigh4Bit(*ptr1))
		{
			tmp_result -= 0x60;
			carry = 0x66;
		}

		*ptr1-- = tmp_result;
	}

	return(carry - 0x66);
}

byte DatBcdDec(byte *ptr, word len)
{
	ptr += len - 1;
	while(--(*ptr) == 0xff)
	{
		*ptr = 0x99;
		ptr--;
		if(--len == 0)
		{
			return 1;
		}
	}

	if(((*ptr) & 0x0f) > 9)
	{
		*ptr -= 0x06;
	}
	return 0;
}

byte DatBcdInc(byte *ptr, word len)
{
	ptr += len - 1;
	while(++(*ptr) > 0x99)
	{
		*ptr = 0;
		ptr--;
		if((--len) == 0)
		{
			return 1;
		}
	}

	if(((*ptr) & 0x0f) > 9)
	{
		*ptr += 0x06;
	}
	return 0;
}


byte DatBcdSub(byte *ptr1, byte *ptr2, word len)
{
	/*~~~~~~~~~~*/
	byte	carry;
	/*~~~~~~~~~~*/

	ptr1 += len - 1;
	ptr2 += len - 1;
	carry = 0;

	while(len-- > 0)
	{
		if((*ptr1 & 0x0f) < ((*ptr2 & 0x0f) + carry))
		{
			carry += 0x06;
		}
		if(*ptr1 < (*ptr2 + carry))
		{
			carry += 0x60;
		}
		*ptr1 = *ptr1 -*ptr2 - carry;
		if(carry >= 0x60)
		{
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		ptr1--;
		ptr2--;
	}

	return carry;
}


void DatBcdToAsc(byte *Asc, byte *Bcd, word Asc_len)
{
	/*~~~~~~~~~~~~~*/
	byte	is_first;
	byte	by;
	/*~~~~~~~~~~~~~*/

	is_first = (Asc_len % 2);				/* change by wxk 98.11.06 */

	while(Asc_len-- > 0)
	{
		if(is_first)
		{
			by = *Bcd & 0x0f;
			Bcd++;
		}
		else
		{
			by = *Bcd >> 4;
		}

		by += (by >= 0x0a) ? 0x37 : '0';	/* 0x37 = 'A' - 0x0a */

		*Asc++ = by;
		is_first = !is_first;
	}
}

/*
 =======================================================================================================================
    功能：把一个压缩Bcd码数转换成一个长整型的无符号数， 如发生溢出，结果为低有效位（16进制数）
    入口参数：指向Bcd码数的指针及Bcd码长度（高位在前）， 出口：长整型的无符号数
 =======================================================================================================================
 */
ulong DatBcdToBin(byte *ptr1, byte len)
{
	/*~~~~~~~~~~~~*/
	ulong	result4;
	/*~~~~~~~~~~~~*/

	result4 = 0;
	while(len-- > 0)
	{
		result4 = result4 * 100 + DatHigh4Bit(*ptr1) * 10 + DatLow4Bit(*ptr1);
		ptr1++;
	}

	return result4;
}

byte DatBinToAsc(byte *ptr, ulong inBin, byte len)
{
	ptr += len - 1;
	while(len-- > 0)
	{
		*ptr = (byte) inBin % 10 + '0';
		inBin /= 10;
		ptr--;
	}

	return(byte) inBin;
}

byte DatBinToBcd(byte *ptr, ulong Bin, byte len)
{
	ptr += len - 1;
	while(len-- > 0)
	{
		*ptr = DatByteToBcd((byte) (Bin % 100));
		Bin /= 100;
		ptr--;
	}

	return((byte) Bin);
}

byte DatHigh4Bit(byte inchar)
{
	return (inchar / 16);
}

byte DatLow4Bit(byte inchar)
{
	return(inchar & 0x0f);
}

byte DatByteToBcd(byte inchar)
{
	return(((inchar / 10) << 4) + (inchar % 10));
}

byte Reverse8(byte ucChar)
{
	ucChar = (ucChar & 0x55) << 1 | (ucChar & 0xAA) >> 1;
	ucChar = (ucChar & 0x33) << 1 | (ucChar & 0xCC) >> 1;
	ucChar = (ucChar & 0x0F) << 1 | (ucChar & 0xF0) >> 1;
	return ucChar;	
}

void DataCnvNacFmatSnd(byte *ptr, word len)
{
	memmove(ptr + 3, ptr, len);
	*ptr++ = 0x02;
	DatBinToBcd(ptr, (ulong) len, 2);
	ptr += 2 + len;
	*ptr++ = 0x03;
	*ptr = DatCalLrc(ptr - len - 3, (word) (len + 3));
}

int main(void)
{
	uchar carry = 0;
	uchar p[] = "12345679098765432345607";
	uchar q[] = "13245678765434567876543";

	carry = DatAscSub(p, q, sizeof(p));
	printf("carry = %d\n", carry);

	return 0;

}
