
import ipaddress

address = input("enter ip address: ")

try:
    ip = ipaddress.ip_address(address)
    print("Valid IP:", ip)
    print("version:", ip.version)

    if ip.version == 4:
        first = int(address.split('.')[0])

        if 1 <= first <= 126:
            prefix = 8
            cls = "A"
        elif 128 <= first <= 191:
            prefix = 16
            cls = "B"
        elif 192 <= first <= 223:
            prefix = 24
            cls = "C"
        elif 224 <= first <= 239:
            prefix = None
            cls = "D (Multicast)"
        else:
            prefix = None
            cls = "E (Experimental)"

        print("class:", cls)

        if prefix is not None:
            net = address + "/" + str(prefix)
            print(net)

            net = ipaddress.ip_network(net, strict=False)

            print("Default Mask:", net.netmask)
            print("Network Address:", net.network_address)
            print("Starting IP:", net.network_address + 1)
            print("Ending IP:", net.broadcast_address - 1)
            print("Broadcast Address:", net.broadcast_address)
            print("Number of Hosts:", net.num_addresses - 2)

except ValueError:
    print("Invalid IP Address")



