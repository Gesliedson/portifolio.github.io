#ifndef BIGINT_H
#define BIGINT_H
#include<cstdint>
#include <string>
#include <iostream>

using namespace std;
class BigInt
{
    private:
        bool neg;
        int nDig;
        int8_t* d;
        BigInt(bool IsNeg, int Size);
        ///metodo privado correct
        void correct ();
        ///metodo privado increment
        void increment ();
        ///metodo privado decrement
        void decrement ();


    public:
        //construtor default
        BigInt();
        ///Construtor por cópia
        BigInt(const BigInt &B);
        ///Construtor por movimento
        BigInt(BigInt &&A)noexcept;
        ///Operador por cópia
        BigInt &operator=(const BigInt &C);
        ///Destrutor
        BigInt &operator =(BigInt && D) noexcept;

        bool isNeg()const {return neg;}
        int size()const {return nDig;}
        bool isZero () const;

        ///Construtor especifico long long int -> BigInt
        BigInt (long long int N);

        ///funcao toInt  metodo(const Classe_Grande &X) para n alterar X
        long long int toInt ()const;
        int operator[](int i)const;

        ///construtor especifico a partir de um de uma string
        explicit BigInt(const std::string &S);

        /// funcao  <<
        friend std::ostream& operator << (std::ostream &J, const BigInt& A);
        ///funcao >>
        friend std::istream& operator>>(std::istream& I, BigInt& B);

        ///operator< (retorna true e o BigInt 1 formar menor q o 2)
        //friend bool operator<(const BigInt &A, const BigInt &B);






        ///operator++() pre-fixado
        BigInt& operator++();
        ///operator--() pre-fixado
        BigInt& operator--();
        ///operador++(int) pos-fixado
        BigInt operator++(int);
        ///operador--(int) pos-fixado
        BigInt operator--(int);




        ///funcao membro operator+ que nao deve modificar o objeto
        const BigInt& operator+() const;

        ///funcao membro operator- que retorna por copia o negativo
        BigInt operator-()const;

        /// funcao classica operator+ (somar BigInts)
        friend BigInt operator+(const BigInt &A,const BigInt &B);

        ///funcao classica operator-(subtrair BigInts)
        friend BigInt operator-(const BigInt &A, const BigInt &B);

        ///funcao classica operator*(multiplicar BigInts)
        friend BigInt operator*(const BigInt &A, const BigInt &B);


        ///Funcao classica operator<<  e >>(desloca os a esquerda e os da direita)
        friend BigInt operator<<(const BigInt &A, int N);
        friend BigInt operator>>(const BigInt &A, int N);

        ///Metodo publico division que faz a divisao inteira do objeto
        void division (const BigInt &D, BigInt &Q, BigInt &R) const;
        ~BigInt();

};


///funcao classica abs(x)
BigInt abs( BigInt X);

bool operator<(const BigInt &A, const BigInt &B);

/// funcao classica (sobrecarga do operator ==)
bool operator==(const BigInt &A, const BigInt &B);

/// operator!= (fazer a sobrecargo de != usando operator==)
bool operator!= (const BigInt &C, const BigInt &D);

///operator> (retorna true e o BigInt 1 for maior q o 2)
bool operator>(const BigInt &A, const BigInt &B);

///operator>= (retrona true se o BigInt 1 for maior ou igual q 2)
bool operator >= (const BigInt &A, const BigInt &B);

///operator<= (retrona true se o BigInt 1 for menor ou igual q 2)
bool operator <= (const BigInt &A, const BigInt &B);

///Funcao classica operator!(calcula o fatorial de um BigInt)
BigInt operator!(const BigInt &A);

BigInt operator/(const BigInt &A, const BigInt &B);
BigInt operator%(const BigInt &A, const BigInt &B);
#endif // BIGINT_H
