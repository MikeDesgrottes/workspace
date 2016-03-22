#ifndef MATRIX_H
#define MATRIX_H
#include <cstdarg>
#include <iostream>
#include <stdio.h>
#include <initializer_list>
#include <vector>
#include <list>
/*
The way my matrices are structure is that they have a dimension and a vector of Vector* columns

M = {a_0,a_1,a_2}
M = |1,0,0|
    |0,1,0|
    |0,0,1|
    
M = {<1,0,0>,<0,1,0>,<0,0,1>} // each vector correspond to a columns.
*/
typedef struct Md Matrix_dimension;

struct Md{
    int rows;
    int columns;
};

class Matrix{
    public:
        Matrix_dimension dimension;
        // This is the vectors of the matrix. M = {a_1,a_2,...,a_n}
        std::vector<Vector*> columns;
        // variadic constructor. it takes a variable number of Vector*.
        template< typename... Args>
        Matrix(Args... args){
            this->columns = {args...};// i don't know why this works lol
            
            int i;
            double di = this->columns[0]->dimension; // number of rows
            for(i=0;i<this->columns.size();i++){ // loop through the columns
                if(i != this->columns.size() -1){
                    if(this->columns[i+1]->dimension != di){ // Checks to see that all vectors have the dimension.
                        printf("The vectors do not have the same dimension\n");
                        printf("%s and %s do not have the same dimension\n",this->columns[i]->printV(),this->columns[i+1]->printV());
                        exit(0);
                    }else{
                        di = this->columns[i+1]->dimension; // this is to make sure that all columns vector are of the same dimension.
                    }
                }
                
            }
            
            this->dimension.columns = columns.size(); // set the amount of columns in the matrix
            this->dimension.rows = di;
        }
        
        // Formatting for a matrix.
        char* printM();
        
        bool is_square(){
            return (this->dimension.rows == this->dimension.columns);
        }
        
        // Overloaded operators
        Matrix& operator +(const Matrix& v);
        Matrix& operator -(const Matrix& v);
        Matrix& operator *(const double& v);
        Vector operator *(const Vector& m);
        
        // initialize an zero matrix with the specified dimension.
        Matrix(int di,int de);
        
        // This function returns a vector(standard) of the rows.
        std::vector<Vector*> row_equiv(Matrix* m);
        
        // make a vector out of a vector.
        Matrix(std::vector<Vector*> v, int di);
        
        Matrix* transpose();
        Matrix* upperTriangular();
        double determinant(){
            double result = 1;
            if(this->is_square()){// Check to see if it's a square matrix
                Matrix* tmp = this->upperTriangular(); // put the matrix in upper triangular form
                for(auto i =0; i< tmp->dimension.columns;i++){
                    result = result * tmp->columns[i]->coordinate[i]; // take the product of the diagonal.
                    
                }
            }
            
            return result;
        }
        bool is_singular(){
            if(this->determinant() == 0){
                return true;
            }
            return false;
        }
        
        // matrix multiplication
        Matrix& operator*(const Matrix& v);
        
        //TODO: make this function work
        double& operator ()(const int i, const int j) const
        {
            return this->columns[i]->coordinate[j];
        }
        //TODO: Make this function work
        double &operator()(int i, int j)
        {
            return this->columns[i]->coordinate[j];
        }
        // This function is neccessary because the way the standard vector initialize pointers is bad. 
        std::vector<Vector*> initialize_vector( int num, int dimension);
        
        Vector solution(Vector& v);
        ~Matrix();
    private:
        // swap row i with row j
        void swap(int i,int j);
    protected:
};
#endif
