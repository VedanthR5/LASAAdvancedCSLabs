 

# **Lab: Hash codes with Chaining**

The hash (unordered_set) lab provides an opportunity to implement a hash table using chaining.

You will utilize your previous linked list code.  The link list node will not use the *data payload pointer, but will need a string key field.

Submission form to be posted on BLEND.   All submissions should be your original work.

Important points in main.cpp:

- A brief menu is provided that can direct input to the program from 1) stdin or 2) a file.  
    - Input is terminated by an empty line, or the word "END".
    - If you choose to use a file you may provide the name of a different file or simply hit <enter> to accept the default.   The default file includes a small array is provided in "data.txt" that can be usedfor debugging.  
    -    You may create other files for testing.
    -    The format for the data is <operation>:<data>  
        -    The <operation> may be;  
            - A|a - Add the integer value (ex. A: 10)
            - D|d - Delete the value (ex. d: 10)
            - T|t - Creates a HashTable with size (ex. t:16).
                - Any previous table is discarded.
                - This should be first operation in the list.
- Do not modify the main.cpp file or any of the informational routines such as; printTable(), printHistogram(), getNumberOfElements(), printList(), or any other supporting routine.
- You should use your linked list code from the earlier lab
- For the entrys in the HashTable and LinkedList use the definition of Element instead of node.  Notice the payload \*data is now a string called "key" //**********************************************************
// List Elements are keys with pointers to the next item.
//**********************************************************
struct Element
{
    string key;
    Element * next;
};
- Fee free to pull this code into an IDE of you choice.  Anything that supports breakpoints and single step debugging may be helpful.  If you must use an online solution (as needed if you are using a chromebook), I recommend onlinegdb.com.  I have used it and it works well.  There are others that might be worth exploring like codesandbox.com.