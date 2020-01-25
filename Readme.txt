CPSC 3500 Computing Systems
Project 1: Implementing a Simple Shell Using Multi-Processing
1/22/20
----------
Strengths
----------
• Passes all tests
• Is able to handle large amounts of data in the example of the last test given
• Very functionally decomposed with each module performing a single action
----------
Weaknesses
----------
• Might not handle every possible error case, major ones are covered.
• Edge cases might not be 100% covered, however many should be.
• Get commands and get tokens are very similar almost to the point of warrenting functional decomposition however due to our implementation of the two functions seperating spaces and pipes in respect to quotations that they act fundamentally different and functional decomposition would be difficult in this case.
----------------------------
Team Members & Contributions
-----------------------------
Nick Doubrovsky
• Coded the command and token parsing
• Functionally decomposed our program and made sure the main function was simple and easy to follow
• Bug testing/fixing
• Error handling
• dup2 and creating children

Eddie Avendano
•Reserved study room for initial team meeting
•Typed out pseudocode for main
•Created exit() function that makes the parent wait for the 
child processes to be killed and shows when each child is killed
•Helped debug and test commands

Marco Rodriguez
•Organized the team over github and managed source control
•Created the makefile
•Created the readme file
•Provided testing for command tests 
•Provided aid in debugging our program such as with the getCommands and createPipes function
