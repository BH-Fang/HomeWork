import math

a = int(input())
b = int(input())
c = int(input())

pan = b ** 2 - 4 * a * c

if(pan > 0):
    x1 = (-b + math.sqrt(pan)) / (2 * a)
    x2 = (-b - math.sqrt(pan)) / (2 * a)
    print ('%.1f\n%.1f' %(x1, x2))
elif(pan == 0):
    x1 = (-b + math.sqrt(pan)) / (2 * a)
    print('%.1f' %x1)
else:
    shi = -b / (2 * a)
    xu =  math.sqrt(-pan) / abs(2 * a)
    print('%.1f+%.1fi\n%.1f-%.1fi'%(shi, xu, shi, xu))


