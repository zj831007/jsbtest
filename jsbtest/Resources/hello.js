require("jsb.js");

//try {
    
    
    var http = new XMLHttpRequest();
    http.open("POST","http://127.0.0.1/t.php",true);
    http.send("a=1&b=2");
    
    function onreadystatechange(){
        cc.log(http.status);
        cc.log(http.readyState);
        cc.log(http.responseText);
    }
    
    
    
    __jsc__.garbageCollect();

    // LOADING PLAY SCENE UNTILL CCBREADER IS FIXED
   

//} catch(e) {log(e);}

