#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "conio2.h"
#include "rlyres.h"
int enterchoice()
{

    int choice,i;
    textcolor(YELLOW);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=1;i<=80;i++)
        printf("-");
    printf("\nSelect an option");
    printf("\n1-View Trains");
    printf("\n2-Book Ticket");
    printf("\n3-View Ticket");
    printf("\n4-Search Ticket No");
    printf("\n5-View All Bookings");
    printf("\n6-View Train Bookings");
    printf("\n7-Cancel Ticket");
    printf("\n8-Cancel Train");
    printf("\n9-Quit");
    printf("\n\nEnter choice:");
    scanf(" %d",&choice);
    return choice;

}
void add_trains()
{
    Train alltrains[4]={
              {"123","BPL","GWA",2100,1500},
              {"546","BPL","DEL",3500,2240},
              {"345","HBJ","AGR",1560,1135},
              {"896","HBJ","MUM",4500,3360},
              };
    FILE *fp=fopen("D:\\CodB Projects\\RailRS files\\alltrains.dat","rb");
    if(fp==NULL)
    {
        fp=fopen("D:\\CodB Projects\\RailRS files\\alltrains.dat","wb");
        fwrite(alltrains,4*sizeof(Train),1,fp);
        printf("File created and saved!\n");

    }
    else
        printf("File already present\n");
    fclose(fp);

}
void view_trains()
{
    int i;
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
     for(i=1;i<=80;i++)
        printf("-");
    FILE *fp=fopen("D:\\CodB Projects\\RailRS files\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
    }
    printf("\n\n\n\n");
    fclose(fp);
}

int check_train_no(char *trainno)
{
    FILE *fp=fopen("D:\\CodB Projects\\RailRS files\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
          if(strcmp(tr.train_no,trainno)==0)
          {
                  fclose(fp);
                  return 1;
          }
    }
fclose(fp);
return 0;
}
int check_mob_no(char*p_mob)
{
    if(strlen(p_mob)!=10)
        return 0;
    while(*p_mob!='\0')
    {
        if(isdigit(*p_mob)==0)//return 0 if char is not a digit
            return 0;
        p_mob++;
    }
    return 1;
}

