#ifndef EQUATION_H
# define EQUATION_H

class Node
{ 
	public:
		double coef;
    int power;
    Node* next; 
}; 

class Equation
{
	private:
		Node *head;
		int degree;
		double a;
		double b;
		double c;
		double d;
	public:
		Equation(void);
		~Equation(void);
/*		double getA(void) { return this->a; }
		double getB(void) { return this->b; }
		double getC(void) { return this->c; }
		void setA(double a) { this->a = a; }
		void setB(double b) { this->b = b; }
		void setC(double c) { this->c = c; }
*/
		void setCoefs(void);
		void solve(void) {}
		void parseEquation(const char *eq);
		void insertPart(double coef, int power);
		void displayReducedForm();
		void displayDegree();
		friend class Solver;
};

#endif