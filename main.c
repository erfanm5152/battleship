#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define MAX_USER 100
#define MAX_PLAYER 1000
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

typedef struct {
    player bazikon1;
    player bazikon2;
    char tarikh[100];
    char saat[100];
    int nobat;
    int vaziyat_bazi;
}save;




void show11();
void delete_linked_list(player**harif,player *bazikon,int adad_delete);
void print_linked_list(player bazikon);
///global متغیر های
int nobat;
save save_bazi;
player player1;
player player2;
player bot;
player player1_load;
player player2_load;

keshti *create_keshti(int size){
    keshti *temp=(keshti*)malloc(sizeof(keshti));
    if (temp==NULL){exit(-100);}
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
    system("cls");
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
                system("cls");
                getchar();
                if (ghabel_jaygozari_bodan_kashtiha(bazikon,satr_ebteda,soton_ebteda,satr_enteha,soton_enteha,1)){
                    bazikon->naghshe[satr_ebteda][soton_ebteda][0]='K';
                    curr->k[0].satr=satr_ebteda;
                    curr->k[0].soton=soton_ebteda;
                    curr=curr->next;
                    gharar_dadan_w_atraf_keshtiha(bazikon);
                }
                else{
                    system("cls");
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
                system("cls");
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
                    system("cls");
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
                system("cls");
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
                    system("cls");
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
                system("cls");
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
                    system("cls");
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
        if (strcmp(temp.user,new)==0 || strcmp(new,"BOT")==0){return false;}
    }
    return true;
}//جست و جو در بین یوزر ها

