import os
import sys
import datetime

def is_valid_port(port):
    return 0 < port <= 49151  # Well-known and registered port range

def main():
    # Step 1: Check command line arguments
    if len(sys.argv) != 5 or sys.argv[1] != "-p" or sys.argv[3] != "-d":
        print("Usage: python3 part1.py -p port -d directory")
        sys.exit(1)

    try:
        port = int(sys.argv[2])
    except ValueError:
        print("Invalid port number. Please provide a valid integer.")
        sys.exit(1)

    directory = sys.argv[4]

    if not is_valid_port(port):
        print("Terminating program, port number is not allowed.", file=sys.stderr)
        sys.exit(1)

    if not os.path.exists(directory):
        print("Terminating program, specified root directory does not exist.", file=sys.stderr)
        sys.exit(1)

    # Step 2: Create a simple HTML file
    content = f"Hello World, I am Twisha Sharma 1797219\r\n"

    with open(os.path.join(directory, "helloWorld.html"), "w") as file:
        file.write(content)

    # Step 3: Form an HTTP Response
    file_path = os.path.join(directory, "helloWorld.html")
    content_length = os.path.getsize(file_path)
    last_modified = datetime.datetime.utcfromtimestamp(os.path.getmtime(file_path)).strftime('%a, %d %b %Y %H:%M:%S GMT')

    response_headers = [
        f"HTTP/1.1 200 OK",
        f"Content-Length: {content_length}",
        f"Content-Type: text/html",
        f"Date: {datetime.datetime.utcnow().strftime('%a, %d %b %Y %H:%M:%S GMT')}",
        f"Last-Modified: {last_modified}",
        "\r\n"
    ]

    response = "\r\n".join(response_headers)

    # Step 4: Print HTTP response message to stdout
    with open(file_path, "rb") as file:
        file_content = file.read()

    sys.stdout.buffer.write(response.encode() + file_content)

if __name__ == "__main__":
    main()