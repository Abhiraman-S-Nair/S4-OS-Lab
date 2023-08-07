#include<stdio.h>
#include<stdlib.h>
int n, i, j, op, check, front=-1, rear=-1, queue[100];
struct process{
    int AT,WT,TAT,BT;
}a[10];

void swap(int *b,int *c){
    int temp=*c;
    *c=*b;
    *b=temp;
}
void fcfs()
{
    int burst=0, CT=0;
    float avg_WT=0.00, avg_TT=0.00, total_WT=0.00, total_TAT=0.00;
    printf("Enter no. of processes: ");
    scanf("%d",&n);
    printf("Enter Arrival time & Burst time of \n");
    for(i=0;i<n;i++)
    {
        printf("process %d: ", i+1);
        scanf("%d %d", &a[i].AT, &a[i].BT);
    }
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i=0;i<n;i++){
        if(i==0)
            a[i].WT=a[i].AT;
        else
            a[i].WT=burst-a[i].AT;
        burst+=a[i].BT;
        CT+=a[i].BT;
        a[i].TAT=CT-a[i].AT;
        total_WT+=a[i].WT;
        total_TAT+=a[i].TAT;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1,a[i].AT,a[i].BT,a[i].WT,a[i].TAT);
    }
    avg_WT=total_WT/n;
    avg_TT=total_TAT/n;
    printf("\nAverage Waiting Time: %.2f", avg_WT);
    printf("\nAverage Turnaround Time: %.2f\n", avg_TT);
}
void sjf_pre() {
    int count=0, short_P, temp[10];
    float avg_WT=0.00, avg_TT=0.00, total_WT=0.00, total_TAT=0.00;
    printf("Enter no. of processes: ");
    scanf("%d",&n);
    printf("Enter Arrival time & Burst time of \n");
    for(i=0;i<n;i++){
        printf("process %d: ", i+1);
        scanf("%d %d", &a[i].AT, &a[i].BT);
        temp[i]=a[i].BT;
    }
    a[9].BT=10000;
    for(j=0;count!=n;j++){
        short_P=9;
        for(i=0;i<n;i++){
            if(a[i].BT<a[short_P].BT && (a[i].AT<=j && a[i].BT>0))
                short_P=i;
        }
        a[short_P].BT=a[short_P].BT-1;
        if(a[short_P].BT==0){
            count++;
            a[short_P].WT=j+1-a[short_P].AT-temp[short_P];
            a[short_P].TAT=j+1-a[short_P].AT;
            total_WT+=a[short_P].WT;
            total_TAT+=a[short_P].TAT;
        }
    }
    avg_WT=total_WT/n;
    avg_TT=total_TAT/n;
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i=0;i<n;i++){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1,a[i].AT,a[i].BT,a[i].WT,a[i].TAT);
    }
    printf("Average WT = %.2f \tAverage TAT = %.2f\n",avg_WT, avg_TT);
}

