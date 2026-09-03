#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

struct eqNode;
struct charNode;
struct treeNode;

typedef struct charNode {
    char            ch;
    struct charNode *next;
} charNode;

/* Stack structure for operands (doubles) */
typedef struct numStack{
    double data;
    struct numStack *next;
} numStack;

typedef struct treeNode {
    charNode *value;                       //Operator or operand
    struct treeNode *left;                // Left subtree pointer
    struct treeNode *right;               // Right subtree pointer
} treeNode;

typedef struct treeStack {
    treeNode        *ptr;
    struct treeStack *next;
} treeStack;

typedef struct opStack {
    char    data;
    struct opStack *next;
} opStack;

int numIsEmpty(numStack *S);
void numPush(numStack **S, double val);
double numPop(numStack **S);
void numFree(numStack **S);

int treeIsEmpty(treeStack *S);
void treePush(treeStack **S, treeNode *ptr);
treeNode* treePop(treeStack **S);
void treeFreeStack(treeStack **S);

int opIsEmpty(opStack *S);
char opTop(opStack *S);
void opPush(opStack **S, char val);
char opPop(opStack **S);
void opFree(opStack **S);

int charIsEmpty(opStack *S);
char charPop(opStack **S);
void charDeleteStack(opStack **S);

void freeEquationList(void);
void appendEquation(charNode *line);

struct eqNode* getEquation(int index);
struct treeNode* buildExpressionTree(struct charNode *postfix);

charNode* strAppend(charNode *head, char c) {
    charNode *n = (charNode*)malloc(sizeof(charNode));
    if (!n) { printf("out of memory\n"); exit(1); }
    n->ch   = c;
    n->next = NULL;
    if (!head) return n;
    charNode *cur = head;
    while (cur->next) cur = cur->next;
    cur->next = n;
    return head;
}


int numIsEmpty(numStack *S) {
    return S == NULL;
}

charNode* strFromLiteral(const char *s) {
    charNode *head = NULL;
    while (*s) head = strAppend(head, *s++);
    return head;
}

// charIsEmpty / charPop / charDeleteStack reuse the opStack type
int charIsEmpty(opStack *S) {
    return S == NULL;
}

char charPop(opStack **S) {
    if (charIsEmpty(*S)) { printf("char stack empty\n"); return '\0'; }
    opStack *tmp = *S;
    char val = tmp->data;
    *S = tmp->next;
    free(tmp);
    return val;
}

void charDeleteStack(opStack **S) {
    while (!charIsEmpty(*S)) charPop(S);
}
// append a character to a string list

// free a string list
void strFree(charNode *head) {
    while (head) {
        charNode *tmp = head;
        head = head->next;
        free(tmp);
    }
}

// length of a string list
int strLen(charNode *head) {
    int len = 0;
    while (head)
        { len++;
    head = head->next; }
    return len;
}

// get character at index i  return '\0' if out of range
char strGet(charNode *head, int i) {
    while (head) {
        if (i == 0) return head->ch;
        i--;
        head = head->next;
    }
    return '\0';
}

// print a string list
void strPrint(charNode *head) {
    while (head) {
            printf("%c", head->ch);
            head = head->next; }
}

// print a string list to a FILE
void strFPrint(FILE *fp, charNode *head) {
    while (head) {
        fprintf(fp, "%c", head->ch);
    head = head->next;
     }
}

//ensures each stage of the project has its own independent version of the equation so that when one of the functions uses it and then deletes there is a copy for the other functions to use
charNode* strCopy(charNode *src) {
    charNode *head = NULL;
    while (src) { head = strAppend(head, src->ch); src = src->next; }
    return head;
}

//checks if linked list is empty strin
int strEmpty(charNode *head)
{
    return head == NULL; }

// append a C-literal string to a string list
charNode* strAppendLiteral(charNode *head, const char *s) {
    while (*s) head = strAppend(head, *s++);
    return head;
}

// append one digit (integer 0-9)
charNode* strAppendDigit(charNode *head, int d) {
    return strAppend(head, (char)('0' + d));
}


 // create a new tree node
