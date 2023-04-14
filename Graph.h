//
//                     Data Structure Fall 2022
//
//         Course Instructor:
//                             Maam Maheen Arshad
//
//         Group:
//                             21I-1111    Talal Habib
//                             21I-1104    Moiz Akhtar
//                             21I-1239    Mahad Shiekh
//

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <stack>

using namespace std;


class Friend_Node {                     //Horizontal Linked list to store Freinds IDs
public:
    int Friends_ID;             //Friend ID
    Friend_Node* next;          //Next Friend ID

    Friend_Node();              //Constructor
};

class Graph_Node {              //Vertical Linked list that contains IDs and pointer to Friends IDs
public:
    int ID_NO;                  //Main ID
    Friend_Node* ID;            //Friends IDs
    Graph_Node* next;           //Next Data ID

    Graph_Node();               //Constructor
    void Insert(int i);         //Inserting of Friends ID
    void Display(Friend_Node* Temp);        //Displayin Friends IDs
};


class Graph {
private:
    Graph_Node* Root;               //Behave Like an Adjacency matrix

public:
    int Size_Graph;                 //Store size of graph

    Graph();                        //Constructor

    void Insert(int Main_ID, vector<int>& Temp_IDs);            //Insertion of ID along with Friend IDs

    void Find_Biggest();                    //Finding the ID with Biggest Social Circle

    void Social_Distance(int ID1, int ID2);         //Finding Distance between Two IDs

    void Common_Friends(Friend_Node* Temp, vector<int>& Data);         //Getting Friends of Friends of ID 

    void Friends(Friend_Node* Temp, vector<int>& Data);             //Getting Direct Friends of Id

    void Find_Common(int ID1, int ID2);                             //Finding Common Friends in Both IDs Social Circle

    void No_Pairs_Check();                      //Checking to Find Pairs that don't intersect

    void Display(Graph_Node* Temp);             //Display function

    bool Search(int ID);                    //Searching for ID is Graph

    Graph_Node* GetHead();
    
    ~Graph();               //Destructor To Delete The Whole Graph
};


Friend_Node::Friend_Node()                  //Constructor of Friend Node Class
{
    Friends_ID = INT32_MIN;                 //Min Value int can store Dummy Value
    next = NULL;                            //Don't Point to anything
}

Graph_Node::Graph_Node()                        //Constructor of Graph Node
{
    ID = NULL;
    next = NULL;
    ID_NO = INT32_MIN;
}

void Graph_Node::Insert(int i)                      //Insertion Function to insert Friend in Friends Linked List
{
    if (ID == NULL)                                 //if Currently No Friend ID exist
    {
        ID = new Friend_Node;
        ID->Friends_ID = i;
        ID->next = NULL;
        return;
    }
    Friend_Node* Temp = ID;                         //New Friend ID is Inserted Here
    while (!(Temp->next == NULL))
    {
        Temp = Temp->next;
    }
    Temp->next = new Friend_Node;
    Temp = Temp->next;
    Temp->Friends_ID = i;
    Temp->next = NULL;
}

void Graph_Node::Display(Friend_Node* Temp)                 //Function to Display All Friend ID
{
    if (Temp)
    {
        cout << Temp->Friends_ID << "\t";
        Display(Temp->next);
    }
}

Graph::Graph() {                    //Constructor of Graph
    Root = NULL;
    Size_Graph = 0;
}

void Graph::Insert(int Main_ID, vector<int>& Temp_IDs)
{
    if (Root == NULL)                           //If No IDs Exist in Graph
    {
        Root = new Graph_Node;                  //Node Created and ID inserted
        Root->ID_NO = Main_ID;
        for (int i = 0; i < Temp_IDs.size(); i++)           //Vector has all the Friends/Edges of the ID
        {
            Root->Insert(Temp_IDs[i]);                      //Inserting them one by one
        }
        return;
    }
    Graph_Node* Temp = Root;
    while (!(Temp->next == NULL))               //Inserting ID down the Linked lsit
    {
        Temp = Temp->next;
    }
    Temp->next = new Graph_Node;
    Temp = Temp->next;
    Temp->ID_NO = Main_ID;
    for (int i = 0; i < Temp_IDs.size(); i++)           //Again vector contains all friends/edges
    {
        Temp->Insert(Temp_IDs[i]);
    }
}

