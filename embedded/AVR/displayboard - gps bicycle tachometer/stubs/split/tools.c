#include "tools.h"

// variant of strtok_r() which finds empty tokens as well (sequences
// of delimiter characters will not be considered to be a single
// delimiter).
// If the start string contains too few tokens for the
// strtok_r_empty()-calls the excessive calls return empty strings.
char *strtok_r_empty( char *p_str, const char *p_delim, char **pp_save )
{
  // *pp_save will save the pointer to the start of the next
  // unprocessed token or NULL if there are no more tokens

  char *p_start = ( p_str ? p_str : *pp_save );
  if( p_start )
  {
    // look for start of next token, or NULL
    *pp_save = strpbrk( p_start, p_delim );

    if( *pp_save )
    {
      // delimiter found
      **pp_save = '\0'; // terminate current token
      ++*pp_save;       // skip delimiter on next call
    }
  }
  // return current token or NULL
  return p_start;
}