treeNode* newTreeNode(charNode *val) {
    treeNode *n = (treeNode*)malloc(sizeof(treeNode));
    if (!n) { printf("out of memory\n"); exit(1); }
    n->value = strCopy(val);
    n->left  = NULL;
    n->right = NULL;
    return n;
}

void freeTree(treeNode *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    strFree(root->value);
    free(root);
}


void numPush(numStack **S, double val) {
    numStack *n = (numStack*)malloc(sizeof(numStack));
    if (!n) { printf("out of memory\n"); exit(1); }
    n->data = val;
    n->next = *S;
    *S = n;
}

double numPop(numStack **S) {
    if (numIsEmpty(*S)) { printf("num stack empty\n"); return 0; }
    numStack *tmp = *S;
    double val = tmp->data;
    *S = tmp->next;
    free(tmp);
    return val;
}


void numFree(numStack **S)
 { while (!numIsEmpty(*S))
    numPop(S);
     }

/* Stack structure for operators and characters */




int treeIsEmpty(treeStack *S)
{
    return S == NULL; }

void treePush(treeStack **S, treeNode *ptr) {
    treeStack *n = (treeStack*)malloc(sizeof(treeStack));
    if (!n) { printf("out of memory\n"); exit(1); }
    n->ptr  = ptr;
    n->next = *S;
    *S = n;
}

treeNode* treePop(treeStack **S) {
    if (treeIsEmpty(*S)) { printf("tree stack empty\n"); return NULL; }
    treeStack *tmp = *S;
    treeNode *ptr  = tmp->ptr;
    *S = tmp->next;
    free(tmp);
    return ptr;
}


void treeFreeStack(treeStack **S)
 { while (!treeIsEmpty(*S))
  treePop(S);
  }




int opIsEmpty(opStack *S){
     return S == NULL;
     }
char  opTop(opStack *S)
{
    return S ? S->data : '\0';
    }

void opPush(opStack **S, char val) {
    opStack *n = (opStack*)malloc(sizeof(opStack));
    if (!n) { printf("out of memory\n"); exit(1); }
    n->data = val;
    n->next = *S;
    *S = n;
}

char opPop(opStack **S) {
    if (opIsEmpty(*S)) { printf("op stack empty\n"); return '\0'; }
    opStack *tmp = *S;
    char val = tmp->data;
    *S = tmp->next;
    free(tmp);
    return val;
}

void opFree(opStack **S) { while (!opIsEmpty(*S)) opPop(S); }


typedef struct eqNode {
    charNode *infix;        // original infix expression
    charNode *postfix;      // converted postfix (NULL until done)
    charNode *validityMsg;  // "valid" or error description
    double result;       // evaluated result
    int isValid;      // 1=valid 0=invalid
    int postfixDone;  // 1=postfix already computed
    struct eqNode *next;
} eqNode;

treeNode* newTreeNode(charNode *val);
void freeTree(treeNode *root);

void freeEquationList(void);
void appendEquation(struct charNode *line);
struct charNode* strFromLiteral(const char *s);
struct charNode* buildErrorMsg(const char *prefix, char ch, int pos);
void charDeleteStack(opStack **S);
int charIsEmpty(opStack *S);
char charPop(opStack **S);
int numIsEmpty(numStack *S);




int isOperator(char ch);
int precedence(char op);
int isOpenBracket(char ch);
int isCloseBracket(char ch);
char matchingClose(char open);
char matchingOpen(char close);

void readEquationsFromFile(void);
int validateExpression(charNode *expr, charNode **errorMsg);
void checkValidity(void);
charNode* infixToPostfix(charNode *infix);
void convertToPostfix(void);
double evaluatePostfix(charNode *postfix);
void evaluateEquations(void);
void printInvalidEquations(void);
treeNode* ExpressionTree(charNode *postfix);
void inorder(treeNode *root);
void postorder(treeNode *root);
void preorder(treeNode *root);
void expressionTreeOption(void);
void writeOutputFile(void);
void printMenu(void);


