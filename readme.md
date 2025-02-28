# MemSearch

Small cli utility to search in Amiga memory.

Investigating process hunks, I coded this small utility to follow/understand seglists and hunks.


## Usage

memsearch STRING/K,LONG/K,START/K,END/K


## Build

Built with VBCC.
Any submitted improvement to another compiler would be integrated.

I use some kind of utility sources for C, grouped in a SRCLIB:ez-C folder, including a useful dbg/dbg.h full of debug macros.
These sources can be found in another repo: 
https://github.com/Agg242/ez-C

After adding it, you build with "make all"



