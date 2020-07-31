#include <iostream>
#include <malloc.h>
#include <string>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include<io.h>  // To make directories
#include <bits/stdc++.h>  // To store a complete text file in a string
#include<conio.h>

int filesCount=0;

void openCount()
{
    ifstream myfile ("filesCount.txt");
    if (myfile)
    {
        myfile>>filesCount;
        myfile.close();
    }
    else
    {
        ofstream enter;
        enter.open("filesCount.txt");
        enter<<filesCount;
        enter.close();
        filesCount=0;
    }
}
void updateCount()
{
    ofstream myfile;
    myfile.open("filesCount.txt");
    myfile<<filesCount;
    myfile.close();
}
//****************************************************
///////////////////////////////////////////////////////////////////////////////////////

void StringToHash(string data,string docName, hash_table_t *table)
{
    /*string data,docName;
    strcpy(&data[0],dataa);
    strcpy(&docName[0],docNamee);*/
    string word,wTemp;
    stringstream iss(data),issTemp(data);
    int p=0;
    int totalWords=0;
    //hash_table_t *table;
    //table=create_hash_table(20);

    while(issTemp >> wTemp)
    {
       totalWords++;
    }

    while (iss >> word)
    {
        add_string(table,&word[0]);

        list_t *item;
        item=lookup_string(table,&word[0]);

        document *x,*orig;
        x=new document;
        x=item->docs;

        for(x ;   ; x= x->next )
        {
            if(item->docs == NULL)
            {
                document *d;
                d=new document;
                d->docName=(char*)malloc(sizeof(char)* strlen(&docName[0]));
                strcpy(d->docName,&docName[0]);
                d->termFreq++;
                d->termRatio=d->termRatio+((float)1/totalWords);

                item->docs=d;
                item->docFreq++;

                break;
            }
            else if(strcmp(x->docName,&docName[0]) == 0  ) // equal = document entry already available
            {
                x->termFreq=x->termFreq+1;
                x->termRatio=x->termRatio+((float)1/totalWords);

                break;
            }
            if(x->next==NULL)
            {
                document *d;
                d=new document;

                d->docName=(char*)malloc(sizeof(char)* strlen(&docName[0]));
                strcpy(d->docName,&docName[0]);

                d->termFreq=1;
                d->termRatio=d->termRatio+((float)1/totalWords);

                x->next=new document;
                x->next=d;

                item->docFreq++;
                break;
            }
        }
        p++;
        //cout<<"P is**************************************:"<<p<<endl;
    }
}
///////////////////////////////////////////////////////////////////////////////////////

void HashToFile(hash_table_t *table)
{
    ofstream file;
    file.open("HashKeys.txt");
    file.close();
    file.open("HashData.txt");
    file.close();

    for(int i=0;i<table->size;i++)
    {
        list_t *x;

        for(x=table->table[i] ; x!=NULL ; x=x->next)
        {
    /*for(int i=0;i<table->size;i++)
    {
        list_t *listt=table->table[i];

        for(list_t *x=listt ; x!=NULL ; x=x->next)
        {*/
            int AlreadyPresent=0;

            ifstream myFile,read;
            myFile.open("HashKeys.txt");
            read.open("HashData.txt");

            string abc;
            abc.assign( (std::istreambuf_iterator<char>(read) ), (std::istreambuf_iterator<char>()    ) );
            //https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
            //cout<<"The data of the datafile:\n"<<abc<<endl;
            read.close();

            ofstream temp;
            temp.open("temp.txt");
            temp<<abc;
            temp.close();

            read.open("temp.txt");

            ofstream myData;
            myData.open("HashData.txt");

            for(string key; getline(myFile,key); )
            {
                string data;
                getline(read,data);
                //cout<<"Key: "<<key<<endl;

                if(strcmp(&key[0], x->str)==0 )
                {
                    //cout<<"ADDED existing"<<endl;
                    myData<<data;
                    document *d =x->docs;

                    while(d != NULL)
                    {
                        myData<<"+"<< d->docName <<" ";
                        myData<<"-"<<(float)d->termRatio<<" ";

                        d=d->next;
                    }
                    myData<<endl;

                    AlreadyPresent=1;
                }
                else
                {
                    //cout<<"Not compare"<<endl;
                    myData << data <<endl;
                }
            }

            if(AlreadyPresent == 0)
            {
                //cout<<"added new"<<endl;
                ofstream WriteKey("HashKeys.txt",  ios::out | ios::app);
                WriteKey<<x->str<<endl;

                document *d;
                d=x->docs;
                while(d!= NULL)
                {
                    myData<<"+"<< d->docName <<" ";
                    myData<<"-"<<(float)d->termRatio<<" ";
                    d=d->next;
                }

                myData<<endl;

                WriteKey.close();

            }
            AlreadyPresent=0;

            myFile.close();
            myData.close();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////


void FileToHash(hash_table_t *table)
{
    ifstream Keys,Data;
    Keys.open("HashKeys.txt");
    Data.open("HashData.txt");

    string key;
    string data;

    while(getline(Keys,key) )
    {
        getline(Data,data);
        add_string(table,&key[0]);

        list_t *item;
        item=lookup_string(table,&key[0]);

        document *x;
        item->docs=new document;
        x=item->docs;

        int i=0;
        //cout<<"KEY IS:....................................."<<&key[0]<<endl;

        for( x=item->docs ;  ; x= x->next )
        {
                   for(  ; i<=strlen(&data[0]); i++)
                   {
                       //cout<<i <<"  is: "<<data[i]<<endl;
                       if(data[i]=='+')
                       {
                           int countt=1;
                          while(data[i+countt+1] != ' ')
                           {
                               countt++;
                           }
                           string temp;
                           temp.resize(countt);
                           for(int j=0;j<countt;j++)
                           {
                               temp[j]=data[i+1+j];
                           }

                            x->docName=(char*)malloc(sizeof(char)* countt);
                            strcpy(x->docName,&temp[0]);
                            //cout<<"Doc name:.........."<<x->docName<<endl;
                            item->docFreq++;

                            i=i+countt;
                       }

                       if(data[i]=='-')
                       {
                           int countt=1;
                           while(data[i+countt+1] != ' ')
                           {
                               countt++;
                           }

                           string temp;
                           temp.resize(countt);
                           for(int j=0;j<countt;j++)
                           {
                               temp[j]=data[i+1+j];
                           }
                            float p;
                            stringstream geek(temp);
                            geek >> p;
                            x->termRatio= p;
                            //cout<<"Term Freq :........."<<x->termFreq<<endl;

                            i=i+countt;
                       }

                       if(data[i+1]=='+')
                       {
                            i++;
                            x->next=new document;
                            break;
                       }

                   }

                  // cout<<"Strlen : "<<strlen(&data[0])<<" and i= "<<i<<endl;
                   if(i>strlen(&data[0]))
                   {
                       break;
                   }

        }
    }
}
