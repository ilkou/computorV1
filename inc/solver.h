#ifndef SOLVER_H
# define SOLVER_H

class Solver
{
	private:
    Equation *e;
		void solveEq2d();
		void solveEq3d();
	public:
		Solver(Equation *a) : e(a) {}
		~Solver(void);
    void start();
};

#endif