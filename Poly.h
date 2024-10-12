#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <fstream>
#include <cmath> // Adicionado para fun��es matem�ticas

class Poly {
private:
    int grau;        // Grau do polin�mio
    double *a;       // Array din�mico de coeficientes

public:
    // Construtores e destrutor
    Poly();                              // Construtor padr�o (polin�mio vazio)
    explicit Poly(int grau);             // Construtor com grau espec�fico
    Poly(const Poly &other);             // Construtor de c�pia
    Poly(Poly &&other) noexcept;         // Construtor de movimento
    ~Poly();                             // Destrutor

    // M�todos de acesso e modifica��o
    int getGrau() const;                 // Retorna o grau do polin�mio
    double getCoef(int i) const;         // Retorna o coeficiente de �ndice i
    void setCoef(int i, double valor);   // Define o coeficiente de �ndice i

    // Operadores sobrecarregados
    Poly& operator=(const Poly &other);  // Operador de atribui��o por c�pia
    Poly& operator=(Poly &&other) noexcept;  // Operador de atribui��o por movimento
    Poly operator-() const;              // Operador un�rio de nega��o
    Poly operator+(const Poly &other) const; // Soma de polin�mios
    Poly operator-(const Poly &other) const; // Subtra��o de polin�mios
    Poly operator*(const Poly &other) const; // Multiplica��o de polin�mios
    bool operator==(const Poly &other) const; // Compara��o de igualdade
    bool operator!=(const Poly &other) const; // Compara��o de desigualdade
    double operator[](int i) const;      // Acesso aos coeficientes via �ndice
    double operator()(double x) const;   // Avalia��o do polin�mio para um dado x

    // M�todos utilit�rios
    bool empty() const;                  // Verifica se o polin�mio � vazio
    bool isZero() const;                 // Verifica se o polin�mio � nulo
    double getValor(double x) const;     // Calcula o valor do polin�mio para um dado valor de x
    void recriar(int novoGrau);          // Redefine o polin�mio para um novo grau

    // Entrada e sa�da de dados
    friend std::istream& operator>>(std::istream &in, Poly &p);
    friend std::ostream& operator<<(std::ostream &out, const Poly &p);
    bool salvar(const std::string &filename) const; // Salva polin�mio em arquivo
    bool ler(const std::string &filename);          // L� polin�mio de arquivo
};

#endif // POLY_H
