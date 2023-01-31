/*
  CSC A48 - Assignment 2 - BSTs, Traversals, a tiny Sequencer

  For this assignment you will be implementing a fully working
  BST. The goal is for you to gain practice with one of the most
  common and more useful data structures you can find.

  The data we will store in the BST corresponds to musical notes
  from a little song, and we have provided (in a separate .c
  file) a very small implementation of a program to making 
  sounds from each of these musical notes.

  ** YOU DO NOT NEED TO look at that code
  ** Everything in 'NoteSynth.c' is provided
  ** just so you can listen to the data in your
  ** BST - but you do not need to look at it for
  ** this assignment, and you're not expected 
  ** to learn or understand that code.

  You can, however, learn from it if you're curious about how
  sound can be synthesized. Don't spend time on that unless you
  have completed everything else.

  Read carefully the comments and descriptions in this starter
  code, as they constitute the specification of what you need
  to do to complete the assignment.

  - Like A1, we will provide a test driver for you to test your
    code. Also like A1, that test driver contains a subset of the
    tests we will be running. You are responsible for running 
    additional tests to ensure your BST works properly!

    Updated Feb. 2022 (c) F. Estrada
*/

#include<stdio.h>
#include<stdlib.h>
#include"NoteSynth.c"

typedef struct BST_Node_Struct
{
    // This compound type stores all data for one node of the
    // BST. Since the BST is used to store musical notes, 
    // the data contained here represents one note from a
    // musical score:
    // freq: A double-precision floating point value, 
    //       corresponding to the frequency (pitch) of the note
    // bar: Musical scores are divided into 'bars' (which you can
    //      see are actually separated by a vertical bar!). This
    //      value indicates which bar the note happens in. The
    //      first bar in the musical score is 0
    // index: Position of the note within the bar, from 0 (at the
    //        beginning of the bar) to 1 (at the end of the bar)
    // key: A unique identifier (remember we discussed BST nodes
    //      should have unique keys to identify each node). We
    //      want our nodes to store notes in the order in which
    //      they occur in the song. So, the key identifier is
    //      created as: key = (10.0*bar)+index
    //      NOTE: This means only one note can have a specific
    //            bar,index value. If two notes should happen
    //            at the same time in the song, we make the
    //            index of one of them a tiny bit bigger or
    //            a tiny bit smaller than the other one so
    //            their keys are very close, but not identical.

    double key;
    double freq;
    int bar;
    double index;

    /*** TO DO:
     * Complete the definition of the BST_Node_Struct
     ***/
    struct BST_Node_Struct *right;
    struct BST_Node_Struct *left;
} BST_Node;

BST_Node *find_parent(BST_Node *root,int bar,double index);
BST_Node *BST_search(BST_Node *root, int bar, double index);
void BST_swap(BST_Node *root);
int bar_num(BST_Node *root);
int bar_array(BST_Node *root, int array[], int i, int max);
void change_bar_index(BST_Node *root,int array[],int bar_num);
void change_all(BST_Node *root, int array[], int bar_num);


BST_Node *newBST_Node(double freq, int bar, double index)
{
    /* 
     * This function creates and initializes a new BST_Node 
     * for a note with the given position (bar:index) and
     * the specified frequency. The key value for the node
     * is computed here as
     * 
     *      (10.0*bar)+index
     */

    /*** TO DO:
     * Complete this function to allocate and initialize a
     * new BST_Node. You should make sure the function sets
     * initial values for the data correctly.
     ****/
    double key=(10.0*bar)+index;
    BST_Node *new=(BST_Node *)calloc(1,sizeof(BST_Node));
    new->freq=freq;
    new->bar=bar;
    new->index=index;
    new->key=key;
    new->right=NULL;
    new->left=NULL;
    return new;
}



