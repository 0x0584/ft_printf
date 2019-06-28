/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf8.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:19:18 by archid-           #+#    #+#             */
/*   Updated: 2019/06/28 16:33:59 by archid-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTF8_H
# define UTF8_H

/*
** Universal Coded Character Set -- Transformation Format 8
** ========================================================
**
** I. Encoding text
** ================
**
** - Unicode provides so many "character set" than any previous encoding.
**   An encoding is when you map a character-set to an integer-set.
**   eg., in ascii 'a' is 97 and 'A' is 65
**
** - Unicode can encode up to 1,114,112 characters between 0x000000-0x10FFFF
**   which fits a 32-bit integer (or 4 bytes). And for backward compatibility,
**   the first 128 characters are the same as ascii.
**
** - UTF-8 is called also multibyte encoding scheme; it requires many bytes
**   to represent one single character. thus comes "unicode sequence".
**
**		00000000 -- 0000007F: 	0bbbbbbb
**		00000080 -- 000007FF: 	110bbbbb 10bbbbbb
**		00000800 -- 0000FFFF: 	1110bbbb 10bbbbbb 10bbbbbb
**		00010000 -- 001FFFFF: 	11110bbb 10bbbbbb 10bbbbbb 10bbbbbb
**
** - A UTF-8 character might require either 1, 2, 3 or 4 Bytes. one thing to
**   notice in this case, is that we cannot represent the whole 32-bit range
**   of characters, FFFFFFFF. Since we use can only use 001FFFFF character
**   representations due to the fact that other bits are use as marks.
**   However, a) we can represent up to 1,114,112 different characters.
**   b) It's fully compatible with 7-bit ASCII c) might use less than 4 Bytes
**   everytime. d) Sorting is reserved, since it's same as sorting integers.
**   e) each unicode character has a mark at the head, thus we can transfer
**   bytes one after the other, and yet still know which one is which. and
**   finally f) UTF-8 is a byte-stream, which means there's no byte order
**   or endiannes[1]
**
** II. utf8.h -- a C library to handle UTF-8
** =========================================
**
** Terminology:
** ~~~~~~~~~~~~
**
** Multibyte {character/string}: refers to a text in one of many possible
** encodings. and it doesn't necessarly need more that one Byte. The encoding
** is determined by the user's _locale settings_.
**
** Wide {character/string}: refers to a fixed size characters, usually 32-bits
** or 4 Bytes, which is a unicode codepoint.
**
**
**   [1] - need documentation
*/

# include "libft.h"

/* conversion */
# define IS_UTF8(c)		((c) & 0xC0 != 0x80)

ssize_t utf8_to_utf32(t_uint32 *dest, size_t destsz, char *src, size_t srcsz);
ssize_t utf8_to_utf8(char *dest, size_t destsz, t_uint32 *src, size_t srcsz);
ssize_t utf8_to_utf8ch(char *dest, size_t destsz, t_uint32 ch);

#endif
