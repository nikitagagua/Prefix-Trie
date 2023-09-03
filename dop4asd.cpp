#include <iostream>
#include <unordered_map>
#include <fstream>
using namespace std;

// here is path to the file with 300000 words (vocabulary)
const std::string FILE_PATH = "/Users/nikitagagua/Desktop/words_alpha.txt";
struct Node {
    unordered_map<char, Node *> child;
    bool isWord;

    Node(){
        isWord = false;
    }
};

// inserting words from file
void insertWords(Node *root){
    ifstream file;
    file.open(FILE_PATH);
    if (file.is_open()) {
        while (!file.eof()) {
            string line;
            getline(file, line);
            Node* current = root;
            for(char c: line){
                if (current->child.find(c) == current->child.end()){
                    current->child[c] = new Node();
                }
                current = current->child[c];
            }
            current->isWord = true;
        }
    }
    else{
        cout<<"Can't open the file"<<endl;
    }
    file.close();
}

// inserting word by User
void insert(string word, Node* root){
    Node* current = root;
    for(char c: word){
        if (current->child.find(c) == current->child.end()){
            current->child[c] = new Node();
        }
        current = current->child[c];
    }
    current->isWord = true;
}

// inner functionality of finding a word
void findWordsWithPrefix(Node* node, string currentPrefix) {
    if (node->isWord) {
        cout << currentPrefix<<endl;
    }

    for (auto pair : node->child) {
        char c = pair.first;
        Node* child = pair.second;
        findWordsWithPrefix(child, currentPrefix + c);
    }
}

void findByPrefix(string prefix, Node* root) {
    Node* current = root;

    for (char c : prefix) {
        if (current->child.find(c) == current->child.end()) {
            cout << "There are no words with this PREFIX" << endl;
            return;
        }
        current = current->child[c];
    }

    findWordsWithPrefix(current, prefix);
}


int main(){
    Node* root = new Node();
    insertWords(root);
    string prefix;
    int choice = 0;
    while(true) {
        cout<<"1 - insert word\n2 - findWords\n3 - quit\n";
        cin>>choice;
        if (choice == 1){
            string word;
            cout<<"Enter word: ";
            cin>>word;
            insert(word, root);
        }
        else if(choice == 2){
            cout << "Enter prefix: ";
            cin >> prefix;
            findByPrefix(prefix, root);
        }
        else{
            cout<<"End."<<endl;
            break;
        }
    }
    return 0;
}