#ifndef MATRIXFRACTIONS_H
#define MATRIXFRACTIONS_H

#include <string>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

template <class U>
class Fraction 
{
    private:

        U n;
        U d;

    public:
        Fraction() {
            U default_n(0);
            U default_d(1);

            this->n = default_n;
            this->d = default_d;
        }

        Fraction(U n) {
            U default_d(1);
            this->n = n;
            this->d = default_d;
        }

        Fraction(U n, U d) {
            U zero(0);
            U negOne(-1);
            bool isNNeg = n < zero;
            bool isDNeg = d < zero;
            if ((isNNeg && isDNeg) || (!isNNeg && isDNeg)) {
                n *= negOne;
                d *= negOne;
            } 

            this->n = n;
            this->d = d;
        }

        Fraction(Fraction const & o) {
            this->n = o.n;
            this->d = o.d;
        }

        Fraction& operator=(Fraction const & b) {
            if (this == &b) {
		        return *this;
            }
            this->n=b.n;
            this->d=b.d;
            return *this;
        }

        Fraction& operator+=(Fraction& b) {
            U n = this->n * b.d + b.n * this->d;
            U d = this->d * b.d;
            
            U zero(0);
            U negOne(-1);
            bool isNNeg = n < zero;
            bool isDNeg = d < zero;
            if ((isNNeg && isDNeg) || (!isNNeg && isDNeg)) {
                n *= negOne;
                d *=  negOne;
            } 

            this->n = n/Gcd(Absolute(n),Absolute(d));
            this->d = d/Gcd(Absolute(n),Absolute(d));
            return *this;
        }
        
        Fraction& operator-=(Fraction& b) {
            U n = this->n * b.d - b.n * this->d;
            U d = this->d * b.d;
            U zero(0);
            U negOne(-1);
            bool isNNeg = n < zero;
            bool isDNeg = d < zero;
            if ((isNNeg && isDNeg) || (!isNNeg && isDNeg)) {
                n *= negOne;
                d *=  negOne;
            } 

            this->n = n/Gcd(Absolute(n),Absolute(d));
            this->d = d/Gcd(Absolute(n),Absolute(d));
            return *this;
        }

        Fraction& operator*=(Fraction& b) {
            this->n=this->n*b.n;
            this->d=this->d*b.d;

            U zero(0);
            U negOne(-1);
            bool isNNeg = n < zero;
            bool isDNeg = d < zero;
            if ((isNNeg && isDNeg) || (!isNNeg && isDNeg)) {
                n *= negOne;
                d *=  negOne;
            } 

            this->n = n/Gcd(Absolute(n),Absolute(d));
            this->d = d/Gcd(Absolute(n),Absolute(d));
            return *this;
        }
        
        Fraction& operator/=(Fraction& b) {
            this->n=this->n*b.d;
            this->d=this->d*b.n;

            U zero(0);
            U negOne(-1);
            bool isNNeg = n < zero;
            bool isDNeg = d < zero;
            if ((isNNeg && isDNeg) || (!isNNeg && isDNeg)) {
                n *= negOne;
                d *=  negOne;
            } 

            this->n = n/Gcd(Absolute(n),Absolute(d));
            this->d = d/Gcd(Absolute(n),Absolute(d));
            return *this;
        }

        template<class V> friend Fraction<V> operator+(Fraction<V> const & a, Fraction<V> const & b);

        template<class V> friend Fraction<V> operator-(Fraction<V> const & a, Fraction<V> const & b);

        template<class V> friend Fraction<V> operator*(Fraction<V> const & a, Fraction<V> const & b);

        template<class V> friend Fraction<V> operator/(Fraction<V> const & a, Fraction<V> const & b);

        template<class V> friend Fraction<V> operator%(Fraction<V> const & a, Fraction<V> const & b);

        template<class V> friend bool operator==(Fraction<V> const &  a, Fraction<V> const & b);

        template<class V> friend bool operator>=(Fraction<V> const & a, Fraction<V> const & b);

