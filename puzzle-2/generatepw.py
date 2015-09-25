from random import randint
for i in range(100):
    pw = ""
    for j in range(20):
        pw += chr(randint(40,100))
    print(pw)
