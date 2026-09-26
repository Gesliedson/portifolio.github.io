#include <iostream>
#include "BigInt.h"
#include <cmath>

using namespace std;
/* *************************************************************************
 * ATENCAO ATENCAO ATENCAO ATENCAO ATENCAO ATENCAO ATENCAO ATENCAO ATENCAO *
 * ************************************************************************* */

// Este NAO EH um arquivo .cpp valido. Soh contem PARTES de codigo,
// que devem ser incluidas (copiar e colar) no arquivo bigint.cpp,
// a ser criado por voceh e incorporado ao projeto.

/* *************************************************************************
 * ATENCAO ATENCAO ATENCAO ATENCAO ATENCAO ATENCAO ATENCAO ATENCAO ATENCAO *
 * ************************************************************************* */

/// Construtor default.
/// Inicializa com um inteiro de 1 digito, valor 0 (zero).
/// NAO PODE SER MODIFICADO
BigInt::BigInt()
  : neg(false)
      , nDig(1)
      , d(new int8_t[1]{0})

{}
//construtor específico privado
BigInt :: BigInt(bool IsNeg, int Size)
    : neg(IsNeg)
    , nDig ( Size>0 ? Size: 1)
    , d(new int8_t[nDig]{})
{}

/// Construtor por copia.
/// Delega ao construtor especifico privado.
/// NAO PODE SER MODIFICADO.
BigInt::BigInt(const BigInt& B)
  : BigInt(B.isNeg(), B.size())
{
  // Copia os digitos
  for (int i=0; i<size(); ++i) d[i] = B.d[i];
}

///construtor por movimento?
BigInt::BigInt(BigInt &&A) noexcept
    : neg(A.neg)
    , nDig(A.nDig)
    , d(A.d)
    {
        A.neg = false;
        A.nDig = 0;
        A.d = nullptr;

    }

///Operador por cópia
BigInt &BigInt::operator=(const BigInt &C)
{
    if (this == &C) return *this;

    delete [] d;

    neg = C.neg;
    nDig = C.nDig;
    d = (nDig > 0? new int8_t[nDig] : nullptr );

    for (int i=0; i<nDig; ++i) d[i] = C.d[i];
    return *this;
}

BigInt &BigInt::operator=( BigInt &&D) noexcept
{

    if (this == &D) return *this;
    delete [] d;

    neg = D.neg;
    nDig = D.nDig;
    d = D.d;

    D.neg = false;
    D.nDig = 0;
    D.d = nullptr;

    return *this;
}

bool BigInt::isZero()const
{
    if (nDig ==1 && d[0] == 0) return true;
    return false;
}
int BigInt::operator[](int i) const
{
    if( i>=size() || i<0) return 0;
    return d[i];
}

/// Construtor especifico a partir de inteiro longo.
/// Tambem conversor de long long int para BigInt.
/// NAO PODE SER MODIFICADO NAS PARTES JAH IMPLEMENTADAS.
/// PODE (E PRECISA) RECEBER ACRESCIMOS, APENAS
/// NAS PARTES INDICADAS POR /* ACRESCENTAR
BigInt::BigInt(long long int N)
  /* ACRESCENTAR */
  ///Vai ser preciso revisar, pois nao parece ser uma boa ideia usar um constutor
  : neg ( N >= 0.0? false : true ) /// diz respeito ao sinal
    , nDig (N == 0.0? 1 : 1+ int(log10(fabs(N)))) ///diz respeito a qtd de digitos
    , d(new int8_t[nDig])

{
  // Calcula os digitos, usando divisao inteira por 10
  for (int i=0; i<size(); ++i)
  {
    d[i] = abs(N%10); // Modulo do resto da divisao
    N /= 10;          // Divisao inteira
  }
}
///implementacao da funcao toInt
///nos parametros e passado uma referencia costante
///para otimizacao e para nao alterar o parametro
long long int BigInt::toInt() const
{
    long long int val(0);
    for (int i= this->size()-1; i>=0; --i)
    {
        val = val*10 + this->d[i];
        if (val < 0)
      {
            cerr << " Erro: O limite maximo foi excedido\n";
            return 0;
        }
    }

    if (this->isNeg()) val = -1*val;
    return val;
}

/// metodo privado correct

