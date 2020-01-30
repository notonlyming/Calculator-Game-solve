# solveLevels.py
# 用于传入指定的配置文件，生成所有关卡的解到一个文件中。

import sys
import os

if __name__ == '__main__':
    path = sys.argv[1]
    with open(path, mode='r', encoding='utf-8') as f:
        levels = eval(f.read())
    
    outputFilePath = path.replace('.py', '.md')
    # 打开以清空或创建文件
    with open(outputFilePath, mode='w', encoding='utf-8') as f:
        pass

    inputFilePath = path.replace('.py', '.input')
    for level in levels:
        with open(outputFilePath, mode='a', encoding='utf-8') as f:
            f.write('### ' + level['name'] + '\n')
        print(level["name"])
        # 要构造的输入数据
        levelInfoInput = '{}\n{}\n{}\n{}\n{}\nn\n'.format(
            level['achieve'], level['start'], level["max_step"], level["buttons"], level["protal"])
        with open(inputFilePath, mode='w', encoding='utf-8') as f:
            f.write(levelInfoInput)
        
        # 调用一次程序解算
        # print("cat {} | ./calculator_game --silent >> {}".format(inputFilePath, outputFilePath))
        os.system("cat {} | ./calculator_game --silent >> {}".format(inputFilePath, outputFilePath))
        