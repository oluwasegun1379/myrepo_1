from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def home():
    user_name = "John Doe"
    account_balance = 5000.00
    last_login = "2023-07-03"

    recent_transactions = [
        {"date": "2023-07-02", "description": "Supermarket", "amount": -100.00},
        {"date": "2023-07-01", "description": "Salary Deposit", "amount": 2500.00},
        {"date": "2023-06-30", "description": "Online Shopping", "amount": -200.00},
        {"date": "2023-06-29", "description": "ATM Withdrawal", "amount": -50.00},
    ]

    return render_template('index.html', user_name=user_name, account_balance=account_balance,
                           last_login=last_login, recent_transactions=recent_transactions)

if __name__ == '__main__':
    app.run()
