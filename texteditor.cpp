// here i build a text editor using oops concept on 7 jan 2023 , i took refernece from this github repo -> https://github.com/shishpalvishnoi/Text-Editor

#include <iostream>
#include <stack>

using namespace std;

class textEditor{

    private:
    stack<char> leftStack; // for storing the charaters onto the left side of cursor 
    stack<char> rightStack; // for storing the charaters onto the right side of cursor 

    public:
    void insertWord(char word[]);
    void insertCharacter(char character);
    bool deleteCharUsingDEL();
    bool deleteCharBackSpace();
    void moveCursor(int position);
    void moveLeftSide(int position,int leftSize);
    void moveRightSide(int position);
    void findAndReplaceChar(char findWhat, char replaceWith);
    void getTheTop();
}; // end of the class texteditor

// definig the functions of text editor class

void textEditor::getTheTop(){
    if(leftStack.empty()){ 
        cout << "LeftStack empty! \t" <<endl;
    }
    else{
        cout<<"leftStack top element : " << leftStack.top() << "\t leftStack current size is : " << leftStack.size() << endl;
    }
    if(rightStack.empty()){
        cout << "rightStack empty! \t" << endl;
    }
    else{
        cout<<"rightStack top element : " << rightStack.top() << "\t rightStack current size is : " << rightStack.size() << endl;
    }
}

void textEditor::insertCharacter(char character){
    leftStack.push(character);
}

void textEditor::insertWord(char word[]){
    int i=0;

    while(word[i] != '\0'){
        insertCharacter(word[i]);
        i++;
    }
}

bool textEditor::deleteCharUsingDEL(){
    //right side of cursor content get deleets 
    if(rightStack.empty()){
        return false;
    }
    else{
        rightStack.pop();
    }
    return true;
}

bool textEditor::deleteCharBackSpace(){
    if(leftStack.empty()){
        return false;
    }
    else{
        leftStack.pop();
    }
    return true;
}

void textEditor::moveCursor(int position){
    int leftSize,rightSize,count;
    leftSize = leftStack.size();
    rightSize = rightStack.size();
    if(position < leftSize){
        moveLeftSide(position,leftSize);
    }
    else{
        count = position-leftSize;
        moveRightSide(count);
    }
}

void textEditor::moveLeftSide(int position,int leftSize){
    int LeftSize = leftSize;
    while(LeftSize!=position){
        rightStack.push(leftStack.top());
        leftStack.pop();
        LeftSize = leftStack.size();
    }   
}

void textEditor::moveRightSide(int count){
    int rightSize = rightStack.size();
    int i=1;
    if(count > rightSize){
        cout<< "Can't move the cursor to the right side upto desiered location!!"<<endl;
    }
    else{
        while(i<=count){
            leftStack.push(rightStack.top());
            rightStack.pop();
            i++;
        }
    }
}


void textEditor::findAndReplaceChar(char findWhat,char replaceWith){
    int count=1;

    //i also store current position of cursor 
    int currentPosition = leftStack.size();
    //firstly i bring cursor to the starting of the text
    moveCursor(0);
    while(!rightStack.empty()){
        if(rightStack.top()==findWhat){
            deleteCharUsingDEL();
            insertCharacter(replaceWith);
        }
        else{
            moveCursor(count);
            count++;
        }
    }
    moveCursor(currentPosition); // after the replace activity bring cursor back to original pposition
}

int main(){
    char text[80];
    textEditor txt;

    cout<<"Enter the text to be inserted "<<endl;
    cin.getline(text,80);
    txt.insertWord(text);

    cout<<"After the insertion of the word : ";
    txt.getTheTop();

    // now second time inserting the new text 

    cout<<"Enter the text to be inserted second time "<<endl;
    cin.getline(text,80);
    txt.insertWord(text);

    cout<<"After the insertion of the word second time : ";
    txt.getTheTop();

    // now moving the cursor 
    cout << "Moving the cursor to position 5"<<endl;
    txt.moveCursor(5);
    txt.getTheTop();

    cout << "Moving the cursor to position 14"<<endl;
    txt.moveCursor(14);
    txt.getTheTop();

    cout << "Moving the cursor to position 17"<<endl;
    txt.moveCursor(17);
    txt.getTheTop();

    // using DEL to delete 3 charaters from right side
    for(int i =0;i<3;i++){
        if(!txt.deleteCharUsingDEL()){
            cout << " Sorry! there is nothing to delete from the right side of cursor" <<endl;
        }
        else{ // means we can delete 
            cout << " delete char using DEL :  ";
            txt.getTheTop();
        }
    }

    //deleteing 7 charter from left using backspace 
    for(int i =0;i<7;i++){
        if(!txt.deleteCharBackSpace()){
            cout << " Sorry! there is nothing to delete from the left side of cursor" <<endl;
        }
        else{ // means we can delete 
            cout << " delete char using backspace :  ";
            txt.getTheTop();
        }
    }

    /// replace the a with A
    txt.findAndReplaceChar('a','A');
    cout <<"Replacing the occurences of a with 'A': ";
    txt.getTheTop();
    return 0;
}