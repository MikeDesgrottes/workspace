#include <stdio.h>
#include <iostream>
#include "Vector.h"
#include <string.h>
#include <math.h>
#include <list>

using namespace std;
// initialize a vector of a certain dimension.
Vector::Vector(int di){
    this->dimension = di;
    this->coordinate = new double[1024];
}
/*
Vector(std::list<double> numbers){
    int k=0;
            int z = 3;
            for(auto i = numbers.begin(); i != numbers.end();++i){
                if((*i == *numbers.begin()) & (z==3)){
                    dimension = *i;
                    int x = dimension;
                    this->coordinate = new double[x];
                }else{
                    this->coordinate[k] = *i;
                    k++;
                    z=0;
                }
            }
}*/
Vector::~Vector()
{
    if(this->coordinate != NULL){
    delete [] this->coordinate;
    }
}

// formatting for a vector
char* Vector::printV(){
    int dimension = this->dimension;
    char* s = new char[dimension*1024];
    int i;
    for(i=0;i<dimension;i++){
        if(i == 0){ // If it's the first coordinate.
            char buffer[500];
            //itoa(v->coordinate[i],buffer,sizeof(int));
            snprintf(buffer,5000,"%f",this->coordinate[i]);
            strncat(s,"<", 1+ strlen(s));
            strncat(s,buffer, strlen(s) + strlen(buffer));
            strncat(s,",",strlen(s) + 1);
        }else if(i == dimension -1){ // if it's the last coordinate.
            char buffer[500];
            snprintf(buffer,5000,"%f",this->coordinate[i]);
            strncat(s,buffer,strlen(s) + strlen(buffer));
            strncat(s,">",strlen(s)+1);
        }else{
            char buffer[500];
            snprintf(buffer,5000,"%f",this->coordinate[i]);
            strncat(s,buffer,strlen(s) + strlen(buffer));
            strncat(s,",",strlen(s) + 1);
        }
    }
    return s;
}
Vector& Vector::operator+(const Vector& v){
    Vector* tmp = new Vector(3);
    if(this->dimension == v.dimension){
        int i;
        for(i=0;i<this->dimension;i++){
            tmp->coordinate[i] = this->coordinate[i] + v.coordinate[i];
        }
    }else{
        printf("The vectors are not the same dimension!\n");
        exit(1);
    }
    
    tmp->dimension = this->dimension;
    return *tmp;
}
Vector& Vector::operator-(const Vector& v){
    Vector* tmp = new Vector(5);
    if(this->dimension == v.dimension){
        int i;
        for(i=0;i<this->dimension;i++){
            tmp->coordinate[i] = this->coordinate[i] - v.coordinate[i];
        }
    }else{
        printf("The vectors are not the same dimension!\n");
        exit(1);
    }
    
    tmp->dimension = this->dimension;
    return *tmp;
}
// dot product of vectors
double Vector::operator*(const Vector& v){
    //Vector* tmp = new Vector();
    if(this->dimension == v.dimension){
        int i;
        double j =0;
        for(i=0;i<this->dimension;i++){
             j += this->coordinate[i] * v.coordinate[i];
        }
        return j;
    }else{
        //exit(0);
        printf("The vectors are not the same dimension!\n");
        exit(1);
    }
}
// scalar multiplication, order matter
Vector& Vector::operator*(const double& v){
    Vector* tmp = new Vector(3);
        int i;
        tmp->dimension = this->dimension;
        for(i=0;i<this->dimension;i++){
             tmp->coordinate[i] = this->coordinate[i] * v;
        }
        return *tmp;
}
// length of a vector
double Vector::norm(){
    int i;
    double result;
    for(i=0;i<this->dimension;i++){
        result += pow(this->coordinate[i],2);
    }
    return sqrt(result);
}
/*
Vector* Vector::normalize(){
    double norm = this->norm();
    Vector* sum = new Vector();
    sum->dimension = this->dimension;
    printf("%f\n",sum->dimension);
    *sum = *this * norm;
    return sum;
    
}*/

// distance between 2 vectors.
Vector* Vector::displacement(Vector* v){
    Vector tmp = *v - *this;
    Vector* result = &tmp;
    result->dimension = v->dimension;
    return result;
}

// this take the cross product between 2 vectors.
Vector& Vector::operator^(const Vector& v){
    Vector* tmp = new Vector(3);
    if((this->dimension == 3) & (v.dimension == 3)){
        tmp->coordinate[0] = this->coordinate[1]*v.coordinate[2] - this->coordinate[2]*v.coordinate[1];
        tmp->coordinate[1] = this->coordinate[2]*v.coordinate[0] - this->coordinate[0]*v.coordinate[2];
        tmp->coordinate[2] = this->coordinate[0]*v.coordinate[1] - this->coordinate[1]*v.coordinate[0];
    }else{
        printf("Cross Product is defined only for 3d vectors!\n");
        exit(1);
    }
    
    tmp->dimension = this->dimension;
    return *tmp;
}

// projection of one vector onto another.
Vector* Vector::proj(Vector* v){
    double w = *this * *v;
    double z = pow(v->norm(),2);
    Vector* f = new Vector(5);
    f->dimension = v ->dimension;
    int i;
    for(i=0;i<f->dimension;i++){
        f->coordinate[i] = (w*v->coordinate[i])/z;
    }
    return f;
}