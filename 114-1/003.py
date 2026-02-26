
name, id, ch, cs, pr = input(), int(input()), int(input()), int(input()), int(input())
total = ch + cs + pr
aver = total // 3

Out = 'Name:{Name}\nId:{Id}\nTotal:{Total}\nAverage:{Average}'.format(Name = name,Id = id,Total = total,Average = aver)
print(Out)