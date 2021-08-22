# Bracket Expansion

## Problem Description

Implement a similar behavior to bash's brace expansion behavior as a runnable program.

For a valid input, print the output. For an invalid input, print nothing and exit.

### Considerations

- Any input without properly matching braces is invalid
- Commas should only appear within braces.
- Restrict the input character set to \[a-zA-Z\{\},\]
- Braces should not be empty, and there should be no "empty" options within braces i.e. {A,}

### Examples of Valid Input
- {A,B,C} -> A B C
- AB{C,D} -> ABC ABD
- {A,B}{C,D} -> AC AD BC BD
- {A,B{C,D}} -> A BC BD
- {{A},{B}} -> A B
- {ABC} -> ABC
- ABC -> ABC

###  Examples of invalid input
- }ABC
- {ABC
- }{
- {}
- A,B,C
- A B C
- {A{B,C}
- {A,}

## Notebook Solutions

To practice with the problem in a more iterative environment and language I implemented a first solution in python.
Attached to the project is a 'notebooks' directory. You can see the results of my initial prototyping process there.
After identifying the main algorithm pattern and some use cases I attempted a c++ solution within jupyter as well.

Through the simplified python implementation I noticed some areas where a class structure with member variables might
be more beneficial. So I began the c++ solution with cleaner code in mind now that I had proved my concept in python.

To configure the jupyter notebook environments please run the setup bash command provided. 
To actually run the notebooks please run the start bash command provided.

## Main Solution

THe main solution is provided in the src directory, with accompanying tests running GoogleTest in the test directory.
The Cmake files should pull the GoogleTest dependency but the src code can be built independently if desired.

