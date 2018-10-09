/*
 Author: Rooman Zahid
 A Pronunciation Dictionary App
 
 This program asks the user to input a word and then performs the following operations:
 1)outputs pronunciation
 2)outputs identical words
 3)Adds/removes/replaces a phoneme and then displays the output
 */

//g++ -o pronounce pronounce.cpp
// ./pronounce
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//This function determines whether a string is valid
bool isValidString(string str){
    for(int i=0; i<str.size(); i++){
        if(((isalpha(str[i])) && (tolower(str[i]) >= 'a') && (tolower(str[i]) <= 'z')) || (str[i] == '\'')){
        }
        else{
            return false;
        }
    }
    return true;
}

//This function spllts a string into two
void splitOnSpace(string s, string & before, string & after) {
    // reset strings
    before = "";
    after = "";
    // accumulate before space
    int i = 0;
    while (i < s.size() && not isspace(s[i])) {
        before += s[i]; i++;
    }
    // skip the space
    i++;
    // accumulate after space
    while (i < s.size()) {
        after += s[i]; i++;
    }
}

//using splitonspace, this function returns identical words
string isIdentical(string str1, string str2){
    string b1, a1;
    string b2, a2;
    splitOnSpace(str1, b1, a1);
    splitOnSpace(str2, b2, a2);
    if(!isValidString(b2)){
        return "-1";
    }
    if(a1 == a2 && b1!=b2){
        return b2;
    }
    else{
        return "-1";
    }
}

string isFound(string inp, string line){
    string a1, b1;
    splitOnSpace(line, b1, a1);
    if(!isValidString(b1)){
        return "-1";
    }
    if(b1 == inp){
        return a1;
    }
    return "-1";
}

string addPhoneme(string str1, string str2){
    string b1, a1;
    string b2, a2;
    splitOnSpace(str1, b1, a1);
    splitOnSpace(str2, b2, a2);
    if(!isValidString(b2)){
        return "-1";
    }
    string strWords1[20], strWords2[20];
    int counter1=0, counter2=0;
    for (int i = 0; i<a1.length(); i++){
        if (a1[i] == ' '){
            counter1++;
        }
        else{
            strWords1[counter1] += a1[i];
        }
    }
    counter1++;
    for (int i = 0; i<a2.length(); i++){
        if (a2[i] == ' '){
            counter2++;
        }
        else{
            strWords2[counter2] += a2[i];
        }
    }
    counter2++;
    if(counter1 + 1 != counter2){
        return "-1";
    }
    else{
        int count = 0, j=0;
        for(int i=0;i<counter1;i++){
            if(strWords1[i] != strWords2[j]){
                count++;
                if(count > 1){
                    return "-1";
                }
                i--;
            }
            j++;
        }
        if(count > 1){
            return "-1";
        }
        return b2;
    }
}

string removePhoneme(string str1, string str2){
    string b1, a1;
    string b2, a2;
    splitOnSpace(str1, b1, a1);
    splitOnSpace(str2, b2, a2);
    if(!isValidString(b2)){
        return "-1";
    }
    string strWords1[20], strWords2[20];
    int counter1=0, counter2=0;
    for (int i = 0; i<a1.length(); i++){
        if (a1[i] == ' '){
            counter1++;
        }
        else{
            strWords1[counter1] += a1[i];
        }
    }
    counter1++;
    for (int i = 0; i<a2.length(); i++){
        if (a2[i] == ' '){
            counter2++;
        }
        else{
            strWords2[counter2] += a2[i];
        }
    }
    counter2++;
    if(counter1 - 1 != counter2){
        return "-1";
    }
    else{
        int count = 0, j=0;
        for(int i=0;i<counter1;i++){
            if(strWords1[i] != strWords2[j]){
                count++;
                if(count > 1){
                    return "-1";
                }
            }
            else{
                j++;
            }
        }
        if(count != 1){
            return "-1";
        }
        return b2;
    }
}

string replacePhoneme(string str1, string str2){
    string b1, a1;
    string b2, a2;
    splitOnSpace(str1, b1, a1);
    splitOnSpace(str2, b2, a2);
    if(!isValidString(b2)){
        return "-1";
    }
    string strWords1[20], strWords2[20];
    int counter1=0, counter2=0;
    for (int i = 0; i<a1.length(); i++){
        if (a1[i] == ' '){
            counter1++;
        }
        else{
            strWords1[counter1] += a1[i];
        }
    }
    counter1++;
    for (int i = 0; i<a2.length(); i++){
        if (a2[i] == ' '){
            counter2++;
        }
        else{
            strWords2[counter2] += a2[i];
        }
    }
    counter2++;
    if(counter1 != counter2){
        return "-1";
    }
    else{
        int count = 0;
        for(int i=0;i<counter1;i++){
            if(strWords1[i] != strWords2[i]){
                count++;
            }
        }
        if(count != 1){
            return "-1";
        }
        return b2;
    }
}

int main(){
    string w;
    cout<<"Enter word to lookup: ";
    cin >> w;
    for(int i=0; i<w.size(); i++){
        w[i] = toupper(w[i]);
    }
    if(!isValidString(w)){
        cout << "Not Found" << endl;
        return 0;
    }
    ifstream infile("cmudict.0.7a");
    string line;
    int flag = 0;
    while(getline(infile, line)){
        string p = isFound(w, line);
        if(p == "-1"){
            continue;
        }
        else{
            flag = 1;
            break;
        }
    }
    infile.close();
    ifstream infile1("cmudict.0.7a");
    string pronunciation = "Pronunciation    : ";
    string identical = "Identical        : ";
    string addp = "Add phoneme      : ";
    string removep = "Remove phoneme   : ";
    string replacep = "Replace phoneme  : ";
    if(flag == 0){
        cout << "Not Found\n";
        return 0;
    }
    string after, before;
    splitOnSpace(line, before, after);
    after = after.substr(1);
    pronunciation += after;
    string origStr = line;
    while(getline(infile1, line)){
        string temp = isIdentical(origStr, line);
        if(temp != "-1"){
            identical += temp + " ";
            continue;
        }
        temp = addPhoneme(origStr, line);
        if(temp != "-1"){
            addp += temp + " ";
            continue;
        }
        temp = removePhoneme(origStr, line);
        if(temp != "-1"){
            removep += temp + " ";
            continue;
        }
        temp = replacePhoneme(origStr, line);
        if(temp != "-1"){
            replacep += temp + " ";
            continue;
        }
    }
    cout << pronunciation << endl << endl << identical << endl << addp << endl << removep << endl << replacep << endl;
    return 0;
}