void BigInt:: correct  ()
{
    int newSize(this->size());

    //o loop vai funcionar enquanto o tamanho do bigint
    // for maior q 1 e os 0's forem os dig. mais significativos
    //Em outras palavras, aqui é eliminado as posicoes invalidas
    while (newSize>1 && this->d[newSize-1] == 0 )
    {
        newSize-=1;
    }

    /// vai verificar se os tamnhos sao diferentes para fazer a permutacao
    /// dos elementos
    if (newSize != this->size())
    {

        BigInt aux(neg, newSize); // BigInt auxiliar para i de 0 ate newSize
        //copia os valores validos para o Bigint auxiliar
        for (int i=0; i<newSize; ++i) {aux.d[i] = d[i];}
        ///nDig = newSize;

        *this = move(aux);
    }
    //corige o zero negativo

    if (this->isZero()) neg = false;
}
///DESTRUTOR?
  BigInt::~BigInt()
  {
      delete [] d;
      d = nullptr;

  }

/// Construtor especifico a partir de string.
/// Nao eh conversor de string para BigInt.
/// Delega ao construtor default.
/// NAO PODE SER MODIFICADO NAS PARTES JAH IMPLEMENTADAS.
/// PODE (E PRECISA) RECEBER ACRESCIMOS, APENAS
/// NAS PARTES INDICADAS POR /* ACRESCENTAR */

BigInt::BigInt(const string &S)
  : BigInt() // Valor inicial zero
{
  // Se string vazia, emite erro e permanece com valor inicial zero
  if (S.empty())
  {
    cerr << "empty string cannot create a BigInt\n";
    return;
  }

  // Posicao onde comecam os digitos, inicialmente zero
  size_t ini=0;
  // Leva em conta o sinal
  bool IsNeg = false;

  if (S[0]=='+' || S[0]=='-')
  {
    // Se nao tem nenhum digito alem do sinal, emite erro e permanece com valor inicial
    if (S.size()==1)
    {
      cerr << "sign-only string cannot create a BigInt\n";
      return;
    }
    IsNeg = (S[0]=='-');
    ++ini;
  }

  // Faz ter sinal (IsNeg) e numero de digitos (tamanho da string - ini) corretos
  /* ACRESCENTAR*/

  *this = BigInt(IsNeg, S.size() - ini); // passando o sinal e o tamanho valido para o BigInt
  for (int i=0; i<size(); ++i)
  {
    const char& c = S[S.size()-1-i]; // Referencia (apelido) para facilitar a notacao
    if (!isdigit(c))
    {
      *this = BigInt(); // = 0
      cerr << "string with invalid character cannot create a BigInt\n";
      return;
    }
    d[i] = static_cast<int8_t>(c-'0');
  }
  // Corrige eventuais numeros fora da especificacao
  correct();
}


/// funcao <<
std::ostream& operator<<(ostream& J, const BigInt& A)
{
    if (A.isNeg()) J << '-';
    for (int i= A.size()-1; i>=0; --i )
    {
        if (A.d[i]>=0 && A.d[i] <=9 )
        {
            J << static_cast<int>(A.d[i]);
        }
        else
        {
            J << '#';
        }
    }

    return J;
}

/// Extracao (digitacao).
/// NAO PODE SER MODIFICADO NAS PARTES JAH IMPLEMENTADAS.
/// PODE (E PRECISA) RECEBER ACRESCIMOS, APENAS
/// NAS PARTES INDICADAS POR /* ACRESCENTAR

std::istream& operator>>(istream& I, BigInt& B)
{
  // Valor inicial zero
  B = BigInt(); // = 0

  // Testa a stream de entrada e descarta eventuais separadores iniciais.
  // Em caso de erro, encerra a digitacao.
  istream::sentry s(I);
  if (!s) return I;

  // Inspeciona o primeiro caractere que serah lido
  char c = I.peek();

  // Testa se o primeiro caractere eh um sinal.
  // Se for, consome (elimina do buffer), processa e inspeciona o proximo caractere.
  if (c=='+' || c=='-')
  {
    // Consome da stream
    I.get(c);  // Valor de "c" permanece o mesmo...
    // Atribui o sinal
    B.neg = (c=='-');
    // Obtem o proximo caractere
    c = I.peek();
  }

  // Numero de digitos que foram digitados
  int numDigitos = 0;

  // Testa se eh um caractere valido: digitos 0 a 9
  while (isdigit(c))
  {
    // Consome da stream
    I.get(c);  // Valor de "c" permanece o mesmo...
    ++numDigitos;

    if (numDigitos>1)
    {
      // Faz o BigInt manter o sinal e passar a ter size()+1 digitos,
      // avancando todos para uma posicao mais significativa aa frente.
      /* ACRESCENTAR*/

      BigInt Aux(B.neg,B.size()+1);

      for (int i=0; i<B.size() ; ++i)
      {
          Aux.d[i+1] = B.d[i];
      }

      B =  move(Aux);
    }

    // Acrescenta o novo digito como sendo o primeiro (o menos significativo)
    B.d[0] = static_cast<int8_t>(c-'0');

    // Inspeciona o proximo caractere que vai ser lido
    c = I.peek();
  }

  // Assinala erro na stream se nenhum digito foi lido
  if (numDigitos==0) I.setstate(ios::failbit);

  // Corrige eventuais erros na digitacao
  B.correct();

  // Encerra a digitacao
  return I;
}

