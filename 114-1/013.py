def isLeep(year):
    return (year % 4 == 0 and year % 100 != 0) or year % 400 == 0

years = [int(input()), int(input())]
for year in years:
    if isLeep(year):
        print('Leap Year')
    else:
        print('Common Year')

