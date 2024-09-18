# 1.WH

```c
#include <stdio.h>
#include <string.h>

struct Handy
{
    char MARKE[20];
    int PREIS;
};

int main(void)
{
    struct Handy HANDY1;
    strcpy(HANDY1.MARKE, "SAMSUNG");
    HANDY1.PREIS = 999;

return 0;
}
```
