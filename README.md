# XML Editor and Social Network Visualizer

## Project Overview
This project is a comprehensive application designed to parse, manipulate, and visualize XML files. The program supports a wide range of operations on XML files, such as checking for consistency, formatting, converting to JSON, and compressing. Additionally, it represents social network data as a graph and performs network analysis to extract valuable insights.

## Features
### Level 1 Features
1. **Command Line Mode**:
   - Perform operations using commands with input and output file locations.
   - Supported operations:
     - Verify XML consistency: `xml_editor verify`
     - Format XML: `xml_editor format`
     - Convert XML to JSON: `xml_editor json`
     - Minify XML: `xml_editor mini`
     - Compress XML: `xml_editor compress`
     - Decompress XML: `xml_editor decompress`

2. **GUI Mode**:
   - User-friendly interface to load and process XML files.
   - Visual display of errors, operation outputs, and results.
   - Save output files to user-defined locations.

3. **XML Operations**:
   - **Verify Consistency**: Detect and fix mismatched or missing XML tags.
   - **Formatting**: Prettify XML files with proper indentation.
   - **Conversion to JSON**: Convert XML data to JSON format.
   - **Minification**: Reduce file size by removing whitespace and newlines.
   - **Compression and Decompression**: Implement efficient file compression using techniques like Byte Pair Encoding.

### Level 2 Features
1. **Graph Representation**:
   - Represent user data (e.g., ID, name, posts, followers) as a graph.
   - Visualize the graph using tools or libraries.

2. **Network Analysis**:
   - Identify the most influential user (highest followers).
   - Determine the most active user (most connections).
   - Find mutual followers between specified users.
   - Suggest followers for users based on their network.

3. **Post Search**:
   - Search posts for specific words or topics.