int main(){

    eqNode *equationList = NULL;
    int equationCount = 0;
    int validityCalc  = 0;

    int choice;
    printf("Welcome to the COMP2421 Calculator!\n");

    do {
        printMenu();
        if(scanf("%d", &choice) != 1){
            int ch;
            while((ch = getchar()) != '\n' && ch != EOF);
            choice = -1;
        }

        switch(choice){
            case 1: readEquationsFromFile();  break;
            case 2: checkValidity();          break;
            case 3: convertToPostfix();       break;
            case 4: evaluateEquations();      break;
            case 5: printInvalidEquations();  break;
            case 6: expressionTreeOption();   break;
            case 7: writeOutputFile();        break;
            case 8: printf("Goodbye!\n");     break;
            default: printf("Invalid choice. Enter 1-8.\n");
        }
    } while(choice != 8);

    return 0;
}

 eqNode *equationList = NULL;
    int equationCount = 0;
    int validityCalc  = 0;

charNode* buildErrorMsg(const char *prefix, char ch, int pos) {
    charNode *msg = strFromLiteral(prefix);
    if (ch != '\0') {
        msg = strAppendLiteral(msg, "'");
        msg = strAppend(msg, ch);
        msg = strAppendLiteral(msg, "' ");
    }
    msg = strAppendLiteral(msg, "at position ");

    // Simple integer to string conversion
    if (pos == 0) {
        msg = strAppend(msg, '0');
    } else {
        int temp = pos;
        int digits = 0;
        while (temp > 0) { digits++; temp /= 10; }
        temp = pos;
        for (int i = 0; i < digits; i++) {
            int p = pow(10, digits - i - 1);
            msg = strAppend(msg, (char)('0' + (temp / p)));
            temp %= p;
        }
    }
    return msg;
}


/*which of the operations is it + - * / */
int isOperator(char ch){
    return ch=='+' || ch=='-' || ch=='*' || ch=='/'||ch=='^';
}

/* order of superiority: * and / beat + and - */
int precedence(char op){
    if(op=='^')return 3;
    if(op=='*' || op=='/') return 2;/*higher precedence*/
    if(op=='+' || op=='-') return 1;
    return 0;
}

/* is it an opening bracket */
int isOpenBracket(char ch){
    return ch=='(' || ch=='[';
}

/* is it a closing bracket */
int isCloseBracket(char ch){
    return ch==')' || ch==']';
}

/* given an opening bracket return its matching closing bracket */
char matchingClose(char open){
    if(open=='(') return ')';
    if(open=='[') return ']';
    return '\0';
}

/* given a closing bracket return its matching opening bracket */
char matchingOpen(char close){
    if(close==')') return '(';
    if(close==']') return '[';
    return '\0';
}
void freeEquationList(void) {
    eqNode *cur = equationList;
    while (cur) {
        eqNode *tmp = cur;
        cur = cur->next;
        strFree(tmp->infix);
        strFree(tmp->postfix);
        strFree(tmp->validityMsg);
        free(tmp);
    }
    equationList  = NULL;
    equationCount = 0;
    validityCalc  = 0;
}

void appendEquation(charNode *line) {
    eqNode *node = (eqNode*)malloc(sizeof(eqNode));
    if (!node) { printf("out of memory\n"); exit(1); }
    node->infix       = strCopy(line);
    node->postfix     = NULL;
    node->validityMsg = NULL;
    node->result      = 0.0;
    node->isValid     = 0;
    node->postfixDone = 0;
    node->next        = NULL;

    // append to end of list
    if (!equationList) { equationList = node; return; }
    eqNode *cur = equationList;
    while (cur->next) cur = cur->next;
    cur->next = node;
}

eqNode* getEquation(int index) {   // 0-based index
    eqNode *cur = equationList;
    int i = 0;
    while (cur) {
        if (i == index) return cur;
        i++;
        cur = cur->next;
    }
    return NULL;
}


