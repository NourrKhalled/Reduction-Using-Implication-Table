#include <bits/stdc++.h>

using namespace std;


//Most Of Used Variables//
    int staten;
    string implem;

//functions

void Mealy(int staten);
void ttprintMealy(int staten , char states[][3] , int outputz[][2]);
void Moore(int staten);
void ttprintMoore(int staten , char states[][3] , int outputz[][1]);


int main()
{


//----------------------------------------------------------------Circuit type--------------------------------------------------------------//

    cout << "Name: Nour Khaled Mohamed\nID: 22011319\n\n\t\tProgram for Reduction of state table using Implication Table method" << "\n\n" << "Type (Mealy/Moore):";
    cin >> implem;
    while(implem != "Mealy" && implem != "Moore"){
        cout << "\n\tWrong Input!" << "\n\n" << "Type (Mealy/Moore):";
        cin >> implem;
    }
//---------------------------------------------------------------Number of states-----------------------------------------------------------//

    cout << "\n\nEnter Number Of States:" ;
    cin >> staten;
    while(staten<0){
        cout << "Must be greater that 0!";
        cout << "\n\nEnter Number Of States:" ;
        cin >> staten;
    }

    if(implem == "Mealy"){
        Mealy(staten);
    }
    else{
        Moore(staten);
    }


    return 0;
}

//----------------------------------------------------------------Mealy Function---------------------------------------------------------------//
void Mealy(int staten){
//--------------------------------------------------------------Initializing States------------------------------------------------------------//

    char states[staten][3];
    int outputz[staten][2];

    for(int i = 0 ; i < staten ; i++){
        states[i][0] =(char) ((int)'A' + i);
        cout << "State " << i << " is : " << states[i][0] << "\n";
    }

//----------------------------------------------------------------Taking User Input-----------------------------------------------------------//
    int choice;
    do{
    for(int i = 0 ; i < staten ; i++){

        cout << "\nEnter next state for " << states[i][0] << " when \n\t\tx = 0:";
        cin >> states[i][1];
        while(states[i][1] > (char) ((int)'A' + staten-1) || states[i][1] < 'A'){
            cout << "\nWrong state! Enter from A to " << (char) ((int)'A' + staten-1);
            cout << "\nEnter next state for " << states[i][0] << " when \n\t\tx = 0:";
            cin >> states[i][1];
        }

        //NS at x = 0


        cout << "\nEnter next state for " << states[i][0] << " when \n\t\tx = 1:";
        cin >> states[i][2];
        while(states[i][2] > (char) ((int)'A' + staten-1) || states[i][2] < 'A'){
            cout << "\nWrong state! Enter from A to " << (char)((int)'A' + (staten-1));
            cout << "\nEnter next state for " << states[i][0] << " when \n\t\tx = 1:";
            cin >> states[i][2];
        }

        //NS at x = 1
            cout << "\nEnter output for " << states[i][0] << " when \n\t\tx = 0:";
            cin >> outputz[i][0];

            while(outputz[i][0] != 0 && outputz[i][0] != 1){
                    cout << "\nWrong input! 0 or 1 only";
                    cout << "\nEnter output for " << states[i][0] << " when \n\t\tx = 0:";
                    cin >> outputz[i][0];
                    }

                    //Z at x = 0

            cout << "\nEnter output for " << states[i][0] << " when \n\t\tx = 1:";
            cin >> outputz[i][1];
            while(outputz[i][1] != 0 && outputz[i][1] != 1){
                    cout << "\nWrong input! 0 or 1 only";
                    cout << "\nEnter output for " << states[i][0] << " when \n\t\tx = 1:";
                    cin >> outputz[i][1];
                    }

                    //Z at x = 1



    }
        ttprintMealy(staten , states , outputz);
        cout << "Press 1 to continue\t\tPress another number to renter Table\n";
        cin >> choice;
    }while(choice != 1);


//----------------------------------------------------------------Initial Equivalent States----------------------------------------------------------//


    map <char , vector<char>> pairs;
        for(int i = 0 ; i < staten ; i++){
                for(int j = 0 ; j < staten ; j++){
                    if(outputz[i][0] == outputz[j][0] && outputz[i][1] == outputz[j][1]){
                                pairs[states[i][0]].push_back(states[j][0]);
                            }
                        }
                    }


        map<char, vector<char>>::iterator itr;
        cout << "\n\n\n";
//----------------------------------------------------------------Print Implication Table----------------------------------------------------------//
        for(int i = 1 ; i < staten ; i++){
            for(int j = 0 ; j < i ; j++){
                    bool x1 , x2;
                    x1 = x2 = false;
                    if(outputz[i][0] == outputz[j][0] && outputz[i][1] == outputz[j][1]){
                        if(states[i][1] != states[j][1]){
                                cout << states[i][1] << " - " << states[j][1];
                                if(pairs[states[i][1]].end() == find(pairs[states[i][1]].begin(), pairs[states[i][1]].end(), states[j][1])){
                                        cout << " X ";
                                        x1 = true;

                                }
                                else{
                                        cout << " / ";

                                }
                        }
                        if(states[i][2] != states[j][2]){
                                cout << states[i][2] << " - " << states[j][2];
                                if(pairs[states[i][2]].end() == find(pairs[states[i][2]].begin(), pairs[states[i][2]].end(), states[j][2])){
                                        cout << " X ";
                                        x2 = true;
                                }
                                else{
                                        cout << " / ";

                                }
                        }
                    }
                    else{
                        cout << " X ";
                        x1 = x2 = true;

                    }
                    if(x1 || x2){
                            for(int it  = 0 ; it < pairs[states[i][0]].size() ; it++){
                                if(pairs[states[i][0]][it] == states[j][0]){
                                        pairs[states[i][0]].erase(pairs[states[i][0]].begin() + it);
                                        for(int it  = 0 ; it < pairs[states[j][0]].size() ; it++){
                                            if(pairs[states[j][0]][it] == states[i][0]){
                                        pairs[states[j][0]].erase(pairs[states[j][0]].begin() + it);
                                        break;
                                            }
                                        }

                                break;
                                }
                            }
                        }

                    cout << "\t" ;
            }

            cout << "\n---\n" ;
    }



cout << "\n\n\n";
//----------------------------------------------------------------Print Equivalent States----------------------------------------------------------//
vector <char> skip;
for(itr = pairs.begin() ; itr != pairs.end() ; itr++){
        if(find( skip.begin() , skip.end() , itr->first)!= skip.end())continue;
            cout << "\n" << itr->first << "  |  ";

            for (char state : itr->second) {
                cout << state << " ";
                skip.push_back(state);
            }
        }
}



