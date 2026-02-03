from flask import Flask, render_template, request, redirect
from cs50 import SQL

app = Flask(__name__)
db = SQL("sqlite:///expenses.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        title = request.form.get("title")
        amount = request.form.get("amount")

        if not title or not amount:
            return redirect("/")

        db.execute(
            "INSERT INTO expenses (title, amount) VALUES (?, ?)",
            title,
            amount
        )
        return redirect("/")

    expenses = db.execute("SELECT * FROM expenses")
    total = db.execute("SELECT SUM(amount) AS total FROM expenses")[0]["total"]

    return render_template("index.html", expenses=expenses, total=total)
