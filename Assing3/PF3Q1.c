#include <stdio.h>

double calculateRepayment(double loan, double interestRate, double installment, int years)
{
    if (years == 0 || loan <= 0) return 0;

    loan = loan + (loan * interestRate/100);
    loan = loan - installment;

    if (loan < 0) loan = 0;

    printf("Year %d: Remaining loan = %.2f\n", years, loan);

    return installment + calculateRepayment(loan, interestRate, installment, years - 1);
}

int main()
{
    double loan = 1000000;
    double rate = 5;
    int years = 3;
    double installment = 35000;

    double total = calculateRepayment(loan, rate, installment, years);

    printf("Total repayment in %d years = %.2f\n", years, total);

    return 0;
}