BST_Node *BST_insert(BST_Node *root, BST_Node *new_node)
{
    /*
     * This function inserts a new node into the BST. The
     * node must already have been initialized with valid
     * note data, and must have its unique key.
     * 
     * The insert function must check that no other node
     * exists in the BST with the same key. If a node with
     * the same key exists, it must print out a message
     * using the following format string
     * 
     * printf("Duplicate node requested (bar:index)=%d,%lf, it was ignored\n",....);
     * (of course you need to provide the relevant variables to print)
     * 
     * And it must return without inserting anyting in the
     * BST.
     */
    
    /*** TO DO:
     * Implement the insert function so we can add notes to the tree!
     ****/
    int bar=new_node->bar;
    double index=new_node->index; 
    double key=(10.0*bar)+index;
    if(BST_search(root, bar, index)!=NULL)
    {
        printf("Duplicate node requested (bar:index)=%d,%lf, it was ignored\n",bar,index);//问题
        return root;
    }
    if(root==NULL)
    {
        return new_node;
    }
    if(key<root->key)
    {
        root->left=BST_insert(root->left,new_node);
    }
    if(key>root->key)
    {
        root->right=BST_insert(root->right,new_node);
    }
    return root;
}

BST_Node *BST_search(BST_Node *root, int bar, double index)
{
    /*
     * This function searches the BST for a note at the
     * specified position. If found, it must return a
     * pointer to the node that contains it. 
     * Search has to happen according to the BST search
     * process - so you need to figure out what value to
     * use during the search process to decide which branch
     * of the tree to search next.
     */
    
    /*** TO DO:
     * Implement this function
     ****/
    double key=(10.0*bar)+index;
    if(root == NULL)
    {
        return NULL;
    }
    if(root->key==key)
    {
        return root;
    }
    else if(root->key<key)
    {
        return BST_search(root->right,bar,index);
    }
    else
    {
        return BST_search(root->left,bar,index);
    }
}

BST_Node *find_successor(BST_Node *right_child_node)
{
    /*
     * This function finds the successor of a node by 
     * searching the right subtree for the node that
     * is most to the left (that will be the node
     * with the smallest key in that subtree)
     */
    
    /*** TO DO:
     * Implement this function
     ****/

    //问题：如果没有subtree怎么办
    if(right_child_node==NULL || right_child_node->right==NULL)
    {
        return NULL;
    }
    BST_Node *s=right_child_node->right;
    while(s->left!=NULL)
    {
        s=s->left;
    }
    return s;
}




BST_Node *BST_delete(BST_Node *root, int bar, double index)
{
    /*
     * Deletes from the BST a note at the specified position.
     * You must implement the three cases of BST deletion
     * we discussed in class. Make sure the function can
     * remove a note at any position without breaking the
     * tree!
     */
    
    /*** TO DO:
     * Implement this function
     ****/
    
    BST_Node *p=BST_search(root, bar, index);
    BST_Node *parent=find_parent(root, bar, index);
    BST_Node *r;
    BST_Node *s;
    BST_Node *sp;
    if(root==NULL || p==NULL)
    {
        return root;
    }

    int where=-1;
    if(parent!=NULL)
    {
        if(parent->left==p)
        {
            where=0;
        }
        if(parent->right==p)
        {
            where=1;
        }
    }

    if(p->right==NULL && p->left==NULL)//无小孩
    {
        free(p);
        if(where==-1)
        {
            return NULL;
        }
        if(where ==0)
        {
            parent->left=NULL;
        }
        if(where==1)
        {
            parent->right=NULL;
        }
        return root;
    }
    else if(p->right==NULL)//只有左小孩
    {
        if(where==-1)
        {
            r=p->left;
            free(p);
            return r;
        }
        if(where==0)
        {
            parent->left=p->left;
        }
        if(where==1)
        {
            parent->right=p->left;
        }
        free(p);
        return root;
    }
    else if(p->left==NULL)//只有右小孩
    {
        if(where==-1)
        {
            r=p->right;
            free(p);
            return r;
        }
        if(where==0)
        {
            parent->left=p->right;
        }
        if(where==1)
        {
            parent->right=p->right;
        }
        free(p);
        return root;
    }
    else //两个小孩
    {
        s=find_successor(p);//s肯定存在
        p->freq=s->freq;
        p->bar=s->bar;
        p->index=s->index;
        p->key=s->key;
        sp=find_parent(p->right, s->bar, s->index);
        if(sp==NULL)
        {
            p->right=s->right;
        }
        else
        {
            sp->left=s->right;
        }
        free(s);
        return root;
    }
}

