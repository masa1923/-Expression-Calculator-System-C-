//MASA QURT
//1243442

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct AVLnode *AVLNode;

typedef struct CharNode{
char ch;
struct CharNode *next;
} CharNode;
typedef CharNode *charList;

charList strToCharList(const char *s){

charList head = NULL;
charList tail = NULL;

while(*s){

    CharNode *node = (CharNode*)malloc(sizeof(CharNode));
    if(!node){

        printf("Out of space\n");
        exit(1);
    }
    node->ch= *s++;
    node->next=NULL;
    if(!head) head= tail = node;//if the head = null meaning its the first node added so the new node is the tail and the head
    else{
        tail->next = node;
        tail=node;

    }

}
return head;


}
charList copyCharList(charList src){


charList head = NULL;
charList tail = NULL;

while(src){



    CharNode *node = (CharNode*)malloc(sizeof(CharNode));
    if(!node){

        printf("Out of space\n");
        exit(1);
    }
    node->ch= src->ch;
    node->next=NULL;
    if(!head) head= tail = node;//if the head = null meaning its the first node added so the new node is the tail and the head
    else{
        tail->next = node;
        tail=node;

    }

     src= src->next;
}
return head;


}
void printCharList(charList cl){

    while(cl){
        putchar(cl->ch);//prints one charachter at a time
        cl=cl->next;
    }

}
void freeCharList(charList cl){

    while(cl){

        CharNode *temp = cl;
        cl=cl->next;
        free(temp);
    }

}
void fprintCharList(FILE *f, charList cl){

    while(cl){

        fputc(cl->ch,f);//print character by character of the linked list into the output file
        cl = cl->next;

    }

}
int compareCharListTostr(charList cl, const char *s)
{
    while(cl&&*s){

        if(cl->ch <*s) //character list coes firt its smaller
            return -1;
        if(cl->ch>*s)//string comes before
            return 1;

        cl=cl->next;
        *s++;
    }
    if(!cl && !*s)
        return 0;
    if(cl!= NULL){

        return 1;//the list is longer and they are equal
    }
    else
        return -1;//the string is longer and they are equal
}
int charListCompare(charList a, charList b)//compares 2 char lists
{
    while (a&&b){

        if(a->ch<b->ch)
            return -1;
        if(a->ch > b->ch)
            return 1;
        a= a->next;
        b= b->next;
    }
    if(!a && !b){
        return 0;

    }
    if (a!=NULL){
        return 1;
    }
    else
        return -1;

}
int charListLen(charList cl){

int n=0;
while (cl){
    n++;
    cl=cl->next;
}
return n;

}
char charListAt(charList cl, int i){

while(cl && i>0){
    cl=cl->next;
    i--;
}
if(cl!=NULL){
    return cl->ch;
}
else
    return '\0';
}


typedef struct BuildingData{
charList name;//linked list for name
int number;
charList address;
int numOfApartments;
int establishmentYear;
bool hasPaidFees;

}BuildingData;

void freeBuildingData(BuildingData *bd){

freeCharList(bd->name);
freeCharList(bd->address);

}

BuildingData copyBuildingData(const BuildingData *src){

BuildingData bd;
bd.address = copyCharList(src->address);
bd.establishmentYear = src->establishmentYear;
bd.hasPaidFees = src->hasPaidFees;
bd.name = copyCharList(src->name);
bd.number = src->number;
bd.numOfApartments = src->numOfApartments;

return bd;
}
bool isOnlySpace(const char *str){

if (str == NULL || strlen(str) == 0) {
        return true;
    }
    for (int i=0; i < strlen(str);i++)
    {
        if (str[i]!=' ')
        return false;
    }

    return true;

}

