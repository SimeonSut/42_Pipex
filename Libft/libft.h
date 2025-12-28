/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssutarmi <ssutarmi@student_42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:26:13 by ssutarmi          #+#    #+#             */
/*   Updated: 2025/12/28 14:19:52 by ssutarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>

// Structure Used
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//----------THESE FUNCTIONS SCAN FOR THE CORRESPONDING CATERGORY OF CHARACTERS

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
// Return value : 1 IF TRUE , 0 IF FALSE

//----------VOID POINTER FUNCTIONS

// Fils the first n bytes of memory area pointed by s with int c
void	*ft_memset(void *s, int c, size_t n);
// Return value : Pointer to s

// Fils the first n bytes of pointer memory are by zeros
void	ft_bzero(void *s, size_t n);
// Return value : None

// Copies first n bytes of src into dest (must not overlap)
void	*ft_memcpy(void *dest, const void *src, size_t n);
// Return value : Pointer to dest

// Copies first n bytes of src into dest (can overlap)
void	*ft_memmove(void *dest, const void *src, size_t n);
// Return value : Pointer to dest

// Scan the first n bytes of s, looking for c
void	*ft_memchr(const void *s, int c, size_t n);
// Return value : Pointer to found bytes or NULL

// Compares n bytes of s1 and s2
int		ft_memcmp(const void *s1, const void *s2, size_t n);
// Return value : s1 - s2

//----------FILE-DESCRIPTOR HELPER FUNCTIONS

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
// No return values

//----------STRING SAFE COPY , CAT AND COMPARISON FUNCTIONS

// Copies up to (size - 1) from NULL terminated src into dest
// , NULL terminating the result
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
// Return value : length of src

// CAT (at most size - strlen(dst) - 1 bytes) of src into dest
size_t	ft_strlcat(char *dst, const char *src, size_t size);
/* Return value : length of dst plus the length of src
if strlcat() traverses size characters without finding a NUL,
the length of the string is considered to be size
and the destination string will not be NUL-terminated
(since there was no space for the NUL)*/

// Calculates the lenght of a string
size_t	ft_strlen(const char *s);
// Return value : lenght of string

//----------STRING SEARCH AND SAFER COMPARE

// Search for the first c in s
char	*ft_strchr(const char *s, int c);
// Return value : pointer to c or NULL

// Search for the last c in s
char	*ft_strrchr(const char *s, int c);
// Return value : pointer to c or NULL

// Compares n bytes of s1 and s2
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// Return value : s1 - s2 when mismatch

// Locates little in big
char	*ft_strnstr(const char *big, const char *little, size_t len);
// Return value : if little is empty its big. If no little, NULL.
// If little found, pointer to start of little in big.

//----------STRING TO INT AND INT TO STRING

// CHAR TO INT/LONG
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
// Return value : THE INT/LONG

// INT TO CHAR
char	*ft_itoa(int n);
// Return value : THE CHAR

//----------MEMORY ALLOCATION HELPERS

// Allocates memory nmemb + size times, populates all with NULL terminators
void	*ft_calloc(size_t nmemb, size_t size);
// Return value : Pointer to allocated memory

// Duplicates a string
char	*ft_strdup(const char *s);
// Return value : Pointer to duplicated string

//----------SUBSTRING, JOIN, TRIM AND SPLIT

//Allocates memory (using malloc(3)) and returns a copy of ’s1’ with
//characters from ’set’ removed from the beginning and the end.
char	*ft_strtrim(char const *s1, char const *set);
// Return value : The trimmed string. NULL if the allocation fails.

// Creates a substring from s, starting at start position of the start string,
// copying len times
char	*ft_substr(char const *s, unsigned int start, size_t len);
// Return value : The substring. NULL if the allocation fails.

// Joins 2 strings together
char	*ft_strjoin(char const *s1, char const *s2);
// Return value : The new string. NULL if the allocation fails.

// Split a string and creates a array of strings.
// c is the separator and doesnt appear on the new strings.
char	**ft_split(char const *s, char c);
// Return value : The array of new strings resulting from the split.
// NULL if the allocation fails.

//----------FUNCTION STRING MEM ALLOCATORS AND ITERATORS

// Applies f to each member of s and
// creates a new string with the result
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
// Return value : The string created from the application of f on s.
// NULL if fails

// Applies f to each member of s
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
// Return value : None

//----------STRUCTURE TREATMENT FUNCTIONS

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//----------PRINTF SECTION DESCRIPTION

int		ft_printf(const char *ptr, ...);

// General Printf Utilities from above
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);

//%c: for printing a single character
int		ft_putchar(int c);

//%s: for printing a string
int		ft_putstr(char *str);

//%p: for printing pointers
int		ft_putptr(void *s);
int		ft_puthexap(unsigned long long nb, char *base);

//%d: for printing a decimal (base 10) number
int		ft_putdec(int nb);

//%i: for printing an integer in base 10
int		ft_putdec(int nb);

//%u: for printing an unsigned decimal (base 10) number
int		ft_putun(int nb);

//%x: for printing a number in hexadecimal (base 16) lowerccase format
int		ft_puthexa(unsigned int nbr, char *base);

//%X: for printing a number in hexadecimal (base 16) uppercase format
int		ft_puthexa(unsigned int nbr, char *base);

//%%: Prints '%' literal
int		ft_putchar(int c);

// THEY ALL RETURN AN INT EQUAL TO THE LENGHT OF THE OUTPUT

//--------------GET_NEXT_LINE SECTION

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif

// Prints a line from a file descriptor, one line at a time, max fd = 1023
char	*get_next_line(int fd);

// Reads from fd and return the first concatenated string containing '\n'
char	*addline(int fd, char *line);

// Returns a line with \n in the end,
// Ovewrites the copied data with the remaining one in the str input string
char	*ft_nextline(char *str, int i);

// Modified strjoin, need two array created via malloc as input,
// free them and return a joined one created via malloc as well.
char	*ft_freejoin(char *s1, char *s2);

#endif
