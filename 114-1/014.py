def angleLimit(angle):
    if angle >= 360:
        return angle - 360
    elif angle <= -360:
        return angle + 360
    else:
        return angle

pos = (0, 0)
rotate = 0
pattern = 'no_pattern'
color = 'black'
alstamp = False
for i in range(6):
    cmd = input().split()
    if cmd[0] == 'reset':
        pos = (0, 0)
        rotate = 0
        pattern = 'no_pattern'
        color = 'black'
    elif cmd[0] == 'mv':
        pos = (pos[0] + float(cmd[1]), pos[1] + int(cmd[2]))
    elif cmd[0] == 'rotate':
        rotate = angleLimit(float(cmd[1]) + rotate)
    elif cmd[0] == 'set_pattern':
        pattern = cmd[1]
    elif cmd[0] == 'set_color':
        color = cmd[1] 
    elif cmd[0] == 'stamp':
        alstamp = True
        print('Stamping... [position: ({x:.2f}, {y:.2f}), rotation: {angle:.2f} degrees, pattern: {pattern}, color: {color}]'.format(x = pos[0], y = pos[1], angle = rotate, pattern = pattern, color = color))
if alstamp == False:
    print('Stamping canceled')