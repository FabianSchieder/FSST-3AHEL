```c
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct person
{
    char vorname[15];
    char nachname[25];
    struct person* next;
}person;

int main(void)
{
    person* start = NULL; //Beginn der Liste
    person* p;
    char auswahl;

    do
    {
        p = (person*)malloc(sizeof(person));
        scanf("%s", (*p).vorname); //Variante 1
        scanf("%s", p->vorname); //Variante 2

        p->next = start;
        start = p;

        auswahl = getche();
    } while (auswahl == 'j');
    
    return 0;
}

```
```c
p = (person*)malloc(sizeof(person));
p->next = NULL;

if(start == NULL)
{
  start = p;
}
else
{
  
}
```