void readEquationsFromFile() {
    // read filename character by character into a string list,
    //  then convert to a temporary C string only for fopen
    const char *filename = "equations.txt";
    FILE *fp = fopen(filename, "r");

    if (!fp) { printf("ERROR: cannot open file\n"); return; }

    freeEquationList();
    equationCount = 0;  //to reset the number of equations with the list
    validityCalc  = 0;
    /* read file one char at a time — no arrays */
    charNode *line = NULL;
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\r') continue;
        if (c == '\n') {
            if (!strEmpty(line)) {
                appendEquation(line);
                equationCount++;
                strFree(line);
                line = NULL;
            }
            continue;
        }
        line = strAppend(line, (char)c);
    }
    //makes sure tha last line has no trailing new line
    if (!strEmpty(line)) {
        appendEquation(line);
        equationCount++;
        strFree(line);
    }


    fclose(fp);
    printf("Read %d equation(s) from '%s'\n", equationCount, filename);

}

 //Returns 1 if valid, 0 if invalid
//errorMsg written reason when invalid
int validateExpression(charNode *expr, charNode **errorMsg){
    opStack *bracketStack = NULL;// tracks open brackets
    charNode *current=expr;
    int switchOp= 1;  //(what comes next)when switch=1 looking for number after when switch=0 looking for an operator
    int present= 0;  //looks at whats present now to check if its an empty string starts at 0(false) as soon as the code finds a correct num or operator accoding to the switch it flips to 1(true)
    int position=0;

    while(current){
        char ch = current->ch;

        if(isspace(ch)){

            current= current->next;
            continue; }


        if(isdigit(ch)){
            if(!switchOp){
                //number right after a number or missing operator
                *errorMsg = strFromLiteral("missing operator before digit at position ");
                *errorMsg = strAppendLiteral(*errorMsg, "");

                charNode *tmp = buildErrorMsg("missing operator before digit ", ch, position);
                *errorMsg = tmp;
                opFree(&bracketStack);
                return 0;
            }
            while(current && isdigit(current->ch)){
            switchOp = 0;
            present = 1;
            current = current->next;
            position++;
            }continue;
        }


        if(isOpenBracket(ch)){
            if(!switchOp)//if the present switch before adding a opening is one meaning an number not a operation we send an error message becuse an opening needs to come after an operation 1(.. false 1*(..)true
                {
                *errorMsg= buildErrorMsg("missing operator before ", ch, position);
                opFree(&bracketStack);
                return 0;
            }
            opPush(&bracketStack, ch);
            switchOp = 1;
             present = 1;
            current = current->next;
            position++;
            continue;
        }


        if(isCloseBracket(ch)){
            if(switchOp){
                *errorMsg = buildErrorMsg("empty brackets near ", ch, position);
                opFree(&bracketStack);
                return 0;
            }
            if(opIsEmpty(bracketStack))//if its empty error because it means that there is no opening before the closing
                {
                *errorMsg = buildErrorMsg("no matching open bracket for ", ch, position);
                return 0;
            }
            char open = opPop(&bracketStack);
            if(matchingClose(open) != ch)//checks if the open the pop of the bracket stack matches the closing bracket we encountered if not error and emptty the stack becuse its wrong
            {
                *errorMsg = buildErrorMsg ("' is not closed", open,position);
                charDeleteStack(&bracketStack);
                return 0;
            }
            switchOp = 0;//after closing it needs to be an operation not a number
            current= current->next;
            position++;
            continue;
        }


        if(isOperator(ch)){
            if(switchOp)//at switchop=1 we are expecting a number but here an operation came so error
                {
                *errorMsg = buildErrorMsg("unexpected operator ", ch, position);
                opFree(&bracketStack);
                return 0;
            }
            switchOp = 1;//adds the operation when not switchop and the makes the switchop=1 so that a number comes after the operation
            current= current->next;
            position++;
            continue;
        }


        *errorMsg = buildErrorMsg("unknown character ", ch, position);
        opFree(&bracketStack);

        return 0;
    }

    // unclosed brackets left on stack
    if(!charIsEmpty(bracketStack)){
        char unclosed = charPop(&bracketStack);
        *errorMsg = buildErrorMsg("unclosed bracket ", unclosed, position);//tool used to actually put words into a string
        opFree(&bracketStack);

        return 0;
    }

    //ended while it still expects a number switchop=1 and present =1(correct)
    if(switchOp && present){
        *errorMsg = strFromLiteral("expression ends with an operator");
        return 0;
    }

    if(!present){
        *errorMsg = strFromLiteral("expression is empty");
        return 0;
    }

    *errorMsg= NULL;
    return 1;
}


