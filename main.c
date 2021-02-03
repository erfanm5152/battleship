#include <stdio.h>
#include <stdlib.h>
void show(){
    printf("1. Play with a Friend\n"
           "2. Play with bot\n"
           "3. Load game\n"
           "4. Load last game\n"
           "5. Settings\n"
           "6. Score Board\n"
           "7. Exit");
}//منو اصلی
void show1(){
    printf("choose user\n"
           "\t1. choose from available users\n"
           "\t2. new user");
}//منو گزینه یک
void show11(){
    printf("2. put ships\n"
           "\t1. Auto\n"
           "\t2. Manual\n");
}//ادامه منو
void show5(){
    printf("1. ships \n"
           "2. map size\n"
           "3. theme (bonus)");
}//منو تنطیمات






int main() {
    lab:
    show();
    int adad_switch;
    scanf("%d",&adad_switch);
    switch (adad_switch) {
        case 1:

        case 2:

        case 3:

        case 4:

        case 5:
            show5();
            goto lab;
        case 6:

        case 7:
            exit(10);
    }
}
