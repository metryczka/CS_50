import os
from datetime import datetime


from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    current = db.execute("SELECT * FROM current WHERE user_id == ?", session["user_id"])
    for row in current:
        data = lookup(row["stocks"])
        row["price"] = data["price"]
        row["total"] = data["price"]*row["amount"]

    cash = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])
    summing = cash[0]["cash"]
    for row in current:
        summing += row["total"]

    return render_template("index.html", total=summing, current=current, cash=cash[0]["cash"])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        data = lookup(request.form.get("symbol"))
        stocks = request.form.get("shares")
        if data == None:
            return apology("invalid symbol")
        elif stocks == None:
            return apology("invalid amount")
        elif stocks.isnumeric() == False:
            return apology("you need to give number")
        elif int(stocks) < 0:
            return apology("Amount must be positive")

        else:
            now = datetime.now()
            stocks = lookup(request.form.get("symbol"))
            cash = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])
            amount = int(request.form.get("shares"))

            if cash[0]["cash"] < stocks["price"]*amount:
                return apology("you don't have enough money")
            else:
                cash_update = cash[0]["cash"] - stocks["price"]*amount
                db.execute("UPDATE users SET cash = ? WHERE id == ?", cash_update, session["user_id"])
                db.execute("INSERT INTO history (user_id, stocks, amount, price, time) VALUES(?, ?, ?, ?, ?)",
                           session["user_id"], stocks["symbol"], amount, stocks["price"], now)
                current_stocks = db.execute("SELECT * FROM current WHERE user_id == ? AND stocks ==?",
                                            session["user_id"], stocks["symbol"])
                if len(current_stocks) == 0:
                    db.execute("INSERT INTO current (user_id, stocks, amount, name) VALUES(?, ?, ?, ?)",
                               session["user_id"], stocks["symbol"], amount, stocks["name"])
                elif len(current_stocks) == 1:
                    current_amount = current_stocks[0]["amount"] + amount
                    db.execute("UPDATE current SET amount = ? WHERE user_id == ? AND stocks== ?",
                               current_amount, session["user_id"], stocks["symbol"])
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM history WHERE user_id == ?", session["user_id"])
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        data = lookup(request.form.get("symbol"))
        if data == None:
            return apology("invalid symbol")
        else:
            return render_template("quoted.html", name=data["name"], price=data["price"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("confirm your password", 400)
        # Query database for username
        users = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(users) != 0 or request.form.get("password") != request.form.get("confirmation"):
            return apology("invalid username and/or password", 400)

        hashed = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=16)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), hashed)

        user = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        print(user[0]["id"])
        # Remember which user has logged in
        session["user_id"] = user[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    current = db.execute("SELECT * FROM current WHERE user_id == ?", session["user_id"])
    if request.method == "POST":
        now = datetime.now()
        stock = db.execute("SELECT * FROM current WHERE user_id ==? AND stocks == ?",
                           session["user_id"], request.form.get("symbol"))
        if len(stock) == 0:
            return apology("You don't have this stocks")
        elif stock[0]["amount"] < int(request.form.get("shares")):
            return apology("You don't have that much stocks")
        else:
            cash = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])
            current_amount = stock[0]["amount"]-int(request.form.get("shares"))
            stocks = lookup(request.form.get("symbol"))
            cash_update = cash[0]["cash"] + stocks["price"]*int(request.form.get("shares"))
            db.execute("UPDATE current SET amount = ? WHERE user_id ==? AND stocks == ? ",
                       current_amount, session["user_id"], request.form.get("symbol"))
            db.execute("UPDATE users SET cash = ? WHERE id == ?", cash_update, session["user_id"])
            db.execute("INSERT INTO history (user_id, stocks, amount, price, time) VALUES(?, ?, ?, ?, ?)",
                       session["user_id"], stocks["symbol"], -int(request.form.get("shares")), stocks["price"], now)

            return redirect("/")
    else:
        return render_template("sell.html", current=current)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
