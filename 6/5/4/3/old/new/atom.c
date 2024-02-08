#include "simple_shell.h"
/**_atoi.c changed to atom.c
 * communicative mode:return 1 if shell is communicative mood
 * information - struct (structure) address
 *
 * return- true if communicative mode if not return 0
 */                                                             int communicative(info_t *info)
{
        return (isatty(STDIN_FILENO) &&info->readfd <= 2);
}
/**
 * for_delim: check if character is a demiliter
 * c - the character to check
 * delim- the delimition to check
 * return - false if 0 and true if 1
 */
int is_delim (char c ,char *delim)
{
        while(*delim)
        if (*delim++==c)
        return (1);
        return (0);
}
/**
 * an_alphabet: this is us to check for alphabetic character
 * c:the character to insert
 * return:1 if c is alphabetic and 0 if not
 */
int an_alphabet(int c)
{
        if ((c>= 'a' && c <= 'z') || (c>= 'A' && c<= 'Z'))
                return (1);
        else
                return(0);
}
/**
 * atom: it convert string to integer
 * s : this is the string to transform
 * return : false if no number in string and transform number if not
 */
int atom (char *s)
{
        int l,tru=1,lie=0,display;
        unsigned int ans = 0;
        for (l= 0;s[l] != '\0' && lie!=2;l++)
        {
                if (s[l] == '-')
                        tru *= -1;
                if (s[l]>= '0'&& s[l] <= '9')
                {
                        lie = 1;
                        ans *=10;
                }
                else if (lie ==1)
                        lie = 2;
        }
        if (tru == -1)
        display = -ans;
        else
                display = ans;

        return (display);
}

