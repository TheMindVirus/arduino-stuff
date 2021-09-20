banks = "ABCDEFGHJKLMNPRT"
ports = 16
data = ""
i = 0
for bank in banks:
    for port in range(1, ports + 1):
        label = "CYC_" + bank + str(port)
        line = "#define " + label + (" " * (10 - len(label))) + str(i)
        data += line + "\n"
        print(line)
        i += 1
    data += "\n"
    print()

file = open("VidorCYC.h", "w")
file.write(data)
file.close()
