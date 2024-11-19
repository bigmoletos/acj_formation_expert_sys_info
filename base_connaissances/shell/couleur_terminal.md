# Comment mettre de la couleur sur nos prints


```C
#define OSMO_LOGCOLOR_NORMAL NULL
#define OSMO_LOGCOLOR_RED "\033[1;31m"
#define OSMO_LOGCOLOR_GREEN "\033[1;32m"
#define OSMO_LOGCOLOR_YELLOW "\033[1;33m"
#define OSMO_LOGCOLOR_BLUE "\033[1;34m"
#define OSMO_LOGCOLOR_PURPLE "\033[1;35m"
#define OSMO_LOGCOLOR_CYAN "\033[1;36m"
#define OSMO_LOGCOLOR_DARKRED "\033[31m"
#define OSMO_LOGCOLOR_DARKGREEN "\033[32m"
#define OSMO_LOGCOLOR_DARKYELLOW "\033[33m"
#define OSMO_LOGCOLOR_DARKBLUE "\033[34m"
#define OSMO_LOGCOLOR_DARKPURPLE "\033[35m"
#define OSMO_LOGCOLOR_DARKCYAN "\033[36m"
#define OSMO_LOGCOLOR_DARKGREY "\033[1;30m"
#define OSMO_LOGCOLOR_GREY "\033[37m"
#define OSMO_LOGCOLOR_BRIGHTWHITE "\033[1;37m"
#define OSMO_LOGCOLOR_END "\033[0;m"

```


## ligne debut en rouge, puis en vert
```C
printf("\033[31m%zu.\033[32m %s\033[0m\n", a,b)
```
## ligne debut en rouge
```C
printf("\033[31mOption inconnue.\033[0m\n");
```
## ligne debut  en vert
```C
printf("\033[32mChoisissez votre option:\033[0m\n");
```