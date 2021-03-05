#include <iostream>
#include <cassert>

using namespace std;
#include "pictapi.h"

#define PAIRWISE 2

int main()
{
    PICT_RET_CODE ret = PICT_SUCCESS;
    PICT_HANDLE task = PictCreateTask();

    PICT_HANDLE model = PictCreateModel();
    
    PictSetRootModel( task, model );

    unsigned int weights[] = {1, 2, 1, 1};
    PICT_HANDLE p1 = PictAddParameter( model, 4, PAIRWISE, weights );
    PICT_HANDLE p2 = PictAddParameter( model, 3, PAIRWISE );
    PICT_HANDLE p3 = PictAddParameter( model, 5, PAIRWISE );
    PICT_HANDLE p4 = PictAddParameter( model, 2, PAIRWISE );    
    PICT_HANDLE p5 = PictAddParameter( model, 4, PAIRWISE );
    
    ret = PictGenerate( task );

    PICT_RESULT_ROW row = PictAllocateResultBuffer( task );
    size_t paramCount = PictGetTotalParameterCount( task );
    PictResetResultFetching( task );

    while( PictGetNextResultRow( task, row ))
    {
        for( size_t index = 0; index < paramCount; ++index )
        {
            wcout << static_cast<unsigned int>( row[ index ] )<< L" ";
        }
        wcout << endl;
    }

    PictFreeResultBuffer( row );

    if( model != NULL )    
    {
        PictDeleteModel( model );
    }

    if( task != NULL )    
    {
        PictDeleteTask( task );
    }

    return 0;
}