        template<class V> friend bool operator<=(Fraction<V> const & a, Fraction<V> const & b);

        template<class V> friend bool operator>(Fraction<V> const & a, Fraction<V>const & b);

        template<class V> friend bool operator<(Fraction<V> const & a, Fraction<V> const & b);

        template<class V> friend bool operator!=(Fraction<V> const & a, Fraction<V> const & b);
        
        template<class V> friend ostream& operator<<(ostream& os, Fraction<V> const & f);

        static U Gcd(U a, U b) {
            U zero(0);
            for (;a > zero && b > zero;) {
                  if (a > b) {
                      a = fmod(a,b);
                  }
                  else {
                      b = fmod(b,a);
                  }
              }
              if (a == zero) {
                  return b;
              }
              return a;
        }
        static U Absolute(U n) {
                U zero(0);
                U negOne(-1);
                if (n < zero)
                {
                    n *= negOne;
                }
                return n;
            }
};  

template <class U>
Fraction<U> operator+(Fraction<U> const & a, Fraction<U> const & b) {
    U n = a.n * b.d + b.n * a.d;
    U d = a.d * b.d;

    U zero(0);
    U negOne(-1);
    bool isNNeg = n < zero;
    bool isDNeg = d < zero;
    if ((isNNeg && isDNeg) || (!isNNeg && isDNeg)) {
        n *= negOne;
        d *=  negOne;
    }
    Fraction result(n/Fraction<U>::Gcd(Fraction<U>::Absolute(n),Fraction<U>::Absolute(d)),d/Fraction<U>::Gcd(Fraction<U>::Absolute(n),Fraction<U>::Absolute(d)));
    return result;
}

template <class U>
Fraction<U>  operator-(Fraction<U> const & a, Fraction<U> const & b) {
    U n = a.n * b.d - b.n * a.d;
    U d = a.d * b.d;
    
    U zero(0);
    U negOne(-1);
    bool isNNeg = n < zero;
    bool isDNeg = d < zero;
    if ((isNNeg && isDNeg) || (!isNNeg && isDNeg)) {
        n *= negOne;
        d *=  negOne;
    }
    Fraction result(n/Fraction<U>::Gcd(Fraction<U>::Absolute(n),Fraction<U>::Absolute(d)),d/Fraction<U>::Gcd(Fraction<U>::Absolute(n),Fraction<U>::Absolute(d)));
    return result;
}

template <class U>
Fraction<U>  operator*(Fraction<U> const & a, Fraction<U> const & b) {
    U n = a.n * b.n;
    U d = a.d * b.d;
    
    U zero(0);
    U negOne(-1);
    bool isNNeg = n < zero;
    bool isDNeg = d < zero;
    if ((isNNeg && isDNeg) || (!isNNeg && isDNeg)) {
        n *= negOne;
        d *=  negOne;
    }
    Fraction result(n/Fraction<U>::Gcd(Fraction<U>::Absolute(n),Fraction<U>::Absolute(d)),d/Fraction<U>::Gcd(Fraction<U>::Absolute(n),Fraction<U>::Absolute(d)));
    return result;
}

template <class U>
Fraction<U>  operator/(Fraction<U> const & a, Fraction<U> const & b) {
    U n = a.n * b.d;
    U d = a.d * b.n;
    
    U zero(0);
    U negOne(-1);
    bool isNNeg = n < zero;
    bool isDNeg = d < zero;
    if ((isNNeg && isDNeg) || (!isNNeg && isDNeg)) {
        n *= negOne;
        d *=  negOne;
    }
    Fraction result(n/Fraction<U>::Gcd(Fraction<U>::Absolute(n),Fraction<U>::Absolute(d)),d/Fraction<U>::Gcd(Fraction<U>::Absolute(n),Fraction<U>::Absolute(d)));
    return result;
}

