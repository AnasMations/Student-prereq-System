#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

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

int main()
{
    vector<string> column1, column2;

    extract_columns("Courses.csv", column1, column2);

    cout<<column1[9]<<endl<<column2[9];

}
