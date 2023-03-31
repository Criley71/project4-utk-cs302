import random
import subprocess
import sys

if len(sys.argv) < 2:
    print("Usage: python generate_map.py <n>")
    sys.exit(1)

n = int(sys.argv[1])


outputFile = "generateMapBenchmarks.txt"
with open(outputFile, "a+") as f:
    pass

with open(outputFile, "w") as f: #this opens and makes a file
    f.write('6 \n')
    f.write('f 3\n')
    f.write('g 1\n')
    f.write('G 2\n')
    f.write('h 4\n')
    f.write('m 7\n')
    f.write('r 5\n')

    list = ['g', 'G', 'h', 'm', 'r']
    end = n - 1
    f.write(str(n) + ' ' + str(n) + '\n')

    for i in range(n):
        for j in range(n):
            f.write(random.choice(list))
            f.write(' ')
        f.write('\n')
    f.write('0 0\n')
    f.write(str(end) + ' ' +  str(end))

cpp = "./dijkstras"
process = subprocess.Popen(["src/dijkstras"], stdin=subprocess.PIPE)
with open("generateMapBenchmarks.txt", "r") as f:
    process.communicate(input=f.read().encode())

# Wait for the process to finish and check the return code
return_code = process.wait()
if return_code != 0:
    print("Error: The C++ program returned a non-zero exit code.")
##output = subprocess.run([cpp, outputFile], capture_output=True, text=True)

##with open (outputFile, "a") as f:
 ##   f.write("\n" + output.stdout)
 