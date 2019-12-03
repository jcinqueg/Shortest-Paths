/*******************************************************************************
 * Name    : shortestpaths.cpp
 * Author  : John Cinquegrana and Megha Mansuria
 * Version : 1.0
 * Date    : January 9, 2016
 * Description : Does some shortest path nonsense.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/


#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

long INF = numeric_limits<long>::max();

int len( int num ) {
    if( num < 10) return 1;
    return 1 + len( num / 10);
}

/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(long** const matrix, const string &label, size_t num_vertices,
    const bool use_letters = false) {

    cout << label << endl;
    long max_val = 0;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            long cell = matrix[i][j];
            if ( INF > cell && cell > max_val) {
                max_val = matrix[i][j];
            }
        }
    }
    int max_cell_width = use_letters ? len(max_val) :
        len( max(static_cast<long>(num_vertices), max_val) );
    cout << ' ';
    for (int j = 0; j < num_vertices; j++) {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < num_vertices; i++) {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num_vertices; j++) {
            cout << " " << setw(max_cell_width);
            if (matrix[i][j] == INF) {
                cout << "-";
            } else if (use_letters) {
                cout << static_cast<char>(matrix[i][j] + 'A');
            } else {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char* const argv[]) {
    istringstream iss;

    if( argc != 2 ) {
        cerr << "Usage: ./shortestpaths <filename>" << endl;
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
        getline(file, to_insert );
        iss.str( to_insert );
        int num_vertices;
        if( !(iss >> num_vertices) ) { //Put the number of vertices into num vertices
            cerr << "First argument isn't a number" << endl;
            return 1;
        }
        else if( num_vertices < 1 || num_vertices > 26 ) {
            cerr << "First argument isn't in bounds" << endl;
            return 1;
        }
        string first_vertex, second_vertex;
        //size_t edge_weight;
        while( !file.eof() ) {
            //We do what we want with to_insert here
            getline( file, to_insert );
            cout << to_insert << endl;
        }
    }
    else {
        cerr << "File was empty" << endl;
        return 1;
    }

    cout << "looks good to me" << endl;

    return 0; //Everything worked fine
}