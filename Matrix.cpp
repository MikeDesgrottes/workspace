#include <stdio.h>
#include <iostream>
#include "Vector.h"
#include <string.h>
#include <math.h>
#include "Matrix.h"
#include <list>

using namespace std;
/*
 * TODO(mike): overload the operator() 
 *             implement the function to solve the system of equation.
 *
 *
 *
 *             
*/


#define AT(i) this->columns[i]->coordinate[i];
#define rowCount this->dimension.rows;
#define colcount this->dimension.columns;

// format for a Matrix
char* Matrix::printM(){
    char* s = new char[5000*1024];
    int i;
    for(i=0;i < this->dimension.rows;i++){ // for each row in the matrix
        int j;
        for(j=0;j< this->dimension.columns;j++){ //for each columns in the matrix
            Vector* tmp = this->columns[j]; // take the jth columns
            int x = this->dimension.columns - 1; // safe guard against segfault.
            if(j == 0){ // if it's the first columns
                char buffer[500];
                //it0oa(v->coordinate[i],buffer,sizeof(int));
                snprintf(buffer,5000,"%f",tmp->coordinate[i]);
                strncat(s,"|", 1+ strlen(s));
                strncat(s,buffer, strlen(s) + strlen(buffer));
                strncat(s,",",strlen(s) + 1);
            }else if(j == x){ // if it's the last column
                char buffer[500];
                snprintf(buffer,5000,"%f",tmp->coordinate[i]);
                strncat(s,buffer,strlen(s) + strlen(buffer));
                strncat(s,"|\n",strlen(s)+2);
            }else{
                char buffer[500];
                snprintf(buffer,5000,"%f",tmp->coordinate[i]);
                strncat(s,buffer,strlen(s) + strlen(buffer));
                strncat(s,",",strlen(s) + 1);
            }
        }
    }
    return s;
}
// initialize a zero vector with the specified dimension.
Matrix::Matrix(int di,int de){
    this->dimension.rows =de;
    this->dimension.columns =di;
    this->columns.assign(di,new Vector(de));
}
// initialize a matrix from a vector of Vector
Matrix::Matrix(std::vector<Vector*> v, int di){
    this->dimension.columns = v.size();
    this->columns = v;
    this->dimension.rows = v[0]->dimension;
}

// Matrix addition
Matrix& Matrix::operator+(const Matrix& v){
    if((this->dimension.rows == v.dimension.rows) & (this->dimension.columns == v.dimension.columns)){ // check that the 2 matrices have the same dimension.
        Matrix* mt = new Matrix(this->dimension.columns,6);// initialize a matrix with the same number of columns as the first matrix, the number 6 is a placeholder.
        mt->dimension = this->dimension;
        int i;
        for(i=0;i< mt->dimension.columns;i++){ // for each columns
            mt->columns[i] = &(*this->columns[i] + *v.columns[i]); // add the columns together, since they are vector.
            printf("%s\n",mt->columns[0]->printV());
        }
        return *mt;
        
    }else{
        printf("The matrices don't have the same dimension.\n");
        printf("The first matrix dimension : %d x %d\n",this->dimension.rows,this->dimension.columns);
        printf("The second matrix dimension : %d x %d\n",v.dimension.rows,v.dimension.columns);
        exit(0);
    }
    
    
}
Matrix& Matrix::operator-(const Matrix& v){
    if((this->dimension.rows == v.dimension.rows) & (this->dimension.columns == v.dimension.columns)){
        Matrix* mt = new Matrix(this->dimension.columns,7);
        mt->dimension = this->dimension;
        int i;
        for(i=0;i< mt->dimension.columns;i++){
            mt->columns[i] = &(*this->columns[i] - *v.columns[i]);
            printf("%s\n",mt->columns[0]->printV());
        }
        return *mt;
    }else{
        printf("The matrices don't have the same dimension.\n");
        printf("The first matrix dimension : %d x %d\n",this->dimension.rows,this->dimension.columns);
        printf("The second matrix dimension : %d x %d\n",v.dimension.rows,v.dimension.columns);
        exit(0);
    }
}
Matrix& Matrix::operator*(const double& v){
    Matrix* mt = new Matrix(this->dimension.columns,3);
    mt->dimension = this->dimension;
    int i;
    for(i=0;i< mt->dimension.columns;i++){
        mt->columns[i] = &(*this->columns[i] * v);
    }
    return *mt;
}
std::vector<Vector*> Matrix::row_equiv(Matrix* m){
    std::list<Vector*> result;
    int i;
    for(i=0;i< m->dimension.rows;i++){
        std::list<double> lists;
        lists.push_back(m->dimension.columns);
        int j;
        for(j=0;j< m->dimension.columns;j++){
            Vector* tmp = m->columns[j];
            lists.push_back(tmp->coordinate[i]);
            //delete tmp;
        }
        j=0;
        //std::initializer_list<double> list_h = lists;
        Vector* tmp = new Vector(lists);
        result.push_back(tmp);
        
    }
    std::vector<Vector*> x{std::begin(result),std::end(result)};
    return x;
}
Matrix* Matrix::transpose(){
    std::vector<Vector*> b = row_equiv(this);
    Matrix* mt = new Matrix(b,this->dimension.rows);
    delete this;
    return mt;
}
Matrix* Matrix::upperTriangular(){
    std::vector<Vector*> tmp = row_equiv(this);
    if(this->is_square()){
        int j;
        for(j=0;j<this->dimension.columns;j++){
            double pivot = tmp[j]->coordinate[j];
            int i;
            for(i=j+1;i<this->dimension.rows;i++){
                tmp[i] = &((*tmp[i]) - (*tmp[j] * (tmp[i]->coordinate[j]/pivot)));
            }
        
        }
    }else if(this->dimension.rows > this->dimension.columns){
        //printf("Hello world,\n");
        int j;
        for(j=0;j<this->dimension.columns;j++){
            double pivot = tmp[j]->coordinate[j];
            printf("%f\n",pivot);
            int i;
            for(i=j+1;i< this->dimension.rows;i++){
                    tmp[i] = &((*tmp[i]) + (*tmp[j] * (tmp[i]->coordinate[j]/-1*pivot)));
            }
        
        }
    }else if(this->dimension.rows < this->dimension.columns){
        printf("Not Hello World!");
    }
    
    Matrix* result = new Matrix(tmp,this->dimension.rows);
    return result->transpose();
}
std::vector<Vector*> Matrix::initialize_vector(int num, int dimension){
    std::vector<Vector*> v(num);
    for(auto i = 0; i< num; i++){
        v[i] = new Vector(dimension);
    }
    return v;
}
// This is supposed to give me the multiplication of matrices.
Matrix& Matrix::operator*(const Matrix& v){
    
    if(this->dimension.columns == v.dimension.rows){
        Matrix* mt  = new Matrix(v.dimension.columns,this->dimension.rows);
        mt->dimension.rows = this->dimension.rows;
        //std::vector<Vector*> tmp = row_equiv(this);
        std::vector<Vector* > result = initialize_vector(v.dimension.columns, this->dimension.rows);
        for(auto i=0; i < this->dimension.rows;i++){
            for(auto j=0; j<v.dimension.columns;j++){
                for(auto k=0; k< this->dimension.columns;k++){
                    result[j]->coordinate[i] += this->columns[k]->coordinate[i] * v.columns[j]->coordinate[k];
                    //printf("j = %d and k = %d and i = %d, %s and %s\n",j,k,i,result[j]->printV(), result[0]->printV());
                }
            }
        }  
        mt = new Matrix(result,3);
        return *mt;
    }else{
       printf("Cannot multiply the 2 matrices together. Check the dimensions of your matrices!\n");
       exit(1);
    }
}

