## Final Project - Proxy Server 

## Short Description
        This proxy server is an advanced HTTP/HTTPS server implemented in C, designed to efficiently manage and process HTTP GET and HEAD requests over both unsecured and secured connections. It supports concurrent handling of multiple client requests through multithreading, ensuring high responsiveness and scalability. Upon receiving a request, the server parses it to extract the destination URL, checks against a list of forbidden sites, and if allowed, forwards the request to the corresponding server over an HTTPS connection if necessary. The server's response is then relayed back to the client. This functionality makes it an indispensable tool for environments requiring the ability to handle simultaneous connections and data fetching without bottlenecking at the server end, while also providing a layer of content filtering.

## Usage
        To start the proxy server, run:
                ./myproxy <port_number> <forbidden file name> <access log file name>
        To test with Single Requests: 
                For a GET request (on a seprate window): curl -x http://localhost:<port_number> http://example.com
                
                For a HEAD request (on a sperate window): curl -x http://localhost:<port_number> -I http://example.com
        To test with Multiple Requests:
                Use a bash script or similar tool: 
                SCRIPT ``` bash: 
                #!/bin/bash

                # Set the proxy server address and port
                PROXY="http://localhost:<port_number>"

                # URL to request
                URL="http://example.com"

                # Number of requests
                N=10

                for ((i=1; i<=N; i++)); do
                echo "Request $i"
                curl -x $PROXY $URL &
                done
                wait
## Features
        HTTP/HTTPS Request Handling: Supports GET and HEAD methods for both unsecured and secured connections, allowing for content retrieval and metadata inspection without downloading the full content.
        Concurrent Processing: Leverages multithreading to handle multiple requests simultaneously, significantly improving throughput and server responsiveness.
        URL Parsing and Conversion: Accurately parses URLs from HTTP requests and automatically converts HTTP URLs to HTTPS when necessary, ensuring correct destination targeting and secure forwarding.
        Request Forwarding and Response Relay: Seamlessly forwards requests to the destination server and relays responses back to the client, maintaining transparency and efficiency.
        Content Filtering: Compares requested URLs against a list of forbidden sites, returning a 403 Forbidden error for any matches, thereby providing a basic level of content filtering.
        Secure Connections: Utilizes OpenSSL to establish secure connections to destination servers for HTTPS requests, ensuring data privacy and integrity.
        Error Handling and Logging: Provides detailed error responses to the client for various failure scenarios and logs all requests along with their outcomes to an access log file for audit and analysis.