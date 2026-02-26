def haveZeroLead(combimation):
    for item in combimation:
        if len(item) > 1 and item[0] == '0':
            return True
    return False

def opsCreater(lenOfNumList, current = [], result = []):
    if lenOfNumList == 0:
        result.append(current[:])
        return result
    ops = ['+', '-', '*']
    for op in ops:
        current.append(op)
        opsCreater(lenOfNumList - 1, current, result)
        current.pop()
    return result
           

def calc(op, nums):
    nums = [int(num) for num in nums]
    while '*' in op:
        index = op.index('*')
        nums[index] = nums[index] * nums[index + 1]
        del nums[index + 1]
        del op[index]
    while '-' in op:
        index = op.index('-')
        nums[index + 1] *= -1
        op[index] = '+'
    return sum(nums)

def main():
    numStr = input()
    target = int(input())
    
    ans = [0]
    current = []
    def dfs(index):
        if index == len(numStr) and not haveZeroLead(current):
            op = opsCreater(len(current) - 1)
            for o in op:
                if calc(o, current) == target:
                    ans[0] += 1
            return
        for i in range(index + 1, len(numStr) + 1):
            current.append(numStr[index:i])
            dfs(i)
            current.pop()
    dfs(0)
    
    print(ans[0])            
    
main()