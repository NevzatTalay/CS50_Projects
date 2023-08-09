from cs50 import get_int
# This is the first code.
while True:
    try:
        s = get_int("Height: ")
        if s > 0 and s < 9:
            break
    except ValueError:  # This is the error return
        print("Invalid integer. The number must be in the range of 1-8.")
for i in range(1, s+1, 1):
    # Kolayca tek donguyle isi biirdim. I am suuupeerrrrr
    print(" " * (s-i) + "#" * i)
