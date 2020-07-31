void SearchQuestion(hash_table_t *table)
{
    cin.clear();    cin.ignore();

    string question,word,wTemp;

    cout<<"Enter the Question you want to search for: \n";
    getline(cin,question);
    cin.clear();

    question=TransformString(&question[0]);

    stringstream iss(question),issTemp(question);
   //*************************************************************** User Query converted to Hash Table
    hash_table_t *qTable;
    qTable=create_hash_table(50);
    StringToHash(question,"Question",qTable);
   //***************************************************************
    int TotalWords=0;
    while(issTemp>>wTemp)
    {
        TotalWords++;
    }
   //***************************************************************

    string done[TotalWords];  //Keeps track of The words that has been already Extracted
    string present[2*TotalWords]; // Documents which include words from the USER QUERY
    int countPresent[2*TotalWords]; //Count of  different words=> appeared in document=>from present[2*TotalWords ARRAY];
    for(int i=0;i<2*TotalWords;i++)
    {
        countPresent[i]=1;
    }
    int p=0; // As an index for entering data to "present" ARRAY
    int p2=0; // As an index for "done" array
   //***************************************************************
    while( iss >> word)
    {
           //Check if there is An Entry for this Word ALREADY
           //***************************************************************
                int flag=0;
                for(int i=0;i<TotalWords;i++)
                {
                    if(strcmp(&word[0],&done[i][0])==0)
                    {
                        flag=1;
                        break;
                    }
                }
                    if(flag==1)
                    {
                        continue;
                    }
            //***************************************************************
            list_t * item,*qItem;
            qItem=lookup_string(qTable,&word[0]);
            item=lookup_string(table,&word[0]);

            if(item==NULL) // NULL => This word does not exist in DATABASE
            {
                continue;
            }

            string docNames[item->docFreq];
            float termRatio[item->docFreq];
            float RatioDiff[item->docFreq];

            document *x;
            x=item->docs;

       //CALCULATES TermFrequency-DIFFERENCE => Between "USER QUERY" AND "DOCUMENT"
       //***************************************************************
            for(int i=0 ;  x!=NULL ; x= x->next)
            {
                docNames[i].resize(strlen(x->docName));
                strcpy(&docNames[i][0],x->docName);
                termRatio[i]=(float)x->termRatio;

                RatioDiff[i]= (qItem->docs->termRatio) - termRatio[i];
                if(RatioDiff[i]<0)
                {
                    RatioDiff[i]=(-1)*RatioDiff[i];
                }
                i++;
                if(x->next==NULL)
                {
                    break;
                }
            }

       //Sort The difference ARRAY in ASCENDING ORDER
       //***************************************************************
            for(int j=0; j<item->docFreq ; j++)
            {
                for(int i=0;i<item->docFreq-1 ; i++)
                {
                    if(RatioDiff[i]>RatioDiff[i+1])
                    {
                        swap(RatioDiff[i] , RatioDiff[i+1]);
                        docNames[i].swap(docNames[i+1]);
                    }

                }
            }


       //IF ENTRY ALREADY EXISTS JUST INCREASE THE COUNT FOR THAT
       //***************************************************************
            int check1=0,check2=0;
            for(int k=0;k<p;k++)
            {
                if(strcmp(&docNames[0][0],&present[k][0])==0)
                {
                    countPresent[k]+=1;
                    check1=1;
                }
                if(strcmp(&docNames[1][0],&present[k][0])==0 && item->docFreq>1)
                {
                    countPresent[k]+=1;
                    check2=1;
                }
            }
       //IF ENTRY DOESNT EXIST THEN MAKE A NEW ENTRY AT NEW INDEX  OF P++
       //***************************************************************
            if(check1==0)
            {
                present[p].resize(strlen(&docNames[0][0]));
                strcpy(&present[p][0],&docNames[0][0]);
                p++;

            }
            if(check2==0 && item->docFreq>1)
            {
                present[p].resize(strlen(&docNames[1][0]));
                strcpy(&present[p][0],&docNames[1][0]);
                p++;
            }
       // Update the Array for DONE words by ADDING THIS NEW WORD
       //***************************************************************
            done[p2].resize(strlen(&word[0]));
            strcpy(&done[p2][0],&word[0]);
            p2++;

        }// END OF WHILE  LOOP

       // Sort the Documents which includes words from Query
       // Descending Order
       // Documents with More words from Query Gets to first position
       //***************************************************************
        for(int j=0; j<p ; j++)
        {
            for(int i=0;i<p-1 ; i++)
            {
                if(countPresent[j]<countPresent[i+1])
                {
                    swap(countPresent[i] , countPresent[i+1]);
                    present[i].swap(present[i+1]);
                }

            }
        }

    /*cout<<"This is present in these docs:"<<endl;
    for(int i=0;i<p;i++)
    {
            cout<<"Doc :"<<present[i]<<endl;
            cout<<"Count: "<<countPresent[i]<<endl<<endl;
    }*/

    int Qfound=0; // Tracks the number of Questions Available to show to User

   // Displays the Questions found according to the User Query
   //***************************************************************
    cout<<"\nChoose the most relevant question among the following: "<<endl;
    for(int i=0;i<p;i++)
    {
        if(i>4){break;}
        Qfound++;

        string temp="Questions/Q"+present[i]+".txt";

        ifstream read(temp.c_str());

        string abc;
        abc.assign( (std::istreambuf_iterator<char>(read) ), (std::istreambuf_iterator<char>()    ) );
        //https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
        cout<<"Question "<<i+1<<" :"<<abc<<endl;
        read.close();
    }
    cout<<endl;

   // User selects the Question from list OR Exit if no Right Match
   //***************************************************************
    int choose=-1;

    cout<<"Choose your question OR Write Any OTHER NUMBER if no suitable questions: "<<endl;
    cin>>choose;
    cout<<endl;

   // Displays the Final Question to User and its Answer available in the DataBase
   //***************************************************************
    if(choose<=Qfound && choose>=1)
    {

        string temp="Answers/A"+present[choose-1]+".txt";
        ifstream read(temp.c_str());

        string abc;
        abc.assign( (std::istreambuf_iterator<char>(read) ), (std::istreambuf_iterator<char>()    ) );
        //https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
        cout<<"Answer "<<choose<<" :"<<abc<<endl;
        read.close();
    }
    else
    {
        cout<<"Sorry , your question not found in database"<<endl;
    }
    cout<<endl;


   //   THE ENDDDDDDDD
   //***************************************************************
    cout<<"Press any key to Exit";
    _getch();
    system("CLS");
}

