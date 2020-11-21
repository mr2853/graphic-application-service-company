list1 = open("podaci.txt")
list2 = open("podaciTest.txt")
text1 = list1.read()
text2 = list2.read()

for i in range(len(text1)):
    if text1[i] != text2[i]:
        print(i)
        break

print(len(text1) == len(text2))