bool isValidNum(const char *str){

if(strlen(str)==0){

    return false;
}

for(int i =0; i< strlen(str) ; i++ ){

    if(str[i]<'0' || str[i]>'9')
        return false;

}
return true;

}
void printBuildingData(BuildingData *bd){

    printf("  Name             : "); printCharList(bd->name);      printf("\n");
    printf("  Number           : %d\n", bd->number);
    printf("  Address          : "); printCharList(bd->address);   printf("\n");
    printf("  Apartments       : %d\n", bd->numOfApartments);
    printf("  Established year : %d\n", bd->establishmentYear);
    printf("  Paid fees        : %s\n", bd->hasPaidFees ? "yes" : "no");
    printf("  -------------------------------------------\n");

}

void saveBuildingDataToFile(FILE *f,const BuildingData *bd){
const char *fee;
fprintCharList(f,bd->name);
fprintf(f,":%d:",bd->number);
fprintCharList(f,bd->address);
 if(bd->hasPaidFees == true)
            fee="yes";
        else
            fee= "no";

fprintf(f,":%d:%d:%s\n",bd->numOfApartments,bd->establishmentYear,fee);

}

void readLine(char *t , int maxLen){

fgets(t,maxLen,stdin);
int len = strlen(t);
if(len>0 && t[len-1]=='\n')
    t[len-1]='\0';

}

BuildingData readBuildingUser(void){

 BuildingData bd;
    char temp[256];

    printf("  Enter name           : ");
    readLine(temp, sizeof(temp));
    while(isOnlySpace(temp)){

        printf("  [!] Name cannot be empty or just spaces.\n");
        printf("  Enter name           : ");
        readLine(temp, sizeof(temp));
    }


    bd.name = strToCharList(temp);

    printf("  Enter number         : ");
    readLine(temp,sizeof(temp));
    while(!isValidNum(temp)){
        printf("  [!] Invalid input. Please enter a valid number.\n");
        printf("  Enter number         : ");
        readLine(temp,sizeof(temp));

    }
     bd.number = atoi(temp);//atoi built in c function converts string to integer

    printf("  Enter address        : ");
    readLine(temp, sizeof(temp));
    while(isOnlySpace(temp)){

        printf("  [!] Address cannot be empty or just spaces.\n");
        printf("  Enter address        : ");
        readLine(temp, sizeof(temp));
    }
    bd.address = strToCharList(temp);

    printf("  Enter # apartments   : ");
    readLine(temp,sizeof(temp));
        while(!isValidNum(temp)){
        printf("  [!] Invalid input. Please enter a valid number.\n");
        printf("  Enter # apartments   : ");
        readLine(temp,sizeof(temp));

    }
    bd.numOfApartments= atoi(temp);


    printf("  Enter establish year : ");
    readLine(temp,sizeof(temp));
        while(!isValidNum(temp)){
        printf("  [!] Invalid input. Please enter a valid year.\n");
        printf("  Enter establish year : ");
        readLine(temp,sizeof(temp));

    }
    bd.establishmentYear = atoi(temp);


    printf("  Paid fees? (yes/no)  : ");
    readLine(temp, sizeof(temp));


        while (strcasecmp(temp, "yes") != 0 && strcasecmp(temp, "no") != 0) {
            printf("  [!] Invalid input. Please enter yes or no.\n");
            printf("  Paid fees? (yes/no)  : ");
            readLine(temp, sizeof(temp));}

    if (strcasecmp(temp,"yes")==0)
        bd.hasPaidFees = true;
    else
        bd.hasPaidFees = false;


    return bd;

}


