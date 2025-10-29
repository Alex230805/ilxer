# iLxer: an improved version of lxer simple lexer 


> [!WARNING]  
> This is NOT a production ready library, but is somethings that could be usefull in multiple parsing context. 


## Improved version of lxer 

This is an evolution of the homonymous project lxer, it's a simple and fast general purpose lexer that can be 
usefull in situations where there is a need for a tokenizer and you don't want to import a very bloated external
lexer.

iLxer is not meant to be "ergonomic" for the user, it doesn't have much functionality to begin with, but only the 
basic tokenization capability and token identification functions that can be used to implement anything from 
simple parser to more complex and elaborated algorithm.

The main structure is similar to the original lxer, but with this fork there are new improvement on the parsing 
process with the addition of a simple syntax control for specific tokens. This means that for some tokens is possible 
to specify if they need to be separated by a space or not, and this can help in many situation where some names may 
contain a token, for example "int" inside the "internal" word and so on. With this addition the tokenizer will recognise 
"int" only if it is separated by a space to avoid unwanted behaviour.
The list of tokens that need to be separated by a space are defined inside a macro in the main header file, 
search for "TOKEN_ISOLATED()" macro.


### Compound expressions 

iLxer introduce the concept of "compound expressions" which are a group of standard tokens that share some sort of 
relation, like creating a bigger token from a group of simple one. This can be used for example for fast pattern-matching 
parsing context where you have to parse group of token very often, for examle "===" which is a group of "=" repeated 
three times.
Those cane be defined easily from the configuration file, look for "DECLARE_COMPOUND_TABLE()" macro used inside "ilxer_default_config.h"

### Fast config syntax 

Modifying the lexer to change the name of a token or the matching word for a token may be a bit hard with the previous design 
where all the main token declaration where just a group of X macro wrapper with poor organization with a lack of simplicity 
for immediate modification. 
So the "ilxer_default_config.h" was introduced to define a simple syntax with the use of the C preprocessor to fast declare 
the entier configuration of ilxer from the token list to the compound expression within a single file. This is 
by default included inside the ilxer.h if the preprocessor flag "STRIP_DEFAULT_IMPLEMENTATION" is not defined. This means that 
if you want to change the mask/configuration of the entire lexer you can simply add a new configuration file and include it 
inside your project and enable the "STRIP_DEFAULT_IMPLEMENTATION" preprocessor flag before including "ilxer.h", this will strip 
of the default configuration letting you decide what rule the lexer must follow.
This was introduced also to separate the configuration from the source code, allowing simple dependencies update by just updating 
only the ilxer.c and ilxer.h without changing your configuration file. Before this functionality was added you had to reconfigure your 
lexer each time after every update to adapt it again to your project. Now you can just define your own configuration and then use 
that inside ilxer with ease.

### Source-code related function

This library include a simple group of function to interact directly with the source code to grep informations like string or 
variable names. Those functions will return a copy of the word before or after ( depending of the provided flag ) the current 
pointed token by the lxer head. 
String literals are not parsed by default by ilxer since it does not support a "mode switching" state, but it have a function 
called "lxer_get_string" that can copy the source code content from the current position to a defined token destination, and this 
can be used to copy a stream of byte that may contain the string literal by jut placing the lxer cursor in the quote token and then 
calling this function to copy the stream from the current quote to the next one inside the stream of token, and this will return a 
copy of this cropped source code stream that can contain the string literal. 


### iLxer precise mode 

Some times it would be usefull to tokenize more informations for general use, maybe for error handling or just to have a more 
general lexer. For that a "precise" mode has been introduced to parse every single word inside a text file and sign the 
unexpected one ( the ones that are not present in the token table configuration file ) will be flagged as a "LXR_WORD" token. 
This mode is not enabled by default since it will use more memory and general computational power to just parse a test file, 
and for that matter since the point of ilxer is having a simple and fast lexer the whole precise mode it's just a plus 
that someone may or may not activate depending on what the requirement are. 
This mode can be enabled by activating the "ILXER_PRECISE_MODE" preprocessor flag during compilation or directly in the header 
file of ilxer to enable the second half of the lexer function and to start parsing every single token. 

This type of token have as a byte_pointer a separated string which contain the word tokenized as LXR_WORD, this will not allow 
the fuction like "lxer_get_rh()" or "lxer_get_rh_lh()" to work properly with this token since those functions are suppose to be 
used when this mode is disabled to get text between two tokens, and since now every text not recognized as a token will be casted 
as a separate token LXR_WORD it's useless to rely on those two functions to get the right hand or left hand content from the 
current pointed token. If this mode is enabled the function "lxer_get_word()" will return directly the string pointer of the LXR_WORD token.