/// funcao classica (sobrecarga do operator ==)
bool operator==(const BigInt &A, const BigInt &B)
{
    //verifica se eles tem mesmo sinal e tamanho
    if (A.isNeg() == B.isNeg() && A.size() == B.size())
    {
        // percorre tentando procurando algum digito diferente
        for (int i = A.size()-1; i>=0; --i)
        {
            if (A[i] != B[i]) return false;
        }

        return true; // retorna isso se n encontar nada !=
    }

    return false; // retorna isso caso tenham sinais e tamanhos !=
}

/// operator!= (fazer a sobrecargo de != usando operator==)

bool operator!=(const BigInt &C, const BigInt &D)
{
    //aproveita a natureza da funcao ==
    // e basta usar ela nu return para implementar o operador!=
    return !(C==D);
}

///operator< (retorna true e o BigInt 1 formar menor q o 2)
bool operator<(const BigInt &A, const BigInt &B)
{
    //sinais diferentes
    if (A.isNeg() != B.isNeg()) return A.isNeg();
    //tamanhos diferentes?
    if (A.size() != B.size())
    {
        if(!A.isNeg()) //positivo ou nulo
        {
            return (A.size() < B.size());
        }
        else //caso contrario
        {
            return ( A.size() > B.size());
        }
    }

    //Mesmo numero de digitos
    for (int i= A.size()-1; i>=0; --i)
    {
        if (A[i] != B[i])
        {
            if(!A.isNeg()) //positivo ou nulo
            {
                return (A[i] < B[i]);
            }
            else
            {
                return (A[i] > B[i]);
            }
        }
    }
    //numeros identicos
    return false;
}

///operator> (retorna true e o BigInt 1 formar maior q o 2)
bool operator>(const BigInt &A, const BigInt &B)
{
    return (B<A);// A>B eh o mesmo que B<A
}

///operator>= (retrona true se o BigInt 1 for maior ou igual q 2)
bool operator>=(const BigInt &A, const BigInt &B)
{
    return !(A<B);//A>=B -> NÃO(A<B)
}

///operator<= (retrona true se o BigInt 1 for menor ou igual q 2)
bool operator<=(const BigInt &A, const BigInt &B)
{
    return !(B<A); //A<=B -> NÃO(B<A)
}

void BigInt::increment()
{
    int k(0);

    while (k<size())
    {
        if(d[k] < 9)
        {
            d[k] = d[k] + 1;
            return;
        }
        d[k] = 0;
        k = k+1;
    }

    BigInt Aux(neg,size()+1);

    for (int i=0; i<size(); ++i) Aux.d[i] = d[i];
    Aux.d[size()] = 1;

    *this = Aux;
}

void BigInt::decrement()
{
    if (isZero())
    {
        neg = true;
        d[0] = 1;
        return;
    }

    int k=0;

    while (k < size())
    {
        if (d[k] > 0)
        {
            d[k] = d[k] - 1;
            break;
        }
        d[k] = 9;
        k = k + 1;
    }
    correct();
}
///operator++ pre-fixado
BigInt& BigInt::operator++()
{
    if(!(isNeg())) increment();
    else decrement();
    return *this;
}
///operator-- pre-fixado
BigInt& BigInt::operator--()
{
    if (isNeg()) increment();
    else decrement();
    return *this;
}
///operador++(int) pos-fixado
BigInt BigInt::operator++(int)
{
    BigInt Aux(*this);
    ++(*this);
    return Aux;
}

///operador--(int) pos-fixado
BigInt BigInt::operator--(int)
{
    BigInt Aux(*this);
    --(*this);
    return Aux;
}
///funcao classica abs(x)
BigInt abs(BigInt X)
{
    if (X.isNeg()) return -X;
    return X;
}
///funcao membro operator+ que nao deve alterar o objeto
const BigInt& BigInt::operator+() const
{
    return *this;
}
BigInt BigInt::operator-() const
{
    BigInt Aux(*this);
    if (Aux.isZero()) Aux.neg = false;
    else Aux.neg = !Aux.neg;
    return Aux;
}

