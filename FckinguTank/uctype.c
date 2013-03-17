#if 0
Character handling functions

This header declares a set of functions to classify and transform individual characters.

All these functions take as parameter the int equivalent of one character and return an int, 
that can either be another character or a value representing a boolean value: 
an int value of 0 means false, and an int value different from 0 represents true.

There are two sets of functions:

First a set of classifying functions that check whether 
the character passed as parameter belongs to a certain category. 

These are:
    isalnum Check if character is alphanumeric (function)
    isalpha Check if character is alphabetic (function)
    iscntrl Check if character is a control character (function)
    isdigit Check if character is decimal digit (function)
    isgraph Check if character has graphical representation (function )
    islower Check if character is lowercase letter (function)
    isprint Check if character is printable (function)
    ispunct Check if character is a punctuation character (function)
    isspace Check if character is a white-space (function )
    isupper Check if character is uppercase letter (function)
    isxdigit Check if character is hexadecimal digit (function)

And secondly, two functions to convert between letter cases:
    tolower Convert uppercase letter to lowercase (function)
    toupper Convert lowercase letter to uppercase (function)


For the first set, here is a map of how the original 127-character ASCII set is considered 
by each function (an x indicates that the function returns true on that character)

The characters in the extended character set (above 0x7F) may belong to 
diverse categories depending on the locale and the platform. 
As a general rule, ispunct, isgraph and isprint return true on these 
for the standard C locale on most platforms supporting extended character sets.
#endif

