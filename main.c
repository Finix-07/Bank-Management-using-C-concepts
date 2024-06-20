#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


struct login
{
    char name[30];
    int acc_no;
    char pass[50];
};
struct acc_info
{
    char name[30];
    int ac_no;
    char add[500];
    int phone_no;
    char type[10];
};
struct Card
{
    char cardNumber[17]; // 16-digit card number + '\0'
    char cardHolderName[50];
    char expiryDate[6]; // MM/YY format
    int cvv;
    double balance;
};
struct Loan
{
    char customerName[50];
    float loanamount;
    float interestRate;
    int loanDuration;
};
struct login l;
struct acc_info aci;
struct transact
{
    char name[20];
    int accno;
    float balance;
} t1;

void transaction();
void account_info();
void convertCurrency();
int validateCard(struct Card card);
void createCard();
void displayCard();
void comp();
void crso();
void risk();
void cras();
void FAQ();
void addLoan();
void displayLoans();

int main()
{

    int flag = 0, ano;
    char password[50];
    FILE *fp;

    fp = fopen("login.txt", "r");

    printf("*********************************************************************\n");
    printf("**********************WELCOME TO BANK MANAGEMENT*********************\n");
    printf("*********************************************************************\n\n\n");
    printf("Enter Account Number: ");
    scanf("%d", &ano);
    printf("\nEnter password: ");
    scanf("%s", password);

    while (fscanf(fp, "%s %d %s", l.name, &l.acc_no, l.pass) == 3 && flag == 0)
    {
        if (l.acc_no == ano && strcmp(l.pass, password) == 0)
        {
            printf("\nLogin Successful....\nWELCOME %s", l.name);
            flag = 1;
            break;
        }
    }
    int count, ch, chh, chhh, chhhh;
    if (flag != 0)
    {
        fclose(fp);
        do
        {
            printf("\n\nMenu\n1. Manage Account Details\n2. Transaction Within Bank\n3. Account Management\n4. Services and Information\n5. Log out\n\n");
            scanf("%d", &count);
            switch (count)
            {
            case 1:
                account_info();
                break;
            case 2:
                transaction();
                break;
            case 3:
                printf("Welcome to Account manager. Enter your prefered choice\n1. Loan Management\n2. Credit/Debit Card Management\n");
                scanf("%d", &ch);
                switch (ch)
                {
                case 1:
                    printf("Enter what you want to do(We suggest going through the interest section to gain information about interst rates of our bank).\n1. Display current loans\n2. Add a loan.\n");
                    scanf("%d", &chh);
                    switch (chh)
                    {
                    case 1:
                        displayLoans();
                        break;
                    case 2:
                        addLoan();
                        break;
                    default:
                        break;
                    }
                    break;
                case 2:
                    printf("Enter what you want to do(We suggest going through the Credit card section of our bank).\n1. Create a new Card\n2. Display current cards.\n3. Validate your card\n");
                    scanf("%d", &chhh);
                    switch (chhh)
                    {
                    case 1:
                        createCard();
                        break;
                    case 2:
                        displayCard();
                        break;
                    case 3:
                        /*char cardNumber[17]; // 16-digit card number + '\0'
                        char cardHolderName[50];
                        char expiryDate[6]; // MM/YY format
                        int cvv;
                        double balance; is the format remember*/
                        struct Card c1;
                        printf("\nEnter you Credit card number: ");
                        scanf("%s", c1.cardNumber);
                        printf("\nEnter Credit Card holder's name: ");
                        scanf("%s", c1.cardHolderName);
                        printf("\nEnter Expiry Date: ");
                        scanf("%s", c1.expiryDate);
                        printf("\nEnter CVV: ");
                        scanf("%d", &c1.cvv);
                        validateCard(c1);
                        break;
                    default:
                        break;
                    }
                default:
                    break;
                }
                break;
            case 4:
                printf("\nServices and information menu...\n1. FAQs\n2. Interest Calculation\n3. Credit scoring and assessment \n4. Currency Exchange Services\n");
                scanf("%d", &chhhh);
                switch (chhhh)
                {
                case 1:
                    FAQ();
                    break;
                case 2:
                    comp();
                    break;
                case 3:
                    cras();
                    break;
                case 4:
                    convertCurrency();
                    break;
                default:
                    break;
                }
                break;
            case 5:
                printf("Thanks for using the program.....\nLogging out....\n\n\nSuccessfully Logged out.");
            }

        } while (count != 5);
    }
    else
    {
        printf("\n\nInvalid credentials.....\nRelaunch the program and try again\n");
    }
    return 0;
}

