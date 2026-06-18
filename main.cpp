#include <bits/stdc++.h>
using namespace std;

struct node
{
    char data;
    node*left;
    node*right;

    node(char val)
    {
        data=val;
        left=NULL;
        right=NULL;
    }
};

struct nodeCNF 
{
    string data;   
    nodeCNF* left;
    nodeCNF* right;

    nodeCNF(string val) 
    {
        
        data=val;
        left=NULL;
        right=NULL;
    } 
};

vector<vector<int>> readfile(string filepath) 
{
    fstream file(filepath, ios::in);

    if (!file.is_open()) 
    {
        cout << "Error: Cannot open file " << filepath << endl;
        return {};
    }

    vector<vector<int>> v;
    string line;

    while (getline(file, line)) 
    {
        if (line.empty() || line[0] == 'p' || line[0] == 'c')
            continue;

        vector<int> row;
        stringstream sinput(line);
        int num;
        while (sinput >> num) 
        {
            if (num == 0) break;
            row.push_back(num);
        }

        v.push_back(row);
    }

    file.close();
    return v;
}
//task1 -------------------------------------------------------------------------------
int priority(char c)
{
    switch(c)
    {
       
        case '>':
            return 1;
        case '+':
            return 2;
        case '*':
            return 3;
        case '~':
            return 4;
        default:
            return -1;

    }
}//priority function 

int isOperator(char c)
{
    if(c == '~' || c == '+' || c == '*' || c == '>')//four of the symbols are there
        return 1;
    return 0;

}

string infixtoprefix(string str)
{
    string ans="";//to hold the result
    
    stack<char> s;

    reverse(str.begin(),str.end());//reversing 

    for(int i=0;i<str.size();i++)
    {
       if(str[i]=='(')
            str[i]=')';
        else if(str[i]==')')
            str[i]='(';
    
    }//swapping ( and )the algo is okay???

    for(int i=0;i<str.size();i++)
    {   
        char c=str[i];
        if(isalnum(c))
            ans+=c;
        else if(c=='(')
            s.push(c);
        else if(c==')')
        {
            while(!s.empty() && s.top()!='(')
            {
                ans+=s.top();
                s.pop();
            
            }
            if (!s.empty())
                 s.pop();
        }
        else if(isOperator(c))
        {
            if(c=='>'||c=='~')
            {
                while(!s.empty()&& priority(c)<=priority(s.top()))
                {
                    ans+=s.top();
                    s.pop();
                }
            }//right associative
            else
            {
                while(!s.empty() && priority(c)<priority(s.top()))
                {
                    ans+=s.top();
                    s.pop();
                }
            }
            s.push(c);
        }//left associative
    
    }

    while(!s.empty())
    {
        ans+=s.top();
        s.pop();
    }//for remaining elements

    reverse(ans.begin(),ans.end());//reversing
     
    return ans;

}

string clauseToPrefix(vector<int>& clause) 
{
    string s = "(+";
    for (int lit : clause) 
    {
        s += " ";
        if (lit < 0)
            s += "~" + to_string(-lit);  // negative numbers → ~N
        else
            s += to_string(lit);          // positive numbers stay
    }
    s += ")";
    return s;
}

string cnfToPrefix(vector<vector<int>>& cnf) 
{
    if (cnf.empty()) return "";

    string prefix = clauseToPrefix(cnf[0]);

    for (size_t i = 1; i < cnf.size(); i++) 
    {
        string nextClause = clauseToPrefix(cnf[i]);
        prefix = "(* " + prefix + " " + nextClause + ")";
    }

    return prefix;
}
//task2----------------------------------------------------------------------------------
node * buildParseTreeChar(string prefix, int &index) 
{
    if (index >= prefix.size())
        return NULL;

    char c = prefix[index];
    index++;

    node* current = new node(c);

    if (c == '~') 
    {               // unary operator
        current->right = buildParseTreeChar(prefix, index);
    } 
    else if (c == '*' || c == '+' || c == '>') 
    { // binary operators
        current->left = buildParseTreeChar(prefix, index);
        current->right = buildParseTreeChar(prefix, index);
    }

    return current;
}