void checkValidity(){
    if(equationCount == 0){
        printf("No equations loaded. Use option 1 first.\n");
        return;
    }

    eqNode *current = equationList;
    printf("\n--- Validity Check ---\n");
    int i=1;
    while (current) {
        charNode *errorMsg = NULL;//initializes errormsg
        current->isValid = validateExpression(current->infix, &errorMsg);//takes the equations and checks for any errors if it finds it fills the errormsg string with whatevere it is
        strFree(current->validityMsg);

        if (current->isValid) {
            current->validityMsg = strFromLiteral("valid");//copy "valid" onto the validit message
            printf("Equation No. %d -> valid\n", i);
        } else {
           current->validityMsg = errorMsg;
            printf("Equation No. %d -> invalid: \n", i);//prints message that is filled in the validate expression function
            strPrint(current->validityMsg);
            printf("\n");
        }
        current = current->next;
         i++;
        }

    validityCalc= 1;//gives the green light for the program to continue"inspection is done"
}

/*
 *  INFIX TO POSTFIX
 *
 *  Scan left to right:
 *    numbers: copy straight to the output
 *    open bracket push to operator stack always doesnt affect the precedence it goes back to 0 so anything can be put above a bracket no matter what is below it
 *    operator : push the operators into stack until lower precedence is come upon
 *    close bracket:pop all that is in the stack to the  output until matching open bracket
 *

*/
charNode* infixToPostfix(charNode *infix) {
    opStack *opStack = NULL;
    charNode *out= NULL;
    charNode *current= infix;




    while(current){

    char ch = current->ch;
        if(isspace(ch)){
            current=current->next;
            continue; }


        if(isdigit(ch)){
            while(current&& isdigit(current->ch)){
                out = strAppend(out, current->ch);;//copying infix into postfix
                current=current->next;

        }
      out = strAppend(out, ' ');
            continue;
    }
        if(isOpenBracket(ch)){
            opPush(&opStack, ch);//push the open Bracket into the opertion stck
            current=current->next;

            continue;
        }


        if(isCloseBracket(ch)){
            while(!charIsEmpty(opStack) && !isOpenBracket(opTop(opStack)))//when a closed bracket occurs push pop of infix to the postfix
                {
                out = strAppend(out, opPop(&opStack));
                out = strAppend(out, ' ');//put spaces between charcters
            }
            if(!opIsEmpty(opStack))
                charPop(&opStack);//pop of the open bracket no brackets in postfix so we just pop no push
            current=current->next;
            continue;
        }


        if(isOperator(ch)){
            while(!opIsEmpty(opStack) && !isOpenBracket(opTop(opStack)) &&precedence(opTop(opStack)) >= precedence(ch))
                //we push all operations int postfix unless a lower precedence occurs after ther already is a higher prceddence in the stcak and the op is not an open bracket
                  {
                out = strAppend(out, opPop(&opStack));
                out = strAppend(out, ' ');//add space always
            }
            opPush(&opStack, ch);
            current=current->next;
            continue;
        }

        current=current->next;



    }while(!charIsEmpty(opStack)){
        out = strAppend(out, opPop(&opStack));
        out = strAppend(out, ' ');

    }


    if(out) {//trims any excess spacing
    charNode *c = out;
        charNode *last = NULL;
        while (c->next) {
            last = c;
            c = c->next; }
        if (c->ch == ' ') {
            if (last) {
                last->next = NULL;
                free(c); }
            else       {
                    free(out);
                    out = NULL; }

        }
        return out;
}
}

void convertToPostfix(){
    if(!validityCalc){
        printf("Please run option 2 first.\n");
        return;
    }
    printf("\n--- Infix to Postfix ---\n");
   eqNode *cur = equationList;
    int i = 1;
    while (cur) {//until current reaches null
        if (cur->isValid) {//can only convert valid equations
            if (!cur->postfixDone) {
                strFree(cur->postfix);
        cur->postfix= infixToPostfix(cur->infix);//converts each equation to postfix
        cur->postfixDone = 1;
    }
    printf("Equation %d -> ", i);
            strPrint(cur->postfix);
            printf("\n");
        }
     cur = cur->next;
     i++;
    }
}



