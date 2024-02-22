# Next Steps

Learn more about Bison, how does it work and start generating grammar for the parsing table: https://www.gnu.org/software/bison/
The approach described seems a good way to complete your project. Here are some points to consider and some recommendations on how to proceed:

## Summary of next steps

1. Tokenizer: done
2. Parsing Table: done
3. Use shift-reduce parsing algo to create parsing tree: https://www.geeksforgeeks.org/shift-reduce-parser-compiler/ && https://youtube.com/results?search_query=shift+reduce+parsing

## Edge Cases Tokenizer

- `"echo \"Hello World\" | cat -e"` works but `"echo "Hello World" | cat -e"` doesnt