nodeCNF* buildCNFParseTree(vector<vector<int>>& v, int index) 
{
    if (v.empty() || index < 0)
         return NULL;

    vector<int> &clause = v[index];
    nodeCNF* clauseNode = NULL;

    if (!clause.empty()) 
    {
        // first literal
        int lit = clause[0];
        nodeCNF* litNode = NULL;

        if (lit < 0) 
        {                    // ~ node
            litNode = new nodeCNF(to_string(-lit));
            nodeCNF* neg = new nodeCNF("~");
            neg->right = litNode;
            litNode = neg;
        }
        else 
        {
            litNode = new nodeCNF(to_string(lit));
        }

        nodeCNF* current = litNode;

        // rest of clause ORed
        for (int j = 1; j < clause.size(); j++) 
        {
            int lit2 = clause[j];
            nodeCNF* nextLit = NULL;
            if (lit2 < 0) 
            {
                nextLit = new nodeCNF(to_string(-lit2));
                nodeCNF* neg = new nodeCNF("~");
                neg->right = nextLit;
                nextLit = neg;
            } 
            else 
            {
                nextLit = new nodeCNF(to_string(lit2));
            }

            nodeCNF* or_node = new nodeCNF("+");
            or_node->left = current;
            or_node->right = nextLit;
            current = or_node;
        }

        clauseNode = current;
    }

    if (index - 1 >= 0) 
    {   // recurse backwards
        nodeCNF* restTree = buildCNFParseTree(v, index - 1);
        nodeCNF* andNode = new nodeCNF("*");
        andNode->left = restTree;       
        andNode->right = clauseNode;    
        return andNode;
    } 
    else 
    {
        return clauseNode;              // first clause becomes leaf
    }
}
//task3-----------------------------------------------------------------------------------
void printinfix_char(node *current)
{
    if(current==NULL)
        return;

     if(current->data == '*' || current->data == '+' || current->data == '>')
    {
        cout << "(";                       
        printinfix_char(current->left);   
        cout << current->data;             
        printinfix_char(current->right);  
        cout << ")";                       
    }

    else if(current->data == '~') 
    {
        cout << "~";
        printinfix_char(current->right); 
    }

    else
    {
        cout<< current->data;
    }
}

void printInfix_cnf(nodeCNF* current) 
{
    if (current == nullptr) return;

    if (current->data == "*" || current->data == "+") 
    {
        cout << "(";
        printInfix_cnf(current->left);
        cout << current->data;
        printInfix_cnf(current->right);
        cout << ")";
    }

    else if (current->data == "~") 
    {
        cout << "~";
        printInfix_cnf(current->right);
    }

    else 
    {
        cout << current->data;
    }
}
//task4-----------------------------------------------------------------------------------
int heightChar(node* root) {
    if (root == NULL)
        return 0;

    int leftheight = heightChar(root->left);
    int rightheight = heightChar(root->right);

    return 1 + max(leftheight, rightheight);
}

int heightCNF(nodeCNF* root) {
    if (root == NULL)
        return 0;

    int leftheight = heightCNF(root->left);
    int rightheight = heightCNF(root->right);

    return 1 + max(leftheight, rightheight);
}
//task5-----------------------------------------------------------------------------------
void getatoms(node *current,set<char> &atomset)
{   
    if(current==NULL)
        return;
    
    if(current->data != '*' && current->data != '+' && current->data != '>' && current->data != '~')
    {
        atomset.insert(current->data);
    }

    getatoms(current->left,atomset);
    getatoms(current->right,atomset);
}