void Graph::Find_Biggest()                      //Finding the Biggest Social Circle
{
    system("CLS");
    int Max_Circle = 0;
    vector<int> Max_Id;
    Graph_Node* Temp = Root;
    while (!(Temp == NULL))
    {
        vector<int> Data;
        Friends(Temp->ID, Data);                            //This Functions Gets the Friends and Friends of Friends of current ID and store them in vector
        sort(Data.begin(), Data.end());                     //Sorting All the Friend ID in the Vector to remove duplicates
        Data.erase(unique(Data.begin(), Data.end()), Data.end());       //This Line Code Removes almost all duplicates
        remove(Data.begin(), Data.end(), Temp->ID_NO);                  //This Removes the instances of Current IDs from vector
        int j = 0;
        for (int i = 0; i < Data.size(); i++)
        {
            if (i > 0 && Data[i] == Data[i - 1])                //This condition is for checking dupliactes as unique doesn't get rid of all duplicates
            {
                continue;                                       //This Loop calculates how many friends are there
            }
            j++;
        }
        if (j == Max_Circle)                                    //If calculate sum of friends is equal to max than ID is Added to Vector
        {
            Max_Id.insert(Max_Id.end(), Temp->ID_NO);
        }
        else if (j > Max_Circle)                                //If sum is greater than max vector is cleared and Id is inserted
        {
            Max_Circle = j;
            Max_Id.clear();
            Max_Id.insert(Max_Id.end(), Temp->ID_NO);
        }
        Temp = Temp->next;
    }

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "\t\tThe Max Social Circle is of \n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    for (int i = 0; i < Max_Id.size(); i++)
    {
        cout << "\t\tID No:\t" << Max_Id[i] << "\tMax No:\t";                        //Displaying Max Social Circle
        cout << Max_Circle << endl;
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void Graph::Social_Distance(int ID1, int ID2)                       //Finding Social Distance Between Two Points/IDs
{
    system("CLS");
    vector<int> Visited_IDs;                            //Vector to Keep track of visited IDs
    stack<int> IDS;                                     //Path taken
    IDS.push(ID1);                                      //Pushing starting point in stack
    Visited_IDs.insert(Visited_IDs.end(), ID1);         //Also pushing it as VIsited
    while (!IDS.empty())                                //Loop runs till stack is not empty when stack is empty no path found
    {
        if (IDS.top() == ID2)                           //If top elemnent of Stack is the End Point
        {
            break;
        }
        Graph_Node* Temp = Root;                        //Finding Stack Top ID in our Graph
        while (!(Temp == NULL))
        {
            if (Temp->ID_NO == IDS.top()) {
                break;
            }
            Temp = Temp->next;
        }
        if (Temp == NULL)                               //if  Id doesn't exist pop from stack
        {
            IDS.pop();
            continue;
        }
        Friend_Node* Temp1 = Temp->ID;                  //Searching friends IDs to see if ending point is in there if yes push and continue loop
        bool Flag = false;
        while (!(Temp1 == NULL))
        {
            if (Temp1->Friends_ID == ID2)
            {
                IDS.push(Temp1->Friends_ID);
                Flag = true;
            }
            Temp1 = Temp1->next;
        }
        if (Flag)
        {
            break;
        }
        Friend_Node* Temp2 = Temp->ID;                  //Moving to next ID and pushing it in stack
        while (!(Temp2 == NULL))
        {
            auto Check = find(Visited_IDs.begin(), Visited_IDs.end(), Temp2->Friends_ID);    //Code to Check if ID is within the visited vector or not
            if (Check != Visited_IDs.end())
            {
                Temp2 = Temp2->next;
            }
            else
            {
                break;
            }
        }
        if (Temp2 == NULL)
        {
            IDS.pop();
            continue;
        }
        IDS.push(Temp2->Friends_ID);                    //Pushing in Stack
        Visited_IDs.insert(Visited_IDs.end(), Temp2->Friends_ID);               //Inserting in Vector
    }
    if (IDS.size() - 2 < 0)
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\t\tCoundln't Find Any Path\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }
    else
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "Path Found with the Social Distance from " << ID1 << " to " << ID2 << "\nWith Social Distance of " << IDS.size() - 2 << endl;
        if (IDS.size() - 2 == 0)
        {
            cout << ID1 << " is an Direct Friend of " << ID2 << endl;
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "                      Path Found\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        vector<int> Temp;
        int j = IDS.size();
        for (int i = 0; i < j; i++)
        {
            Temp.insert(Temp.begin(), IDS.top());
            IDS.pop();
        }                                   //Inserting stack into an vector to show the Path found
        cout << Temp[0];
        for (int i = 1; i < Temp.size(); i++)
        {
            cout << "->" << Temp[i];
        }
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }
}

void Graph::Common_Friends(Friend_Node* Temp, vector<int>& Data)        //Getting Friends of Friend of ID        
{
    if (Temp == NULL)
    {
        return;
    }
    Data.insert(Data.end(), Temp->Friends_ID);
    Common_Friends(Temp->next, Data);
}

void Graph::Friends(Friend_Node* Temp, vector<int>& Data)           //Getting the Data of Direct Friends of ID
{
    if (Temp == NULL)
    {
        return;
    }
    Graph_Node* Root_temp = Root;
    while (!(Root_temp == NULL))
    {
        if (Root_temp->ID_NO == Temp->Friends_ID)
        {
            Common_Friends(Root_temp->ID, Data);
            break;
        }
        Root_temp = Root_temp->next;
    }
    Data.insert(Data.end(), Temp->Friends_ID);
    Friends(Temp->next, Data);
}

void Graph::Find_Common(int ID1, int ID2)                       //Finding Common Friends in Friend Circles of Both IDs
{
    system("CLS");
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "                Common Friends in Social Circle\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "              \tof " << ID1 << "\t And " << ID2 << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    vector<int> ID1_Data;
    Graph_Node* Root_temp = Root;
    while (!(Root_temp->ID_NO == ID1))
    {
        Root_temp = Root_temp->next;
    }
    Friends(Root_temp->ID, ID1_Data);               //Getting Friend Circle for ID1
    vector<int> ID2_Data;
    Root_temp = Root;
    while (!(Root_temp->ID_NO == ID2))
    {
        Root_temp = Root_temp->next;
    }
    Friends(Root_temp->ID, ID2_Data);               //Getting Friend Circle for ID2

    sort(ID1_Data.begin(), ID1_Data.end());         //Sorting Data
    sort(ID2_Data.begin(), ID2_Data.end());
    ID1_Data.erase(unique(ID1_Data.begin(), ID1_Data.end()), ID1_Data.end());           //Removing Duplicates
    ID2_Data.erase(unique(ID2_Data.begin(), ID2_Data.end()), ID2_Data.end());
    remove(ID1_Data.begin(), ID1_Data.end(), ID1);                      //Removing Instances of IDs from the Vectors
    remove(ID2_Data.begin(), ID2_Data.end(), ID2);
    for (int i = 0; i < ID1_Data.size() - 1; i++)
    {
        if (i > 0 && ID1_Data[i] == ID1_Data[i - 1])
        {
            continue;
        }
        auto Check = find(ID2_Data.begin(), ID2_Data.end(), ID1_Data[i]);
        if (Check != ID2_Data.end())                                        //Finding Common Friends in Friend Circle for both IDs
        {
            cout << "\t\t\t\t" << ID1_Data[i] << "\n";
        }
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void Graph::No_Pairs_Check()                //Finding All pairs that never intersect
{
    system("CLS");
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "                       Finding Pairs\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    const int i = Size_Graph;
    vector<vector<int>>IDS_Freinds(i);              //2D Vector :)  i is the size of rows in this vector
    Graph_Node* Temp = Root;
    int j = 0;
    int* IDS = new int[i];              //Total No of IDs
    while (!(Temp == NULL))
    {
        IDS[j] = Temp->ID_NO;
        Friends(Temp->ID, IDS_Freinds[j]);              //Gets Friend Circle
        sort(IDS_Freinds[j].begin(), IDS_Freinds[j].end());             //Sorts it 
        IDS_Freinds[j].erase(unique(IDS_Freinds[j].begin(), IDS_Freinds[j].end()), IDS_Freinds[j].end());           //Remove Duplicates
        remove(IDS_Freinds[j].begin(), IDS_Freinds[j].end(), Temp->ID_NO);              //Remove the Main ID from friends ID
        j++;
        Temp = Temp->next;              //We move
    }
    bool Global_Flag = true;                //In The Event No Pairs are found
    for (int q = 0; q < IDS_Freinds.size(); q++)                //Checking All Possible Combinations 
    {
        for (int p = q + 1; p < IDS_Freinds.size(); p++)
        {
            bool Flag = true;
            for (int k = 0; k < IDS_Freinds[q].size(); k++)
            {
                if (k > 0 && IDS_Freinds[q][k] == IDS_Freinds[q][k - 1])        //Skipping Dupliactes
                {
                    continue;
                }
                auto Check = find(IDS_Freinds[p].begin(), IDS_Freinds[p].end(), IDS_Freinds[q][k]);         //Checking if any common friends exist if yes break and move on
                if (Check != IDS_Freinds[p].end())
                {
                    Flag = false;
                    break;
                }
            }
            if (Flag)       //If Pair Found show them
            {
                cout << "\tPair Found\t\tID NOs:\t";
                cout << IDS[q] << "\t" << IDS[p] << endl;
                Global_Flag = false;
            }
        }
    }

    if (Global_Flag)
    {
        cout << "No Possible Pairs that Donnot Intersect With Each Other\n\n";
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void Graph::Display(Graph_Node* Temp)           //Displays The IDs along with Displaying Friends ID
{
    if (Temp)
    {
        cout << Temp->ID_NO << ":\t";
        Temp->Display(Temp->ID);
        cout << endl;
        Display(Temp->next);
    }
}

bool Graph::Search(int ID)                  //Searching whether ID exist within the Graph or not
{
    Graph_Node* Temp = Root;
    while (!(Temp == NULL))
    {
        if (Temp->ID_NO == ID)
        {
            return true;
        }
        Temp = Temp->next;
    }
    return false;
}

Graph_Node* Graph::GetHead() { return Root; }           //Gets Head 

Graph::~Graph()
{
    Graph_Node* Temp = NULL;            //Deleting Vertical Linked List 
    while (!Root == NULL)
    {
        Temp = Root;
        Friend_Node* Prev = NULL;           //Deleting Horizontal Linked List
        while (!(Temp->ID == NULL))
        {
            Prev = Temp->ID;
            Temp->ID = Temp->ID->next;
            delete Prev;
        }
        Root = Root->next;
        delete Temp;
    }
}

int Cin_Data(string);               //For Error Handling

void Graph_Menu();                  //Menu of Graph Part of Project

int Cin_Data(string ptr)            //Gets number from user check if string is all integer than returns integer
{
    string str;
    bool flag = false;
    do {
        flag = false;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\t\t\t" << ptr;
        cin >> str;
        for (int i = 0; i < str.size(); i++)
        {
            if (isdigit(str[i]) == false)
            {
                flag = true;
                cout << "Please Enter a Number\n\n";
                break;
            }
        }
    } while (flag == true);
    return stoi(str);
}

void Graph_Menu()
{
    string File_Names[13] = {
    "Fall2022DSDataFile001.txt",
    "Fall2022DSDataFile002.txt",
    "Fall2022DSDataFile003.txt",
    "Fall2022DSDataFile004.txt",
    "Fall2022DSDataFile005.txt",
    "Fall2022DSDataFile006.txt",
    "Fall2022DSDataFile007.txt",
    "Fall2022DSDataFile008.txt",
    "Fall2022DSDataFile009.txt",
    "Fall2022DSDataFile010.txt",
    "Fall2022DSDataFile011.txt",
    "Fall2022DSDataFile012.txt",
    "friends.txt"
    };

    system("Color 3");

    //Code To Read Data and Insert IN Class From Here
    Graph Graph_Check;
    string Data;
    fstream MyFile;
    MyFile.open(File_Names[12]);
    getline(MyFile, Data);
    while (!Data.empty() && !MyFile.eof())                   //Reading Till string is empty
    {
        string Main_ID;
        stringstream Splitting(Data);                       //Using sstream to split the string
        getline(Splitting, Main_ID, ':');                   //First Split for Main ID
        string Temp;
        vector<int> Friend_IDs;
        getline(Splitting, Temp, ' ');
        while (getline(Splitting, Temp, ' '))
        {
            Friend_IDs.insert(Friend_IDs.end(), stoi(Temp));        //Further Splits for Friends of Main ID storing them in vector
        }
        int i = stoi(Main_ID);
        Graph_Check.Insert(i, Friend_IDs);                  //Passing Main_Id and vector of friends to insert in graph
        Data = "";
        Graph_Check.Size_Graph++;
        getline(MyFile, Data);
    }

    //To Here 
    int Data1, Data2;
    char ch;
    do {
        system("CLS");          //Menu Self Explanatory
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "                                        Graph Menu\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "\t1.\tFind The Biggest Social Circle Among the ID in Graph\n"
            << "\t2.\tFind The Common Friends of the any Two IDs\n"
            << "\t3.\tFind All IDs that Don't Form a Pair with one another\n"
            << "\t4.\tFind the Shortest Distance Among Two IDs\n"
            << "\t0.\tExit\n"
            << "\t\tSelect Option = ";
        cin >> ch;
        switch (ch)
        {
        case '1':
            Graph_Check.Find_Biggest();
            system("PAUSE");
            break;
        case '2':
            do {
                Data1 = Cin_Data("Enter The First ID to Check=");
                if (!(Graph_Check.Search(Data1)))
                {
                    cout << "This ID does not Exists In the Graph!!!!\nPls Enter Again\n";
                }
            } while (!(Graph_Check.Search(Data1)));
            do {
                Data2 = Cin_Data("Enter The Second ID to Check=");
                if (!(Graph_Check.Search(Data2)))
                {
                    cout << "This ID does not Exists In the Graph!!!!\nPls Enter Again\n";
                }
                if (Data1 == Data2)
                {
                    cout << "Already Entered This Value Pls Enter Different Value\n";
                }
            } while (!(Graph_Check.Search(Data2)) || Data1 == Data2);
            Graph_Check.Find_Common(Data1, Data2);
            system("PAUSE");
            break;
        case '3':
            Graph_Check.No_Pairs_Check();
            system("PAUSE");
            break;
        case '4':
            do {
                Data1 = Cin_Data("Enter The First ID to Check=");
                if (!(Graph_Check.Search(Data1)))
                {
                    cout << "This ID does not Exists In the Graph!!!!\nPls Enter Again\n";
                }
            } while (!(Graph_Check.Search(Data1)));
            do {
                Data2 = Cin_Data("Enter The Second ID to Check=");
                if (!(Graph_Check.Search(Data2)))
                {
                    cout << "This ID does not Exists In the Graph!!!!\nPls Enter Again\n";
                }
                if (Data1 == Data2)
                {
                    cout << "Already Entered This Value Pls Enter Different Value\n";
                }
            } while (!(Graph_Check.Search(Data2)) || Data1 == Data2);
            Graph_Check.Social_Distance(Data1, Data2);
            system("PAUSE");
            break;
        case '0':
            break;
        default:cout << "Invlaid Option Please Select Again\n";
            system("PAUSE");
            break;
        }
    } while (ch != '0');

}