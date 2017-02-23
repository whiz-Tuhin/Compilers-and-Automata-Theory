#include<cstdio>
#include<cstdlib>
#include<string>

int id1=0;

typedef struct Token
{
    char lexname[30];
    int index;
}token;

typedef struct Node
{
    int id;
    char name[20];
    char type[10];
    int size;
    char scope;
    struct Node *next;
}node;

node *head=NULL;
node *h;

void create(int id1,char * name,char *type,int s,char sc)
{

     node *new=(node *)malloc(sizeof(node));

     new->id=id1;
     strcpy(new->name,name);
     strcpy(new->type,type);
     new->size=s;
     new->scope=sc;

     new->next=NULL;
     if(head==NULL)
     {
         head=new;
         h=head;
     }
     else
     {
         head->next=new;
         head=head->next;
     }
}

int search(char *a)
{
    node *ptr=h;
    while(ptr!=NULL)
    {
        if(strcmp(a,ptr->name)==0)
            return 1;
        ptr=ptr->next;
    }
    return 0;
}

void display()
{
    printf("ID\tNAME\tTYPE\tSIZE\tSCOPE\n");
    while(h!=NULL)
    {
        printf("%d\t%s\t%s\t%d\t%c\n",h->id,h->name,h->type,h->size,h->scope);
        h=h->next;
    }
}