void sjf_non_pre() {
    int check=0, CT=0, min;
    float avg_WT=0.00, avg_TT=0.00, total_WT=0.00, total_TAT=0.00;
    printf("Enter no. of processes: ");
    scanf("%d",&n);
    printf("Enter Arrival time & Burst time of \n");
    for(i=0;i<n;i++){
        printf("process %d: ", i+1);
        scanf("%d %d", &a[i].AT, &a[i].BT);
        if(i==0)
            check=a[i].AT;
        if(check!=a[i].AT )
            check=1;
    }
    if(check!=0){
        for(i=0;i<n;i++){
            for(j=0;j<n-i-1;j++){
                if(a[j].AT>a[j+1].AT){
                    swap(&a[j].AT, &a[j+1].AT);
                    swap(&a[j].BT, &a[j+1].BT);
                }}}
        a[0].WT=a[0].AT;
        a[0].TAT=a[0].BT-a[0].AT;
        CT=a[0].TAT;
        total_WT+=a[0].WT;
        total_TAT+=a[0].TAT;
        for(i=1;i<n;i++){
            min=a[i].BT;
            for(j=i+1;j<n;j++){
                if(min>a[j].BT && a[j].AT<=CT){
                    min=a[j].BT;
                    swap(&a[i].AT, &a[j].AT);
                    swap(&a[i].BT, &a[j].BT);
                }
            }
            a[i].WT=CT-a[i].AT;
            total_WT+=a[i].WT;
            CT+=a[i].BT;
            a[i].TAT=CT-a[i].AT;
            total_TAT+=a[i].TAT;
        }
    }
    else{
        for( i=0;i<n;i++){
            min=a[i].BT;
            for(j=i+1;j<n;j++){
                if(min>a[j].BT && a[j].AT<=CT){
                    min=a[j].BT;
                    swap(&a[i].AT, &a[j].AT);
                    swap(&a[i].BT, &a[j].BT);
                }}
            a[i].WT=CT-a[i].AT;
            CT+=a[i].BT;
            a[i].TAT=CT-a[i].AT;
            total_WT+=a[i].WT;
            total_TAT+=a[i].TAT;
        }
    }
    avg_WT=total_WT/n;
    avg_TT=total_TAT/n;
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i=0;i<n;i++)
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1,a[i].AT,a[i].BT,a[i].WT,a[i].TAT);
    printf("Average WT = %.2f \tAverage TAT = %.2f\n",avg_WT, avg_TT);
}
struct prio{
    int WT,AT,BT,TAT,PR;
}b[10];
void Prio_pre(){
    int count=0, short_p, temp[10];
    float avg_WT=0.00, avg_TT=0.00, total_WT=0.00, total_TAT=0.00;
    printf("Enter no. of processes: ");
    scanf("%d",&n);
    printf("Enter Arrival time, Burst time & Priority of \n");
    for(i=0;i<n;i++){
        printf("process %d: ", i+1);
        scanf("%d %d %d", &b[i].AT, &b[i].BT, &b[i].PR);
        temp[i]=b[i].BT;
    }
    b[9].PR=10000;
    for(j=0;count!=n;j++){
        short_p=9;
        for(i=0;i<n;i++){
            if(b[short_p].PR>b[i].PR && b[i].AT<=j && b[i].BT>0)
                short_p=i;
        }
        b[short_p].BT=b[short_p].BT-1;
        if(b[short_p].BT==0){
            count++;
            b[short_p].WT=j+1-b[short_p].AT-temp[short_p];
            b[short_p].TAT=j+1-b[short_p].AT;
            total_WT+=b[short_p].WT;
            total_TAT+=b[short_p].TAT;
        }
    }
    avg_WT=total_WT/n;
    avg_TT=total_TAT/n;
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i=0;i<n;i++)
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1,a[i].AT,a[i].BT,a[i].WT,a[i].TAT);
    printf("Average WT = %.2f \tAverage TAT = %.2f\n",avg_WT, avg_TT);
}