Passenger* get_passenger_details()
{
    clrscr();
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to Exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    static Passenger psn;
    printf("\nEnter passenger name: ");
    fflush(stdin);
    fgets(psn.p_name,20,stdin);
    char* pos;
    pos=strchr(psn.p_name,'\n');
    *pos='\0';
    if(strcmp(psn.p_name,"0")==0)
    {
      textcolor(LIGHTRED);
      gotoxy(2,25);
      printf("Reservation Cancelled !");
      getch();
      textcolor(YELLOW);
      clrscr();
      return NULL;
    }
    int valid;
    printf("Enter Gender(M/F): ");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.gender);
        if(psn.gender=='0')
        {
          textcolor(LIGHTRED);
          gotoxy(2,25);
          printf("\t\t\t\t\t\t\t\t");
          gotoxy(2,25);
          printf("Reservation Cancelled !");
          getch();
          textcolor(YELLOW);
          clrscr();
          return NULL;
        }
        if(psn.gender!='M'&&psn.gender!='F')
        {
            textcolor(LIGHTRED);
            gotoxy(2,25);
            printf("Error! gender should be either M or F(in upper case) !");
            valid=0;
            getch();
            gotoxy(20,3);
            printf(" \b");//or printf("\t\t\t"); gotoxy(20,3);
            textcolor(YELLOW);
        }
    }while(valid==0);

    gotoxy(2,25);
    printf("\t\t\t\t\t\t\t\t");
    gotoxy(1,4);
    printf("Enter Train No: ");
  do
    {
        fflush(stdin);
        scanf("%s",psn.train_no);
        if(strcmp(psn.train_no,"0")==0)
        {
          textcolor(LIGHTRED);
          gotoxy(2,25);
          printf("\t\t\t\t\t\t\t\t");
          gotoxy(2,25);
          printf("Reservation Cancelled !");
          getch();
          textcolor(YELLOW);
          clrscr();
          return NULL;
        }
       valid=check_train_no(psn.train_no); //if train no. wrong then valid become 0.
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(2,25);
            printf("Error! Invalid Train no.!");
            getch();
            gotoxy(17,4);
            printf(" \t\t\t\t");
            gotoxy(17,4);
            textcolor(YELLOW);
        }
    }while(valid==0);
     gotoxy(2,25);
     printf("\t\t\t\t\t\t\t\t");
     gotoxy(1,5);
     printf("Enter travelling class(first AC:F, second AC:S): ");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if(psn.p_class=='0')
        {
          textcolor(LIGHTRED);
          gotoxy(2,25);
          printf("\t\t\t\t\t\t\t\t");
          gotoxy(2,25);
          printf("Reservation Cancelled !");
          getch();
          textcolor(YELLOW);
          clrscr();
          return NULL;
        }
        if(psn.p_class!='S'&& psn.p_class!='F')
        {
            textcolor(LIGHTRED);
            gotoxy(2,25);
            printf("Error! Class should be either F or S(in upper case) !");
            valid=0;
            getch();
            gotoxy(50,5);
            printf(" \b");//or printf("\t\t\t"); gotoxy(50,5);
            textcolor(YELLOW);
        }
    }while(valid==0);
     gotoxy(2,25);
     printf("\t\t\t\t\t\t\t\t");
     gotoxy(1,6);
     printf("Enter Address: ");
     fflush(stdin);
     fgets(psn.address,30,stdin);
      pos=strchr(psn.address,'\n');
     *pos='\0';
    if(strcmp(psn.address,"0")==0)
    {
      textcolor(LIGHTRED);
      gotoxy(2,25);
      printf("\t\t\t\t\t\t\t\t");
      gotoxy(2,25);
      printf("Reservation Cancelled !");
      getch();
      textcolor(YELLOW);
      clrscr();
      return NULL;
    }

    printf("Enter age: ");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%d",&psn.age);
    if(psn.age==0)
    {
      textcolor(LIGHTRED);
      gotoxy(2,25);
      printf("\t\t\t\t\t\t\t\t");
      gotoxy(2,25);
      printf("Reservation Cancelled !");
      getch();
      textcolor(YELLOW);
      clrscr();
      return NULL;
    }
    if(psn.age<0||psn.age>=200)
    {
            textcolor(LIGHTRED);
            gotoxy(2,25);
            printf("Error! Age should be positive and valid !");
            valid=0;
            getch();
            gotoxy(12,7);
            printf("\t\t\t\t");
            gotoxy(12,7);
            textcolor(YELLOW);
    }
    }while(valid==0);
     gotoxy(2,25);
     printf("\t\t\t\t\t\t\t\t");
     gotoxy(1,8);
     printf("Enter Mobile no: ");
      do
    {
        valid=1;
        fflush(stdin);
        fgets(psn.mob_no,12,stdin);
        pos=strchr(psn.mob_no,'\n');
        if(pos!=NULL)
        *pos='\0';
    if(strcmp(psn.mob_no,"0")==0)
    {
      textcolor(LIGHTRED);
      gotoxy(2,25);
      printf("\t\t\t\t\t\t\t\t");
      gotoxy(2,25);
      printf("Reservation Cancelled !");
      getch();
      textcolor(YELLOW);
      clrscr();
      return NULL;
    }
    valid=check_mob_no(psn.mob_no);
     if(valid==0)
    {
            textcolor(LIGHTRED);
            gotoxy(2,25);
            printf("Error! Invalid mobile no!");
            getch();
            gotoxy(18,8);
            printf("\t\t\t\t");
            gotoxy(18,8);
            textcolor(YELLOW);
    }
    }while(valid==0);
     gotoxy(2,25);
     printf("\t\t\t\t\t\t\t\t");
     getch();

    return &psn;
}

int get_booked_ticket_count(char *train_no,char tc)
{
    FILE *fp=fopen("D:\\CodB Projects\\RailRS files\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    int count=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0&&pr.p_class==tc)
            ++count;
    }
    fclose(fp);
    return count;
}
int last_ticket_no()
{
    FILE*fp=fopen("D:\\CodB Projects\\RailRS files\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    fseek(fp,-1L*sizeof(pr),SEEK_END);//SEEK_END put the cursor at EOF
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;
}

int book_ticket(Passenger p)
{
   int tc=get_booked_ticket_count(p.train_no,p.p_class);
   if(tc==4)
   {
    //gotoxy();
    textcolor(LIGHTRED);
    printf("All seats full in train no %s in %c class!",p.train_no,p.p_class);
    return -1;
   }
   p.ticketno=last_ticket_no()+1;
    FILE*fp=fopen("D:\\CodB Projects\\RailRS files\\allbookings.dat","ab");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File can't be opened");
        return -1;
    }
   fwrite(&p,sizeof(p),1,fp);
   fclose(fp);
   return p.ticketno;
}