bool parseLine(const char *line, BuildingData *out)
// to take whats in the file and parse them to indivisual pieces to convert them to the building data structure and to make suere its valid
{

    char nameB[200] ={0};
    char addressB [200]= {0};
    char feesB [10] = {0};

    int BuildingNum = 0;
    int totalAps=0;
    int creationYear = 0;

    //to make sure its valid and has 6 data
    int parseFieldCount = sscanf(line, "%200[^:]:%d:%200[^:]:%d:%d:%15[^:]",nameB,&BuildingNum,addressB,&totalAps,&creationYear,feesB);
    //scan a max of 200 charatcter [^:] but stop at teh : and skip it (the colon)
    //sscanf returns a number as it s output
    if(parseFieldCount !=6)
        return false;

    if (strlen(nameB) == 0 || (strlen(nameB) == 1 && nameB[0] == ' ')) {
    return false;
}
    out->address = strToCharList(addressB);
    out->establishmentYear = creationYear;
    out->name = strToCharList(nameB);
    out->number = BuildingNum;
    out->numOfApartments = totalAps;

    if (strcasecmp(feesB,"yes")==0){
        out->hasPaidFees = true;}
        else{
          out->hasPaidFees = false;
        }
    return true;
}


struct AVLnode
{
BuildingData data;

struct AVLnode *Left;
struct AVLnode *Right;
int Height; //Balance information
};

AVLNode MakeEmpty( AVLNode T )
{
if( T != NULL )
{
MakeEmpty( T->Left );
MakeEmpty( T->Right );
freeCharList( T->data.name );
freeCharList( T->data.address );
free( T );
}
return NULL;
}

AVLNode Find( charList name, AVLNode T )
{
if( T == NULL )
return NULL;
 int cmp = charListCompare( name, T->data.name );

    if( cmp < 0 )
        return Find( name, T->Left );
    else if( cmp > 0 )
        return Find( name, T->Right );
    else
        return T;
}

AVLNode FindMin( AVLNode T )
{
if( T == NULL )
return NULL;
else if( T->Left == NULL )
return T;
else
return FindMin( T->Left );
}

AVLNode FindMax( AVLNode T )
{
if( T != NULL )
while( T->Right != NULL )
T = T->Right;

return T;
}

/* START: fig4_36.txt */
int Height( AVLNode P )
{
if( P == NULL )
return -1;
else
return P -> Height;
}
/* END */

int Max( int Lhs, int Rhs )
{
return Lhs > Rhs ? Lhs : Rhs;
}

/* START: fig4_39.txt */
/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */
/* Update heights, then return new root */

AVLNode SingleRotateWithLeft( AVLNode K2 )
{
AVLNode K1;

K1 = K2->Left;
K2->Left = K1->Right;
K1->Right = K2;

K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
K1->Height = Max( Height( K1->Left ), Height(K2) ) + 1;

return K1; /* New root */
}


/* This function can be called only if K1 has a right child */
/* Perform a rotate between a node (K1) and its right child */
/* Update heights, then return new root */

AVLNode SingleRotateWithRight( AVLNode K1 )
{
AVLNode K2;

K2 = K1->Right;
K1->Right = K2->Left;
K2->Left = K1;

K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
K2->Height = Max( Height( K2->Right ), Height(K1) ) + 1;

return K2; /* New root */
}

/* START: fig4_41.txt */
/* This function can be called only if K3 has a left */
/* child and K3's left child has a right child */
/* Do the left-right double rotation */
/* Update heights, then return new root */

AVLNode DoubleRotateWithLeft( AVLNode K3 )
{
/* Rotate between K1 and K2 */
K3->Left = SingleRotateWithRight( K3->Left );

/* Rotate between K3 and K2 */
return SingleRotateWithLeft( K3 );
}
/* END */

/* This function can be called only if K1 has a right */
/* child and K1's right child has a left child */
/* Do the right-left double rotation */
/* Update heights, then return new root */

AVLNode DoubleRotateWithRight( AVLNode K1 )
{
/* Rotate between K3 and K2 */
K1->Right = SingleRotateWithLeft( K1->Right );

/* Rotate between K1 and K2 */
return SingleRotateWithRight( K1 );
}



