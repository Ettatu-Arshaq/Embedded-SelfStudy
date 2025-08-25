#include <stdio.h>
#include <stdint.h>
typedef struct{
    uint8_t ODR;
}GPIODEF;
GPIODEF PORTA;

void ledon(GPIODEF *port){
    port->ODR=1;
    printf("LED TURNED ON/PORT:%d\n",port->ODR);
}

void ledoff(GPIODEF *port){
    port->ODR=0;
    printf("LED TURNED OFF/PORT:%d\n",port->ODR);
}
void main(){
    int c;
    GPIODEF *gp=&PORTA;
    void(*ledcontrol)(GPIODEF*);
    do{
        printf("1.ON\n2.OFF\nEnter Choice :");
        scanf("%d",&c);
        if(c==1){ledcontrol=ledon;}
        else if (c==2){ledcontrol=ledoff;}
        else{exit(0);}
        ledcontrol(gp);
    }while(1);
}