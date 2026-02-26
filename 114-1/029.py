
def awf(texts, i, n, word):
    sl = texts[i].split()
    sl.insert(n, word)
    new = ''
    for w in sl:
        new += w + ' '
    new = new[:-1]
    texts[i] = new
    
def awa(texts, i, n, word):
    sl = texts[i].split()
    sl.insert(n + 1 , word)
    new = ''
    for w in sl:
        new += w + ' '
    new = new[:-1]
    texts[i] = new
    
def asf(texts, i, sentance):
    texts[i] = sentance + ' ' + texts[i]
    
def asa(texts, i, sentance):
    texts[i] = texts[i] + ' ' + sentance 
    
def _if(texts, key, word):
    for i in range(len(texts)):
        texts[i] = texts[i].replace(key, word + ' ' + key)
        
def ia(texts, key, word):
    for i in range(len(texts)):
        texts[i] = texts[i].replace(key, key + ' ' + word)
        
def dw(texts, i, n):
    sl = texts[i].split()
    del sl[n]
    new = ''
    for w in sl:
        new += w + ' '
    new = new[:-1]  
    texts[i] = new
    
def dl(texts, i):
    del texts[i]
    
def rp(texts, old, new):
    for i in range(len(texts)):
        texts[i] = texts[i].replace(old, new)

def c(texts):
    count = 0
    for line in texts:
        count += len(line.split())
    print(count)

def runCmd(cmds, texts):
    for cmd in cmds:
        cs = cmd.split()
        if cs[0] == 'awf':
            awf(texts, int(cs[1]) - 1, int(cs[2]) - 1, cs[3])
        elif cs[0] == 'awa':
            awa(texts, int(cs[1]) - 1, int(cs[2]) - 1, cs[3])
        elif cs[0] == 'asf':
            asf(texts, int(cs[1]) - 1, cmd[cmd.find(' ', cmd.find(' ') + 1) + 1:])
        elif cs[0] == 'asa':
            asa(texts, int(cs[1]) - 1, cmd[cmd.find(' ', cmd.find(' ') + 1) + 1:])
        elif cs[0] == 'if':
            _if(texts, cs[1], cs[2])
        elif cs[0] == 'ia':
            ia(texts, cs[1], cs[2])
        elif cs[0] == 'dw':
            dw(texts, int(cs[1]) - 1, int(cs[2]) - 1)
        elif cs[0] == 'dl':
            dl(texts, int(cs[1]) - 1)
        elif cs[0] == 'rp':
            rp(texts, cs[1], cs[2])
        elif cs[0] == 'c':
            c(texts)
           
def pTexts(texts):
    for line in texts:
        print(line)
    
def main():
    In = input().split()
    cmds = []
    M, N = int(In[0]), int(In[1])
    texts = []
    for i in range(M):
        texts.append(input())
    for i in range(N):
        cmds.append(input())
    runCmd(cmds, texts)
    pTexts(texts)
    
       
main()