void BST_makePlayList(BST_Node *root)
{
    /*
     * This function does an in-order traversal of the BST to
     * generate an ordered list of notes to be played. Each
     * note is added to a linked-list (already implemented,
     * you only need to call the insert function) and the 
     * play list is then playable using the code in NoteSynth.c
     * 
     * To insert a note, you need to call the function provided
     * in NoteSynth.c:
     * 
     * playlist_head=playlist_insert(playlist_head,freq,bar,index);
     * 
     * playlist_head is a GLOBAL variable declared in NoteSynth.c
     * precisely for this purpose. Don't worry about initializing
     * it. It's set to NULL.
     * 
     * playlist_insert() takes the frequency, bar, and index, and
     * adds the note to the the *end* of the list - so notes 
     * have to be added in order - hence the in-order traversal
     * this function has to do.
     */
    
    /**** TO DO:
     * Implement this function
     ****/
    if(root==NULL)
    {
        return;
    }
    BST_makePlayList(root->left);
    playlist_head=playlist_insert(playlist_head,root->freq,root->bar,root->index);
    BST_makePlayList(root->right);

}

void BST_inOrder(BST_Node *root, int depth)
{
    /*
     * This function performs an in-order traversal of the BST
     * and prints out the note information for each note
     * using this print statement:
     * 
     *  printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",...);
     *
     * Obviously, you must provide the bar, index, and frequency
     * of the note that needs to be printed to complete the
     * statement - we're just giving you the formatting string.
     * 
     * The depth value is increased by 1 for each recursive call
     * so when you print, you can see at what level each node
     * is located! (this should help you debug your code by
     * making it easier to check the shape of your BST).
     */
    
    /*** TO DO:
     * Implement this function
     ****/
    if(root==NULL)
    {
        return;
    }
    depth++;
    BST_inOrder(root->left,depth);
    printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",depth-1,root->bar,root->index,root->freq);
    BST_inOrder(root->right,depth);
} 

void BST_preOrder(BST_Node *root, int depth)
{
    /*
     * This function performs an pre-order traversal of the BST
     * and prints out the note information for each note
     * using this print statement:
     * 
     *  printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",...);
     *
     * Obviously, you must provide the bar, index, and frequency
     * of the note that needs to be printed to complete the
     * statement - we're just giving you the formatting string.
     * 
     * The depth value is increased by 1 for each recursive call
     * so when you print, you can see at what level each node
     * is located! (this should help you debug your code by
     * making it easier to check the shape of your BST).
     */
    
    /*** TO DO:
     * Implement this function
     ****/
    if(root==NULL)
    {
        return;
    }
    depth++;
    printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",depth-1,root->bar,root->index,root->freq);
    BST_preOrder(root->left,depth);
    BST_preOrder(root->right,depth);
}

void BST_postOrder(BST_Node *root,int depth)
{
    /*
     * This function performs an post-order traversal of the BST
     * and prints out the note information for each note
     * using this print statement:
     * 
     *  printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",...);
     *
     * Obviously, you must provide the bar, index, and frequency
     * of the note that needs to be printed to complete the
     * statement - we're just giving you the formatting string.
     * 
     * The depth value is increased by 1 for each recursive call
     * so when you print, you can see at what level each node
     * is located! (this should help you debug your code by
     * making it easier to check the shape of your BST).
     */
    
    /*** TO DO:
     * Implement this function
     ****/
    if(root==NULL)
    {
        return;
    }
    depth++;
    BST_postOrder(root->left,depth);
    BST_postOrder(root->right,depth);
    printf("Depth=%d, Bar:Index (%d:%f), F=%f Hz\n",depth-1,root->bar,root->index,root->freq);
} 

