import socket
import os
import sys
import mimetypes
import argparse
from datetime import datetime

# Function that checks if a given port is within the valid range of well-known and registered ports (1-49151)
def is_valid_port(port):
    # Range of well known and registered port numbers
    return 0 < port <= 49151

# Function that determines the content type based on the file extension. It maps file extension to MIME types
def get_content_type(file_path):
    # Separate file path into root and extension part
    file_extension = get_file_extension(file_path)
    # Dictionary that maps file extensions to their corresponding MIME types
    # Each key-val pair represents a file extension and its associated MIME type
    extension_to_type = {
        ".html": "text/html",
        ".txt": "text/plain",
        ".csv": "text/csv",
        ".png": "image/png",
        ".jpg": "image/jpeg",
        ".gif": "image/gif",
        ".zip": "application/zip",
        ".doc": "application/msword",
        ".docx": "application/vnd.openxmlformats-officedocument.wordprocessingml.document"
    }
    # If file extension not found in dictionary, default to generic binary file type - "application/octet-stream"
    return extension_to_type.get(file_extension, "application/octet-stream")

# Function that handles the clients HTTP request. It reads the request, parses it, and sends back the appropriate HTTP response
def handle_client_request(connection_socket, root_directory):
    # Step 1: Receive HTTP request from the client decoding it from bytes to a string
    # Recieve data over the socket, maximum number of bytes to be received at once - 1024
    # Decode the data into a string - converts the bytes to a string 
    request_data = connection_socket.recv(1024).decode()
    if not request_data:
        return
    # Step 2: Parse the HTTP request
    # Split the request data into lines, at every new line
    # "request_lines" is a list where each element is a line in the HTTP request
    request_lines = request_data.split("\r\n")
    # Extract the first line from the list of request lines 
    # "request_line" contains the request method, URL, and HTTP version
    request_line = request_lines[0].split()
    # Check if it's a valid GET request
    if len(request_line) != 3 or request_line[0] != "GET":
        # If not, send the 501 Not Implemented response.
        send_http_response(connection_socket, 501, "Not Implemented")
        return
    # Extract the requested path from the request line.
    requested_path = request_line[1]
    # Construct the file path by appending that path to the root directory
    # Remove the leading '/'
    file_path = os.path.join(root_directory, requested_path[1:])
    # Step 3: Check if the requested file exists
    if not os.path.exists(file_path):
        # If not, send 404 Not Found response
        send_http_response(connection_socket, 404, "Not Found")
        return
    # Step 4: Form an HTTP Response
    # Calculate the content length - "getsize" returns the size of the file in an int
    content_length = os.path.getsize(file_path)
    # Calculate the last modified timestamp - "datetime.utcfromtimestamp" converts the timestamp from "gettime" into an object representing the date and time of the last modification
    last_modified = datetime.utcfromtimestamp(os.path.getmtime(file_path)).strftime('%a, %d %b %Y %H:%M:%S GMT')
    # Construct the complete HTTP response (headers + body)
    response_headers = [
        "HTTP/1.1 200 OK",
        "Content-Length: {}".format(content_length),
        "Content-Type: {}".format(mimetypes.guess_type(file_path)[0]),
        "Date: {}".format(datetime.utcnow().strftime('%a, %d %b %Y %H:%M:%S GMT')),
        "Last-Modified: {}".format(last_modified),
        "Connection: close",
        "\r\n"
    ]
    # Join the response list together so it can be sent
    response = "\r\n".join(response_headers)
    # Step 5: Send the HTTP Response to the client
    # Open the file in read binary mode
    with open(file_path, "rb") as file:
        # Read the contents of the file and store it into a variable
        file_content = file.read()
    # Convert the string into bytes using encode
    # Send the HTTP response headers to the client
    connection_socket.send(response.encode())
    # Send the file contents to the client
    connection_socket.send(file_content)

# Function that extracts and formats the file extension from a given file path
def get_file_extension(file_path):
    # Use os path basename to get the filename (discard the directory path)
    filename = os.path.basename(file_path)
    # Use os path splitext to split the filename into root and extension
    file_root, file_extension = os.path.splitext(filename)
    # Remove the leading dot from the extension
    return file_extension.lstrip(".").lower()

# Function that determines the content type based on the file extension. It maps the file extension to MIME types
def send_http_response(connection_socket, status_code, status_phrase):
    response = "HTTP/1.1 {} {}\r\nConnection: close\r\n\r\n".format(status_code, status_phrase)
    connection_socket.send(response.encode())

def main():
    # Step 1: Parse command line arguments using argparse
    parser = argparse.ArgumentParser(description='Simple HTTP Server')
    parser.add_argument('-p', '--port', type=int, help='Port number for the server', required=True)
    parser.add_argument('-d', '--directory', type=str, help='Root directory for serving files', required=True)
    args = parser.parse_args()

    # Step 2: Check if the provided port is within the valid range
    if not is_valid_port(args.port):
        print("Terminating program, port number is not allowed.", file=sys.stderr)
        sys.exit(1)

    # Check if the specified root directory exists
    if not os.path.exists(args.directory):
        print("Terminating program, specified root directory does not exist.", file=sys.stderr)
        sys.exit(1)

    # Step 3: Create a welcome socket
    # Using IPv4 and TCP, a welcome socket is made, and bound to the specified IP address and port, and is ready to listen for incoming connections
    host_ip = socket.gethostbyname(socket.gethostname())
    # Create and set the socket to the correct parameters
    welcome_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    welcome_socket.bind((host_ip, args.port))
    welcome_socket.listen(1)
    print("Welcome socket created: {}, {}".format(host_ip, args.port))

    # Step 4: Accept incoming connections
    running = True
    try:
        while running:
            # Continuously accept incoming connections
            connection_socket, client_address = welcome_socket.accept()
            # Print a message when a connection is established
            print("Connection socket created: {}, {}".format(client_address[0], client_address[1]))
            # Step 5: Handle the client's request
            # Call handle client request function to process the clients HTTP request
            handle_client_request(connection_socket, args.directory)
            # Step 6: Close the connection socket
            connection_socket.close()
            # Print a message when the connection is closed
            print("Connection to {}, {} is now closed.".format(client_address[0], client_address[1]))
    except KeyboardInterrupt:
        # Ctrl+C encountered
        print(" Server terminated by user.")
        running = False
    finally:
        # Close the welcome socket
        welcome_socket.close()

if __name__ == "__main__":
    main()

