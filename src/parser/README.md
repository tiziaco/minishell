## Summary of next steps

1. Tokenizer: done
2. Minishell Grammar: done
2. Parsing Table based on grammar: done
3. read parsing table into a pointer struct array: done
3. Use shift-reduce parsing algo to create parsing tree: https://www.geeksforgeeks.org/shift-reduce-parser-compiler/ && https://youtube.com/results?search_query=shift+reduce+parsing

## Edge Cases Tokenizer

- `"echo \"Hello World\" | cat -e"` works but `"echo "Hello World" | cat -e"` doesnt


## Learnings

- Why do we need a stack and a parsing tree linked list data structure?
    - If we have the input `"echo "Hello World" | cat -e"` we initially encounter the terminal WORD_TOKEN (i.e. "echo"), which 



    You start by shifting tokens one by one into the stack, following rules determined by the parsing table. When a reduce operation is encountered, a certain number of items are popped from the stack to form a subtree. This subtree is then added back into the parse tree (not the stack) which is being constructed during the parsing process.






    ## Next things to do
    - figure out how to best add the parsing tree to the cmd_struct
    - what kind of structure makes the most sense?