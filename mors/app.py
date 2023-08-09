from cs50 import SQL
from flask import Flask, render_template, request, redirect, send_file
import io
import pyqrcode
import qrcode
import sys
from PIL import Image
app = Flask(__name__)

db = SQL("sqlite:///kanban.db")
app.config["UPLOAD_FOLDER"] = "static/Kanbans/"


@app.route('/', methods=["GET", "POST"])
def index():
    return render_template("index.html")


@app.route('/see', methods=["GET", "POST"])
def see():
    data = db.execute("SELECT * FROM machList;")
    if request.method == "POST":
        username = request.form.get("username")
        print("Merhaba:" + username)
        return redirect("/show?machid=" + username)
    else:
        return render_template("machList.html", tableA=data)


@app.route('/qr3', methods=["GET", "POST"])
def qr3():
    if request.method == "POST":
        link2 = request.form.get("qr")
        url = pyqrcode.QRCode(link2, error='H')
        url.png('/workspaces/10831367/mors/static/test.png', scale=10)
        im = Image.open('/workspaces/10831367/mors/static/test.png')
        h, w = im.size
        im = im.convert("RGBA")
        logo = Image.open('/workspaces/10831367/mors/static/stellantis-tr.png')
        logo = logo.resize((int(h/3), int(h/3)))
        hl, wl = logo.size
        im.paste(logo, (int((h-hl)/2), int((w-wl)/2)), logo.convert('RGBA'))
        im.save("/workspaces/10831367/mors/static/imagelist/defaultcode.png")
        return render_template("qrcode.html", text="../static/imagelist/defaultcode.png")
    else:
        return render_template("qrcode.html")


@app.route('/newmachine', methods=["GET", "POST"])
def newmachine():
    if request.method == "POST":
        location = request.form.get("location")
        brand = request.form.get("brand")
        product_function = request.form.get("product_function")
        Status = request.form.get("Status")
        brand = request.form.get("brand")
        product_name = request.form.get("product_name")

        add_newmachine = db.execute("INSERT INTO machList (LOCATION, BRAND, FUNCTION, STATUS, PRODUCTNAME) VALUES (?,?,?,?,?);",
                                    location, brand, product_function, Status, product_name)
        add_machinestatus = db.execute(
            "INSERT INTO kex (K1, K2, K3, K4, K5) VALUES (?,?,?,?,?);", 0, 0, 0, 0, 0)
        return render_template("newmachine.html")
    else:
        return render_template("newmachine.html")


@app.route("/show", methods=["GET", "POST"])
def show():
    if request.method == "GET":
        machid = request.args.get("machid")
        indexed = db.execute("SELECT * FROM kex WHERE MACH_ID = ?;", machid)
        # DICTIONARY INDEXING FOR TICK AND X SYMBOL
        k_name = ["K1", "K2", "K3", "K4", "K5"]
        for x in k_name:
            if indexed[0][x] == 0:
                indexed[0][x] = "remove.png"
            else:
                indexed[0][x] = "accept.png"
        return render_template("show.html", k1=indexed[0]["K1"], k2=indexed[0]["K2"], k3=indexed[0]["K3"], k4=indexed[0]["K4"], k5=indexed[0]["K5"])
    else:
        machid = request.args.get("machid")
        orderkanban = request.form.get("orderkanban")
        orderkanban = machid + "_" + orderkanban
        return render_template("seekanban.html", orderkanban=orderkanban)


@app.route('/uploadkanban', methods=["GET", "POST"])
def uploadkanban():
    if request.method == "POST":
        machine_id2 = request.form.get("machine_id2")
        file_type2 = request.form.get("file_type2")
        print("Form No: "+file_type2[1])
        if int(file_type2[1]) == 1:
            #update_machinestatus = db.execute(
                #"INSERT INTO kex (K1) VALUES (?);", 1)
            update_machinestatus = db.execute("UPDATE kex SET K1 = 1 WHERE MACH_ID = ?;",int(machine_id2))
        elif int(file_type2[1]) == 2:
            update_machinestatus = db.execute("UPDATE kex SET K2 = 1 WHERE MACH_ID = ?;",int(machine_id2))
        elif int(file_type2[1]) == 3:
            update_machinestatus = db.execute("UPDATE kex SET K3 = 1 WHERE MACH_ID = ?;",int(machine_id2))
        elif int(file_type2[1]) == 4:
            update_machinestatus = db.execute("UPDATE kex SET K4 = 1 WHERE MACH_ID = ?;",int(machine_id2))
        elif int(file_type2[1]) == 5:
            update_machinestatus = db.execute("UPDATE kex SET K5 = 1 WHERE MACH_ID = ?;",int(machine_id2))

        f = request.files['files']
        f.save(app.config['UPLOAD_FOLDER'] +
               machine_id2 + "_" + file_type2 + ".pdf")
        return render_template("uploadkanban.html")
    else:
        return render_template("uploadkanban.html")
