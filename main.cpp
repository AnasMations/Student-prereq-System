#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

//Binary tree node
class node{
public:
    int key;
    node *left;
    node *right;

    node()
    {
        key = 0;
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
        cout<<"Tree has been declared!"<<endl;
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
        if (std::isdigit(c) == 0) return false;
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
    cout<< tree.root->left->left->left->key;

}
