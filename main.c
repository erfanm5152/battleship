#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_USER 100
#define NAGHSHE 10
#define MAX_SIZE_KASHTI 5
int nobat;
typedef struct {
    int size;
    char *khod_kashti[MAX_SIZE_KASHTI];
    struct keshti *next;
}keshti;
keshti *create_keshti(int size){
    keshti *temp=(keshti*)malloc(sizeof(keshti));
    temp->size=size;
    temp->next=NULL;
    temp->khod_kashti[0] = NULL;
    return temp;
}


typedef struct {
    char user[MAX_USER];
    int seke;
    keshti *head;
    char naghshe[NAGHSHE][NAGHSHE][2];
}player;
player player1;
player player2;


void sakhte_keshtiha(player*bazikon){
    bazikon->head=create_keshti(1);
    keshti *temp;
    keshti *curr=bazikon->head;
    for (int i = 0; i <3 ; i++,curr=curr->next) {
        temp=create_keshti(1);
        curr->next=temp;
    }
    for (int j = 0; j <3 ; j++,curr=curr->next) {
        temp=create_keshti(2);
        curr->next=temp;
    }
    for (int k = 0; k <2 ; k++,curr=curr->next) {
        temp=create_keshti(3);
        curr->next=temp;
    }
    temp=create_keshti(5);
    curr->next=temp;
}//برای ساخت لینک لیستی از کشتی های هر بازیکن

void print_naghshe(char naghshe[NAGHSHE][NAGHSHE][2],int n){
    printf("\\ ");
    for (int i = 0; i <10 ; i++) {
        printf("%d ",i);
    }
    printf("\n");
    for (int j = 0; j <NAGHSHE ; j++) {
        printf("%d ",j);
        for (int i = 0; i <NAGHSHE ; i++) {
            printf("%c ",naghshe[j][i][n]);
        }
        printf("\n");
    }
}

void create_board(player *bazikon){
    for (int i = 0; i <NAGHSHE ; i++) {
        for (int j = 0; j <NAGHSHE ; j++) {
            bazikon->naghshe[i][j][0]='-';
            bazikon->naghshe[i][j][1]='-';
        }
    }
}

void put_ships(player*bazikon){

}


void show(){
    printf("1. Play with a Friend\n"
           "2. Play with bot\n"
           "3. Load game\n"
           "4. Load last game\n"
           "5. Settings\n"
           "6. Score Board\n"
           "7. Exit\n");
}//منو اصلی
void show1(){
    printf("choose user\n"
           "\t1. choose from available users\n"
           "\t2. new user\n");
}//منو گزینه یک
void show11(){
    printf("2. put ships\n"
           "\t1. Auto\n"
           "\t2. Manual\n");
}//ادامه منو
void show5(){
    printf("\t1. ships \n"
           "\t2. map size\n"
           "\t3. theme (bonus)\n");
}//منو تنطیمات


bool search(FILE *user,char *new){
    rewind(user);
    player temp;
    while (fread(&temp,sizeof(player),1,user)>0){
        if (strcmp(temp.user,new)==0){return false;}
    }
    return true;
}//جست و جو در بین یوزر ها

player chose_user(FILE *user){
    int adad_switch;
    player temp,natige;
    lab1:
    show1();
    scanf("%d",&adad_switch);
    getchar();
    switch (adad_switch) {
        case 1:
            rewind(user);
            int i = 1;
            while (fread(&temp, sizeof(player), 1, user) > 0) {
                printf("%d)%s \n", i, temp.user);
                i++;
            }
            printf("adad user mored nadzar ra entekhab konid : \n");
            scanf("%d",&adad_switch);
            fseek(user,(adad_switch-1)*sizeof(player),SEEK_SET);
            fread(&natige,sizeof(player),1,user);
            return natige;
        case 2:
            printf("new user: ");
            char new_user[MAX_USER];
            fflush(stdin);
            gets(new_user);
            player new;
            if (search(user,new_user)){
                strcpy(new.user,new_user);
                new.seke=0;
                fwrite(&new,sizeof(player),1,user);
                return new;
            }
            else{
                printf("in user vojod darad.\n");
                goto lab1;
            }
    }
}//برای انتخاب کردن یوزر

void play_with_friend(FILE*user){
    printf("first player:\n");
    player1=chose_user(user);
    create_board(&player1);
    sakhte_keshtiha(&player1);


}

int main() {
    FILE *fuser=fopen("user.bin","a+b");
    lab:
    show();
    int adad_switch;
    scanf("%d",&adad_switch);
    switch (adad_switch) {
        case 1:
            play_with_friend(fuser);
            break;
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
