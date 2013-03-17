#ifndef U_STRING_H
#define U_STRING_H

int u_strlen(char *str);
char *u_strcat(char *dst, char *src);
void squeeze(char *str, int c);
void squeeze_ext(char *str1, char *str2);
int any_match(char *str1, char *str2);
int strindex(char *str, char *sub);
int strrindex(char *s, char *t);
int strrindex_ext(char *s, char *t);

#endif /* U_STRING_H */
