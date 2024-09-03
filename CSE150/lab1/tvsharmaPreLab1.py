import subprocess

def name_to_ip(hostname):
    ip = subprocess.check_output(['dig','+noall','+answer',hostname], text = True)
    #split the output of dig into lines
    ip = ip.strip()
    output = ip.splitlines()[0]
    if output:
        out = f"{output}"
        print(out)
        return out
    else:
        print("Unable to resolve the hostname")

def ip_to_binary(out, hostname):
    if out:
        #octets = out.split('.') #[-14:]
        #last_octet = octets[4:7]
        #ip_address = last_octet

        ip_address = subprocess.check_output(['dig', '+short', hostname], text = True)
        ip = [s.replace(".","") for s in ip_address];
        ip_address = " ".join(ip)
        binary = [bin(int(ip_address))[2:].zfill(8) for octet in octets]
        print(binary)
        #b_rep= '.'.join(binary)
        print(f"The equivalent binary is {binary}")

def main():
   # Get host name from user
    hostname = input("what is the host name?")
    address = name_to_ip(hostname)
    if address is not None:
        ip_to_binary(address, hostname)
    else:
        print("Unable to resolve the hostname")

if __name__ == "__main__":
    main()