AVLNode Insert( BuildingData bd, AVLNode T )
{
if( T == NULL )
{
/* Create and return a one-node tree */
T = malloc( sizeof( struct AVLnode ) );
if( T == NULL )
printf( "Out of space!!!" );
else
{
T->data = bd;
T->Height = 0;
T->Left = T->Right = NULL;
}
}
else if(charListCompare(bd.name,T->data.name)<0){
    T->Left = Insert(bd,T->Left);
    if(Height(T->Left)-Height(T->Right)==2)
    {
        if( charListCompare( bd.name, T->Left->data.name ) < 0 ){
            T= SingleRotateWithLeft(T);//left left
            }
        else
            T= DoubleRotateWithLeft(T);//left right


    }

}

else if(charListCompare(bd.name,T->data.name)>0){

    T->Right = Insert(bd,T->Right);
    if(Height(T->Right)-Height(T->Left)==2)
    {
        if(charListCompare(bd.name,T->Right->data.name)>0)
            T= SingleRotateWithRight(T);// right right
        else
            T= DoubleRotateWithRight(T);//right left
    }
}
T->Height= Max(Height(T->Left),Height(T->Right))+1;

return T;

}


AVLNode Delete(charList name, AVLNode T){

if(T==NULL){

    printf("Building not found!");
    return NULL;
}

int cmp = charListCompare(name,T->data.name);

if(cmp<0){

    T->Left = Delete(name,T->Left);

}
else if(cmp>0){

    T->Right= Delete(name,T->Right);

}
else//node we wannt to delete is found
{

    if(T->Left!=NULL && T->Right!=NULL){//two children we delete like in BST

        AVLNode temp = FindMin(T->Right);
        //we want to find the smallest value thats still bigger than t to put in the place of t so that the tree stays balanced
        freeBuildingData(&T->data);
        T->data = copyBuildingData(&temp->data);
        T->Right = Delete(temp->data.name, T->Right);
         //becuse freeBuilding take pointer to BUildingData we are deleting the data in t and over writing it
        printf("building was deleted successfully");
    }
    else{//zero or one child

        AVLNode temp = T;
        if(T->Left!=NULL){

            T=T->Left;
        }
        else
            T=T->Right;

        freeBuildingData(&temp->data);
        free(temp);
        printf("building was deleted successfully");
        return T;
    }
}

T->Height = Max(Height(T->Left),Height(T->Right))+1;
int balance = Height(T->Left)- Height(T->Right);

 if( balance == 2 )
    {
        if( Height( T->Left->Left ) >= Height( T->Left->Right ) )
            T = SingleRotateWithLeft( T );
        else
            T = DoubleRotateWithLeft( T );
    }
    else if( balance == -2 )
    {
        if( Height( T->Right->Right ) >= Height( T->Right->Left ) )
            T = SingleRotateWithRight( T );
        else
            T = DoubleRotateWithRight( T );
    }

    return T;
}

void listByApts(AVLNode t, int n){

    if(!t)return;

    listByApts(t->Left,n);
    if(t->data.numOfApartments>n){
        printBuildingData(&t->data);

    }

    listByApts(t->Right,n);
}


void listOfUnpaid(AVLNode t){

    if (!t)
        return;
    listOfUnpaid(t->Left);
    if (!t->data.hasPaidFees){
        printBuildingData(&t->data);

    }
    listOfUnpaid(t->Right);

}


void avlSaveToFile(AVLNode t,FILE *f){

if (!t)
    return;
avlSaveToFile(t->Left,f);
saveBuildingDataToFile(f,&t->data);
avlSaveToFile(t->Right,f);

}


void freeTree(AVLNode t){

if(!t)
return;
freeTree(t->Left);
freeTree(t->Right);
freeBuildingData(&t->data);
free(t);

}




//in-order print to see the elements
void PrintInOrder( AVLNode t)
{
if( t != NULL)
{
PrintInOrder( t->Left );
printBuildingData(&t->data);
PrintInOrder( t->Right );
}
}



