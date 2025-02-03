# multicfg

a config manager equivalent to JSON written for C

it works the same but every tree is a single node
nested nodes are not implemented yet it supports strings

# here's how it works:


`find_node_start();` is first function to find node and initial `cords` structure
first off, you pass cords struct, filename, node name and size of it

it iterates into that file and copying it into a 2d buffer
then it iterates again into that buffer to finds the row that is start of desired node by a comparison procedure

that row then copied into `cords->start` to be used in `find_row_end();`

the process of finding the end or length of node starts in `find_node_end();` function

it iterates from `cord->start` and evaluating times that curly backets appeared in buffer then `cords->end` is founded

**and final step is finding the value of key in node children**

now we got both start and end range to lookup
we got another member in cords named `value` to save string data from key

theres another comparison on node children till we finally found the one we want