int accept_ticket_no()
{
    gotoxy(50,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to Exit input screen");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter a valid ticket no: ");
    int valid;
    int ticket_no;
    do
    {
      valid=1;
      scanf("%d",&ticket_no);
      if(ticket_no==0)
      {
       textcolor(LIGHTRED);
       gotoxy(2,25);
       printf("\t\t\t\t\t\t\t\t");
       gotoxy(2,25);
       printf("Cancelling the input...");
       getch();
       textcolor(YELLOW);
       clrscr();
       return 0;
      }
     if(ticket_no<0)
    {
            textcolor(LIGHTRED);
            gotoxy(2,25);
            printf("Error! Invalid (Ticket number should be positive)!");
            getch();
            valid=0;
            gotoxy(26,1);
            printf("\t\t\t\t");
            gotoxy(26,1);
            textcolor(YELLOW);
    }
    }while(valid==0);
    return ticket_no;
}

void view_ticket(int ticket_no)
{
    FILE*fp=fopen("D:\\CodB Projects\\RailRS files\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File not available");
    }
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(ticket_no==pr.ticketno)
        {
            printf("\nNAME:%s\nGENDER:%c\nTRAIN NO:%s\nCLASS:%c\nADDRESS:%s\nAGE:%d\nMOBILE NO:%s\nTICKET NO:%d",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticketno);
            found=1;
            break;
        }
    }
    if(found==0)
    {
        textcolor(LIGHTRED);
        printf("\nNo ticket booked against ticket no %d",ticket_no);
    }
    fclose(fp);
}

char *accept_mob_no()
{
    static char mob_no[12];
    char*pos;
    int valid;
    printf("Enter valid mobile no: ");
    do
    {
      fflush(stdin);
      fgets(mob_no,13,stdin);
       pos=strchr(mob_no,'\n');
        if(pos!=NULL)
        *pos='\0';
    if(strcmp(mob_no,"0")==0)
    {
      textcolor(LIGHTRED);
      gotoxy(2,25);
      printf("\t\t\t\t\t\t\t\t");
      gotoxy(2,25);
      printf("Exiting input screen...");
      getch();
      textcolor(YELLOW);
      clrscr();
      return NULL;
    }
    valid=check_mob_no(mob_no);
     if(valid==0)
    {
            textcolor(LIGHTRED);
            gotoxy(2,25);
            printf("Error! Invalid mobile no!");
            getch();
            gotoxy(24,1);
            printf("\t\t\t\t");
            gotoxy(24,1);
            textcolor(YELLOW);
    }
    }while(valid==0);
    clrscr();
    return mob_no;
}

int * get_ticket_no(char*mbn)
{
    int count=0;
   FILE*fp=fopen("D:\\CodB Projects\\RailRS files\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File is not present");
        return NULL;
    }
    Passenger pr;
     while(fread(&pr,sizeof(pr),1,fp)==1)
     {
          if(strcmp(pr.mob_no,mbn)==0)
          {
              ++count;
          }
     }
     if(count==0)
       {
         fclose(fp);
         return NULL;
       }

           int *arr=(int*)malloc((count+1)*sizeof(int));
           rewind(fp);// or fseek(fp,0,SEEK_SET);
           count=0;
        while(fread(&pr,sizeof(pr),1,fp)==1)
          {
            if(strcmp(pr.mob_no,mbn)==0)
            {
              *(arr+count)=pr.ticketno; //*arr[count]=pr.ticketno;//we shouldn't increment the pointer itself(arr++), since we need the base address.
              count++;
            }
          }
           *(arr+count)=-1; //arr[count]=-1;//this is at the last index of the array

       fclose(fp);
       return arr;
}

void view_all_tickets(char*pmob_no,int*pticket_no)
{
  if(pticket_no==NULL)
  {
      textcolor(LIGHTRED);
      printf("Sorry! No Tickets booked against given mob no %s",pmob_no);
      textcolor(WHITE);
      printf("\npress any key to go back to main screen");
      getch();
      textcolor(YELLOW);
      return;
  }
  printf("Following are the tickets booked for given mob no %s:",pmob_no);
  int i;
  printf("\n\nTICKET NO.");
  printf("\n-------------------------------------------------------------");
  for(i=0;*(pticket_no+i)!=-1;i++)
  {
      printf("\n %d",*(pticket_no+i));
  }
  textcolor(WHITE);
   printf("\npress any key to go back to main screen");
   textcolor(YELLOW);
   getch();
   free(pticket_no);
   return;
}