#define HC_empty 0
#define HC_occupied 1
#define HC_deleted 2
typedef struct HashCell{
int status; //empty occupied or deleted
BuildingData data;

}HashCell;
typedef struct Hashtable *HashTable;
struct Hashtable{
HashCell *cells;
int size;
int count;
} ;

static bool isPrime(int n){
if(n<2)
    return false;
if (n==2)
    return true;
if(n%2==0)
    return false;
for(int i=3;i*i<=n;i+=2)
{
    if(n%i==0)
        return false;

}
return true;
}



static int nextPrime(int n){

while(!isPrime(n))
    n++;
return n;
}




static int HashFunction(charList name, int tableSize){

int sum = 0;
charList current = name;
for(int i=0; i<4 && current; current = current->next,i++)
{
    sum+=(int)(unsigned char )current->ch;


}

return sum %tableSize;


}

HashTable createHT(int capacity) {
    HashTable ht = (HashTable )malloc(sizeof( HashTable));
    if (!ht)
        { printf("Out of space!\n");
        exit(1); }

    ht->cells = (HashCell *)malloc(capacity * sizeof(HashCell));
    if (!ht->cells)
        { printf("Out of space!\n");
        exit(1); }

    ht->size  = capacity;
    ht->count = 0;

    //Initialise every slot to EMPTY with NULL charList pointers
    for (int i = 0; i < capacity; i++) {
        ht->cells[i].status                    = HC_empty ;
        ht->cells[i].data.name                 = NULL;
        ht->cells[i].data.address              = NULL;
        ht->cells[i].data.number               = 0;
        ht->cells[i].data.numOfApartments      = 0;
        ht->cells[i].data.establishmentYear    = 0;
        ht->cells[i].data.hasPaidFees          = false;
    }
    return ht;
}

void freeHt(HashTable ht){

for (int i=0;i< ht->size;i++){

    if(ht->cells[i].status==HC_occupied)
        freeBuildingData(&ht->cells[i].data);


    }
free(ht->cells);
    free(ht);
}
//linear probing
bool htInsert(HashTable ht,BuildingData bd){

if(ht->count>=ht->size)
{
    printf("hash table is full!\n");
    return false;
}

    int starterCell = HashFunction(bd.name,ht->size);
    int savedDeletedCell = -1;
    for(int i= 0;i<ht->size;i++){

        int currentCell = (starterCell +i)%ht->size;

        if(ht->cells[currentCell].status == HC_empty)
        {
            int finalCell =0;
            if (savedDeletedCell!=-1){
             finalCell = savedDeletedCell;}
            else
                finalCell= currentCell;


            ht->cells[finalCell].status= HC_occupied;
            ht->cells[finalCell].data=bd;
            ht->count++;
            return true;

        }
        if(ht->cells[currentCell].status == HC_deleted)
        {
            if(savedDeletedCell==-1){
                savedDeletedCell= currentCell;
            }
        }

        else{//the cell is occupied

            if(charListCompare(ht->cells[currentCell].data.name,bd.name)==0)
            {
                printf("BUILDING ALREADY IN HASH TABLE\n");
                freeBuildingData(&bd);
                return false;
            }
        }


    }

    if(savedDeletedCell!=-1){
        ht->cells[savedDeletedCell].status=HC_occupied;
        ht->cells[savedDeletedCell].data=bd;
        ht->count++;
        return true;
    }
    printf("Hash table is full!\n");
}
//function that searches for a specific building and gives us the option to get the number of collision before reaching the cell we want
int searchHt(HashTable ht, charList name, bool printCollisions){

int cell = HashFunction(name,ht->size);
int collisions =0;
for(int i=0;i<ht->size;i++){
    int index = (cell+i)%ht->size;
    if(ht->cells[index].status== HC_empty)
        break;

    if(ht->cells[index].status==HC_occupied){
        if(charListCompare(ht->cells[index].data.name,name)==0){
        if(printCollisions){
            printf("collisions to reach this building: %d\n",collisions);
        }
        return index;
            }
            collisions++;
        }
    }

printf(" Building not found in the hash table.\n");
return -1;
}


