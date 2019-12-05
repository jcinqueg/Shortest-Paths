/*******************************************************************************
 * Name         : shortestpaths.cpp
 * Author       : John Cinquegrana and Megha Mansuria
 * Version      : 1.0
 * Date         : January 9, 2016
 * Description  : Reieves a directed graph as input and determines all the shortest
 *                  possible paths that can be taken within that text file.
 * Pledge       : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/


#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <utility>

using namespace std;

long INF = numeric_limits<long>::max();

/**
 * Returns the number of digits required to write out a number in base ten.
 */
int len( long num ) {
    if( num < 10) return 1;
    else return 1 + len( num / 10);
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

/**
 * Deletes the two dimensional array that is passed into it.
 */
void cleanup( long** const matrix, int length ) {
    for( int i = 0; i < length; i++) {
        delete[] matrix[i]; //Delete each subarray in matrix
    }
    delete[] matrix; //Then delete the matrix itself
}

/**
 * Counts the number of words, seperated by whitespace, that appear in a string.
 */
int count_words( string str ) {
    int count = 0;
    bool was_whitespace = true;
    for( auto ch = str.begin(); ch <= str.end(); ++ch) {
        char check = *ch;
        if( isspace( check ) ) {
            was_whitespace = true;
        }
        else {
            if( was_whitespace ) {
                count++;
            }
            was_whitespace = false;
        }
    }
    return count;
}

/**
 * Returns an OSS object that contains the specified word in the string. Words are
 * groups of non-whitespace characters and are delimited by whitespace.
 */
ostringstream get_word( string str, int num ) {
    int count = 0;
    bool was_whitespace = true;
    ostringstream end;
    for( auto ch = str.begin(); ch <= str.end(); ++ch) {
        char check = *ch;
        if( isspace( check ) ) {
            was_whitespace = true;
        }
        else {
            if( was_whitespace ) {
                count++;
            }
            was_whitespace = false;
            if( count == num ) {
                end << check;
            }
        }
    }
    return end;
}

/**
 * Employs floyd's algorithm to find a matrix consisting of the intermediary values of paths.
 * Changes the passed in mat matrix to be that matrix's transitive closure.
 */
long** floyd(long** mat, int num_vertices) {
    //Creating the array to be filled with intermediaries
    long** intermediates = new long*[num_vertices]; //Rows
    for( int i = 0; i < num_vertices; i++) {
        intermediates[i] = new long[num_vertices]; //Columns
        for( int j = 0; j < num_vertices; j++) {
            intermediates[i][j] = INF; //Each intermediate begins as nothing
        }
    }
    //The long matrix will be altered to contain it's transitive closure
    for( int k = 0; k < num_vertices; k++) {
        for( int i = 0; i < num_vertices; i++) {
            for( int j = 0; j < num_vertices; j++) {
                if( mat[i][k] != INF && mat[k][j] != INF && mat[i][j] > mat[i][k] + mat[k][j] ) {
                    //We have some replacing to do
                    mat[i][j] = mat[i][k] + mat[k][j];
                    intermediates[i][j] = k;
                }
            }
        }
    }
    return intermediates;
}

void find_paths_helper( long** const intermediates, long from, long to ) {
    //Find the intermediary
    long inter = intermediates[from][to];
    if( inter == INF )  {
        cout << " -> " << (char)('A'+to);
    }
    else {
        find_paths_helper( intermediates, from, inter );
        find_paths_helper( intermediates, inter, to );
    }
}

/**
 * INPUT:
 *  distances: a 2-dimensional matrix of longs indexed as distances[row][column]. It contains
 *      the length of the shortest path between two vertices.
 *  intermediates: a 2-dimensional matrix of longs. The matrix is of longs for convenience, you
 *      should think of it as a character matrix. at intermediates[row][col] is the vertex that
 *      serves as the intermediate in the path between the two. This is what you'll be using to
 *      recurse over in the tree-way he showed during class.
 *  length: an integer containing the length of each matrix. Each matrix is a square with the same
 *      amount of rows and columns. Both have exactly length many rows and columns.
 * OUTPUT TO CONSOLE:
 *  This function is made to output all paths that can be found, and their minimum distance, as is
 *  shown with the test cases.
 * TIPS:
 *  The vertexes are named by capital letters but are referred to in code by longs and numbers. the
 *      vertex 'A' is referred to as 0, 'B' as 1, and so on. No vertex should have a value of length
 *      or greater.
 *  I recommend writing only one helper function. This function will print everything up until the
 *      colon, and the helper would print the actual path. Going down the tree is easiest with
 *      recursion, but it only needs the intermediates table, and two verticies, it doesn't need to
 *      bother with the rest of the inputs. Doing this in a helper makes it much more manageable.
 */
void find_paths( long** const distances, long** const intermediates, int length ) {
    for( long first = 0; first < length; first++ ) {
        for( long second = 0; second < length; second++ ) {
            if ( distances[first][second] < INF ) {
                //The path exists
                cout << (char)('A'+first) << " -> " << (char)('A'+second)
                << ", distance: " << distances[first][second] << ", path: " << (char)('A'+first);
                if( first != second ) find_paths_helper( intermediates, first, second );
                cout << endl;
            }
            else {
                cout << (char)('A'+first) << " -> " << (char)('A'+second)
                << ", distance: infinity, path: none" << endl;
                //The path does not exist
            }
        }
    }
}

/**
 * Parses the input data into a single matrix than passes it through floyd's algorithm
 * and prints the results.
 */
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

    string to_insert;
     // istringstream iss was declared above

    if ( getline(file, to_insert ) ) {
        line_number++;
        iss.str( to_insert );
        if( !(iss >> num_vertices) || num_vertices < 1 || num_vertices > 26 ) {
            //Put the number of vertices into num vertices
            cerr << "Error: Invalid number of vertices '" << to_insert << "' on line " << line_number << "." << endl;
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
            distance_matrix[i][j] = (i == j) ? 0 : INF; //Each distance starts out as infinity
        }
    }

    /*
    distance_matrix contains a 2d long matrix of INF of num_vertices by num_vertices size
    num_vertices contains the number of vertices
    */

    //Parse the number of edges into the matrix
    //  string to_insert was declared above
    char first_vertex, second_vertex;
    long edge_weight;
    //Iterates to the next line

    //Starts the parsing loop
    while( getline( file, to_insert ) ) {
        line_number++; //Increase the line number we are at
        iss.str( to_insert ); //Cannot go directly to an input stream itself
        //Parsing for our expected formats
        //Checking to make sure we have exactly three components
        if( count_words( to_insert ) != 3) {
            cerr << "Error: Invalid edge data '" << to_insert << "' on line " << line_number << "." << endl;
            cleanup( distance_matrix, num_vertices);
            return 1;
        }
        //Parsing the first vertex
        iss.str( get_word( to_insert, 1).str() );
        if ( !(iss >> first_vertex) || first_vertex < 'A' || first_vertex > ('A' + num_vertices-1)) {
            cerr << "Error: Starting vertex '" << get_word( to_insert, 1).str() << "' on line " << line_number << " is not among valid values A-" << (char)('A' + num_vertices-1) << "." << endl;
            cleanup( distance_matrix, num_vertices);
            return 1;
        }
        //Parsing the ending vertex
        iss.str( get_word( to_insert, 2).str() );
        if ( !(iss >> second_vertex) || second_vertex < 'A' || second_vertex > ('A' + num_vertices-1)) {
            cerr << "Error: Ending vertex '" << get_word( to_insert, 2).str() << "' on line " << line_number << " is not among valid values A-" << (char)('A' + num_vertices-1) << "." << endl;
            cleanup( distance_matrix, num_vertices);
            return 1;
        }
        //Parsing the edge weight
        iss.str( get_word( to_insert, 3).str() );
        if ( !(iss >> edge_weight) || edge_weight < 1) {
            cerr << "Error: Invalid edge weight '" << get_word( to_insert, 3).str() << "' on line " << line_number << "." << endl;
            cleanup( distance_matrix, num_vertices);
            return 1;
        }
        //All the input data is correct for an edge
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
        //Iterates to the next line
    }

    display_table(distance_matrix, "Distance matrix:", num_vertices );
    long** intermediates = floyd( distance_matrix, num_vertices );
    display_table( distance_matrix, "Path lengths:", num_vertices );
    display_table( intermediates, "Intermediate vertices:", num_vertices, true );
    //Finding paths
    find_paths( distance_matrix, intermediates, num_vertices );
    //Cleanup
    cleanup( distance_matrix, num_vertices); //Delete the distance_matrix
    cleanup( intermediates, num_vertices );

    return 0; //Everything worked fine
}