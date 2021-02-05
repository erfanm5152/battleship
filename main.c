#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_USER 100
#define NAGHSHE 10
#define MAX_SIZE_KASHTI 5


typedef struct {
    int satr,soton;
}mokhtasat;

typedef struct {
    int size;
    mokhtasat k[MAX_SIZE_KASHTI];
    char khod_kashti[MAX_SIZE_KASHTI];
    struct keshti *next;
}keshti;

typedef struct {
    char user[MAX_USER];
    int seke;
    keshti *head;
    char naghshe[NAGHSHE][NAGHSHE][2];
}player;


void show11();
void delete_linked_list(player**harif,player *bazikon,int adad_delete);

int nobat;

player player1;
player player2;

keshti *create_keshti(int size){
    keshti *temp=(keshti*)malloc(sizeof(keshti));
    temp->size=size;
    temp->k->satr=-1;
    temp->k->soton=-1;
    int i;
    for ( i = 0; i <size ; i++) {
        temp->khod_kashti[i]='K';
    }
    temp->khod_kashti[i]='\0';
    temp->next=NULL;
    return temp;
}






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
}//ساخت صفحه خالی بازی



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
//تشخیص درست بودن یا نبودن خونه های کشتی
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
                    curr->k[0].satr=satr_ebteda;
                    curr->k[0].soton=soton_ebteda;
                    curr=curr->next;
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
                    curr->k[0].satr=satr_ebteda;
                    curr->k[0].soton=soton_ebteda;
                    curr->k[1].soton=soton_enteha;
                    curr->k[1].satr=satr_enteha;
                    curr=curr->next;
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
                    int j=0;
                    if (satr_enteha == satr_ebteda){
                        for (int i = minimum(soton_ebteda,soton_enteha); i <minimum(soton_ebteda,soton_enteha)+3 ; j++,i++) {
                            bazikon->naghshe[satr_ebteda][i][0]='K';
                            curr->k[j].satr=satr_ebteda;
                            curr->k[j].soton=i;
                        }
                    }
                    else{
                        for (int i = minimum(satr_ebteda,satr_enteha); i <minimum(satr_ebteda,satr_enteha)+3 ; j++,i++) {
                            bazikon->naghshe[i][soton_enteha][0]='K';
                            curr->k[j].satr=i;
                            curr->k[j].soton=soton_ebteda;
                        }
                    }
                    curr=curr->next;
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
                    int j=0;
                    if (satr_enteha==satr_ebteda){
                        for (int i = minimum(soton_ebteda,soton_enteha); i <minimum(soton_ebteda,soton_enteha)+5 ; j++,i++) {
                            bazikon->naghshe[satr_ebteda][i][0]='K';
                            curr->k[j].satr=satr_ebteda;
                            curr->k[j].soton=i;
                        }
                    }
                    else{
                        for (int i = minimum(satr_ebteda,satr_enteha); i <minimum(satr_ebteda,satr_enteha)+5 ; j++,i++) {
                            bazikon->naghshe[i][soton_enteha][0]='K';
                            curr->k[j].satr=i;
                            curr->k[j].soton=soton_ebteda;
                        }
                    }

                    curr=curr->next;
                    gharar_dadan_w_atraf_keshtiha(bazikon);
                }
                else{
                    printf("in mahal ghabel jay gozari nist.\n");
                    goto lab4;
                }
            }


    }
}
//قراردادن کشتی ها

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
}//برای ایجاد player1 و player2  در بازی دو نفره


bool dorost_bodan_khone_entekhabi(player harif,int satr,int soton){
    if (satr>9||satr<0||soton>9||soton<0){return false;}
    if (harif.naghshe[satr][soton][1]=='S' || harif.naghshe[satr][soton][1]=='C'|| harif.naghshe[satr][soton][1]=='W'){return false;}
    return true;
}
void ghara_dadan_W_dar_naghshe_harif(player*harif){
    for (int i = 0; i <NAGHSHE ; i++) {
        for (int j = 0; j <NAGHSHE ; j++) {
            if (harif->naghshe[i][j][1]=='C'){
                for (int k = i-1; k <i+2 ; k++) {
                    for (int l = j-1; l <j+2 ; l++) {
                        if (k<0||k>9||l<0||l>9||harif->naghshe[k][l][1]=='C'){ continue;}
                        else{harif->naghshe[k][l][1]='W';}
                    }
                }
            }
        }
    }
}




