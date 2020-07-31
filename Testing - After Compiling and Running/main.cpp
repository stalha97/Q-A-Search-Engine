#include <iostream>
#include <malloc.h>
#include <string>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include<io.h>  // To make directories
#include <bits/stdc++.h>  // To store a complete text file in a string
#include<conio.h>

#include "hash.h"
#include "String_Hash_FIle.h"
#include "TransformString.h"
#include "AddInfo.h"
#include "Searching.h"

using namespace std;

void listQstns()
{
    for(int i=1;i<=filesCount;i++)
    {
        char temp[50];
        sprintf(temp,"Questions/Q%d.txt",i);

        ifstream read(temp);

        string abc;
        abc.assign( (std::istreambuf_iterator<char>(read) ), (std::istreambuf_iterator<char>()    ) );
        //https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
        cout<<"Question "<<i<<" :"<<abc<<endl;
        read.close();
    }
}
int main()
{
    openCount();
    hash_table_t *table;
    table=create_hash_table(500);

    FileToHash(table);

    int choice=-1;
    do
    {
        listQstns();
        cout<<endl;
        cout<<"Here are the choices: "<<endl;
        cout<<"1. To Enter your Info"<<endl;
        cout<<"2. To Ask a Question"<<endl;
        cout<<"3. To End"<<endl<<"Your Choice: ";
        cin>>choice;
        cout<<endl<<endl;
        system("CLS");

        if(choice==1)
        {
            EnterInfo(table);
            system("CLS");
        }
        else if(choice==2)
        {
            SearchQuestion(table);
        }
        else if(choice==3)
        {
            break;
        }

    }while(1);

    return 0;
}

