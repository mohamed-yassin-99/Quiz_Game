#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "function.h"

#define Score           "\033[6;36m"
#define len_Question    "\033[5;36m"
#define Question        "\033[1;34m"
#define Correct         "\033[7;32m"
#define Wrong           "\033[7;31m"
#define Cyane           "\033[1;36m"
#define Resert          "\033[0m"


struct Quiz_Game
{
    char question[5][100];
    char true_answer;
};



char letter ()
{
    char ch;
    while ((ch=getch())!='\n')
    {
        switch (ch)
        {
            case 'a': 
            case 'b': 
            case 'c': 
            case 'd': 
            case 'q': 
                return (ch-32) ;
                break;
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'Q':
                return (ch);
            break;
            default :
                printf("Enter a valid choice (A, B, C, D, or Q):\n");
                break;
        }
    }
}
int choosen_number(int arrloop) {
    static int arrchoosen[100];
    int record, is_duplicate, i;
    if (arrloop>=50)
    {
        printf ("this is the final Question \n");
        exit(EXIT_SUCCESS);     
    }


    do {
        record = rand() % 99;
        is_duplicate = 0;

        
        for (i = 0; i < arrloop; i++) {
            if (arrchoosen[i] == record) 
            {
                is_duplicate = 1; 
                break;
            }
        }
    } while (is_duplicate);

    arrchoosen[arrloop] = record; 
    return record;
}
void open_file (FILE ** file,const char *name,const char *mode)
{
     if ((*file=fopen (name,mode))==NULL)
    {
        perror ("can't open this file \n");
        exit (EXIT_FAILURE);
    }
    
}
void display_socre(int score,int show_question)
{
    sleep(1);
    system ("clear");
    printf (Score"\t\t\t Score = %d\t\t",score);
    printf (Resert);
    printf (len_Question"Question = %d\n",show_question);
    printf (Resert);

}





int main()
{
    struct Quiz_Game questions;
    int i,record,offset;
    char choose;
    int score=0,show_qeustion=0;
    
    FILE *file_write;
    
    
    srand (time(NULL));

    open_file(&file_write,"question.bin","rb");


    while(1)
    {
       display_socre(score,show_qeustion);
                    

        record =choosen_number(show_qeustion);
        offset=(record-1)*sizeof(questions);


        if (!fseek(file_write,offset,0))
        {
            fread(&questions,sizeof(questions),1,file_write);
            printf(Question"\t%s\n",questions.question[0]);
            printf (Resert);

            for (i=1;i<5;i++)
                printf ("%s\n",questions.question[i]);
        }


        printf (Cyane"Choose \n"Resert);
        choose = letter();


        if (choose == questions.true_answer)
        {
            printf (Correct"Correct\n"Resert);
            score++;
        }
        else if  (choose == 'q' || choose == 'Q')
        {
            printf ("Good Game\n");
            exit(EXIT_SUCCESS);
        }
        else 
        {
            printf (Wrong"worng \n"Resert);
            printf (Correct"The corrcet answer is %c \n\n",questions.true_answer);
            printf (Resert);
            
            sleep(3);
            system("clear");
        }
        show_qeustion++; 

    }
    
    
    fclose(file_write);
    
    return 0;


}

