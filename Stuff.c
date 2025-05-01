#include "danStuff.h"

/* cut off trailing carrige return/linefeed */
void chomp(char * string) {
  int target;
  
  target = strcspn(string,"\r\n");
  string[target] = '\0';
  
}

/* case insensitive character compare */
int chricmp(char a, char b) {
  if (tolower(a) == tolower(b)) return 1;
  else                          return 0;
}

/* swap the case of a character */
char othercase(char a) {
  if (isupper(a)) return tolower(a);
  else            return toupper(a);
}

/* convert a string to uppercase */
char * strupper(char *a) {
  char *p;
  p = a;
  while(*p) {
    *p = toupper(*p);
    p++;
  }
  return a;
}

/* convert a string to lowercase */
char * strlower(char *a) {
  char *p;
  p = a;
  while(*p) {
    *p = tolower(*p);
    p++;
  }
  return a;
}

/* print n characters of a string */
void nprints(char * str, unsigned long n) {
  printf("%.*s", n, str);
}




/* Generate a string of size filled with c */
char * aGenRun( char c, uint16_t size) {
   char *b;
   
   b = malloc(size+2);
   memset(b, c, size);
   b[size+1] = 0;
   
   return b;
}

/* Append all of this to that */
int astrcat(char ** dst,  const char * src) {
  char * temp;
  int  rv;
  
  if (*dst == NULL) {
    if ( (rv = asprintf(dst, "%s", src)) != -1) {
      return rv;
    }  
  }  
  
  if ( (rv = asprintf(&temp, "%s%s", *dst, src)) != -1) {
    free(*dst);
    *dst = temp;
    return rv;
  }
  
  return -1;
}

/* Append only so much of this to that */
int astrncat(char ** dst,  const char * src, unsigned long n) {
  char * temp;
  int  rv;
  
  if (*dst == NULL) {
    if ( (rv = asprintf(dst, "%.*s", n, src)) != -1) {
      return rv;
    }  
  }  
  
  if ( (rv = asprintf(&temp, "%s%.*s", *dst, n, src)) != -1) {
    free(*dst);
    *dst = temp;
    return rv;
  }
  
  return -1;
}




/*   insert a character into a string with dynamic allocation dst will be freed  */
int astrinsc(char ** dst,  const char ins, unsigned int pos) {
  char * temp;
  int  rv;
  
  if (pos > strlen(*dst)) return -1;
  
  if ( (rv = asprintf(&temp, "%.*s%c%s", pos, *dst, ins, *dst+pos)) != -1) {
    free(*dst);
    *dst = temp;
    return rv;
  }
  return -1;
}

/*   insert a string into a string with dynamic allocation dst will be freed  */
int astrinss(char ** dst,  const char * ins, unsigned int pos) {
  char * temp;
  int  rv;
  
  if (pos > strlen(*dst)) return -1;
  
  if ( (rv = asprintf(&temp, "%.*s%s%s", pos, *dst, ins, *dst+pos)) != -1) {
    free(*dst);
    *dst = temp;
    return rv;
  }
  return -1;
}





/*
void initRand( void ) {

 time_t t;
 
 srand((unsigned) time(&t));
 
}


float randomf( float top ) {
  float r;
  
  r = ((float)rand()/(float)RAND_MAX) * top;
  if (rand() % 2) r *= (-1);
  
  return  r;

}


// use strndup
int    astrncpy  ( char ** dst, char * str, unsigned long n);
  
  if (*dst) free(*dst);
   
  n = Min(n, strlen(str));
  if (n == 0) return *dst;
  
  b = malloc(n+2);
  memcpy( *dst , str, n);
  *dst + n = 0;
  
  return *dst;
}

//   concat two strings with dynamic allocation  
int _astrcat(char ** dst,  const char * src) {
  char * temp;
  int  rv;
  
  if ( (rv = asprintf(&temp, "%s%s", *dst, src)) != -1) {
    free(*dst);
    *dst = temp;
    return rv;
  }
  return -1;
}

// print n characters of a string 
void nprints(char * str, unsigned long n) {

  char * tmp;  
  tmp = strndup(str, n);
  printf("%s", tmp);  
  free(tmp);
  
}

*/
