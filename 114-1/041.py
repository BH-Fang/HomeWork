import math

def get_rank_percent(sid, data, total_stu):
    sort_data = sorted(data, key = lambda a: (-a[1], a[0]))
    rank = [n[0] for n in sort_data].index(sid) + 1
    for k in range(1, 101):
        limit_count = math.ceil(total_stu * k / 100)
        if limit_count >= rank:
            return k

def input_(M, courses, students):
    for _ in range(M):
            input_split = tuple(input().split())
            course = input_split[:2]
            courses[input_split[:2]] = dict()
            for _ in range(int(input_split[2])):
                input_split1 = input().split()
                student = input_split1[0] 
                score = input_split1[1:]
                if not 'w' in score:
                    score = [int(s) for s in score]
                courses[course][student] = score
                if student not in students:
                    students[student] = dict()
                students[student][course] = score

def get_o11(students):
    o11 = set()
    #(mayor, year, course_year)
    for id, c in students.items():
        for course_id in c:
            o11.add((id[3:6], id[:3], course_id[1][:3]))
    return sorted(list(o11))

def get_o12(o11, o12, students):
    for group in o11:
        total_stu = 0
        data = []
        for sid, c in students.items():
            if group[0] == sid[3:6] and group[1] == sid[:3]:
                total_stu += 1
                courses_count = 0
                withdraw_count = 0
                average_score = 0
                total_credit = 0
                for course_id, score in c.items():
                    if course_id[1][:3] == group[2]:
                        if score == ['w']:
                            withdraw_count += 1
                        elif course_id[0][:3] != '101' and course_id[0][:3] != '201':
                            credit = int(course_id[0][3])
                            average_score += int(score[0]) * credit
                            total_credit += credit
                        else:
                            credit = int(course_id[0][3])
                            average_score += math.ceil(int(score[0]) * 0.7 + int(score[1]) * 0.3) * credit
                            total_credit += credit
                        courses_count += 1
                if total_credit != 0: 
                    average_score //= total_credit
                    data.append([sid, average_score, 0, math.floor((withdraw_count / courses_count) * 100)])
        for i in range(len(data)):
            data[i][2] = get_rank_percent(data[i][0], data, total_stu)
        failed = [d for d in data if d[1] < 60]
        failed.sort(key = lambda a: -a[1])
        o12.append(failed)

def get_o2(courses):
    result = []
    for course_id, stu in courses.items():
        scores = []
        withdraw_count = 0
        for sid, score in stu.items():
            if score == ['w']:
                withdraw_count += 1
            elif course_id[0][:3] != '101' and course_id[0][:3] != '201':
                 scores.append((sid, score[0]))
            else:
                 scores.append((sid, math.ceil(int(score[0]) * 0.7 + int(score[1]) * 0.3)))
        scores.sort(key = lambda a: (-a[1], a[0]))
        stu_count = len(scores)
        average_score = sum([s[1] for s in scores]) // stu_count
        withdraw_rate =  math.floor((withdraw_count / (withdraw_count + stu_count)) * 100)
        over40_count = len([a for a in scores if a[1] > 40])
        result.append(((course_id[0], course_id[1][:3]), (scores[0][1], average_score, scores[stu_count - 1][1], withdraw_rate, over40_count)))
    return sorted(result)

def print_o1(o11, o12):
    for index, item in enumerate(o11):
        print('{0} {1} {2}'.format(item[0], item[1], item[2]))
        if len(o12[index]) >= 3:
            for index1 in range(3):
                item1 = o12[index][index1]
                print('{0} {1} {2}% {3}%'.format(item1[0], item1[1], item1[2], item1[3]))
        else:
            print('Not Enough Student ') 

def print_o2(o2):
    for item in o2:
        print('{0} {1}'.format(item[0][0], item[0][1]))
        print('{0} {1} {2} {3}% {4}'.format(item[1][0],item[1][1],item[1][2],item[1][3],item[1][4],))

def main():
    M = int(input())
    courses = dict() #coures:student:score
    students = dict() #student:coures:score
    input_(M, courses, students)
    
    o11 = get_o11(students)
    o12 = []
    get_o12(o11, o12, students)
    o2 = get_o2(courses)
    
    print_o1(o11, o12)
    print_o2(o2)
                         
main()