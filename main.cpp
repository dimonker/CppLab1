#include <iostream>
#include <fstream>

using namespace std;

class Matrix{
private:
    int rows, cols;
    double** data;
public:
    Matrix(){};

    Matrix(int rows, int cols){
        this->rows = rows;
        this->cols = cols;
        createMatrix();
    }

    void createMatrix(){
        data = new double*[rows];
        for(int i = 0; i < rows; i++)
            data[i] = new double[cols];
    }

    void setRows(int rows){
        this->rows = rows;
    }

    int getRows(){
        return rows;
    }

    void setCols(int cols){
        this->cols = cols;
    }

    int getCols(){
        return cols;
    }

    double& operator ()(int i, int j){
        return data[i][j];
    }

    Matrix& operator = (const Matrix& m){
        rows = m.rows;
        cols = m.cols;

        createMatrix();

        for (int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                data[i][j] = m.data[i][j];

        return *this;
    }

    Matrix operator +(const Matrix& other){
        if (this->rows != other.rows || this->cols != other.cols){
            cout << "Матрицы разных размеров" << endl;
            return *this;
        }

        int rows = this->rows;
        int cols = this->cols;
        Matrix m(rows, cols);

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                m.data[i][j] = this->data[i][j] + other.data[i][j];
        return m;
    }

    Matrix& operator += (const Matrix& other){
        return *this = *this + other;
    }

    Matrix operator -(const Matrix& other){
        if (this->rows != other.rows || this->cols != other.cols){
            cout << "Матрицы разных размеров" << endl;
            return  *this;
        }
        int rows = this->rows;
        int cols = this->cols;
        Matrix m(rows, cols);

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                m.data[i][j] = this->data[i][j] - other.data[i][j];
        return m;
    }

    Matrix& operator -= (const Matrix& other){
        return *this = *this + other;
    }

    Matrix operator + (double n){
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                data[i][j] += n;
        return *this;
    }

    Matrix& operator +=(double n){
        return *this = *this + n;
    }

    Matrix operator - (double n){
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                data[i][j] -= n;
        return *this;
    }

    Matrix& operator -=(double n){
        return *this = *this - n;
    }

    Matrix operator * (double n){
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                data[i][j] *= n;
        return *this;
    }

    Matrix& operator *=(double n){
        return *this = *this * n;
    }

    void T(){
        double temp;
        Matrix m(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                m.data[i][j] = this->data[i][j];

        temp = this->rows;
        this->rows = this->cols;
        this->cols = temp;

        createMatrix();

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                this->data[i][j] = m.data[j][i];
            }
        }
    }

    Matrix Dot(const Matrix& other){
        if (cols != other.rows){
            cout << "Количество столбцов первой матрицы не равно количеству строк второй матрицы" << endl;
            return *this;
        }

        Matrix m(rows, other.cols);
        double sum = 0;

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < other.cols; j++){
                for (int n = 0; n < cols; n++)
                    sum+= data[i][n] * other.data[n][j];
                m.data[i][j] = sum;
                sum = 0;
            }
        return m;
    }

    friend istream& operator >> (istream& in, Matrix& m){
        int rows, cols;
        in >> rows;
        m.rows = rows;
        in >> cols;
        m.cols = cols;

        m.createMatrix();

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                in >> m.data[i][j];
        return in;
    }

    friend ostream& operator << (ostream& out, Matrix& m){
        out << "-------" << endl;
        for (int i = 0; i < m.getRows(); i++){
            for (int j = 0; j < m.getCols(); j++){
                out << m.data[i][j] << " ";
            }
            out << endl;
        }
        out << "-------" << endl;
        return out;
    }

    Matrix (const Matrix& m){
        this->rows = m.rows;
        this->cols = m.cols;
        createMatrix();

        for (int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                data[i][j] = m.data[i][j];
    }

    ~Matrix(){
        for (int i = 0; i < rows; i++){
            delete [] data[i];
        }
        delete [] data;
    }
};

int main() {
    ifstream fin;
    fin.open("1.txt");
    Matrix m1;
    fin >> m1;
    fin.close();
    cout << m1;

    fin.open("2.txt");
    Matrix m2;
    fin >> m2;
    fin.close();
    cout << m2;

    Matrix m3;
    cout << "m1 + m2" << endl;
    m3 = m1 + m2;
    cout << m3 << endl;

    cout << "m3 * 3" << endl;
    m3 = m3 * 3;
    cout << m3 <<endl;

    cout << "m1 * m2" << endl;
    m3 = m1.Dot(m2);
    cout << m3 << endl;

    cout << "m3.T()" << endl;
    m3.T();
    cout << m3 << endl;
    return 0;
}