void Prio_nonpre(){
    int check=0, CT=0, min;
    float avg_WT=0.00, avg_TT=0.00, total_WT=0.00, total_TAT=0.00;
    printf("Enter no. of processes: ");
    scanf("%d",&n);
    printf("Enter Arrival time, Burst time & Priority of \n");
    for(i=0;i<n;i++){
        printf("process %d: ", i+1);
        scanf("%d %d %d", &b[i].AT, &b[i].BT, &b[i].PR);
        if(i==0)
            check=b[i].AT;
        if(check!=b[i].AT )
            check=1;
    }
    if(check!=0){
        for(i=0;i<n;i++){
            for(j=0;j<n-i-1;j++){
                if(b[j].AT>b[j+1].AT){
                    swap(&b[j].AT, &b[j+1].AT);
                    swap(&b[j].BT, &b[j+1].BT);
                    swap(&b[j].PR, &b[j+1].PR);
                }}}
        b[0].WT=b[0].AT;
        b[0].TAT=b[0].BT-b[0].AT;
        CT=b[0].TAT;
        total_WT+=b[0].WT;
        total_TAT+=b[0].TAT;
        for(i=1;i<n;i++){
            min=b[i].PR;
            for(j=i+1;j<n;j++){
                if(min>b[j].PR && b[j].AT<=CT){
                    min=b[j].PR;
                    swap(&b[i].AT, &b[j].AT);
                    swap(&b[i].BT, &b[j].BT);
                    swap(&b[j].PR, &b[j+1].PR);
                }
            }
            b[i].WT=CT-b[i].AT;
            total_WT+=b[i].WT;
            CT+=b[i].BT;
            b[i].TAT=CT-b[i].AT;
            total_TAT+=b[i].TAT;
        }
    }
    else{
        for(i=0;i<n;i++){
            min=b[i].PR;
            for(j=i+1;j<n;j++){
                if(min>b[j].PR && b[j].AT<=CT){
                    min=b[j].PR;
                    swap(&b[i].AT, &b[j].AT);
                    swap(&b[i].BT, &b[j].BT);
                    swap(&b[j].PR, &b[j+1].PR);
                }}
            b[i].WT=CT-b[i].AT;
            CT+=b[i].BT;
            b[i].TAT=CT-b[i].AT;
            total_WT+=b[i].WT;
            total_TAT+=b[i].TAT;
        }
    }
    avg_WT=total_WT/n;
    avg_TT=total_TAT/n;
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i=0;i<n;i++)
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1,a[i].AT,a[i].BT,a[i].WT,a[i].TAT);
    printf("Average WT = %.2f \tAverage TAT = %.2f\n",avg_WT, avg_TT);
}
void insert(int x){
    if(front==-1)
        front=0;
    rear++;
    queue[rear]=x;
}
int delete(){
    int x=queue[front];
    front++;
    return x;
}
int rr() {
    int TQ, p, TIME=0, temp[10], exist[10]={0};
    float avg_WT=0.00, avg_TT=0.00, total_WT=0.00, total_TAT=0.00;
    printf("Enter no. of processes: ");
    scanf("%d",&n);
    printf("Enter Arrival time & Burst time of \n");
    for(i=0;i<n;i++){
        printf("process %d: ", i+1);
        scanf("%d %d", &a[i].AT, &a[i].BT);
        temp[i]=a[i].BT;
    }
    printf("Enter the time quantum: ");
    scanf("%d", &TQ);
    insert(0);
    exist[0]=1;
    while(front<=rear){
        p=delete();
        if(a[p].BT>=TQ){
            a[p].BT-=TQ;
            TIME+=TQ;
        }
        else{
            TIME+=a[p].BT;
            a[p].BT=0;
        }
        for(i=0;i<n;i++){
            if(exist[i]==0 && a[i].AT<=TIME){
                insert(i);
                exist[i]=1;
            }}
        if(a[p].BT==0){
            a[p].TAT=TIME-a[p].AT;
            a[p].WT=a[p].TAT-temp[p];
            total_TAT+=a[p].TAT;
            total_WT+=a[p].WT;
        }
        else
            insert(p);
    }
    avg_TT=total_TAT/n;
    avg_WT=total_WT/n;
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");;
    for(int i=0;i<n;i++)
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1,a[i].AT,a[i].BT,a[i].WT,a[i].TAT);
    printf("Average WT = %.2f \tAverage TAT = %.2f\n",avg_WT, avg_TT);
}
int main()
{
    int i=1;
    while(i!=0)
    {
        int cho;
        printf("1.FCFS\n2.Preemptive SJF\n3.Non Preemtive SJF\n4.Non Preemptive Priority Scheduling\n5. Preemptive Priority Scheduling\n6.Round Robing\n7.Exit\nEnter your choice:\n");
        scanf("%d",&cho);
        switch(cho)
        {
            case 1:
                fcfs();
                break;
            case 2:
                sjf_pre();
                break;
            case 3:
                sjf_non_pre();
                break;
            case 4:
                Prio_pre();
                break;
            case 5:
                Prio_nonpre();
                break;
            case 6:
                rr();
                break;
            case 7:
                printf("Exiting...");
                i=0;
                exit(0);
                break;
        }
    }
}
