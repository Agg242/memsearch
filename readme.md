# MemSearch

Small cli utility to search in Amiga memory.

Investigating process hunks, I coded this small utility to follow/understand seglists and hunks.


## Usage

`memsearch STRING/K,LONG/K,START/K,END/K`

```
5.Files:Dev/C/Projets/memsearch
> memsearch string library start 0x01800000 end 0x01820000                             
Found at 0x01811056
Found at 0x01811BCE
5.Files:Dev/C/Projets/memsearch
> memdump 0x01811050 32                             
Address: 01811050  size: 32
0000: 533a766e 632e6c69 62726172 79000000 S:vnc.library...
0010: 01811018 059d9cca 00000000 00000001 ................
5.Files:Dev/C/Projets/memsearch
> memdump 0x01811bc0 32                             
Address: 01811bc0  size: 32
0000: 1bd60181 1bf27665 7273696f 6e2e6c69 ......version.li
0010: 62726172 79007665 7273696f 6e203437 brary.version 47
```


## Build

Built with VBCC.
Any submitted improvement to another compiler would be integrated.

I use some kind of utility sources for C, grouped in a SRCLIB:ez-C folder, including a useful dbg/dbg.h full of debug macros.
These sources can be found in another repo: 
https://github.com/Agg242/ez-C

After adding it, you build with "make all"