void DeleteFromHT(HashTable ht, charList name) {
    int index = searchHt(ht, name, false);
    if (index == -1) { printf("  Building not found in hash table.\n");
     return;
      }
    freeBuildingData(&ht->cells[index].data);
    ht->cells[index].data.name    = NULL;
    ht->cells[index].data.address = NULL;
    ht->cells[index].status       = HC_deleted;
    ht->count--;
    printf(" Building deleted from hash table.\n");
}
void printHT(HashTable ht) {
    for (int i = 0; i < ht->size; i++) {
        printf("  [%3d] ", i);
        if(ht->cells[i].status == HC_empty)
            printf("(empty)\n");
        else if (ht->cells[i].status == HC_deleted)
          printf("(deleted)\n");
        else {
        printf("(Occupied:)\n");
         printBuildingData(&ht->cells[i].data);
         }
    }
}

void printStatsHT(HashTable ht) {
    printf("  Table size  : %d\n", ht->size);
    printf("  Occupied    : %d\n", ht->count);
    printf("  Load factor : %.4f\n", (float)ht->count / ht->size);
}

void saveHtToFile(HashTable ht, const char *filename){

FILE *f = fopen(filename,"w");
if(!f){

    printf("cannot open %s for writing \n",filename);
    return;
        }
    for(int i=0;i< ht->size;i++){

        if(ht->cells[i].status==HC_occupied){

            saveBuildingDataToFile(f,&ht->cells[i].data);

        }
    }
    fclose(f);
    printf("Data saved to hash.txt");

}


int countLines(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        return 0;
    }

    int count = 0;
    char temp[500];

    // Read line by line
    while (fgets(temp, sizeof(temp), f)) {
        // Basic check to ensure we don't count completely empty lines
        if (temp[0] != '\n' && temp[0] != '\r' && strlen(temp) > 0) {
            count++;
        }
    }

    fclose(f);
    return count;
}

AVLNode loadTree(const char *filename)
{

    FILE *f = fopen(filename,"r");
    if(!f){
        printf("cannot open %s starting with empty tree\n",filename);
        return NULL;
    }

    char temp[500];
    AVLNode node = NULL;
    int loaded=0;

    while(fgets(temp,sizeof(temp),f)){

        if(temp[0]=='\0'||temp[0]=='\n'){
            continue;
        }
        BuildingData bd;
        if(parseLine(temp,&bd)){
            node = Insert(bd,node);
            loaded++;

        }
        else{
                printf("skipping wrongly formatted line: %s",temp);
            }


    }
    fclose(f);
    printf("loaded %d buildings into AVL tree from: %s\n",loaded,filename);
    return node;

}

HashTable loadHash(const char *filename){

int n = countLines(filename);
if(n==0)n=17;//defult

int tableSize = nextPrime(2*n +1);
HashTable ht = createHT(tableSize);

FILE *f = fopen(filename,"r");
if(!f){
     printf("cannot open %s starting with empty hash table\n",filename);
     return ht;
}

char temp[500];
int loaded=0;
while (fgets(temp,sizeof(temp),f)){

          if(temp[0]=='\0'||temp[0]=='\n'){
            continue;
        }
        BuildingData bd;
        if(parseLine(temp,&bd)){
            htInsert(ht,bd);
            loaded++;

        }
        else{
                printf("skipping wrongly formatted line: %s",temp);
            }


    }
    fclose(f);


 printf("loaded %d buildings into hash table from: %s\n",loaded,filename);
    return ht;

}


