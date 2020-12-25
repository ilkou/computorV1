#include <computor.h>

Node* newNode(double coef, int power) 
{ 
    Node* new_node = new Node(); 
  
    new_node->coef = coef;
    new_node->power = power;
    new_node->next = NULL; 
    return (new_node); 
}

string removeSpaces(string str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}