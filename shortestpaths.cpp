/*******************************************************************************
 * Name    : shortestpaths.cpp
 * Author  : John Cinquegrana and Megha Mansuria
 * Version : 1.0
 * Date    : January 9, 2016
 * Description : Does some shortest path nonsense.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <sstream>
#include <iostream>
#include <fstream>

int main(int argc, char* const argv[]) {

    istringstream iss;

    if( argc != 2 ) {
        cerr << "Usage: ./anagramfinder <dictionary file>" << endl;
        return 1;
    }

    //Creating a stream for the dictionary file
    string filepath( argv[1] );
    ifstream file;
    file.open(filepath);
    if( !file.is_open() ) { //File was not correctly loaded
        cerr << "Error: File '" << filepath << "' not found." << endl;
        return 1;
    }

    if ( !file.eof() ) {
        string to_insert;
        file >> to_insert;
        while( !file.eof() ) {
            //We do what we want with to_insert here

            file >> to_insert;  //No touch this line
        }
    }

    return 0; //Everything worked fine
}