char* accept_train_no()
{
    static char train_no[10];
    int valid;
      gotoxy(57,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit input ");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter a valid Train no: ");
    do
    {
      fflush(stdin);
     scanf("%s",train_no); //input will have no spaces so no need of fgets(train_no,11,stdin);
    if(strcmp(train_no,"0")==0)
    {
      textcolor(LIGHTRED);
      gotoxy(2,25);
      printf("\t\t\t\t\t\t\t\t");
      gotoxy(2,25);
      printf("Exiting input screen...");
      getch();
      textcolor(YELLOW);
      clrscr();
      return NULL;
    }
    valid=check_train_no(train_no);
     if(valid==0)
    {
            textcolor(LIGHTRED);
            gotoxy(2,25);
            printf("Error! Invalid Train no!");
            getch();
            gotoxy(25,1);
            printf("\t\t\t\t");
            gotoxy(25,1);
            textcolor(YELLOW);
    }
    }while(valid==0);
    clrscr();
    return train_no;
}

void view_bookings(char*train_no)
{
    int found=0;
    FILE*fp=fopen("D:\\CodB Projects\\RailRS files\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File is not present");
        return;
    }
    Passenger pr;
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(found=80;found>0;found--)
    printf("-");
    int row=3;
     while(fread(&pr,sizeof(pr),1,fp)==1)
     {
          if(strcmp(pr.train_no,train_no)==0)
          {
              ++found;
              printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
              gotoxy(41,row);
              printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
              row++;
          }
     }
     if(found==0) //or  if(!found)
       {
         clrscr();
         textcolor(LIGHTRED);
         printf("\n No bookings in given train no %s",train_no);
       }
       fclose(fp);
       textcolor(WHITE);
       printf("\n\nPress any key to go back to main menu");
       textcolor(YELLOW);
       getch();
}

void view_all_bookings()
{
    int found=0;
    FILE*fp=fopen("D:\\CodB Projects\\RailRS files\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File is not present");
        return;
    }
    Passenger pr;
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(found=80;found>0;found--)
    printf("-");
    int row=3;
     while(fread(&pr,sizeof(pr),1,fp)==1)
     {
              ++found;
              printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
              gotoxy(41,row);
              printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
              row++;
     }
     if(found==0) //or  if(!found)
       {
         clrscr();
         textcolor(LIGHTRED);
         printf("\n No booking details found in the file!!");
       }
       fclose(fp);
       textcolor(WHITE);
       printf("\n\nPress any key to go back to main menu");
       textcolor(YELLOW);
       getch();
}

int cancel_ticket(int ticket_no)
{
    int result;
    FILE *fp1=fopen("D:\\CodB Projects\\RailRS files\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("No Bookings done yet!");
        return -1;
    }
    FILE *fp2=fopen("D:\\CodB Projects\\RailRS files\\temp.dat","wb");
    Passenger pr;
    int found=0;//i;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            found=1;
            /*textcolor(WHITE);
            printf("\n\nPress any key to confirm cancellation of the above ticket ");
            scanf(" %d",&i);
            if(i==0)
            {
                clrscr();
                return 3;
            }*/
            clrscr();
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("D:\\CodB Projects\\RailRS files\\temp.dat");
    }
    else
    {
        result=remove("D:\\CodB Projects\\RailRS files\\allbookings.dat");
        if(result!=0)
            return 2;

        result=rename("D:\\CodB Projects\\RailRS files\\temp.dat","D:\\CodB Projects\\RailRS files\\allbookings.dat");
        if(result!=0)
            return 2;
    }
    return found;
}

