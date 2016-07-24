//// Basic implementation of the icalcterm interface

#include "icalcterm/icalcterm.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>

#define EXPORT __attribute__ ((visibility ("default"))) 

bool parse_number( char const* input, double& result );

extern "C" {

void EXPORT CI_init( CI_Config* config )
{
    // Not implemented
}

void EXPORT CI_config( CI_Config* )
{
    // Not implemented
}

// Note: this function returns a pointer, but for some strange
// reason we must put the asterisk after the EXPORT.
CI_Result EXPORT * CI_submit( char const* input )
{
    double number;
    if( !parse_number( input, number ) )
        return NULL;

    std::ostringstream ss;
    ss << number;
    std::string result = ss.str();

    CI_Result* res = new CI_Result;

    res->input_one_line  = strdup( input );
    res->output_one_line = strdup( result.c_str() );

    res->input_grid_rows  = 1;
    res->output_grid_rows = 1;

    res->input_grid  = new char*[res->input_grid_rows];
    res->output_grid = new char*[res->output_grid_rows];

    for( int i = 0; i < res->input_grid_rows; ++i )
        res->input_grid[i] = strdup( input );
    for( int i = 0; i < res->output_grid_rows; ++i )
        res->output_grid[i] = strdup( result.c_str() );

    return res;
}

void EXPORT CI_result_free( CI_Result* result )
{
    free( result->input_one_line );
    free( result->output_one_line );

    for( int i = 0; i < result->input_grid_rows; ++i )
        free( result->input_grid[i] );
    for( int i = 0; i < result->output_grid_rows; ++i )
        free( result->output_grid[i] );

    delete[] result->input_grid;
    delete[] result->output_grid;

    delete result;
}

} // extern "C"
