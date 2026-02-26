
def afterDay(data, d, people, rehabilitation, infectDevideRehabilitation, confirmed_num_list): #data: (confirmedPeople, immunity)
    confirmedPeople = data[0]
    immunity = data[1]
    if d == 0:
        confirmed_num_list.append(confirmedPeople)
        print('{0} {1} {2} {3}'.format(d + 1, confirmedPeople, confirmedPeople, 0))
        return (confirmedPeople ,immunity)
    
    x = infectDevideRehabilitation * (1 - immunity)
    y = int(confirmedPeople * x)
    top = int(people * (1 - immunity) - confirmedPeople)
    if y > top:
        y = top
    confirmed_num_list.append(y)
    
    if d >= rehabilitation:
        confirmedPeople -= confirmed_num_list[d - rehabilitation]
        print('{0} {1} {2} {3}'.format(d + 1, confirmedPeople + y, y, confirmed_num_list[d - rehabilitation]))
        immunity = (people * immunity + confirmed_num_list[d - rehabilitation]) / people 
        return (confirmedPeople + y, immunity)
        
    print('{0} {1} {2} {3}'.format(d + 1, data[0] + y, y, 0))
        
    return (confirmedPeople + y, immunity)

def main():
    people = int(input())
    day = int(input())
    first_confirmed = int(input())
    infect = float(input())
    rehabilitation = int(input())
    immunity = float(input())
    confirmed_num_list = []
    infectDevideRehabilitation = infect / rehabilitation
    count = 0
    
    data = (first_confirmed, immunity)
    for d in range(day):
        data = afterDay(data, d, people, rehabilitation, infectDevideRehabilitation, confirmed_num_list)
    for i in confirmed_num_list:
        count += i
    print(count)

main()