void add_trains2()
{
    int valid;
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to Exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    Train psn;
    printf("\nEnter Train number: ");
    fflush(stdin);
    scanf("%s",psn.train_no);
    /*fgets(psn.train_no,11,stdin);
    char* pos;
    pos=strchr(psn.train_no,'\n');
    *pos='\0';*/
    if(strcmp(psn.train_no,"0")==0)
    {
      textcolor(LIGHTRED);
      gotoxy(2,25);
      printf("Adding Train aborted!");
      getch();
      textcolor(YELLOW);
      clrscr();
      return;
    }

    gotoxy(1,3);
    printf("Enter Train From: ");
        fflush(stdin);
        fgets(psn.from,11,stdin);
        char* pos;
        pos=strchr(psn.from,'\n');
        *pos='\0';
        //scanf("%s",psn.from);
        if(strcmp(psn.from,"0")==0)
        {
          textcolor(LIGHTRED);
          gotoxy(2,25);
          printf("\t\t\t\t\t\t\t\t");
          gotoxy(2,25);
          printf("Adding Train aborted!");
          getch();
          textcolor(YELLOW);
          clrscr();
          return;
        }

     gotoxy(2,25);
     printf("\t\t\t\t\t\t\t\t");
     gotoxy(1,4);
        printf("Enter Train To: ");
        fflush(stdin);
        fgets(psn.to,11,stdin);
        pos=strchr(psn.to,'\n');
        *pos='\0';
        //scanf("%s",psn.from);
        if(strcmp(psn.to,"0")==0)
        {
          textcolor(LIGHTRED);
          gotoxy(2,25);
          printf("\t\t\t\t\t\t\t\t");
          gotoxy(2,25);
          printf("Adding Train aborted!");
          getch();
          textcolor(YELLOW);
          clrscr();
          return;
        }
    do
    {
        gotoxy(2,25);
        printf("\t\t\t\t\t\t\t\t");
        gotoxy(1,5);
        printf("Enter First AC fare: ");
        valid=1;
        fflush(stdin);
        scanf("%d",&psn.fac_fare);
    if(psn.fac_fare==0)
    {
      textcolor(LIGHTRED);
      gotoxy(2,25);
      printf("\t\t\t\t\t\t\t\t");
      gotoxy(2,25);
      printf("Adding Train aborted!");
      getch();
      textcolor(YELLOW);
      clrscr();
      return;
    }
    if(psn.fac_fare<0||psn.fac_fare>=10000)
    {
            textcolor(LIGHTRED);
            gotoxy(2,25);
            printf("Error! Abnormal fare");
            valid=0;
            getch();
            gotoxy(22,5);
            printf("\t\t\t\t");
            gotoxy(22,5);
            textcolor(YELLOW);
    }
    }while(valid==0);

     do
    {
        gotoxy(2,25);
        printf("\t\t\t\t\t\t\t\t");
        gotoxy(1,6);
        printf("Enter Second AC fare: ");
        valid=1;
        fflush(stdin);
        scanf("%d",&psn.sac_fare);
    if(psn.sac_fare==0)
    {
      textcolor(LIGHTRED);
      gotoxy(2,25);
      printf("\t\t\t\t\t\t\t\t");
      gotoxy(2,25);
      printf("Adding Train aborted!");
      getch();
      textcolor(YELLOW);
      clrscr();
      return;
    }
    if(psn.sac_fare<0||psn.sac_fare>=10000)
    {
            textcolor(LIGHTRED);
            gotoxy(2,25);
            printf("Error! Abnormal fare");
            valid=0;
            getch();
            gotoxy(23,6);
            printf("\t\t\t\t");
            gotoxy(23,6);
            textcolor(YELLOW);
    }
    }while(valid==0);

    FILE*fp=fopen("D:\\CodB Projects\\RailRS files\\alltrains.dat","ab");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File can't be opened");
        getch();
        return;
    }
   if(fwrite(&psn,sizeof(psn),1,fp)==1)
   {
    clrscr();
    textcolor(LIGHTGREEN);
    printf("New Train details added to the file successfully!");
   }
    textcolor(WHITE);
    printf("\n\npress any key to go back to the main screen");
    getch();
   fclose(fp);
}

int cancel_train(char*train_no)
{
    int found=0;
    FILE*fp=fopen("D:\\CodB Projects\\RailRS files\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File is not present");
        return -1;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
     {
          if(strcmp(pr.train_no,train_no)==0)
          {
             found=cancel_ticket(pr.ticketno);
             if(found==2)
             {
                textcolor(LIGHTRED);
                printf("Error in ticket cancellation. Try later!");
                getch();
                return -1;
             }
          }
     }
       fclose(fp);

    int result;
    FILE *fp1=fopen("D:\\CodB Projects\\RailRS files\\alltrains.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("Error in opening train file!");
        return -1;
    }
    FILE *fp2=fopen("D:\\CodB Projects\\RailRS files\\temp.dat","wb");
    Train tr;
    found=0;//i;
    while(fread(&tr,sizeof(tr),1,fp1)==1)
    {
        if(strcmp(tr.train_no,train_no)==0)
        {
            found=1;
        }
        else
        {
            fwrite(&tr,sizeof(tr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("D:\\CodB Projects\\RailRS files\\temp.dat");
    }
    else
    {
        result=remove("D:\\CodB Projects\\RailRS files\\alltrains.dat");
        if(result!=0)
            return 2;

        result=rename("D:\\CodB Projects\\RailRS files\\temp.dat","D:\\CodB Projects\\RailRS files\\alltrains.dat");
        if(result!=0)
            return 2;
    }
    return found;
}
