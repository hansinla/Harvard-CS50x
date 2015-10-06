node* cursor = head;
while(cursor != NULL)
{
    // do something
    cursor = cursor->next;
}

// TRIES

typedef struct node
{
    bool is_word;
    struct node* children[27];

} node;

node* root;

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;

} node;

node* hashtable[26];


//////////////////
node* node1 = malloc(sizeof(node));
    node* node2 = malloc(sizeof(node));
    node1->word = "Hello";
    node2->word = "World";
    node1->next = node2;
    
    node* new_node = malloc(sizeof(node));
    fscanf(file, "%s", new_node->word);
    
    //hashfunction
    
    
    
    /////////////////////////////////
    
    unsigned char c = word[i];
            if (c != '\n')
            {
                c = tolower(c);
            }
