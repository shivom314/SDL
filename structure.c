#include<stdio.h>
int main()
{
    struct marvel {
        int power ;
        char win ;
        int level ;
        char love[20] ;
    }captain , rdj , strange , wanda;
    scanf("%d%d%c",&captain.level,&captain.power,&captain.win) ;
    printf("%d %d %c",captain.level,captain.power,captain.win) ;
    struct marvel loki ;
    scanf("%d%d%c",&loki.level,&loki.power,&loki.win) ;
    printf("Power , win and level of loki is %d %c %d",loki.power,loki.win,loki.level) ;
    return 0;
}
