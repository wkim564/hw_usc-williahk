#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char * argv[]){
  //declaration of variables
  int lineNum;
  string *wordCount;
  ifstream file;
  string buffer;
  //initiate stringstream
  stringstream ss;
  //open file
  file.open(argv[1]);
  //write first line of file to buffer
  getline (file,buffer);
  //send first line holding total line data to string stream and into lineNum integer variable to convert
  ss << buffer;
  ss >> lineNum;
  //clear the string stream
  ss.clear();
  //allocate memory to string array to hold the rest of the file
  wordCount = new string [lineNum];
  //writes each line declared in the first line of the folder into the newly allocated string array
  for(int i=0; i < lineNum; i++){
    getline(file, wordCount[i]);
  }
  //counts the number of words per line from the last index of the array to the beginning
  for(int i=1; i <=lineNum; i++){
    //declares variable
    int wordsPerLine=0;
    //send text to stringstream to be used in getline as argument
    ss << wordCount[lineNum-i];
    //while there is text on a line, read to a ' ' delimeter and write to the buffer. For each ' '     //delimeter check to see if it has no text. If it has no text repeat the loop. If the buffer
    //has text, add 1 to the wordsPerLine integer variable
    while(getline(ss,buffer,' ')){
      if(buffer=="")
	continue;
       wordsPerLine++;
    }
    //output data to command line interface
    cout << wordsPerLine << endl;
    //clear stringstream for reuse
    ss.clear();
  }
  //deallocate the memory used in dynamic memory
  delete [] wordCount;
  //closes file
  file.close();
}
