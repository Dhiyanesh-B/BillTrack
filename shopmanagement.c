#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
struct Item
{
    char name[100];
    float price;
    int stock;
};
int main()
{
    struct Item items[100];
    int option,itemCount=0,i,d,x,r;
    FILE *file;
    first:
    itemCount=0;
    int font=8;
    printf("\t\t\t\t\t  WELCOME TO PSG STORES\n");
    printf("\t\t\t\t\tOpen billing\t-\t1\n\t\t\t\t\tStock Check\t-\t2\n\t\t\t\t\tStock updation\t-\t3\n\t\t\t\t\tAdd item\t-\t4\n\t\t\t\t\tDelete item\t-\t5\n\t\t\t\t\tSales view\t-\t6\n\t\t\t\t\tBill view\t-\t7\n\t\t\t\t\tExit\t\t-\t0");
    file=fopen("filez.txt","r");
    while(fscanf(file,"%s %f %d",items[itemCount].name,&items[itemCount].price,&items[itemCount].stock)!=EOF)
    {
        itemCount++;
    }
    fclose(file);
    for(i=0;i<itemCount;i++)
    {
        if(items[i].stock<=30)
        {
            printf("\n\nNotification:The item %s stock is only %d.\n",items[i].name,items[i].stock);
        }
    }
    re:
    printf("\nEnter your option:");
    scanf("%d",&option);
    switch(option)
    {
        case 0:
            goto end;
        case 1:
            bill();
            break;
        case 2:
            d=st_check();
            if(d==1)
            {
                system("cls");
            }
            break;
        case 3:
            st_update();
            system("cls");
            break;
        case 4:
            x=add_item();
            if(x==1)
            {
                system("cls");
            }
            break;
        case 5:
            del();
            system("cls");
            break;
        case 6:
            sf();
            system("cls");
            break;
        case 7:
            r=bill_view();
            if(r==1)
            {
                system("cls");
            }
            break;
        default:
            printf("Re-enter the number: ");
            goto re;
    }
    goto first;
    end:
    return 0;
}
int bill()
{
    system("cls");
    FILE *file;
    FILE *profit;
    FILE *bill;
    int m=1;
    while(1)
    {
        char itemToBuy[50];
        float totalCost=0,G=0;
        struct Item items[70];
        int itemCount=0,j=0,k,z=1,flag=0,i=0,e=0,num=1;
        float w[100],qu=0,q[100];
        float sum=0;
        char a[100][100],names[100];
        float b;
        int x=0,o=0;
        float totalprofit[100];
        int itemNot=0,ex=0;
        time_t t;
        file=fopen("filez.txt","r");
        if(file==NULL)
        {
            printf("Failed to open the file.\n");
            return 1;
        }
        printf("S.NO\t\tITEM\t          PRICE\n");
        while(fscanf(file,"%s %f %d",items[itemCount].name,&items[itemCount].price,&items[itemCount].stock)!=EOF)
        {
            printf("%d.\t%12s%15.0f\n",num,items[itemCount].name,items[itemCount].price);
            itemCount++;
            num++;
        }
        fclose(file);
        printf("Enter the item you want to buy (type 'done' to finish):\nEnter \"exit\" in name to exit\n\n");
        se:
        printf("Enter your name:");
        scanf("%s",names);
        if(strcmp(names,"exit")==0)
        {
            goto end;
        }
        for(i=0;i<itemCount;i++)
        {
            if(strcmp(names,items[i].name)==0)
            {
                goto se;
            }
        }
        while(1)
        {
            l1:
            printf("Enter the item:");
            scanf("%s",itemToBuy);
            if(strcmp(itemToBuy,"done")==0)
            {
                break;
            }
            for(e=0;e<itemCount;e++)
            {
                if(strcmp(itemToBuy,items[e].name)==0)
                {
                    tr:
                    o=1;
                    printf("Enter number of packets you want:");
                    scanf("%f",&qu);
                    totalCost=totalCost+(qu*items[e].price);
                    strcpy(a[j],itemToBuy);
                    w[j]=qu*items[e].price;
                    q[j]=qu;
                    if(items[e].stock<qu)
                    {
                        printf("ENTERED QUANTITY IS NOT AVALABLE, AVAILABLE STOCK IS %d\n",items[e].stock);
                        goto tr;
                    }
                    else
                    {
                        items[e].stock=items[e].stock-q[j];
                        j++;
                        break;
                    }
                }
            }
            if(e>=itemCount)
            {
                printf("ITEM IS NOT IN THE STORE TRY AGAIN...\n");
            }
        }
        if(o==0)
        {
            goto end;
        }
        G=totalCost*0.05;
        // Print the bill
        time(&t);
        printf("\n=================================== Bill =========================================\n");
        printf("Name:%s\t\t\t\t\t\t%s\n",names,ctime(&t));
        printf("Bill No.: %d\n",m);
        printf("S.No\t\tITEM\t\tQUANTITY\t ITEM PRICE\t\tPRICE\n");
        printf("-----------------------------------------------------------------------------------\n");
        for(i=0;i<itemCount;i++)
        {
            for(k=0;k<itemCount;k++)
            {
                if(strcmp(a[k],items[i].name)==0)
                {
                    printf("%d.\t%12s:\t\t%.2f\t\t%6.2f*%.2f\t\tRS.%.2f\n",z,a[k],q[k],items[i].price,q[k],w[k]);
                    z++;
                }
            }
        }
        printf("-----------------------------------------------------------------------------------\n");
        printf("Product sum cost: \t\t\t\t\t\t\tRS.%.2f\n",totalCost);
        printf("GST (5%%): \t\t\t\t\t\t\t\tRS.%.2f\n",G);
        printf("Total Cost: \t\t\t\t\t\t\t\tRS.%.2f\n",totalCost+G);
        printf("-----------------------------------------------------------------------------------\n");

        //printing bill in file
        bill=fopen("bill.txt","a");
        fprintf(bill,"\n=================================== Bill =========================================\n");
        fprintf(bill,"Name:%s\t\t\t\t\t\t%s\n",names,ctime(&t));
        fprintf(bill,"Bill No.: %d\n",m);
        fprintf(bill,"S.No\t\tITEM\t\tQUANTITY\t ITEM PRICE\t\tPRICE\n");
        fprintf(bill,"-----------------------------------------------------------------------------------\n");
        z=1;
        for(i=0;i<itemCount;i++)
        {
            for(k=0;k<itemCount;k++)
            {
                if(strcmp(a[k],items[i].name)==0)
                {
                    fprintf(bill,"%d.\t%12s:\t\t%.2f\t\t%6.2f*%.2f\t\tRS.%.2f\n",z,a[k],q[k],items[i].price,q[k],w[k]);
                    z++;
                }
            }
        }
        fprintf(bill,"-----------------------------------------------------------------------------------\n");
        fprintf(bill,"Product sum cost: \t\t\t\t\t\t\tRS.%.2f\n",totalCost);
        fprintf(bill,"GST (5%%): \t\t\t\t\t\t\t\tRS.%.2f\n",G);
        fprintf(bill,"Total Cost: \t\t\t\t\t\t\t\tRS.%.2f\n",totalCost+G);
        fprintf(bill,"-----------------------------------------------------------------------------------\n");
        fclose(bill);
        Beep(10000,500);
        //stock Management
        file=fopen("filez.txt","w");
        for(int j=0;j<itemCount;j++)
        {
            fprintf(file,"%s %.0f %d\n",items[j].name,items[j].price,items[j].stock);
        }
        fclose(file);
        profit=fopen("profit.txt","a");
        fprintf(profit,"%.2f\n",totalCost+G);
        fclose(profit);
        m++;
        printf("Press 1 for next bill\n");
        l2:
        scanf("%d",&ex);
        if(ex==1)
        {
            memset(a,'\0',sizeof(a));
            system("cls");
        }
        else
        {
            printf("Enter the number 1: ");
            goto l2;
        }
    }
    end:
    system("cls");
    return 0;
}
int st_check()
{
    system("cls");
    struct Item items[100];
    int itemCount=0,i,num=1,e;
    FILE *file;
    file=fopen("filez.txt","r");
        if(file==NULL)
        {
            printf("Failed to open the file.\n");
            return 1;
        }
        printf("S.NO\t\tITEM\t    STOCK AVALABLE\n");
        while(fscanf(file,"%s %f %d",items[itemCount].name,&items[itemCount].price,&items[itemCount].stock)!=EOF)
        {

            printf("%d.\t%12s%15.d\n",num,items[itemCount].name,items[itemCount].stock);
            itemCount++;
            num++;
        }
        fclose(file);
        for(i=0;i<itemCount;i++)
        {
            fprintf(file,"%s %f %d",items[i].name,&items[i].price,&items[i].stock);
        }
        printf("Enter 1 to exit\n");
        up:
        scanf("%d",&e);
        if(e==1)
        {
            return 1;
        }
        else
        {
            printf("Enter 1 to exit\n");
            goto up;
        }
}
int st_update()
{
    system("cls");
    struct Item items[100];
    int qu=0,itemCount=0,e,i;
    char pro[100];
    FILE *file;
    file=fopen("filez.txt","r");
    if(file==NULL)
    {
        printf("Failed to open the file.\n");
        return 1;
    }
    while(fscanf(file,"%s %f %d",items[itemCount].name,&items[itemCount].price,&items[itemCount].stock)!=EOF)
    {
        itemCount++;
    }
    fclose(file);
    while(1)
    {
        printf("Enter the item:");
        scanf("%s",pro);
        for(e=0;e<itemCount;e++)
        {
            if(strcmp(pro,items[e].name)==0)
            {
                printf("Enter the quantity:");
                scanf("%d",&qu);
                items[e].stock=qu;
            }
        }
        if(strcmp(pro,"done")==0)
        {
            break;
        }

    }
    file=fopen("filez.txt","w");
    for(i=0;i<itemCount;i++)
    {
        fprintf(file,"%s %.0f %d\n",items[i].name,items[i].price,items[i].stock);
    }
    fclose(file);
    return 0;
}
int add_item()
{
    system("cls");
    FILE *file;
    char item[100],sim[10];
    float rate;
    int stock;
    printf("To end adding type \"done\"\n");
    printf("Enter the name of the item to be added:");
    scanf("%s",item);
    if(strcmp(item,"done")==0)
    {
        goto end;
    }
    rst:
    printf("Enter the price of the item:");
    scanf("%f",&rate);
    gcvt(rate,5,sim);
    if(strcmp(sim,"done")==0)
    {
        goto end;
    }
    if(isdigit((int)rate)==0)
    {
        rate=0;
        goto rst;
    }
    stk:
    printf("Enter the stock of the item:");
    scanf("%d",&stock);
    gcvt(stock,5,sim);
    if(strcmp(sim,"done")==0)
    {
        goto end;
    }
    if(isdigit(stock)!=0)
    {
        goto stk;
    }
    file=fopen("filez.txt","a");
    fprintf(file,"%s %.0f %d",item,rate,stock);
    fclose(file);
    end:
    system("cls");
}
int del()
{
    system("cls");
    char ittodel[70];
    struct Item items[100];
    int itemCount=0,i=0,a=0;
    FILE *file;
    printf("To end adding type ""done""\n");
    file=fopen("filez.txt","r");
    while(fscanf(file,"%s %f %d",items[itemCount].name,&items[itemCount].price,&items[itemCount].stock)!=EOF)
        {
            itemCount++;
        }
    fclose(file);
    while(1)
    {
        int v=0;
        printf("Enter the item to be deleted:");
        scanf("%s",ittodel);
        if(strcmp(ittodel,"done")==0)
        {
            break;
        }
        file=fopen("filez.txt","w");
        for(i=0;i<itemCount;i++)
        {
            if(strcmp(ittodel,items[i].name)==0)
            {
                v=1;
                continue;
            }
            else
            {
                fprintf(file,"%s %.0f %d\n",items[i].name,items[i].price,items[i].stock);
            }
        }
        fclose(file);
        if(v==1)
        {
            printf("%s is deleted from the shop.\n",ittodel);
        }
        else
        {
            printf("Item not found\n");
        }
    }
    return 0;
}
int sf()
{
    system("cls");
    FILE *profit;
    float totalprofit[100];
    int x=0,e;
    float sum=0;
    profit=fopen("profit.txt","r");
    while((fscanf(profit,"%f\n",&totalprofit[x]))!=EOF)
    {
        sum=sum+totalprofit[x];
        x++;
    }
    printf("Total sales: %.2f\n",sum);
    fclose(profit);
    printf("\n\nEnter 1 to exit\n");
    scanf("%d",&e);
    if(e==1)
    {
        return 0;
    }
}
int bill_view()
{
    system("cls");
    int i=0,quit;
    char bill[1000][100];
    FILE *file=fopen("bill.txt","r");
    while(!feof(file))
    {
        printf("%s",fgets(&bill[i],100,file));
        i++;
    }
    printf("Enter 1 to exit\n");
    uq:
    scanf("%d",&quit);
    if(quit==1)
    {
        return 1;
    }
    else
    {
        printf("Re-enter the number\n");
        goto uq;
    }
}
