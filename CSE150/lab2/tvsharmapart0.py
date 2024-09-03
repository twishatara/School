import sys

def is_valid_port(port):
    # return if port is well known and within the registered port range
    return 0 < port < 49151

def main():
    if len(sys.argv) != 5 or sys.argv[1] != "-p" or sys.argv[3] != "-d":
        print("Usage: python3 part0.py -p port -d directory")
        sys.exit(1)
    try:
        port = int(sys.argv[2])
    except ValueError:
        print("Invlid port number. Please provide a valid integer.")
        sys.exit(1)
    directory = sys.argv[4]
    if not is_valid_port(port):
        print("Terminating program, port number is not allowed.", file=sys.stderr)
        sys.exit(1)

    # if http
    if port == 80:
        print(f"{port} {directory}")
    elif 0 < port <= 1023:
        print(f"Well-known port number {port} entered - could cause a conflict.")
        print(f"{port} {directory}")
    else:
        print(f"Registered port number {port} entered - could cause a conflict.")
        print(f"{port} {directory}")

if __name__ == "__main__":
    main()