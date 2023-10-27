//apply gaussian elimination to solve equiv
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
const int N = 20;
double matrix[N][N] = {0};
int size;
int pivot[N] = {0};
double epslion = 0.001;

void write_matrix();
void print_matrix();
bool isignore(double num);
int row_swap(int row1,int row2);//swap row1 and row2
int row_multi(int row,double k);//let row times k
int row_add(int row,double k,int add);//let k times of row_add added to row
int find_nonzero_element(const int step[]);//find the row of the first non-zero element on the col
int col_elimi(const int step[]);//let the other elelments of the col into zero
int get_rank();
int simplify_step(int rank);
int back_step(int rank);

int main()
{
    // read and initialize the matrix
    write_matrix();
    // Gaussian Elimination
    int step[2] = {0,0};//the location of pivot element
    int point[2] = {0,0};//actually a little of no use 
    for(int j=0;j<size;++j){
        //find non-zero element
        point[0] = find_nonzero_element(step);
        point[1] = j;
        if(point[0] == -1){
            ++step[1];
            continue;
        }
        //swap row
        if(point[0] != step[0]) pivot[row_swap(step[0], point[0])] = point[1];
        else pivot[step[0]] = point[1];
        //eliminate the col
        col_elimi(step);
        //to next col
        ++step[1],++step[0];
    }
    //identify the rank
    int rank = get_rank();
    //show the result
    if(rank == -1){
        cout << "No solution!" << endl;
    }
    else if(rank < size){
        cout << "No unique solution!" << endl;
    }
    else{
        back_step(rank);
    }
    //print_matrix();
    return 0;
}

void write_matrix(){
    char ch;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            //write elements
            cin >> matrix[i][j];
            //judge size of matrix
            if((ch=cin.get()) != ' '){
                size = j;
                break;
            }
        }
        if(i == size-1) break;
    }
}

void print_matrix(){
    
    for(int i=0;i<size;++i){
        for(int j=0;j<=size;++j){
            cout << setiosflags(ios::fixed) << setprecision(4) << setiosflags(ios::showpoint);
            cout << matrix[i][j] << '\t';
        }
        cout << '\n';
    }
}

bool isignore(double num){
    //ignore the number too small 
    if(abs(num) < epslion){
        return true;
    }
    else{
        return false;
    }
}

int row_swap(int row1,int row2){
    int temp[N];
    for(int i=0;i<=size;++i){
        temp[i] = matrix[row1][i];
    }
    for(int i=0;i<=size;++i){
        matrix[row1][i] = matrix[row2][i];
    }
    for(int i=0;i<=size;++i){
        matrix[row2][i] = temp[i];
    }
    return row1;
}

int row_multi(int row,double k){
    for(int i=0;i<=size;++i){
        matrix[row][i] *= k;
    }
    return 0;
}

int row_add(int row,double k,int add){
    double temp[N] = {0};
    for(int i=0;i<=size;++i){
        temp[i] = matrix[add][i] * k;
    }
    for(int i=0;i<=size;++i){
        matrix[row][i] += temp[i];
    }
    return 0;
}

int find_nonzero_element(const int step[]){
    int row=step[0],col=step[1];
    for(int i=row;i<size;++i){
        if(!isignore(matrix[i][col])) return i;
    }
    return -1;
}

int col_elimi(const int step[]){
    int row_base=step[0],col=step[1];
    for(int i=row_base+1;i<size;++i){
        if(!matrix[i][col]) continue;
        row_add(i,-matrix[i][col]/matrix[row_base][col],row_base);
    }
    return 0;
}

int get_rank(){
    int col1=size-1,col2=size;
    for(int i=0;i<size;++i){
        if(i==size-1&&isignore(matrix[i][col1])&&!isignore(matrix[i][col2])){
            return -1;
        }
        if(isignore(matrix[i][col1])&&isignore(matrix[i][col2])){
            if(isignore(matrix[i-1][col1])&&!isignore(matrix[i-1][col2])) return -1;
            else return i;
        }
    }
    return size;
}

int simplify_step(int rank){
    for(int i=rank-1;i>=0;--i){
        row_multi(i,1/matrix[i][pivot[i]]);
        for(int j=i-1;j>=0;--j){
            row_add(j,-matrix[j][pivot[i]],i);
        }
    }
    return 0;
}

int back_step(int rank){
    simplify_step(rank);
    for(int i=0;i<rank;++i){
        cout << setiosflags(ios::fixed) << setprecision(4) << setiosflags(ios::showpoint);
        cout << matrix[i][size] << " ";
    }
    return 0;
}
