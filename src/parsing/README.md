# Next Steps

Learn more about Bison, how does it work and start generating grammar for the parsing table: https://www.gnu.org/software/bison/
The approach described seems a good way to complete your project. Here are some points to consider and some recommendations on how to proceed:

## Summary of next steps

1. Parsing Table: Given your requirements, generating a parsing table manually (like shown in the description) seems feasible, considering the grammar of your shell isn't that complex. 

2. Lexer & Parser: Having your lexer complete is a good starting point. However, your task may be much simplified by the effective use of a lexer-parser generator like Flex & Bison or ANTLR, should you decide to use them. Granted, they may generate code that doesn't comply with your school's code style requirements, but it could work as a good reference.

3. Software Design: Remember to decouple the lexer and the parser as much as possible. They should do their own jobs and communicate with a simple interface. It would make it easier for testing and maintenance.

4. Parser: A Recursive Descent Parser could be simple and effective choice for your project. Each production rule will be a function and it will recursively call other functions based on the production it needs to match.

5. Implementations: Create functions to handle each rule. e.g., 
```C
void pipe_sequence(...) {
  simple_command(...);
  if (... match '|') {
    pipe_sequence(...);
  }
}
```
6. Error Handling: Ensure to correctly handle error cases and provide meaningful error messages. Be wary of infinite looping in erroneous condition.

7. Testing: Finally, do not forget to use extensive testing. It helps to uncover issues early.

In summary, the logical steps you've found will work for the project. Understanding how to manually build the parsing table is a great exercise. However, do not be discouraged to explore and use existing tools that will simplify your job if they match the project requirements.