void delete_BST(BST_Node *root)
{
    /*
     * This function deletes the BST and frees all memory used for
     * nodes in it. Recall that there is a specific order in which
     * this needs to be done! (consult the Unit 4 notes as needed)
     */
    
    /**** TO DO:
     * Implement this function
     ****/
    if(root==NULL)
    {
        return;
    }
    delete_BST(root->left);
    delete_BST(root->right);
    free(root);
}

BST_Node *reverseSong(BST_Node *root)
{
    /*
     * This function will reverse the song currently stored in our
     * tree - that means the song will play *backwards*.
     * 
     * For instance, if the song contains notes
     *   
     *  A B C D E F G     in that order
     *  
     *  after reversing it should play
     * 
     *  G F E D C B A     in that order
     * 
     *  In terms of the bar and index of each note in the input tree,
     *  here are some pieces of information you will need to figure
     *  out what the new bar and index of each note will be:
     * 
     *  If the maximum bar for a note in the input tree is MAX_BAR
     *  and the minimum (smallest) bar for a note in the input tree
     *  is MIN_BAR
     * 
     *  A note with bar=MIN_BAR will end up with bar=MAX_BAR
     *  A note with bar=MAX_BAR will end up with bar=MIN_BAR
     *
     *  The index for any note must be between 0 and 1. If the
     *  original note had index=0, it will end up with index=1 
     *  if the original note had index=1, it will end up with index=0 
     * 
     *  That's all the information you need to figure out how to
     *  generate the notes for the backwards version of the song.
     * 
     *  It's up to you how to modify the tree so that the resulting
     *  song plays backwards. *There's many different ways to do this*
     *  As ever, I recommend you solve this first *on paper* and
     *  only start coding once you know what you have to do to solve this
     *  part.
     * 
     */
    
    /*** TO DO:
     * Implement this function! (Crunchy!)
     ****/
    int i;
    if(root==NULL)
    {
        return NULL;
    }
    int bar_total=bar_num(root);
    //bar_total is the maximum bar number
    int array[bar_total+1];//blc bar can be 0
    for(i=0;i<bar_total+1;i++)
    {
        array[i]=-1;
    }
    bar_array(root,array,0,bar_total+1);
    //0,1,2,4,6,-1,-1
    int bar=0;
    while(bar<bar_total+1 && array[bar]!=-1)
    {
        bar++;
    }
    //there are bar different bar numbers
    //now we need to find how big a specific root's bar is
    //and change that root's bar,index,key
    change_all(root,array,bar);
    BST_swap(root);
    return root;
}

/********************************************************************************************
 *      Add any helper functions you need for implementing BST_harmonize() just below this
 * comment block, and above BST_Harmonize itself!
 * ******************************************************************************************/
BST_Node *find_parent(BST_Node *root,int bar,double index)
{
    if(BST_search(root,bar,index)==NULL || root==NULL || BST_search(root,bar,index)==root)
    {
        return NULL;
    }
    double key=(10.0*bar)+index;
    if(BST_search(root->left,bar,index)==root->left|| BST_search(root->right,bar,index)==root->right)
    {
        return root;
    }
    else
    {  
        if(key<root->key)
        {
            return find_parent(root->left,bar,index);
        }
        else
        {
            return find_parent(root->right,bar,index);
        }
    }
}

int bar_num(BST_Node *root)
{
    if(root==NULL)
    {
        return 0;
    }

    while(root->right!=NULL)
    {
        root=root->right;
    }
    //printf("bar num is: %d\n",root->bar);//删掉
    return (root->bar);
}


int bar_array(BST_Node *root, int array[], int i, int max)
{
    
    if(root==NULL || i>=max)
    {
        return i;
    }
    
    i=bar_array(root->left,array,i,max);
    if(i==0)
    {
        array[i]=root->bar;
        i++;
    }
    else
    {
        if(array[i-1]!=root->bar)
        {
            array[i]=root->bar;
            i++;
        }
    }
    i=bar_array(root->right,array,i,max);
    return i;
}

// void bar_array(BST_Node *root, int array[], int i, int max)
// {
    