bool evaluate_string(node* current, map<char,bool> &truthvalues) {
    if (current == nullptr)
        return false;

    if (current->left == nullptr && current->right == nullptr)
        return truthvalues[current->data];

    if (current->data == '~')
        return !evaluate_string(current->right, truthvalues);

    bool left = evaluate_string(current->left, truthvalues);
    bool right = evaluate_string(current->right, truthvalues);

    switch (current->data) 
    {
        case '*':
            return left && right;
        case '+':
            return left || right;
        case '>':
            return (!left) || right;
        default:
            return false;
    }
}

void gettruthvalue_char(node *root)
{
     set<char> atomset;
     getatoms(root,atomset);

     if(atomset.size()>20)
     {
        cout<<"The truth table is too large to generate"<<endl;
        return;
     }
     map<char,bool> truthvalues;

     vector<char> atoms(atomset.begin(), atomset.end());
     int n = atoms.size();
     cout << "Truth table:\n";
     for(char a: atoms) cout << a << " ";
     cout << "| Result\n";
     cout << string(2*n + 9, '-') << "\n";

     for(int i=0;i<(1<<n);i++)
     {
         for(int j=0;j<n;j++)
         {
             bool val = i & (1<< (n-j-1));
             truthvalues[atoms[j]] = val;
             cout << val << " ";
         }
         bool val = evaluate_string(root, truthvalues);
         cout << "| " << val << "\n";
     }
}

void collectLeafNodes(nodeCNF* current, unordered_set<string>& leaves) 
{
    if (current == NULL) return;

    if (current->left == NULL && current->right == NULL) 
    {
        leaves.insert(current->data);
        return;
    }

    collectLeafNodes(current->left, leaves);
    collectLeafNodes(current->right, leaves);
}

bool evaluateCNF(nodeCNF* current,unordered_map<string,bool> &truthMap) 
{
    if (current == NULL) return true;

    if (current->left == NULL && current->right == NULL)
        return truthMap.at(current->data);

    if (current->data == "~")
        return !evaluateCNF(current->right,truthMap);

    if (current->data == "*")
        return evaluateCNF(current->left,truthMap) && evaluateCNF(current->right,truthMap);

    if (current->data == "+")
        return evaluateCNF(current->left,truthMap) || evaluateCNF(current->right,truthMap);
    
    return false;
}

