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