Vector Matrix::operator *(const Vector& m){
    std::vector<Vector*>  mt = row_equiv(this);
    if(this->dimension.columns == m.dimension){
        Vector* v = new Vector(m.dimension);
        for(auto i =0; i < v->dimension; i++){
            v->coordinate[i] = *mt[i] * m;
        }
        for(auto j = 0; j < mt.size();j++){
        delete mt[j];
    }
        return *v;
    }else{
        for(auto i = 0; i < mt.size();i++){
            delete mt[i];
        }
        printf("Cannot multiply this vector by the matrix.\n");
        exit(1);
    }
    for(auto i = 0; i < mt.size();i++){
        delete mt[i];
    }
    
}
/*
Vector Matrix::solution(Vector& v){
    std::vector<Vector*> tmp = row_equiv(this);
    Vector* tmp1 = new Vector(v.dimension);
    for(auto k =0 ; k<v.dimension;k++){
        tmp1->coordinate[k] = v.coordinate[k];
    }
    if(this->dimension.columns == v.dimension){
        int j;
        for(j=0;j<this->dimension.columns;j++){
            double pivot = tmp[j]->coordinate[j];
            //printf("%f\n",pivot);
            int i;
            for(i=j+1;i< this->dimension.rows;i++){
                    tmp1->coordinate[i] = tmp1->coordinate[i] + (tmp1->coordinate[j] * (tmp[i]->coordinate[j]/(-1*pivot)));
                    tmp[i] = &((*tmp[i]) + (*tmp[j] * (tmp[i]->coordinate[j]/(-1*pivot))));
                    printf("%f\n",tmp1->coordinate[i]);
            }
        
        }
        for(j=this->dimension.columns -1 ;0<=j;j--){
            double pivot = tmp[j]->coordinate[j];
            for(auto i = j -1; 0<=i;  i--){
                tmp1->coordinate[i] = tmp1->coordinate[i] + (tmp1->coordinate[j] * (tmp[i]->coordinate[j]/(-1*pivot)));
                tmp[i] = &((*tmp[i]) + (*tmp[j] * (tmp[i]->coordinate[j]/(-1*pivot))));
                printf("%s\n",tmp[i]->printV());
            }
        }
        for(auto k = 0; k < this->dimension.columns;k++){
            double pivot = this->columns[k]->coordinate[k];
            tmp1->coordinate[k] = tmp1->coordinate[k]/(pivot);
        }
        return *tmp1;
    }
    for(auto i = 0; i < tmp.size();i++){
        if(tmp[i] != NULL){
        delete tmp[i];
        }
    }
}
*/

Vector Matrix::solution(Vector& v) {
    Vector *res = new Vector(v->dimension);
    int lead =0;
    for(auto r =0; r < rowCount; ++r) {
        if(colcount <= lead) {
            return *res;
        }

        double i = r;
        while(AT(i,r) == 0) {
            i++;
            if(rowCount == i) {
                i = r;
                lead++;
                if(colcount == lead) return *res;
            }
        }


    }
}
Matrix::~Matrix(){
    for(auto i = 0; i < this->columns.size();i++){
        if(this->columns[i] != NULL){
        delete this->columns[i];
        }
    }
}
