\anchor milodatabaserestapicommunication 
 
Milo Code DB main ([online](https://qtdocs.milosolutions.com/milo-code-db/main/) | [offline](\ref milodatabasemain)) 

RestAPICommunication is a project that shows sample code to communicate via REST API.

It was created for the MiloCodeDatabase project.


# Main features: # {#main-features}  

    1. core classes for REST API communication  
    2. class to managment of request  
    3. class for queuing requests  
    4. prioritization of request  
    5. classes based at inteligent pointers  
    6. possibility to inherit  
    7. one API endpoint represented by one class (see in example)  
    8. easy way to handle multiple REST API  
    9. very simple to use in other project  


# How use this in my project? # {#howtouse}

    1. include .pri file in project .pro file - include(mrestapi/mrestapi.pri)  
    2. set configuration for API (base url) - use RestRequestConfig or create own class based on it (if needed)
    3. create RestRequestManager
    4. create classes for each endpoint (inherit from RestRequest)
    5. look to the example ;)  


# How create request (create classes for endpoints)? # {#howtocreate}  

    Description based on LoginRequest class.  
    1. create class and inherit form Request class (e.g. MrBabuRequest), implement setMethod() metod - do this point only one time  
    2. select the name for the class which will be represented API endpoint - associated with what is doing the endpoint  
    3. create class and inherit form class created in point 1 ( eg class LoginRequest : public MrBabuRequest)  
    4. pass part of url in class constructor (e.g. MrBabuRequest("login") )  
    5. set the request type and priority  
    6. implement parse() method  
    7. add new signal to emit information about the received data  



For example usage, see /example/RestAPICommunication.pro file.  

In example project we can see comunication with two API.  
The first example is based on MrBabuQt project and it not sent any real request - but it is very good part of code.  
The second example is a simple communication with the weather API.



This project is fully docummented - please check doxygen docs or see the comments directly in the source file(s).

# License # {#license}

This project is licensed under the MIT License - see the LICENSE-MiloCodeDB.txt file for details