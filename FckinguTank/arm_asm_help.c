#include <stdio.h>
#include <stdlib.h>

typedef struct st_arm_isa{
     int  iNum;
     char *pMnemonics;
     char *pISA;
     char *pEDescription;
     char *pCDescription;
}ST_ARM_ISA;

typedef struct st_arm_set{
     int  iNum;
     char *pMnemonics;
     char *pType;
}ST_ARM_SET;

typedef struct st_cond_flag{
     int  iBit;
     char cFlag;
     char *pName;
     char *pEDescription;
     char *pCDescription;
}ST_COND_FLAG;

typedef struct st_vector_tab{
     char *pException;
     char *pShorthand;
     unsigned int iAddr;
     unsigned int iHighAddr;
}ST_VECTOR_TAB;


typedef struct st_proc_mode{
     char *pMode;
     char *pAbbreviation;
     char *pDescription;
}ST_PROC_MODE;

void show_arm_isa(void)
{
     int i;
     ST_ARM_ISA glST_ARM_ISA[] = {
          {0,  "ADC",      "v1", "add two 32-bit values and carry"},
          {0,  "ADD",      "v1", "add two 32-bit values"},
          {1,  "AND",      "v1", "logical bitwise AND of two 32-bit values"},
          {2,  "B",        "v1", "branch relative +/-32MB"},
          {3,  "BIC",      "v1", "logical bit clear (AND NOT) of two 32-bit values"},
          {4,  "BKPT",     "v5", "breakpoint instructions"},
          {5,  "BL",       "v1", "relative branch with link"},
          {6,  "BLX",      "v5", "branch with link and exchange"},
          {7,  "BX",       "v5", "branch with exchange"},
          {8,  "CDP/CDP2", "v1", "coprocessor data processing operation"},
          {9,  "CLZ",      "v1", "count leading zeros"},
          {10, "CMN",      "v1", "compare negative two 32-bit values"},
          {11, "CMP",      "v1", "compare two 32-bit values"},
          {12, "EOR",      "v1", "logical exclusive OR of two 32-bit values"},
          {13, "LDC/LDC2", "v1", "load to coprocessor single or multiple 32-bit values"},
          {14, "LDM",      "v1", "load multiple 32-bit words from memory to ARM registers"},
          {15, "LDR",      "v1", "load a single value from a virtual address in memory"},
          {16, "MCR/MCR2/MCRR",  "v1", "move to coprocessor from an ARM register or registers"},
          {17, "MLA",      "v1", "multiply and accumulate 32-bit values"},
          {18, "MOV",      "v1", "move a 32-bit value into a register"},
          {19, "MRC/MRC2/MRRC",  "v1", "move to ARM register or registers from a coprocessor"},
          {20, "MRS",      "v1", "move to ARM register from a status register (cpsr or spsr)"},
          {21, "MSR",      "v1", "move to a status register (cpsr or spsr) from an ARM register"},
          {22, "MUL",      "v1", "multiply two 32-bit values"},
          {23, "MVN",      "v1", "move the logical NOT of 32-bit value into a register"},
          {24, "ORR",      "v1", "logical bitwise OR of two 32-bit values"},
          {25, "PLD",      "v1", "preload hint instruction"},
          {26, "QADD",     "v1", "signed saturated 32-bit add"},
          {27, "QDADD",    "v1", "signed saturated double and 32-bit add"},
          {28, "QDSUB",    "v1", "signed saturated double and 32-bit subtract"},
          {29, "QSUB",     "v1", "signed saturated 32-bit subtract"},              
          {30, "RSB",      "v1", "reverse subtract of two 32-bit values"},
          {31, "RSC",      "v1", "reverse subtract with carry of two 32-bit integers"},
          {32, "SBC",      "v1", "subtract with carry of two 32-bit values"},
          {33, "SMLAxy",   "v1", "signed multiply accumulate instructions ((16 * 16) + 32 = 32-bit)"},
          {34, "SMLAL",    "v1", "signed multiply accumulate long ((32 * 32) + 64 = 64-bit)"},
          {35, "SMLALxy",  "v1", "signed multiply accumulate long ((16 * 16) + 64 = 64-bit)"},
          {36, "SMLAWy",   "v1", "signed multiply accumulate instruction (((32 * 16) >> 16) + 32 = 32-bit)"},
          {37, "SMULL",    "v1", "signed multiply long (32 * 32 = 64-bit)"},
          {38, "SMULxy",   "v1", "signed multiply instructions (16 * 16 = 32-bit)"},
          {39, "SMULWy",   "v1", "signed multiply instruction ((32 * 16) >> 16 = 32-bit)"},
          {40, "STC/STC2", "v1", "store to memory single or multiple 32-bit values from coprocessor"},
          {41, "STM",      "v1", "store multiple 32-bit registers to memory"},
          {42, "STR",      "v1", "store register to a virtual address in memory"},
          {43, "SUB",      "v1", "subtract two 32-bit values"},
          {44, "SWI",      "v1", "software interrupt"},
          {45, "SWP",      "v2a", "swap a word/byte in memory with a register, without interruption"},
          {46, "TEQ",      "v1",  "test for equality of two 32-bit values"},
          {47, "TST",      "v1",  "test for bits in a 32-bit value"},
          {48, "UMLAL",    "v3M", "unsigned multiply accumulate long ((32 * 32) + 64 = 64-bit)"},
          {49, "UMULL",    "v3M", "unsigned multiply long (32 * 32 = 64-bit)"},
     };

     for(i = 0; i < sizeof(glST_ARM_ISA)/sizeof(glST_ARM_ISA[0]); i++)
     {
//          printf("%.2d <%s>\n\t%s\n", i, glST_ARM_ISA[i].pMnemonics, glST_ARM_ISA[i].pDescription);
          printf("  <%s>\n\t%s\n", glST_ARM_ISA[i].pMnemonics, glST_ARM_ISA[i].pEDescription);
     }
}