void gettruthvalue_cnf(nodeCNF* root) 
{
    unordered_set<string> leaves;
    collectLeafNodes(root, leaves);

    vector<string> atoms(leaves.begin(), leaves.end());
    int n = atoms.size();

    if(n>20)
    {
        cout<<"The truth table is too large to generate"<<endl;
        return;
    }

    cout << "Truth table:\n";
    for (auto &a: atoms) cout << a << " ";
    cout << "| Result\n";
    cout << string(2*n + 9, '-') << "\n";

    for(int i=0;i<(1<<n);i++)
    {
        unordered_map<string,bool> truthMap;
        for(int j=0;j<n;j++)
        {
            bool val = i & (1 << (n-j-1));
            truthMap[atoms[j]] = val;
            cout << val << " ";
        }
        bool val = evaluateCNF(root, truthMap);
        cout << "| " << val << "\n";
    }
}
//task6-----------------------------------------------------------------------------------
void deleteTree(node* root) 
{
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

node* copyTree(node* root) 
{
    if (root == NULL) return NULL;
    node* n = new node(root->data);
    n->left = copyTree(root->left);
    n->right = copyTree(root->right);
    return n;
}

node* impl_free(node* root) 
{
    if (root == NULL) 
        return NULL;
    root->left = impl_free(root->left);
    root->right = impl_free(root->right);

    if (root->data == '>') 
    {
        node* a = root->left;
        node* b = root->right;
        delete root; // The old '>' node is now deleted.

        node* notA = new node('~');
        notA->right = a;
        node* orNode = new node('+');
        orNode->left = notA;
        orNode->right = b;
        return orNode;
    }
    return root;
}

node* nnf(node* root) {
    if (root == NULL) 
        return NULL;

    if (root->data == '~') 
    {
        node* c = root->right;

        // Rule: ~~A -> A
        if (c->data == '~') 
        {
            node* grandChild = c->right;
            delete root; // delete outer ~
            delete c;    // delete inner ~
            return nnf(grandChild);
        }
        // Rule: ~(A + B) -> (~A * ~B)
        else if (c->data == '+')
        {
            node* a = c->left;
            node* b = c->right;
            delete root; // delete ~
            delete c;    // delete +

            node* andNode = new node('*');
            node* na = new node('~'); na->right = a;
            node* nb = new node('~'); nb->right = b;
            andNode->left = nnf(na);
            andNode->right = nnf(nb);
            return andNode;
        }
        // Rule: ~(A * B) -> (~A + ~B)
        else if (c->data == '*') 
        {
            node* orNode = new node('+');
            node* a = c->left;
            node* b = c->right;
            delete root; // delete ~
            delete c;    // delete *
            
            node* na = new node('~'); na->right = a;
            node* nb = new node('~'); nb->right = b;
            orNode->left = nnf(na);
            orNode->right = nnf(nb);
            return orNode;
        } 
        else 
            return root;
    }

    root->left = nnf(root->left);
    root->right = nnf(root->right);
    return root;
}

node* cnf(node* root);

node* distr(node* A, node* B) {
    // Rule: (A1 * A2) + B -> (A1 + B) * (A2 + B)
    if (A->data == '*') 
    {
        node* a1 = A->left;
        node* a2 = A->right;
        delete A; 

        node* new_left_or = new node('+');
        new_left_or->left = a1;
        new_left_or->right = copyTree(B); // B is used twice, so copy for the first use

        node* new_right_or = new node('+');
        new_right_or->left = a2;
        new_right_or->right = B;

        node* andNode = new node('*');
        andNode->left = cnf(new_left_or);
        andNode->right = cnf(new_right_or);
        return andNode;
    }
    // A + (B1 * B2) -> (A + B1) * (A + B2)
    if (B->data == '*') 
    {
        node* b1 = B->left;
        node* b2 = B->right;
        delete B; 

        node* new_left_or = new node('+');
        new_left_or->left = copyTree(A); 
        new_left_or->right = b1;

        node* new_right_or = new node('+');
        new_right_or->left = A; 
        new_right_or->right = b2;
        
        node* andNode = new node('*');
        andNode->left = cnf(new_left_or);
        andNode->right = cnf(new_right_or);
        return andNode;
    }

    //  A + B (no distribution needed)
    node* orNode = new node('+');
    orNode->left = A;
    orNode->right = B;
    return orNode;
}

node* cnf(node* root) 
{
    if (root == NULL) 
        return NULL;
    root->left = cnf(root->left);
    root->right = cnf(root->right);

    if (root->data == '+') 
    {
        node* new_tree = distr(root->left, root->right);
        delete root; 
        return new_tree;
    }
    return root;
}

void collectClauses(node* root, vector<vector<string>>& clauses) {
    if (root == NULL) return;

    if (root->data == '*') 
    {
        collectClauses(root->left, clauses);
        collectClauses(root->right, clauses);
    } 
    else 
    {
        vector<string> clause;
        queue<node*> q;
        q.push(root);

        while (!q.empty()) 
        {
            node* cur = q.front(); q.pop();
            if (cur == NULL) continue;

            if (cur->data == '+') 
            {
                q.push(cur->left);
                q.push(cur->right);
            } 
            else if (cur->data == '~') 
            {
                if (cur->right)
                    clause.push_back("~" + string(1, cur->right->data));
            } 
            else {
                clause.push_back(string(1, cur->data));
            }
        }
        clauses.push_back(clause);
    }
}

vector<vector<string>> convertToCNF(node* root) 
{
    node* cnf_tree = copyTree(root);

    cnf_tree = impl_free(cnf_tree);
    cnf_tree = nnf(cnf_tree);
    cnf_tree = cnf(cnf_tree);

    cout<<"CNF form:"<<endl;
    printinfix_char(cnf_tree);

    vector<vector<string>> result;
    collectClauses(cnf_tree, result);

    deleteTree(cnf_tree);
    return result;
}
//task7-----------------------------------------------------------------------------------
bool checkvalidity_cnffile(vector<vector<int>> &v) 
{
    int validCount = 0, invalidCount = 0;

    for (int i = 0; i < v.size(); i++) 
    {
        vector<int> row = v[i];
        unordered_set<int> s(row.begin(), row.end());

        bool val = false;
        for (int j = 0; j < row.size(); j++) 
        {
            if (s.count(-row[j])) 
            {
                val = true;
                break;
            }
        }

        if (val)
            validCount++;
        else
            invalidCount++;
    }

    cout << "Valid clauses: " << validCount << endl;
    cout << "Invalid clauses: " << invalidCount << endl;

    return invalidCount == 0;
}

bool checkvalidity_string(vector<vector<string>> &v) 
{
    int validCount = 0, invalidCount = 0;

    for (int i = 0; i < v.size(); i++) 
    {
        vector<string> row = v[i];
        unordered_set<string> s(row.begin(), row.end());

        bool val = false;
        for (int j = 0; j < row.size(); j++) 
        {
            string lit = row[j];
            string neg = (!lit.empty() && lit[0] == '~') ? lit.substr(1) : "~" + lit;

            if (s.count(neg)) 
            {
                val = true;
                break;
            }
        }

        if (val)
            validCount++;
        else
            invalidCount++;
    }

    cout << "Valid clauses: " << validCount << endl;
    cout << "Invalid clauses: " << invalidCount << endl;

    return invalidCount == 0;
}

int main()
{
    int choice=0;
    cout<<"Enter 0 for custom propostional formula and 1 for using cnf file"<<endl;
    cin>>choice;

    switch(choice)
    {
        case 0:
        {
            string input;
            cout<<"Enter the propostional string :"<<endl;
            cin.ignore();
            getline(cin,input);//input has propostional string

            //task1
            cout<<"Prefix expression:"<<endl;
            string prefix=infixtoprefix(input);
            cout<<prefix<<endl;
            //task2
            int i=0;
            node *root=buildParseTreeChar(prefix,i);
            //task3
            cout<<"Inorder traversal of tree:"<<endl;
            printinfix_char(root);
            cout<<endl;
            //task4
            cout<<"Height of the parse tree: ";
            cout<<heightChar(root)<<endl;
            //task5
            cout<<"Truth table of the given expression:"<<endl;
            gettruthvalue_char(root);
            //task6
            vector<vector<string>> result=convertToCNF(root);
            cout<<endl;
            //task7
            bool validity=checkvalidity_string(result);
            cout<< ((validity==0)?"The given expression is not valid":"The given expression is valid");
            break;
        }
        case 1:
        {
            string filepath;//using the cnf file input
            cout << "Enter the filepath: " << endl;
            cin >> filepath;

            vector<vector<int>> v_cnf = readfile(filepath);
            if(v_cnf.empty())
            {
                return 0;
            }
            //task1
            string prefix = cnfToPrefix(v_cnf);
            cout<<"Prefix expression:"<<endl;
            cout << prefix << endl;
            //task2
            nodeCNF *root=buildCNFParseTree(v_cnf,v_cnf.size()-1);
            //task3
            cout<<"Inorder traversal of tree:"<<endl;
            printInfix_cnf(root);
            cout<<endl;
            //task4
            cout<<"Height of the parse tree: ";
            cout<<heightCNF(root)<<endl;
            //task5
            cout<<"Truth table of the given expression:"<<endl;
            gettruthvalue_cnf(root);
            //task6
            cout<<"The expression is already in CNF form.The above traversal shows the complete formula"<<endl;
            //task7
            bool validity=checkvalidity_cnffile(v_cnf);
            cout<< ((validity==0)?"The given expression is not valid":"The given expression is valid");
            break;
        }
        default:
            cout<<"Please enter a valid number"<<endl;
            break;
    }

    return 0;
}