//     if(root==NULL)
//     {
//         //printf("when root is NULL, i is: %d\n",i);//删掉
//         return;
//     }
    
//     bar_array(root->left,array,i,max);
//     //printf("i=bar_array(root->left,array,i,max): i is: %d\n",i);//删掉
//     if(i==0)
//     {
//         array[i]=root->bar;
//         //printf("array[i] is: %d\n",array[i]);//删掉
//         i++;
//     }
//     else if(i<max)
//     {
//         if(array[i-1]!=root->bar)
//         {
//             array[i]=root->bar;
//             //printf("array[i] is: %d\n",array[i]);//删掉
//             i++;
//         }
//     }
//     bar_array(root->right,array,i,max);
//     //printf("i=bar_array(root->right,array,i,max): i is: %d\n",i);删掉
//     //return 0;
// }

void change_bar_index(BST_Node *root,int array[],int bar_num)
{
    int bar=root->bar;
    int i=0;
    while(array[i]!=bar)
    {
        i++;
    }
    root->bar=array[bar_num-i-1];
    //bar换好了
    root->index=1-(root->index);
    root->key=(10.0*root->bar)+root->index;
}

//需要把所有的node换一遍
void change_all(BST_Node *root, int array[], int bar_num)
{
    if(root==NULL)
    {
        return;
    }
    change_all(root->left,array,bar_num);
    change_bar_index(root,array,bar_num);
    change_all(root->right,array,bar_num);
}

void BST_swap(BST_Node *root)
{
    if(root==NULL)
    {
        return;
    }
    BST_swap(root->left);
    BST_swap(root->right);
    BST_Node *p;
    p=root->left;
    root->left=root->right;
    root->right=p;
}


//问题：bar从几开始


// void insert_new(BST_Node *root, int semitones, double time_shift, BST_Node *root_all)
// {
//     double frequency=root->freq;
//     int i=0;
//     while(i<100 && note_freq[i]!=frequency)
//     {
//         i++;
//     }
//     if(i==100 || i+semitones<0 || i+semitones>99)
//     {
//         return;//没找到，不用找了
//     }
//     frequency=note_freq[i+semitones];
//     double index=root->index+time_shift;
//     if(index<0 || index>=1)
//     {
//         return;
//     }
//     int bar=root->bar;
    
//     BST_Node *new=newBST_Node(frequency, bar, index);
//     BST_insert(root_all, new);
// }

// void help_harmonize(BST_Node *root, int semitones, double time_shift, BST_Node *root_all)
// {
//     if(root==NULL)
//     {
//         return;
//     }
//     help_harmonize(root->left,semitones,time_shift,root_all);
//     insert_new(root, semitones, time_shift, root_all);
//     help_harmonize(root->right,semitones,time_shift,root_all);
// }

//新建一个node，把node的pointer放到linked list里
//把pointer放到tree里

typedef struct harmonized
{
    BST_Node *p;
    struct harmonized *next;
}H_Node;


H_Node *new_H_Node(BST_Node *root, int semitones, double time_shift)
{
    double frequency=root->freq;
    int i=0;
    while(i<100 && note_freq[i]!=frequency)
    {
        i++;
    }
    if(i==100 || i+semitones<0 || i+semitones>99)
    {
        return NULL;//没找到，不用找了
    }
    frequency=note_freq[i+semitones];
    double index=root->index+time_shift;
    if(index<0 || index>=1)
    {
        return NULL;
    }
    int bar=root->bar;
    
    BST_Node *new=newBST_Node(frequency, bar, index);
    H_Node *new_H=(H_Node *)calloc(1,sizeof(H_Node));
    new_H->p=new;
    new_H->next=NULL;
    return new_H;
}

H_Node *insert_H_Node(H_Node *head, H_Node *new)
{
    if(head==NULL)
    {
        return new;
    }
    H_Node *p=head;
    while(p->next!=NULL)
    {
        p=p->next;
    }
    p->next=new;
    return head;
}

//traverse the tree, create H_nodes

