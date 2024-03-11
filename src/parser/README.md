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
-   You start by shifting tokens one by one into the stack, following rules determined by the parsing table. When a reduce operation is encountered, a certain number of items are popped from the stack to form a subtree. This subtree is then added back into the parse tree (not the stack) which is being constructed during the parsing process.


## Edge cases

- What about two redirections in the same command line?
    - `ls < input.txt >> output.txt | grep 'keyword' > filtered_output.txt << EOF\n content_here \nEOF`
- Still a weird error with super long echoes


## Things to do next
- fix memory leaks (check is the allocation with one array too much works (since you are using array_index but argc))
- possibly implement prefixes
- expansion, single quotes, dobule quotes

