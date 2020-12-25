#include <computor.h>
#include <float.h>
#include <limits>

// a * x² + b * x + c = 0
//https://en.cppreference.com/w/cpp/regex/regex_token_iterator/regex_token_iterator
//https://codes-sources.commentcamarche.net/source/9533-resolution-d-une-equation-du-second-degre-devc-en-c

string rgx_double = "[0-9]+(\\.[0-9]*)?";
string rgx_spaces = "\\s*";
string rgx_power = "[0-9]+";//"[012][^0-9]";//"[+-]?[0-9]{1,13}(\\.[0-9]*)?";
string rgx_exp1 = rgx_spaces + rgx_double + rgx_spaces + "\\*" + rgx_spaces + "[xX]" + rgx_spaces + "(\\^" + rgx_spaces + rgx_power + rgx_spaces + ")?";
string rgx_exp2 = rgx_spaces + "[xX]" + rgx_spaces + "(\\^" + rgx_spaces + rgx_power + rgx_spaces + ")?" + "\\*" + rgx_spaces + rgx_double + rgx_spaces;
string rgx_exp3 = rgx_spaces + "(" + rgx_double + rgx_spaces + "\\*)?" + rgx_spaces + "[xX]" + rgx_spaces + "(\\^" + rgx_spaces + rgx_power + rgx_spaces + ")?";
string rgx_exp4 = rgx_spaces + rgx_double + rgx_spaces + "(\\*" + rgx_spaces + "[xX]" + rgx_spaces + "(\\^" + rgx_spaces + rgx_power + rgx_spaces + ")?)?";
string rgx_exp5 = rgx_spaces + "[xX]" + rgx_spaces + "(\\^" + rgx_spaces + rgx_power + rgx_spaces + ")?" + "(\\*" + rgx_spaces + rgx_double + rgx_spaces + ")?";
string rgx_exp6 = rgx_spaces + "([xX]" + rgx_spaces + "(\\^" + rgx_spaces + rgx_power + rgx_spaces + ")?" + "\\*)?" + rgx_spaces + rgx_double + rgx_spaces;

Equation::Equation(void) {
    head = NULL;
    degree = 0;
    a = 0.0;
    b = 0.0;
    c = 0.0;
    d = 0.0;
}
Equation::~Equation(void) {
    Node* current = head;
    while( current != NULL ) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = NULL;
}

