h, w = float(input()), int(input())
BMI = w / h ** 2
if BMI < 18:
    print('Underweight')
elif BMI < 24:
    print('Normal')
elif BMI < 27:
    print('Overweight')
elif BMI < 30:
    print('Mild obesity')
elif BMI < 35:
    print('Moderate obesity')
else:
    print('Severe obesity')