void mainMenu(void){

int choice;
char temp[200];

printf("\n loading info.txt into AVL tree\n");
AVLNode node = loadTree("info.txt");

HashTable ht= NULL;



    do {
        printf("\n|------------------------------------------|\n");
        printf("|     Building Management System           |\n");
        printf("|------------------------------------------|\n");
        printf("|  -- Phase 1: AVL Tree --                 |\n");
        printf("|   1. List all buildings (A-Z)            |\n");
        printf("|   2. Insert a new building               |\n");
        printf("|   3. Find / Update a building            |\n");
        printf("|   4. List buildings with apartments > N  |\n");
        printf("|   5. List buildings that have NOT paid   |\n");
        printf("|   6. Delete a building                   |\n");
        printf("|   7. Save tree >> Load Hash Table        |\n");
        printf("|------------------------------------------|\n");


        if (ht != NULL) {
            printf("|  -- Phase 2: Hash Table --               |\n");
            printf("|   8.  Print entire hash table            |\n");
            printf("|   9.  Print table size and load factor   |\n");
            printf("|   10. Insert a record into hash table    |\n");
            printf("|   11. Search for a building              |\n");
            printf("|   12. Delete a record from hash table    |\n");
            printf("|------------------------------------------|\n");
        }

        printf("|   0. Save and Exit                       |\n");
        printf("|------------------------------------------|\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();


        switch(choice){

    case 1:{
         printf("\n--- All Buildings (A-Z) ---\n");
         if(!node){
            printf("tree is empty");}
            else
                PrintInOrder(node);
            break;
         }
    case 2:{
         printf("\n--- Insert New Building ---\n");
        BuildingData bd = readBuildingUser();
        node = Insert(bd,node);
        break;

        }
    case 3:{
        printf("\n--- Find / Update Building ---\n");
        printf("  Enter building name: ");

        readLine(temp,sizeof(temp));

        charList key = strToCharList(temp);
        AVLNode found = Find(key,node);
        freeCharList(key);
        if(!found){
            printf("building not found\n");
        }
        else{
            printf("found:\n");
            printBuildingData(&found->data);
             do{
                    printf("do you want to update the data?(yes/no)");
                    readLine(temp,sizeof(temp));

                        if(strcasecmp(temp,"yes")!=0 && strcasecmp(temp,"no")!=0)
                        {
                     printf("invalid input. please enter yes or no");
                            }
                }while(strcasecmp(temp,"yes")!=0 && strcasecmp(temp,"no")!=0);

            if(strcasecmp(temp,"yes")==0){

                printf("  Enter number         : ");
    readLine(temp,sizeof(temp));
    while(!isValidNum(temp)){
        printf("  [!] Invalid input. Please enter a valid number.\n");
        printf("  Enter number         : ");
        readLine(temp,sizeof(temp));

    }
     found->data.number = atoi(temp);//atoi built in c function converts string to integer

    printf("  Enter address        : ");
    readLine(temp, sizeof(temp));
    while(isOnlySpace(temp)){

        printf("  [!] Address cannot be empty or just spaces.\n");
        printf("  Enter address        : ");
        readLine(temp, sizeof(temp));
    }
    freeCharList(found->data.address);//free old address
    found->data.address = strToCharList(temp);

    printf("  Enter # apartments   : ");
    readLine(temp,sizeof(temp));
        while(!isValidNum(temp)){
        printf("  [!] Invalid input. Please enter a valid number.\n");
        printf("  Enter # apartments   : ");
        readLine(temp,sizeof(temp));

    }
    found->data.numOfApartments= atoi(temp);


                do{
                    printf("paid fees?\n");
                    readLine(temp,sizeof(temp));
                        if(strcasecmp(temp,"yes")!=0 && strcasecmp(temp,"no")!=0)
                        {
                            printf("invalid input. please enter yes or no\n");
                            }
                }while(strcasecmp(temp,"yes")!=0 && strcasecmp(temp,"no")!=0);

                    found->data.hasPaidFees =(strcasecmp(temp,"yes")==0);

                    printf("Record Updated!\n");

            }
        }
        break;
    }
    case 4:{

    int n;
    printf("\n--- Buildings with Apartments > N ---\n");
    printf("  Enter N: ");
    readLine(temp,sizeof(temp));
    while(!isValidNum(temp)){
        printf("  [!] Invalid input. Please enter a valid number.\n");
        printf("  Enter N: ");
        readLine(temp,sizeof(temp));

    }
    n = atoi(temp);
    listByApts(node,n);


    break;
    }

    case 5:{
    printf("\n--- Buildings That Have NOT Paid Fees ---\n");
    listOfUnpaid(node);
    break;
    }

    case 6:{
    printf("\n--- Delete Building from AVL Tree ---\n");
    printf("enter building name: ");
    readLine(temp,sizeof(temp));
    charList key = strToCharList(temp);
    node = Delete(key,node);
    freeCharList(key);

    break;
    }

    case 7:{

        FILE *f = fopen("hash.txt","w");
        if(!f){
            printf("could not open file hash.txt fro writing\n");
            break;
        }
        avlSaveToFile(node,f);
        fclose(f);
        printf("AVL tree saved to hash.txt\n");

        if(ht!=NULL)
        freeHt(ht);//free old hash table if user hits 7 more than once

    printf("  [*] Building hash table from hash.txt...\n");
    ht = loadHash("hash.txt");
    printf("  Hash table ready. Phase 2 options are now unlocked.\n");
        break;

    }
    case 8:{

    if(!ht){
        printf("please choose option 7 first to load the hash table");
        break;
    }
    printf("\n--- Hash Table Contents ---\n");
    printHT(ht);
    break;

    }
    case 9:{

    if(!ht){
        printf("please choose option 7 first to load the hash table");
        break;
    }
          printf("\n--- Hash Table Statistics ---\n");
          printStatsHT(ht);
          break;
    }

    case 10:{

          if(!ht){
        printf("please choose option 7 first to load the hash table");
        break;

    }
    printf("\n--- Insert Into Hash Table ---\n");
    BuildingData bd = readBuildingUser();
    htInsert(ht,bd);
    break;

    }

    case 11:{

        if(!ht){
            printf("please choose option 7 first to load the hash table");
            break;

    }
        printf("\n--- Search Hash Table ---\n");
        printf("  Enter building name: ");
        readLine(temp,sizeof(temp));
        charList key = strToCharList(temp);
        int index = searchHt(ht,key,true);
        if(index==-1){
            printf("building not found!\n");
        }
        else{
            printf("found at cell: %d",index);
            BuildingData bd = ht->cells[index].data;
            printBuildingData(&bd);
        }
        break;

    }
    case 12:{

        if(!ht){
            printf("please choose option 7 first to load the hash table");
            break;
    }
        printf("\n--- Delete From Hash Table ---\n");
        printf("  Enter building name: ");
        readLine(temp,sizeof(temp));
        charList key = strToCharList(temp);
        DeleteFromHT(ht,key);
        freeCharList(key);
        break;

    }
    case 0:
        {
            //save everything and exit

             if (ht != NULL){
                    saveHtToFile(ht,"hash.txt");
            }

            else {
                 FILE *f = fopen("hash.txt","w");
                    if (f) {
                    saveHtToFile(ht,f);

                    fclose(f);
                    printf("Data saved to hash.txt\n");
                }
                else {
            printf("Could not open hash.txt for writing.\n");
        }
               }}
            break;

    default:{
        printf("INVALID CHOICE!\n");

        }
        }



 }while(choice !=0);

freeTree(node);
if(ht!=NULL)
    freeHt(ht);



}


int main()
{
     printf("==============================================\n");
    printf("   COMP2421 Project #2 - Building Manager   \n");
    printf("==============================================\n");

    mainMenu();

    printf("\n[*] Goodbye!\n");
    return 0;
}