//----------------------------------------------------------------Print Mealy Truth Table----------------------------------------------------------//

void ttprintMealy(int staten , char states[][3] , int outputz[][2]){
    cout << "Present State |        Next State               |           Output Z\n";
    cout << "                        x = 0   |    x = 1      ";
    cout <<"|    x = 0    |    x = 1\n";
    for(int i = 0 ; i < staten ; i++){
        cout << "\t";
        cout << states[i][0];
        cout << " \t|\t ";
        cout << states[i][1];
        cout << " \t|\t ";
        cout << states[i][2];
        cout << " \t|\t ";
        cout << outputz[i][0];
        cout << " \t|\t ";
        cout << outputz[i][1];
        cout << "\n\n\n\n";
    }
}

//----------------------------------------------------------------Moore Function---------------------------------------------------------------//


void Moore(int staten){
//--------------------------------------------------------------Initializing States------------------------------------------------------------//

    char states[staten][3];
    int outputz[staten][1];

    for(int i = 0 ; i < staten ; i++){
        states[i][0] =(char) ((int)'A' + i);
        cout << "State " << i << " is : " << states[i][0] << "\n";
    }

//----------------------------------------------------------------Taking User Input------------------------------------------------------------//
    int choice;
    do{
    for(int i = 0 ; i < staten ; i++){

        cout << "\nEnter next state for " << states[i][0] << " when \n\t\tx = 0:";
        cin >> states[i][1];
        while(states[i][1] > (char) ((int)'A' + staten-1) || states[i][1] < 'A'){
            cout << "\nWrong state! Enter from A to " << (char) ((int)'A' + staten-1);
            cout << "\nEnter next state for " << states[i][0] << " when \n\t\tx = 0:";
            cin >> states[i][1];
        }

        //NS at x = 0


        cout << "\nEnter next state for " << states[i][0] << " when \n\t\tx = 1:";
        cin >> states[i][2];
        while(states[i][2] > (char) ((int)'A' + staten-1) || states[i][2] < 'A'){
            cout << "\nWrong state! Enter from A to " << (char)((int)'A' + (staten-1));
            cout << "\nEnter next state for " << states[i][0] << " when \n\t\tx = 1:";
            cin >> states[i][2];
        }

        //NS at x = 1
            cout << "\nEnter output for " << states[i][0] << " :";
            cin >> outputz[i][0];

            while(outputz[i][0] != 0 && outputz[i][0] != 1){
                    cout << "\nWrong input! 0 or 1 only";
                    cout << "\nEnter output for " << states[i][0] << " :";
                    cin >> outputz[i][0];
                    }

                    //Z
    }
        ttprintMoore(staten , states , outputz);
        cout << "Press 1 to continue\t\tPress another number to renter Table\n";
        cin >> choice;
    }while(choice != 1);


//----------------------------------------------------------------Initial Equivalent States----------------------------------------------------------//


    map <char , vector<char>> pairs;
        for(int i = 0 ; i < staten ; i++){
                for(int j = 0 ; j < staten ; j++){
                    if(outputz[i][0] == outputz[j][0]){
                                pairs[states[i][0]].push_back(states[j][0]);
                            }
                        }
                    }


        map<char, vector<char>>::iterator itr;
        cout << "\n\n\n";
//----------------------------------------------------------------Print Implication Table----------------------------------------------------------//
        for(int i = 1 ; i < staten ; i++){
            for(int j = 0 ; j < i ; j++){
                    bool x1 , x2;
                    x1 = x2 = false;
                    if(outputz[i][0] == outputz[j][0]){
                        if(states[i][1] != states[j][1]){
                                cout << states[i][1] << " - " << states[j][1];
                                if(pairs[states[i][1]].end() == find(pairs[states[i][1]].begin(), pairs[states[i][1]].end(), states[j][1])){
                                        cout << " X ";
                                        x1 = true;

                                }
                                else{
                                        cout << " / ";

                                }
                        }
                        if(states[i][2] != states[j][2]){
                                cout << states[i][2] << " - " << states[j][2];
                                if(pairs[states[i][2]].end() == find(pairs[states[i][2]].begin(), pairs[states[i][2]].end(), states[j][2])){
                                        cout << " X ";
                                        x2 = true;
                                }
                                else{
                                        cout << " / ";

                                }
                        }
                    }
                    else{
                        cout << " X ";
                        x1 = x2 = true;

                    }
                    if(x1 || x2){
                            for(int it  = 0 ; it < pairs[states[i][0]].size() ; it++){
                                if(pairs[states[i][0]][it] == states[j][0]){
                                        pairs[states[i][0]].erase(pairs[states[i][0]].begin() + it);
                                        for(int it  = 0 ; it < pairs[states[j][0]].size() ; it++){
                                            if(pairs[states[j][0]][it] == states[i][0]){
                                        pairs[states[j][0]].erase(pairs[states[j][0]].begin() + it);
                                        break;
                                            }
                                        }

                                break;
                                }
                            }
                        }

                    cout << "\t" ;
            }

            cout << "\n---\n" ;
    }



cout << "\n\n\n";
//----------------------------------------------------------------Print Equivalent States----------------------------------------------------------//
vector <char> skip;
for(itr = pairs.begin() ; itr != pairs.end() ; itr++){
        if(find( skip.begin() , skip.end() , itr->first)!= skip.end())continue;
            cout << "\n" << itr->first << "  |  ";

            for (char state : itr->second) {
                cout << state << " ";
                skip.push_back(state);
            }
        }
}




//----------------------------------------------------------------Print Moore Truth Table----------------------------------------------------------//

void ttprintMoore(int staten , char states[][3] , int outputz[][1]){
    cout << "Present State |        Next State               |           Output Z\n";
    cout << "                        x = 0   |    x = 1      \n";
    for(int i = 0 ; i < staten ; i++){
        cout << "\t";
        cout << states[i][0];
        cout << " \t|\t ";
        cout << states[i][1];
        cout << " \t|\t ";
        cout << states[i][2];
        cout << " \t|\t ";
        cout << outputz[i][0];
        cout << "\n\n\n\n";
    }
}