double evaluatePostfix(charNode *postfix){
   numStack *valStack = NULL;
    charNode *cur   = postfix;

    while (cur) {
        char ch = cur->ch;

        if (ch == ' ') {
        cur = cur->next;
         continue; }

        if (isdigit(ch)) {//we are handling multiple digit numbers
            double num = 0;
            while (cur && isdigit(cur->ch)) {
                num = num * 10 + (cur->ch - '0');//converts the ascii to its actual integer value
                cur = cur->next;
            }
            numPush(&valStack, num);//once the full number is built we push
            continue;
        }

        if (isOperator(ch)) {//when we get to an operator we pop the top two numbers
            cur = cur->next;
            double right = numPop(&valStack);//first number popped is the right operand
            double left  = numPop(&valStack);
            double res   = 0;
            if      (ch=='+') res = left + right;
            else if (ch=='-') res = left - right;
            else if (ch=='*') res = left * right;
            else if (ch=='/') {
                if (right == 0) {
                    printf("ERROR: division by zero\n");
                    numFree(&valStack); return 0;
                }
                res = left / right;
            }
            else if (ch=='^') res = pow(left, right);
            numPush(&valStack, res);
            continue;
        }

        cur = cur->next;
    }

    double answer = numIsEmpty(valStack) ? 0 : numPop(&valStack);
    numFree(&valStack);
    return answer;
}


void evaluateEquations(){
     if (!validityCalc) {
            printf("Please run option 2 first.\n");
     return; }

    eqNode *current = equationList;
    while (current) {
        if (current->isValid && !current->postfixDone){ //checks if the postfix for this eq has been done or not
            strFree(current->postfix);
            current->postfix     = infixToPostfix(current->infix);
            current->postfixDone = 1;
        }
        current = current->next;
    }

    printf("\n--- Evaluation Results ---\n");
    current = equationList;
    int i = 1;
    while (current) {
        if (current->isValid) {
        current->result = evaluatePostfix(current->postfix);//evaluates results by finding the postfix using the function and the evaluating it using evaluatepostfix function



            printf("Equation No. %d -> %.2f\n", i, current->result);
        }
        current = current->next;
        i++;
    }
}

void printInvalidEquations(){
    if(!validityCalc)//makes sure that the equations have been checked or not if not it tells the use to run 2 wich is check validity for the eq
        {
        printf("Please run option 2 first.\n");
        return;
    }
    printf("\n--- Invalid Equations ---\n");
    eqNode *current = equationList;
    int i=1;
    int found = 0;
    while (current) {
        if (!current->isValid) {
            printf("Equation %d: ", i); strPrint(current->infix);  printf("\n");
            printf("  Reason: ");       strPrint(current->validityMsg); printf("\n");
            found = 1;
        }
        current = current->next; i++;
    }
    if (!found) printf("All equations are valid!\n");
}

//first pop of the stack (number) makes up th right leaf and the second one to the left leaf
//  then wgen we find an operator it becomes the parent/connection node
struct treeNode* buildExpressionTree(charNode *postfix){
    treeStack *ts  = NULL;
    charNode  *current = postfix;

    while (current) {
        if (current->ch == ' ') {
                current = current->next;
        continue; }

        if (isdigit(current->ch)) {
            charNode *numStr = NULL;
            while (current && isdigit(current->ch)) {
                numStr = strAppend(numStr, current->ch);
                current = current->next;
            }
            treePush(&ts, newTreeNode(numStr));
            strFree(numStr);
            continue;
        }

        if (isOperator(current->ch)) {
            charNode *opStr = strAppend(NULL, current->ch);
            current = current->next;
            treeNode *n = newTreeNode(opStr);
            strFree(opStr);
            n->right = treePop(&ts);
            n->left  = treePop(&ts);
            treePush(&ts, n);
            continue;
        }

        current = current->next;
    }

