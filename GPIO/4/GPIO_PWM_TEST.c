#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <termio.h>
#include <softPwm.h>

#define GPIO0 0  //Physical 11
#define GPIO3 3  //Physical 15


#define ENA 0  //Physical 
#define IN1 3  //Physical 
#define IN2 0  //Physical 
#define ENB 3  //Physical 
#define IN3 0  //Physical 
#define IN4 3  //Physical 

#define MAX_PWM_DUTY 100
#define baud_rate 115200


int getch(void)
{

int ch;
struct termios buf;
struct termios save;

tcgetattr(0, &save);
buf = save;
buf.c_lflag &= ~(ICANON|ECHO);
buf.c_cc[VMIN] = 1;
buf.c_cc[VTIME] = 0;
tcsetattr(0, TCSAFLUSH, &buf);
ch = getchar();
tcsetattr(0, TCSAFLUSH, &save);
return ch;
}

int main(void)
{
    
    int fd;
    int pwm_a=0;
    unsigned char test,receive_char;
    if(wiringPiSetup()==-1)
    {
        printf("wiringPi Setup error !\n");
        return -1;
    }
    
    if((fd=serialOpen("/dev/ttyACM0",baud_rate))<0)
    {
        printf("UART open error ! \n");
        return -1;
    }

    pinMode(ENA,OUTPUT);
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    
    pinMode(ENB,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);
    
    softPwmCreate(ENA,1,MAX_PWM_DUTY);
    softPwmCreate(ENB,1,MAX_PWM_DUTY);
    
    softPwmWrite(ENA,pwm_a);
    softPwmWrite(ENB,50);

    test='B';

    
    while(1)
    {
        softPwmWrite(ENA,pwm_a);
        pwm_a+=1;
        if(pwm_a>100) pwm_a=0;
        delay(500);

    }

    return 0;

}
