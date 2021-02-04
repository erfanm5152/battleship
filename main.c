#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_USER 100
#define NAGHSHE 10
#define MAX_SIZE_KASHTI 5

void show11();
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



bool ghabel_jaygozari_bodan_kashtiha(player*bazikon,int ebteda_satr,int ebteda_soton,int enteha_satr,int enteha_soton,int size){
    if (bazikon->naghshe[ebteda_satr][ebteda_soton][0]=='W'||bazikon->naghshe[ebteda_satr][ebteda_soton][0]=='K'){return false;}
    if (size==1){
        if (ebteda_satr<0||ebteda_satr>9||ebteda_soton>9||ebteda_satr<0){return false;}
        else{return true;}
    }
    if (bazikon->naghshe[enteha_satr][enteha_soton][0]=='W'||bazikon->naghshe[enteha_satr][enteha_soton][0]=='K'){return false;}
    else{
        if (ebteda_satr<0||ebteda_satr>9||ebteda_soton>9||ebteda_satr<0||enteha_satr<0||enteha_satr>9||enteha_soton<0||enteha_soton>9){return false;}
        if ((ebteda_satr!=enteha_satr) && (enteha_soton!=ebteda_soton)){return false;}
        else{
            if (ebteda_satr==enteha_satr){
                if ((abs(enteha_soton-ebteda_soton))==size-1){
                    return true;
                }
                else{return false;}
            }
            else if (ebteda_soton == enteha_soton){
                if ((abs(enteha_satr-ebteda_satr))==size-1){
                    return true;
                }
                else{return false;}
            }
        }
    }
}

int minimum(int a,int b){
    if (a>b){return b;}
    else{return a;}
}
void gharar_dadan_w_atraf_keshtiha(player*bazikon){
    for (int i = 0; i <NAGHSHE ; i++) {
        for (int j = 0; j <NAGHSHE ; j++) {
            if (bazikon->naghshe[i][j][0]=='K'){
                for (int k = i-1; k <i+2 ; k++) {
                    for (int l = j-1; l <j+2 ; l++) {
                        if (k<0||k>9||l<0||l>9||bazikon->naghshe[k][l][0]=='K'){ continue;}
                        else{bazikon->naghshe[k][l][0]='W';}
                    }
                }
            }
        }
    }
}


void vasl_kardan_keshtiha_be_linkedlist(player *bazikon,int size){

}