H_Node *create_all_nodes(BST_Node *root,int semitones, double time_shift,H_Node *head)
{
    if(root==NULL)
    {
        return head;
    }
    head=create_all_nodes(root->left,semitones,time_shift,head);
    H_Node *new=new_H_Node(root, semitones, time_shift);
    head=insert_H_Node(head,new);
    head=create_all_nodes(root->right,semitones,time_shift,head);
    return head;
}

// void help_harmonize(BST_Node *root, int semitones, double time_shift, BST_Node *root_all)
// {
//     if(root==NULL)
//     {
//         return;
//     }
//     help_harmonize(root->left,semitones,time_shift,root_all);
//     insert_new(root, semitones, time_shift, root_all);
//     help_harmonize(root->right,semitones,time_shift,root_all);
// }



BST_Node *BST_harmonize(BST_Node *root, int semitones, double time_shift)
{
    /* Let's play with notes, because we can.
     * 
     * This function traverses the BST, and for each existing
     * note, inserts a new, modified note (i.e. it will add sounds
     * to an already existing song, based on the notes it already has)
     * 
     * The new note has the following properties:
     * - The frequency is shifted by the specified number of semitones
     *   (A semitone is the difference between one note and the
     *    immediately next one in the musical scale - ot what is the
     *    same, the difference in pitch between a white key and the
     *    black key immediately next to it in a piano)
     * - It plays in the same *bar* as the original note
     * - But its *index* is shifted by the specified time_shift
     *   (this value is between 0 and 1, but you have to check 
     *    that the final index remains between 0 and 1)
     * 
     * Both the 'semitones' and 'time_shift' parameter can be
     * positive or negative. A typical value for semitones
     * could be 4 or 7, corresponding to musical 3rds or
     * musical 5ths - this should produce some interesting
     * harmony! but you can play with this function and try
     * various things for fun.
     * 
     * In practice, figuring out the frequency of the note
     * you have to insert is easy. For instance, suppose
     * you have an existing note in  the BST with
     * 
     * freq=440.0, at bar=10, index=.25
     * 
     * Now suppose the user specified
     * 
     * semitones=4
     * time_shift=.1
     * 
     * Then you go to the note_freq[] array, find the index
     * of the entry for frequency 440.0 (let's say it's 
     * j), then go to note_freq[j+4] to find the frequency
     * of the note you need to add.
     * 
     * NOTE: If the value of  j+semitones  is < 0 or > 99
     *       then there is no note with the frequency you
     *       want. In that case you don't insert a new
     *       note. 
     * 
     * You then add a new note with that frequency at
     * bar=10 (same bar!)
     * index=.25 + .1  (the original index plus the time_shift)
     * 
     * NOTE: If the resulting index is less than 0, or >= 1,
     *       then you DO NOT insert the new note.
     * 
     * This function is crunchy - and if you don't think it 
     * through before you start implementing it you'll run into
     * all kinds of trouble.
     * 
     * This is the problem solving exercise for A2, so don't
     * look for people on Piazza to give you answers, or tell you
     * what to do, or verify you're doing the right thing.
     * 
     * It's up to you how to solve this, and if you want an opinion,
     * you can come to visit us during office hours!
     * 
     * Expected result: The BST will have about twice as many notes
     *   as before, and the new notes are shifted in pitch and 
     *   in time as specified by the parameters. 
     */
    
    /*** TO DO:
     * Implement this function
     ****/
    if(root==NULL)
    {
        return NULL;
    }
    H_Node *head=NULL;
    H_Node *ptr=NULL;
    head=create_all_nodes(root,semitones,time_shift,head);
    if(head==NULL)
    {
        return root;
    }
    ptr=head;
    while(ptr!=NULL)
    {
        BST_insert(root, ptr->p);
        ptr=ptr->next;
    }
    ptr=head;
    H_Node *q=NULL;
    
    while(ptr!=NULL)
    {
        q=ptr->next;
        free(ptr);
        ptr=q;
    }
    return root;




    // help_harmonize(root,semitones,time_shift,root);
    // return root;

}
