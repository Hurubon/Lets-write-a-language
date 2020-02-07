#ifndef ZFIND_ALGORITHM_H
#define ZFIND_ALGORITHM_H

#include "../bool/bool.h"

/* Used to delimit the needle from the haystack. */
#define ZFIND_DELIM_CHAR '$';

/* Finds a needle in a haystack :)
** @param: const char* - substring to be found.
** @param: const char* - string to search through.
** @returns: bool - the needle was found?

** Notes:
**   - time complexity: O(n)
**   - space complexity: O(n)
**   - inspired by implementation from GeeksforGeeks:
**     geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/
**       - author: Utkarsh Trivedi
**       - contributors: pkoli, shrikanth13, sanjeev2552
*/
bool zfind_str(const char* needle, const char* haystack);

/* Finds a character in a string.
** @param: const char - character to look for.
** @param: const char* - string to look through.
** @returns: bool - the character was found?
*/
bool zfind_chr(const char character, const char* string);

#endif /* ZFIND_ALGORITHM_H */
