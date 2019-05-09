Generate code documentation in HTML-format using Doxygen.

Use the next commands to install the necessary tooling:

>sudo apt-get update
>sudo apt install doxygen
>sudo apt install doxygen-gui
>sudo apt-get install graphviz


Goto ...../fccfMQTT-docs

In this directory the file Doxyfile is found.
This file contains the configuration data for genearting the documentation.

Start the doxygen wizard:
>doxywizard

The started tooling needs to use the already available Doxyfile file.
Choose File, Open to choose the file Doxyfile.

Always use relative paths for INPUT files. 

By selecting Run tab the documentaion will be generated in the subdirectory 
html in html format.

