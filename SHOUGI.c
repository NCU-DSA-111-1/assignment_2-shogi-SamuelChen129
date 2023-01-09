#include<stdio.h>
#include<stdlib.h>
#include <locale.h>
#include <wchar.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#include"tools.h"


int main(int argc,char *argv[])
{
    bool player=true;
    int win=0;
    enum chess_type {
                     BU_1=0,SHUN_1=1,GWAE_1=2,SILVER_1=3,GOLD_1=4,
                     KING_1=5,GIOAW_1=6,FEI_1=7,GIOAW_S_1=8,FEI_S_1=9,
                     BU_2=10,SHUN_2=11,GWAE_2=12,SILVER_2=13,GOLD_2=14,
                     KING_2=15,GIOAW_2=16,FEI_2=17,GIOAW_S_2=18,FEI_S_2=19,
                     BU_S_1=20,SHUN_S_1=21,GWAE_S_1=22,SILVER_S_1=23,
                     BU_S_2=30,SHUN_S_2=31,GWAE_S_2=32,SILVER_S_2=33                   
                    };
    int die[MAXDIE]={40};//die[] is the number of the chess,not the type of the chess
    int eat=0;
    int board[3][MAXCHESS];
    int ori_row,ori_col,des_row,des_col;
    int moved_chess;
    char en,act;
    bool correct,has_chess;
    int step=1;
    struct record{
        record *prev; 
        int step;
        int num;//the number of the moving chess
        int type;
        int o_row;
        int o_col;
        int d_row;
        int d_col;
        int eat_type;
        int eat_num;//the number of the eaten chess
        char enhanced;
        char act;
        record *next;
    };
    setlocale(LC_ALL, "chs");
    //get the instruction to determine we should open new game or load the record
    //instr[2] is the name of the record file
    int c,m;
    char *filename;
    extern char *optarg;
    extern int optind, opterr, optopt;
    while((c=getopt(argc, argv, "ns:l:")) != -1)
    {
       switch(c)
       {
        case 'n':
           m=c;
        break;
        case 's':
           filename=optarg;
        break;
        case 'l':
           m=c;
           filename=optarg;
        break;
        case '?'://the command is invalid
        puts("wrong command");
        break;
       }
    } 
    //load the old game
    record *replay;
    replay=NULL;
    record *last_step;
    if(m=='l')
    {
        char data[100];
        FILE *file;
        file=fopen(filename,"r");
        for(int i=0;i<11;i++){fscanf(file,"%s",&data);}
        while(!feof(file))
        {
            record *tmp;
            tmp=(record*)malloc(sizeof(record));
            if(replay!=NULL)
                replay->next=tmp;
            fscanf(file,"%d",&tmp->step);
            fscanf(file,"%d",&tmp->num);
            fscanf(file,"%d",&tmp->type);
            fscanf(file,"%d",&tmp->o_row);
            fscanf(file,"%d",&tmp->o_col);
            fscanf(file,"%d",&tmp->d_row);
            fscanf(file,"%d",&tmp->d_col);
            fscanf(file,"%d",&tmp->eat_num);
            fscanf(file,"%d",&tmp->eat_type);
            fscanf(file,"%s",&tmp->enhanced);
            fscanf(file,"%s",&tmp->act);
            tmp->prev=replay;
            replay=tmp;
        }
        last_step=replay;
        while((replay->prev)!=NULL)
        {
            replay=(replay->prev);
        }
    }
    initial(board);
    show_checkerboard(player,board);
    //old game
    while(m=='l'){
        printf("enter \033[32mf\033[m for next step\n");
        printf("enter \033[32mb\033[m for last step\n");
        printf("enter \033[32mq\033[m if you want to quit\n");
        printf("->");
        scanf("%s",&act);
        if(act=='q'){break;}
        if(act=='b')
        {
            if((replay->step)==1)
            {
                printf("this is the first step!\n");
                show_checkerboard(player,board);
                continue;
            }
            replay=(replay->prev);
            if((replay->act)=='a' || (replay->act)=='e')
            {
                board[0][(replay->num)]=(replay->o_row);
                board[1][(replay->num)]=(replay->o_col);
                if((replay->act)=='e')
                {
                    board[0][(replay->eat_num)]=(replay->d_row);
                    board[1][(replay->eat_num)]=(replay->d_col);
                    board[2][(replay->eat_num)]=(replay->eat_type);                                       
                }
            }
            if((replay->act)=='d')
            {
                board[0][(replay->num)]=0;
                board[1][(replay->num)]=0;
            }
            if((replay->enhanced)=='y')
            {
                board[2][(replay->num)]=level_down(board[2][(replay->num)]);
            }
        }
        if(act=='f')
        {
            if(replay==last_step)
            {
                printf("no more step!\n");
                show_checkerboard(player,board);
                continue;
            }
            if((replay->act)=='a' || (replay->act)=='e')
            {
                board[0][(replay->num)]=(replay->d_row);
                board[1][(replay->num)]=(replay->d_col);
                if((replay->act)=='e')
                {
                    board[0][(replay->eat_num)]=0;
                    board[1][(replay->eat_num)]=0;                                       
                }
            }
            if((replay->act)=='d')
            {
                board[0][(replay->num)]=(replay->d_row);
                board[1][(replay->num)]=(replay->d_col);
                board[2][(replay->num)]=(replay->type);
            }
            if((replay->enhanced)=='y')
            {
                board[2][(replay->num)]=level_up(board[2][(replay->num)]);
            }
            replay=(replay->next);
        }  
        show_checkerboard(player,board);       
    }
    //new game
    record *process;
    process=NULL;
    record *first_step;
    while(m=='n'){
        has_chess=false;
        if(player){printf("player1,\n");}
        if(!player){printf("player2,\n");}
        printf("enter \033[32ma\033[m if you want to move the chess on the board\n");
        printf("enter \033[32md\033[m if you want to put the died chess on the board\n");
        printf("enter \033[32m0\033[m if your opponent wants to change his/her last move\n");
        printf("enter \033[32ms\033[m if you want to save the gaming record\n");
        printf("enter \033[32mq\033[m if you want to quit the game\n");
        printf("->");
        scanf("%s",&act);
        if(act=='q'){break;}
        if(act=='d')
        {   
            int n=0;
            int chess_for_put[MAXDIE]={40};  
            n=0;
            for(int i=0;i<eat;i++)
            {
                if(player && whose(board[2][die[i]]))
                {
                    chess_for_put[n]=die[i];
                    n++;
                }
                if(!player && !whose(board[2][die[i]]))
                {
                    chess_for_put[n]=die[i];
                    n++;
                }
            }
            for(int i=0;i<n;i++)
            {
                int tmp;
                if(player)
                {
                    tmp=board[2][chess_for_put[i]];
                }
                if(!player)
                {
                    tmp=board[2][chess_for_put[i]]-10;
                }
                printf("%d",i);
                switch(tmp)
                {
                    setlocale(LC_ALL, "chs");
                    case 0:
                        wprintf(L"步 ");
                        break;
                    case 1:
                        wprintf(L"香 ");
                        break;
                    case 2:
                        wprintf(L"桂 ");
                        break;
                    case 3:
                        wprintf(L"銀 ");
                        break;
                    case 4:
                        wprintf(L"金 ");
                        break;
                    case 5:
                        wprintf(L"王 ");
                        break;
                    case 6:
                        wprintf(L"角 ");
                        break;
                    case 7:
                        wprintf(L"飛 ");
                        break;
                }
            }
            printf("\n");
            if(n>0)
            {
                printf("enter the number on the left of the chess you want put:");
                int put,put_row,put_col;
                scanf("%d",&put);
                if(put>n-1 || put<0)
                {
                    printf("this is not in the options!\n");
                    continue;
                }
                printf("input the position you want to put to\n");
                wprintf(L"段:");
                scanf("%d",&put_row);
                wprintf(L"筋:");
                scanf("%d",&put_col);
                //checking if the desired position is out of the checkerboard
                if(put_col>9 || put_col<1 || put_row>9 || put_row<1)
                {
                    show_checkerboard(player,board);
                    printf("the position is out of the checkerboard!\n");
                    continue;
                }
                //checking if the desired position has any chess on it
                bool position_has_chess=false;
                for(int i=0;i<MAXCHESS;i++)
                {
                    if(board[0][i]==put_row && board[1][i]==put_col)
                    {
                        position_has_chess=true;
                        break;
                    }
                }
                if(position_has_chess)
                {
                    show_checkerboard(player,board);
                    printf("the position is already has chess!\n");
                    continue;
                }

                board[0][chess_for_put[put]]=put_row;
                board[1][chess_for_put[put]]=put_col;

                //checking if it's checkmate
                if(!player)
                {change_view(board);}
                if(checkmate(board))
                {
                    printf("!!!!!checkmate!!!!!\n");
                }
                if(!player)
                {change_view(board);}

                //after putting the chess, compact the "die" stack
                int gap;
                for(int i=0;i<eat;i++)       
                {
                    if(die[i]==chess_for_put[put])
                    {
                        gap=i;
                        break;
                    }
                } 
                for(int i=gap;i<eat;i++)
                {
                    die[i]=die[i+1];
                }
                eat--;

                //save the process
                record *tmp; 
                tmp=(record*)malloc(sizeof(record));
                if(process!=NULL)
                    process->next=tmp;
                else
                    first_step=tmp;
                tmp->step=step;
                tmp->num=chess_for_put[put];
                tmp->type=board[2][chess_for_put[put]];
                tmp->o_row=0;
                tmp->o_col=0;
                tmp->d_row=put_row;
                tmp->d_col=put_col;
                tmp->eat_type=40;
                tmp->eat_num=40;
                tmp->enhanced='n';
                tmp->act='d';
                tmp->prev=process;
                process=tmp;
                step++;

                player=!player;
                change_view(board);
                show_checkerboard(player,board);
            }
            //if the player has not eaten any chess , then this action is meaningless 
            if(n==0)
            {
                show_checkerboard(player,board);
                printf("no chess to put\n");
            }
            continue;
        }
        if(act=='0')
        {
            if(step==1){
                show_checkerboard(player,board);
                printf("this is the first step!\n");
                continue;
            }
            step--;
            record *tmp;
            tmp=process;
            //back to last situation
            if((process->act)=='a' || (process->act)=='e')
            {
                if(!player){
                    board[0][(process->num)]=10-(process->o_row);
                    board[1][(process->num)]=10-(process->o_col);
                }
                if(player){
                    board[0][(process->num)]=(process->o_row);
                    board[1][(process->num)]=(process->o_col);
                }
                //if the chess has enhanced, let it degenerates
                if((process->enhanced)=='y')
                {
                    board[2][(process->num)]=level_down(board[2][(process->num)]);
                }
                //if a chess has eaten, let it comes back
                if((process->act)=='e')
                {                     
                    if(!player){
                        board[0][(process->eat_num)]=10-(process->d_row);
                        board[1][(process->eat_num)]=10-(process->d_col);
                    }
                    if(player){
                        board[0][(process->eat_num)]=(process->d_row);
                        board[1][(process->eat_num)]=(process->d_col);
                    }
                    board[2][(process->eat_num)]=(process->eat_type);
                    eat--;
                }
            }
            //if the chess has reborned, let it die
            if((process->act)=='d')
            {
                board[0][(process->num)]=0;
                board[1][(process->num)]=0;
                die[eat]=(process->num);
                eat++;
            }
            process=(process->prev);
            free(tmp);
            player=!player;
            change_view(board);
            show_checkerboard(player,board);
            continue;
        }
        if(act=='s')
        {
            record *save;
            save=first_step;
            FILE *file;
            file=fopen(filename,"w+");
            fprintf(file,"step  chess_num  chess_type  src_row  src_col  next_row  next_col  eat_num  eat_type  enhanced?  act\n");
            for(int i=1;i<step;i++)
            {
                fprintf(file,"%d",(save->step));
                for(int i=0;i<4;i++){fprintf(file," ");}
                if((save->step)<10){fprintf(file," ");}

                fprintf(file,"%d",(save->num));
                for(int i=0;i<9;i++){fprintf(file," ");}
                if((save->num)<10){fprintf(file," ");}

                fprintf(file,"%d",(save->type));
                for(int i=0;i<10;i++){fprintf(file," ");}
                if((save->type)<10){fprintf(file," ");}

                fprintf(file,"%d",(save->o_row));
                for(int i=0;i<7;i++){fprintf(file," ");}
                if((save->o_row)<10){fprintf(file," ");}

                fprintf(file,"%d",(save->o_col));
                for(int i=0;i<7;i++){fprintf(file," ");}
                if((save->o_col)<10){fprintf(file," ");}

                fprintf(file,"%d",(save->d_row));
                for(int i=0;i<8;i++){fprintf(file," ");}
                if((save->d_row)<10){fprintf(file," ");}

                fprintf(file,"%d",(save->d_col));
                for(int i=0;i<8;i++){fprintf(file," ");}
                if((save->d_col)<10){fprintf(file," ");}
                
                fprintf(file,"%d",(save->eat_num));
                for(int i=0;i<7;i++){fprintf(file," ");}
                if((save->eat_num)<10){fprintf(file," ");}

                fprintf(file,"%d",(save->eat_type));
                for(int i=0;i<8;i++){fprintf(file," ");}
                if((save->eat_type)<10){fprintf(file," ");}

                fprintf(file,"%c",(save->enhanced));
                for(int i=0;i<10;i++){fprintf(file," ");}

                fprintf(file,"%c\n",(save->act));
                save=save->next;
            }
            fclose(file);
            show_checkerboard(player,board);
            continue;
        }
        //moving chess
        printf("input the position of chess you want to move\n");
        wprintf(L"段:");
        scanf("%d",&ori_row);
        wprintf(L"筋:");
        scanf("%d",&ori_col);
        printf("input the position you want to move to\n");
        wprintf(L"段:");
        scanf("%d",&des_row);
        wprintf(L"筋:");
        scanf("%d",&des_col);
        record *tmp;
        tmp=(record*)malloc(sizeof(record));
        (tmp->o_row)=ori_row;
        (tmp->o_col)=ori_col;
        (tmp->d_row)=des_row;
        (tmp->d_col)=des_col;
        (tmp->eat_type)=40;
        (tmp->eat_num)=40;
        (tmp->enhanced)='n';
        (tmp->act)='a';
        if(!player)
        {
            ori_row=10-ori_row;
            ori_col=10-ori_col;
            des_row=10-des_row;
            des_col=10-des_col;
        }
        for(int i=0;i<MAXCHESS;i++)
        {
            if(board[0][i]==ori_row && board[1][i]==ori_col)
            {
                has_chess=true;
                correct=rule_checking(des_col,des_row,ori_col,ori_row,board[2][i],board);
                //check if there's an obstacle on the position which the chess move to
                if(correct){
                    for(int j=0;j<MAXCHESS;j++)
                    {
                        if(board[0][j]==des_row && board[1][j]==des_col)
                        {
                            if(player && whose(board[2][i])){
                                if(whose(board[2][j])){correct = false;}
                                else{
                                    board[0][j]=0;board[1][j]=0;//if the chess on the destination is player2's,eat it
                                    (tmp->eat_type)=board[2][j];
                                    if(board[2][j]>=10 && board[2][j]<=17){board[2][j]=board[2][j]-10;}
                                    if(board[2][j]==GIOAW_S_2 || board[2][j]==FEI_S_2){board[2][j]=board[2][j]-12;}
                                    if(board[2][j]>=30 && board[2][j]<=33){board[2][j]=board[2][j]-30;}
                                    die[eat]=j;
                                    eat++;
                                    (tmp->act)='e';
                                    (tmp->eat_num)=j;
                                    if(board[2][j]==KING_2){win=1;}//if the eaten chess is king,the player1 wins
                                }
                            }
                            if(!player && !(whose(board[2][i]))){
                                if(!(whose(board[2][j]))){correct = false;}
                                else{
                                    board[0][j]=0;board[1][j]=0;//if the chess on the destination is player1's,eat it
                                    (tmp->eat_type)=board[2][j];
                                    if(board[2][j]>=0 && board[2][j]<=7){board[2][j]=board[2][j]+10;}
                                    if(board[2][j]==GIOAW_S_1 || board[2][j]==FEI_S_1){board[2][j]=board[2][j]+8;}
                                    if(board[2][j]>=20 && board[2][j]<=23){board[2][j]=board[2][j]-10;}
                                    die[eat]=j;
                                    eat++;
                                    (tmp->act)='e';
                                    (tmp->eat_num)=j;
                                    if(board[2][j]==KING_1){win=2;}//if the eaten chess is king,the player2 wins
                                }
                            }
                            break; 
                        }
                    }
                }
                moved_chess=i;
                break;
            }
        }
        //check if the move is beyond the board
        if(des_col>9 || des_col<1 || des_row>9 || des_row<1){correct = false;}
        //check if there's a chess on the position choosed
        if(!has_chess){correct = false;}
        //check if the player is using his/her chess
        if(has_chess && player && !whose(board[2][moved_chess]))
        {
            correct = false;
            printf("that's not your chess,");
        }
        if(has_chess && !player && whose(board[2][moved_chess]))
        {
            correct = false;
            printf("that's not your chess,");
        }
        //if all the checking is passed, move the chess
        //enhance the chess if the player wants
        if(correct)
        {
            board[0][moved_chess]=des_row;board[1][moved_chess]=des_col;
            player=!player;
            change_view(board);           
        }
        if( board[0][moved_chess]>6 && 
            board[2][moved_chess]!=GOLD_1 && board[2][moved_chess]!=KING_1
         && board[2][moved_chess]!=GIOAW_S_1 &&board[2][moved_chess]!=FEI_S_1 &&  
            board[2][moved_chess]!=GOLD_2 && board[2][moved_chess]!=KING_2
         && board[2][moved_chess]!=GIOAW_S_2 &&board[2][moved_chess]!=FEI_S_2 &&
            board[2][moved_chess]<20 && 
            correct)
        {
            printf("enhanced the chess?(y/n)");
            scanf("%s",&en);//scanf("%c",&en) can't be executed
            if(en=='y' || en=='Y')
            {
                (tmp->enhanced)='y';
                board[2][moved_chess]=level_up(board[2][moved_chess]);
            }
        }
        //save the process
        if(correct)
        {
            if(process!=NULL)
                (process->next)=tmp;
            else
                first_step=tmp;
            (tmp->step)=step;
            (tmp->num)=moved_chess;
            (tmp->type)=board[2][moved_chess];
            (tmp->prev)=process;
            process=tmp;
            step++;
        }
        else
            free(tmp);
        //checking if it's checkmate
        if(!player)
        {change_view(board);}
        if(correct && checkmate(board))
        {
            printf("!!!!!checkmate!!!!!\n");
        }
        if(!player)
        {change_view(board);}
        if(!correct)
        {
            if(!has_chess){printf("there's no chess on the position you choosed,");}
            printf("the move is illegal!\n");
        }
        show_checkerboard(player,board);
        if(win==1){printf("player1 wins!");break;}
        if(win==2){printf("player2 wins!");break;}
    }
    return 0;
}
//main func end
