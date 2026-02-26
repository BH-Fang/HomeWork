import coverage
import unittest

cov = coverage.Coverage(branch=True, source=['myBmi'])
cov.start() #啟動測試涵蓋度紀錄
suite = unittest.defaultTestLoader.discover("./", "myBmiTest.py") # 載入測試套件
unittest.TextTestRunner().run(suite) #執行測試套件組之測試
cov.stop() #停止測試涵蓋度紀錄
cov.save() #儲存測試涵蓋度資料
cov.report() # 命令列模式展示結果
cov.html_report(directory='cov') #製作測試涵蓋度結果報表,存放在cov子目錄