#include "../string.h"

/**
 * Copys n bytes from src to dest
 */
void memcpy(void *dest, void *src, int n)
{
   // Typecast src and dest addresses to (char *)
   char *csrc = (char *)src;
   char *cdest = (char *)dest;

   int i;
   for (i=0; i<n; i++)
       cdest[i] = csrc[i];
}
