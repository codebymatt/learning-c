// Ex: Rewrite the function lower, which converts upper case letters to lower case, 
// with a conditional expression instead of if-else .

// Trivial example so not going to bother with input and output

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}