void main()
{
    FILE *f1,*f2;
    int i,j,flag=0,tag=0,num,num1;
    long x;
    char name[100],name1[100],c[100],dtype[10],t,u,argu[20],h1[10],x1;
    char a[11][10]={"char","int","if","float","void","for","while","do","else","break","long"};
    printf("Input file: ");
    scanf("%s",name);
    f1=fopen(name,"r");
    if(f1==NULL)
    {
        printf("\n**ERROR**\n");
        exit(0);
    }
    printf("Output file: ");
    scanf("%s",name1);
    f2=fopen(name1,"w+");
    do
    {
        t=fgetc(f1);
        //remove header files
        if(tag==0)
            if(t=='#')
                while(t!='\n')
                    t=fgetc(f1);
        if(t=='{')
            tag++;
        if(t=='}')
            tag--;
        if(t=='\n')
        {
            fputc(t,f2);
            continue;
        }
        //literals removal
        else if(t==34)
        {
            t=fgetc(f1);
            while (t!=34)
                t=fgetc(f1);
            continue;
        }
        //comments
        else if(t=='/')
        {
            t=fgetc(f1);
            if(t=='/')
                while(t!='\n')
                    t=fgetc(f1);
            else if(t=='*')
            {
                do
                {
                    while(t!='*')
                        t=fgetc(f1);
                    t=fgetc(f1);
                }while(t!='/');
                continue;
            }
            else
            {
                x=ftell(f1);//for retract
                fseek(f1,x-1,SEEK_SET);
            }
        }
        //relational operator
        else if(t=='=')
        {
            i=0;
            c[i++]=t;
            t=fgetc(f1);
            if(t=='=')
            {
                c[i++]=t;
                c[i]='\0';
                fputc('<',f2);
                fputs(c,f2);
                fputc('>',f2);
                continue;
            }
            else
            {
                x=ftell(f1);//for retract
                fseek(f1,x-1,SEEK_SET);//retract
                c[i]='\0';
                fputc('<',f2);
                fputs(c,f2);
                fputc('>',f2);
                continue;
            }
        }
        else if(t=='<'||t=='>'||t=='!')
        {
            i=0;
            c[i++]=t;
            t=fgetc(f1);
            if(t=='=')
            {
                c[i++]=t;
                c[i]='\0';
                fputc('<',f2);
                fputs(c,f2);
                fputc('>',f2);
                continue;
            }
            else
            {
                x=ftell(f1);//for retract
                fseek(f1,x-1,SEEK_SET);//retract
                c[i]='\0';
                fputc('<',f2);
                fputs(c,f2);
                fputc('>',f2);
                continue;
            }
        }
        //arithmetic operator and special symbols
        else if(t=='+'||t=='-'||t=='*'||t==';'||t=='/'||t==39||t==','||t==')'||t=='('||t=='{'||t=='}')
        {
            fputc('<',f2);
            fputc(t,f2);
            fputc('>',f2);
            continue;
        }
        //number
        else if(isdigit(t))
        {
            i=1;
            strcpy(c,"\0");
            strcat(c,&t);
            t=fgetc(f1);
            while(isdigit(t))
            {
                c[i]=t;
                strcat(c,&t);
                t=fgetc(f1);
                i++;
            }
            c[i]='\0';
            x=ftell(f1);//for retract
            fseek(f1,x-1,SEEK_SET);
            fputc('<',f2);
            fputs("NUM",f2);
            fputc(',',f2);
            if(search(c)==0)
                create(++id1,c,"NUM",strlen(c)*sizeof(int),'n');
            for(j=0;j<strlen(c);j++)
                fputc(c[j],f2);
            fputc('>',f2);
            continue;
        }
        //identifiers
        else if(isalpha(t))
        {
            i=1;
            strcpy(c,"\0");
            strcat(c,&t);
            t=fgetc(f1);
            while(isalnum(t))
            {
                c[i]=t;
                strcat(c,&t);
                t=fgetc(f1);i++;
            }
            c[i]='\0';
            flag=0;
            x=ftell(f1);//for retract
            fseek(f1,x-1,SEEK_SET);//retract
            //array c has the complete identifier;
            for(i=0;i<11;i++)
                if(strcmp(a[i],c)==0)
                {
                    // c is a keyword
                    flag=1;
                    fputc('<',f2);
                    for(j=0;j<strlen(c);j++)
                        fputc(c[j],f2);
                    fputc('>',f2);
                    break;
                }
            if(strcmp(c,"int")==0)
                    strcpy(dtype,c);
            else if(strcmp(c,"char")==0)
                    strcpy(dtype,c);
            else if(strcmp(c,"float")==0)
                    strcpy(dtype,c);
            if(flag==0)
            {
                t=fgetc(f1);
                if(t==' ')
                    while(t==' ')
                        t=fgetc(f1);
                if(t=='(')
                    {
                        //c is a function
                        i=0;
                        fputc('<',f2);
                        fputs("FN",f2);
                        fputc(',',f2);
                        for(j=0;j<strlen(c);j++)
                             fputc(c[j],f2);
                        fputc('>',f2);
                        if(search(c)==0)
                            create(++id1,c,"FN",0,'g');
                        x=ftell(f1);//for retract
                        fseek(f1,x-1,SEEK_SET);//retract
                        continue;
                    }
                else if(t=='[')
                {
                    num=0;
                    flag=0;
                    i=0;
                    // the identifier is an array
                    do
                    {
                        t=fgetc(f1);h1[i++]=t;
                        if(t==']')
                            break;
                        if(isdigit(t))
                        {
                            num=num*10+(t-48);
                            flag=1;
                        }
                        else break;
                    h1[i]='\0';
                    create(++id1,h1,"NUM",strlen(h1)*sizeof(int),'g');
                    }while(t!=']');
                    //num has size of the array
                    t=fgetc(f1);
                    num1=1;
                    if(t=='[')
                    {
                        num1=0;flag=0;i=0;
                        do
                        {
                            t=fgetc(f1);
                            h1[i++]=t;
                            if(t==']')
                                break;
                            if(isdigit(t))
                            {
                                num1=num1*10+(t-48);
                                flag=1;
                            }
                                else break;
                                h1[i]='\0';
                                create(++id1,h1,"NUM",strlen(h1)*sizeof(int),'g');
                        }while(t!=']');
                    }
                    else
                    {
                        //retract
                        x=ftell(f1);
                        fseek(f1,x-1,SEEK_SET);//retract
                    }
                    if(flag==1)
                        printf("Size of array %s type %s is:%d\n",c,dtype,num*num1);
                }
                x=ftell(f1);//for retract
                fseek(f1,x-1,SEEK_SET);//retract
                if(tag>0)
                    x1='l';
                else
                    x1='g';
                 // c is an identifier
                if(search(c)==0)
                    create(++id1,c,dtype,strlen(c)*sizeof(char),x1);
                fputc('<',f2);
                fputs("id",f2);
                fputc(',',f2);
                for(j=0;j<strlen(c);j++)
                    fputc(c[j],f2);
                fputc('>',f2);
            }
            else
            {
                //among keyword check datatype
                if(strcmp(c,"int")==0)
                    strcpy(dtype,c);
                else if(strcmp(c,"char")==0)
                    strcpy(dtype,c);
                else if(strcmp(c,"long")==0)
                    strcpy(dtype,c);
            }
            continue;
        }
    }while(t!=EOF);
    display();
    fclose(f1);
    fclose(f2);
}