template <class U>
Fraction<U>  operator%(Fraction<U> const & a, Fraction<U> const & b) {
    //mod(a, n) = a - n * floor(a / n)
    U s1 = a.n * b.d;
    U s2 = a.d * b.n;
    U s3 = s1 / s2;
    U s4 = floor(s3);
    U s5 = b.n * s4;
    U s6 = a.n * b.d;
    U s7 = s5 * a.d;
    U n = s6 - s7;
    U d = a.d * b.d;
    
    U zero(0);
    U negOne(-1);
    bool isNNeg = n < zero;
    bool isDNeg = d < zero;
    if ((isNNeg && isDNeg) || (!isNNeg && isDNeg)) {
        n *= negOne;
        d *=  negOne;
    }
    //if want modulo to be more like rem (remainder) than uncomment below
    /*
    if (n < zero) {
        //if negative then perform
        //n/d + b 
        U z1 = n * b.d;
        U z2 = Fraction<U>::Absolute(b.n) * d;
        U z3 = b.d * d;

        n = z1 + z2;
        d = z3;

        isNNeg = n < zero;
        isDNeg = d < zero;
        if ((isNNeg && isDNeg) || (!isNNeg && isDNeg)) {
            n *= negOne;
            d *=  negOne;
        }
    } 
    */
    
    Fraction result(n/Fraction<U>::Gcd(Fraction<U>::Absolute(n),Fraction<U>::Absolute(d)),d/Fraction<U>::Gcd(Fraction<U>::Absolute(n),Fraction<U>::Absolute(d)));
    return result;
}

template <class U>
bool operator==(Fraction<U> const & a, Fraction<U> const & b) {
    return (a.n/a.d == b.n/b.d) || (a.n == b.n && a.d == b.d);
}

template <class U>
bool operator>=(Fraction<U> const & a, Fraction<U> const & b) {
    return (a.n/a.d >= b.n/b.d) || (a.n >= b.n && a.d >= b.d);
}

template <class U>
bool operator<=(Fraction<U> const & a, Fraction<U> const & b) {
    return (a.n/a.d <= b.n/b.d) || (a.n <= b.n && a.d <= b.d);
}

template <class U>
bool operator>(Fraction<U> const & a, Fraction<U> const & b) {
    return (a.n/a.d > b.n/b.d) || (a.n > b.n && a.d > b.d);
}

template <class U>
bool operator<(Fraction<U> const & a, Fraction<U> const & b) {
    return (a.n/a.d < b.n/b.d) || (a.n < b.n && a.d < b.d);
}

template <class U>
bool operator!=(Fraction<U> const & a, Fraction<U> const & b) {
    return (a.n/a.d != b.n/b.d) || (a.n != b.n && a.d != b.d);
}        
        
template <class U>
ostream& operator<<(ostream& os, Fraction<U> const & f) {
            os << f.n << "/" << f.d;
            return os;
}

template <class T>
class Row
{
    private:

        vector<T> arr;
        int n;

    public:

        Row(int n);

        Row(vector<T>& arr);

        Row(int n, vector<T>& arr);

        T GetCell(int i) const;

        void SetCell(int i, T val);

        int GetRowSize() const;

        void Print() const;

        T DotProduct(Row& b) const;
};

template <class W>
class Matrix
{
    private:

        vector<W> arr;
        int n;

    public:

        Matrix(int n);
        
        Matrix(int n, vector<W>& arr);
    
        W GetCell(int i, int j) const;
    
        void SetCell(int i, int j, W val);
    
        Row<W>* GetRow(int i) const;
    
        Row<W>* GetCol(int j) const;
    
        int GetRowSize() const;
    
        void Print() const;
    
        vector<W> GetArr() const;
    
        vector<vector<W>> ConvertTo2DArray() const;
    
        Matrix* Multiply(Matrix& B);
    
        vector<Matrix*> LUDecomposition();
    
        Matrix* Inversion();
    
        static Matrix* InvertUpperTriangularMatrix(Matrix& M);
    
        static Matrix* InvertLowerTriangularMatrix(Matrix& M);


};

#endif