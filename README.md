# SCPI_parse
 Parser prototype(job in progress)
## FILES
-main.c - initialization of command trees, and basic structs. Call for processing functions.

-parser.c - functions for processing of cmd tree.
```process_tree``` needed for recursive bypass of tree elements
```choose_root``` needed to determine which tree needed, and handle its root to 
```process_tree```.

-parser.h - typedefs and needed structs. Function prototypes.