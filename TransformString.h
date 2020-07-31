/* THIS FUNCTION WILL TRANSFORM A STRING FROM ITS COMPLEX FORM TO SIMPLE FORM
WHERE ITS EASY TO EXTRACT DATA AND USE THAT SIMPLIFIED TEXT FOR ANY OPERATION
*/

string TransformString(string old)
{
    string neww;
    neww.resize(strlen(&old[0]));

    for(int i=0; i<strlen(&old[0]) ; i++)
    {
        if      ( old[i]>=48 && old[i] <=57  ) { neww[i]=old[i]; /* ITS A DIGIT BETWEEN 0 - 9*/ }
        else if ( old[i]>=97 && old[i] <=122 ) { neww[i]=old[i]; /* ITS A SMALL LETTER ALPHABET */ }
        else if ( old[i]>=64 && old[i] <=90  ) /* ITS A CAPITAL LETTER ALPHABET */
        {
            neww[i]=old[i] +32;
        }
        else
        {
            neww[i]=' ';
        }
    }

    string arr[]={"a", "about", "above", "above", "across", "after", "afterwards", "again", "against", "all", "almost", "alone", "along", "already", "also","although","always","am","among", "amongst", "amoungst", "amount",  "an", "and", "another", "any","anyhow","anyone","anything","anyway", "anywhere", "are", "around", "as",  "at", "back","be","became", "because","become","becomes", "becoming", "been", "before", "beforehand", "behind", "being", "below", "beside", "besides", "between", "beyond", "bill", "both", "bottom","but", "by", "call", "can", "cannot", "cant", "co", "con", "could", "couldnt", "cry", "de", "describe", "detail", "do", "done", "down", "due", "during", "each", "eg", "eight", "either", "eleven","else", "elsewhere", "empty", "enough", "etc", "even", "ever", "every", "everyone", "everything", "everywhere", "except", "few", "fifteen", "fify", "fill", "find", "fire", "first", "five", "for", "former", "formerly", "forty", "found", "four", "from", "front", "full", "further", "get", "give", "go", "had", "has", "hasnt", "have", "he", "hence", "her", "here", "hereafter", "hereby", "herein", "hereupon", "hers", "herself", "him", "himself", "his", "how", "however", "hundred", "ie", "if", "in", "inc", "indeed", "interest", "into", "is", "it", "its", "itself", "keep", "last", "latter", "latterly", "least", "less", "ltd", "made", "many", "may", "me", "meanwhile", "might", "mill", "mine", "more", "moreover", "most", "mostly", "move", "much", "must", "my", "myself", "name", "namely", "neither", "never", "nevertheless", "next", "nine", "no", "nobody", "none", "noone", "nor", "not", "nothing", "now", "nowhere", "of", "off", "often", "on", "once", "one", "only", "onto", "or", "other", "others", "otherwise", "our", "ours", "ourselves", "out", "over", "own","part", "per", "perhaps", "please", "put", "rather", "re", "same", "see", "seem", "seemed", "seeming", "seems", "serious", "several", "she", "should", "show", "side", "since", "sincere", "six", "sixty", "so", "some", "somehow", "someone", "something", "sometime", "sometimes", "somewhere", "still", "such", "system", "take", "ten", "than", "that", "the", "their", "them", "themselves", "then", "thence", "there", "thereafter", "thereby", "therefore", "therein", "thereupon", "these", "they", "thickv", "thin", "third", "this", "those", "though", "three", "through", "throughout", "thru", "thus", "to", "together", "too", "top", "toward", "towards", "twelve", "twenty", "two", "un", "under", "until", "up", "upon", "us", "very", "via", "was", "we", "well", "were", "what", "whatever", "when", "whence", "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "whereupon", "wherever", "whether", "which", "while", "whither", "who", "whoever", "whole", "whom", "whose", "why", "will", "with", "within", "without", "would", "yet", "you", "your", "yours", "yourself", "yourselves", "the"};
    hash_table_t *table;
    table=create_hash_table(100);
    for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
    {
        add_string(table,&arr[i][0]);
    }

    string word;
    stringstream iss(neww);

    string Final="";
    while(iss>>word)
    {
        list_t *item;
        item=lookup_string(table,&word[0]);

        if(item==NULL)// This Word is not the STOP WORD
        {
            int sizee= strlen(&Final[0]) + strlen(&word[0]) +1;
            Final.resize(sizee);

            strcat(&Final[0],&word[0]);
            strcat(&Final[0]," ");
        }
        else
        {
            strcat(&Final[0]," ");
        }

    }

    return Final;
}
