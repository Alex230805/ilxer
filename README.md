# iLxer: an improved version of lxer simple lexer 


> [!WARNING]  
> This is NOT a production ready library, but is somethings that could be usefull in multiple parsing context. 


## Improved version of lxer 

This is an evolution of the homonymous project lxer, it's a simple and fast general purpose parser that could be 
usefull in situations where there is a need for a tokenizer and you don't want to import a very bloated external
parser.

iLxer is not meant to be "ergonomic" for the user, it doesn't have much functionality to begin with, but only the 
basic tokenization capability and token identification functions that can be used to implement anything from 
simple parser to more complex and elaborated algorithm.

The main structure is similar to the original lxer, but with this fork there are new improvement on the parsing 
process with the addition of a simple syntax control for specific tokens. This means that for some tokens is possible 
to specify if they need to be separated by a space or not, and this can help in many situation where some variable 
name may contain a token, for example "int" inside the "internal" word. With this addition the tokenizer will recognise 
"int" only if it is separated by a space to avoid unwanted behaviour.

#### This list is easily modifiable, for more information take a look to ilxer.c file. 


This library include a very basic "left hand" and "right hand" get function to fetch the prefious word or the next word 
by having the current token as the reference. This is referred to just normal word and not token, for example the string 
"zeno = 'god'" with the tracker pointing at "=" will have "zeno" as left hand, but the right hand here will result to 
be invalid becase there is nothing different from a token between the "=" and "'" ( which is the following token after " ");


### Line tracking 

There is no function to track the line of each token, insted the library provide a slice array of token with the corresponding 
tokens and pointers. This is a deliberate decision that allow the implementation of a more accurate line tracker depending 
on the user case, this is a direct reference to the concept of "adapting" before using. 


## Pitfalls 

This is a simple library, but with it simplicity comes some problems, and the majority of them is basically about the "plug and play"
concept that in this library did not exist. 
With this I mean that to be able to use the library you need first to adapt it to your own use case, and depending from what it is it 
may require the implementation of many more function and wrapper to turn iLxer in something usefull for your project, and example is 
the line tracking method that is non existent, also each token must be defined and customized before start to parse something. 
Since it is so simple for general purpose project, simple parsers or anything that involve text to token translation, but for more 
complext project, with lots of specification that are required even on a level of the tokenizer this library is not the one you should 
use, especially if you need to add a lot of line of code just to make it running like you want. 




