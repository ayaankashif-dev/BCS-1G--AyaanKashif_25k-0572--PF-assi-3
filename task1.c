#include <stdio.h>

double calculateRepayment(double loan, double interestRate, double installment, int years, int currentYear) {

    if (loan <= 0 || years == 0) {
        printf("Loan fully repaid or no years left.\n");
        return 0;
    }

    loan = loan + (loan * interestRate);

    loan = loan - installment;
    if (loan < 0) {
        loan = 0; 
    }

    printf("Year %d: Remaining loan = %.2f\n", currentYear, loan);

    return installment + calculateRepayment(loan, interestRate, installment, years - 1, currentYear + 1);
}

int main() {
    double loan = 100000;
    double interestRate = 0.05; 
    double installment = 35000;
    int years = 3;

    double total = calculateRepayment(loan, interestRate, installment, years, 1);

    printf("\nTotal repayment over %d years = %.2f\n", years, total);
    return 0;
}
