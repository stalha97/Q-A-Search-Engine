//********************************************************************************************************
//***************PART 1 : INFORMATION CREATION : ENTERING QUESTIONS AND ANSWERS : FILE HANDLING***********
//********************************************************************************************************
//****************************************************
void EnterInfo(hash_table_t *table)
{
    string question,answer;
    cin.clear();    cin.ignore();

    cout<<"Enter a question: "<<endl;
    getline(cin,question);
    cout<<endl;

    cin.clear();

    cout<<"Enter the answer for it: "<<endl;
    getline(cin,answer);
    cout<<endl;

    cin.clear();
    //*************************************
    //question=TransformString(question);
    filesCount = filesCount+1;
    char temp[30];
    ofstream myfile;

    mkdir("Questions");
    mkdir("Answers");

    sprintf(temp,"Questions/Q%d.txt",filesCount);
    myfile.open(temp);
    myfile<<question;
    myfile.close();

    sprintf(temp,"Answers/A%d.txt",filesCount);
    myfile.open(temp);
    myfile<<answer;
    myfile.close();

    question=TransformString(&question[0]);

    sprintf(temp,"%d",filesCount);
    StringToHash(&question[0],&temp[0],table);
    HashToFile(table);
    updateCount();
    //printHash(table);

}
///////////////////////////////////////////////////////////////////////////////////////

