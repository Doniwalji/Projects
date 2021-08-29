#include <stdio.h>
#include <stdlib.h>
#include "conio2.h"
#include "rlyres.h"
int main()
{
    int choice,ticket_no,result; char c;
    char*pmob_no,*ptrain_no;
    int*pticket_no;
    Passenger *ptr;
    add_trains();
    while(1)
    {
        choice=enterchoice();
        if(choice==9)
            exit(0);
        switch(choice)
        {
                       case 1:
                                    view_trains();
                                    getch();
                                    clrscr();
                                    break;
                       case 2:
                                    //book_ticket();
                                    ptr=get_passenger_details();
                                    clrscr();
                                    if(ptr!=NULL)
                                    {
                                       ticket_no=book_ticket(*ptr);
                                       if(ticket_no==-1)
                                       {
                                           textcolor(LIGHTRED);
                                           printf(" Booking Failed");
                                       }
                                       else
                                       {
                                           textcolor(LIGHTGREEN);
                                           printf("Ticket Successfully Booked");
                                           printf("\nyour ticket number is: %d",ticket_no);
                                       }
                                       textcolor(WHITE);
                                       printf("\nPress any key to go back to the main screen");
                                       getch();
                                       clrscr();
                                    }
                                    break;
                       case 3:
                                    //view_ticket();
                                    do
                                    {
                                    result=1;
                                    clrscr();
                                    ticket_no=accept_ticket_no();
                                    if(ticket_no!=0)
                                        view_ticket(ticket_no);
                                    textcolor(WHITE);
                                    printf("\n\npress Y to view another ticket or\npress any other key to go back to the main screen:");
                                    scanf(" %c",&c);
                                    if(c=='Y'||c=='y')
                                        result=0;
                                    }while(result==0);
                                    clrscr();
                                    break;
                       case 4:
                                    //get_ticket_no();
                                    clrscr();
                                    pmob_no=accept_mob_no();
                                    if(pmob_no!=NULL)
                                    {
                                        pticket_no=get_ticket_no(pmob_no);
                                        view_all_tickets(pmob_no,pticket_no);
                                    }
                                    clrscr();
                                    break;
                       case 5:
                                    //view_all_bookings();
                                    clrscr();
                                    view_all_bookings();
                                    clrscr();
                                    break;
                       case 6:
                                    //view_bookings();
                                    clrscr();
                                    ptrain_no=accept_train_no();
                                    if(ptrain_no!=NULL)
                                    {
                                        view_bookings(ptrain_no);
                                    }
                                    clrscr();
                                    break;
                       case 7:
                                    //cancel_ticket();
                                    clrscr();
                                    ticket_no=accept_ticket_no();

                                    if(ticket_no!=0)
                                    {
                                       clrscr();
                                    /*{  gotoxy(65,1);
                                         textcolor(LIGHTGREEN);
                                         printf("Press 0 to Exit");
                                         gotoxy(1,1);
                                         textcolor(YELLOW);
                                         view_ticket(ticket_no);
                                      }*/
                                        result=cancel_ticket(ticket_no);
                                        if(result==0)
                                        {
                                            textcolor(LIGHTRED);
                                            printf("Not found, No ticket booked against ticket no %d",ticket_no);
                                        }
                                        else if(result==1)
                                        {
                                          textcolor(LIGHTGREEN);
                                          printf("\nTicket no %d successfully cancelled",ticket_no);
                                        }
                                        else if(result==2)
                                        {
                                            textcolor(LIGHTRED);
                                            printf("Error in cancellation. Try later!");
                                        }
                                        textcolor(WHITE);
                                        printf("\n\nPress any key to go back to main screen");
                                        getch();
                                    }
                                    clrscr();
                                    break;
                       case 8:
                                    //cancel_train();
                                    clrscr();
                                    ptrain_no=accept_train_no();
                                    if(ptrain_no!=NULL)
                                    {
                                           clrscr();
                                    /*{  gotoxy(65,1);
                                         textcolor(LIGHTGREEN);
                                         printf("Press 0 to Exit");
                                         gotoxy(1,1);
                                         textcolor(YELLOW);
                                         view_ticket(ticket_no);
                                      }*/
                                        result=cancel_train(ptrain_no);
                                        if(result==0)
                                        {
                                           textcolor(LIGHTRED);
                                           printf("Train no %s not found in file",ptrain_no);
                                        }
                                        else if(result==1)
                                        {
                                           textcolor(LIGHTGREEN);
                                           printf("\nTrain no %s successfully cancelled",ptrain_no);
                                        }
                                        else if(result==2)
                                        {
                                           textcolor(LIGHTRED);
                                           printf("Error in cancellation(remove,rename). Try later!");
                                        }

                                        textcolor(WHITE);
                                        printf("\n\nPress any key to go back to main screen");
                                        getch();

                                    }
                                    clrscr();
                                    break;
                       case 10:
                                    //add train;
                                    clrscr();
                                    add_trains2();
                                    clrscr();
                                    break;
                       default:
                                      textcolor(LIGHTRED);
                                      printf("Wrong Choice! Try Again\n");
                                      getch();
                                      clrscr();
        }
    }

    return 0;
}
