# Bank Management using C concepts
 1st semester project

### Overview
This console-based banking management project was developed for our first semester project to practically apply our understanding of the C/C++ programming languages. The system uses a file-based storage system to persist data across sessions.

We worked upon this project as a group where my work mainly involved implementing:
- Account management, Transaction, Credit card information and navigating around the project.

### Features
1. **Account Management**
   - Create and manage user accounts.
   - Update account details.
   - Delete accounts.

2. **Transactions**
   - Transfer funds between accounts.
   - Validate transactions using account details and passwords.

### Modules and Functions

#### 1. **Main Menu**
   - Displays options for account management, fund transfer, credit cards and loans.
   - Prompts the user to choose an option and navigate to the respective function.

#### 2. **Account Management**
   - **Create Account**: Collects user details (name, address, phone number, account type) and stores them in a file.
   - **Update Account**: Allows users to update their account details.

#### 3. **Fund Transfer**
   - Prompts user for source and destination account numbers and amount.
   - Validates account details and performs the transfer if the source account has sufficient balance.

#### 4. **Credit Card Information**
   - Prompts user for card details (card number, expiration date, CVV).
   - Validates the card details and processes the payment.

#### 5. **Loan Management**
   - User can apply for loans on their account.
   - Display the user current pending loans and its details. 

### File Storage

#### `login.txt`
- **Purpose**: Stores login credentials for users.
- **Format**: Each line contains three fields separated by spaces:
  - `name`: Name of the user (string)
  - `acc_no`: Account number (integer)
  - `pass`: Password (string)

#### `balance.txt`
- **Purpose**: Tracks account balances for transactions.
- **Format**: Each line contains three fields separated by spaces:
  - `name`: Name associated with the account (string)
  - `accno`: Account number (integer)
  - `balance`: Current balance in the account (floating point number)

#### `aci.txt`
- **Purpose**: Stores detailed account information.
- **Format**: Each line contains five fields separated by spaces:
  - `name`: Name of the account holder (string)
  - `ac_no`: Account number (integer)
  - `add`: Address of the account holder (string)
  - `phone_no`: Phone number associated with the account (integer)
  - `type`: Type of account (string)

#### `cards.txt`
- **Purpose**: Stores information related to credit/debit cards.
- **Format**: Each line contains five fields separated by spaces:
  - `cardNumber`: Card number (string)
  - `cardHolderName`: Name of the card holder (string)
  - `expiryDate`: Expiry date of the card (string, MM/YY format)
  - `cvv`: CVV number (integer)
  - `balance`: Current balance on the card (floating point number)

#### `loans.txt`
- **Purpose**: Records information about loans.
- **Format**: Each line contains four fields separated by spaces:
  - `customerName`: Name of the customer applying for the loan (string)
  - `loanamount`: Amount of the loan (floating point number)
  - `interestRate`: Interest rate associated with the loan (floating point number)
  - `loanDuration`: Duration of the loan in months (integer)
