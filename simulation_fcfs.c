#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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
         printf("%s \t\t %d\t\t %.2f\t\t",process.process,process.arrt,process.bt);
              tt = time - process.arrt;
              wt = tt - process.bt;
              wto = wto + wt;
              count++;
              printf("%.2f \t\t %.2f \t\t %.2f\t\t\n",tt,wt,time);
             }
         printf("average waiting time: %.2f\n\n",(float)(wto/count));
         point = start;
         int col = 0,r;
         printf("GANTT CHART\n");
         printf("------------------------------------------------------------------------------------\n");
         while(point!=NULL){
               printf("%s",point->p);
               
              
            
               r = point->bt;
               while(r--){
                   printf("||");
                }
              
              printf("--");
              

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
