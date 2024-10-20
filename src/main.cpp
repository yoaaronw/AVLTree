#include <iostream>
#include <sstream>
#include "AVLTree.h"

using namespace std;


int main()
{

    AVLTree tree;

    string line;
    getline(cin, line);
    istringstream in(line);
    int numCommands;
    in >> numCommands;

    for (int i = 0; i < numCommands; i++)
    {
        getline(cin, line);
        istringstream commands(line);
        string command;
        commands >> command;

        if (command == "insert")
        {
            // Read up until first '"'
            string temp;
            getline(commands, temp, '"');
            // Read name
            string name;
            getline(commands, name, '"');
            // Get rid of space
            getline(commands, temp, ' ');
            // Read ufid
            string ufid;
            getline(commands, ufid);

            tree.insert(name, ufid);
        }
        else if (command == "remove")
        {
            string temp;
            getline(commands, temp, ' ');
            string ufid;
            getline(commands, ufid);

            tree.remove(ufid);
        }
        else if (command == "search")
        {
            string temp;
            getline(commands, temp, ' ');
            string ufid;
            getline(commands, ufid);

            if (ufid.at(0) == '"')
            {
                string name = ufid.substr(1, ufid.size() - 2);
                tree.searchName(name);
            }
            else
            {
                tree.searchID(ufid);
            }
        }
        else if (command == "printInorder")
        {
            tree.inorder();
        }
        else if (command == "printPreorder")
        {
            tree.preorder();
        }
        else if (command == "printPostorder")
        {
            tree.postorder();
        }
        else if (command == "printLevelCount")
        {
            tree.levelCount();
        }
        else if (command == "removeInorder")
        {
            string temp;
            getline(commands, temp, ' ');
            string n;
            getline(commands, n);

            tree.removeInorder(n);
        }
        else
        {
            cout << "unsuccessful" << endl;
        }
    }

    return 0;
}

