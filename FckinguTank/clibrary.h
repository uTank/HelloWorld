#ifndef U_CLIBRARY_H
#define U_CLIBRARY_H

/* -.- */
#define UTANK_FUCKING_CODE
#undef UTANK_FUCKING_CODE

/* -.- */
#ifdef UTANK_FUCKING_CODE
#define UTANK_REDCOLOR
#define UTANK_ASSERT_H
#define UTANK_ERRNO_H
#define UTANK_LIMITS_H
#define UTANK_STDIO_H
#define UTANK_STDLIB_H
#define UTANK_STRING_H
#define UTANK_TIME_H
#define UTANK_CTYPE_H
#define UTANK_STDARG_H
#define UTANK_MATH_H
#endif

/* -.- */
#ifdef UTANK_REDCOLOR

#ifdef UTANK_ASSERT_H
#define assert
#endif /* UTANK_ASSERT_H*/

#ifdef UTANK_ERRNO_H
#define errno
#endif /* UTANK_ERRNO_H */

#ifdef UTANK_LIMITS_H
#define CHAR_BIT
#define SCHAR_MIN
#define SCHAR_MAX
#define UCHAR_MAX
#define CHAR_MIN
#define CHAR_MAX
#define MB_LEN_MAX
#define SHRT_MIN
#define SHRT_MAX
#define USHRT_MAX
#define INT_MIN
#define INT_MAX
#define UINT_MAX
#define LONG_MIN
#define LONG_MAX
#define ULONG_MAX
#endif /* UTANK_LIMITS_H */

#ifdef UTANK_STDIO_H
/* Operations on files */
#define remove     int remove ( const char * filename );
#define rename     int rename ( const char * oldname, const char * newname );
#define tmpfile    FILE * tmpfile ( void );
#define tmpnam     char * tmpnam ( char * str );
/* File access */
#define fclose     int fclose ( FILE * stream );
#define fflush     int fflush ( FILE * stream );
#define fopen      FILE * fopen ( const char * filename, const char * mode );
#define freopen    FILE * freopen ( const char * filename, const char * mode, FILE * stream );
#define setbuf     void setbuf ( FILE * stream, char * buffer );
#define setvbuf    int setvbuf ( FILE * stream, char * buffer, int mode, size_t size );
/* Formatted input/output */
#define printf     int printf ( const char * format, ... );
#define sprintf    int sprintf ( char * str, const char * format, ... );
#define fprintf    int fprintf ( FILE * stream, const char * format, ... );
#define scanf      int scanf ( const char * format, ... );
#define sscanf     int sscanf ( const char * str, const char * format, ...);
#define fscanf     int fscanf ( FILE * stream, const char * format, ... );
#define vprintf    int vprintf ( const char * format, va_list arg );
#define vsprintf   int vsprintf (char * str, const char * format, va_list arg );
#define vfprintf   int vfprintf ( FILE * stream, const char * format, va_list arg );

/* Character input/output */
#define fgetc      int fgetc ( FILE * stream );
#define fgets      char * fgets ( char * str, int num, FILE * stream );
#define fputc      int fputc ( int character, FILE * stream );
#define fputs      int fputs ( const char * str, FILE * stream );
#define getc       int getc ( FILE * stream );
#define getchar    int getchar ( void );
#define gets       char * gets ( char * str );
#define putc       int putc ( int character, FILE * stream );
#define putchar    int putchar ( int character );
#define puts       int puts ( const char * str );
#define ungetc     int ungetc ( int character, FILE * stream );
/* Direct input/output */
#define fread      size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );
#define fwrite     size_t fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
/* File positioning */
#define fgetpos    int fgetpos ( FILE * stream, fpos_t * position );
#define fseek      int fseek ( FILE * stream, long int offset, int origin );
#define fsetpos    int fsetpos ( FILE * stream, const fpos_t * pos );
#define ftell      long int ftell ( FILE * stream );
#define rewind     void rewind ( FILE * stream );
/* Error-handing */
#define clearerr   void clearerr ( FILE * stream );
#define feof       int feof ( FILE * stream );
#define ferror     int ferror ( FILE * stream );
#define perror     void perror ( const char * str );
/* Macros */
#define EOF             "End-of-File"
#define FILENAME_MAX    "Maximum length of file names"
#define NULL            "Null pointer"
#define TMP_MAX         "Number of temporary files"
/* Types */
/* Object containing information to control a stream */
struct FILE{};
/* Object containing information to specify a position within a file  */
struct fpos_t{};
/* size_t : Unsigned integral type */
typedef int size_t;
#endif /* UTANK_STDIO_H */

