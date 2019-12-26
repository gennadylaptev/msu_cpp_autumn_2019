import subprocess
import os

def test1():
    print("# Crash test 1")
    file_to_del = "part_3.bin"
    p = subprocess.Popen(["valgrind", "--leak-check=full", "./main"])

    while (True):
        if file_to_del in os.listdir():
            print(f'# Crash test 1: Removing {file_to_del}')
            os.remove(file_to_del)
            p.wait()        
            break

        elif p.poll() is not None:
            print('# Crash test 1 is over')
            break
            
def test2():
    print("# Crash test 2")
    file_to_del = "part_12.bin"
    p = subprocess.Popen(["valgrind", "--leak-check=full", "./main"])

    while (True):
        if file_to_del in os.listdir():
            print(f'# Crash test 2: Removing {file_to_del}')
            os.remove(file_to_del)
            p.wait()        
            break

        elif p.poll() is not None:
            print('# Crash test 2 is over')
            break

test1()
test2()