BigInt operator+(const BigInt &A, const BigInt &B)
{
    if (A.isZero()) return B;
    if (B.isZero()) return A;
    if (A.isNeg() != B.isNeg()) return A-(-B);

    BigInt C(A.neg, 1+max(A.size(), B.size()));
    int carry = 0;

    for (int i=0; i < C.size(); ++i)
    {
        C.d[i] = A[i] + B[i] + carry;
        if(C.d[i] > 9)
        {
            C.d[i] = C.d[i]-10;
            carry = 1;
        }
        else carry = 0;
    }
    C.correct();
    return C;
}
///funcao classica operator-(subtrair BigInts)
BigInt operator-(const BigInt &A,const BigInt &B)
{
    if(A.isZero()) return -B;
    if(B.isZero()) return A;
    if(A.isNeg() != B.isNeg()) return A+(-B);
    if(abs(A) < abs(B)) return -(B-A);

    BigInt C(A.neg, A.size());
    int borrow = 0;

    for(int i=0; i<C.size(); ++i)
    {
        C.d[i] = A[i] - B[i] - borrow;
        if (C.d[i] < 0)
        {
            C.d[i] = C.d[i] + 10;
            borrow = 1;
        }
        else borrow = 0;
    }
    C.correct();
    return C;
}
///funcao classica operator*(multiplicar BigInts)
BigInt operator*(const BigInt &A, const BigInt &B)
{
    if(A.isZero() || B.isZero()) return 0;
    BigInt C( A.neg!=B.neg? true : false, A.size() + B.size());

    for (int i=0; i<A.size(); ++i)
    {
        if (A.d[i] != 0)
        {
            for (int j=0; j<B.size(); ++j)
            {
                if (B.d[j] != 0)
                {
                    int k = i+j;
                    C.d[k] = C.d[k] + A.d[i] * B.d[j];

                    while (C.d[k] > 9)
                    {
                        int carry = C.d[k] / 10;
                        C.d[k]= C.d[k]% 10;
                        k = k + 1;
                        C.d[k] = C.d[k] + carry;
                    }
                }
            }
        }
    }
    C.correct();
    return C;
}
///Funcao classica operator!(calcula o fatorial de um BigInt)
BigInt operator!(const BigInt &A)
{
    if(A.isNeg())
    {
        cout << "Erro: numero negativo\n";
        return 0;
    }

    BigInt C(1);
    for (BigInt N =2 ; N<=A; ++N)
    {
        C = C * N;
    }

    return C;
}

///Funcao classica operator<< (desloca os a esquerda)
BigInt operator<<(const BigInt &A, int N)
{
    if (N <= 0 || A.isZero()) return A;
    BigInt C(A.neg, A.size()+N);

    for (int i=N; i<C.size(); ++i)
    {
        C.d[i] = A.d[i-N];
    }
    return C;
}
///Funcao classica operator<< (desloca os a direita)
BigInt operator>>(const BigInt &A, int N)
{
    if (N<=0 || A.isZero()) return A;
    if (N >= A.size()) return 0;

    BigInt C(A.neg, A.size()-N);

    for (int i=0; i<C.size(); ++i)
    {
        C.d[i] = A.d[i+N];
    }

    return C;
}
void BigInt::division (const BigInt &D, BigInt &Q, BigInt &R) const
{
    if  ( this->isZero() || D.isZero())
    {
        if(D.isZero()) cerr << "Erro: Divisao por zero\n";
        Q = 0;
        R = 0;
        return;
    }

    BigInt absD(abs(D));

    if (abs(*this) < absD)
    {
        Q = 0;
        R = *this;
        return;
    }

      Q = BigInt(this->isNeg() != D.isNeg()? true : false, this->size() - D.size() + 1 );

    R = abs( *this >> (this->size() - D.size()));

    for (int i= Q.size()-1; i>=0; --i)
    {
        int div = 0;

        while ( R >= absD)
        {
            R = R - absD;
            div = div + 1;
        }

        Q.d[i] = div;

        if (i>0)
        {
            R = R << 1;
            R.d[0] = this->d[i-1];
        }
    }
    Q.correct();

    if (!(R.isZero())) R.neg = this->isNeg();
}
/// Funcao classica do operator/ (retorna o quociente)
BigInt operator/(const BigInt &A, const BigInt &B)
{
    BigInt Q, R;
    A.division(B,Q,R);

    return Q;
}
/// Funcao classica do operator% (retorna o resto)
BigInt operator%(const BigInt &A, const BigInt &B)
{
    BigInt Q, R;
    A.division(B,Q,R);

    return R;
}
