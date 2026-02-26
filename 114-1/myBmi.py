def computeBMI(weight, height):

    if not (3 <= weight <= 200 and 0.50 <= height <= 2.50):
        return -1
    bmi = weight / (height ** 2)
    return round(bmi, 2)

def printResult(weight, height):
    Bmi = computeBMI(weight, height)
    if Bmi >= 27:
        return 'Obesity'
    elif Bmi >=24:
        return 'Overweight'
    elif Bmi >= 18.5:
        return 'Normal'
    elif Bmi >= 0:
        return 'Underweight'
    else:
        return 'ERROR INPUT'