void put_ships(player*bazikon){
    show11();
    int adad_switch;
    scanf("%d",&adad_switch);
    getchar();
    keshti *curr=bazikon->head;
    int satr_ebteda,soton_ebteda,soton_enteha,satr_enteha;
    switch (adad_switch) {
        case 1:
            break;
        case 2:
            for (int i = 0; i <4 ; i++) {
                lab1:
                print_naghshe(bazikon->naghshe,0);
                printf("kashti be tol 1:\n");
                printf("\tsatr: ");
                scanf("%d",&satr_ebteda);
                getchar();
                printf("\tsoton: ");
                scanf("%d",&soton_ebteda);
                getchar();
                if (ghabel_jaygozari_bodan_kashtiha(bazikon,satr_ebteda,soton_ebteda,satr_enteha,soton_enteha,1)){
                    bazikon->naghshe[satr_ebteda][soton_ebteda][0]='K';
                    //وصل کردن کشتی به لینک لیست اضافه شود
                    gharar_dadan_w_atraf_keshtiha(bazikon);
                }
                else{
                    printf("in mahal ghabel jay gozari nist.\n");
                    goto lab1;
                }
            }
            for (int j = 0; j <3 ; j++) {
                lab2:
                print_naghshe(bazikon->naghshe,0);
                printf("kashti be tol 2:\n");
                printf("\tsatre ebteda: ");
                scanf("%d",&satr_ebteda);
                getchar();
                printf("\tsoton ebteda: ");
                scanf("%d",&soton_ebteda);
                getchar();
                printf("\tsatre enteha: ");
                scanf("%d",&satr_enteha);
                getchar();
                printf("\tsoton enteha: ");
                scanf("%d",&soton_enteha);
                getchar();
                if (ghabel_jaygozari_bodan_kashtiha(bazikon,satr_ebteda,soton_ebteda,satr_enteha,soton_enteha,2)){
                    bazikon->naghshe[satr_ebteda][soton_ebteda][0]='K';
                    bazikon->naghshe[satr_enteha][soton_enteha][0]='K';
                    // وصل کردن کشتی به لینک لیست اضافه شود
                    gharar_dadan_w_atraf_keshtiha(bazikon);
                }
                else{
                    printf("in mahal ghabel jay gozari nist.\n");
                    goto lab2;
                }
            }
            for (int k = 0; k <2 ; k++) {
                lab3:
                print_naghshe(bazikon->naghshe,0);
                printf("kashti be tol 3:\n");
                printf("\tsatre ebteda: ");
                scanf("%d",&satr_ebteda);
                getchar();
                printf("\tsoton ebteda: ");
                scanf("%d",&soton_ebteda);
                getchar();
                printf("\tsatre enteha: ");
                scanf("%d",&satr_enteha);
                getchar();
                printf("\tsoton enteha: ");
                scanf("%d",&soton_enteha);
                getchar();
                if (ghabel_jaygozari_bodan_kashtiha(bazikon,satr_ebteda,soton_ebteda,satr_enteha,soton_enteha,3)){
                    if (satr_enteha == satr_ebteda){
                        for (int i = minimum(soton_ebteda,soton_enteha); i <minimum(soton_ebteda,soton_enteha)+3 ; i++) {
                            bazikon->naghshe[satr_ebteda][i][0]='K';
                        }
                    }
                    else{
                        for (int i = minimum(satr_ebteda,satr_enteha); i <minimum(satr_ebteda,satr_enteha)+3 ; i++) {
                            bazikon->naghshe[i][soton_enteha][0]='K';
                        }
                    }
                    gharar_dadan_w_atraf_keshtiha(bazikon);
                }
                else{
                    printf("in mahal ghabel jay gozari nist.\n");
                    goto lab3;
                }
            }
            for (int l = 0; l <1 ; l++) {
                lab4:
                print_naghshe(bazikon->naghshe,0);
                printf("kashti be tol 5:\n");
                printf("\tsatre ebteda: ");
                scanf("%d",&satr_ebteda);
                getchar();
                printf("\tsoton ebteda: ");
                scanf("%d",&soton_ebteda);
                getchar();
                printf("\tsatre enteha: ");
                scanf("%d",&satr_enteha);
                getchar();
                printf("\tsoton enteha: ");
                scanf("%d",&soton_enteha);
                getchar();
                if (ghabel_jaygozari_bodan_kashtiha(bazikon,satr_ebteda,soton_ebteda,satr_enteha,soton_enteha,5)){
                    if (satr_enteha==satr_ebteda){
                        for (int i = minimum(soton_ebteda,soton_enteha); i <minimum(soton_ebteda,soton_enteha)+5 ; i++) {
                            bazikon->naghshe[satr_ebteda][i][0]='K';
                        }
                    }
                    else{
                        for (int i = minimum(satr_ebteda,satr_enteha); i <minimum(satr_ebteda,satr_enteha)+5 ; i++) {
                            bazikon->naghshe[i][soton_enteha][0]='K';
                        }
                    }
                    gharar_dadan_w_atraf_keshtiha(bazikon);
                }
                else{
                    printf("in mahal ghabel jay gozari nist.\n");
                    goto lab4;
                }
            }


    }
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
    put_ships(&player1);
    print_naghshe(player1.naghshe,0);
    printf("second player:\n");
    lab5:
    player2=chose_user(user);
    if (strcmp(player1.user,player2.user)==0){
        printf("in user ghablan entekhab shode.\n"
               "user digari ra entekhab konid.\n");
        goto lab5;
    }
    create_board(&player2);
    sakhte_keshtiha(&player2);
    put_ships(&player2);
    print_naghshe(player2.naghshe,0);
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