void gharar_dadan_C_ha(player**harif,player *bazikon){
    keshti *curr=(*harif)->head;
    int k=0;
    while (curr!=NULL){
        int j=0;
        for (int i = 0; i <curr->size ; i++) {
            if ((*harif)->naghshe[curr->k[i].satr][curr->k[i].soton][1]=='S'){j++;}
            if (j==curr->size){
                for (int l = 0; l <curr->size ; l++) {
                    (*harif)->naghshe[curr->k[l].satr][curr->k[l].soton][1]='C';
                }
                delete_linked_list(harif,bazikon,k);
            }
        }
        curr=curr->next;
        k++;
    }
}
void delete_linked_list(player**harif,player *bazikon,int adad_delete){//adad_delete از صفر شروع مییشود//
    keshti *curr=(*harif)->head;
    keshti *a=curr->next;
    for (int i = 0; i <adad_delete-1 ; i++) {
        curr=curr->next;
        a=a->next;
    }
    if (curr==(*harif)->head){(*harif)->head=a;}
    else{
        curr->next=a->next;
    }
    if (a->size==1){bazikon->seke+=25;}
    else if(a->size==2){bazikon->seke+=12;}
    else if(a->size==3){bazikon->seke+=8;}
    else if(a->size==5){bazikon->seke+=5;}
}

bool emal_taghir_dar_khane_entekhab_shode(player*harif ,int satr,int soton){//در صورتی که خانه انتخاب شده کشتی باشد true بر میگرداند.
    if (harif->naghshe[satr][soton][0]=='W'){
        harif->naghshe[satr][soton][1]='W';
        return false;
    }
    if (harif->naghshe[satr][soton][0]=='K'){
        harif->naghshe[satr][soton][1]='S';
        return true;
    }
    if (harif->naghshe[satr][soton][0]=='-'){
        harif->naghshe[satr][soton][1]='x';
        return false;
    }
}
void gameloop(player **bazikon1,player **bazikon2){//اضافه کردن مشخص شدن برنده و خروج از برنامه با گرفتن یک عدد (1-) و save کردن آن
    player **bazikon,**harif;
    int satr,soton;
    while ((*bazikon1)->head!=NULL && (*bazikon2)->head!=NULL) {
        if (nobat % 2 == 0) {
            bazikon = bazikon1;
            harif = bazikon2;
        } else {
            bazikon = bazikon2;
            harif = bazikon1;
        }
        lab6:
        print_naghshe((*harif)->naghshe,1);
        printf("user %s khanei ra entekhab konid :\n",(*bazikon)->user);
        printf("\tsatr: ");
        scanf("%d",&satr);
        getchar();
        printf("\tsoton: ");
        scanf("%d",&soton);
        getchar();
        if (dorost_bodan_khone_entekhabi(**harif,satr,soton)==false){
            printf("khone entekhab shode mojaz nist.\n"
                   "khane digari ra entekhab konid.\n");
            goto lab6;
        }
        if (emal_taghir_dar_khane_entekhab_shode(*harif,satr,soton)==false){nobat++;}
        gharar_dadan_C_ha(harif,*bazikon);
        ghara_dadan_W_dar_naghshe_harif(*harif);
        print_naghshe((*harif)->naghshe,1);
    }
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
            player *player11=&player1;
            player *player22=&player2;
            gameloop(&player11,&player22);
            break;
        case 2:

        case 3:

        case 4:

        case 5:
            show5();
            goto lab;
        case 6:

        case 7:
            fclose(fuser);
            exit(10);
    }
}
