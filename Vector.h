#ifndef VECTOR_H
#define VECTOR_H
#include <cstdarg>
#include <iostream>
#include <stdio.h>
#include <initializer_list>
#include <vector>
#include <list>

class Vector{
    public:
        // This is an array of the coordinates.
        double* coordinate;
        double dimension;
        std::vector<double> list;
        // a version of the constructor that create a vector from a list of numbers.
        Vector(std::list<double> numbers){
            int k=0;
            double z = 3E78;
            for(auto i = numbers.begin(); i != numbers.end();++i){
                if((*i == *numbers.begin()) & (z==3E78)){
                    dimension = *i;
                    int x = dimension;
                    this->coordinate = new double[x];
                    z=0;
                }else{
                    this->coordinate[k] = *i;
                    k++;
                    z=0;
                }
            }
        }
        Vector(std::initializer_list<double> numbers){
            int k=0;
            int z = 3;// this is used to seperate the dimension from the coordinates
            for(auto i = numbers.begin(); i != numbers.end();++i){
                if((*i == *numbers.begin()) & (z==3)){ // this check is for in case *i == 3.
                    dimension = *i;
                    int x = dimension;
                    this->coordinate = new double[x];
                    z=0;
                }else{
                    this->coordinate[k] = *i;
                    k++;
                    z=0;
                }
            }
        }
        // variadic constructor.
        template< typename... Args>
        Vector(int dimension,Args... args){
            std::vector<double> tmp = {args...};
            this->dimension = dimension;
            this->coordinate = new double[dimension];
            for(auto i = 0; i<tmp.size();++i){
                this->coordinate[i] = tmp[i];
            }
        }
        // function prototype
        Vector(int di);
        char* printV();
        Vector& operator+(const Vector& v);
        Vector& operator-(const Vector& v);
        double operator*(const Vector& v);
        Vector& operator*(const double& v);
        Vector& operator^(const Vector& v);
        double norm();
        // This function gives you the unit vector of a vector.
        Vector* normalize(){
            double norm = 1/(this->norm());
            Vector* sum = new Vector(5);
            sum->dimension = this->dimension;
            printf("%f\n",sum->dimension);
            *sum = *this * norm;
            return sum;
        }
        
        
        bool is_orthorgonal(Vector* v){
            return (*this * *v)==0;
        }
        
        Vector* proj(Vector* v);
        Vector* displacement(Vector* v);
        ~Vector();
    protected:
    private:
};
#endif 
