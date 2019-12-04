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
void display_table(long** const matrix, const string &label, int num_vertices,
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

void cleanup( long** const matrix, int length ) {
    for( int i = 0; i < length; i++) {
        delete[] matrix[i]; //Delete each subarray in matrix
    }
    delete[] matrix; //Then delete the matrix itself
}

int main(int argc, char* const argv[]) {
    //Declaring fields I'll need for later
    istringstream iss;
    size_t line_number = 0;
    int num_vertices = -1;

    if( argc != 2 ) {
        cerr << "Usage: ./shortestpaths <filename>" << endl;
        return 1;
    }
    
    //Creating a stream for the dictionary file
    string filepath( argv[1] );
    ifstream file;
    file.open(filepath);
    if( !file.is_open() ) { //File was not correctly loaded
        cerr << "Error: Cannot open file '" << filepath << "'." << endl;
        return 1;
    }

    if ( !file.eof() ) {
        string to_insert;
        istringstream iss;
        getline(file, to_insert );
        line_number++;
        iss.str( to_insert );
        if( !(iss >> num_vertices) || num_vertices < 1 || num_vertices > 26 ) {
            //Put the number of vertices into num vertices
            cerr << "Error: Invalid number of vertices '" << num_vertices << "' on line " << line_number << "." << endl;
            return 1;
        }
    }
    else {
        cerr << "Error: Text file exists, but was empty." << endl;
        return 1;
    }

    //Once we know the number of vertices, create the matrix
    long** const distance_matrix = new long*[num_vertices]; //Rows
    for( int i = 0; i < num_vertices; i++) {
        distance_matrix[i] = new long[num_vertices]; //Columns
        for( int j = 0; j < num_vertices; j++) {
            distance_matrix[i][j] = INF; //Each distance starts out as infinity
        }
    }

    /*
    distance_matrix contains a 2d long matrix of INF of num_vertices by num_vertices size
    num_vertices contains the number of vertices
    */

    //Parse the number of edges into the matrix
    if ( !file.eof() ) {
        string to_insert;
        string first_input, second_input, third_input;
        char first_vertex, second_vertex;
        long edge_weight;
        while( !file.eof() ) {
            getline( file, to_insert ); //Trades to our input via a string object
            line_number++; //Increase the line number we are at
            iss.str( to_insert ); //Cannot go directly to an input stream itself
            //Parsing for our expected formats
            if( !(iss >> first_input) ) { //Parse the first vertex
                cerr << "Error: Invalid edge data '" << to_insert << "' on line " << line_number << "." << endl;
                cleanup( distance_matrix, num_vertices);
                return 1;
            }
            if( !(iss >> second_input) ) { //Parse the second vertex
                cerr << "Error: Invalid edge data '" << to_insert << "' on line " << line_number << "." << endl;
                cleanup( distance_matrix, num_vertices);
                return 1;
            }
            if( !(iss >> third_input ) ) {
                cerr << "Error: Invalid edge data '" << to_insert << "' on line " << line_number << "." << endl;
                cleanup( distance_matrix, num_vertices);
                return 1;
            }
            if ( first_vertex < 'A' || first_vertex > ('A' + num_vertices-1)) {
                cerr << "Bad vertex inserted" << endl;
                cleanup( distance_matrix, num_vertices);
                return 1;
            }
            if ( second_vertex < 'A' || second_vertex > ('A' + num_vertices-1)) {
                cerr << "Bad vertex inserted" << endl;
                cleanup( distance_matrix, num_vertices);
                return 1;
            }
            //The Edge Weight
            else {
                //All the input was correct
                int row = first_vertex - 'A';
                int col = second_vertex - 'A';
                if (distance_matrix[row][col] != INF) {
                    cerr << "Edge has been repeated" << endl;
                    cleanup( distance_matrix, num_vertices);
                    return 1;
                }
                else {
                    distance_matrix[row][col] = edge_weight;
                }
            }
        }
    }
    else {
        cerr << "No lines were included" << endl;
        cleanup( distance_matrix, num_vertices);
        return 1;
    }

    display_table(distance_matrix, "Just for fun", num_vertices );

    //Cleanup
    cleanup( distance_matrix, num_vertices); //Delete the distance_matrix

    return 0; //Everything worked fine
}