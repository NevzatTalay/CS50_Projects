import os

from cs50 import SQL
import datetime
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    indexed = db.execute(
        "SELECT * FROM stocks WHERE user_id = ?;", session["user_id"])
    sum = db.execute(
        "SELECT trans FROM stocks WHERE user_id=?;", session["user_id"])

    bakiye = db.execute(
        "SELECT * FROM users WHERE id = ?", session["user_id"])
    print("aaaaaaaaaaaaaaaaaaaaaaaa")
    print(sum)
    print("aaaaaaaaaaaaaaaaaaaaaaaa")
    if sum == []:
        sum.append({})
        sum[0]["trans"] = 0
    return render_template("index.html", indexed=indexed, sum= sum[0]['trans'] + bakiye[0]['cash'], bakiye=bakiye[0]['cash'])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        stock_info = lookup(symbol)
        if str(stock_info) != "None":
            bakiye = db.execute(
                "SELECT cash FROM users WHERE id = ?", session["user_id"])
            if (float(stock_info['price'])*int(shares)) <= float(bakiye[0]["cash"]):
                bought_before = db.execute(
                    "SELECT * FROM stocks WHERE symbol = ? AND user_id = ?", str(symbol), int(session["user_id"]))
                if bought_before != []:
                    db.execute("UPDATE stocks SET shares =  shares + ? WHERE user_id = ? AND symbol= ?;",
                               int(shares), session["user_id"], str(symbol))
                    db.execute(
                        "UPDATE users SET cash = cash - ? WHERE id = ?", float(stock_info['price'])*int(shares), session["user_id"])
                    db.execute("INSERT INTO history (user_id, symbol, shares, price, type, transacted) VALUES(?, ?, ?, ? ,?, ?);", session["user_id"], str(
                        symbol), int(shares), usd(float(stock_info['price'])), 'BUY', datetime.datetime.now())
                    return redirect("/")
                else:

                    db.execute("INSERT INTO stocks (user_id, symbol, name, shares, price) VALUES(?, ?, ?, ?,?);", session["user_id"], str(
                        symbol), stock_info['name'], int(shares), float(stock_info['price']))
                    db.execute("UPDATE users SET cash = cash - ? WHERE id = ?",
                               float(stock_info['price'])*int(shares), session["user_id"])
                    db.execute("INSERT INTO history (user_id, symbol, shares, price, type, transacted) VALUES(?, ?, ?, ? ,?, ?);", session["user_id"], str(
                        symbol), int(shares), usd(float(stock_info['price'])), 'BUY', datetime.datetime.now())
                    return redirect("/")
            else:
                return apology("NOT ENOUGH CASH", 400)

        else:
            return apology("Invalid Stock Name", 400)
    else:
        return render_template("/buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    personal_hist = db.execute(
        "SELECT * FROM history WHERE user_id = ?;", session["user_id"])
    return render_template("history.html", personal_hist=personal_hist)


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    """Add Cash to your Balance"""
    if request.method == "POST":
        add_cash = request.form.get("add_cash")
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?;",
                   float(add_cash), session["user_id"])
        return apology("YOU MADE IT", 400)
    else:
        return render_template("addcash.html")


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
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

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
        symbol = request.form.get("symbol")
        stock_info = lookup(symbol)
        if str(stock_info) != "None":
            return render_template("/quoted.html", symbol=stock_info["name"], stock_price=usd(stock_info["price"]), stock_symbol=stock_info["symbol"])
        else:
            return apology("Invalid Stock Name", 400)
    else:
        return render_template("/quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Redirect user to home page
        username = request.form.get("username")
        password = request.form.get("password")
        hashed = generate_password_hash(password, method='pbkdf2:sha256')
        cash = 10000
        existence_check = len(db.execute(
            "SELECT * FROM users WHERE EXISTS (SELECT * FROM users WHERE username=?);", username))

        if not request.form.get("username"):
            return apology("must provide username", 400)
        if not request.form.get("password"):
            return apology("must provide password", 400)
        if not request.form.get("confirmation"):
            return apology("must provide confirmation of your password", 400)
        if request.form.get("confirmation") != request.form.get("password"):
            return apology("Passwords do not match", 400)
        if existence_check != 0:
            return apology("already used", 400)
        db.execute(
            "INSERT INTO users (username,hash,cash) VALUES(?, ?, ?)", username, hashed, cash)
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))
        session["user_id"] = rows[0]["id"]
        # Ensure username exists and password is correct
        return redirect("/")
    else:
        return render_template("/register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        stock_info = lookup(symbol)
        inv_check = db.execute("SELECT * FROM stocks WHERE symbol = ? AND user_id = ?",
                               str(symbol), int(session["user_id"]))
        if str(stock_info) != "None" and inv_check != []:
            if int(shares) == int(inv_check[0]['shares']):
                db.execute("DELETE FROM stocks WHERE user_id = ? AND symbol= ?;",
                           session["user_id"], str(symbol))
                return redirect("/")
            elif int(shares) <= int(inv_check[0]['shares']):
                db.execute("UPDATE stocks SET shares =  shares - ?, price = price WHERE user_id = ? AND symbol= ?;",
                           int(shares), session["user_id"], str(symbol))
                db.execute("INSERT INTO history (user_id, symbol, shares, price, type, transacted) VALUES(?, ?, ?, ? ,?, ?);", session["user_id"], str(
                    symbol), int(shares), usd(stock_info['price']), 'SELL', datetime.datetime.now())
                return redirect("/")
            else:
                return apology("DONT ENOUGH STOCK", 400)
        else:
            return apology("INVALID STOCK NAME/OR DONT HAVE ANY", 400)
    else:
        list = db.execute(
            "select symbol from stocks where user_id=?;", session["user_id"])
        return render_template("/sell.html", list=list)