player chose_user(FILE *user){
    int adad_switch;
    player temp,natige;
    lab1:
    show1();
    scanf("%d",&adad_switch);
    system("cls");
    getchar();
    switch (adad_switch) {
        case 1:
            rewind(user);
            int i = 1;
            printf("  %-30s %s\n","USER","SEKE");
            while (fread(&temp, sizeof(player), 1, user) > 0) {
                printf("%d)%-30s %d\n", i, temp.user,temp.seke);
                i++;
            }
            printf("adad user mored nadzar ra entekhab konid (baraye bargasht -1 ): \n");
            scanf("%d",&adad_switch);
            if (adad_switch==-1){ goto lab1;}
            system("cls");
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
                system("cls");
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
    printf("naghshe player1: %s\n",player1.user);
    system("pause");
    system("cls");
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
    printf("naghshe player2: %s\n",player2.user);
    system("pause");
    system("cls");
}//برای ایجاد player1 و player2  در بازی دو نفره

void print_player(player bazikon){//برای دیباگ کردن
    puts(bazikon.user);
    printf("%d\n",bazikon.seke);
    printf("naghshe 0:\n");
    print_naghshe(bazikon.naghshe,0);
    printf("naghshe 1:\n");
    print_naghshe(bazikon.naghshe,1);
    print_linked_list(bazikon);

}

bool dorost_bodan_khone_entekhabi(player harif,int satr,int soton){
    if (satr>9||satr<0||soton>9||soton<0){return false;}
    if (harif.naghshe[satr][soton][1]=='S' || harif.naghshe[satr][soton][1]=='C'|| harif.naghshe[satr][soton][1]=='W'||harif.naghshe[satr][soton][1]=='x'){return false;}
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

void print_linked_list(player bazikon){
    keshti *curr=bazikon.head;
    int i=1;
    while (curr!=NULL){
        printf("%d) %d ",i,curr->size);
        for (int j = 0; j <curr->size ; j++) {
            printf(" %d %d ! ",curr->k[j].satr,curr->k[j].soton);
        }
        printf("\n");
        i++;
        curr=curr->next;
    }
}///برای دیباگ کردن

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
    keshti *a=(*harif)->head->next;
    for (int i = 0; i <adad_delete-1 ; i++) {
        curr=curr->next;
        a=a->next;
    }
    if (adad_delete==0){
        (*harif)->head=a;
        if (curr->size==1){bazikon->seke+=25;}
        else if(curr->size==2){bazikon->seke+=12;}
        else if(curr->size==3){bazikon->seke+=8;}
        else if(curr->size==5){bazikon->seke+=5;}
    }
    else{
        curr->next=a->next;
        if (a->size==1){bazikon->seke+=25;}
        else if(a->size==2){bazikon->seke+=12;}
        else if(a->size==3){bazikon->seke+=8;}
        else if(a->size==5){bazikon->seke+=5;}
    }

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
int gameloop(player **bazikon1,player **bazikon2){//وضعیت بازی را نشان میدهد.
    player **bazikon,**harif;
    int satr,soton;
    bool a;
    while ((*bazikon1)->head!=NULL && (*bazikon2)->head!=NULL) {
        if (nobat % 2 == 0) {
            bazikon = bazikon1;
            harif = bazikon2;
        } else {
            bazikon = bazikon2;
            harif = bazikon1;
        }
        lab6:
        system("cls");
        printf("*** BARAYE KHOROJ AZ BAZI -1 RA DAR SATR YA SOTON VARED KONID ***\n");
        print_naghshe((*harif)->naghshe,1);
        printf("user %s khanei ra entekhab konid :\n",(*bazikon)->user);
        printf("\tsatr: ");
        scanf("%d",&satr);
        getchar();
        if (satr==-1){return 10;}//ناتمام
        printf("\tsoton: ");
        scanf("%d",&soton);
        getchar();
        if (soton==-1){return 10;}//ناتمام
        if (dorost_bodan_khone_entekhabi(**harif,satr,soton)==false){
            printf("khone entekhab shode mojaz nist.\n"
                   "khane digari ra entekhab konid.\n");
            system("pause");//برای نمایش درست
            goto lab6;
        }
        if ((a=emal_taghir_dar_khane_entekhab_shode(*harif,satr,soton)) == false){nobat++;}
        gharar_dadan_C_ha(harif,*bazikon);
        ghara_dadan_W_dar_naghshe_harif(*harif);
        print_naghshe((*harif)->naghshe,1);
        if (a==false){
            system("cls");
            print_naghshe((*harif)->naghshe,1);
            system("pause");
        }//برای نمایش
    }
    system("cls");
    if ((*bazikon1)->head!=NULL){
        printf("%s barande shod!!!!!!\n"
               "tabrik.\n",(*bazikon1)->user);
        (*bazikon2)->seke=(*bazikon2)->seke/2;
        system("pause");
        return 1;//پلیر 1 برده است
    }
    else{
        printf("%s barande shod!!!!!!\n"
               "tabrik.\n",(*bazikon2)->user);
        (*bazikon1)->seke=(*bazikon1)->seke/2;
        system("pause");
        return 2;//پلیر 2 برده است
    }
}

mokhtasat entekhab_khane_bot(){
    mokhtasat a;
    time_t t = time(NULL);
    srand(t);
    a.satr=rand()%10;
    a.soton=rand()%10;
    return a;
}

int game_loop_bot(player**bazikon1,player**bazikon2){
    player **bazikon,**harif;
    bool a;
    system("cls");
    int satr,soton;
    while ((*bazikon1)->head != NULL && (*bazikon2)->head != NULL) {
        if (nobat % 2 == 0) {
            bazikon = bazikon1;
            harif = bazikon2;
        }
        else {
            bazikon = bazikon2;
            harif = bazikon1;
        }
        if (strcmp((*bazikon)->user,"BOT")==0){
            lab8: ;
            mokhtasat hadaf;
            hadaf=entekhab_khane_bot();
            if (dorost_bodan_khone_entekhabi(**harif,hadaf.satr,hadaf.soton) == false){
                goto lab8;
            }
            if (emal_taghir_dar_khane_entekhab_shode(*harif,hadaf.satr,hadaf.soton) == false){nobat++;}
            gharar_dadan_C_ha(harif,*bazikon);
            ghara_dadan_W_dar_naghshe_harif(*harif);
            system("cls");
            printf("entekhab bot: \n");
            print_naghshe((*harif)->naghshe,1);
            system("pause");
        }
        else{
            lab9:
            system("cls");
            printf("*** BARAYE KHOROJ AZ BAZI -1 RA DAR SATR YA SOTON VARED KONID ***\n");
            print_naghshe((*harif)->naghshe,1);
            printf("user %s khanei ra entekhab konid :\n",(*bazikon)->user);
            printf("\tsatr: ");
            scanf("%d",&satr);
            getchar();
            if (satr==-1){return 10;}//ناتمام
            printf("\tsoton: ");
            scanf("%d",&soton);
            getchar();
            if (soton==-1){return 10;}//ناتمام
            if (dorost_bodan_khone_entekhabi(**harif,satr,soton)==false){
                printf("khone entekhab shode mojaz nist.\n"
                       "khane digari ra entekhab konid.\n");
                system("pause");
                goto lab9;
            }
            if ((a=emal_taghir_dar_khane_entekhab_shode(*harif,satr,soton)) == false){nobat++;}
            gharar_dadan_C_ha(harif,*bazikon);
            ghara_dadan_W_dar_naghshe_harif(*harif);
            print_naghshe((*harif)->naghshe,1);
            if (a==false){
                system("cls");
                print_naghshe((*harif)->naghshe,1);
                system("pause");
            }//برای نمایش
        }
    }
    system("cls");
    if ((*bazikon1)->head!=NULL){
        printf("%s barande shod!!!!!!\n"
               "tabrik.\n",(*bazikon1)->user);
        (*bazikon2)->seke=(*bazikon2)->seke/2;
        system("pause");
        return 1;//پلیر 1 برده است
    }
    else{
        printf("%s barande shod!!!!!!\n"
               "tabrik.\n",(*bazikon2)->user);
        (*bazikon1)->seke=(*bazikon1)->seke/2;
        system("pause");
        return 2;//پلیر 2 (bot)برده است
    }
}


void print_game_list(save bazi){
    printf("player1: %s\tplayer2: %s\t TIME:%s \t DATE:%s\n",bazi.bazikon1.user,bazi.bazikon2.user,bazi.saat,bazi.tarikh);
    if (bazi.vaziyat_bazi != 10){
        printf("in bazi be payan reside.\t");
        if (bazi.vaziyat_bazi==1){
            printf("%s barande shode ast.\n",bazi.bazikon1.user);
        }
        else{
            printf("%s barande shode ast.\n",bazi.bazikon2.user);
        }
    }
    else{
        if (bazi.nobat%2==0){printf("nobat %s ast\n",bazi.bazikon1.user);}
        else{printf("nobat %s ast.\n",bazi.bazikon2.user);}
    }

}

int print_save_file(FILE*fsave){//شماره آخرین بازی را بر میگرداند.
    save a;
    int i=1;
    rewind(fsave);
    while (fread(&a,sizeof(save),1,fsave)>0){
        printf("%d)",i);
        print_game_list(a);
        i++;
    }
    return i-1;
}


save entekhab_bazi(FILE*fsave,int n){
    save a;
    fseek(fsave,(n-1)*sizeof(save),SEEK_SET);
    fread(&a,sizeof(save),1,fsave);
    return a;
}


void save_linked_list(FILE*fkeshti1,player bazikon1){
    keshti a;
    a.size=0;
    keshti *curr1 = bazikon1.head;
    fseek(fkeshti1,0,SEEK_END);
    fwrite(&a,sizeof(keshti),1,fkeshti1);
    while (curr1!=NULL){
        a = *curr1;
        fwrite(&a,sizeof(keshti),1,fkeshti1);
        curr1=curr1->next;
    }
}

void match_kardan_linkedlist_az_file(FILE*fkeshti,player*bazikon,int adad){
    int k=0;
    keshti a;
    bazikon->head=create_keshti(0);
    keshti *curr=bazikon->head;
    while (k!=adad){
        fread(&a,sizeof(keshti),1,fkeshti);
        if (a.size == 0){k++;}
    }
    while (fread(&a,sizeof(keshti),1,fkeshti)>0 ){
        if (a.size==0){ break;}
        keshti *temp=create_keshti(a.size);
        if (temp==NULL){exit(-1);}
        for (int i = 0; i <a.size ; i++) {
            temp->k[i]=a.k[i];
        }
        curr->next=temp;
        curr=curr->next;
    }
    bazikon->head=bazikon->head->next;
}

void print_file(FILE*fkeshti){
    keshti a;
    while (fread(&a,sizeof(keshti),1,fkeshti)>0){
        printf("%d ",a.size);
        for (int i = 0; i <a.size ; i++) {
            printf("%d %d ! ",a.k[i].satr,a.k[i].soton);
        }
        printf("\n");
    }
}

void save_kardan(FILE*fsave,player bazikon1,player bazikon2){
    save_bazi.bazikon1=bazikon1;
    save_bazi.bazikon2=bazikon2;
    save_bazi.nobat=nobat;
    strcpy(save_bazi.saat,__TIME__);
    strcpy(save_bazi.tarikh,__DATE__);
    fseek(fsave,0,SEEK_END);
    fwrite(&save_bazi,sizeof(save),1,fsave);
}

void update_user(FILE *fuser,player *bazikon){/// مشکل دارد
    player temp;
    fclose(fuser);
    fuser=fopen("user.bin","r+b");
    if (fuser==NULL){exit(-100);}
    int i=0;
    fread(&temp,sizeof(temp),1,fuser);
    while (strcmp(temp.user,bazikon->user)!=0){
        fread(&temp,sizeof(temp),1,fuser);
        i++;
    }
    bazikon->seke+=temp.seke;
    fseek(fuser,i*sizeof(player),SEEK_SET);
    fwrite(bazikon,sizeof(player),1,fuser);
    bazikon->seke=0;
    fclose(fuser);
}

int compare(void*i1,void*i2){
    player a= *((player*)i1);
    player b= *((player*)i2);
    return a.seke>b.seke?-1:(a.seke==b.seke)?0:1;
}

void score_board(FILE*fuser){
    player a[MAX_PLAYER];
    player temp;
    rewind(fuser);
    int i=0;
    while (fread(&temp,sizeof(player),1,fuser)>0){
        a[i]=temp;
        i++;
    }
    qsort(a,i,sizeof(player),compare);
    printf("   %-30s %s\n","USER","SEKE");
    for (int j = 0; j <i ; j++) {
        printf("%d) %-30s %d\n",j+1,a[j].user,a[j].seke);
    }
    printf("\n\n\n\n");
}

void load_bot(FILE*fbot,FILE*fkeshti_bot){
    fread(&bot,sizeof(player),1,fbot);
    match_kardan_linkedlist_az_file(fkeshti_bot,&bot,1);
}

void sakhte_bot(FILE*fbot,FILE*fkeshti_bot){
    fbot=fopen("bot.bin","r+b");
    fkeshti_bot=fopen("fkeshti bot.bin","r+b");
    if (fkeshti_bot==NULL||fbot==NULL){exit(-100);}
    strcpy(bot.user,"BOT");
    bot.seke=0;
    create_board(&bot);
    sakhte_keshtiha(&bot);
    put_ships(&bot);
    fwrite(&bot,sizeof(player),1,fbot);
    save_linked_list(fkeshti_bot,bot);
}//بات را درست میکنه و در فایل ذخیره میکند تا در بازی با بات از آن استفاده کند.
//کاربر نیازی به این تابع ندارد.

int main() {
    lab:  ;
    system("cls");
    FILE *fuser=fopen("user.bin","a+b");
    FILE *fsave=fopen("save.bin","a+b");
    FILE *fsave_tamam=fopen("save tamam.bin","a+b");
    FILE *fkeshti1=fopen("fkeshti1.bin","a+b");
    FILE *fkeshti2=fopen("fkeshti2.bin","a+b");
    FILE *fbot=fopen("bot.bin","r+b");
    FILE *fkeshti_bot=fopen("fkeshti bot.bin","r+b");
    if (fuser==NULL||fsave==NULL||fsave_tamam==NULL||fkeshti1==NULL||fkeshti2==NULL||fbot==NULL||fkeshti_bot==NULL){exit(-100);}
    show();
    save a;//برای چک کردن خالی بودن فایل save
    int adad_switch;
    int adad_akharin_bazi;
    scanf("%d",&adad_switch);
    system("cls");
    switch (adad_switch) {
        case 1:
            play_with_friend(fuser);
            player *player11=&player1;
            player *player22=&player2;
            player1.seke=0;
            player2.seke=0;
            save_bazi.vaziyat_bazi=gameloop(&player11,&player22);
            if (save_bazi.vaziyat_bazi == 10){
                save_kardan(fsave,player1,player2);
                fseek(fkeshti2,0,SEEK_END);
                save_linked_list(fkeshti1,player1);
                save_linked_list(fkeshti2,player2);
            }
            else{
                save_kardan(fsave_tamam,player1,player2);
                update_user(fuser,&player1);
                update_user(fuser,&player2);
                //اپدیت سکه ها
            }
            break;
        case 2:
            load_bot(fbot,fkeshti_bot);
            player1=chose_user(fuser);
            player1.seke=0;
            create_board(&player1);
            sakhte_keshtiha(&player1);
            put_ships(&player1);
            player *player111=&player1;
            player *player222=&bot;
            save_bazi.vaziyat_bazi=game_loop_bot(&player111,&player222);
            if (save_bazi.vaziyat_bazi == 10){
                save_kardan(fsave,player1,bot);
                save_linked_list(fkeshti1,player1);
                save_linked_list(fkeshti2,bot);
            }
            else{
                save_kardan(fsave_tamam,player1,player2);
                update_user(fuser,&player1);
//                update_user(fuser,&bot);
                //اپدیت سکه ها
            }
            break;
        case 3:
        lab7:
            if (fread(&a,sizeof(save),1,fsave)<1){
                printf("savei vojod nadarad.\n");
                system("pause");
                goto lab;
            }
            print_save_file(fsave);
            printf("shomare bazi morede nazar ra vared konid(baraye bargasht -1 ra vared konid): \n");
            scanf("%d",&adad_switch);
            if (adad_switch==-1){ goto lab;}
            fflush(stdin);
            save_bazi=entekhab_bazi(fsave,adad_switch);
            if (save_bazi.vaziyat_bazi!=10){
                printf("in bazi be payan reside ast.\n"
                       "bazi digari ra entekhab konid.\n");
                goto lab7;
            }
            player1_load=save_bazi.bazikon1;
            player2_load=save_bazi.bazikon2;
            nobat=save_bazi.nobat;
            match_kardan_linkedlist_az_file(fkeshti1,&player1_load,adad_switch);
            match_kardan_linkedlist_az_file(fkeshti2,&player2_load,adad_switch);
            player *player11_load = &player1_load;
            player *player22_load = &player2_load;
//            fclose(fsave);
//            FILE *fsave=fopen("save.bin","a+b");
            fseek(fsave,0,SEEK_END);
            if (strcmp(player2_load.user,"BOT")==0){
                save_bazi.vaziyat_bazi=game_loop_bot(&player11_load,&player22_load);
            }
            else {
                save_bazi.vaziyat_bazi = gameloop(&player11_load, &player22_load);
            }
            if (save_bazi.vaziyat_bazi == 10){
                save_kardan(fsave,player1_load,player2_load);
                save_linked_list(fkeshti1,player1_load);
                save_linked_list(fkeshti2,player2_load);
            }
            else{
                save_kardan(fsave_tamam,player1_load,player2_load);
                update_user(fuser,&player1_load);
                if (strcmp(player2_load.user,"BOT")!=0) {
                    update_user(fuser, &player2_load);
                }
                //اپدیته سکه ها
            }
            break;
        case 4://load last game
            if (fread(&a,sizeof(save),1,fsave)<1){
                printf("savei vojod nadarad.\n");
                system("pause");
                goto lab;
            }
            adad_akharin_bazi=print_save_file(fsave);
            save_bazi=entekhab_bazi(fsave,adad_akharin_bazi);
//            if (save_bazi.vaziyat_bazi!=10){
//                printf("in bazi be payan reside ast.\n"
//                       "bazi digari ra entekhab konid.\n");
//                goto lab7;
//            }
            player1_load=save_bazi.bazikon1;
            player2_load=save_bazi.bazikon2;
            nobat=save_bazi.nobat;

            match_kardan_linkedlist_az_file(fkeshti1,&player1_load,adad_akharin_bazi);
            match_kardan_linkedlist_az_file(fkeshti2,&player2_load,adad_akharin_bazi);
            player11_load = &player1_load;
            player22_load = &player2_load;
//            fclose(fsave);
//            FILE *fsave=fopen("save.bin","a+b");
            fseek(fsave,0,SEEK_END);
            if (strcmp(player2_load.user,"BOT")==0){
                save_bazi.vaziyat_bazi=game_loop_bot(&player11_load,&player22_load);
            }
            else {
                save_bazi.vaziyat_bazi = gameloop(&player11_load, &player22_load);
            }
            if (save_bazi.vaziyat_bazi == 10){
                save_kardan(fsave,player1_load,player2_load);
                save_linked_list(fkeshti1,player1_load);
                save_linked_list(fkeshti2,player2_load);
            }
            else{
                save_kardan(fsave_tamam,player1_load,player2_load);
                update_user(fuser,&player1_load);

                if (strcmp(player2_load.user,"BOT")!=0) {
                    update_user(fuser, &player2_load);
                }
                //اپدیته سکه ها
            }
            break;
        case 5://setting
            show5();
            system("pause");
            break;
        case 6://scoreboard
            score_board(fuser);
            printf("tarikhche bazihaye tamam shode: \n");
            print_save_file(fsave_tamam);
            printf("\n\n\n\n");
            system("pause");
            break;
        case 7: //exit
            exit(10);

    }
    fclose(fkeshti_bot);
    fclose(fbot);
    fclose(fkeshti1);
    fclose(fkeshti2);
    fclose(fsave_tamam);
    fclose(fuser);
    fclose(fsave);
    goto lab;
}