#ifdef UTANK_STDLIB_H
/* String conversion */
#define atof       double atof ( const char * str );
#define atoi       int atoi ( const char * str );
#define atol       long int atol ( const char * str );
#define strtod     double strtod ( const char * str, char ** endptr );
#define strtol     long int strtol ( const char * str, char ** endptr, int base );
#define strtoul    unsigned long int strtoul ( const char * str, char ** endptr, int base );
/* Pseudo-random sequence generation */
#define rand       int rand ( void );
#define srand      void srand ( unsigned int seed );
/* Dynamic memory management */
#define calloc     void * calloc ( size_t num, size_t size );
#define free       void free ( void * ptr );
#define malloc     void * malloc ( size_t size );
#define realloc    void * realloc ( void * ptr, size_t size );
/* Environment */
#define abort      void abort ( void );
#define atexit     int atexit ( void ( * function ) (void) );
#define exit       void exit ( int status );
#define getenv     char * getenv ( const char * name );
#define system     int system ( const char * command );
/* Searching and sorting */
#define bsearch
#define qsort
/* Integer arithmethics */
#define abs        int abs ( int n );
#define div        div_t div ( int numerator, int denominator );
#define labs       long int labs ( long int n );
#define ldiv       ldiv_t ldiv ( long int numerator, long int denominator );
/* Multibyte characters */
#define mblen
#define mbtowc
#define wctomb
/* Multibyte strings */
#define mbstowcs
#define wcstombs
/* Macros */
#define EXIT_FAILURE    "Failure termination code"
#define EXIT_SUCCESS    "Success termination code "
#define MB_CUR_MAX      "Maximum size of multibyte characters"
#define RAND_MAX        "Maximum value returned by rand"
#define NULL
/* Types */
/* Structure used to represent the value of an integral division performed by div */
struct div_t{
    int qout;
    int rem;
};
/* Structure used to represent the value of an integral division performed by ldiv*/
struct ldiv_t{
    long quot; 
    long rem;
};
/* size_t : Unsigned integral type */
typedef int size_t;

#endif /* UTANK_STDLIB_H */

#ifdef UTANK_STRING_H
/* Copying */
#define memcpy     void * memcpy ( void * destination, const void * source, size_t num );
#define memmove    void * memmove ( void * destination, const void * source, size_t num );
#define strcpy     char * strcpy ( char * destination, const char * source );
#define strncpy    char * strncpy ( char * destination, const char * source, size_t num );
/* Concatenation */
#define strcat     char * strcat ( char * destination, const char * source );
#define strncat    char * strncat ( char * destination, char * source, size_t num );
/* Comparison */
#define memcmp     int memcmp ( const void * ptr1, const void * ptr2, size_t num );
#define strcmp     int strcmp ( const char * str1, const char * str2 );
#define strcoll    int strcoll ( const char * str1, const char * str2 );
#define strncmp    int strncmp ( const char * str1, const char * str2, size_t num );
#define strxfrm    size_t strxfrm ( char * destination, const char * source, size_t num );
/* Searching */
#define memchr     void * memchr ( const void * ptr, int value, size_t num );
#define strchr     char * strchr ( const char * str, int character );
#define strcspn    size_t strcspn ( const char * str1, const char * str2 );
#define strpbrk    char * strpbrk ( const char * str1, const char * str2 );
#define strrchr    char * strrchr ( const char * str, int character );
#define strspn     size_t strspn ( const char * str1, const char * str2 );
#define strstr     char * strstr ( const char * str1, const char * str2 );
#define strtok     char * strtok ( char * str, const char * delimiters );
/* Other */
#define memset     void * memset ( void * ptr, int value, size_t num );
#define strerror   char * strerror ( int errnum );
#define strlen     size_t strlen ( const char * str );
#endif /* UTANK_STRING_H */

#ifdef UTANK_TIME_H
/* Time structure */
struct tm{
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};
/* Time manipulation */
#define clock      clock_t clock ( void );
#define difftime   double difftime ( time_t time2, time_t time1 );
#define mktime     time_t mktime ( struct tm * timeptr );
#define time       time_t time ( time_t * timer );
/* Conversion */
#define asctime    char * asctime ( const struct tm * timeptr );
#define ctime      char * ctime ( const time_t * timer );
#define gmtime     struct tm * gmtime ( const time_t * timer );
#define localtime  struct tm * localtime ( const time_t * timer );
#define strftime   size_t strftime ( char * ptr, size_t maxsize, const char * format, const struct tm * timeptr );
/* Macros */
#define CLOCK_PER_SEC   " Clock ticks per second "
#define NULL
/* types */
/* size_t : Unsigned integral type */
typedef int size_t;
/* clock_t : Type capable of representing clock tick counts and support arithmetical operations*/
#define clock_t
/* time_t : Type capable of representing times and support arithmetical operations*/
#define time_t

#endif /* UTANK_TIME_H */

#ifdef UTANK_CTYPE_H
#define isalnum    " Check if character is alphanumeric "
#define isalpha    " Check if character is alphabetic "
#define iscntrl    " Check if character is a control character "
#define isdigit    " Check if character is decimal digit "
#define isgraph    " Check if character has graphical representation "
#define islower    " Check if character is lowercase letter "
#define isprint    " Check if character is printable "
#define ispunct    " Check if character is a punctuation character "
#define isspace    " Check if character is a white-space "
#define isupper    " Check if character is uppercase letter "
#define isxdigit   " Check if character is hexadecimal digit "
#define tolower    " Convert uppercase letter to lowercase "
#define toupper    " Convert lowercase letter to uppercase "
#endif /* UTANK_CTYPE_H */

#ifdef UTANK_MATH_H
/* */
/* */
/* */
/* */
/* */
/* */
/* */
/* */
#endif /* UTANK_MATH_H */

#ifdef UTANK_STDARG_H
#define va_list    " Type to hold information about variable arguments "
#define va_start   void va_start ( va_list ap, paramN );
#define va_arg     type va_arg ( va_list ap, type )
#define va_end     void va_end ( va_list ap );
#endif /* UTANK_STDARG_H */

#endif /* UTANK_REDCOLOR */

#endif /* U_CLABRARY_H */
