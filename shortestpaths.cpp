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

int len( int num ) {
    if( num < 10) return 1;
    return 1 + len( num / 10);
}

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
        istringstream iss;
        file >> to_insert;
        iss( to_insert );
        int num_vertices;
        if( !(iss >> num_vertices) ) {
            cerr << "First argument isn't a number" << endl;
            return 1;
        }
        else if( num_vertices < 1 || num_vertices > 100 ) {
            cerr << "First argument isn't in bounds" << endl;
            return 1;
        }
        while( !file.eof() ) {
            //We do what we want with to_insert here
            cout << to_insert << endl;
            file >> to_insert;  //No touch this line
        }
    }
    else {
        cerr << "File was empty" << endl;
        return 1;
    }

    cout << "looks good to me" << endl;

    return 0; //Everything worked fine
}