    if (treeIsEmpty(ts))
        return NULL;
    return treePop(&ts);
}
//inorder: Left, Root, Right (infix form)
void inorder(struct treeNode *root){
    if(!root)
        return;
    int isLeaf = (!root->left && !root->right);
    if(!isLeaf) printf("(");
    inorder(root->left);
        strPrint(root->value);
    printf("\n");
            inorder(root->right);
    if(!isLeaf) printf(")");
}

// postorder: Left, Right, Root    (postfix form)
void postorder(struct treeNode *root){
    if(!root)
        return;
    postorder(root->left);
    postorder(root->right);
    strPrint(root->value);
    printf("\n");
}

// preorder: Root, Left, Right (prefix form)
void preorder(struct treeNode *root){
    if(!root) return;
    strPrint(root->value);
printf("\n");
    preorder(root->left);
    preorder(root->right);
}


void expressionTreeOption(){
    if(!validityCalc){
        printf("Please run option 2 first.\n");
        return;
    }
    printf("Enter equation number (1-%d): ", equationCount);
    int num;
    scanf("%d", &num);

    if(num < 1 || num > equationCount){
        printf("Invalid equation number.\n");
        return;
    }

     eqNode *eq = getEquation(num - 1);
    if(!eq){
        printf("Equation No. %d is not found:\n", num);
        return;
    }
    if (!eq->isValid) {
        printf("Equation No. %d is invalid: ", num);
        strPrint(eq->validityMsg); printf("\n");
        return;
    }

    if (!eq->postfixDone) {
        strFree(eq->postfix);
        eq->postfix= infixToPostfix(eq->infix);
        eq->postfixDone = 1;
    }

    struct treeNode *root = buildExpressionTree(eq->postfix);
    if(root == NULL){ printf("Could not build tree.\n"); return; }

    printf("\n--- Expression Tree for Equation No. %d ---\n", num);
    printf("a) Inorder   (infix)  : ");
    inorder(root);
    printf("\n");

    printf("b) Postorder (postfix): ");
    postorder(root);
    printf("\n");

    printf("c) Preorder  (prefix) : ");
    preorder(root);
    printf("\n");

    freeTree(root);
}


void writeOutputFile(){
    if(!validityCalc){
        printf("Please run option 2 first.\n");
        return;
    }

   eqNode *current = equationList;
    while (current) {
        if (current->isValid) {
            if (!current->postfixDone) {
                strFree(current->postfix);
                current->postfix     = infixToPostfix(current->infix);
                current->postfixDone = 1;
            }
            current->result = evaluatePostfix(current->postfix);
        }
        current = current->next;
    }
    FILE *out = fopen("output.txt", "w");
    if(out == NULL){ printf("ERROR: cannot create output.txt\n"); return; }

    fprintf(out, "============================================\n");
    fprintf(out, "            Calculator Results\n");
    fprintf(out, "============================================\n\n");

     current = equationList;
    int i = 1;
    while (current) {
        fprintf(out, "Equation No. %d :", i);
        strFPrint(out, current->infix);
        fprintf(out, "\n");

        if(current->isValid){
            fprintf(out, "  Status  : valid\n");
            fprintf(out, "  Postfix : \n");
            strFPrint(out, current->postfix);
            fprintf(out, "\n");
            fprintf(out, "  Result  : %.2f\n", current->result);
            }
         else {
            fprintf(out, "  Status  : invalid\n");
            fprintf(out, "  Reason  : \n");
            strFPrint(out, current->validityMsg);
            fprintf(out, "\n");
        }
        fprintf(out, "\n");
        current=current->next;
        i++;
    }

    fclose(out);
    printf("Results written to output.txt\n");
}

void printMenu(){
    printf("\n========================================\n");
    printf("  COMP2421 Calculator System\n");
    printf("========================================\n");
    printf("  1. Read equations from file\n");
    printf("  2. Check validity of equations\n");
    printf("  3. Convert valid equations to postfix\n");
    printf("  4. Evaluate postfix expressions\n");
    printf("  5. Print invalid equations\n");
    printf("  6. Expression tree\n");
    printf("  7. Write results to output.txt\n");
    printf("  8. Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}




