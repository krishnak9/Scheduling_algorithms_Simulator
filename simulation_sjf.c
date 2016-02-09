//sjf scheduling algorithm using process input from a text file .
//coded by ::::>>> krishna kumar
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//bash colors to display Gantt chart
#define RE     "\x1b[31m"
#define GR   "\x1b[32m"
#define YE  "\x1b[33m"
#define BL    "\x1b[34m"
#define MA "\x1b[35m"
#define CY    "\x1b[36m"
#define RESET   "\x1b[0m"

struct node{
      char process[3];
      int arrt;
      float bt;
      struct node*link;
 }*front=NULL;
struct gantt{
         char p[3];
         int at;
         float bt;
         float time;  
         struct gantt*link;
};

void insert(char pname[],int at,float bt){
          struct node*tmp,*p;
          tmp = (struct node *)malloc(sizeof(struct node));
          if(tmp==NULL){
              printf("Memory not available");
              return;
              }
          strcpy(tmp->process,pname);
          tmp->arrt=at;
          tmp->bt=bt;
          
          if(isEmpty() || at < front->arrt){
             tmp->link=front;
             front=tmp;
            }
          else{
            p = front;
            while(p->link!=NULL && p->link->arrt <= at)
                  p = p->link;

            tmp->link=p->link;
            p->link=tmp;
            }
}

struct node del(){
        struct node *tmp;
        struct node rvalue;
        if( isEmpty() ){
           printf("QUEUE UNDERFLOW\n");
           exit(1);
          }
        else{
          tmp = front;
          strcpy(rvalue.process,tmp->process);
          rvalue.arrt=tmp->arrt;
          rvalue.bt=tmp->bt;
          rvalue.link=NULL;
          front=front->link;
          free(tmp);
         }
       return rvalue;
}   
int isEmpty(){
      if(front == NULL )
         return 1;
      else
         return 0;
 }
//swap function used in modified bubble-sort to implement sjf
void swap(struct gantt*a,struct gantt*b){
           int t2;
           float t3;
           char t1[3];
           strcpy(t1,a->p);
           t2=a->at;
           t3=a->bt;
           strcpy(a->p,b->p);
           a->at=b->at;
           a->bt=b->bt;
           strcpy(b->p,t1);
           b->at=t2;
           b->bt=t3;
}

int main(){
       FILE *fp;
       char filename[100];
       struct gantt*start=NULL,*point,*tmp;
       printf("enter name of file\n");
       scanf("%s",filename);
       fp = fopen(filename,"r");
       int at,count=0;
        
       char p[3];
       float bt,tt,wt,wto;
       struct node process;
       if(fp == NULL){ 
           printf("File doesn't Exist\n");
           exit(1);
           }
       while(fscanf(fp, "%s %d %f",p,&at,&bt)!=EOF){
              insert(p,at,bt);
              }
       fclose(fp);
       float time = 0;
       printf("Process\t Arrival Time\t Burst Time \t Turnaround Time\t Waiting Time\t Completion Time\t\n");
       while(isEmpty()!=1){
             process = del();
             time = time + process.bt;
             tmp = (struct gantt*)malloc(sizeof(struct gantt));
                strcpy(tmp->p,process.process);
                tmp->at = process.arrt;
                tmp->bt = process.bt;
                tmp->link = NULL;
                tmp->time=time;
             if(start==NULL){
                  start = tmp;
                  point = start;
                 }
             else{
                point->link=tmp;
                point= point->link;
               }
         
             }
//This is to implement sjf algorithm to the input process queue :>
       struct gantt*w,*q;
       point = start;
       //a1 is currently running time
       int a1 = 0;
       while(point->link!=NULL){
              w = point;
              q = point->link;
              while(q!=NULL){
                   if(w->bt > q->bt && q->at<=a1){
                        swap(w,q);
                        
                        }
                      q=q->link;
                     }
              point = point->link;
             a1=a1+ w->bt;
             w->time=a1;
             }
//completion time for last process 
       point->time=a1+point->bt;    
       point = start;
       wto = 0;
       count=0;
       time=0;
//calculating completion time,turnaround-time,waiting-time,wto is used for calculating total average time at last
       while(point!=NULL){
            printf("%s\t\t %d\t\t %.1f\t\t",point->p,point->at,point->bt);
            time = time+point->bt;
            tt = time-point->at;
            wt= tt-point->bt;
            wto = wto + wt;
            printf("%.1f\t\t %.1f\t\t %.1f\t\t\n",tt,wt,time);
            count++;
            point=point->link;
            }
//printing Gantt chart
         int col=0,r;
       printf("Average waiting time:%.1f\n",(float)(wto/count));
         point = start;
         printf("GANTT CHART\n");
         printf("------------------------------------------------------------------------------------\n");
         while(point!=NULL){
               printf("%s",point->p);
                r = point->bt;
               if(col==0){
                while(r--){
                printf( CY "||" RESET);
                }
               }
               if(col==1){
                while(r--){
                printf( RE "||" RESET);
                  }
                }
              if(col==2){
                while(r--){
                printf( GR "||" RESET);
                }
               }
              if(col==3){
                while(r--){
                printf( MA "||" RESET);
                }
              }
              if(col==4){
              while(r--){
                printf( YE "||" RESET);
                }
              }
              col = (col+1)%5;

               point=point->link;
               }
         printf("\n");
         printf("------------------------------------------------------------------------------------\n");
         point=start;
          while(point!=NULL){
               r = point->bt;
               while(r--){
                  printf("  ");
                  }
               printf("%.1f",point->time);
               point=point->link;
               }

         printf("\n");
               
       
return 0;
}
