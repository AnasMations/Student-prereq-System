#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

//Binary tree node
class node{
public:
    int key;
    bool isStudied;
    node *left;
    node *right;

    node()
    {
        key = 0;
        isStudied = false;
        left = NULL;
        right = NULL;
    }
};

class BST{
public:
    node *root = new node();

    BST()
    {
        root = NULL;
    }

    void construct_tree(vector<int> col1, vector<int> col2)
    {
        for(int i=0; i<col1.size(); i++)
        {
            //insert at root
            if(col2[i] == 0)
            {
                node *temp = new node();
                temp->key = col1[i];
                root = temp;
            }else
            {
                node *newNode = new node();
                node *parentNode = new node();

                newNode->key = col1[i];
                parentNode = Search(root, col2[i]);

                //if left is not empty, insert at left
                if(parentNode->left == NULL)
                {
                    parentNode->left = newNode;
                }else
                {
                    parentNode->right = newNode;
                }
            }
        }
        cout<<"Tree has been constructed!"<<endl;
    }

    //Function to search the whole binary tree
    node* Search(node* root, int key)
    {
        // Base Cases: root is null or key is present at root
        if (root == NULL || root->key == key)
           return root;

        node* x = Search(root->right, key);
        if(x != NULL) return x;
        Search(root->left, key);
    }

    //Function to check whether this course is allowed to be taken or not
    bool check_course(int parent)
    {
        node* temp = Search(root, parent);
        if (temp->isStudied) return true;
        return false;
    }
};

//Extracts two columns from the given CSV file
void extract_columns(string fileName, vector<string> &column1, vector<string> &column2)
{
    //importing the file
    fstream file;
    file.open(fileName);

    string line, word;

    //loop on every whole line in the file
    while(getline(file, line))
    {
        //break the line into words and store it in 's'
        stringstream s(line);

        //loop on every word in that line
        for(int i=0; getline(s, word, ','); i++)
        {
            // add all the column data of a row to a vector
            if(i%2==0)
            {
                column1.push_back(word);
            }else
            {
                column2.push_back(word);
            }
        }
    }
}

//iterate over every char of the string (better than isdigit())
bool is_number(string str)
{
    for (char const &c : str)
    {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

//get first 3 digits in the string
vector<int> change_to_int(vector<string> column_str)
{
    vector<int> column_int;

    for(int i=0; i<column_str.size(); i++)
    {
        if( is_number( column_str[i].substr(0, 3) ) )
        {
            column_int.push_back( stoi(column_str[i].substr(0, 3)) );
        }else
        {
            column_int.push_back(0);
        }
    }

    return column_int;
}

//get index of an element from the vector
int getIndex(vector<int> v, int K)
{
    auto it = find(v.begin(), v.end(), K);

    // If element was found
    if (it != v.end())
    {

        // calculating the index
        // of K
        int index = it - v.begin();
        return index;
    }
    else {
        // If the element is not
        // present in the vector
        return -1;
    }
}

int main()
{
    vector<string> column1_str, column2_str;
    vector<int> column1, column2;

    extract_columns("Courses.csv", column1_str, column2_str);

    column1 = change_to_int(column1_str);
    column2 = change_to_int(column2_str);

    //Form Binary Search Tree
    BST tree;
    tree.construct_tree(column1, column2);

    cout<<endl;

    //Input
    string userInput;
    cout<<"Enter the courses which you already studied (enter 0 when done):"<<endl;
    while(true)
    {
        cout<<"Enter course: ";
        getline(cin, userInput);
        if(userInput=="0") break;
        //Mark inputed courses as studied
        tree.Search( tree.root, stoi(userInput.substr(0, 3)) )->isStudied = true;
    }

    cout<<endl;

    vector<string> okCourses, notOkCourses;
    cout<<"Enter the courses you want to study (enter 0 when done):"<<endl;
    while(true)
    {
        cout<<"Enter course: ";
        getline(cin, userInput);
        if(userInput=="0") break;
        //get index of child in column 1
        int i = getIndex(column1 ,stoi(userInput.substr(0, 3)));
        //check the parent from column 2 of the given index
        if(tree.check_course(column2[i]))
        {
            //course ok to take
            okCourses.push_back(column1_str[i]);
        }else
        {
            //courses not ok to take
            notOkCourses.push_back(column1_str[i]);
        }

    }

    cout<<endl;

    //Output
    cout<<"The following courses are OK to take:"<<endl;
    for(int i=0; i<okCourses.size(); i++)
    {
        cout<<okCourses[i]<<endl;
    }

    cout<<endl;

    cout<<"The following courses CANNOT be taken:"<<endl;
    for(int i=0; i<notOkCourses.size(); i++)
    {
        cout<<notOkCourses[i]<<endl;
    }

}