void    Equation::insertPart(double coef, int power) {
    Node** head_ref = &head;
    Node* new_node;
    Node* current;

    new_node = newNode(coef, power);
    if (*head_ref == NULL || (*head_ref)->power > new_node->power) { 
        new_node->next = *head_ref; 
        *head_ref = new_node; 
    }
    else {
        current = *head_ref; 
        while (current->next != NULL && current->power < new_node->power) { 
            current = current->next; 
        }
        if (current->power == new_node->power) {
            current->coef += new_node->coef;
            delete new_node;
        }
        else {
            new_node->next = current->next; 
            current->next = new_node; 
        }
        
    }
}
void Equation::setCoefs(void) {
    Node* current = head;

    while (current != NULL && current->coef == 0.0) {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head = current;
    while (current != NULL) {
        if (current->power == 0)
            c = current->coef;
        else if (current->power == 1)
            b = current->coef;
        else if (current->power == 2)
            a = current->coef;
        else if (current->power == 3)
            d = current->coef;
        if (current->coef != 0.0)
            degree = current->power;
        current = current->next;
    }
    if (d != 0.0) {
        a /= d;
        b /= d;
        c /= d;
    }
}

void    Equation::parseEquation(const char *eq) {
    string var(eq);
    var += " ";
    
    regex rgx_nd_part("(=.*)");
    regex rgx_sign("^([+-]).*");

    string rgx_exp =
    "(=?" + rgx_spaces + "[-+]?"
        + "("
            + rgx_exp1
                + "|"
            + rgx_exp2
                + "|"
            + rgx_exp3
                + "|"
            + rgx_exp4
                + "|"
            + rgx_exp5
                + "|"
            + rgx_exp6
        + ")"
    + ")";
    regex e(rgx_exp);

    // default constructor = end-of-sequence:
    regex_token_iterator<string::iterator> rend;

    //cout << "entire matches:" << endl;
    regex_token_iterator<string::iterator> noMatches ( var.begin(), var.end(), e, -1);
    while (noMatches != rend) {
        if ((*noMatches).compare("") != 0) {
            cout << "error syntax !" << endl; exit(EXIT_FAILURE);
        }
        noMatches++;
    }

    regex_token_iterator<string::iterator> matches ( var.begin(), var.end(), e, 1);
    regex rgx_1("=?([+-]?" + rgx_double + ")\\*" + "[xX]" + "(\\^" + rgx_power + ")?");
    regex rgx_2("=?[+-]?[xX]\\^" + rgx_power + "\\*(" + rgx_double + ")" );
    regex rgx_5("=?[+-]?[xX]\\*(" + rgx_double + ")" );
    regex rgx_3("=?([+-]?(" + rgx_double + ")?)[xX](\\^" + rgx_power + ")?");
    regex rgx_4("=?([+-]?" + rgx_double + ")");
    regex rgx_std_power("[xX]\\^(" + rgx_power + ")");
    double secondPart = 1.0;
    int firstPartSignCheck = 1;
    int secondPartSignCheck = -1;

    cout << (details ? "Matches : " : "");
    while (matches != rend) {
        string match( *matches );
        match = removeSpaces(match);
        if (details)
            cout << "[" << match << "] ";

        if (regex_match(match, rgx_nd_part) && secondPart == 1.0) {
            secondPartSignCheck = 1;
            secondPart = -1.0;
        }
        else if (regex_match(match, rgx_nd_part) && secondPart == -1.0) {
            cout << "error: multiple equal character (" << match << ")" << endl; exit(EXIT_FAILURE);
        }

        if (!regex_match(match, rgx_sign) && firstPartSignCheck != 1 && secondPartSignCheck != 1) {
            cout << "error: " << match << endl;//cout << "error: " << match << " with no sign" << endl;
            exit(EXIT_FAILURE);
        }

        if (regex_match(match, rgx_1)) {
            regex_token_iterator<string::iterator> match_1 ( match.begin(), match.end(), rgx_1, 1);
            string match_1_str( *match_1);
            regex_token_iterator<string::iterator> match_1_power ( match.begin(), match.end(), rgx_std_power, 1);
            int power;
            if (match_1_power == rend) // power == 1
                power = 1;
            else {
                string match_1_power_str( *match_1_power);
                power = stoi(match_1_power_str);
            }
            insertPart(secondPart * stod(match_1_str), power);
        }
        else if (regex_match(match, rgx_2)) {
            regex_token_iterator<string::iterator> match_2 ( match.begin(), match.end(), rgx_2, 1);
            string match_2_str( *match_2);
            regex_token_iterator<string::iterator> match_2_power ( match.begin(), match.end(), rgx_std_power, 1);
            int power;
            if (match_2_power == rend) // power == 1
                power = 1;
            else {
                string match_2_power_str( *match_2_power);
                power = stoi(match_2_power_str);
            }

            insertPart(secondPart * stod(match_2_str), power);
        }
        else if (regex_match(match, rgx_5)) {
            regex_token_iterator<string::iterator> match_2 ( match.begin(), match.end(), rgx_2, 1);
            string match_2_str( *match_2);
            insertPart(secondPart * stod(match_2_str), 1);
        }
        else if (regex_match(match, rgx_3)) {
            regex_token_iterator<string::iterator> match_3 ( match.begin(), match.end(), rgx_3, 1);
            string match_3_str( *match_3);
            regex_token_iterator<string::iterator> match_3_power ( match.begin(), match.end(), rgx_std_power, 1);
            int power;
            if (match_3_power == rend) // power == 1
                power = 1;
            else {
                string match_3_power_str( *match_3_power);
                power = stoi(match_3_power_str);
            }
            double coef;
            if ( match_3_str.compare("-") == 0 )
                coef = -secondPart;
            else if ( match_3_str.compare("") == 0 || match_3_str.compare("+") == 0 )
                coef = secondPart;
            else
                coef = secondPart * stod(match_3_str);
            insertPart(coef, power);
        }
        else if (regex_match(match, rgx_4)) {
            regex_token_iterator<string::iterator> match_4 ( match.begin(), match.end(), rgx_4, 1);
            string match_4_str( *match_4);
            insertPart(secondPart * stod(match_4_str), 0);
        }
        if (firstPartSignCheck == 1)
            firstPartSignCheck = -1;
        if (secondPartSignCheck == 1)
            secondPartSignCheck = -1;
        matches++;
    }
    if (details)
        cout << endl;
    if (secondPart == 1.0) {
        cout << endl << "error: second part of equation not found !" << endl;
        exit(EXIT_FAILURE);
    }
}

void    Equation::displayReducedForm() {
    Node* temp = head;

    cout << "Reduced form: ";
    if (temp == NULL)
        cout << "0";
    while (temp != NULL) {
        if (temp->coef != 0.0)
            cout << ((temp != head) ? (temp->coef < 0.0 ? " - " : " + ") : (temp->coef < 0.0 ? "- " : "") ) << (temp->coef < 0 ? -temp->coef : temp->coef) << " * X^" << temp->power; 
        temp = temp->next; 
    }
    cout << " = 0" << endl;
    if (details && degree != 3) {
        printf("Form:         c * X^0 + b * X^1 + a * X^2 = 0\n");
        printf("Coefficients: a = %.2lf   b = %.2lf   c = %.2lf\n", this->a, this->b, this->c);
    }
}

void    Equation::displayDegree() {
    cout << "Polynomial degree: " << degree << endl;
}
