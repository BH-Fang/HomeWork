
def getSearch(input):
    input = input.split('+')
    result = []
    for s in input:
        result.append(set(s.split()))
    return result

def main():
    n = int(input())
    schools = []
    tags = []
    for i in range(n): 
        tmp = input().split()
        schools.append(tmp[0])
        tags.append(set(tmp[1:]))
    m = int(input())
    searchs = []
    for i in range(m): 
        searchs.append(getSearch(input()))
    b = int(input())

    ans = []
    if not b:
        for search in searchs:
            scores = [0] * n
            for item in search:
                for index, tag in enumerate(tags):
                    if item <= tag:
                        scores[index] += 1
            maxValue = max(scores)
            ans.append([schools[i] for i in range(n) if scores[i] == maxValue])
    else:   
        for search in searchs:
            scores = [0] * n
            search_set = set()
            for s in search:
                search_set.update(s)
            for index, tag in enumerate(tags):
                scores[index] = len(tag & search_set)
            tmp = []
            for i in range(n):
                if scores[i] == 0:
                    continue
                tmp.append((scores[i], i, schools[i]))
            tmp.sort(key = lambda x: (-x[0], x[1]))
            ans.append([t[2] for t in tmp])
            
    for a in ans:
        print(' '.join(a))

main()