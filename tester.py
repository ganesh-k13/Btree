import subprocess
from random import randint
import matplotlib.pyplot as plt
from itertools import accumulate
import re

testcases = 20

t_values = [2**i for i in range(2, 10)] 
    

def build_tree(t, records_num):
    print("\nCompiling for T="+str(t)+"....")
    p = subprocess.Popen(['make','clean'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    p = subprocess.Popen(['make','T='+str(t)], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    out, err = p.communicate()

    print("Compiling done....")
    print("\nBuilding tree....")
    p = subprocess.Popen(['./test', '-b', str(records_num)], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    out, err = p.communicate()
    print(out)
    return float((re.findall("\d+\.\d+", str(out)))[0])

def test_search(key):
    
    p = subprocess.Popen(['./test', '-s', str(key)], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    out, err = p.communicate()
    
    time = float((re.findall("\d+\.\d+", str(out)))[0])
    
    print(time)

    return(time)
    
    
if __name__ == "__main__":
    records_num = 100000
    build_times = list()
    avg_times = list()
    search_items = [randint(1, 10000000) for i in range(10)]
    for i in t_values:
        build_times.append(build_tree(i, records_num))
        search_times = list()
        for s in search_items:
            search_times.append(test_search(s))
        avg_times.append(sum(search_times)/len(search_times))

    print(t_values, build_times)
    plt.xlabel('T Values')
    plt.ylabel('Time in ms')
    plt.title('Tree Building')
    plt.plot(t_values, build_times)
    plt.show()
    plt.clf()

    plt.xlabel('T Values')
    plt.ylabel('Time in ms')
    plt.title('Tree Search For 10 Random Keys(Avg)')
    plt.plot(t_values, avg_times)
    plt.show()
    plt.clf()

    # print(build_times)
    

# def test_insert(factor):
#     p = subprocess.Popen(['./test', '-i', '100', str(factor)], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
#     out, err = p.communicate()

#     times = list(map(float, out.split()))

#     print('Maximium: ' + str(max(times)))

#     plt.plot(range(len(times)), list(accumulate(times)), label=str(factor))
    
    
# def test_delete(factor):
#     p = subprocess.Popen(['./test', '-d', '100', str(factor)], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
#     out, err = p.communicate()

#     times = list(map(float, out.split()))

#     print('Maximium: ' + str(max(times)))
    
#     plt.plot(range(len(times)), list(accumulate(times)), label=str(factor))
    
# def test_ratio(factor, t1, t2):
#     p = subprocess.Popen(['./test', '-r', '100', str(factor), str(t1), str(t2)], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
#     out, err = p.communicate()

#     times = list(map(float, out.split()))

#     print('Maximium: ' + str(max(times)))
    
#     plt.plot(range(len(times)), list(accumulate(times)), label=str(factor))

# if __name__ == "__main__":
    

#     plt.xlabel('Current Size')
#     plt.ylabel('Time')
#     plt.title('Insert')
    
#     print("INSERT")
#     for f in factors:
#         test_insert(f)
    
#     plt.legend(loc="upper left")
#     plt.show()
#     plt.clf()

#     plt.xlabel('Current Size')
#     plt.ylabel('Time')
#     plt.title('Delete')
    
#     print("DELETE")
#     for f in factors:
#         test_delete(f)
    
#     plt.legend(loc="upper left")
#     plt.show()
#     plt.clf()

#     plt.xlabel('Operation Number')
#     plt.ylabel('Time')
#     plt.title('RATIO 4:3')
    
#     print("RATIO 4:3")
#     for f in factors:
#         test_ratio(f, 4000000, 3000000);
#     plt.legend(loc="upper left")
#     plt.show()
#     plt.clf()
    
#     plt.xlabel('Operation Number')
#     plt.ylabel('Time')
#     plt.title('RATIO 4:2')
    
#     print("RATIO 4:2")
#     for f in factors:
#         test_ratio(f, 4000000, 2000000);
#     plt.legend(loc="upper left")
#     plt.show()
#     plt.clf()
