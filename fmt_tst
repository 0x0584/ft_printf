#include <stdlib.h>


// 1111 1111
//   ^^ ^^^^
//   0- + #$
enum length_modifiers {
  HH,
  H,
  L,  // when used with dou (as in ld, lo, lu) is like DOU
      // in chars and string too
  LL,
  J,
  T,
  Z,

  DEFAULT_MODIF = -1
};

enum conversions {
  SIGNED_DECI, // d or i
  UNSIGNED_OCTA, // o
  UNSIGNED_DECI, // u
  UNSIGNED_HEXA, // x
  UNSIGNED_HEXA2,// X
  DOUBLE_EXP, // e
  DOUBLE_EXP2, // E
  DOUBLE_NORMAL, // f
  DOUBLE_NORMAL2, // F
  CHAR, // c
  STRING, // s
  POINTER, // p
  PERCENTAGE, // %

  DEFAULT_CONV = -1
};

void handle_format(char **fmt)
{
    char *tmp, *bar = NULL;
    int min_width = 0;
    int flags[5] = { 0 };
    int precision = 0;
    enum length_modifiers len = DEFAULT_MODIF;
    enum conversions conv = DEFAULT_CONV;

    bar = (*fmt) + 1; // skip %

    // handle the $ sign
    int argindex = 0;

    while (isdigit(*bar))
    {
        argindex = (argindex << 3) + (argindex << 1);
        argindex += (*bar++ - '0');
    }

    if (*bar != '$')
    {
        // this is not the arg argument
        min_width = argindex;
        argindex = -1;
    }

    // handle the flags
    *fmt = bar + (*bar == '$');
    bar = *fmt;


    while (*bar)
    {
        if (*bar == '#')
            flags[0] = 1;
        else if (*bar == '+')
            flags[1] = 1;
        else if (*bar == ' ')
            flags[2] = 1;
        else if (*bar == '-')
            flags[3] = 1;
        else if (*bar == '0')
            flags[4] = 1;
        else
        {
            //printf("done here [%s]\n", bar);
            break;
        }
        bar++;
    }
    *fmt = bar;

    // handle minimum width
    bar = *fmt;
    while (argindex != -1 && isdigit(*bar))
    {
        min_width = (min_width << 3) + (min_width << 1);
        min_width += (*bar++ - '0');
    }
    *fmt = bar;

    // handle precision
    bar = *fmt;
    if (*bar == '.')
    {
        // this must be precision
        bar++;
        while (isdigit(*bar))
        {
            precision = (precision << 3) + (precision << 1);
            precision += (*bar++ - '0');
        }
    }
    *fmt = bar;

    // handle length modifier
    bar = *fmt;
    if (*bar)
    {
        if (*bar == 'h') {
          if (*(bar + 1) == 'h')
              len = HH;
          else
              len = H;
        } else if (*bar == 'l') {
            if (*(bar + 1) == 'l')
              len = LL;
            else
              len = L;
        } else if (*bar == 'j')
            len = J;
        else if (*bar == 't')
           len = T;
        else if (*bar == 'z')
           len = Z;
        if (len != DEFAULT_MODIF)
          *fmt = bar + 1 + (len == HH || len == LL);
    }

    // conversion
    bar = *fmt;
    if (*bar == 'd' || *bar == 'i') {
      conv = SIGNED_DECI;
	}
    else if (*bar == 'o')
      conv = UNSIGNED_OCTA;
    else if (*bar == 'u')
      conv = UNSIGNED_DECI;
    else if (*bar == 'x')
      conv = UNSIGNED_HEXA;
    else if (*bar == 'X')
      conv = UNSIGNED_HEXA2;
    else if (*bar == 'D')
    {
      len = L;
      conv = SIGNED_DECI;
    }
    else if (*bar == 'O')
    {
      len = L;
      conv = UNSIGNED_OCTA;
    }
    else if (*bar == 'U')
    {
      len = L;
      conv = UNSIGNED_DECI;
    }
    else if (*bar == 'e')
      conv = DOUBLE_EXP;
    else if (*bar == 'E')
      conv = DOUBLE_EXP2;
    else if (*bar == 'f')
      conv = DOUBLE_NORMAL;
    else if (*bar == 'F')
      conv = DOUBLE_NORMAL2;
    else if (*bar == 'c')
      conv = CHAR;
    else if (*bar == 'C')
    {
      len = L;
      conv = CHAR;
    }
    else if (*bar == 's')
      conv = STRING;
    else if (*bar == 'S')
    {
      len = L;
      conv = STRING;
    }
    else if (*bar == 'p')
      conv = POINTER;
    else if (*bar == '%')
      conv = PERCENTAGE;

    printf("\n\n-------------------\narg_index: %d\n"
           "flags:\n #: {%d} 0: {%d} -: {%d} +: {%d} (blank): {%d}\n"
           "min_width: %d\nprecision: %d\n"
           "length_mod: %d\nconversion: %d\n",
           argindex,
           flags[0],flags[1],flags[2],flags[3],flags[4],
           min_width, precision,
           len, conv);
}

int main() {
  char *foo = "cool %4.2ls %2$#+-14.6hhd have to %1$ -#27lo nice";
  char *tmp;

  puts(foo);
  while (*foo)
  {
      if (*foo == '%')
        handle_format(&foo);
      else if ((tmp = strchr(foo, '%'))) {
          while (foo < tmp)
              putchar(*foo++);
          putchar('\n');
      } else {
          printf("string's tail [%s]\n", foo);
          break;
      }
  }
  return 0;
}
