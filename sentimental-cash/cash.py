from cs50 import get_float
# This is the first code.
while True:
    try:
        s = get_float("Change owed: ")
        if s > 0:
            break
    except ValueError:  # This is the error return
        print("Problem Detected")
bozukluk = ["0.25", "0.1", "0.05", "0.01"]
residual = s
coin_amount = 0.0
for item in bozukluk:
    coin_amount = coin_amount + int(residual/float(item))
    residual = round(residual % float(item), 2)
print(coin_amount)