list1 = open("podaci.txt")
list2 = open("podaciTest.txt")
text1 = list1.read()
text2 = list2.read()

for i in range(len(text1)):
    if text1[i] != text2[i]:
        print(i)
        break

print(len(text1) == len(text2))
# def max(a,n):
#     m = 0
#     for i in range(n):
#         s = 0
#         for j in range(i,n):
#             s = s + a[j]
#             if m < s:
#                 m = s
#     return m
# list = [2,-1,1,3,-4,-6,7,-2,3,-5]
# print(max(list, 10))