void transaction()
{
    FILE *trf;
    int fl = 1, amount, Reciever_No, Sender_No;
    trf = fopen("balance.txt", "r+");
    if (trf == NULL)
    {
        printf("Error with the application, Try restarting the program.....");
    }
    fseek(trf, 0, SEEK_SET);
    printf("Re-Validate your account number..\n");
    scanf("%d", &Sender_No);
    while (fscanf(trf, "%s %d %f", t1.name, &t1.accno, &t1.balance) == 3)
    {
        if (t1.accno == Sender_No)
        {
            printf("Your Current balance is: %.2f", t1.balance);
            printf("\nEnter the amount to be Sent: ");
            scanf("%d", &amount);
            printf("\nEnter the account number of the reciever: ");
            scanf("%d", &Reciever_No);
            printf("Transaction is successful. \n Your new balance is %f", t1.balance - amount);
            fl = 0;

            break;
        }
        fseek(trf, 0, SEEK_SET);
        FILE *tempFile;
        tempFile = fopen("temp.txt", "w+");
        while (fscanf(trf, "%s %d %f", t1.name, &t1.accno, &t1.balance) == 3)
        {
            if (t1.accno == Sender_No)
            {
                t1.balance = t1.balance - amount;
                fprintf(tempFile, "%s %d %f\n", t1.name, t1.accno, t1.balance);
            }
            if (t1.accno == Reciever_No)
            {
                t1.balance = t1.balance + amount;
                fprintf(tempFile, "%s %d %f\n", t1.name, t1.accno, t1.balance);
            }

            fprintf(tempFile, "%s %d %f\n", t1.name, t1.accno, t1.balance);
        }
        fclose(tempFile);
        fclose(trf);
        (remove("balance.txt"));
        (rename("temp.txt", "balance.txt"));
    }
    if (fl == 1)
    {
        printf("Error fetching Account's balance kindly retry after sometime....");
    }
}
void account_info()
{
    int ch = 1, c, fl = 0, option;
    char corr_name[30];
    int ano;
    while (ch)
    {
        printf("\n\n\nSelect the desired choice.\n");
        printf("1. Show account's information\n");
        printf("2. Edit/Modify Details\n");
        scanf("%d", &c);

        switch (c)
        {
        case 1:
            fl = 0;
            FILE *fp1;
            fp1 = fopen("aci.txt", "r");
            while (fscanf(fp1, "%s %d %s %d %s", aci.name, &aci.ac_no, aci.add, &aci.phone_no, aci.type) == 5 && fl == 0)
            {
                if (aci.ac_no == l.acc_no)
                {
                    printf("Your details are:-\n");
                    printf("Name:%s\nAccount Number:%03d\nAddress:%s\nPhone Number:%d\nAccount Type:%s", aci.name, aci.ac_no, aci.add, aci.phone_no, aci.type);
                    fl = 1;
                    break;
                }
            }
            fclose(fp1);
            break;

        case 2:
            FILE *fp;
            struct acc_info aci;
            int ano;
            int fl = 0;

            fp = fopen("aci.txt", "r+");
            if (fp == NULL)
            {
                printf("Error opening file.\n");
            }
            printf("Enter the account number: ");
            scanf("%d", &ano);

            fseek(fp, 0, SEEK_SET);

            // Shows the current saved record
            while (fscanf(fp, "%s %d %s %d %s", aci.name, &aci.ac_no, aci.add, &aci.phone_no, aci.type) == 5)
            {
                if (aci.ac_no == ano)
                {
                    printf("Your details are:\n");
                    printf("Name: %s\nAccount Number: %03d\nAddress: %s\nPhone Number: %d\nAccount Type: %s\n",
                           aci.name, aci.ac_no, aci.add, aci.phone_no, aci.type);
                    fl = 1;
                    break;
                }
            }

            if (fl == 0)
            {
                printf("Account not found.\n");
                fclose(fp);
            }

            fseek(fp, 0, SEEK_SET);

            // make a temp file to replace current
            FILE *tempFile;
            tempFile = fopen("temp.txt", "w");

            // update the info in the temp file
            while (fscanf(fp, "%s %d %s %d %s", aci.name, &aci.ac_no, aci.add, &aci.phone_no, aci.type) == 5)
            {
                if (aci.ac_no == ano)
                {
                    printf("\nEnter the updated records:\n");
                    printf("Enter updated name: ");
                    scanf("%s", aci.name);
                    printf("Enter updated address: ");
                    scanf("%s", aci.add);
                    printf("Enter updated Phone Number: ");
                    scanf("%d", &aci.phone_no);
                }
                fprintf(tempFile, "%s %03d %s %d %s\n", aci.name, aci.ac_no, aci.add, aci.phone_no, aci.type);
            }

            fclose(fp);
            fclose(tempFile);

            // Remove the file with the old data
            (remove("aci.txt"));

            // Rename the temporary file to the deleted file name
            (rename("temp.txt", "aci.txt"));

            printf("\nRecord updated successfully.\n");

        default:
            ch = 0;
            break;
        }
    }
}
// currency convert
void convertCurrency()
{
    float amount, exchangeRate, result;

    printf("Enter the amount in Foreign Currency: ");
    scanf("%f", &amount);

    printf("\nFrom The given table Enter the conversion Rate from the currency you entered.");
    printf("\n1.USD->INR:82.81\n2.EUR->INR:87.99\n3.GBP->INR:100.02\n4.JPY->INR:0.61\n5.CHF->INR:89.68\n6.CAD->INR:60.21\n7.AUD->INR:54.94\n8.SGD->INR:61.33\n9.HKD->INR:10.54\n10.CNY->INR:11.98\n");

    printf("\nEnter the exchange rate from the table above: ");
    scanf("%f", &exchangeRate);

    printf("Please note our Bank charges 1.5 percent conversion tax for all conversions\n");
    // Perform currency conversion
    result = amount * exchangeRate * 0.985;

    printf("The money you will recieve after conversion is : %.1f INR\n", result);
}
// CC/DC
int validateCard(struct Card card)
{
    // Perform basic validation
    if (strlen(card.cardNumber) != 16 || strlen(card.expiryDate) != 5 || strlen(card.cardHolderName) == 0 || card.cvv < 100 || card.cvv > 999 || card.balance < 0)
    {
        return 0; // Invalid card information
    }

    return 1; // Card information is valid
}
void createCard()
{
    struct Card newCard;

    printf("Enter card number (16 digits): ");
    scanf("%s", newCard.cardNumber);
    printf("Enter cardholder name: ");
    scanf("%s", newCard.cardHolderName);
    printf("Enter expiry date (MM/YY): ");
    scanf("%s", newCard.expiryDate);
    printf("Enter CVV (3 digits): ");
    scanf("%d", &newCard.cvv);
    printf("Enter initial balance: $");
    scanf("%lf", &newCard.balance);

    // Validate card information
    if (validateCard(newCard))
    {
        FILE *file = fopen("cards.txt", "a");
        if (file == NULL)
        {
            printf("Error opening file.\n");
            return;
        }

        fprintf(file, "%s %s %s %d %.2f\n", newCard.cardNumber, newCard.cardHolderName, newCard.expiryDate, newCard.cvv, newCard.balance);

        fclose(file);

        printf("Card created successfully.\n");
    }
    else
    {
        printf("Invalid card information. Card not created.\n");
    }
}
void displayCard()
{
    char searchNumber[17];
    struct Card currentCard;

    printf("Enter card number to display: ");
    scanf("%s", searchNumber);

    FILE *file = fopen("cards.txt", "r");
    if (file == NULL)
    {
        printf("No cards found.\n");
        return;
    }

    int found = 0;
    while (fscanf(file, "%s %s %s %d %lf", currentCard.cardNumber, currentCard.cardHolderName, currentCard.expiryDate, &currentCard.cvv, &currentCard.balance) != EOF)
    {
        if (strcmp(searchNumber, currentCard.cardNumber) == 0)
        {
            printf("Card Number: %s\n", currentCard.cardNumber);
            printf("Cardholder Name: %s\n", currentCard.cardHolderName);
            printf("Expiry Date: %s\n", currentCard.expiryDate);
            printf("CVV: %d\n", currentCard.cvv);
            printf("Balance: $%.2f\n", currentCard.balance);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("Card not found for the given number '%s'.\n", searchNumber);
    }
}
// Loan enquiry
void comp()
{
    int cho;
    printf("\nHello Client,\n At our bank, we believe in giving our customers the best value for their\n money; allowing them to enjoy the benefits of borrowing and saving at the same time.\nSo we took it upon us to set an interest rate which keeps up \nwith how the market changes as this influences many other interest rates in the economy.\n");
    printf("Also taking other factors into consideration,\n**FOR MORE DETAILS REFERS THE FAQS.**\n Our bank offers: \nRate for Saving Accounts - \n2.00 P.A. for balances up to INR 10Cr \n2.50 P.A. for balances of INR 10Cr and above.\n");
    printf("\n\nIf you interested in an interest calculation and interested in knowing how it works enter any number, else enter 0 to exit.\n");
    scanf("%d", &cho);
    if (cho){
    printf("\nNow a simple calculator for your estimation:\n");    
    float p, r, si;
    double ci;
    int t;
    printf("Enter the principal amount:");
    scanf("%f", &p);
    printf("Enter the rate of interest :");
    scanf("%f", &r);
    printf("Enter the time:");
    scanf("%d", &t);
    si = p * r * t / 100;
    printf("The simple interest is:%.2f\n", si);

    ci = p * (pow((1 + r / 100), t));

    printf("The compound interest is:%.2lf\n", ci);

    printf("\n\nSimple interest is easy to calculate: your interest is the principal multiplied by the \n interest rate multiplied by the number of time intervals.\n The formula is:\nA=P(1+r/n)^nt\nWhere\nA = Final sum\nP = Principal\nr = Interest rate\nn = number of times interest is compounded in a time frame\nt = time frame");
    printf("\nCompound interest works by adding accumulated interest over time to your principal. \nThis means that accounts that compound interest grow more rapidly compared to simple interest without compounding.\n The compound interest formula is:\n A = P (1 + r/n)^(nt)\n where \n P is your principal (initial deposit)\nr is the annual rate of interest as a decimal\nt is the length of time the principal is on deposit\nn is the number of times interest is compounded per unit of t\nA is the future value you will have at the end of the time period");
    }
}
    
// cred score+risk+FAQ
void crso()
{
    printf("Credit scoring: What is it?\n");
    printf("As a responsible lender, we take into account your personal and/or business circumstances when opening a personal or business account, establishing the appropriate level of credit to grant you or your business. To help us do this, a statistical analysis is performed to determine the creditworthiness of our client.\n\n");

    printf("B. How does credit scoring work?\n");
    printf("Credit scoring takes into account information provided directly by you, any information we may hold about you, and any information we may obtain from other organisations. Where we use information from other organisations, which may include a licensed Credit Reference Agency (CRA), a credit score is influenced by five categories:\n");
    printf("1. Payment history (35 percent)\n");
    printf("2. Amounts owed (30 percent)\n");
    printf("3. Length of credit history (15 percent)\n");
    printf("4. New credit (10 percent)\n");
    printf("5. Credit mix (10 percent)\n\n");
    printf("The credit scoring system allocates points for each piece of relevant information and adds these up to produce a score. When your score reaches a certain level, then we will generally agree to your application. If your score does not reach this level, we may not.\n\n");

    printf("Is credit scoring fair?\n");
    printf("We believe that credit scoring is fair and impartial. It does not single out a specific piece of information as the reason for declining an application. We test our credit scoring methods regularly to make sure they continue to be fair and unbiased.\n");

}
void risk()
{
    printf("\n\n\nPlease go through this brief overview to know about risks.\n");

    printf("A. What is a banking risk assessment?\n");
    printf("A banking risk assessment is the process by which a bank assesses the potential risks it may face in conducting its business activities. The risk assessment often entails:\n");
    printf("1. Identifying and analyzing high-risk areas,\n");
    printf("2. Assessing the likelihood and potential effect of those risks,\n");
    printf("3. Comparing those risks to an organization’s overall risk appetite, and\n");
    printf("4. Developing risk mitigation plans.\n\n");

    printf("B. Key categories of risks commonly assessed\n");
    printf("1. Credit risk: The risk that borrowers or counterparties might default on their obligations, leading to financial loss for the bank.\n");
    printf("2. Market risk: The risk of losses arising from adverse changes in market prices and rates, such as interest rates, foreign exchange rates, equity prices, and commodity prices.\n");
    printf("3. Operational risk: Risks arising from failures in internal processes, systems, people, or external events.\n");
    printf("4. Liquidity risk: The risk that the bank may not be able to meet its financial obligations as they come due, without incurring unacceptable losses.\n");
    printf("5. Strategic risk: Risks arising from poor business decisions or inept implementation of business strategies.\n\n");

    printf("C. Common compliance risks for banks\n");
    printf("Banks have four high-priority compliance risks:\n");
    printf("1. Data privacy and cybersecurity breaches.\n");
    printf("2. Anti-Money laundering (AML) violations.\n");
    printf("3. Customer due diligence (CDD) failures.\n");
    printf("4. Consumer protection violations.\n");}
void cras()
{
    int choice;
    printf("\n\nHello Client,\nWhat would you like to know about?\nA.To know about credit scoring and how it works please press 1.\nB.To understand how our bank identifies risks and assesses please press 2.\n");
    printf("Please enter your option: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    {
        crso();
        break;
    }
    case 2:
    {
        risk();
        break;
    }
    default:
        break;
    }
}
void FAQ()
{
    printf("\n\n\n1.What is the purpose of loan management?\n");
    printf("  Loan Management System is designed to streamline the process of managing loans within a financial institution. It automates various aspects of the loan lifecycle, from origination (application and approval) to servicing and repayment.\n");
    printf("\n2. All About Currency Exchange services\n");
    printf("  Currency exchange works by letting you convert one currency, like dollars, to another, like euros. You give a currency exchange an amount in one currency, and they give you back an amount of a different currency with a similar purchasing power, subtracting out any fees or other charges.\n");
    printf("  By exchanging currencies, travelers can purchase goods using the currency that's most frequently accepted wherever they are visiting.\n");
    printf("** THERE'S NO SUCH THING AS NO COMMISSION, THE FEE IS JUST HIDDEN IN THE RATE**\n");
    printf("  Listed below are our most popular traded currencies and the AVERAGE rate we provide:\n");
    printf("  1.Bahraini Dinar(BHD): 1BHD = INR 221.2 \n");
    printf("  2.US Dollar(USD): 1USD = INR 69.910\n");
    printf("  3.Euro(EUR): 1EUR = INR 90.23\n");
    printf("  4.British pound sterling (GBP): 1GBP = INR 105.29\n");
    printf("  5. United Arab Emirates Dirham(AED): 1AED = INR 43.71\n");
    printf("\n3.Worried about your data?\n");
    printf("  Well...Fear not! We have our own data centers and data backup facilities and we have taken high-level physical and cyber security measures to protect data from unauthorized access and catastrophic events.\n");
    printf("  TO protect against the risk of a single location data centers are geographically dispersed...maybe across countries or cities who knows! All you need to know is that your data is under safe hands\n");
    printf("\n4.Our E-Commerce facilities and how you can use them\n");
    printf("  We have have established a transactional website  where one can perform many basic banking functions such as checking balances, transferring funds, or applying for credit cards.\n\n");
}
// Manage loans
void addLoan()
{
    struct Loan newLoan;

    printf("Enter customer name: ");
    scanf("%s", newLoan.customerName);
    printf("Enter loan amount: ");
    scanf("%f", &newLoan.loanamount);
    printf("Enter interest rate: ");
    scanf("%f", &newLoan.interestRate);
    printf("Enter loan duration (in months): ");
    scanf("%d", &newLoan.loanDuration);

    FILE *file = fopen("loans.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s %.2f %.2f %d\n", newLoan.customerName, newLoan.loanamount, newLoan.interestRate, newLoan.loanDuration);

    fclose(file);

    printf("Loan added successfully.\n");
}
void displayLoans()
{
    struct Loan currentLoan;

    FILE *file = fopen("loans.txt", "r");
    if (file == NULL)
    {
        printf("No loans found.\n");
        return;
    }

    printf("\nLoans:\n");
    while (fscanf(file, "%s %f %f %d", currentLoan.customerName, &currentLoan.loanamount, &currentLoan.interestRate, &currentLoan.loanDuration) != EOF)
    {
        printf("Customer: %s\n", currentLoan.customerName);
        printf("amount: $%.2f\n", currentLoan.loanamount);
        printf("Interest Rate: %.2f%%\n", currentLoan.interestRate);
        printf("Duration: %d months\n", currentLoan.loanDuration);
        printf("----------------\n");
    }

    fclose(file);
}
