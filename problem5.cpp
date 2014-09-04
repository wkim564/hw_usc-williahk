#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

//declaration of struct type for data storage
struct bucket{
  int *bucket;
  int bucketSize;
  bool filled;
};

int main(int argc, char * argv[]){
  //declare variables
  bucket *buckets;
  ifstream file;
  int bucketInUse;
  string temp;
  //declare stringstream
  stringstream ss;
  int numBuckets=0;
  int numActions;
  //open the file
  file.open(argv[1]);
  //write first line of file containing number of buckets and number of actions
  //to temp string
  getline(file, temp);
  //send temp string data to stringstream and convert to integer values in numBuckets
  //and numActions
  ss << temp;
  ss >> numBuckets >> numActions;
  //allocate memory for dynamic arrays indicating number of buckets, a bool correlated to a 
  //bucket indicating its state, and a variable indicating the size of the bucket
  buckets = new bucket [numBuckets];
  //initialize boolean array
  for(int i=0; i<numBuckets; i++){
    buckets[i].filled=false;
  }
  //main loop takes input from file and does actions according to input
  for(int i=0; i <numActions; i++){
    //initialize new stringstream
    stringstream ss2;
    //writes a line up until first break to temp string
    getline(file, temp, ' ');
    //compares temp string with predetermined commands and acts accordingly
    //first common indicating input from file
    if(temp == "PUT"){
      //writes a line to temp string
      getline(file,temp);
      //sends temp string to stringstream for conversion to integer values
      ss2 << temp;
      //outputs first integer to bucketInUse variable
      ss2 >> bucketInUse;
      //checks if bucketInUse has already been filled, out putting an error if it is
      if(buckets[bucketInUse-1].filled){
	cout << "Error - bucket " << bucketInUse << " is not empty\n";
      }
      //checks if bucketInUse exists in the range. outputting an error message if it doesn't
      else if(bucketInUse==0 || bucketInUse > numBuckets){
	cout << "Error - bucket " << bucketInUse << " does not exist\n";
      }
      //otherwise executes actions
      else{
	//flags bucket as filled
	buckets[bucketInUse-1].filled=true;
	//inputs second integer indicating size of the bucket to bucketSize variable
	ss2 >> buckets[bucketInUse-1].bucketSize;
	//allocates 2dimensional array to size of bucketSize variable
	buckets[bucketInUse-1].bucket=new int [buckets[bucketInUse-1].bucketSize];
	//streams the remaining integers in order to the newly allocated array
	for(int i=0; i < buckets[bucketInUse-1].bucketSize; i++){
	  ss2 >> buckets[bucketInUse-1].bucket[i];
	}
      }
    }
    //second action indicating output of data
    else if(temp == "OUTPUT"){
      //writes file to temp string
      getline(file,temp);
      //sends string to stream for conversion to integer values
      ss2 << temp;
      //sends first integer input to bucketInUse variable
      ss2 >> bucketInUse;
      //checks if bucketInUse exists in the range, outputting failure if it doesn't
      if(bucketInUse==0 || bucketInUse > numBuckets){
	cout << "Error - bucket " << bucketInUse << " does not exist\n";
      }
      //checks if the bucket is empty, outputting empty if it is
      else if(!buckets[bucketInUse-1].filled){
	cout << "empty\n";
      }
      //otherwise proceeds to output the numbers stored in the buckets in the order inserted
      //using a for loop based on the bucketSize variable at the index of the bucketInUse-1
      else{
	for(int i=0; i < (buckets[bucketInUse-1].bucketSize); i++){
	  cout << buckets[bucketInUse-1].bucket[i] << " ";
	}
	cout << endl;
      }
    }
    //last command indicating deletion of data
    else if(temp == "EMPTY"){
      //writes file to temp for conversion to int
      getline(file,temp);
      //sends temp string to stream for conversion
      ss2 << temp;
      //converts first value into int for bucketInUse
      ss2 >> bucketInUse;
      //checks if bucketInUse exists in the range, outputting failure if it doesn't
      if(bucketInUse==0 || bucketInUse > numBuckets){
	cout << "Error - bucket " << bucketInUse << " does not exist\n";
      }
      //deletes the array so it can be redeclared and sets flag to false
      else{
	delete [] buckets[bucketInUse-1].bucket;
	buckets[bucketInUse-1].filled=false;
      }
    }
  }
  //deallocate all allocated memory
  for(int i=0; i < numBuckets; i++){
    if(buckets[i].filled){
      delete [] buckets[i].bucket;
    }
  }
  delete [] buckets;
  //close file
  file.close();
}