void show_cond_flag(void)
{
     int i;
     ST_COND_FLAG glST_CondFlag[] = {
          {31, 'N', "Negative",   "bit 31 of the result is a binary 1",
               "结果的第31位为1"},
          {30, 'Z', "Zero",       "the result is zero, frequently used to indicate equality",
               "结果为0, 通常用来表示是否相等"},
          {29, 'C', "Carry",      "the result causes an unsigned carry",
               "结果导致一个无符号数进位"},
          {28, 'V', "oVerflow",   "the result causes a signed overflow",
               "结果导致一个有符号数溢出"},
          {27, 'Q', "Saturation", "the result causes an overflow and/or saturation",
               "结果导致一个溢出 和/或 饱和"},
     };
     for(i = 0; i < sizeof(glST_CondFlag)/sizeof(glST_CondFlag[0]); i++)
     {
          printf("  CPRS-Bit[%d] <%c> [%s]\n\t%s\n\t%s\n",
               glST_CondFlag[i].iBit, glST_CondFlag[i].cFlag, glST_CondFlag[i].pName,
               glST_CondFlag[i].pEDescription, glST_CondFlag[i].pCDescription);
     }
}


void show_vector_tab(void)
{
     int i;
     ST_VECTOR_TAB glST_VectorTab[] = {
          {"Reset                 ", "RESET", 0x00000000, 0xffff0000},
          {"Undefined instruction ", "UNDEF", 0x00000004, 0xffff0004},
          {"Software interrupt    ", "SWI  ", 0x00000008, 0xffff0008},
          {"Prefetch abort        ", "PABT ", 0x0000000c, 0xffff000c},
          {"Data abort            ", "DABT ", 0x00000010, 0xffff0010},
          {"Reserved              ", "-.-  ", 0x00000014, 0xffff0014},
          {"Interrupt request     ", "IRQ  ", 0x00000018, 0xffff0018},
          {"Fast interrupt request", "FIQ  ", 0x0000001c, 0xffff001c},
     };
     printf(" %25s %12s %10s %15s\n", "Exception/interrupt", "Shorthand", "Address", "High Address");
     for(i = 0; i < sizeof(glST_VectorTab)/sizeof(ST_VECTOR_TAB); i++)
     {
          printf("%25s %11s    0x%.8x    0x%.8x\n", glST_VectorTab[i].pException, glST_VectorTab[i].pShorthand,
               glST_VectorTab[i].iAddr, glST_VectorTab[i].iHighAddr);
     }
}

void show_proc_mode(void)
{
     int i;
     ST_PROC_MODE glST_ProcessorMode[] = {
          {"10111", "abt", "Abort                 "},
          {"10001", "fiq", "Fast interrupt request"},
          {"10010", "irq", "Interrupt request     "},
          {"10011", "svc", "Supervisor            "},
          {"11111", "sys", "System                "},
          {"11011", "und", "Undefined             "},
          {"10000", "usr", "User                  "},
     };
     printf("%15s %25s %12s\n", "Mode", "Abbreviation", "Mode[4:0]");
     for(i = 0; i < sizeof(glST_ProcessorMode)/sizeof(ST_PROC_MODE); i++)
     {
          printf("%25s %10s %15s\n", glST_ProcessorMode[i].pDescription,
               glST_ProcessorMode[i].pAbbreviation, glST_ProcessorMode[i].pMode);
     }
}

int main(void)
{
     /*
     char *fck[] = {
          "Data Processing Instructions",
          "Move",
          "Arithmetic",
          "Logical",
          "Comparison",
          "Multiply",
         
          "Branch Instructions",
         
          "Load-Store Instructions",
          "Single-Register Transfer",
          "Multiple-Register Transfer",
          "Swap",
         
          "Software Interrupt Instructions",
          "Program Status Register Instructions",
     };
     */
     printf("\n=========================== ARM Instruction Set ===========================\n");
     show_arm_isa();
     printf("=========================== ARM Instruction Set ===========================\n");
    
     printf("\n============================= Condition Flags =============================\n");
     show_cond_flag();
     printf("============================= Condition Flags =============================\n");


     printf("\n============================== Vector Tables ==============================\n");
     show_vector_tab();
     printf("============================== Vector Tables ==============================\n");

     printf("\n============================== Processor Mode =============================\n");
     show_proc_mode();
     printf("============================== Processor Mode =============================\n");
    
     printf("\n\n");
     system("pause");

     return 0;
}




