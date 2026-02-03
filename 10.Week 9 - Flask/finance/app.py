from cs50 import SQL
from flask import Flask, render_template, request, redirect, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)

# Configure session
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/buy", methods=["GET", "POST"])
def buy():
    return render_template("buy.html")

@app.route("/sell", methods=["GET", "POST"])
def sell():
    return render_template("sell.html")

@app.route("/history")
def history():
    return render_template("history.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    return render_template("login.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    return render_template("register.html")

@app.route("/quote", methods=["GET", "POST"])
def quote():
    return render_template("quote.html")
