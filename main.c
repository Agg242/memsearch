#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// no alignment error
#pragma dontwarn 307 
#include <exec/exec.h>
#include <exec/execbase.h>
#include <proto/dos.h>
#pragma popwarn

#include <dos/dos.h>

#include <dbg/dbg.h>


// get read of suspicious format string
#pragma dontwarn 214

#pragma dontwarn 168
const char __ver[] = "$VER: Memory Search 1.0 (16/02/2025)";
#pragma popwarn


#define ARG_STRING 0
#define ARG_LONG   1
#define ARG_START  2
#define ARG_END    3
#define PARAMS_MAX 4


// Execbase pointer cast
//#pragma dontwarn 81
// todo: use ExecBase
//#pragma dontwarn 65

static void search_blob(UBYTE *blob, ULONG size, UBYTE *start, UBYTE *end)
{
    int blob_pos;
    UBYTE *pos = start;
    while(pos < (end - size))
    {
        blob_pos = 0;
        while(blob_pos < size)
        {
            if(blob[blob_pos] == pos[blob_pos])
            {
                blob_pos++;
            }
            else
            {
                break;
            } 
        }
        
        if(blob_pos == size)
        {
            printf("Found at 0x%08lX\n", pos);
        }
        
        pos++;
    }
    
} 


static void search_ulong(ULONG value, UBYTE *start, UBYTE *end)
{
    search_blob((UBYTE *)&value, sizeof(value), start, end);
}

static void search_string(char *str, UBYTE *start, UBYTE *end)
{
    search_blob(str, strlen(str), start, end);
}



int main(void)
{
    int res = RETURN_WARN;
    struct RDArgs *args = NULL;
    LONG  params[PARAMS_MAX];
    LONG err = 0L;
    UBYTE *start, *end;
    char template[] = "STRING/K,LONG/K,START/K,END/K";
    int i;
    
    for(i = 0; i < PARAMS_MAX; i++)
    {
        params[i] = 0L;
    }
    
    args = ReadArgs((STRPTR)template, params, NULL);
    if(NULL == args)
    {
        err = IoErr();
        PrintFault(err, "Error");               
        printf("Usage: memsearch %s\n", template);
        sentinel("No args");
    }
    else
    {
        check(((0L != params[ARG_STRING]) || (0L != params[ARG_LONG])), "Choose either string or long to search for");
        check(((0L != params[ARG_START]) && (0L != params[ARG_END])), "Don't be shy, give me start and end addresses");

        start = (UBYTE *)strtol((char *)params[ARG_START], NULL, 0);
        check(start != NULL, "Bad start address: %s", (char *)params[ARG_START]);
        end = (UBYTE *)strtol((char *)params[ARG_END], NULL, 0);
        check(end != NULL, "Bad end address: %s", (char *)params[ARG_END]);
        
        if(0L != params[ARG_LONG])
        {
            search_ulong(*((ULONG*)params[ARG_LONG]), start, end);
        }
        else
        {
            search_string((char *)params[ARG_STRING], start, end);
        }
        
        // check args corrects
        //  ck start unit
        //  ck end uint
        //  si long, ck long uint
        
        
        
        
    }    
        

    res = RETURN_OK;
    
    
on_error:
    FreeArgs(args);
   return res; 
}
